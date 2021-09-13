// WebSocketStuff.hpp - Header for the Websocket things of the library.
// May 13, 2021
// Chris M.
// https://github.com/RealTimeChris

#pragma once

#ifndef _WEBSOCKET_STUFF_
#define _WEBSOCKET_STUFF_

#include "../pch.h"
#include "DataParsingFunctions.hpp"

namespace DiscordCoreInternal {

	enum class WebSocketEventType {
		Application_Command_Create = 0,
		Application_Command_Update = 1,
		Application_Command_Delete = 2,
		Channel_Create = 3,
		Channel_Update = 4,
		Channel_Delete = 5,
		Channel_Pins_Update = 6,
		Thread_Create = 7,
		Thread_Update = 8,
		Thread_Delete = 9,
		Thread_List_Sync = 10,
		Thread_Member_Update = 11,
		Thread_Members_Update = 12,
		Guild_Create = 13,
		Guild_Update = 14,
		Guild_Delete = 15,
		Guild_Ban_Add = 16,
		Guild_Ban_Remove = 17,
		Guild_Emojis_Update = 18,
		Guild_Stickers_Update = 19,
		Guild_Integrations_Update = 20,
		Guild_Member_Add = 21,
		Guild_Member_Remove = 22,
		Guild_Member_Update = 23,
		Guild_Members_Chunk = 24,
		Guild_Role_Create = 25,
		Guild_Role_Update = 26,
		Guild_Role_Delete = 27,
		Integration_Create = 28,
		Integration_Update = 29,
		Integration_Delete = 30,
		Interaction_Create = 31,
		Invite_Create = 32,
		Invite_Delete = 33,
		Message_Create = 34,
		Message_Update = 35,
		Message_Delete = 36,
		Message_Delete_Bulk = 37,
		Message_Reaction_Add = 38,
		Message_Reaction_Remove = 39,
		Message_Reaction_Remove_All = 40,
		Message_Reaction_Remove_Emoji = 41,
		Presence_Update = 42,
		Stage_Instance_Create = 43,
		Stage_Instance_Delete = 44,
		Stage_Instance_Update = 45,
		Typing_Start = 46,
		User_Update = 47,
		Voice_State_Update = 48,
		Voice_Server_Update = 49,
		Webhooks_Update = 50
	};

	struct WebSocketWorkload {
		WebSocketEventType eventType{};
		json payLoad{};
	};

	struct GetVoiceConnectionData {
		string channelId{ "" };
		string guildId{ "" };
		string userId{ "" };
	};

	class WebSocketConnectionAgent : ThreadContext, agent {
	public:

		template <class _Ty>
		friend _CONSTEXPR20_DYNALLOC void std::_Destroy_in_place(_Ty& _Obj) noexcept;
		friend class DiscordCoreAPI::DiscordCoreClient;
		friend class DiscordCoreAPI::VoiceConnection;
		friend class VoiceChannelWebSocketAgent;
		friend class DiscordCoreAPI::BotUser;

		WebSocketConnectionAgent(unbounded_buffer<json>* target, hstring botTokenNew, bool* doWeQuitNew)
			:ThreadContext(*ThreadManager::getThreadContext().get()), agent(*this->scheduler->scheduler) {
			this->collectVoiceConnectionDataBuffer = make_shared<unbounded_buffer<GetVoiceConnectionData>>();
			this->voiceConnectionDataBuffer = make_shared<unbounded_buffer<VoiceConnectionData>>();
			this->webSocketWorkloadTarget = target;
			this->botToken = botTokenNew;
			this->doWeQuit = doWeQuitNew;
		}

	protected:

