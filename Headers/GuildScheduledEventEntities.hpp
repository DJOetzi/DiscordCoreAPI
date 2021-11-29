// GuildScheduledEventEntities.hpp - Header for the Guild Scheduled Events stuff.
// Nov 27, 2021
// Chris M.
// https://github.com/RealTimeChris

#pragma once

#include "IndexInitial.hpp"
#include "FoundationEntities.hpp"
#include "CoRoutine.hpp"
#include "Http.hpp"

namespace DiscordCoreAPI {

	/**
	* \addtogroup foundation_entities
	* @{
	*/
	/// For collecting a list of a Guild's scheduled events. \brief For collecting a list of a Guild's scheduled events.
	struct DiscordCoreAPI_Dll GetGuildScheduledEventsData {
		bool withUserCount{ false };///< Do we collect the user counts?
		string guildId{ "" };///< Guild from which we would like to collect the events.
	};

	/// For creating a GuildScheduledEvent. \brief For creating a GuildScheduledEvent.
	struct DiscordCoreAPI_Dll CreateGuildScheduledEventData {
		GuildScheduledEventPrivacyLevel	privacyLevel{ GuildScheduledEventPrivacyLevel::GUILD_ONLY};///< The privacy level of the scheduled event.
		GuildScheduledEventMetadata entityMetadata{};/// The entity metadata of the scheduled event.
		GuildScheduledEventEntityType	entityType{};///< The entity type of the scheduled event.
		string scheduledStartTime{ "" };///< The time to schedule the scheduled event.
		string scheduledEndTime{ "" };///< The time when the scheduled event is scheduled to end.
		string description{ "" };///< The description of the scheduled event.
		string channelId{ "" };///< The channel id of the scheduled event.
		string guildId{ "" };///< The guild within which to create the event.
		string name{ "" };///< The name of the scheduled event.
	};
	
	/// For collecting a single Guild scheduled event. \brief For collecting a single Guild scheduled event.
	struct DiscordCoreAPI_Dll GetGuildScheduledEventData {
		string guildScheduledEventId{ "" };///< The id of the desired scheduled event.
		bool withUserCount{ false };///< Do we collect the user counts?
		string guildId{ "" };///< Guild from which we would like to collect the events.
	};

	/// For modifying a single Guild Scheduled Event. \brief For modifying a single Guild Scheduled Event.
	struct DiscordCoreAPI_Dll ModifyGuildScheduledEventData {
		GuildScheduledEventPrivacyLevel	privacyLevel{ GuildScheduledEventPrivacyLevel::GUILD_ONLY };///< The privacy level of the scheduled event.
		GuildScheduledEventStatus status{ GuildScheduledEventStatus::ACTIVE };///< The status of the scheduled event.
		GuildScheduledEventMetadata entityMetadata{};///< The entity metadata of the scheduled event.
		GuildScheduledEventEntityType entityType{};///< The entity type of the scheduled event.
		string guildScheduledEventId{ "" };///< The id of the event to modify.
		string scheduledStartTime{ "" };///< The time to schedule the scheduled event.
		string scheduledEndTime{ "" };///< The time when the scheduled event is scheduled to end.
		string description{ "" };///< The description of the scheduled event.
		string channelId{ "" };///< The channel id of the scheduled event, set to null if changing entity type to EXTERNAL.
		string guildId{ "" };///< The Guild within which to modify the event.
		string name{ "" };///< The name of the scheduled event.
	};

	/// For deleting a single Guild Scheduled Event. \brief For deleting a single Guild Scheduled Event.
	struct DiscordCoreAPI_Dll DeleteGuildScheduledEventData {
		string guildScheduledEventId{ "" };///< The id of the event to modify.
		string guildId{ "" };///< The Guild within which to modify the event.
	};

	/// For collecting a list of Guild Scheduled Event Users. \brief For collecting a list of Guild Scheduled Event Users.
	struct DiscordCoreAPI_Dll GetGuildScheduledEventUsersData {
		string guildScheduledEventId{ "" };///< The id of the event to modify.
		bool withMember{ false };///< Include guild member data if it exists.
		string guildId{ "" };///< The Guild within which to modify the event.
		uint32_t limit{ 0 };///< How many users to receive from the event.
		string before{ "" };///< Consider only users before given user id.
		string after{ "" };///< Consider only users after given user id.
	};

	/// A single GuildScheduledEvent data structure. \brief A single GuildScheduledEvent data structure.
	class DiscordCoreAPI_Dll GuildScheduledEvent : public GuildScheduledEventData {
	public:

		friend class DiscordCoreInternal::HttpRequestAgent;
		template<typename returnValueType>
		friend class CoRoutine;
		friend class GuildScheduledEvents;

		GuildScheduledEvent();

		virtual ~GuildScheduledEvent() {};

	protected:

		GuildScheduledEvent(GuildScheduledEventData dataPackage);
	};

	/**@}*/

	/**
	* \addtogroup discord_core_client
	* @{
	*/
	/// An interface class DiscordCoreAPI_Dll for the GuildScheduledEvent related Discord endpoints. \brief An interface class DiscordCoreAPI_Dll for the GuildScheduledEvent related Discord endpoints.
	class DiscordCoreAPI_Dll GuildScheduledEvents {
	public:

		/// Gets a list of a given Guild's scheduled events. \brief Gets a list of a given Guild's scheduled events.
		/// \param dataPackage A GetGuildScheduledEventData structure.
		/// \returns A CoRoutine containing vector<GuildScheduledEvent>.
		static CoRoutine<vector<GuildScheduledEvent>> getGuildScheduledEventsAsync(GetGuildScheduledEventsData dataPackage);

		/// Creates a new GuildScheduledEvent within a chosen Guild. \brief Creates a new GuildScheduledEvent within a chosen Guild.
		/// \param dataPackage A CreateGuildScheduledEventData structure.
		/// \returns A CoRoutine containing GuildScheduledEvent.
		static CoRoutine<GuildScheduledEvent> createGuildScheduledEventAsync(CreateGuildScheduledEventData dataPackage);

		/// Collects a single GuildScheduledEvent. \brief Collects a single GuildScheduledEvent.
		/// \param dataPackage A GetGuildScheduledEventData structure.
		/// \returns A CoRoutine containing GuildScheduledEvent.
		static CoRoutine<GuildScheduledEvent> getGuildScheduledEventAsync(GetGuildScheduledEventData dataPackage);

		/// Modifies a single GuildScheduledEvent. \brief Modifies a single GuildScheduledEvent.
		/// \param dataPackage A ModifyGuildScheduledEventData structure.
		/// \returns A CoRoutine containing GuildScheduledEvent.
		static CoRoutine<GuildScheduledEvent> modifyGuildScheduledEventAsync(ModifyGuildScheduledEventData dataPackage);

		/// Deletes a single GuildScheduledEvent. \brief Deletes a single GuildScheduledEvent.
		/// \param dataPackage A DeleteGuildScheduledEventData structure.
		/// \returns A CoRoutine containing void.
		static CoRoutine<void> deleteGuildScheduledEventAsync(DeleteGuildScheduledEventData dataPackage);
		

		/// Collects a list of Users for a given GuildScheduledEvent. \brief Collects a list of Users for a given GuildScheduledEvent.
		/// \param dataPackage A GetGuildScheduledEventUsersData structure.
		/// \returns A CoRoutine containing vector<GuildScheduledEventUser>.
		static CoRoutine<vector<GuildScheduledEventUserData>> getGuildScheduledEventUsersAsync(GetGuildScheduledEventUsersData dataPackage);
	};
	/**@}*/
}
