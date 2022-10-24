/*
	DiscordCoreAPI, A bot library for Discord, written in C++, and featuring explicit multithreading through the usage of custom, asynchronous C++ CoRoutines.

	Copyright 2021, 2022 Chris M. (RealTimeChris)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
	USA
*/
/// FoundationEntities.hpp - Header for all of the Discord/Support API data
/// structures. May 12, 2021 Chris M.
/// https://discordcoreapi.com
/// \file FoundationEntities.hpp

#pragma once

#ifndef FOUNDATION_ENTITIES
	#define FOUNDATION_ENTITIES

	#include <discordcoreapi/Utilities.hpp>
	#include <discordcoreapi/DataParsingFunctions.hpp>

namespace DiscordCoreInternal {

	struct DiscordCoreAPI_Dll VoiceConnectionData {
		std::string sessionId{};
		std::string endPoint{};
		std::string token{};
	};

	struct DiscordCoreAPI_Dll WebSocketResumeData {
		int32_t lastNumberReceived{};
		std::string sessionId{};
		std::string botToken{};

		operator DiscordCoreAPI::Jsonifier();
	};

	struct DiscordCoreAPI_Dll WebSocketIdentifyData {
		UpdatePresenceData presence{};
		int32_t largeThreshold{ 250 };
		int32_t numberOfShards{};
		int32_t currentShard{};
		std::string botToken{};
		int64_t intents{};

		operator DiscordCoreAPI::Jsonifier();
	};

	struct DiscordCoreAPI_Dll VoiceSocketProtocolPayloadData {
		std::string voiceEncryptionMode{};
		std::string externalIp{};
		uint64_t voicePort{};

		operator DiscordCoreAPI::Jsonifier();
	};

	struct DiscordCoreAPI_Dll VoiceIdentifyData {
		DiscordCoreAPI::VoiceConnectInitData connectInitData{};
		VoiceConnectionData connectionData{};

		operator DiscordCoreAPI::Jsonifier();
	};

	enum class SendSpeakingType : uint8_t {
		Microphone = 1 << 0,
		Soundshare = 1 << 1,
		Priority = 1 << 2,
		Priority_And_Voice = Microphone | Priority,
	};

	struct DiscordCoreAPI_Dll SendSpeakingData {
		SendSpeakingType type{};
		int32_t delay{};
		int32_t ssrc{};

		operator DiscordCoreAPI::Jsonifier();
	};

	enum class HttpsWorkloadClass : uint8_t { Get = 0, Put = 1, Post = 2, Patch = 3, Delete = 4 };

	enum class PayloadType : uint8_t { Application_Json = 1, Multipart_Form = 2 };

	enum class HttpsWorkloadType : uint8_t {
		Unset = 0,
		Get_Global_Application_Commands = 1,
		Post_Global_Application_Command = 2,
		Get_Global_Application_Command = 3,
		Patch_Global_Application_Command = 4,
		Delete_Global_Application_Command = 5,
		Bulk_Put_Global_Application_Commands = 6,
		Get_Guild_Application_Commands = 7,
		Post_Guild_Application_Command = 8,
		Get_Guild_Application_Command = 9,
		Patch_Guild_Application_Command = 10,
		Delete_Guild_Application_Command = 11,
		Bulk_Put_Guild_Application_Commands = 12,
		Get_Guild_Application_Commands_Permissions = 13,
		Get_Guild_Application_Command_Permissions = 14,
		Put_Guild_Application_Command_Permissions = 15,
		Batch_Put_Guild_Application_Command_Permissions = 16,
		Post_Interaction_Response = 17,
		Get_Interaction_Response = 18,
		Patch_Interaction_Response = 19,
		Delete_Interaction_Response = 20,
		Post_Followup_Message = 21,
		Get_Followup_Message = 22,
		Patch_Followup_Message = 23,
		Delete_Followup_Message = 24,
		Get_Guild_Audit_Logs = 25,
		Get_Channel = 26,
		Patch_Channel = 27,
		Delete_Channel = 28,
		Get_Messages = 29,
		Get_Message = 30,
		Post_Message = 31,
		Crosspost_Message = 32,
		Put_Reaction = 33,
		Delete_Own_Reaction = 34,
		Delete_User_Reaction = 35,
		Get_Reactions = 36,
		Delete_All_Reactions = 37,
		Delete_Reactions_By_Emoji = 38,
		Patch_Message = 39,
		Delete_Message = 40,
		Delete_Message_Old = 41,
		Bulk_Delete_Messages = 42,
		Put_Channel_Permission_Overwrites = 43,
		Get_Channel_Invites = 44,
		Post_Channel_Invite = 45,
		Delete_Channel_Permission_Overwrites = 46,
		Post_Follow_News_Channel = 47,
		Post_Trigger_Typing_Indicator = 48,
		Get_Pinned_Messages = 49,
		Put_Pin_Message = 50,
		Delete_Pin_Message = 51,
		Put_Recipient_To_Group_Dm = 52,
		Delete_Recipient_From_Group_Dm = 53,
		Post_Thread_With_Message = 54,
		Post_Thread_Without_Message = 55,
		Put_Self_In_Thread = 56,
		Put_Thread_Member = 57,
		Delete_Self_From_Thread = 58,
		Delete_Thread_Member = 59,
		Get_Thread_Member = 60,
		Get_Thread_Members = 61,
		Get_Active_Threads = 62,
		Get_Public_Archived_Threads = 63,
		Get_Private_Archived_Threads = 64,
		Get_Joined_Private_Archived_Threads = 65,
		Get_Emoji_List = 66,
		Get_Guild_Emoji = 67,
		Post_Guild_Emoji = 68,
		Patch_Guild_Emoji = 69,
		Delete_Guild_Emoji = 70,
		Post_Guild = 71,
		Get_Guild = 72,
		Get_Guild_Preview = 73,
		Patch_Guild = 74,
		Delete_Guild = 75,
		Get_Guild_Channels = 76,
		Post_Guild_Channel = 77,
		Patch_Guild_Channel_Positions = 78,
		Get_Guild_Active_Threads = 79,
		Get_Guild_Member = 80,
		Get_Guild_Members = 81,
		Get_Search_Guild_Members = 82,
		Put_Guild_Member = 83,
		Patch_Guild_Member = 84,
		Patch_Current_Guild_Member = 85,
		Put_Guild_Member_Role = 86,
		Delete_Guild_Member_Role = 87,
		Delete_Guild_Member = 88,
		Get_Guild_Bans = 89,
		Get_Guild_Ban = 90,
		Put_Guild_Ban = 91,
		Delete_Guild_Ban = 92,
		Get_Guild_Roles = 93,
		Post_Guild_Role = 94,
		Patch_Guild_Role_Positions = 95,
		Patch_Guild_Role = 96,
		Delete_Guild_Role = 97,
		Get_Guild_Prune_Count = 98,
		Post_Guild_Prune = 99,
		Get_Guild_Voice_Regions = 100,
		Get_Guild_Invites = 101,
		Get_Guild_Integrations = 102,
		Delete_Guild_Integration = 103,
		Get_Guild_Widget_Settings = 104,
		Patch_Guild_Widget = 105,
		Get_Guild_Widget = 106,
		Get_Vanity_Invite = 107,
		Get_Guild_Widget_Image = 108,
		Get_Guild_Welcome_Screen = 109,
		Patch_Guild_Welcome_Screen = 110,
		Patch_Current_User_Voice_State = 111,
		Patch_User_Voice_State = 112,
		Get_Guild_Scheduled_Events = 113,
		Post_Guild_Scheduled_Event = 114,
		Get_Guild_Scheduled_Event = 115,
		Patch_Guild_Scheduled_Event = 116,
		Delete_Guild_Scheduled_Event = 117,
		Get_Guild_Scheduled_Event_Users = 118,
		Get_Guild_Template = 119,
		Post_Guild_From_Guild_Template = 120,
		Get_Guild_Templates = 121,
		Post_Guild_Template = 122,
		Put_Guild_Template = 123,
		Patch_Guild_Template = 124,
		Delete_Guild_Template = 125,
		Get_Invite = 126,
		Delete_Invite = 127,
		Post_Stage_Instance = 128,
		Get_Stage_Instance = 129,
		Patch_Stage_Instance = 130,
		Delete_Stage_Instance = 131,
		Get_Sticker = 132,
		Get_Nitro_Sticker_Packs = 133,
		Get_Guild_Stickers = 134,
		Post_Guild_Sticker = 135,
		Patch_Guild_Sticker = 136,
		Delete_Guild_Sticker = 137,
		Get_Current_User = 138,
		Get_User = 139,
		Patch_Current_User = 140,
		Get_Current_User_Guilds = 141,
		Delete_Leave_Guild = 142,
		Post_Create_User_Dm = 143,
		Get_User_Connections = 144,
		Get_Voice_Regions = 145,
		Post_Webhook = 146,
		Get_Channel_Webhooks = 147,
		Get_Guild_Webhooks = 148,
		Get_Webhook = 149,
		Get_Webhook_With_Token = 150,
		Patch_Webhook = 151,
		Patch_Webhook_With_Token = 152,
		Delete_Webhook = 153,
		Delete_Webhook_With_Token = 154,
		Post_Execute_Webhook = 155,
		Get_Webhook_Message = 156,
		Patch_Webhook_Message = 157,
		Delete_Webhook_Message = 158,
		Get_Application_Info = 159,
		Get_Authorization_Info = 160,
		Get_Gateway_Bot = 161,
		Post_Thread_In_Forum_Channel = 162,
		Get_Auto_Moderation_Rules = 163,
		Get_Auto_Moderation_Rule = 164,
		Post_Auto_Moderation_Rule = 165,
		Patch_Auto_Moderation_Rule = 166,
		Delete_Auto_Moderation_Rule = 167,
		YouTubeGetSearchResults = 168,
		SoundCloudGetSearchResults = 169,
		LAST = 170
	};

	class DiscordCoreAPI_Dll HttpsWorkloadData {
	  public:
		friend class HttpsClient;

		static std::unordered_map<HttpsWorkloadType, std::unique_ptr<std::atomic_int64_t>> workloadIdsExternal;
		static std::unordered_map<HttpsWorkloadType, std::unique_ptr<std::atomic_int64_t>> workloadIdsInternal;

		PayloadType payloadType{ PayloadType::Application_Json };
		mutable std::unordered_map<std::string, std::string> headersToInsert{};
		mutable std::atomic_int64_t thisWorkerId{ 0 };
		HttpsWorkloadClass workloadClass{};
		mutable std::string baseUrl{};
		std::string relativePath{};
		std::string callStack{};
		std::string content{};

		HttpsWorkloadData& operator=(HttpsWorkloadData&& other) noexcept;

		HttpsWorkloadData(HttpsWorkloadData&& other) noexcept;

		HttpsWorkloadData& operator=(const HttpsWorkloadData& other) noexcept = delete;

		HttpsWorkloadData(const HttpsWorkloadData& other) noexcept = delete;

		HttpsWorkloadData(DiscordCoreInternal::HttpsWorkloadType type) noexcept;

	  protected:
		static int64_t incrementAndGetWorkloadId(HttpsWorkloadType workloadType) noexcept;

		HttpsWorkloadType workloadType{};
	};

	struct DiscordCoreAPI_Dll HelloData {
		HelloData(simdjson::ondemand::value);
		int32_t heartbeatInterval{};
	};

	struct DiscordCoreAPI_Dll WebSocketMessage {
		uint64_t op{ static_cast<uint64_t>(-1) };
		simdjson::ondemand::value d{};
		std::string t{};
		uint64_t s{};

		WebSocketMessage() noexcept = default;

		WebSocketMessage(simdjson::ondemand::value);

		template<typename RTy> RTy processJsonMessage() {
			return RTy{ this->d };
		}
	};

	struct DiscordCoreAPI_Dll InvalidSessionData {
		InvalidSessionData(simdjson::ondemand::value);
		bool d{};
	};
}

/// The main namespace for this library. \brief The main namespace for this
/// library.
namespace DiscordCoreAPI {

	/**
	 * \addtogroup foundation_entities
	 * @{
	*/

	class DiscordCoreAPI_Dll NewBase {};

	struct DiscordCoreAPI_Dll ConnectionPackage {
		int32_t currentReconnectTries{ 0 };
		bool areWeResuming{ false };
		uint32_t currentShard{ 0 };
	};

	/// Timeout durations for the timeout command. \brief Timeout durations for the timeout command.
	enum class TimeoutDurations : int16_t {
		None = 0,///< None - remove timeout.
		Minute = 1,///< 1 Minute timeout.
		Five_Minutes = 5,///< 5 Minute timeout.
		Ten_Minutes = 10,///< 10 Minute timeout.
		Hour = 60,///< 1 Hour timeout.
		Day = 1440,///< 1 Day timeout.
		Week = 10080///< 1 Week timeout.
	};

	/// Base class for all Discord entities. \brief Base class for all Discord entities.
	class DiscordCoreAPI_Dll DiscordEntity {
	  public:
		Snowflake id{};///< The identifier "snowflake" of the given entity.
		/// Converts the snowflake-id into a time and date stamp. \brief Converts the
		/// snowflake-id into a time and date stamp. \returns std::string A
		/// std::string containing the timeStamp.
		std::string getCreatedAtTimestamp(TimeFormat timeFormat);

		virtual ~DiscordEntity() noexcept = default;
	};

	/// Role tags data. \brief Role tags data.
	struct DiscordCoreAPI_Dll RoleTagsData {
		std::string premiumSubscriber{};///< Are they a premium subscriber?
		std::string integrationId{};///< What is the integration id?
		std::string botId{};///< What is the bot id?

		RoleTagsData() noexcept = default;

		RoleTagsData(simdjson::ondemand::value);

		virtual ~RoleTagsData() noexcept = default;
	};

	/// User flags. \brief User flags.
	enum class UserFlags : int32_t {
		Staff = 1 << 0,///< Discord Employee.
		Partner = 1 << 1,///< Partnered Server Owner.
		Hypesquad = 1 << 2,///< HypeSquad Events Member.
		Bug_Hunter_Level_1 = 1 << 3,///< Bug Hunter Level 1.
		Hypesquad_Online_House_1 = 1 << 6,///< House Bravery Member.
		Hypesquad_Online_House_2 = 1 << 7,///< House Brilliance Member.
		Hypesquad_Online_House_3 = 1 << 8,///< House Balance Member.
		Premium_Early_Suppoerter = 1 << 9,///< Early Nitro Supporter.
		Team_Pseudo_User = 1 << 10,///< User is a team.
		Bug_Hunter_Level_2 = 1 << 14,///< Bug Hunter Level 2.
		Verified_Bot = 1 << 16,///< Verified Bot.
		Verified_Developer = 1 << 17,///< Early Verified Bot Developer.
		Certified_Moderator = 1 << 18,///< Discord Certified Moderator.
		Bot_Http_Interactions = 1 << 19,///< Bot uses only HTTP interactions and is shown in the online member list.
		Bot = 1 << 20,///< Is it a bot?
		MFAEnabled = 1 << 21,///< Is MFA enabled?
		System = 1 << 22,///< Is it a system integration?
		Verified = 1 << 23///< Is it verified?
	};

	/// Premium types denote the level of premium a user has. \brief Premium types denote the level of premium a user has.
	enum class PremiumType : uint8_t {
		None = 0,///< None.
		Nitro_Classic = 1,///< Nitro classic.
		Nitro = 2///< Nitro.
	};

	/// Data structure representing a single User. \brief Data structure representing a single User.
	class DiscordCoreAPI_Dll UserData : public DiscordEntity {
	  public:
		friend class GuildData;

		StringWrapper discriminator{};///< The user's 4-digit discord-tag	identify.
		StringWrapper userName{};///< The user's userName, not unique across the platform identify.
		IconHash avatar{};///< The user's avatar hash.
		int32_t flags{};///< The public flags on a user' s account.

		UserData() noexcept = default;

		UserData& operator=(UserData&&) noexcept = default;

		UserData(UserData&&) noexcept = default;

		UserData& operator=(const UserData&) noexcept = default;

		UserData(const UserData&) noexcept = default;

		UserData(simdjson::ondemand::value jsonObjectData);

		std::string getAvatarUrl();

		virtual ~UserData() noexcept = default;
	};

	/// Attachment data. \brief Attachment data.
	class DiscordCoreAPI_Dll AttachmentData : public DiscordEntity {
	  public:
		bool ephemeral{ false };///< Whether it was an ephemeral response.
		std::string contentType{};///< Type of content for the attachment.
		std::string description{};///< A description of the attachment.
		std::string filename{};///< The file name of the attachment.
		std::string proxyUrl{};///< The proxy url for the attachment.
		int32_t height{ 0 };///< The height of the attachment.
		int32_t width{ 0 };///< The width of the attachment.
		int32_t size{ 0 };///< The size of the attachment.
		std::string url{};///< The url for the attachment.

		operator Jsonifier();

		AttachmentData() noexcept = default;

		AttachmentData(simdjson::ondemand::value);

		virtual ~AttachmentData() noexcept = default;
	};

	/// Sticker format types. \brief Sticker format types.
	enum class StickerFormatType : uint8_t {
		Png = 1,///< Png.
		Apng = 2,///< Apng.
		Lottie = 3///< Lottie
	};

	/// Embed footer data. \brief Embed footer data.
	struct DiscordCoreAPI_Dll EmbedFooterData {
		std::string proxyIconUrl{};///< Proxy icon url.
		std::string iconUrl{};///< Icon url.
		std::string text{};///< Footer text.

		EmbedFooterData() noexcept = default;

		EmbedFooterData(simdjson::ondemand::value jsonObjectData);