		int intentsValue{ ((1 << 0) + (1 << 1) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5) + (1 << 6) + (1 << 7) + (1 << 8) + (1 << 9) + (1 << 10) + (1 << 11) + (1 << 12) + (1 << 13) + (1 << 14)) };
		shared_ptr<unbounded_buffer<GetVoiceConnectionData>> collectVoiceConnectionDataBuffer{ nullptr };
		shared_ptr<unbounded_buffer<VoiceConnectionData>> voiceConnectionDataBuffer{ nullptr };
		unbounded_buffer<json>* webSocketWorkloadTarget{ nullptr };
		unbounded_buffer<exception> errorBuffer{ nullptr };
		GetVoiceConnectionData voiceConnectInitData{};
		ThreadPoolTimer heartbeatTimer{ nullptr };
		VoiceConnectionData voiceConnectionData{};
		MessageWebSocket webSocket{ nullptr };
		bool didWeReceiveHeartbeatAck{ true };
		DataWriter messageWriter{ nullptr };
		bool serverUpdateCollected{ false };
		bool stateUpdateCollected{ false };
		event_token messageReceivedToken{};
		const int maxReconnectTries{ 10 };
		bool areWeCollectingData{ false };
		int currentReconnectTries{ 0 };
		int lastNumberReceived{ 0 };
		int heartbeatInterval{ 0 };
		hstring socketPath{ L"" };
		event_token closedToken{};
		bool* doWeQuit{ nullptr };
		hstring sessionID{ L"" };
		hstring botToken{ L"" };

		void setSocketPath(string socketPathBase) {
			std::wstringstream stream;
			stream << DiscordCoreInternal::getSocketPath(to_hstring(socketPathBase)).c_str();
			stream << L"/?v=9&encoding=json";
			this->socketPath = stream.str();
		}

		void getVoiceConnectionData(GetVoiceConnectionData doWeCollect) {
			this->voiceConnectInitData = doWeCollect;
			UpdateVoiceStateData dataPackage;
			dataPackage.channelId = doWeCollect.channelId;
			dataPackage.guildId = doWeCollect.guildId;
			dataPackage.selfDeaf = true;
			dataPackage.selfMute = false;
			string newString = getVoiceStateUpdatePayload(dataPackage);
			this->areWeCollectingData = true;
			this->sendMessage(newString);
		}

		~WebSocketConnectionAgent() {
			this->terminate();
			this->getError();
		}

		void getError() {
			exception error;
			while (try_receive(errorBuffer, error)) {
				cout << "WebSocketConnectionAgent Error: " << error.what() << endl;
			}
		}

		void run() {
			try {
				this->connect();
			}
			catch (exception& e) {
				send(this->errorBuffer, e);
				done();
			}
		}

		void sendMessage(string& text) {
			try {
				string message = text;
				if (message.empty()) {
					cout << "Please specify text to send" << endl;
					return;
				}

				cout << "Sending Message: ";
				cout << message << endl;

				if (this->messageWriter != nullptr) {
					this->messageWriter.WriteString(to_hstring(message));
					this->messageWriter.StoreAsync().get();
				}

				cout << "Send Complete" << endl << endl;
			}
			catch (...) {
				auto exceptionNew = current_exception();
				try {
					rethrow_exception(exceptionNew);
				}
				catch (exception& e) {
					cout << "WebSocketConnectionAgent::sendMessage() Error: " << e.what() << endl;
				}
			}
		}

		void connect() {
			this->webSocket = MessageWebSocket();
			this->messageWriter = DataWriter(this->webSocket.OutputStream());
			this->webSocket.Control().MessageType(SocketMessageType::Utf8);
			this->messageWriter.UnicodeEncoding(UnicodeEncoding::Utf8);
			this->closedToken = this->webSocket.Closed({ this, &WebSocketConnectionAgent::onClosed });
			this->messageReceivedToken = this->webSocket.MessageReceived({ this, &WebSocketConnectionAgent::onMessageReceived });
			this->webSocket.ConnectAsync(winrt::Windows::Foundation::Uri(this->socketPath)).get();
		}

		void onClosed(IWebSocket const&, WebSocketClosedEventArgs const& args) {
			wcout << L"WebSocket Closed; Code: " << args.Code() << ", Reason: " << args.Reason().c_str() << endl;
			if (this->maxReconnectTries > this->currentReconnectTries) {
				this->currentReconnectTries += 1;
				this->cleanup();
				this->connect();
				string resume = getResumePayload(to_string(this->botToken), to_string(this->sessionID), this->lastNumberReceived);
				this->sendMessage(resume);
			}
			else {
				this->terminate();
			}
		}

		void sendHeartBeat() {
			string heartbeat = getHeartbeatPayload(this->lastNumberReceived);
			this->sendMessage(heartbeat);
			this->didWeReceiveHeartbeatAck = false;
		}

