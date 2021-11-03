// ChannelEntities.hpp - Header for the classes related classes and structs.
// May 13, 2021
// Chris M.
// https://github.com/RealTimeChris

#pragma once

#include "IndexInitial.hpp"
#include "FoundationEntities.hpp"

namespace DiscordCoreAPI {

	/**
	* \addtogroup foundation_entities
	* @{
	*/
	/// For editing the Permission overwrites of a given Channel, for a given role or User. \brief For editing the Permission overwrites of a given Channel, for a given role or User.
	struct DiscordCoreAPI_Dll EditChannelPermissionOverwritesData {
		EditChannelPermissionOverwritesType type{}; ///< The type of overwrite.
		string roleOrUserId{ "" };	///< The role or User Id to modify the permissions for.
		string channelId{ "" };	///< The Channel id of the desired Channel to modify the permissions for.
		string allow{ "" };	///< The permissions to list as "allowed".
		string deny{ "" };	///< The permissions to list as "deny".
	};

	/// For collecting a Channel from Discord's servers. \brief For collecting a Channel from Discord's servers.
	struct DiscordCoreAPI_Dll GetChannelData {
		string channelId{ "" }; ///< The id of the Channel to acquire.
	};

	/// For deleting or closing a Channel. \brief For deleting or closing a Channel.
	struct DiscordCoreAPI_Dll DeleteChannelData {
		string channelId{ "" };
		string reason{ "" };
	};

	/// For modifying a channel's properties. \brief For modifying a channel's properties.
	struct DiscordCoreAPI_Dll ModifyChannelData {
		ModifyChannelData(ChannelData newData) {
			this->channelData.permissionOverwrites = newData.permissionOverwrites;
			this->channelData.rateLimitPerUser = newData.rateLimitPerUser;
			this->channelData.userLimit = newData.userLimit;
			this->channelData.rtcRgion = newData.rtcRegion;
			this->channelData.parentId = newData.parentId;
			this->channelData.position = newData.position;
			this->channelData.topic = newData.topic;
			this->channelData.name = newData.name;
			this->channelData.nsfw = newData.nsfw;
			this->channelData.type = newData.type;
		};
		UpdateChannelData channelData{};///< The data of the channel to be updated.
		string channelId{ "" };///< The id of the Channel to modify.
	};

	/// For deleting the Permission overwrites of a given Channel for a given role or User. \brief For deleting the Permission overwrites of a given Channel for a given role or User.
	struct DiscordCoreAPI_Dll DeleteChannelPermissionOverwritesData {
		string roleOrUserId{ "" }; ///< The role or User id for whom to delete the Permission overwrites.
		string channelId{ "" }; ///< The id of the Channel to modify permissions for..
	};

	/// For collecting a direct-messaging Channel. \brief For collecting a direct-messaging Channel.
	struct DiscordCoreAPI_Dll GetDMChannelData {
		string userId{ "" }; ///< The User for whom to collect the direct-messaging Channel to.
	};

	/// A Channel object. \brief A Channel object.
	class DiscordCoreAPI_Dll Channel : public ChannelData {
	protected:

		friend struct Concurrency::details::_ResultHolder<Channel>;
		friend class DiscordCoreInternal::ChannelManager;
		template<typename returnValueType>
		friend class DiscordCoreAPI::CoRoutine;
		friend struct OnChannelDeletionData;
		friend struct OnChannelCreationData;
		friend struct OnThreadCreationData;
		friend struct OnThreadDeletionData;
		friend struct OnChannelUpdateData;
		friend struct OnThreadUpdateData;
		friend class DiscordCoreClient;
		friend class Guild;

		Channel();

		Channel(ChannelData dataNew);
	};
	/**@}*/
};

namespace DiscordCoreInternal {

	class DiscordCoreAPI_Dll ChannelManager {
	public:

		friend class DiscordCoreAPI::DiscordCoreClient;
		friend class DiscordCoreAPI::Channels;
		friend class DiscordCoreAPI::Guild;

	protected:

		overwrite_buffer<map<string, DiscordCoreAPI::Channel>> cache{};

		DiscordCoreAPI::CoRoutine<DiscordCoreAPI::Channel> getCachedChannelAsync(DiscordCoreAPI::GetChannelData dataPackage);

		DiscordCoreAPI::CoRoutine<DiscordCoreAPI::Channel> getChannelAsync(DiscordCoreAPI::GetChannelData dataPackage);

		DiscordCoreAPI::CoRoutine<DiscordCoreAPI::Channel> modifyChannelAsync(DiscordCoreAPI::ModifyChannelData dataPackage);

		DiscordCoreAPI::CoRoutine<void>  deleteOrCloseChannelAsync(DiscordCoreAPI::DeleteChannelData dataPackage);

		DiscordCoreAPI::CoRoutine<DiscordCoreAPI::Channel> getDMChannelAsync(DiscordCoreAPI::GetDMChannelData dataPackage);

		DiscordCoreAPI::CoRoutine<void> editChannelPermissionOverwritesAsync(DiscordCoreAPI::EditChannelPermissionOverwritesData dataPackage);

		DiscordCoreAPI::CoRoutine<void> deleteChannelPermissionOverwritesAsync(DiscordCoreAPI::DeleteChannelPermissionOverwritesData dataPackage);

		void insertChannel(DiscordCoreAPI::Channel channel);

		void removeChannel(string channelId);
	};
}