		virtual ~EmbedFooterData() noexcept = default;
	};

	/// Embed image data. \brief Embed image data.
	struct DiscordCoreAPI_Dll EmbedImageData {
		std::string proxyUrl{};///< Proxy url.
		int32_t height{ 0 };///< Image height.
		int32_t width{ 0 };///< Image width.
		std::string url{};///< Image url.

		EmbedImageData() noexcept = default;

		EmbedImageData(simdjson::ondemand::value jsonObjectData);

		virtual ~EmbedImageData() noexcept = default;
	};

	/// Embed thumbnail data. \brief Embed thumbnail data.
	struct DiscordCoreAPI_Dll EmbedThumbnailData {
		std::string proxyUrl{};///< Proxy url.
		int32_t height{ 0 };///< Image height.
		int32_t width{ 0 };///< Image width.
		std::string url{};///< Image url.

		EmbedThumbnailData() noexcept = default;

		EmbedThumbnailData(simdjson::ondemand::value jsonObjectData);

		virtual ~EmbedThumbnailData() noexcept = default;
	};

	/// Embed video data. \brief Embed video data.
	struct DiscordCoreAPI_Dll EmbedVideoData {
		std::string proxyUrl{};///< Proxy url.
		int32_t height{ 0 };///< Image height.
		int32_t width{ 0 };///< Image width.
		std::string url{};///< Image url.

		EmbedVideoData() noexcept = default;

		EmbedVideoData(simdjson::ondemand::value jsonObjectData);

		virtual ~EmbedVideoData() noexcept = default;
	};

	/// Embed provider data. \brief Embed provider data.
	struct DiscordCoreAPI_Dll EmbedProviderData {
		std::string name{};///< Name.
		std::string url{};///< Url.

		EmbedProviderData() noexcept = default;

		EmbedProviderData(simdjson::ondemand::value jsonObjectData);

		virtual ~EmbedProviderData() noexcept = default;
	};

	/// Embed author data. \brief Embed author data.
	struct DiscordCoreAPI_Dll EmbedAuthorData {
		std::string proxyIconUrl{};///< Proxy icon url.
		std::string iconUrl{};///< Icon url.
		std::string name{};///< Name.
		std::string url{};///< Url.

		EmbedAuthorData() noexcept = default;

		EmbedAuthorData(simdjson::ondemand::value jsonObjectData);

		virtual ~EmbedAuthorData() noexcept = default;
	};

	/// Embed field data. \brief Embed field data.
	struct DiscordCoreAPI_Dll EmbedFieldData {
		bool Inline{ false };///< Is the field inline with the rest of them?
		std::string value{};///< The text on the field.
		std::string name{};///< The title of the field.

		EmbedFieldData() noexcept = default;

		EmbedFieldData(simdjson::ondemand::value jsonObjectData);

		operator Jsonifier();

		virtual ~EmbedFieldData() noexcept = default;
	};

	/// Embed types. \brief Embed types.
	enum class EmbedType : uint8_t {
		Rich = 0,///< Rich.
		Image = 1,///< Image.
		Video = 2,///< Video.
		Gifv = 3,///< Gifv.
		Article = 4,///< Article.
		link = 5///< Link.
	};

	/// Embed data. \brief Embed data.
	class DiscordCoreAPI_Dll EmbedData {
	  public:
		std::vector<EmbedFieldData> fields{};///< Array of embed fields.
		EmbedThumbnailData thumbnail{};///< Embed thumbnail data.
		ColorValue hexColorValue{ 0 };///< Hex color value of the embed.
		EmbedProviderData provider{};///< Embed provider data.
		EmbedFooterData footer{};///< Embed footer data.
		EmbedAuthorData author{};///< Embed author data.
		EmbedImageData image{};///< Embed image data.
		EmbedVideoData video{};///< Embed video data.
		std::string description{};///< Description of the embed.
		std::string timeStamp{};///< Timestamp to be placed on the embed.
		std::string title{};///< Title of the embed.
		std::string type{};///< Type of the embed.
		std::string url{};///< Url for the embed.

		EmbedData() noexcept = default;

		operator Jsonifier();

		/// Sets the author's name and avatar for the embed. \brief Sets the author's name and avatar for the embed.
		/// \param authorName The author's name.
		/// \param authorAvatarUrl The url to their avatar.
		/// \returns EmbedData& A reference to this embed.
		EmbedData& setAuthor(const std::string& authorName, const std::string& authorAvatarUrl = "");

		/// Sets the footer's values for the embed. \brief Sets the footer's values for the embed.
		/// \param footerText The footer's text.
		/// \param footerIconUrlText Url to the footer's icon.
		/// \returns EmbedData& A reference to this embed.
		EmbedData& setFooter(const std::string& footerText, const std::string& footerIconUrlText = "");

		/// Sets the timeStamp on the embed. \brief Sets the timeStamp on the embed.
		/// \param timeStamp The timeStamp to be set.
		/// \returns EmbedData& A reference to this embed.
		EmbedData& setTimeStamp(const std::string& timeStamp);

		/// Adds a field to the embed. \brief Adds a field to the embed.
		/// \param name The title of the embed field.
		/// \param value The contents of the embed field.
		/// \param Inline Is it inline with the rest of the fields on the embed?
		/// \returns EmbedData& A reference to this embed.
		EmbedData& addField(const std::string& name, const std::string& value, bool Inline = true);

		/// Sets the description (the main contents) of the embed. \brief Sets the description (the main contents) of the embed.
		/// \param descriptionNew The contents of the description to set.
		/// \returns EmbedData& A reference to this embed.
		EmbedData& setDescription(const std::string& descriptionNew);

		/// Sets the color of the embed, by applying a hex-color value. \brief Sets the color of the embed, by applying a hex-color value.
		/// \param hexColorValueNew A string containing a hex-number value (Between 0x00 0xFFFFFF).
		/// \returns EmbedData& A reference to this embed.
		EmbedData& setColor(const std::string& hexColorValueNew);

		/// Sets the thumbnail of the embed. \brief Sets the thumbnail of the embed.
		/// \param thumbnailUrl The url to the thumbnail to be used.
		/// \returns EmbedData& A reference to this embed.
		EmbedData& setThumbnail(const std::string& thumbnailUrl);

		/// Sets the title of the embed. \brief Sets the title of the embed.
		/// \param titleNew A string containing the desired title.
		/// \returns EmbedData& A reference to this embed.
		EmbedData& setTitle(const std::string& titleNew);

		/// Sets the image of the embed. \brief Sets the image of the embed.
		/// \param imageUrl The url of the image to be set on the embed.
		/// \returns EmbedData& A reference to this embed.
		EmbedData& setImage(const std::string& imageUrl);

		EmbedData(simdjson::ondemand::value jsonObjectData);

		virtual ~EmbedData() noexcept = default;
	};

	/// Message reference data.\brief Message reference data.
	struct DiscordCoreAPI_Dll MessageReferenceData {
		bool failIfNotExists{ false };///< Fail if the Message doesn't exist?
		Snowflake messageId{};///< Id of the Message to reference.
		Snowflake channelId{};///< Id of the Channel that the referenced Message was sent in.
		Snowflake guildId{};///< Id of the Guild that the referenced Message was sent in.

		MessageReferenceData() noexcept = default;

		MessageReferenceData(simdjson::ondemand::value jsonObjectData);

		operator Jsonifier();

		virtual ~MessageReferenceData() noexcept = default;
	};

	enum class MediaType : uint8_t { png = 0, gif = 1, jpeg = 2, mpeg = 3, mp3 = 4 };

	/// Data representing a file to be sent via multipart-form data. \brief Data representing a file to be sent via multipart-form data.
	struct DiscordCoreAPI_Dll File {
		std::string fileName{};///< The name of the file.
		std::string data{};///< The data of the file.
	};

	/// The sorting order, for Guild Forum channels. \brief The sorting order, for Guild Forum channels.
	enum class SortOrderTypes {
		Latest_Activity = 0,///< Sort forum posts by activity.
		Creation_Date = 1///< Sort forum posts by creation time(from most recent to oldest).
	};

	/// Channel types. \brief Channel types.
	enum class ChannelType : uint8_t {
		Guild_Text = 0,///< Guild text.
		Dm = 1,///< Direct-Message.
		Guild_Voice = 2,/// Guild voice.
		Group_Dm = 3,///< Group direct-Message.
		Guild_Category = 4,///< Guild category.
		Guild_News = 5,///< Guild news.
		Guild_Store = 6,///< Guild store.
		Guild_News_Thread = 10,///< Guild news Thread.
		Guild_Public_Thread = 11,///< Guild public Thread.
		Guild_Private_Thread = 12,///< Guild private Thread.
		Guild_Stage_Voice = 13,///< Guild stage-voice.
		Guild_Directory = 14,///< The channel in a hub containing the listed servers.
		Guild_Forum = 15///< A channel that can only contain threads.
	};

	/// Meta data for a Thread type of Channel. \brief Meta data for a Thread type of Channel.
	struct DiscordCoreAPI_Dll ThreadMetadataData {
		TimeStamp<std::chrono::milliseconds> archiveTimestamp{};///< (Where applicable) the time at which this Thread was archived.
		int32_t autoArchiveDuration{ 0 };///< How int64_t before archiving this Thread.
		bool invitable{ false };///< The id of the individual who archived this Thread.
		bool archived{ false };///< Whether or not this Thread is currently archived.
		bool locked{ false };///< Whether or not this Thread is currently locked.

		ThreadMetadataData() noexcept = default;

		ThreadMetadataData(simdjson::ondemand::value);

		virtual ~ThreadMetadataData() noexcept = default;
	};

	/// Data for a single member of a Thread. \brief Data for a single member of a Thread.
	class DiscordCoreAPI_Dll ThreadMemberData : public DiscordEntity {
	  public:
		TimeStamp<std::chrono::milliseconds> joinTimestamp{};///< The time at which the member joined this Thread.
		Snowflake userId{};///< The User's id.
		int32_t flags{ 0 };///< Flags.

		ThreadMemberData() noexcept = default;

		ThreadMemberData(simdjson::ondemand::value);

		virtual ~ThreadMemberData() noexcept = default;
	};

	class DiscordCoreAPI_Dll ThreadMemberDataVector {
	  public:
		ThreadMemberDataVector() noexcept = default;

		operator std::vector<ThreadMemberData>();

		ThreadMemberDataVector(simdjson::ondemand::value);

		virtual ~ThreadMemberDataVector() noexcept = default;

	  protected:
		std::vector<ThreadMemberData> threadMemberDatas{};
	};

	/// Thread types. \brief Thread types.
	enum class ThreadType : uint8_t {
		Guild_News_Thread = 10,///< Guild news Thread.
		Guild_Public_Thread = 11,///< Guild public Thread.
		Guild_Private_Thread = 12///< Guild private Thread.
	};

	/// Voice state data. \brief Voice state data.
	struct DiscordCoreAPI_Dll VoiceStateData {
		TimeStamp<std::chrono::milliseconds> requestToSpeakTimestamp{};///< The time at which the User requested to speak.
		bool selfStream{ false };///< Whether this User is streaming using "Go Live".
		bool selfVideo{ false };///< Whether this User's camera is enabled.
		bool selfDeaf{ false };///< Whether this User is locally deafened.
		bool selfMute{ false };///< Whether this User is locally muted.
		bool suppress{ false };///< Whether this User is muted by the current User.
		Snowflake channelId{};///< The Channel id this User is connected to.
		Snowflake guildId{};///< The Guild id this voice state is for.
		std::string sessionId{};///< The session id for this voice state.
		bool deaf{ false };///< Whether this User is deafened by the server.
		bool mute{ false };///< Whether this User is muted by the server.
		Snowflake userId{};///< The User id this voice state is for.

		VoiceStateData() noexcept = default;

		VoiceStateData(simdjson::ondemand::value jsonObjectData);

		virtual ~VoiceStateData() noexcept = default;
	};

	/// Automatic Thread archiving durations. \brief Automatic Thread archiving durations.
	enum class ThreadAutoArchiveDuration : int16_t {
		Shortest = 60,///< Shortest.
		Short = 1440,///< Short.
		Long = 4320,///< Long.
		Longest = 10080///< Longest.
	};

	/// Party data. \brief Party data.
	class DiscordCoreAPI_Dll PartyData : public DiscordEntity {
	  public:
		std::vector<int32_t> size{ 0, 0 };///< The size of the party.

		PartyData() noexcept = default;

		PartyData(simdjson::ondemand::value jsonObjectData);

		virtual ~PartyData() noexcept = default;
	};

	enum class RoleFlags : uint8_t { Mentionable = 1 << 0, Managed = 1 << 1, Hoist = 1 << 2 };

	/// Data structure representing a single Role. \brief Data structure representing a single Role.
	class DiscordCoreAPI_Dll RoleData : public DiscordEntity {
	  public:
		friend class GuildData;

		StringWrapper unicodeEmoji{};///< Emoji representing the Role.
		Permissions permissions{};///< The Role's base Guild Permissions.
		ColorValue color{ 0 };///< The Role's color.
		StringWrapper name{};///< The Role's name.
		int16_t position{ 0 };///< Its position amongst the rest of the Guild's roles.
		Snowflake guildId{};///< The id of the Guild that this Role is from.
		int8_t flags{ 0 };///< Role flags.

		RoleData() noexcept = default;

		RoleData& operator=(RoleData&&) noexcept = default;

		RoleData(RoleData&&) noexcept = default;

		RoleData& operator=(const RoleData&) noexcept = default;

		RoleData(const RoleData&) noexcept = default;

		RoleData(simdjson::ondemand::value jsonObjectData);

		virtual ~RoleData() noexcept = default;
	};

	/// Data structure representing a single emoji. \brief Data structure representing a single emoji.
	class DiscordCoreAPI_Dll EmojiData : public DiscordEntity {
	  public:
		std::wstring unicodeName{ L"" };///< What is its unicode name?
		bool requireColons{ false };///< Require colons to render it?
		std::vector<RoleData> roles{};///< Roles that are allowed to use this emoji.
		bool available{ true };///< Is it available to be used?
		bool animated{ false };///< Is it animated?
		bool managed{ false };///< Is it managed?
		StringWrapper name{};///< What is its name?
		UserData user{};///< User that created this emoji.

		EmojiData() noexcept = default;

		EmojiData(simdjson::ondemand::value jsonObjectData);

		virtual ~EmojiData() noexcept = default;
	};

	/// Assets data. \brief Party data.
	struct DiscordCoreAPI_Dll AssetsData {
		StringWrapper largeImage{};///< Keyname of an asset to display.
		StringWrapper smallImage{};///< Keyname of an asset to display.
		StringWrapper largeText{};///< Hover text for the large image.
		StringWrapper smallText{};///< Hover text for the small image.

		AssetsData() noexcept = default;

		virtual ~AssetsData() noexcept = default;
	};

	/// Secrets data. \brief Secrets data.
	struct DiscordCoreAPI_Dll SecretsData {
		StringWrapper spectate{};///< Unique hash for the given match context.
		StringWrapper match{};///< Unique hash for Spectate button.
		StringWrapper join{};///< Unique hash for chat invitesand Ask to Join.

		SecretsData() noexcept = default;

		virtual ~SecretsData() noexcept = default;
	};

	/// Timestamp data. \brief Timestamp data.
	struct DiscordCoreAPI_Dll TimestampData {
		int64_t start{ 0 };///< Unix timeStamp - Send this to have an "elapsed" timer.
		int64_t end{ 0 };///< Unix timeStamp - send this to have a "remaining" timer.

		TimestampData() noexcept = default;

		virtual ~TimestampData() noexcept = default;
	};

	/// Button data. \brief Button data.
	struct DiscordCoreAPI_Dll ButtonData {
		StringWrapper label{};///< Visible label of the button.
		StringWrapper url{};///< Url to display on the button.
	};

	/// Activity types. \brief Activity types.
	enum class ActivityType : uint8_t {
		Game = 0,///< Game.
		Streaming = 1,///< Streaming.
		Listening = 2,///< Listening.
		Watching = 3,///< Watching.
		Custom = 4,///< Custom.
		Competing = 5///< Competing.
	};

	/// Activity data. \brief Activity data.
	struct DiscordCoreAPI_Dll ActivityData {
		TimestampData timestamps{};///< Timestamp data.
		Snowflake applicationId{};///< Application id for the current application.
		StringWrapper details{};///< Details about the activity.
		bool instance{ false };///< Whether this activity is an instanced context, like a match.
		StringWrapper state{};///< The player's current party status.
		SecretsData secrets{};///< Secrets data.
		int32_t createdAt{ 0 };///< Timestamp of when the activity began.
		ButtonData buttons{};///< Button Data.
		StringWrapper name{};///< Name of the activity.
		ActivityType type{};///< Activity data.
		AssetsData assets{};///< Assets data.
		StringWrapper url{};///< Url associated with the activity.
		EmojiData emoji{};///< Emoji associated with the activity.
		PartyData party{};///< Party data.
		int32_t flags{ 0 };///< Flags.

		ActivityData() noexcept = default;

		virtual ~ActivityData() noexcept = default;
	};

	enum class PresenceUpdateFlags : uint8_t {
		Desktop_Online = 0b00000001,
		Desktop_Idle = 0b00000010,
		Desktop_Dnd = 0b000000011,
		Mobile_Online = 0b00000010,
		Mobile_Idle = 0b00000100,
		Mobile_Dnd = 0b00000110,
		Web_Online = 0b00000100,
		Web_Idle = 0b00001000,
		Web_Dnd = 0b00001100,
		Status_Online = 0b00001000,
		Status_Idle = 0b00010000,
		Status_Dnd = 0b00011000
	};

