// VoiceConnection.hpp - Header for the voice connection class.
// Jul 15, 2021
// Chris M.
// https://github.com/RealTimeChris

#ifndef VOICE_CONNECTION
#define VOICE_CONNECTION

#pragma comment(lib, "libsodium.lib")

#include "FoundationEntities.hpp"
#include "WebSocketEntities.hpp"
#include "AudioEncoder.hpp"
#include "CoRoutine.hpp"
#include <sodium.h>

namespace DiscordCoreAPI {

	class DiscordCoreAPI_Dll AudioEncrypter {
	public:

		AudioEncrypter();

		std::vector<uint8_t> encryptSingleAudioFrame(EncodedFrameData& bufferToSend, int32_t audioSSRC, std::string keys);

	protected:

		int32_t sequenceIndex{ 0 };
		int32_t timeStamp{ 0 };
	};

	/**
	* \addtogroup voice_connection
	* @{
	*/
	/// VoiceConnection class - represents the connection to a given voice channel. \brief VoiceConnection class - represents the connection to a given voice channel.
	class DiscordCoreAPI_Dll VoiceConnection {
	public:

		friend SoundCloudAPI;
		friend YouTubeAPI;
		friend SongAPI;
		friend Guild;

		Event<CoRoutine<void>, SongCompletionEventData> onSongCompletionEvent{};

		VoiceConnection(DiscordCoreInternal::BaseSocketAgent* BaseSocketAgentNew);

		VoiceConnection() = default;

		/// Send a single frame of audio data. Be sure to send one frame every x ms apart where x is the duration of each frame, and also be sure to call SongAPI::play() before calling this. \brief Send a single frame of audio data. Be sure to send one frame every x ms apart where x is the duration of each frame, and also be sure to call SongAPI::play() before calling this.
		/// \param frameData A single frame worth of audio data.
		void sendSingleFrame(AudioFrameData frameData);

		/// For setting up behavior in response to a completed song. \brief For setting up behavior in response to a completed song.
		/// \param handler A delegate taking a SongCompletionEventData structure as an argument.
		/// \returns An event_token for later de-registering the event. 
		EventDelegateToken onSongCompletion(EventDelegate<CoRoutine<void>, SongCompletionEventData> handler);

		/// For de-registering the event-handler std::function that was previously registered. \brief For de-registering the event-handler std::function that was previously registered.
		/// \param token The event_token that was returned from the registration std::function.
		void onSongCompletion(EventDelegateToken token);

		/// Collects the currently connected-to voice Channel's id. \brief Collects the currently connected-to voice Channel's id.
		/// \returns A std::string containing the Channel's id. 
		std::string getChannelId();

	protected:
		
		std::unique_ptr<DiscordCoreInternal::VoiceSocketAgent> voiceSocketAgent{ nullptr };
		DiscordCoreInternal::BaseSocketAgent* baseSocketAgent{ nullptr };
		DiscordCoreInternal::VoiceConnectInitData voiceConnectInitData{};
		DiscordCoreInternal::VoiceConnectionData voiceConnectionData{};
		TSUnboundedMessageBlock<AudioFrameData> audioBuffer{};
		std::unique_ptr<CoRoutine<void>> theTask{ nullptr };
		std::unique_ptr<AudioEncoder> encoder{ nullptr };
		EventWaiter* doWeReconnect{ nullptr };
		const int32_t maxBufferSize{ 1276 };
		bool areWeConnectedBool{ false };
		AudioEncrypter audioEncrypter{};
		bool areWeInstantiated{ false };
		bool didWeJustConnect{ true };
		bool hasTerminateRun{ false };
		bool areWeStopping{ false };
		uint16_t sequenceIndex{ 0 };
		EventWaiter playSetEvent{};
		EventWaiter stopSetEvent{};
		bool areWePlaying{ false };
		AudioFrameData audioData{};
		bool areWePaused{ false };
		EventWaiter pauseEvent{};
		uint32_t timestamp{ 0 };
		bool doWeQuit{ false };

		void connect(DiscordCoreInternal::VoiceConnectInitData voiceConnectInitDataNew);

		TSUnboundedMessageBlock<AudioFrameData>& getAudioBuffer();

		void sendSingleAudioFrame(std::string& audioDataPacketNew);

		void sendSpeakingMessage(bool isSpeaking);

		bool areWeCurrentlyPlaying();

		bool areWeConnected();
		
		void clearAudioData();

		CoRoutine<void> run();

		void pauseToggle();

		void sendSilence();

		void disconnect();

		void reconnect();

		bool stop();

		bool skip();

		bool play();
	};
	/**@}*/

};
#endif