		void onMessageReceived(MessageWebSocket const&, MessageWebSocketMessageReceivedEventArgs const& args) {
			hstring message;
			if (args != nullptr) {
				if (args.IsMessageComplete()) {
					if (args.GetDataReader() != nullptr) {
						args.GetDataReader().UnicodeEncoding(UnicodeEncoding::Utf8);
						if (args.GetDataReader().UnconsumedBufferLength() > 0) {
							message = args.GetDataReader().ReadString(args.GetDataReader().UnconsumedBufferLength());
						}
					}
				}
			}
			json payload = payload.parse(to_string(message));

			send(*this->webSocketWorkloadTarget, payload);

			if (this->areWeCollectingData && payload.at("t") == "VOICE_SERVER_UPDATE" && !this->serverUpdateCollected) {
				if (this->serverUpdateCollected != true && this->stateUpdateCollected != true) {
					this->voiceConnectionData = VoiceConnectionData();
					this->voiceConnectionData.endPoint = payload.at("d").at("endpoint").get<string>();
					this->voiceConnectionData.token = payload.at("d").at("token").get<string>();
					this->serverUpdateCollected = true;
				}
				else {
					this->voiceConnectionData.endPoint = payload.at("d").at("endpoint").get<string>();
					this->voiceConnectionData.token = payload.at("d").at("token").get<string>();
					this->serverUpdateCollected = true;
					send(*this->voiceConnectionDataBuffer, this->voiceConnectionData);
					this->serverUpdateCollected = false;
					this->stateUpdateCollected = false;
					this->areWeCollectingData = false;
				}
			}
			if (this->areWeCollectingData && payload.at("t") == "VOICE_STATE_UPDATE" && !this->stateUpdateCollected && payload.at("d").at("member").at("user").at("id") == this->voiceConnectInitData.userId) {
				if (this->stateUpdateCollected != true && this->serverUpdateCollected != true) {
					this->voiceConnectionData = VoiceConnectionData();
					this->voiceConnectionData.sessionId = payload.at("d").at("session_id").get<string>();
					this->stateUpdateCollected = true;
				}
				else {
					this->voiceConnectionData.sessionId = payload.at("d").at("session_id").get<string>();
					send(*this->voiceConnectionDataBuffer, this->voiceConnectionData);
					this->serverUpdateCollected = false;
					this->stateUpdateCollected = false;
					this->areWeCollectingData = false;
				}
			}

			if (payload.at("s") >= 0) {
				this->lastNumberReceived = payload.at("s");
			}

			if (payload.at("t") == "PRESENCE_UPDATE") {
				return;
			}

			if (payload.at("t") == "GUILD_CREATE") {
				return;
			}

			if (payload.at("t") == "READY") {
				string sessionIDTemp;
				sessionIDTemp = payload.at("d").at("session_id");
				this->sessionID = to_hstring(sessionIDTemp);
			}

			if (payload.at("op") == 1) {
				this->sendHeartBeat();
			}

			if (payload.at("op") == 7) {
				cout << "Reconnecting (Type 7)!" << endl << endl;
				if (this->maxReconnectTries > this->currentReconnectTries) {
					this->currentReconnectTries += 1;
					this->cleanup();
					this->connect();
					string resume = getResumePayload(to_string(this->botToken), to_string(this->sessionID), this->lastNumberReceived);
					this->sendMessage(resume);
				}
				else {
					this->terminate();
				}
			}

			if (payload.at("op") == 9) {
				cout << "Reconnecting (Type 9)!" << endl << endl;
				if (this->maxReconnectTries > this->currentReconnectTries) {
					this->currentReconnectTries += 1;
					this->cleanup();
					this->connect();
					string resume = getResumePayload(to_string(this->botToken), to_string(this->sessionID), this->lastNumberReceived);
					this->sendMessage(resume);
				}
				else {
					this->terminate();
				}
			}

			if (payload.at("op") == 10) {
				this->heartbeatInterval = payload.at("d").at("heartbeat_interval");
				TimerElapsedHandler onHeartBeat = [this](ThreadPoolTimer timer) {
					WebSocketConnectionAgent::sendHeartBeat();
				};
				this->heartbeatTimer = this->heartbeatTimer.CreatePeriodicTimer(onHeartBeat, winrt::Windows::Foundation::TimeSpan(this->heartbeatInterval * 10000));
				std::string identity = getIdentifyPayload(to_string(this->botToken), this->intentsValue);
				this->sendMessage(identity);
			}

			if (payload.at("op") == 11) {
				this->didWeReceiveHeartbeatAck = true;
			}

			cout << "Message received from WebSocket: " << to_string(message) << endl << endl;
		};