	void parseObject(simdjson::ondemand::value jsonObjectData, PresenceUpdateFlags& data);

	/// Presence update data. \brief Presence update data.
	struct DiscordCoreAPI_Dll PresenceUpdateData {
		Snowflake guildId{};///< Guild id for the current presence.
		Snowflake userId{};///< User id for the current presence.
		uint8_t theStatus{};///< Current client status.

		PresenceUpdateData() noexcept = default;

		PresenceUpdateData(simdjson::ondemand::value jsonObjectData);

		virtual ~PresenceUpdateData() noexcept = default;
	};

	enum class GuildMemberFlags : uint8_t { Pending = 1 << 0, Deaf = 1 << 1, Mute = 1 << 2 };

	/// Data structure representing a single GuildMember. \brief Data structure representing a single GuildMember.
	/// Data structure representing a single Guild. \brief Data structure representing a single Guild.
	class DiscordCoreAPI_Dll GuildMemberData : public DiscordEntity {
	  public:
		friend class GuildData;
		TimeStamp<std::chrono::milliseconds> joinedAt{};///< When they joined the Guild.
		Snowflake voiceChannelId{};///< Currently held voice channel, if applicable.
		Permissions permissions{};///< Their base-level Permissions in the Guild.
		std::vector<Snowflake> roles{};///< The Guild roles that they have.
		StringWrapper nick{};///< Their nick/display name.
		Snowflake guildId{};///< The current Guild's id.
		IconHash avatar{};///< This GuildMember's Guild Avatar.
		int8_t flags{ 0 };///< GuildMember flags.

		GuildMemberData() noexcept = default;

		GuildMemberData& operator=(GuildMemberData&&) noexcept;

		GuildMemberData(GuildMemberData&&) noexcept;

		GuildMemberData& operator=(const GuildMemberData&) noexcept = default;

		GuildMemberData(const GuildMemberData&) noexcept = default;

		GuildMemberData& operator=(simdjson::ondemand::value);

		GuildMemberData(simdjson::ondemand::value);

		std::string getAvatarUrl();

		UserData getUserData();

		virtual ~GuildMemberData() noexcept = default;
	};

	/// PermissionTypes overwrites types. \brief PermissionTypes overwrites types.
	enum class PermissionOverwritesType : uint8_t {
		Role = 0,///< Role.
		User = 1///< User.
	};

	/// A PermissionTypes overwrite, for a given Channel. \brief A PermissionTypes overwrite, for a given Channel.
	class DiscordCoreAPI_Dll OverWriteData : public DiscordEntity {
	  public:
		PermissionOverwritesType type{};///< Role or User type.
		uint64_t allow{};///< Collection of Permissions to allow.
		uint64_t deny{};///< Collection of Permissions to deny.

		OverWriteData() noexcept = default;

		OverWriteData(simdjson::ondemand::value jsonObjectData);

		virtual ~OverWriteData() noexcept = default;
	};

	enum class ChannelFlags : uint8_t { NSFW = 1 << 0 };

	struct DefaultReactionData {
		Snowflake emojiId{};///< The id of a guild's custom emoji.
		std::string emojiName{};///< The unicode character of the emoji.

		DefaultReactionData() noexcept = default;

		DefaultReactionData(simdjson::ondemand::value jsonObjectData);
	};

	struct ForumTagData {
		Snowflake emojiId{};///< The id of a guild's custom emoji.
		std::string emojiName{};///< The unicode character of the emoji.
		bool moderated{};///< Whether this tag can only be added to or removed from threads by a member with the MANAGE_THREADS permission.
		Snowflake id{};///< Id of the tag.
		std::string name{};///< The name of the tag(0 - 20 characters).

		ForumTagData() noexcept = default;

		ForumTagData(simdjson::ondemand::value jsonObjectData);

		virtual ~ForumTagData() noexcept = default;
	};

	/// Data structure representing a single Channel. \brief Data structure representing a single Channel.
	class DiscordCoreAPI_Dll ChannelData : public DiscordEntity {
	  public:
		friend class GuildData;

		std::vector<OverWriteData> permissionOverwrites{};///< Permission overwrites.
		ChannelType type{ ChannelType::Dm };///< The type of the Channel.
		SortOrderTypes defaultSortOrder{};///< Default sorting order for a forum thread.
		int32_t memberCount{ 0 };///< Count of members active in the Channel.
		StringWrapper topic{};///< Channel topic.
		uint16_t position{ 0 };///< The position of the Channel, in the Guild's Channel list.
		Snowflake parentId{};///< Id of the Channel's parent Channel/category.
		StringWrapper name{};///< Name of the Channel.
		Snowflake ownerId{};///< Id of the Channel's owner.
		Snowflake guildId{};///< Id of the Channel's Guild, if applicable.
		uint8_t flags{};///< Flags combined as a bitmask.

		ChannelData() noexcept = default;

		ChannelData& operator=(ChannelData&&) noexcept = default;

		ChannelData(ChannelData&&) noexcept = default;

		ChannelData& operator=(const ChannelData&) noexcept = default;

		ChannelData(const ChannelData&) noexcept = default;

		ChannelData(simdjson::ondemand::value);

		virtual ~ChannelData() noexcept = default;
	};

	/// Data representing an active Thread. \brief Data representing an active Thread.
	struct DiscordCoreAPI_Dll ActiveThreadsData {
		std::vector<ThreadMemberData> members{};
		std::vector<ChannelData> threads{};
		bool hasMore{ false };

		ActiveThreadsData() noexcept = default;

		ActiveThreadsData(simdjson::ondemand::value jsonObjectData);

		virtual ~ActiveThreadsData() noexcept = default;
	};

	/// Data representing an archived Thread. \brief Data representing an archived Thread.
	struct DiscordCoreAPI_Dll ArchivedThreadsData {
		std::vector<ThreadMemberData> members{};
		std::vector<ChannelData> threads{};
		bool hasMore{ false };

		ArchivedThreadsData() noexcept = default;

		ArchivedThreadsData(simdjson::ondemand::value jsonObjectData);

		virtual ~ArchivedThreadsData() noexcept = default;
	};

	/// Application command-option types. \brief Application command-option types.
	enum class ApplicationCommandOptionType : uint8_t {
		Sub_Command = 1,///< Sub-command.
		Sub_Command_Group = 2,///< Sub-command group.
		String = 3,///< std::string.
		Integer = 4,///< Integer.
		Boolean = 5,///< Boolean.
		User = 6,///< User.
		Channel = 7,///< Channel.
		Role = 8,///< Role.
		Mentionable = 9,///< Mentionable.
		Number = 10,///< Number.
		Attachment = 11///< Attachment.
	};

	/// Application command permission-types. \brief Application command permission-types.
	enum class ApplicationCommandPermissionType : uint8_t {
		Role = 1,///< Role.
		User = 2,///< User.
		Channel = 3///< Channel.
	};

	/// Event types for auto-moderation. \brief Event types for auto-moderation.
	enum class EventType : uint8_t {
		Message_Send = 1,///< When a member sends or edits a message in the guild.
	};

	/// Trigger types for auto-moderation. \brief Trigger types for auto-moderation.
	enum class TriggerType : uint8_t {
		Keyword = 1,///< Check if content contains words from a user defined list of keywords.
		Spam = 3,///< Check if content represents generic spam.
		Keyword_Preset = 4,///< Check if content contains words from internal pre-defined wordsets.
		Mention_Spam = 5///< Check if content contains more unique mentions than allowed.
	};

	/// Keyword preset types for auto-moderation. \brief Keyword preset types for auto-moderation.
	enum class KeywordPresetType : uint8_t {
		Profanity = 1,///< Words that may be considered forms of swearing or cursing.
		Sexual_Content = 2,///< Words that refer to sexually explicit behavior or activity
		Slurs = 3///< Personal insults or words that may be considered hate speech.
	};

	/// Action types for auto-moderation. \brief Action types for auto-moderation.
	enum class ActionType : uint8_t {
		Block_Message = 1,///< Blocks the content of a message according to the rule.
		Send_Alert_Message = 2,///< Logs user content to a specified channel.
		Timeout = 3///< Timeout user for a specified duration.
	};

	/// Action metadata for auto-moderation-rules. \brief Action metadata for auto-moderation-rules.
	struct DiscordCoreAPI_Dll ActionMetaData {
		int64_t durationSeconds{};///< Timeout duration in seconds.
		Snowflake channelId{};///< Channel to which user content should be logged.

		ActionMetaData() noexcept = default;

		ActionMetaData(simdjson::ondemand::value jsonObjectData);

		virtual ~ActionMetaData() noexcept = default;
	};

	/// Trigger metadata for auto-moderation-rules. \brief Trigger metadata for auto-moderation-rules.
	struct DiscordCoreAPI_Dll TriggerMetaData {
		std::vector<KeywordPresetType> presets{};///< The internally pre-defined wordsets which will be searched for in content.
		std::vector<std::string> keywordFilter{};///< Substrings which will be searched for in content.keyword_filter	array of strings.
		std::vector<std::string> allowList{};///< Substrings which will be exempt from triggering the preset trigger type.
		int32_t mentionTotalLimit{};///< Total number of unique role and user mentions allowed per message (Maximum of 50).

		TriggerMetaData() noexcept = default;

		TriggerMetaData(simdjson::ondemand::value jsonObjectData);

		virtual ~TriggerMetaData() noexcept = default;
	};

	/// For representing a single auto-moderation-rule-action. \brief For representing a single auto-moderation-rule-action.
	struct DiscordCoreAPI_Dll ActionData {
		ActionType type{};///< The type of action.
		ActionMetaData metadata{};///< Additional metadata needed during execution for this specific action type.

		ActionData() noexcept = default;

		ActionData(simdjson::ondemand::value jsonObjectData);

		virtual ~ActionData() noexcept = default;
	};

	/// Represents an auto-moderation-rule. \brief Represents an auto-moderation-rule.
	class DiscordCoreAPI_Dll AutoModerationRuleData : public DiscordEntity {
	  public:
		std::vector<Snowflake> exemptChannels{};///< The channel ids that should not be affected by the rule(Maximum of 50).
		TriggerMetaData triggerMetaData{};///< The rule trigger metadata actions array of action objects the.
		std::vector<Snowflake> exemptRoles{};///< The role ids that should not be affected by the rule(Maximum of 20).
		std::vector<ActionData> actions{};///< Actions which will execute when the rule is triggered.
		TriggerType triggerType{};///< The rule trigger type.
		EventType eventType{};///< The rule event type.
		Snowflake creatorId{};///< The user which first created this rule.
		Snowflake guildId{};///< The guild which this rule belongs to.
		bool enabled{};///< Whether the rule is enabled.
		std::string name{};///< The rule name.

		AutoModerationRuleData() noexcept = default;

		AutoModerationRuleData(simdjson::ondemand::value jsonObjectData);

		virtual ~AutoModerationRuleData() noexcept = default;
	};

	/// Permissions data for an ApplicationCommand. \brief Permissions data for an ApplicationCommand.
	class DiscordCoreAPI_Dll ApplicationCommandPermissionData : public DiscordEntity {
	  public:
		ApplicationCommandPermissionType type{ ApplicationCommandPermissionType::Role };///< The type of PermissionTypes.
		bool permission{ false };///< Whether the PermissionTypes is active or not.

		ApplicationCommandPermissionData() noexcept = default;

		ApplicationCommandPermissionData(simdjson::ondemand::value jsonObjectData);

		virtual ~ApplicationCommandPermissionData() noexcept = default;
	};

	/// Represents the Permissions for accessing an ApplicationCommand from within a Guild. \brief Represents the Permissions for accessing an ApplicationCommand from within a Guild.
	class DiscordCoreAPI_Dll GuildApplicationCommandPermissionsData : public DiscordEntity {
	  public:
		std::vector<ApplicationCommandPermissionData> permissions{};///< The Permissions.
		Snowflake applicationId{};///< The application's id.
		Snowflake guildId{};///< The Guild's id.

		GuildApplicationCommandPermissionsData() noexcept = default;

		GuildApplicationCommandPermissionsData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildApplicationCommandPermissionsData() noexcept = default;
	};

	class DiscordCoreAPI_Dll GuildApplicationCommandPermissionsDataVector {
	  public:
		GuildApplicationCommandPermissionsDataVector() noexcept = default;

		operator std::vector<GuildApplicationCommandPermissionsData>();

		GuildApplicationCommandPermissionsDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildApplicationCommandPermissionsDataVector() noexcept = default;

	  protected:
		std::vector<GuildApplicationCommandPermissionsData> guildApplicationCommandPermissionsDatas{};
	};

	class DiscordCoreAPI_Dll EmojiDataVector {
	  public:
		EmojiDataVector() noexcept = default;

		EmojiDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~EmojiDataVector() noexcept = default;

	  protected:
		std::vector<EmojiData> theEmojiDatas{};
	};

	/// For updating/modifying a given Channel's properties. \brief For updating/modifying a given Channel's properties.
	struct DiscordCoreAPI_Dll UpdateChannelData {
		std::vector<OverWriteData> permissionOverwrites{};
		int32_t defaultAutoArchiveDuration{ 10080 };
		int32_t videoQualityMode{ 1 };
		int32_t rateLimitPerUser{ 0 };
		int32_t bitrate{ 48000 };
		int32_t userLimit{ 0 };
		int32_t position{ 0 };
		ChannelType type{};
		bool nsfw{ false };
		std::string parentId{};
		std::string rtcRgion{};
		std::string topic{};
		std::string name{};
	};

	/// Data structure representing a single reaction. \brief/// Data structure representing a single reaction.
	class DiscordCoreAPI_Dll ReactionData : public DiscordEntity {
	  public:
		GuildMemberData member{};///< The GuildMember who placed the reaction.
		Snowflake channelId{};///< The id of the Channel where it was placed.
		Snowflake messageId{};///< The id of the Message upon which it was placed.
		Snowflake guildId{};///< The id of the Guild where it was placed.
		Snowflake userId{};///< The id of the User who placed the reaction.
		EmojiData emoji{};///< The emoji that was placed as a reaction.
		int32_t count{ 0 };///< The number of times this particular emoji was placed as a reaction to the given Message.
		bool me{ false };///< Whether or not I (The bot) placed it.

		ReactionData() noexcept = default;

		ReactionData(simdjson::ondemand::value jsonObjectData);

		virtual ~ReactionData() noexcept = default;
	};

	/// Structure representing Voice Region Data. \brief Structure representing Voice Region Data.
	struct DiscordCoreAPI_Dll VoiceRegionData {
		bool deprecated{ false };///< Whether this is a deprecated voice region(avoid switching to these).
		bool optimal{ false };///< True for a single server that is closest to the current User's client.
		bool custom{ false };///< Whether this is a custom voice region(used for events / etc).
		Snowflake id{};///< Unique ID for the region.
		std::string name{};///< Name of the region.

		VoiceRegionData() noexcept = default;

		VoiceRegionData(simdjson::ondemand::value jsonObjectData);

		virtual ~VoiceRegionData() noexcept = default;
	};

	class DiscordCoreAPI_Dll VoiceRegionDataVector {
	  public:
		VoiceRegionDataVector() noexcept = default;

		operator std::vector<VoiceRegionData>();

		VoiceRegionDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~VoiceRegionDataVector() noexcept = default;

	  protected:
		std::vector<VoiceRegionData> theVoiceRegionDatas{};
	};

	/// Message activity types. \brief Message activity types.
	enum class MessageActivityType : uint8_t {
		Join = 1,///< Join.
		Spectate = 2,///< Spectate.
		Listen = 3,///< Listen.
		Join_Request = 5///< Join-request.
	};

	/// Message activity data. \brief Message activity data.
	struct DiscordCoreAPI_Dll MessageActivityData {
		MessageActivityType type{ MessageActivityType::Join };///< Message activity type.
		std::string partyId{};///< Party id.

		MessageActivityData() noexcept = default;

		MessageActivityData(simdjson::ondemand::value jsonObjectData);

		virtual ~MessageActivityData() noexcept = default;
	};

	/// Ban data. \brief Ban data.
	struct DiscordCoreAPI_Dll BanData {
		bool failedDueToPerms{ false };///< Failed due to perms?
		std::string reason{};///< Reason for the ban.
		UserData user{};///< User that was banned.

		BanData() noexcept = default;

		BanData(simdjson::ondemand::value jsonObjectData);

		virtual ~BanData() noexcept = default;
	};

	class DiscordCoreAPI_Dll BanDataVector {
	  public:
		BanDataVector() noexcept = default;

		operator std::vector<BanData>();

		BanDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~BanDataVector() noexcept = default;

	  protected:
		std::vector<BanData> theBanDatas{};
	};

	/// Team members object data. \brief Team members object data.
	struct DiscordCoreAPI_Dll TeamMembersObjectData {
		std::vector<Permissions> permissions{};///< Permissions for the team.
		int32_t membershipState{ 0 };///< Current state.
		Snowflake teamId{};///< Id of the current team.
		UserData user{};///< User data of the current User.

		TeamMembersObjectData() noexcept = default;

		TeamMembersObjectData(simdjson::ondemand::value jsonObjectData);

		virtual ~TeamMembersObjectData() noexcept = default;
	};

	/// For updating the current voice state. \brief For updating the current voice state.
	struct DiscordCoreAPI_Dll UpdateVoiceStateData {
		bool selfMute{ false };///< Whether or not we self-mute ourselves.
		bool selfDeaf{ false };///< Whether or not we self-deafen ourselves.
		Snowflake channelId{};///< Id of the desired voice Channel. Leave blank to disconnect.
		Snowflake guildId{};///< The id of the Guild fo which we would like to establish a voice connection.