		void cleanup() {
			if (this->messageWriter != nullptr) {
				this->messageWriter.DetachStream();
				this->messageWriter.Close();
				this->messageWriter = nullptr;
			}

			if (this->webSocket != nullptr) {
				this->webSocket.Close(1000, L"Closed due to user request.");
				this->webSocket = nullptr;
			}

			if (this->heartbeatTimer) {
				this->heartbeatTimer.Cancel();
				this->heartbeatTimer = nullptr;
			}
		}

		void terminate() {
			*this->doWeQuit = true;
			this->done();
			this->cleanup();
		}

	};

	class VoiceChannelWebSocketAgent : ThreadContext, agent {
	public:

		friend class DiscordCoreAPI::VoiceConnection;
		friend class Guild;

		VoiceChannelWebSocketAgent(unbounded_buffer<bool>* readyBufferNew, VoiceConnectInitData initDataNew, shared_ptr<WebSocketConnectionAgent> webSocketConnectionAgentNew)
			:
			ThreadContext(*ThreadManager::getThreadContext(ThreadType::Music).get()),
			agent(*this->scheduler->scheduler) {
			this->voiceConnectionDataBuffer = webSocketConnectionAgentNew->voiceConnectionDataBuffer;
			this->webSocketConnectionAgent = webSocketConnectionAgentNew;
			this->voiceConnectInitData = initDataNew;
			GetVoiceConnectionData dataPackage;
			dataPackage.channelId = this->voiceConnectInitData.channelId;
			dataPackage.guildId = this->voiceConnectInitData.guildId;
			dataPackage.userId = this->voiceConnectInitData.userId;
			this->webSocketConnectionAgent->getVoiceConnectionData(dataPackage);
			this->readyBuffer = readyBufferNew;
		}

		void sendVoiceData(vector<uint8_t> data) {
			vector<uint8_t> message = data;
			if (message.size() == 0) {
				cout << "Please specify voice data to send" << endl << endl;
				return;
			}
			else {
				this->dataWriter.WriteBytes(message);
				this->dataWriter.StoreAsync().get();
			}
		}

		void sendMessage(string text) {
			string message = text;
			if (message.empty()) {
				cout << "Please specify text to send" << endl;
				return;
			}

			cout << "Sending Voice Message: ";
			cout << message << endl;

			try {
				// Buffer any data we want to send.
				winrt::Windows::Storage::Streams::InMemoryRandomAccessStream randomAccessStream;
				DataWriter dataWriterMessage(randomAccessStream);
				dataWriterMessage.UnicodeEncoding(UnicodeEncoding::Utf8);
				dataWriterMessage.WriteString(to_hstring(message));
				dataWriterMessage.StoreAsync().get();
				randomAccessStream.FlushAsync().get();
				if (randomAccessStream.CanRead()) {
					DataReader dataReader(randomAccessStream.GetInputStreamAt(0));
					dataReader.UnicodeEncoding(UnicodeEncoding::Utf8);
					dataReader.LoadAsync((uint32_t)message.length()).get();
					IBuffer buffer = dataReader.ReadBuffer((uint32_t)message.length());
					this->webSocket.OutputStream().WriteAsync(buffer).get();
				}

				cout << "Send Complete" << endl << endl;
			}
			catch (...) {
				auto exceptionNew = current_exception();
				try {
					rethrow_exception(exceptionNew);
				}
				catch (exception& e) {
					cout << "VoiceChannelWebSocketAgent::sendMessage() Error: " << e.what() << endl;
				}
			}
			
		}

		~VoiceChannelWebSocketAgent() {
			this->terminate();
			this->getError();
		}

	protected:

		shared_ptr<unbounded_buffer<VoiceConnectionData>> voiceConnectionDataBuffer{ nullptr };
		shared_ptr<WebSocketConnectionAgent> webSocketConnectionAgent{ nullptr };
		unbounded_buffer<bool> readyToVoiceConnectBuffer{ nullptr };
		unbounded_buffer<exception> errorBuffer{ nullptr };
		unbounded_buffer<bool>* readyBuffer{ nullptr };
		VoiceConnectInitData voiceConnectInitData{};
		ThreadPoolTimer heartbeatTimer{ nullptr };
		VoiceConnectionData voiceConnectionData{};
		DatagramSocket voiceSocket{ nullptr };
		MessageWebSocket webSocket{ nullptr };
		bool didWeReceiveHeartbeatAck{ true };
		event_token voiceDataReceivedToken{};
		event_token messageReceivedToken{};
		const int maxReconnectTries{ 10 };
		DataWriter dataWriter{ nullptr };
		int currentReconnectTries{ 0 };
		bool areWeWaitingForIp{ true };
		int lastNumberReceived{ 0 };
		int heartbeatInterval{ 0 };
		event_token closedToken{};

		void getError() {
			exception error;
			while (try_receive(errorBuffer, error)) {
				cout << "VoiceChannelWebSocketAgent Error: " << error.what() << endl << endl;
			}
		}

		void connect() {
			try {
				this->voiceConnectionData = receive(this->voiceConnectionDataBuffer.get(), 20000);
				this->voiceConnectionData.endPoint = "wss://" + this->voiceConnectionData.endPoint + "/?v=4";
				this->heartbeatTimer = ThreadPoolTimer(nullptr);
				this->webSocket = MessageWebSocket();
				this->webSocket.Control().MessageType(SocketMessageType::Utf8);
				this->closedToken = this->webSocket.Closed({ this, &VoiceChannelWebSocketAgent::onClosed });
				this->messageReceivedToken = this->webSocket.MessageReceived({ this, &VoiceChannelWebSocketAgent::onMessageReceived });
				this->webSocket.ConnectAsync(winrt::Windows::Foundation::Uri(to_hstring(this->voiceConnectionData.endPoint))).get();
			}
			catch (...) {
				auto exceptionNew = current_exception();
				try {
					rethrow_exception(exceptionNew);
				}
				catch (exception& e) {
					cout << "VoiceChannelWebSocketAgent::connect() Error: " << e.what() << endl;
				}
				if (this->maxReconnectTries > this->currentReconnectTries) {
					this->currentReconnectTries += 1;
					GetVoiceConnectionData dataPackage;
					dataPackage.channelId = this->voiceConnectInitData.channelId;
					dataPackage.guildId = this->voiceConnectInitData.guildId;
					dataPackage.userId = this->voiceConnectInitData.userId;
					this->webSocketConnectionAgent->getVoiceConnectionData(dataPackage);
					this->connect();
				}
				else {
					this->terminate();
				}
			}
		}

		void collectExternalIP() {
			unsigned char packet[70] = { 0 };
			packet[0] = (this->voiceConnectionData.audioSSRC >> 24) & 0xff;
			packet[1] = (this->voiceConnectionData.audioSSRC >> 16) & 0xff;
			packet[2] = (this->voiceConnectionData.audioSSRC >> 8) & 0xff;
			packet[3] = (this->voiceConnectionData.audioSSRC) & 0xff;
			vector<uint8_t> sendVector;
			for (unsigned int x = 0; x < 70; x += 1) {
				sendVector.push_back(packet[x]);
			}
			this->sendVoiceData(sendVector);
		}

		void voiceConnect() {
			try {
				receive(this->readyToVoiceConnectBuffer, 10000);
				this->voiceSocket = DatagramSocket();
				this->voiceSocket.Control().QualityOfService(SocketQualityOfService::LowLatency);
				winrt::Windows::Networking::HostName hostName(to_hstring(this->voiceConnectionData.voiceIp));
				auto endpointPair = this->voiceSocket.GetEndpointPairsAsync(hostName, to_hstring(this->voiceConnectionData.voicePort)).get();
				this->voiceDataReceivedToken = this->voiceSocket.MessageReceived({ this,&VoiceChannelWebSocketAgent::onVoiceDataReceived });
				this->voiceSocket.ConnectAsync(endpointPair.First().Current()).get();
				this->dataWriter = DataWriter(this->voiceSocket.GetOutputStreamAsync(hostName, to_hstring(this->voiceConnectionData.voicePort)).get());
				this->dataWriter.UnicodeEncoding(UnicodeEncoding::Utf8);
			}
			catch (...) {
				auto exceptionNew = current_exception();
				try {
					rethrow_exception(exceptionNew);
				}
				catch (exception& e) {
					cout << "VoiceChannelWebSocketAgent::voiceConnect() Error: " << e.what() << endl;
				}
			}
		}

		void run() {
			try {
				this->connect();
			}
			catch (const exception& e) {
				send(errorBuffer, e);
				done();
			}
		}

		void onClosed(IWebSocket const&, WebSocketClosedEventArgs const& args) {
			wcout << L"Voice WebSocket Closed; Code: " << args.Code() << ", Reason: " << args.Reason().c_str() << endl;
			if (args.Code() != 1000 && args.Code() != 4014) {
				if (this->maxReconnectTries > this->currentReconnectTries) {
					this->currentReconnectTries += 1;
					this->cleanup();
					GetVoiceConnectionData dataPackage;
					dataPackage.channelId = this->voiceConnectInitData.channelId;
					dataPackage.guildId = this->voiceConnectInitData.guildId;
					dataPackage.userId = this->voiceConnectInitData.userId;
					this->webSocketConnectionAgent->getVoiceConnectionData(dataPackage);
					this->connect();
				}
				else {
					this->terminate();
				}
			}
		}

		void sendHeartBeat(bool* didWeReceiveHeartbeatAckNew) {
			string heartbeatPayload = getVoiceHeartbeatPayload(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
			this->sendMessage(heartbeatPayload);
			*didWeReceiveHeartbeatAckNew = true;
		}

		void onMessageReceived(MessageWebSocket msgWebSocket, MessageWebSocketMessageReceivedEventArgs args) {

			hstring message;
			DataReader dataReader{ nullptr };
			if (args.GetDataReader() != nullptr) {
				dataReader = args.GetDataReader();
				dataReader.UnicodeEncoding(UnicodeEncoding::Utf8);
				if (dataReader.UnconsumedBufferLength() > 0) {
					message = dataReader.ReadString(dataReader.UnconsumedBufferLength());
				}
			}
			json payload = payload.parse(to_string(message));
			cout << "Message received from Voice WebSocket: " << to_string(message) << endl << endl;

			if (payload.contains("op")) {
				if (payload.at("op") == 6) {
					this->didWeReceiveHeartbeatAck = true;
				}

				if (payload.at("op") == 2) {
					this->voiceConnectionData.audioSSRC = payload.at("d").at("ssrc");
					this->voiceConnectionData.voiceIp = payload.at("d").at("ip");
					this->voiceConnectionData.voicePort = to_string(payload.at("d").at("port"));
					for (auto value : payload.at("d").at("modes")) {
						if (value == "xsalsa20_poly1305") {
							this->voiceConnectionData.voiceEncryptionMode = value;
						}
					}
					send(this->readyToVoiceConnectBuffer, true);
					this->voiceConnect();
					this->collectExternalIP();
					while (this->areWeWaitingForIp) { cout << "Were here!" << endl; };
					string protocolPayloadSelectString = getSelectProtocolPayload(this->voiceConnectionData.voicePort, this->voiceConnectionData.externalIp, this->voiceConnectionData.voiceEncryptionMode);
					this->sendMessage(protocolPayloadSelectString);
				}

				if (payload.at("op") == 4) {
					for (unsigned int x = 0; x < payload.at("d").at("secret_key").size(); x += 1) {
						this->voiceConnectionData.secretKey.push_back(payload.at("d").at("secret_key").at(x).get<uint8_t>());
					}
					for (auto value : this->voiceConnectionData.secretKey) {
						this->voiceConnectionData.keys.push_back(value);
					}
					send(this->readyBuffer, true);
				}

				if (payload.at("op") == 8) {
					if (payload.at("d").contains("heartbeat_interval")) {
						this->heartbeatInterval = (int)payload.at("d").at("heartbeat_interval").get<float>();
					}
					string identifyPayload = getVoiceIdentifyPayload(this->voiceConnectionData, this->voiceConnectInitData);
					this->sendMessage(identifyPayload);
					TimerElapsedHandler onHeartBeat = [&, this](ThreadPoolTimer timer) ->void {
						VoiceChannelWebSocketAgent::sendHeartBeat(&this->didWeReceiveHeartbeatAck);
						this->didWeReceiveHeartbeatAck = false;
					};
					this->heartbeatTimer = this->heartbeatTimer.CreatePeriodicTimer(onHeartBeat, winrt::Windows::Foundation::TimeSpan(this->heartbeatInterval * 10000));
				}
			}
		}

		void onVoiceDataReceived(DatagramSocket const&, DatagramSocketMessageReceivedEventArgs const& args) {

			string message;
			DataReader dataReader{ nullptr };
			if (args.GetDataReader() != nullptr) {
				dataReader = args.GetDataReader();
				dataReader.UnicodeEncoding(UnicodeEncoding::Utf8);
				vector<uint8_t> newVector(dataReader.UnconsumedBufferLength());
				if (dataReader.UnconsumedBufferLength() > 0) {
					dataReader.ReadBytes(newVector);
				}
				for (auto value : newVector) {
					message.push_back(value);
				}
			}

			if (this->areWeWaitingForIp) {
				this->areWeWaitingForIp = false;
				this->voiceConnectionData.externalIp = message.substr(4, message.find('\u0000', 4) - 4);
			}
		}

		void cleanup() {
			if (this != nullptr) {
				if (this->voiceSocket != nullptr) {
					this->voiceSocket.Close();
					this->voiceSocket = nullptr;
				}
				if (this->webSocket != nullptr) {
					this->webSocket.Close(1000, L"Disconnecting");
					this->webSocket = nullptr;
				}
				if (this->heartbeatTimer != nullptr) {
					this->heartbeatTimer.Cancel();
					this->heartbeatTimer = nullptr;
				}

			}
		}

		void terminate() {
			done();
			this->cleanup();
		}

	};

	class WebSocketReceiverAgent : ThreadContext, agent {
	public:

		template <class _Ty>
		friend _CONSTEXPR20_DYNALLOC void std::_Destroy_in_place(_Ty& _Obj) noexcept;
		template <class _Ty>
		friend struct default_delete;
		friend class DiscordCoreAPI::DiscordCoreClient;

		WebSocketReceiverAgent()
			: ThreadContext(*ThreadManager::getThreadContext().get()),
			agent(*this->scheduler->scheduler) {}

	protected:
		unbounded_buffer<WebSocketWorkload> webSocketWorkloadTarget{ nullptr };
		unbounded_buffer<json> webSocketWorkloadSource{ nullptr };
		unbounded_buffer<exception> errorBuffer{ nullptr };
		bool doWeQuit{ false };

		void getError() {
			exception error;
			while (try_receive(errorBuffer, error)) {
				cout << "WebSocketReceiverAgent Error: " << error.what() << endl << endl;
			}
		}

		void run() {
			try {
				while (doWeQuit == false) {
					try {
						json payload = receive(this->webSocketWorkloadSource, 15000);
						this->onMessageReceived(payload);
					}
					catch (operation_timed_out&) {
						continue;
					}					
				}
			}
			catch (const exception& e) {
				send(errorBuffer, e);
			}
			done();
		}

		void onMessageReceived(json payload) {
			WebSocketWorkload workload;
			workload.payLoad = payload.at("d");

			if (payload.at("t") == "APPLICATION_COMMAND_CREATE") {
				workload.eventType = WebSocketEventType::Application_Command_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "APPLICATION_COMMAND_UPDATE") {
				workload.eventType = WebSocketEventType::Application_Command_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "APPLICATION_COMMAND_DELETE") {
				workload.eventType = WebSocketEventType::Application_Command_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "APPLICATION_COMMAND_DELETE") {
				workload.eventType = WebSocketEventType::Application_Command_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "CHANNEL_CREATE") {
				workload.eventType = WebSocketEventType::Channel_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "CHANNEL_UPDATE") {
				workload.eventType = WebSocketEventType::Channel_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "CHANNEL_DELETE") {
				workload.eventType = WebSocketEventType::Channel_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "CHANNEL_PINS_UPDATE") {
				workload.eventType = WebSocketEventType::Channel_Pins_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "THREAD_CREATE") {
				workload.eventType = WebSocketEventType::Thread_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "THREAD_UPDATE") {
				workload.eventType = WebSocketEventType::Thread_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "THREAD_DELETE") {
				workload.eventType = WebSocketEventType::Thread_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "THREAD_LIST_SYNC") {
				workload.eventType = WebSocketEventType::Thread_List_Sync;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "THREAD_MEMBER_UPDATE") {
				workload.eventType = WebSocketEventType::Thread_Member_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "THREAD_MEMBERS_UPDATE") {
				workload.eventType = WebSocketEventType::Thread_Members_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_CREATE") {
				workload.eventType = WebSocketEventType::Guild_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_UPDATE") {
				workload.eventType = WebSocketEventType::Guild_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_DELETE") {
				workload.eventType = WebSocketEventType::Guild_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_BAN_ADD") {
				workload.eventType = WebSocketEventType::Guild_Ban_Add;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_BAN_REMOVE") {
				workload.eventType = WebSocketEventType::Guild_Ban_Remove;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_EMOJIS_UPDATE") {
				workload.eventType = WebSocketEventType::Guild_Emojis_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_STICKERS_UPDATE") {
				workload.eventType = WebSocketEventType::Guild_Stickers_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_INTEGRATIONS_UPDATE") {
				workload.eventType = WebSocketEventType::Guild_Integrations_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_MEMBER_ADD") {
				workload.eventType = WebSocketEventType::Guild_Member_Add;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_MEMBER_REMOVE") {
				workload.eventType = WebSocketEventType::Guild_Member_Remove;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_MEMBER_UPDATE") {
				workload.eventType = WebSocketEventType::Guild_Member_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_MEMBERS_CHUNK") {
				workload.eventType = WebSocketEventType::Guild_Members_Chunk;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_ROLE_CREATE") {
				workload.eventType = WebSocketEventType::Guild_Role_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_ROLE_UPDATE") {
				workload.eventType = WebSocketEventType::Guild_Role_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "GUILD_ROLE_DELETE") {
				workload.eventType = WebSocketEventType::Guild_Role_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "INTEGRATION_ROLE_CREATE") {
				workload.eventType = WebSocketEventType::Integration_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "INTEGRATION_ROLE_UPDATE") {
				workload.eventType = WebSocketEventType::Integration_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "INTEGRATION_ROLE_DELETE") {
				workload.eventType = WebSocketEventType::Integration_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "INTERACTION_CREATE") {
				workload.eventType = WebSocketEventType::Interaction_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "INVITE_CREATE") {
				workload.eventType = WebSocketEventType::Invite_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "INVITE_DELETE") {
				workload.eventType = WebSocketEventType::Invite_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "MESSAGE_CREATE") {
				workload.eventType = WebSocketEventType::Message_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "MESSAGE_UPDATE") {
				workload.eventType = WebSocketEventType::Message_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "MESSAGE_DELETE") {
				workload.eventType = WebSocketEventType::Message_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "MESSAGE_DELETE_BULK") {
				workload.eventType = WebSocketEventType::Message_Delete_Bulk;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "MESSAGE_REACTION_ADD") {
				workload.eventType = WebSocketEventType::Message_Reaction_Add;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "MESSAGE_REACTION_REMOVE") {
				workload.eventType = WebSocketEventType::Message_Reaction_Remove;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "MESSAGE_REACTION_REMOVE_ALL") {
				workload.eventType = WebSocketEventType::Message_Reaction_Remove_All;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "MESSAGE_REACTION_REMOVE_EMOJI") {
				workload.eventType = WebSocketEventType::Message_Reaction_Remove_Emoji;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "PRESENCE_UPDATE") {
				workload.eventType = WebSocketEventType::Presence_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "STAGE_INSTANCE_CREATE") {
				workload.eventType = WebSocketEventType::Stage_Instance_Create;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "STAGE_INSTANCE_DELETE") {
				workload.eventType = WebSocketEventType::Stage_Instance_Delete;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "STAGE_INSTANCE_UPDATE") {
				workload.eventType = WebSocketEventType::Stage_Instance_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "TYPING_START") {
				workload.eventType = WebSocketEventType::Typing_Start;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "USER_UPDATE") {
				workload.eventType = WebSocketEventType::User_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "VOICE_STATE_UPDATE") {
				workload.eventType = WebSocketEventType::Voice_State_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "VOICE_SERVER_UPDATE") {
				workload.eventType = WebSocketEventType::Voice_Server_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

			if (payload.at("t") == "WEBHOOKS_UPDATE") {
				workload.eventType = WebSocketEventType::Webhooks_Update;
				send(this->webSocketWorkloadTarget, workload);
			}

		}

		void terminate() {
			this->doWeQuit = true;
		}

		~WebSocketReceiverAgent() {
			this->terminate();
			this->getError();
		}
	};
}
#endif