		operator Jsonifier();
	};

	/// Team object data. \brief Team object data.
	class DiscordCoreAPI_Dll TeamObjectData : public DiscordEntity {
	  public:
		std::vector<TeamMembersObjectData> members{};///< Array of team members object data.
		Snowflake ownerUserId{};///< User id of the team owner.
		std::string icon{};///< Icon for the team.

		TeamObjectData() noexcept = default;

		TeamObjectData(simdjson::ondemand::value jsonObjectData);

		virtual ~TeamObjectData() noexcept = default;
	};

	/// Application flags, for the ApplicationData structure.
	enum class ApplicationFlags : int32_t {
		Gateway_Presence = 1 << 12,///< Intent required for bots in 100 or more servers to receive presence_update events.
		Gateway_Presence_Limited = 1 << 13,///< Intent required for bots in under 100 servers to receive presence_update events, found in Bot Settings.
		Gateway_Guild_Members = 1 << 14,///< Intent required for bots in 100 or more servers to receive member-related events like guild_member_add.
		Gateway_Guild_Members_Limited = 1 << 15,///< Intent required for bots in under 100 servers to receive member-related events like guild_member_add, found in Bot Settings.
		Verificatino_Pending_Guild_Limit = 1 << 16,///< Indicates unusual growth of an app that prevents verification
		Embedded = 1 << 17,///< Indicates if an app is embedded within the Discord client (currently unavailable publicly)
		Gateway_Message_Content = 1 << 18,///< Intent required for bots in 100 or more servers to receive message content
		Gateway_Message_Content_Limited = 1 << 19///< Intent required for bots in under 100 servers to receive message content, found in Bot Settings};
	};

	/// Install params data, for application data. \brief Install params data, for application data.
	struct DiscordCoreAPI_Dll InstallParamsData {
		Permissions permissions{};///< The permissions to request for the bot role.
		std::vector<std::string> scopes{};///< The scopes to add the application to the server with.

		InstallParamsData() noexcept = default;

		InstallParamsData(simdjson::ondemand::value jsonObjectData);

		virtual ~InstallParamsData() noexcept = default;
	};

	/// Application data. \brief Application data.
	class DiscordCoreAPI_Dll ApplicationData : public DiscordEntity {
	  public:
		bool botRequireCodeGrant{ false };///< Does the bot require a code grant?
		std::vector<std::string> rpcOrigins{};///< Array of RPC origin strings.
		ApplicationFlags flags{ 0 };///< Application flags.
		std::string termsOfServiceUrl{};///< Terms of service Url.
		InstallParamsData params{};///< Settings for the application's default in-app authorization link, if enabled std::string customInstallUrl{};
		std::string privacyPolicyUrl{};///< Privacy policy Url.
		bool botPublic{ false };///< Is the bot public?
		TeamObjectData team{};///< Team object data.
		std::vector<std::string> tags{};///< Up to 5 tags describing the content and functionality of the application install_params.
		std::string primarySkuId{};///< Primary SKU Id.
		std::string description{};///< Description of the application.
		std::string coverImage{};///< The cover image.
		Snowflake guildId{};///< Guild id.
		std::string verifyKey{};///< The verification key.
		std::string summary{};///< Summary of the application.
		UserData owner{};///< Application's owner.
		std::string slug{};///< Sluhg.
		std::string name{};///< Application's name.
		std::string icon{};///< Application's icon.

		ApplicationData() noexcept = default;

		ApplicationData(simdjson::ondemand::value jsonObjectData);

		virtual ~ApplicationData() noexcept = default;
	};

	/// Authorization info structure. \brief Authorization info structure.
	struct DiscordCoreAPI_Dll AuthorizationInfoData {
		ApplicationData application{};///< Partial application object the current application.
		std::vector<std::string> scopes{};///< Array of strings - the scopes the User has authorized the application for.
		std::string expires{};///< When the access token expires.
		UserData user{};/// The User who has authorized, if the User has authorized with the identify scope.

		AuthorizationInfoData() noexcept = default;

		AuthorizationInfoData(simdjson::ondemand::value jsonObjectData);

		virtual ~AuthorizationInfoData() noexcept = default;
	};

	/// Account data. \brief Account data.
	class DiscordCoreAPI_Dll AccountData : public DiscordEntity {
	  public:
		std::string name{};///< Name of the account.

		AccountData() noexcept = default;

		AccountData(simdjson::ondemand::value jsonObjectData);

		virtual ~AccountData() noexcept = default;
	};

	/// Guild Widget Data. \brief Guild Widget Data.
	struct DiscordCoreAPI_Dll GuildWidgetData {
		Snowflake channelId{};///< The widget Channel id.
		bool enabled{ false };///< Whether the widget is enabled.

		GuildWidgetData() noexcept = default;

		GuildWidgetData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildWidgetData() noexcept = default;
	};

	/// Get Guild Widget Data. \brief Get Guild Widget Data.
	struct DiscordCoreAPI_Dll GetGuildWidgetObjectData : public DiscordEntity {
		std::vector<ChannelData> channels{};///< Voice and stage channels which are accessible by everyone.
		std::vector<UserData> members{};///< Special widget user objects that includes users presence (Limit 100).
		int32_t presence_count{ 0 };///< Number of online members in this guild.
		std::string instantInvite{};///< Instant invite for the guilds specified widget invite channel.
		std::string name{};///< Guild name (2-100 characters).
	};

	/// Widget style options. \brief Widget style options.
	enum class WidgetStyleOptions : uint8_t {
		Shield = 0,///< Shield
		Banner1 = 1,///< Banner1
		Banner2 = 2,///< Banner2
		Banner3 = 3,///< Banner3
		Banner4 = 4///< Banner4
	};

	/// Guild widget image data. \brief Guild widget image data.
	struct DiscordCoreAPI_Dll GuildWidgetImageData {
		std::string url{};

		GuildWidgetImageData() noexcept = default;

		GuildWidgetImageData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildWidgetImageData() noexcept = default;
	};

	/// Integration data. \brief Integration data.
	class DiscordCoreAPI_Dll IntegrationData : public DiscordEntity {
	  public:
		TimeStamp<std::chrono::milliseconds> syncedAt{};///< Time it was last synced at.
		ApplicationData application{};///< Application data.
		int32_t expireGracePeriod{ 0 };///< How int64_t before the integration expires.
		bool enableEmoticons{ true };///< Emoticons enabled?
		int32_t subscriberCount{ 0 };///< Number of current subscribers.
		int32_t expireBehavior{ 0 };///< What to do upon expiry.
		bool enabled{ false };///< Enabled?
		bool syncing{ false };///< Is it syncing?
		AccountData account{};///< Account data.
		bool revoked{ false };///< Has it been revoked?
		Snowflake roleId{};///< Role Id.
		UserData user{};///< User data for the integration.
		std::string name{};///< Name of the integration.
		std::string type{};///< Type of integration.

		IntegrationData() noexcept = default;

		IntegrationData(simdjson::ondemand::value jsonObjectData);

		virtual ~IntegrationData() noexcept = default;
	};

	class DiscordCoreAPI_Dll IntegrationDataVector {
	  public:
		IntegrationDataVector() noexcept = default;

		operator std::vector<IntegrationData>();

		IntegrationDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~IntegrationDataVector() noexcept = default;

	  protected:
		std::vector<IntegrationData> integeregrationDatas{};
	};

	/// Audit log events. \brief Audit log events.
	enum class AuditLogEvent : uint8_t {
		Guild_Update = 1,///< Guild update.
		Channel_Create = 10,///< Channel create.
		Channel_Update = 11,///< Channel update.
		Channel_Delete = 12,///< Channel delete.
		Channel_Overwrite_Create = 13,///< Channel overwrite create.
		Channel_Overwrite_Update = 14,///< Channel overwrite update.
		Channel_Overwrite_Delete = 15,///< Channel overwrite delete.
		Member_Kick = 20,///< Member kick.
		Member_Prune = 21,///< Member prune.
		Member_Ban_Add = 22,///< Member ban add.
		Member_Ban_Remove = 23,///< Member ban remove.
		Member_Update = 24,///< Member update.
		Member_Role_Update = 25,///< Member role update.
		Member_Move = 26,///< Member move.
		Member_Disconnect = 27,///< Member disconnect.
		Bot_Add = 28,///< Bot add.
		Role_Create = 30,///< Role create.
		Role_Update = 31,///< Role update.
		Role_Delete = 32,///< Role delete.
		Invite_Create = 40,///< Invite create.
		Invite_Update = 41,///< Invite update.
		Invite_Delete = 42,///< Invite delete.
		Webhook_Create = 50,///< Webhook create.
		Webhook_Update = 51,///< Webhook update.
		Webhook_Delete = 52,///< Webhook delete.
		Emoji_Create = 60,///< Emoji create.
		Emoji_Update = 61,///< Emoji update.
		Emoji_Delete = 62,///< Emoji delete.
		Message_Delete = 72,///< Message delete.
		Message_Bulk_Delete = 73,///< Message bulk delete.
		Message_Pin = 74,///< Message pin.
		Message_Unpin = 75,///< Message unpin.
		Integration_Create = 80,///< Integration create.
		Integration_Update = 81,///< Integration update.
		Integration_Delete = 82,///< Integration delete.
		Stage_Instance_Create = 83,///< Stage-Instance create.
		Stage_Instance_Update = 84,///< Stage-Instance update.
		Stage_Instance_Delete = 85,///< Stage-Instance delete.
		Sticker_Create = 90,///< Sticker create.
		Sticker_Update = 91,///< Sticker update.
		Sticker_Delete = 92,///< Sticker delete.
		Guild_Scheduled_Event_Create = 100,///< Guild-scheduled-event create.
		Guild_Scheduled_Event_Update = 101,///< Guild-scheduled-event update.
		Guild_Scheduled_Event_Delete = 102,///< Guild-scheduled-event delete.
		Thread_Create = 110,///< Thread create.
		Thread_Update = 111,///< Thread update.
		Thread_Delete = 112,///< Thread delete.
		Application_Command_Permission_Update = 121,///< Permissions were updated for a command.
		Auto_Moderation_Rule_Create = 140,///< Auto Moderation rule was created.
		Auto_Moderation_Rule_Update = 141,///< Auto Moderation rule was updated.
		Auto_Moderation_Rule_Delete = 142,///< Auto Moderation rule was deleted.
		Auto_Moderation_Block_Message = 143///< Message was blocked by AutoMod (according to a rule).
	};

	/// Audit log entry info data \brief Audit log entry info data.
	class DiscordCoreAPI_Dll OptionalAuditEntryInfoData : public DiscordEntity {
	  public:
		std::string deleteMemberDays{};///< Number of days for which the member's Messages were deleted.
		Snowflake applicationId{};///< ID of the app whose permissions were targeted APPLICATION_COMMAND_PERMISSION_UPDATE.
		std::string membersRemoved{};///< Number of members that were removed upon a prune.
		Snowflake channelId{};///< Channel Id.
		Snowflake messageId{};///< Message Id.
		std::string roleName{};///< Role name.
		std::string count{};///< Count.
		std::string type{};///< Type.

		OptionalAuditEntryInfoData() noexcept = default;

		OptionalAuditEntryInfoData(simdjson::ondemand::value jsonObjectData);

		virtual ~OptionalAuditEntryInfoData() noexcept = default;
	};

	/// Audit log change data. \brief Audit log change data.
	struct DiscordCoreAPI_Dll AuditLogChangeData {
		JsonStringValue newValue{};///< New value.
		JsonStringValue oldValue{};///< Old value.
		std::string key{};///< The key of the audit log change.

		AuditLogChangeData() noexcept = default;

		AuditLogChangeData(simdjson::ondemand::value jsonObjectData);

		virtual ~AuditLogChangeData() noexcept = default;
	};

	/// Guild prune count data. \brief Guild prune count data.
	struct DiscordCoreAPI_Dll GuildPruneCountData {
		int32_t count{ 0 };

		GuildPruneCountData() noexcept = default;

		GuildPruneCountData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildPruneCountData() noexcept = default;
	};

	/// Audit log entry data. \brief Audit log entry data.
	class DiscordCoreAPI_Dll AuditLogEntryData : public DiscordEntity {
	  public:
		TimeStamp<std::chrono::milliseconds> createdTimeStamp{};///< Time at which this entry was created.
		std::vector<AuditLogChangeData> changes{};///< Array of audit log change data.
		OptionalAuditEntryInfoData options{};///< Audit log entry info data.
		AuditLogEvent actionType{};///< Audit log action type.
		Snowflake targetId{};///< Id of the target User.
		Snowflake userId{};///< Id of the executing User.
		std::string reason{};///< The reason that was entered for the given change.

		AuditLogEntryData() noexcept = default;

		AuditLogEntryData(simdjson::ondemand::value jsonObjectData);

		virtual ~AuditLogEntryData() noexcept = default;
	};

	/// Premium tier levels. \brief Premium tier levels.
	enum class PremiumTier : uint8_t {
		None = 0,///< None.
		Tier_1 = 1,///< Tier 1.
		Tier_2 = 2,///< Tier 2.
		Tier_3 = 3///< Tier 3.
	};

	/// Default Message notification levels. \brief Default Message notification
	/// levels.
	enum class DefaultMessageNotificationLevel : uint8_t {
		All_Messages = 0,///< All messages.
		Only_Mentions = 1///< Only mentions.
	};

	/// Explicit content filter levels. \brief Explicit content filter levels.
	enum class ExplicitContentFilterLevel : uint8_t {
		Disabled = 0,///< Disabled.
		Members_Without_Roles = 1,///< Members without roles.
		All_Members = 2///< All members.
	};

	/// MFA levels. \brief MFA levels.
	enum class MFALevel : uint8_t {
		None = 0,///< None.
		Elevated = 1///< Elevated.
	};

	/// Verification levels. \brief/// Verification levels.
	enum class VerificationLevel : uint8_t {
		None = 0,///< None.
		Low = 1,///< Low.
		Medium = 2,///< Medium.
		High = 3,///< High.
		Very_High = 4///< Very high.
	};

	/// Welcome screen Channel data. \brief Welcome screen Channel data.
	struct DiscordCoreAPI_Dll WelcomeScreenChannelData {
		Snowflake channelId{};///< Id of the welcome Channel.
		std::string description{};///< Description of the welcome Channel.
		Snowflake emojiId{};///< Emoji id for the Channel.
		std::string emojiName{};///< Emoji name for the Channel.

		WelcomeScreenChannelData() noexcept = default;

		WelcomeScreenChannelData(simdjson::ondemand::value jsonObjectData);

		virtual ~WelcomeScreenChannelData() noexcept = default;
	};

	/// Welcome screen data. \brief Welcome screen data.
	struct DiscordCoreAPI_Dll WelcomeScreenData {
		std::vector<WelcomeScreenChannelData> welcomeChannels{};///< Welcome screen Channel data.
		std::string description{};///< Description of the welcome screen.

		WelcomeScreenData() noexcept = default;

		WelcomeScreenData(simdjson::ondemand::value jsonObjectData);

		virtual ~WelcomeScreenData() noexcept = default;
	};

	/// Stage instance privacy levels. \brief Stage instance privacy levels.
	enum class StageInstancePrivacyLevel : uint8_t {
		Public = 1,///< Public.
		Guild_Only = 2///< Guild only.
	};

	/// Stage instance data. \brief Stage instance data.
	class DiscordCoreAPI_Dll StageInstanceData : public DiscordEntity {
	  public:
		StageInstancePrivacyLevel privacyLevel{ 0 };///< Privacy level of the Channel.
		bool discoverableDisabled{ false };///< Is it discoverable?
		Snowflake channelId{};///< The Channel's id.
		Snowflake guildId{};///< The Guild id for which the Channel exists in.
		std::string topic{};///< The topic of the StageInstance.

		StageInstanceData() noexcept = default;

		StageInstanceData(simdjson::ondemand::value jsonObjectData);

		virtual ~StageInstanceData() noexcept = default;
	};

	/// Sticker types. \brief Sticker types.
	enum class StickerType : uint8_t {
		Standard = 1,///< Standard.
		Guild = 2///< Guild.
	};

	enum class StickerFlags : uint8_t { Available = 1 << 0 };

	/// Data representing a single Sticker. \brief Data representing a single Sticker.
	class DiscordCoreAPI_Dll StickerData : public DiscordEntity {
	  public:
		StickerFormatType formatType{};///< Format type.
		int8_t stickerFlags{ 0 };///< Sticker flags.
		int32_t nsfwLevel{ 0 };///< NSFW warning level.
		int32_t sortValue{ 0 };///< Where in the stack of stickers it resides.
		std::string description{};///< Description of the Sticker.
		Snowflake guildId{};///< The Guild id for which the Sticker exists in.
		StickerType type{};///< The type of Sticker.
		std::string packId{};///< Pack id of the Sticker.
		std::string asset{};///< Asset value for the Sticker.
		std::string name{};///< The Sticker's name.
		std::string tags{};///< Tags for the Sticker to use.

		UserData user{};///< The User that uploaded the Guild Sticker.

		StickerData() noexcept = default;

		StickerData(simdjson::ondemand::value jsonObjectData);

		virtual ~StickerData() noexcept = default;
	};

	/// Data representing a single Guild preview. \brief Data representing a single Guild preview.
	struct DiscordCoreAPI_Dll GuildPreviewData {
		int32_t approximatePresenceCount{ 0 };
		int32_t approximateMemberCount{ 0 };
		std::vector<StickerData> stickers{};
		std::vector<EmojiData> emojis{};
		std::vector<std::string> features{};
		std::string discoverySplash{};
		std::string description{};
		std::string splash{};
		Snowflake id{};
		std::string name{};
		std::string icon{};

		GuildPreviewData() noexcept = default;

		GuildPreviewData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildPreviewData() noexcept = default;
	};

	/// Afk timeout durations. \brief Afk timeout durations.
	enum class AfkTimeOutDurations : int16_t {
		Shortest = 60,///< Shortest.
		Short = 300,///< Short.
		Medium = 900,///< Medium.
		Long = 1800,///< Long.
		Longest = 3600///< Longest.
	};

	/// Guild NSFW level. \brief Guild NSFW level.
	enum class GuildNSFWLevel : uint8_t {
		Default = 0,///< Default.
		Explicit = 1,///< Explicit.
		Safe = 2,///< Safe.
		Age_Restricted = 3///< Age restricted.
	};

	/// System channel flags. \brief System channel flags.
	enum class SystemChannelFlags : uint8_t {
		Suppress_Join_Notifications = 1 << 0,///< Suppress member join notifications.
		Suppress_Premium_Subscriptions = 1 << 1,///< Suppress server boost notifications.
		Suppress_Guild_Reminder_Notifications = 1 << 2,///< Suppress server setup tips.
		Suppress_Join_Notification_Replies = 1 << 3///< Hide member join sticker reply buttons.
	};

	/// Guild flags. \brief Guild flags.
	enum class GuildFlags : uint8_t {
		WidgetEnabled = 1 << 0,///< Widget enabled.
		Unavailable = 1 << 1,///< Unavailable.
		Owner = 1 << 2,///< Owner.
		Large = 1 << 3,///< Large.
		Premium_Progress_Bar_Enabled = 1 << 4///< Premium progress bar enabled
	};

	/// Data structure representing a single Guild. \brief Data structure representing a single Guild.
	class DiscordCoreAPI_Dll GuildData : public DiscordEntity {
	  public:
		DiscordCoreClient* discordCoreClient{ nullptr };///< A pointer to the DiscordCoreClient.
		TimeStamp<std::chrono::milliseconds> joinedAt{};///< When the bot joined this Guild.
		VoiceConnection* voiceConnectionPtr{ nullptr };///< A pointer to the VoiceConnection, if present.
		std::vector<Snowflake> guildScheduledEvents{};///< Array of Guild channels.
		std::vector<PresenceUpdateData> presences{};///< Presence states for each of the GuildMembers..
		std::vector<Snowflake> stageInstances{};///< Array of Guild channels.
		std::vector<Snowflake> stickers{};///< Array of Guild channels.
		std::vector<Snowflake> channels{};///< Array of Guild channels.
		std::vector<Snowflake> threads{};///< Array of Guild channels.
		std::vector<Snowflake> members{};///< Array of GuildMembers.
		std::vector<Snowflake> roles{};///< Array of Guild roles.
		std::vector<Snowflake> emoji{};///< Array of Guild channels.
		int32_t memberCount{ 0 };///< Member count.
		StringWrapper name{};///< The Guild's name.
		Snowflake ownerId{};///< User id of the Guild's owner.
		int8_t flags{ 0 };///< Guild flags.
		IconHash icon{};///< Url to the Guild's icon.

		GuildData() noexcept = default;

		GuildData& operator=(GuildData&&) noexcept = default;
		;

		GuildData(GuildData&&) noexcept = default;

		GuildData& operator=(const GuildData&) noexcept = default;

		GuildData(const GuildData&) noexcept = default;

		GuildData(simdjson::ondemand::value jsonObjectData);

		/// For connecting to an individual voice channel. \brief For connecting to an individual voice channel.
		/// \param guildMemberId An id of the guild member who's current voice channel to connect to.
		/// \param channelId An id of the voice channel to connect to.
		/// \param selfDeaf Whether or not to self-deafen the bot.
		/// \param selfMute Whether or not to self-mute the bot.
		/// \param streamType For usage with the Vc-to-Vc audio streaming option.
		/// \param streamInfo For usage with the Vc-to-Vc audio streaming option.
		/// \returns VoiceConnection* A pointer to the currently held voice connection, or nullptr if it failed to connect.
		VoiceConnection* connectToVoice(const Snowflake guildMemberId, const Snowflake channelId = Snowflake{ 0 }, bool selfDeaf = false, bool selfMute = false,
			StreamType streamType = StreamType::None, StreamInfo streamInfo = StreamInfo{});

		std::string getBannerUrl() noexcept;

		std::string getIconUrl() noexcept;

		bool areWeConnected();

		void disconnect();

		virtual ~GuildData() noexcept = default;
	};

	class DiscordCoreAPI_Dll GuildDataVector {
	  public:
		friend class Guilds;

		GuildDataVector() noexcept = default;

		operator std::vector<GuildData>();

		GuildDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildDataVector() noexcept = default;

	  protected:
		std::vector<GuildData> guildDatas{};
	};

	/// Guild scheduled event privacy levels. \brief Guild scheduled event privacy levels.
	enum class GuildScheduledEventPrivacyLevel : uint8_t {
		Public = 1,///< Public.
		Guild_Only = 2///< Guild only.
	};

	/// GuildScheduledEventStatus. \brief GuildScheduledEventStatus.
	enum class GuildScheduledEventStatus : uint8_t {
		Scheduled = 1,///< Scheduled.
		Active = 2,///< Active.
		Completed = 3,///< Completed.
		Canceled = 4///< Cancelled.
	};

	/// Guild scheduled event entity types. \brief Guild scheduled event entity types.
	enum class GuildScheduledEventEntityType : uint8_t {
		None = 0,///< None.
		State_Instance = 1,///< Stage instance.
		Voice = 2,///< Voice.
		External = 3///< External.
	};

	/// Guild scheduled event entity metadata. \brief Guild scheduled event entity metadata.
	struct DiscordCoreAPI_Dll GuildScheduledEventMetadata {
		std::string location{};

		GuildScheduledEventMetadata() noexcept = default;

		GuildScheduledEventMetadata(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildScheduledEventMetadata() noexcept = default;
	};

	/// Data representing a Guild Scheduled Event. \brief Data representing a Guild Scheduled Event.
	class DiscordCoreAPI_Dll GuildScheduledEventData : public DiscordEntity {
	  public:
		GuildScheduledEventPrivacyLevel privacyLevel{};///< The privacy level of the scheduled event.
		GuildScheduledEventMetadata entityMetadata{};///< Additional metadata for the Guild scheduled event.
		GuildScheduledEventEntityType entityType{};///< The type of the scheduled event.
		GuildScheduledEventStatus status{};///< The status of the scheduled event.
		std::string scheduledStartTime{};///< The time the scheduled event will start.
		std::string scheduledEndTime{};///< The time the scheduled event will end, required if entity_type is External.
		uint32_t userCount{ 0 };///< The number of users subscribed to the scheduled event.
		Snowflake channelId{};///< The Channel id in which the scheduled event will be hosted, or null if scheduled entity type is External.
		std::string description{};///< The description of the scheduled event(1 - 1000 characters.
		Snowflake guildId{};///< The Guild id which the scheduled event belongs to.
		Snowflake creatorId{};///< The id of the User that created the scheduled event *.
		UserData creator{};///< The User that created the scheduled event.
		Snowflake entityId{};///< The id of an entity associated with a Guild scheduled event.
		std::string name{};///< The name of the scheduled event(1 - 100 characters).

		GuildScheduledEventData() noexcept = default;

		GuildScheduledEventData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildScheduledEventData() noexcept = default;
	};

	/// Data representing a single GuildScheduledEventUser. \brief Data representing a single GuildScheduledEventUser.
	struct DiscordCoreAPI_Dll GuildScheduledEventUserData {
		Snowflake guildScheduledEventId{};///< The scheduled event id which the User subscribed to/
		GuildMemberData member{};///< Guild member data for this User for the Guild which this event belongs to, if any.
		UserData user{};///< User which subscribed to an event.

		GuildScheduledEventUserData() noexcept = default;

		GuildScheduledEventUserData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildScheduledEventUserData() noexcept = default;
	};

	class DiscordCoreAPI_Dll GuildScheduledEventUserDataVector {
	  public:
		GuildScheduledEventUserDataVector() noexcept = default;

		operator std::vector<GuildScheduledEventUserData>();

		GuildScheduledEventUserDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildScheduledEventUserDataVector() noexcept = default;

	  protected:
		std::vector<GuildScheduledEventUserData> guildScheduledEventUserDatas{};
	};

	class DiscordCoreAPI_Dll GuildScheduledEventDataVector {
	  public:
		GuildScheduledEventDataVector() noexcept = default;

		operator std::vector<GuildScheduledEventData>();

		GuildScheduledEventDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildScheduledEventDataVector() noexcept = default;

	  protected:
		std::vector<GuildScheduledEventData> guildScheduledEventDatas{};
	};

	/// Invite data. \brief Invite data.
	struct DiscordCoreAPI_Dll InviteData {
		TimeStamp<std::chrono::milliseconds> expiresAt{};///< When the invite expires.
		TimeStamp<std::chrono::milliseconds> createdAt{};///< Time it was created at.
		GuildScheduledEventData guildScheduledEvent{};///< Scheduled Guild event.
		int32_t approximatePresenceCount{ 0 };///< Approximate presence count.
		ApplicationData targetApplication{};///< Application data.
		int32_t approximateMemberCount{ 0 };///< Approximate member count.
		StageInstanceData stageInstance{};///< Stage instance data.
		bool temporary{ false };///< Is it temporary?
		int32_t targetType{ 0 };///< Target type.
		UserData targetUser{};///< Target User of the invite.
		ChannelData channel{};///< Channel data of the Channel that the invite is for.
		Snowflake guildId{};///< The Guild this invite is for.
		UserData inviter{};///< The User who created the invite.
		int32_t maxUses{ 0 };///< Max number of uses.
		int32_t maxAge{ 0 };///< Maximum age of the invite.
		GuildData guild{};///< Guild data of the Channel that the invite is for.
		int32_t uses{ 0 };///< The current number of uses.
		std::string code{};///< Unique invite code.

		InviteData() noexcept = default;

		InviteData(simdjson::ondemand::value jsonObjectData);

		virtual ~InviteData() noexcept = default;
	};

	class DiscordCoreAPI_Dll InviteDataVector {
	  public:
		InviteDataVector() noexcept = default;

		operator std::vector<InviteData>();

		InviteDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~InviteDataVector() noexcept = default;

	  protected:
		std::vector<InviteData> theInviteDatas{};
	};

	/// Represents a Guild Template. \brief Represents a Guild Template.
	struct DiscordCoreAPI_Dll GuildTemplateData {
		GuildData serializedSourceGuild{};///< The Guild snapshot this template contains.
		uint32_t usageCount{ 0 };///< Number of times this template has been used.
		std::string sourceGuildId{};///< The ID of the Guild this template is based on.
		bool isDirty{ false };///< Whether the template has unsynced changes.
		std::string description{};///< The description for the template.
		std::string creatorId{};///< The ID of the User who created the template.
		std::string createdAt{};///< When this template was created.
		std::string updatedAt{};///< When this template was last synced to the source Guild.
		UserData creator{};///< The User who created the template.
		std::string code{};///< The template code(unique ID).
		std::string name{};///< Template name.

		GuildTemplateData() noexcept = default;

		GuildTemplateData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildTemplateData() noexcept = default;
	};

	class DiscordCoreAPI_Dll GuildTemplateDataVector {
	  public:
		GuildTemplateDataVector() noexcept = default;

		operator std::vector<GuildTemplateData>();

		GuildTemplateDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildTemplateDataVector() noexcept = default;

	  protected:
		std::vector<GuildTemplateData> guildTemplateDatas{};
	};

	/// Invite target types. \brief Invite target types.
	enum class InviteTargetTypes : uint8_t {
		Stream = 1,///< Stream.
		Embedded_Application = 2///< Embedded application.
	};

	/// WebHook types. \brief WebHook types.
	enum class WebHookType : uint8_t {
		Incoming = 1,///< Incoming.
		Channel_Follower = 2,///< Channel follower.
		Application = 3///< Application.
	};

	/// WebHook data. \brief WebHook data.
	class DiscordCoreAPI_Dll WebHookData : public DiscordEntity {
	  public:
		ChannelData sourceChannel{};///< Channel for which th WebHook was issued.
		Snowflake applicationId{};///< Application id.
		GuildData sourceGuild{};///< Source Guild id.
		WebHookType type{ 0 };///< Type of WebHook.
		Snowflake channelId{};///< Channel id for which the WebHook was issued.
		Snowflake guildId{};///< Guild id for which the WebHook was issued.
		UserData user{};///< User which create the WebHook.
		std::string avatar{};///< Avatar of the WebHook.
		std::string token{};///< Token of the WebHook.
		std::string name{};///< Name of the WebHook.
		std::string url{};///< Url of the WebHook.

		WebHookData() noexcept = default;

		WebHookData(simdjson::ondemand::value jsonObjectData);

		virtual ~WebHookData() noexcept = default;
	};

	class DiscordCoreAPI_Dll WebHookDataVector {
	  public:
		WebHookDataVector() noexcept = default;

		operator std::vector<WebHookData>();

		WebHookDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~WebHookDataVector() noexcept = default;

	  protected:
		std::vector<WebHookData> theWebHookDatas{};
	};

	/// Audit log data. \brief Audit log data.
	class DiscordCoreAPI_Dll AuditLogData {
	  public:
		std::vector<GuildScheduledEventData> guildScheduledEvents{};///< Array of guild scheduled event objects.
		std::vector<AutoModerationRuleData> autoModerationRules{};///< List of auto moderation rules referenced in the audit log.
		std::vector<AuditLogEntryData> auditLogEntries{};///< Array of audit log entry objects.
		std::vector<IntegrationData> integrations{};///< Array of partial integration objects.
		std::vector<WebHookData> webhooks{};///< Array of webhook objects.
		std::vector<ChannelData> threads{};///< Array of thread-specific channel objects.
		std::vector<UserData> users{};///< Array of user objects.

		auto getAuditLogData(const Snowflake userIdOfChanger, AuditLogEvent auditLogType);

		auto getAuditLogData(AuditLogEvent auditLogType, const Snowflake userIdOfTarget);

		AuditLogData() noexcept = default;

		AuditLogData(simdjson::ondemand::value jsonObjectData);

		virtual ~AuditLogData() noexcept = default;
	};

	/// For removing a reaction. \brief For removing a reaction.
	struct DiscordCoreAPI_Dll ReactionRemoveData {
		Snowflake channelId{};
		Snowflake messageId{};
		Snowflake guildId{};
		Snowflake userId{};
		EmojiData emoji{};

		ReactionRemoveData() noexcept = default;

		ReactionRemoveData(simdjson::ondemand::value jsonObjectData);

		virtual ~ReactionRemoveData() noexcept = default;
	};

	/// For storing Interaction-related values. \brief For storing Interaction-related values.
	struct DiscordCoreAPI_Dll InteractionPackageData {
		std::string interactionToken{};
		Snowflake applicationId{};
		Snowflake interactionId{};
	};

	/// For storing Message-related values. \brief For storing Message-related values.
	struct DiscordCoreAPI_Dll MessagePackageData {
		Snowflake channelId{};
		Snowflake messageId{};
	};

	/// Data structure representing an ApplicationCommand's option choice. \brief Data structure representing an ApplicationCommand's option choice.
	class DiscordCoreAPI_Dll ApplicationCommandOptionChoiceData {
	  public:
		std::unordered_map<std::string, std::string> nameLocalizations{};///< Dictionary with keys in available locales Localization dictionary for the name field.
		std::string value{};///< The value of the option.
		JsonType type{};///< The type of the option.
		std::string name{};///< The name of the current choice.

		ApplicationCommandOptionChoiceData() noexcept = default;

		ApplicationCommandOptionChoiceData& operator=(ApplicationCommandOptionChoiceData&&) noexcept = default;
		ApplicationCommandOptionChoiceData(ApplicationCommandOptionChoiceData&&) noexcept = default;

		ApplicationCommandOptionChoiceData& operator=(const ApplicationCommandOptionChoiceData&) noexcept = default;
		ApplicationCommandOptionChoiceData(const ApplicationCommandOptionChoiceData&) noexcept = default;

		operator Jsonifier();

		ApplicationCommandOptionChoiceData(simdjson::ondemand::value jsonObjectData);

		friend bool operator==(const ApplicationCommandOptionChoiceData&, const ApplicationCommandOptionChoiceData&);

		virtual ~ApplicationCommandOptionChoiceData() noexcept = default;
	};

	/// Data structure representing an ApplicationCommand's option. \brief Data structure representing an ApplicationCommand's option.
	struct DiscordCoreAPI_Dll ApplicationCommandOptionData {
		std::vector<ApplicationCommandOptionChoiceData> choices{};///< A vector of possible choices for the current ApplicationCommand option.
		int32_t minValue{ std::numeric_limits<int32_t>::max() };///< If the option is an INTEGER or NUMBER type, the minimum value permitted.
		int32_t maxValue{ std::numeric_limits<int32_t>::min() };///< If the option is an INTEGER or NUMBER type, the maximum value permitted.
		std::unordered_map<std::string, std::string> descriptionLocalizations{};///< Dictionary for the description localizations field.
		std::vector<ApplicationCommandOptionData> options{};///< A vector of possible options for the current ApplicationCommand option.
		std::unordered_map<std::string, std::string> nameLocalizations{};///< Dictionary for the name localizations field.
		ApplicationCommandOptionType type{};///< The type of command option.
		std::vector<ChannelType> channelTypes{};///< Set when the ApplicationCommand option type is set to Channel.
		bool autocomplete{ false };///< If autocomplete interactions are enabled for this STRING, INTEGER, or NUMBER type option.
		bool required{ false };///< If the parameter is required or optional-- default false.
		std::string description{};///< A description of the current ApplicationCommand option.
		std::string name{};///< Name of the current ApplicationCommand option.

		ApplicationCommandOptionData() noexcept = default;

		operator Jsonifier();

		friend bool operator==(const ApplicationCommandOptionData&, const ApplicationCommandOptionData&);

		ApplicationCommandOptionData(simdjson::ondemand::value jsonObjectData);

		virtual ~ApplicationCommandOptionData() noexcept = default;
	};

	/// Representing "TypingStart" data. \brief Representing "TypingStart" data.
	struct DiscordCoreAPI_Dll TypingStartData {
		GuildMemberData member{};
		Snowflake channelId{};
		int32_t timeStamp{ 0 };
		Snowflake guildId{};
		Snowflake userId{};

		TypingStartData() noexcept = default;

		TypingStartData(simdjson::ondemand::value jsonObjectData);

		virtual ~TypingStartData() noexcept = default;
	};

	struct DiscordCoreAPI_Dll YouTubeFormat {
		int32_t averageBitrate{ 0 };
		int64_t contentLength{ 0 };
		std::string signatureCipher{};
		std::string audioSampleRate{};
		std::string audioQuality{};
		std::string downloadUrl{};
		int32_t bitrate{ 0 };
		std::string signature{};
		std::string mimeType{};
		int32_t height{ 0 };
		std::string quality{};
		int32_t width{ 0 };
		std::string codecs{};
		std::string aitags{};
		int32_t itag{ 0 };
		int32_t fps{ 0 };

		YouTubeFormat() noexcept = default;

		YouTubeFormat(simdjson::ondemand::value);
	};

	/// YouTube format data. \brief YouTube format data.
	class DiscordCoreAPI_Dll YouTubeFormatVector {
	  public:
		YouTubeFormatVector() noexcept = default;

		operator std::vector<YouTubeFormat>();

		YouTubeFormatVector(simdjson::ondemand::value jsonObjectData);

		virtual ~YouTubeFormatVector() noexcept = default;

	  protected:
		std::vector<YouTubeFormat> theFormats{};
	};

	/// Application command types. \brief Application command types.
	enum class ApplicationCommandType : uint8_t {
		Chat_Input = 1,///< Chat input.
		User = 2,///< User.
		Message = 3///< Message.
	};

	/// User command Interaction data. \brief User command Interaction data.
	struct DiscordCoreAPI_Dll UserCommandInteractionData {
		Snowflake targetId{};///< The target User's id.

		UserCommandInteractionData() noexcept = default;

		UserCommandInteractionData(simdjson::ondemand::value jsonObjectData);

		virtual ~UserCommandInteractionData() noexcept = default;
	};

	/// Message command interacction data. \brief Message command interacction data.
	struct DiscordCoreAPI_Dll MessageCommandInteractionData {
		Snowflake targetId{};///< The target Message's id.

		MessageCommandInteractionData() noexcept = default;

		MessageCommandInteractionData(simdjson::ondemand::value jsonObjectData);

		virtual ~MessageCommandInteractionData() noexcept = default;
	};

	/// Component types. \brief Component types.
	enum class ComponentType : uint8_t {
		ActionRow = 1,///< A container for other components.
		Button = 2,///< A button object.
		SelectMenu = 3,///< A select menu for picking from choices.
		TextInput = 4///< A text input object
	};

	/// Component Interaction data. \brief Component Interaction data.
	struct DiscordCoreAPI_Dll ComponentInteractionData {
		ComponentType componentType{};///< The type of component.
		std::vector<std::string> values{};///< The values of the components.
		std::string customId{};///< The custom id of the Interaction entity.

		ComponentInteractionData() noexcept = default;

		ComponentInteractionData(simdjson::ondemand::value jsonObjectData);

		virtual ~ComponentInteractionData() noexcept = default;
	};

	/// Modal interaction data, for inputs from text modals. \brief Modal interaction data, for inputs from text modals.
	struct DiscordCoreAPI_Dll ModalInteractionData {
		std::string customIdSmall{};///< The custom id of a particular modal input.
		std::string customId{};///< The custom id of the Interaction entity.
		std::string value{};///< The input value of the modal.

		ModalInteractionData() noexcept = default;

		ModalInteractionData(simdjson::ondemand::value jsonObjectData);

		virtual ~ModalInteractionData() noexcept = default;
	};

	/// Allowable mentions for a Message. \brief Allowable mentions for a Message.
	class DiscordCoreAPI_Dll AllowedMentionsData {
	  public:
		bool repliedUser{ false };///< For replies, whether to mention the author of the Message being replied to (default false).
		std::vector<std::string> parse{};///< A vector of allowed mention types to parse from the content.
		std::vector<std::string> roles{};///< Array of role_ids to mention (Max size of 100)
		std::vector<std::string> users{};///< Array of user_ids to mention (Max size of 100)

		AllowedMentionsData() noexcept = default;

		AllowedMentionsData(simdjson::ondemand::value jsonObjectData);

		operator Jsonifier();

		virtual ~AllowedMentionsData() noexcept = default;
	};

	/// Interaction types. \brief Interaction types.
	enum class InteractionType : uint8_t {
		Ping = 1,///< Ping.
		Application_Command = 2,///< Application command.
		Message_Component = 3,///< Message component.
		Application_Command_Autocomplete = 4,///< Application command autocomplete.
		Modal_Submit = 5///< Modal submission.
	};

	/// Represents a single selection from a select-menu. \brief Represents a single selection from a select-menu.
	class DiscordCoreAPI_Dll SelectOptionData {
	  public:
		bool _default{ false };///< Is it the default option?
		std::string description{};///< Description of the select-menu-option.
		EmojiData emoji{};///< An optional emoji to put on it.
		std::string label{};///< A visible label for the select-menu-option.
		std::string value{};///< A value for identifying the option.

		SelectOptionData() noexcept = default;

		SelectOptionData(simdjson::ondemand::value jsonObjectData);

		virtual ~SelectOptionData() noexcept = default;
	};

	/// Button styles. \brief Button styles.
	enum class ButtonStyle : uint8_t {
		Primary = 1,///< Primary.
		Success = 3,///< Success.
		Secondary = 2,///< Secondary.
		Danger = 4,///< Danger.
		Link = 5///< Link.
	};

	/// Represents a single Message-component. \brief Represents a single Message-component.
	struct DiscordCoreAPI_Dll ComponentData {
		std::vector<SelectOptionData> options{};///< Aray of select options the choices in the select, max 25.
		bool required{ false };///< Whether this component is required to be filled.
		bool disabled{ false };///< Whether the component is disabled, default false.
		std::string placeholder{};///< Custom placeholder text if nothing is selected, max 100 characters.
		int32_t minValues{ 0 };///< The minimum number of items that must be chosen; default 1, min 0, max 25.
		int32_t maxValues{ 0 };///< The maximum number of items that can be chosen; default 1, max 25.
		int32_t minLength{ 0 };///< The minimum input length for a text input.
		int32_t maxLength{ 0 };///< The maximum input length for a text input.
		ComponentType type{};///< Integer component type.
		std::string customId{};///< A developer-defined identifier for the component, max 100 characters.
		EmojiData emoji{};///< Emoji name, id, and animated.
		std::string label{};///< The label for this component.
		std::string value{};///< A pre-filled value for this component.
		std::string title{};///< Url, for url types.
		int32_t style{};///< One of ButtonStyle, or TextInputStyle.
		std::string url{};///< Url, for url types.

		ComponentData() noexcept = default;

		ComponentData(simdjson::ondemand::value);
	};

	/// Action row data of Message components. \brief Action row data of Message components.
	class DiscordCoreAPI_Dll ActionRowData {
	  public:
		std::vector<ComponentData> components{};///< Array of components to make up the action-row.

		ActionRowData() noexcept = default;

		operator Jsonifier();

		ActionRowData(simdjson::ondemand::value jsonObjectData);

		virtual ~ActionRowData() noexcept = default;
	};

	/// Interaction callback types. \brief Interaction callback types.
	enum class InteractionCallbackType : uint8_t {
		Pong = 1,///< ACK a Ping.
		Channel_Message_With_Source = 4,///< Respond to an interaction with a message.
		Deferred_Channel_Message_With_Source = 5,///< ACK an interaction and edit a response later, the user sees a loading state.
		Deferred_Update_Message = 6,///< For components, ACK an interaction and edit the original message later; the user does not see a loading state.
		Update_Message = 7,///< For components, edit the message the component was attached to.
		Application_Command_Autocomplete_Result = 8,///< Respond to an autocomplete interaction with suggested choices.
		Modal = 9///< Respond to an interaction with a popup modal.
	};

	/// Interaction ApplicationCommand callback data. \brief Interaction ApplicationCommand callback data.
	struct DiscordCoreAPI_Dll InteractionCallbackData {
		std::vector<ApplicationCommandOptionChoiceData> choices{};///< Autocomplete choices(max of 25 choices).
		AllowedMentionsData allowedMentions{};///< Allowed mentions data.
		std::vector<AttachmentData> attachments{};///< Array of partial attachment objects attachment objects with filename and description.
		std::vector<ActionRowData> components{};///< Message components.
		std::vector<EmbedData> embeds{};///< Message embeds.
		std::vector<File> files{};///< Files for uploading.
		std::string customId{};///< A developer-defined identifier for the component, max 100 characters.
		bool tts{ false };///< Is it TTS?
		std::string content{};///< Message content.
		int32_t flags{ 0 };///< Flags.
		std::string title{};///< The title of the popup modal.
	};

	struct CreateApplicationCommandData;

	/// Data structure representing an ApplicationCommand. \brief Data structure representing an ApplicationCommand.
	class DiscordCoreAPI_Dll ApplicationCommandData : public DiscordEntity {
	  public:
		std::unordered_map<std::string, std::string> descriptionLocalizations{};///< Dictionary with keys in available locales Localization dictionary for name field.
		std::vector<ApplicationCommandOptionData> options{};///< A vector of possible options for the current ApplicationCommand.
		std::unordered_map<std::string, std::string> nameLocalizations{};///< Dictionary with keys in available locales Localization dictionary for name field.
		Permissions defaultMemberPermissions{};///< Set of permissions represented as a bit set all
		ApplicationCommandType type{};///< The type of ApplicationCommand.
		bool dmPermission{ false };///< Indicates whether the command is available in DMs with the app, only for globally - scoped commands.
		Snowflake applicationId{};///< The current application id.
		std::string description{};///< A description of the current ApplicationCommand.
		Snowflake guildId{};///< (Where applicable) a Guild id for which guild to assign this ApplicationCommand to.
		std::string version{};///< An autoincremented version.
		std::string name{};///< Name of the current ApplicationCommand.

		ApplicationCommandData() noexcept = default;

		ApplicationCommandData(simdjson::ondemand::value jsonObjectData);

		friend bool operator==(const ApplicationCommandData&, const ApplicationCommandData&);

		virtual ~ApplicationCommandData() noexcept = default;
	};

	/// Channel mention data. \brief Channel mention data.
	class DiscordCoreAPI_Dll ChannelMentionData : public DiscordEntity {
	  public:
		Snowflake guildId{};///< The id of the Guild where it took place.
		std::string name{};///< The name of the Channel that was mentioned.
		ChannelType type{};///< The type of Channel that was mentioned.

		ChannelMentionData() noexcept = default;

		ChannelMentionData(simdjson::ondemand::value jsonObjectData);

		virtual ~ChannelMentionData() noexcept = default;
	};

	/// Data for when some Channel pins are updated. \brief Data for when some Channel pins are updated.
	struct DiscordCoreAPI_Dll ChannelPinsUpdateEventData {
		TimeStamp<std::chrono::milliseconds> lastPinTimeStamp{};///< The time of the last pinned Message.
		Snowflake channelId{};///< The id of the Channel within which the Message was pinned.
		Snowflake guildId{};///< The id of the Guild within which the Message was pinned.

		ChannelPinsUpdateEventData() noexcept = default;

		ChannelPinsUpdateEventData(simdjson::ondemand::value jsonObjectData);

		virtual ~ChannelPinsUpdateEventData() noexcept = default;
	};

	/// Data for when threads are synced. \brief Data for when threads are synced.
	struct DiscordCoreAPI_Dll ThreadListSyncData {
		std::vector<ThreadMemberData> members{};///< Array of members that are a part of the Thread.
		std::vector<ChannelData> threads{};///< All active threads in the given channels that the current User can access.
		std::vector<std::string> channelIds{};///< The parent Channel ids whose threads are being synced. If omitted, then threads were synced for entire Guild.
		Snowflake guildId{};///< The id of the Guild for which the threads are being synced.

		ThreadListSyncData() noexcept = default;

		ThreadListSyncData(simdjson::ondemand::value jsonObjectData);

		virtual ~ThreadListSyncData() noexcept = default;
	};

	/// Represents a Thread-members-update. \brief Represents a Thread-members-update.
	class DiscordCoreAPI_Dll ThreadMembersUpdateData : public DiscordEntity {
	  public:
		std::vector<ThreadMemberData> addedMembers{};///< New members added to the Thread.
		std::vector<std::string> removedMemberIds{};///< Members who have been removed.
		int32_t memberCount{ 0 };///< Number of Guild-members in the Thread.
		Snowflake guildId{};///< Guild id of the Thread.

		ThreadMembersUpdateData() noexcept = default;

		ThreadMembersUpdateData(simdjson::ondemand::value jsonObjectData);

		virtual ~ThreadMembersUpdateData() noexcept = default;
	};

	/// Message Interaction data. \brief Message Interaction data.
	class DiscordCoreAPI_Dll MessageInteractionData : public DiscordEntity {
	  public:
		GuildMemberData member{};
		InteractionType type{};
		UserData user{};
		std::string name{};

		MessageInteractionData() noexcept = default;

		MessageInteractionData(simdjson::ondemand::value jsonObjectData);

		virtual ~MessageInteractionData() noexcept = default;
	};

	/// Message types. \brief Message types.
	enum class MessageType : uint8_t {
		Default = 0,///< Default.
		Recipient_Add = 1,///< Recipient add.
		Recipient_Remove = 2,///< Recipient remove.
		Call = 3,///< Call.
		Channel_Name_Change = 4,///< Channel name change.
		Channel_Icon_Change = 5,///< Channel icon change.
		Channel_Pinned_Message = 6,///< Channel pinned Message.
		Guild_Member_Join = 7,///< Guild memeber join.
		User_Premium_Guild_Subscription = 8,///< User premium Guild subscription.
		User_Premium_Guild_Subscription_Tier_1 = 9,///< User premium Guild subscription tier 1.
		User_Premium_Guild_Subscription_Tier_2 = 10,///< User premium Guild subscription tier 2.
		User_Premium_Guild_Subscription_Tier_3 = 11,///< User premium Guild subscription tier 3.
		Channel_Follow_Add = 12,///< Channel follow add.
		Guild_Discovery_Disqualified = 14,///< Guild discovery disqualified.
		Guild_Discovery_Requalified = 15,///< Guild discovery requalified.
		Guild_Discovery_Grace_Period_Initial_Warning = 16,///< Guild discovery grade period initial warning.
		Guild_Discovery_Grace_Period_Final_Warning = 17,///< Guild discovery grade period final warning.
		Thread_Created = 18,///< Thread created.
		Reply = 19,///< Reply.
		Chat_Input_Command = 20,///< Chat input command.
		Thread_Starter_Message = 21,///< Thread starter Message.
		Guild_Invite_Reminder = 22,///< Guild invite reminder.
		Context_Menu_Command = 23///< Context menu command.
	};

	/// Message flags. \brief Message flags.
	enum class MessageFlags : uint8_t {
		Crossposted = 1 << 0,///< Crossposted.
		Is_Crosspost = 1 << 1,///< Is crosspost.
		Suppress_Embeds = 1 << 2,///< Supress embeds.
		Source_Message_Deleted = 1 << 3,///< Source Message deleted.
		Urgent = 1 << 4,///< Urgent.
		Has_Thread = 1 << 5,///< Has Thread.
		Ephemeral = 1 << 6,///< Ephemeral.
		Loading = 1 << 7///< Loading.
	};

	/// Sticker item types. \brief Sticker item types.
	enum class StickerItemType : uint8_t {
		Png = 1,///< Png.
		Apng = 2,///< Apng.
		Lottie = 3///< Lottie.
	};

	/// Represents a forum thread message. \brief Represents a forum thread message.
	struct DiscordCoreAPI_Dll ForumThreadMessageData {
		std::vector<AttachmentData> attachments{};///< Array of partial attachment objects attachment objects with filename.
		AllowedMentionsData allowedMentions{};///< Allowed mention object allowed mentions for the message.
		std::vector<ActionRowData> components{};///< Array of message component objects the components to include with the message.
		std::vector<std::string> stickerIds{};///< Array of snowflakes IDs of up to 3 stickers in the server to send in the message.
		std::vector<EmbedData> embeds{};///< Array of embed objects	embedded rich content (up to 6000 characters).
		std::vector<File> files{};///< File contents the contents of the file being sent one of content, file, embed(s), sticker_ids.
		std::string content{};///< The message contents (up to 2000 characters).
		int32_t flags{ 0 };///< Flags to be set for the message.
	};

	/// Message Sticker item data. \brief Message Sticker item data.
	class DiscordCoreAPI_Dll StickerItemData : public DiscordEntity {
	  public:
		StickerItemType formatType{};///< Message Sticker item type.
		std::string name{};///< The name of the Sticker.

		StickerItemData() noexcept = default;

		StickerItemData(simdjson::ondemand::value jsonObjectData);

		virtual ~StickerItemData() noexcept = default;
	};

	/// The core of a Message's data structure. \brief The core of a Message's data structure.
	class DiscordCoreAPI_Dll MessageDataOld : public DiscordEntity {
	  public:
		TimeStamp<std::chrono::milliseconds> editedTimestamp{};///< The time at which it was edited.
		TimeStamp<std::chrono::milliseconds> timeStamp{};///< The timeStamp of when the Message was created.
		std::vector<ChannelMentionData> mentionChannels{};///< array of Channel mention data.
		MessageReferenceData messageReference{};///< Message reference data.
		std::vector<StickerItemData> stickerItems{};///< Array of Message Sticker item data.
		std::vector<AttachmentData> attachments{};///< Array of attachment data.
		MessageInteractionData interaction{};///< Message Interaction data.
		std::vector<ActionRowData> components{};///< Array of action row data.
		std::vector<ReactionData> reactions{};//< Array of reaction data.
		std::vector<StickerData> stickers{};///< Array of Message Sticker data.
		MessageActivityData activity{};///< Message activity data.
		bool mentionEveryone{ false };///< Does the Message mention everyone?
		ApplicationData application{};///< Application data.
		std::vector<std::string> mentionRoles{};///< std::vector of "mention roles" ids.
		std::vector<UserData> mentions{};///< Array of User data, for individual's that were mentioned.
		std::vector<EmbedData> embeds{};///< Array of Message embeds.
		Snowflake applicationId{};///< Application id.
		GuildMemberData member{};///< The author's Guild member data.
		Snowflake channelId{};///< The Channel it was sent in.
		Snowflake webHookId{};///< WebHook id of the Message, if applicable.
		bool pinned{ false };///< Is it pinned?
		ChannelData thread{};///< The Thread that the Message was sent in, if applicable.
		Snowflake guildId{};///< The id of the Guild the Message was sent in.
		MessageType type{};///< Message type.
		UserData author{};///< The author's User data.
		bool tts{ false };///< Is it a text-to-speech Message?
		std::string content{};///< The Message's content.
		int32_t flags{ 0 };///< Flags.
		std::string nonce{};///< Nonce.

		MessageDataOld() noexcept = default;

		MessageDataOld(simdjson::ondemand::value jsonObjectData);

		virtual ~MessageDataOld() noexcept = default;
	};

	/// Data structure representing a single Message. \brief Data structure representing a single Message.
	class DiscordCoreAPI_Dll MessageData : public MessageDataOld {
	  public:
		std::unique_ptr<MessageDataOld> referencedMessage{ std::make_unique<MessageDataOld>() };///< The referenced Message, to reply to.

		MessageData& operator=(const MessageData& other);

		MessageData(const MessageData& other);

		MessageData() noexcept = default;

		MessageData(simdjson::ondemand::value jsonObjectData);

		virtual ~MessageData() noexcept = default;
	};

	/// Resolved data. \brief Resolved data.
	struct DiscordCoreAPI_Dll ResolvedData {
		std::unordered_map<uint64_t, AttachmentData> attachments{};///< std::map of Snowflakes to attachment objects the ids and attachment objects.
		std::unordered_map<uint64_t, GuildMemberData> members{};///< std::map full of GuildMemeberData.
		std::unordered_map<uint64_t, MessageData> messages{};///< std::map full of messageData->
		std::unordered_map<uint64_t, ChannelData> channels{};///< std::map full of ChannelData.
		std::unordered_map<uint64_t, UserData> users{};///< std::map full of UserData.
		std::unordered_map<uint64_t, RoleData> roles{};///< std::map full of RoleData.

		ResolvedData() noexcept = default;

		ResolvedData(simdjson::ondemand::value jsonObjectData);
	};

	/// Represents a Sticker pack. \brief Represents a Sticker pack.
	struct DiscordCoreAPI_Dll StickerPackData {
		std::vector<StickerData> stickers{};///< Array of Sticker objects	the stickers in the pack.
		std::string coverStickerId{};///< Id of a Sticker in the pack which is shown as the pack's icon.
		std::string bannerAssetId{};///< Id of the Sticker pack's banner image.
		std::string description{};///< Description of the Sticker pack.
		std::string skuId{};///< Id of the pack's SKU.
		Snowflake Id{};///< Id of the Sticker pack.
		std::string name{};///< Name of the Sticker pack.

		StickerPackData() noexcept = default;

		StickerPackData(simdjson::ondemand::value jsonObjectData);

		virtual ~StickerPackData() noexcept = default;
	};

	class DiscordCoreAPI_Dll StickerPackDataVector {
	  public:
		StickerPackDataVector() noexcept = default;

		operator std::vector<StickerPackData>();

		StickerPackDataVector(simdjson::ondemand::value jsonObjectData);

		virtual ~StickerPackDataVector() noexcept = default;

	  protected:
		std::vector<StickerPackData> theStickerPackDatas{};
	};

	/// Connection visibility types. \brief Connection visibility types.
	enum class ConnectionVisibilityTypes : uint8_t {
		None = 0,///< None.
		Everyone = 1///< Everyone.
	};

	/// Represents a single User Connection. \brief Represents a single User Connection.
	struct DiscordCoreAPI_Dll ConnectionData {
		std::vector<IntegrationData> integrations{};///< An array of partial server integrations.
		ConnectionVisibilityTypes visibility{};///< Visibility of this connection.
		bool showActivity{ false };///< Whether activities related to this connection will be shown in presence updates.
		bool friendSync{ false };///< Whether friend sync is enabled for this connection.
		bool verified{ false };///< Whether the connection is verified.
		bool revoked{ false };///< Whether the connection is revoked.
		Snowflake id{};///< Id of the connection account.
		std::string name{};///< The userName of the connection account.
		std::string type{};///< The service of the connection(twitch, youtube).

		ConnectionData() noexcept = default;

		ConnectionData(simdjson::ondemand::value jsonObjectData);

		virtual ~ConnectionData() noexcept = default;
	};

	class DiscordCoreAPI_Dll ConnectionDataVector {
	  public:
		ConnectionDataVector() noexcept = default;

		ConnectionDataVector(simdjson::ondemand::value jsonObjectData) noexcept;

		operator std::vector<ConnectionData>();

		virtual ~ConnectionDataVector() noexcept = default;

	  protected:
		std::vector<ConnectionData> connectionDatas{};
	};

	/// ApplicationCommand Interaction data option. \brief ApplicationCommand Interaction data option.
	struct DiscordCoreAPI_Dll ApplicationCommandInteractionDataOption {
		std::vector<ApplicationCommandInteractionDataOption> options{};///< ApplicationCommand Interaction data options.
		ApplicationCommandOptionType type{};///< The type of ApplicationCommand options.
		JsonStringValue value{};///< The value if it's an int32_t.
		bool focused{ false };///< 	True if this option is the currently focused option for autocomplete.
		std::string name{};///< The name of the current option.

		ApplicationCommandInteractionDataOption() noexcept = default;

		ApplicationCommandInteractionDataOption(simdjson::ondemand::value jsonObjectData);

		virtual ~ApplicationCommandInteractionDataOption() noexcept = default;
	};

	/// ApplicationCommand Interaction data. \brief ApplicationCommand Interaction data.
	class DiscordCoreAPI_Dll ApplicationCommandInteractionData : public DiscordEntity {
	  public:
		std::vector<ApplicationCommandInteractionDataOption> options{};///< ApplicationCommand Interaction data options.
		ApplicationCommandType type{};///< The type of ApplicationCommand.
		ResolvedData resolved{};///< Resolved data.
		Snowflake guildId{};///< The guild that the command took place in.
		std::string name{};///< The name of the command.

		ApplicationCommandInteractionData() noexcept = default;

		ApplicationCommandInteractionData(simdjson::ondemand::value jsonObjectData);

		virtual ~ApplicationCommandInteractionData() noexcept = default;
	};

	/// Interaction data data. \brief Interaction data data.
	struct DiscordCoreAPI_Dll InteractionDataData {
		ApplicationCommandInteractionData applicationCommandData{};///< ApplicationCommand Interaction data.
		MessageCommandInteractionData messageInteractionData{};///< Message command Interaction data.
		UserCommandInteractionData userInteractionData{};///< User command Interaction data.
		ComponentInteractionData componentData{};///< Component Interaction data.
		ModalInteractionData modalData{};///< Modal Interaction data.

		InteractionDataData() noexcept = default;

		InteractionDataData(simdjson::ondemand::value jsonObjectData);

		virtual ~InteractionDataData() noexcept = default;
	};

	/// Interaction data. \brief Interaction data.
	class DiscordCoreAPI_Dll InteractionData : public DiscordEntity {
	  public:
		Permissions appPermissions{};///< Bitwise set of permissions the app or bot has within the channel the interaction was sent from.
		InteractionDataData data{};///< The Interaction's data.
		Snowflake applicationId{};///< The application's id.
		GuildMemberData member{};///< The data of the Guild member who sent the Interaction, if applicable.
		InteractionType type{};///< The type of Interaction.
		MessageData message{};///< The Message that the Interaction came through on, if applicable.
		Snowflake channelId{};///< The Channel the Interaction was sent in.
		std::string guildLocale{};///< The guild's preferred locale, if invoked in a guild.
		Snowflake guildId{};///< The Guild id of the Guild it was sent in.
		int32_t version{ 0 };///< The Interaction version.
		UserData user{};///< The User data of the sender of the Interaction.
		std::string locale{};///< The selected language of the invoking user.
		std::string token{};///< The Interaction token.

		InteractionData() noexcept = default;

		InteractionData(simdjson::ondemand::value jsonObjectData);

		virtual ~InteractionData() noexcept = default;
	};

	/// Data from the SessionStart info. \brief Data from the SessionStart info.
	struct DiscordCoreAPI_Dll SessionStartData {
		uint32_t maxConcurrency{ 0 };///< The number of identify requests allowed per 5 seconds.
		uint32_t resetAfter{ 0 };///< The number of std::chrono::milliseconds after which the limit resets.
		uint32_t remaining{ 0 };///< The remaining number of session starts the current User is allowed.
		uint32_t total{ 0 };///< The total number of session starts the current User is allowed.

		SessionStartData() noexcept = default;

		SessionStartData(simdjson::ondemand::value jsonObjectData);

		virtual ~SessionStartData() noexcept = default;
	};

	/// Data from the GetGatewayBot endpoint. \brief Data from the GetGatewayBot endpoint.
	struct DiscordCoreAPI_Dll GatewayBotData {
		SessionStartData sessionStartLimit{};///< Information on the current session start limit.
		uint32_t shards{ 0 };///< The recommended number of shards to use when connecting.
		std::string url{};///< The WSS Url that can be used for connecting to the gateway.

		GatewayBotData() noexcept = default;

		GatewayBotData(simdjson::ondemand::value jsonObjectData);

		virtual ~GatewayBotData() noexcept = default;
	};

	/// Text input style for modals. \brief Text input style for modals.
	enum class TextInputStyle : uint8_t {
		Short = 1,///< A single-line input.
		Paragraph = 2///< A multi-line input.
	};

	/// Data representing a Guild Emoji Update event. \brief Data representing a Guild Emoji Update event.
	struct DiscordCoreAPI_Dll GuildEmojisUpdateEventData {
		std::vector<EmojiData> emojis{};
		Snowflake guildId{};

		GuildEmojisUpdateEventData() noexcept = default;

		GuildEmojisUpdateEventData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildEmojisUpdateEventData() noexcept = default;
	};

	/// Data representing a Guild Sticker Update event. \brief Data representing a Guild Stickers Update event.
	struct DiscordCoreAPI_Dll GuildStickersUpdateEventData {
		std::vector<StickerData> stickers{};
		Snowflake guildId{};

		GuildStickersUpdateEventData() noexcept = default;

		GuildStickersUpdateEventData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildStickersUpdateEventData() noexcept = default;
	};

	struct DiscordCoreAPI_Dll GuildMembersChunkEventData {
		std::vector<PresenceUpdateData> presences{};
		std::vector<GuildMemberData> members{};
		std::vector<std::string> notFound{};
		int32_t chunkIndex{ 0 };
		int32_t chunkCount{ 0 };
		Snowflake guildId{};
		std::string nonce{};

		GuildMembersChunkEventData() noexcept = default;

		GuildMembersChunkEventData(simdjson::ondemand::value jsonObjectData);

		virtual ~GuildMembersChunkEventData() noexcept = default;
	};

	/// Data representing an input-event, which is any Message or Interaction that is coming into the bot as an input. \brief Data representing an input-event, which is any Message or Interaction that is coming into the bot as an input.
	class DiscordCoreAPI_Dll InputEventData {
	  public:
		friend struct OnInteractionCreationData;
		friend struct BaseFunctionArguments;

		friend class DiscordCoreInternal::WebSocketSSLShard;
		friend class DiscordCoreInternal::BaseSocketAgent;
		friend class RespondToInputEventData;
		friend class DiscordCoreClient;
		friend class CommandData;
		friend class InputEvents;

		InputEventResponseType responseType{};///< The type of response that this input value represents.

		InputEventData& operator=(InputEventData&& other) noexcept;

		InputEventData(InputEventData&& other) noexcept;

		InputEventData& operator=(const InputEventData& other) noexcept;

		InputEventData(const InputEventData& other) noexcept;

		InputEventData& operator=(const InteractionData& other) noexcept;

		InputEventData(const InteractionData& interactionData) noexcept;

		InputEventData() noexcept = default;

		/// Returns the userName of the last User to trigger this input-event. \brief Returns the userName of the last User to trigger this input-event.
		/// \returns std::string A string containing the User name.
		std::string getUserName() const;

		/// Gets the avatar Url of the last User to trigger this input-event. \brief Gets the avatar Url of the last User to trigger this input-event.
		/// \returns std::string A string containing the avatar Url.
		std::string getAvatarUrl() const;

		/// Returns the Message embeds that are on the Message, if applicable. \brief Returns the Message embeds that are on the Message, if applicable.
		/// \returns std::vector A vector containing the EmbedData.
		std::vector<EmbedData> getEmbeds() const;

		/// Returns the Message components that are on the Message, if applicable. \brief Returns the Message components that are on the Message, if applicable.
		/// \returns std::vector A vector containing ActionRowData.
		std::vector<ActionRowData> getComponents() const;

		/// Returns the User id of the last requester of this input-event. \brief Returns the User id of the last requester of this input-event.
		/// \returns Snowflake A Snowflake containing the author's id.
		Snowflake getAuthorId() const;

		/// Returns the Interaction id, if appplicable, of this input-event. \brief Returns the Interaction id, if appplicable, of this input-event.
		/// \returns Snowflake A Snowflake containing the Interaction id.
		Snowflake getInteractionId() const;

		/// Returns the application id. \brief Returns the application id.
		/// \returns Snowflake A Snowflake containing the application id.
		Snowflake getApplicationId() const;

		/// Returns the Channel id of this input-event. \brief Returns the Channel id of this input-event.
		/// \returns Snowflake A Snowflake containing the Channel id.
		Snowflake getChannelId() const;

		/// Returns the Interaction token, if applicable, of this input-event. \brief Returns the Interaction token, if applicable, of this input-event.
		/// \returns std::string A string containing the Interaction token.
		std::string getInteractionToken() const;

		/// Returns the Guild id, of this input-event. \brief Returns the Guild id, of this input-event.
		/// \returns Snowflake A Snowflake containing the Guild id.
		Snowflake getGuildId() const;

		/// Returns the Message id, if applicable, of this input-event. \brief Returns the Message id, if applicable, of this input-event.
		/// \returns Snowflake A Snowflake containing the Message id.
		Snowflake getMessageId() const;

		/// Returns the Interaction data, if applicable, of this input-event. \brief Returns the InteractionData, if applicable, of this input-event.
		/// \returns InteractionData An InteractionData structure.
		InteractionData getInteractionData() const;

		/// Returns the Message data, if applicable, of this input-event. \brief Returns the Message data, if applicable, of this input-event.
		/// \returns MessageData A MessageData structure.
		MessageData getMessageData() const;

		virtual ~InputEventData() noexcept = default;

	  protected:
		std::unique_ptr<InteractionData> interactionData{ std::make_unique<InteractionData>() };
	};

	/// \brief Data for responding to an input-event.
	class DiscordCoreAPI_Dll RespondToInputEventData {
	  public:
		friend struct DeleteInteractionResponseData;
		friend struct DeleteFollowUpMessageData;
		friend struct InteractionResponseData;

		friend class CreateEphemeralInteractionResponseData;
		friend class CreateDeferredInteractionResponseData;
		friend class CreateEphemeralFollowUpMessageData;
		friend class CreateInteractionResponseData;
		friend class EditInteractionResponseData;
		friend class CreateFollowUpMessageData;
		friend class EditFollowUpMessageData;
		friend class CreateMessageData;
		friend class EditMessageData;
		friend class InputEvents;
		friend class SendDMData;

		RespondToInputEventData& operator=(const InteractionData& dataPackage);

		RespondToInputEventData(const InteractionData& dataPackage);

		RespondToInputEventData& operator=(const InputEventData& dataPackage);

		RespondToInputEventData(const InputEventData& dataPackage);

		/// Adds a button to the response Message. \brief Adds a button to the response Message.
		/// \param disabled Whether the button is active or not.
		/// \param customIdNew A custom id to give for identifying the button.
		/// \param buttonLabel A visible label for the button.
		/// \param buttonStyle The style of the button.
		/// \param emojiName An emoji name, if desired.
		/// \param emojiId An emoji id, if desired.
		/// \param url A url, if applicable.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& addButton(bool disabled, const std::string& customIdNew, const std::string& buttonLabel, ButtonStyle buttonStyle, const std::string& emojiName = "",
			Snowflake emojiId = Snowflake{ 0 }, const std::string& url = "");

		/// Adds a select-menu to the response Message. \brief Adds a select-menu to the response Message.
		/// \param disabled Whether the select-menu is active or not.
		/// \param customIdNew A custom id to give for identifying the select-menu.
		/// \param options A vector of select-menu-options to offer.
		/// \param placeholder Custom placeholder text if nothing is selected, max 100 characters.
		/// \param maxValues Maximum number of selections that are possible.
		/// \param minValues Minimum required number of selections that are required.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& addSelectMenu(bool disabled, const std::string& customIdNew, std::vector<SelectOptionData> options, const std::string& placeholder, int32_t maxValues,
			int32_t minValues);

		/// Adds a modal to the response Message. \brief Adds a modal to the response Message.
		/// \param topTitleNew A title for the modal.
		/// \param topCustomIdNew A custom id to give for the modal.
		/// \param titleNew A title for the modal's individual input.
		/// \param customIdNew A custom id to give for the modal's individual input.
		/// \param required Is it a required response?
		/// \param minLength Minimum length.
		/// \param maxLength Maximum length.
		/// \param inputStyle The input style.
		/// \param label A label for the modal.
		/// \param placeholder A placeholder for the modal.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& addModal(const std::string& topTitleNew, const std::string& topCustomIdNew, const std::string& titleNew, const std::string& customIdNew, bool required,
			int32_t minLength, int32_t maxLength, TextInputStyle inputStyle, const std::string& label = "", const std::string& placeholder = "");

		/// Adds a file to the current collection of files for this message response. \brief Adds a file to the current collection of files for this message response.
		/// \param theFile The file to be added.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& addFile(File theFile);

		/// For setting the allowable mentions in a response. \brief For setting the allowable mentions in a response.
		/// \param dataPackage An AllowedMentionsData structure.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& addAllowedMentions(AllowedMentionsData dataPackage);

		/// For setting the type of response to make. \brief For setting the type of response to make.
		/// \param typeNew An InputEventResponseType.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& setResponseType(InputEventResponseType typeNew);

		/// For setting the components in a response. \brief For setting the components in a response.
		/// \param dataPackage An ActionRowData structure.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& addComponentRow(ActionRowData dataPackage);

		/// For setting the embeds in a response. \brief For setting the embeds in a response.
		/// \param dataPackage An EmbedData structure.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& addMessageEmbed(EmbedData dataPackage);

		/// For setting the Message content in a response. \brief For setting the Message content in a response.
		/// \param dataPackage A string, containing the content.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& addContent(const std::string& dataPackage);

		/// For setting the tts status of a response. \brief For setting the tts status of a response.
		/// \param enabledTTs A bool.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& setTTSStatus(bool enabledTTs);

		/// For setting the choices of an autocomplete response. \brief For setting the choices of an autocomplete response.
		/// \param value An simdjson::ondemand::object value that is either a float, int32_t or a string.
		/// \param theName A string for the name of the choice.
		/// \param theNameLocalizations A std::unordered_map<std::string, std::string> for the name localizations.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& setAutoCompleteChoice(Jsonifier value, const std::string& theName, std::unordered_map<std::string, std::string> theNameLocalizations);

		/// For setting the direct-Message User target of a response. \brief For setting the direct-Message User target of a response.
		/// \param targetUserIdNew A string, containing the target User's id.
		/// \returns RespondToInputEventData& A reference to this data structure.
		RespondToInputEventData& setTargetUserID(const Snowflake targetUserIdNew);

	  protected:
		std::vector<ApplicationCommandOptionChoiceData> choices{};
		AllowedMentionsData allowedMentions{};
		std::vector<ActionRowData> components{};
		InputEventResponseType type{};///< The type of response to make.
		InteractionType eventType{};
		std::vector<EmbedData> embeds{};
		Snowflake interactionId{};
		Snowflake applicationId{};
		std::string interactionToken{};
		Snowflake targetUserId{};
		Snowflake channelId{};
		Snowflake messageId{};
		std::vector<File> files{};
		bool tts{ false };
		std::string customId{};
		std::string content{};
		int32_t flags{ 0 };
		std::string title{};
	};

	/// Message response base, for responding to messages. \brief Message response base, for responding to messages.
	class DiscordCoreAPI_Dll MessageResponseBase {
	  public:
		/// Adds a button to the response Message. \brief Adds a button to the response Message.
		/// \param disabled Whether the button is active or not.
		/// \param customIdNew A custom id to give for identifying the button.
		/// \param buttonLabel A visible label for the button.
		/// \param buttonStyle The style of the button.
		/// \param emojiName An emoji name, if desired.
		/// \param emojiId An emoji id, if desired.
		/// \param url A url, if applicable.
		/// \returns MessageResponseBase& A reference to this data structure.
		MessageResponseBase& addButton(bool disabled, const std::string& customIdNew, const std::string& buttonLabel, ButtonStyle buttonStyle, const std::string& emojiName = "",
			Snowflake emojiId = Snowflake{ 0 }, const std::string& url = "");

		/// Adds a select-menu to the response Message. \brief Adds a select-menu to the response Message.
		/// \param disabled Whether the select-menu is active or not.
		/// \param customIdNew A custom id to give for identifying the select-menu.
		/// \param options A vector of select-menu-options to offer.
		/// \param placeholder Custom placeholder text if nothing is selected, max 100 characters.
		/// \param maxValues Maximum number of selections that are possible.
		/// \param minValues Minimum required number of selections that are required.
		/// \returns MessageResponseBase& A reference to this data structure.
		MessageResponseBase& addSelectMenu(bool disabled, const std::string& customIdNew, std::vector<SelectOptionData> options, const std::string& placeholder, int32_t maxValues, int32_t minValues);

		/// Adds a modal to the response Message. \brief Adds a modal to the response Message.
		/// \param topTitleNew A title for the modal.
		/// \param topCustomIdNew A custom id to give for the modal.
		/// \param titleNew A title for the modal's individual input.
		/// \param customIdNew A custom id to give for the modal's individual input.
		/// \param required Is it a required response?
		/// \param minLength Minimum length.
		/// \param maxLength Maximum length.
		/// \param inputStyle The input style.
		/// \param label A label for the modal.
		/// \param placeholder A placeholder for the modal.
		/// \returns MessageResponseBase& A reference to this data structure.
		MessageResponseBase& addModal(const std::string& topTitleNew, const std::string& topCustomIdNew, const std::string& titleNew, const std::string& customIdNew, bool required, int32_t minLength,
			int32_t maxLength, TextInputStyle inputStyle, const std::string& label = "", const std::string& placeholder = "");

		/// Adds a file to the current collection of files for this message response. \brief Adds a file to the current collection of files for this message response.
		/// \param theFile The file to be added.
		/// \returns MessageResponseBase& A reference to this data structure.
		MessageResponseBase& addFile(File theFile);

		/// For setting the allowable mentions in a response. \brief For setting the allowable mentions in a response.
		/// \param dataPackage An AllowedMentionsData structure.
		/// \returns MessageResponseBase& A reference to this data structure.
		MessageResponseBase& addAllowedMentions(AllowedMentionsData dataPackage);

		/// For setting the components in a response. \brief For setting the components in a response.
		/// \param dataPackage An ActionRowData structure.
		/// \returns MessageResponseBase& A reference to this data structure.
		MessageResponseBase& addComponentRow(ActionRowData dataPackage);

		/// For setting the embeds in a response. \brief For setting the embeds in a response.
		/// \param dataPackage An EmbedData structure.
		/// \returns MessageResponseBase& A reference to this data structure.
		MessageResponseBase& addMessageEmbed(EmbedData dataPackage);

		/// For setting the Message content in a response. \brief For setting the Message content in a response.
		/// \param dataPackage A string, containing the content.
		/// \returns MessageResponseBase& A reference to this data structure.
		MessageResponseBase& addContent(const std::string& dataPackage);

		/// For setting the tts status of a response. \brief For setting the tts status of a response.
		/// \param enabledTTs A bool.
		/// \returns MessageResponseBase& A reference to this data structure.
		MessageResponseBase& setTTSStatus(bool enabledTTs);

	  protected:
		AllowedMentionsData allowedMentions{};
		std::vector<ActionRowData> components{};
		std::vector<EmbedData> embeds{};
		std::vector<File> files{};
		bool tts{ false };
		std::string customId{};
		std::string content{};
		int32_t flags{ 0 };
		std::string title{};
	};

	/// Interaction response data. \brief Interaction response data.
	struct DiscordCoreAPI_Dll InteractionResponseData {
		InteractionCallbackData data{};///< Interaction ApplicationCommand callback data.
		InteractionCallbackType type{};///< Interaction callback type.

		InteractionResponseData& operator=(const RespondToInputEventData& other);

		InteractionResponseData(const RespondToInputEventData& other);

		InteractionResponseData() noexcept = default;

		operator Jsonifier();
	};

	/// Guild application command permissions data. \brief Guild application command permissions data.
	class DiscordCoreAPI_Dll GuildApplicationCommandPermissionData : public DiscordEntity {
	  public:
		std::vector<ApplicationCommandPermissionData> permissions{};
		Snowflake applicationId{};
		Snowflake guildId{};

		virtual ~GuildApplicationCommandPermissionData() noexcept = default;
	};

	/**@}*/

	/// Song types. \brief Song types.
	enum class SongType : uint8_t {
		YouTube = 0,///< YouTube.
		SoundCloud = 1///< SoundCloud.
	};

	/// Represents a download Url. \brief Represents a download Url.
	struct DiscordCoreAPI_Dll DownloadUrl {
		int32_t contentSize{ 0 };
		std::string urlPath{};
	};

	/**
	 * \addtogroup voice_connection
	 * @{
	 */

	struct DiscordCoreAPI_Dll MediaTranscoding {
		std::string thePreset{};
		std::string theUrl{};

		MediaTranscoding() noexcept = default;
		MediaTranscoding(simdjson::ondemand::value);
	};

	/// A song from the various platforms. \brief A song from the various platforms.
	class DiscordCoreAPI_Dll Song {
	  public:
		friend class DiscordCoreInternal::SoundCloudRequestBuilder;
		friend class DiscordCoreInternal::YouTubeRequestBuilder;
		friend class DiscordCoreInternal::SoundCloudAPI;
		friend class DiscordCoreInternal::YouTubeAPI;
		friend class SongAPI;

		std::vector<DownloadUrl> finalDownloadUrls{};
		SongType type{ SongType::SoundCloud };///< The type of song.
		std::string secondDownloadUrl{};
		Snowflake addedByUserId{};///< The User id of the individual who added this Song to the playlist.
		std::string firstDownloadUrl{};
		uint64_t contentLength{ 0 };
		std::string html5PlayerFile{};
		std::string addedByUserName{};///< The User name of the individual who added this Song to the playlist.
		std::string thumbnailUrl{};///< The Url of the thumbnail image of this Song.
		std::string html5Player{};
		std::string description{};///< A description of the Song.
		std::string songTitle{};///< The title of the Song.
		std::string duration{};///< The duration of the Song.
		std::string viewUrl{};///< The url for listening to this Song through a browser.
		std::string songId{};

		Song() noexcept = default;

		Song(simdjson::ondemand::value jsonObjectData);

		virtual ~Song() noexcept = default;

	  protected:
		std::string trackAuthorization{};
		bool doWeGetSaved{ false };
		YouTubeFormat format{};
	};

	/// Song completion event data. \brief Song completion event data.
	struct DiscordCoreAPI_Dll SongCompletionEventData {
		GuildMemberData guildMember{};///< The sending GuildMember.
		bool wasItAFail{ false };///< Is this a replay? (Did a track recently fail to play?)
		Song previousSong{};///< The previously played Song.
		GuildData guild{};///< The sending Guild.
	};

	/// Playlist of songs and other variables. \brief Playlist of songs and other variables.
	struct DiscordCoreAPI_Dll Playlist {
		bool isLoopSongEnabled{ false };///< Is looping of Songs currently enabled?
		bool isLoopAllEnabled{ false };///< Is looping of the entire Playlist currently enabled?
		std::vector<Song> songQueue{};///< The list of Songs that are stored to be played.
		Song currentSong{};///< The current Song that is playing.
	};

	/**@}*/

	/**
	 * \addtogroup utilities
	 * @{
	 */

	struct DiscordCoreAPI_Dll JsonifierValue {
		std::unordered_map<std::string, JsonStringValue> values{};
	};

	/// Command data, for functions executed by the CommandController. \brief Command data, for functions executed by the CommandController.
	class DiscordCoreAPI_Dll CommandData {
	  public:
		JsonifierValue optionsArgs{};
		std::string subCommandGroupName{};
		InputEventData eventData{};
		std::string subCommandName{};
		std::string commandName{};

		CommandData() noexcept = default;

		CommandData& operator=(CommandData&&) noexcept = default;

		CommandData(CommandData&&) noexcept = default;

		CommandData& operator=(const CommandData&) noexcept = default;

		CommandData(const CommandData&) noexcept = default;

		CommandData(InputEventData inputEventData);

		CommandData(simdjson::ondemand::value jsonObjectData);

		virtual ~CommandData() noexcept = default;
	};

	/// Base arguments for the command classes. \brief Base arguments for the command classes.
	struct DiscordCoreAPI_Dll BaseFunctionArguments : public CommandData {
		DiscordCoreClient* discordCoreClient{ nullptr };///< A pointer to the instance of DiscordCoreClient.

		BaseFunctionArguments() noexcept = default;

		BaseFunctionArguments(CommandData commandData, DiscordCoreClient* discordCoreClientNew);

		virtual ~BaseFunctionArguments() noexcept = default;
	};

	/// Base class for the command classes. \brief Base class for the command classes.
	struct DiscordCoreAPI_Dll BaseFunction {
		std::string helpDescription{};///< Description of the command for the Help command.
		EmbedData helpEmbed{};///< A Message embed for displaying the command via the Help command.
		std::string commandName{};///< Name of the command for calling purposes.

		BaseFunction() noexcept = default;

		/// The base function for the command's execute function. \brief The base function for the command's execute function.
		/// \param args A reference to an instance of BaseFunctionArguments.
		virtual void execute(BaseFunctionArguments& args) = 0;
		virtual std::unique_ptr<BaseFunction> create() = 0;
		virtual ~BaseFunction() noexcept = default;
	};

	struct DiscordCoreAPI_Dll MoveThroughMessagePagesData {
		InputEventData inputEventData{};
		uint32_t currentPageIndex{};
		std::string buttonId{};
	};

	DiscordCoreAPI_Dll MoveThroughMessagePagesData moveThroughMessagePages(const std::string& userID, InputEventData originalEvent, uint32_t currentPageIndex,
		const std::vector<EmbedData>& messageEmbeds, bool deleteAfter, uint32_t waitForMaxMs, bool returnResult = false);

	/**@}*/

};// namespace DiscordCoreAPI

namespace DiscordCoreInternal {

	struct DiscordCoreAPI_Dll ReadyData {
		DiscordCoreAPI::ApplicationData application{};
		DiscordCoreAPI::UserData user{};
		std::string resumeGatewayUrl{};
		std::string sessionId{};
		uint32_t shard[2]{};
		int32_t v{};

		ReadyData(simdjson::ondemand::value);
		ReadyData() noexcept = default;
	};
}

template<> struct DiscordCoreAPI_Dll std::hash<DiscordCoreAPI::DiscordEntity> {
	uint64_t operator()(DiscordCoreAPI::DiscordEntity const& object) const noexcept {
		return static_cast<DiscordCoreAPI::Snowflake>(object.id).operator size_t();
	}
};

template<> struct DiscordCoreAPI_Dll std::hash<DiscordCoreAPI::ChannelData> {
	uint64_t operator()(DiscordCoreAPI::ChannelData const& object) const noexcept {
		return static_cast<DiscordCoreAPI::Snowflake>(object.id).operator size_t();
	}
};

template<> struct DiscordCoreAPI_Dll std::hash<DiscordCoreAPI::GuildData> {
	uint64_t operator()(DiscordCoreAPI::GuildData const& object) const noexcept {
		return static_cast<DiscordCoreAPI::Snowflake>(object.id).operator size_t();
	}
};

template<> struct DiscordCoreAPI_Dll std::hash<DiscordCoreAPI::RoleData> {
	uint64_t operator()(DiscordCoreAPI::RoleData const& object) const noexcept {
		return static_cast<DiscordCoreAPI::Snowflake>(object.id).operator size_t();
	}
};

template<> struct DiscordCoreAPI_Dll std::hash<DiscordCoreAPI::UserData> {
	uint64_t operator()(DiscordCoreAPI::UserData const& object) const noexcept {
		return static_cast<DiscordCoreAPI::Snowflake>(object.id).operator size_t();
	}
};

template<> struct DiscordCoreAPI_Dll std::hash<DiscordCoreAPI::GuildMemberData> {
	uint64_t operator()(DiscordCoreAPI::GuildMemberData const& object) const noexcept {
		return static_cast<DiscordCoreAPI::Snowflake>(object.guildId).operator size_t() ^ (static_cast<DiscordCoreAPI::Snowflake>(object.id).operator size_t() << 1);
	}
};

#endif