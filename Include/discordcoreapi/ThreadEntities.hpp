/*
	MIT License

	DiscordCoreAPI, A bot library for Discord, written in C++, and featuring explicit multithreading through the usage of custom, asynchronous C++ CoRoutines.

	Copyright 2022, 2023 Chris M. (RealTimeChris)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
/// ThreadEntities.hpp - Header file for the thread-related stuff.
/// Nov 29, 2021
/// https://discordcoreapi.com
/// \file ThreadEntities.hpp

#pragma once

#include <discordcoreapi/FoundationEntities.hpp>
#include <discordcoreapi/CoRoutine.hpp>
#include <discordcoreapi/ChannelEntities.hpp>

namespace DiscordCoreAPI {

	/**
	 * \addtogroup foundation_entities
	 * @{
	 */

	/// \brief For starting a Thread, based on a Message.
	struct DiscordCoreAPI_Dll StartThreadWithMessageData {
		ThreadAutoArchiveDuration autoArchiveDuration{ ThreadAutoArchiveDuration::Shortest };///< The duration before it is auto-archived, in minutes.
		int32_t rateLimitPerUser{};///< Integer amount of seconds a user has to wait before sending another message(0 - 21600).
		std::string threadName{};///< The name of the new Thread.
		Snowflake messageId{};///< The Message Snowflake to base the Thread off of.
		Snowflake channelId{};///< The Channel to start the Thread in.
		std::string reason{};///< Reason for starting the Thread.
	};

	/// \brief For starting a Thread, not based on a Message.
	struct DiscordCoreAPI_Dll StartThreadWithoutMessageData {
		ThreadAutoArchiveDuration autoArchiveDuration{ ThreadAutoArchiveDuration::Shortest };///< The duration before it is auto-archived, in minutes.
		ThreadType type{ ThreadType::Guild_Public_Thread };///< Type of Thread to create.
		int32_t rateLimitPerUser{};///< Integer amount of seconds a user has to wait before sending another message(0 - 21600).
		std::string threadName{};///< The name of the new Thread.
		Snowflake channelId{};///< The Channel to start the Thread in.
		std::string reason{};///< Reason for starting the Thread.
		bool invitable{};///< Whether non-moderators can add other non - moderators to a thread; only available when creating a protected thread.
	};

	/// \brief For starting a Thread, in a forum channel.
	struct DiscordCoreAPI_Dll StartThreadInForumChannelData {
		ThreadAutoArchiveDuration autoArchiveDuration{ ThreadAutoArchiveDuration::Longest };/// Duration in minutes to automatically archive.
		ForumThreadMessageData message{};///< A forum thread message params object contents of the first message in the forum thread.
		int32_t rateLimitPerUser{};///< Integer amount of seconds a user has to wait before sending another message(0 - 21600).
		Snowflake channelId{};///< The id of the channel.
		std::string reason{};///< Reason for starting the Thread.
		std::string name{};///< 1-100 character channel name auto_archive_duration.
	};

	/// \brief For joining a Thread.
	struct DiscordCoreAPI_Dll JoinThreadData {
		Snowflake channelId{};///< The id of the Thread to join.
	};

	/// \brief For adding a chosen User to a chosen Thread.
	struct DiscordCoreAPI_Dll AddThreadMemberData {
		Snowflake channelId{};///< The id of the Thread to join.
		Snowflake userId{};///< The id of the User to add to the Thread.
	};

	/// \brief For leaving a Thread.
	struct DiscordCoreAPI_Dll LeaveThreadData {
		Snowflake channelId{};///< The id of the Thread to leave.
	};

	/// \brief For removing a chosen User from a Thread.
	struct DiscordCoreAPI_Dll RemoveThreadMemberData {
		Snowflake channelId{};///< The id of the Thread to remove them from.
		Snowflake userId{};///< The id of the User to remove from the Thread.
	};

	/// \brief For collecting a ThreadMember responseData structure for a given ThreadMember.
	struct DiscordCoreAPI_Dll GetThreadMemberData {
		Snowflake channelId{};///< The id of the Thread to collect them from.
		Snowflake userId{};///< The id of the User to collect from the Thread.
	};

	/// \brief For collecting the list of ThreadMembers from a Thread.
	struct DiscordCoreAPI_Dll GetThreadMembersData {
		Snowflake channelId{};///< The id of the Thread to collect them from.
	};

	/// \brief For collecting the list of active Threads.
	struct DiscordCoreAPI_Dll GetActiveThreadsData {
		Snowflake channelId{};///< The id of the Channel to collect the Threads from.
	};

	/// \brief For collecting puiblic archived Threads from a given Channel.
	struct DiscordCoreAPI_Dll GetPublicArchivedThreadsData {
		Snowflake channelId{};///< The Channel to acquire the Threads from.
		std::string before{};///< Returns threads before this timeStamp.
		int32_t limit{};///< Maximum number of threads to return.
	};

	/// \brief For collecting protected archived Threads from a given Channel.
	struct DiscordCoreAPI_Dll GetPrivateArchivedThreadsData {
		Snowflake channelId{};///< The Channel to acquire the Threads from.
		std::string before{};///< Returns threads before this timeStamp.
		int32_t limit{};///< Maximum number of threads to return.
	};

	/// \brief For collecting joined protected archived Threads from a given Channel.
	struct DiscordCoreAPI_Dll GetJoinedPrivateArchivedThreadsData {
		Snowflake channelId{};///< The Channel to acquire the Threads from.
		std::string before{};///< Returns threads before this timeStamp.
		int32_t limit{};///< Maximum number of threads to return.
	};

	/// \brief For listing the active Threads in a chosen Guild.
	struct DiscordCoreAPI_Dll GetActiveGuildThreadsData {
		Snowflake guildId{};///< The Guild from which to list the Threads from.
	};

	/**@}*/

	/**
	 * \addtogroup main_endpoints
	 * @{
	 */
	/// \brief An interface class for the Thread related endpoints.
	class DiscordCoreAPI_Dll Threads {
	  public:
		static void initialize(DiscordCoreInternal::HttpsClient*);

		/// \brief Starts a Thread, based on a starting Message.
		/// \param dataPackage A StartThreadWithMessageData structure.
		/// \returns A CoRoutine containing a Channel.
		static CoRoutine<Thread> startThreadWithMessageAsync(StartThreadWithMessageData dataPackage);

		/// \brief Starts a Thread, not based on a starting Message.
		/// \param dataPackage A StartThreadWithoutMessageData structure.
		/// \returns A CoRoutine containing a Channel.
		static CoRoutine<Thread> startThreadWithoutMessageAsync(StartThreadWithoutMessageData dataPackage);

		/// \brief Starts a Thread, in a forum channel.
		/// \param dataPackage A StartThreadInForumChannelData structure.
		/// \returns A CoRoutine containing a Channel.
		static CoRoutine<Thread> startThreadInForumChannelAsync(StartThreadInForumChannelData dataPackage);

		/// \brief Joins a Thread.
		/// \param dataPackage A JoinThreadData structure.
		/// \returns A CoRoutine containing void.
		static CoRoutine<void> joinThreadAsync(JoinThreadData dataPackage);

		/// \brief Adds a new User to a chosen Thread.
		/// \param dataPackage An AddThreadMemberData structure.
		/// \returns A CoRoutine containing void.
		static CoRoutine<void> addThreadMemberAsync(AddThreadMemberData dataPackage);

		/// \brief Leaves a Thread.
		/// \param dataPackage A LeaveThreadData  structure.
		/// \returns A CoRoutine containing void.
		static CoRoutine<void> leaveThreadAsync(LeaveThreadData dataPackage);

		/// \brief Removes a User from a chosen Thread.
		/// \param dataPackage A RemoveThreadMemberData  structure.
		/// \returns A CoRoutine containing void.
		static CoRoutine<void> removeThreadMemberAsync(RemoveThreadMemberData dataPackage);

		/// \brief Collects a ThreadMember if they exist.
		/// \param dataPackage A GetThreadMemberData structure.
		/// \returns A CoRoutine containing a ThreadMemberData.
		static CoRoutine<ThreadMemberData> getThreadMemberAsync(GetThreadMemberData dataPackage);

		/// \brief Collects a list of ThreadMembers if they exist.
		/// \param dataPackage A GetThreadMembersData structure.
		/// returns A CoRoutine containing a vector<ThreadMemberData>.
		static CoRoutine<ThreadMemberDataVector> getThreadMembersAsync(GetThreadMembersData dataPackage);

		/// \brief Collects a list of Threads from a given Channel.
		/// \param dataPackage A GetActiveThreadsData structure.
		/// \returns A CoRoutine containing a ActiveThreadsData.
		static CoRoutine<ActiveThreadsData> getActiveThreadsAsync(GetActiveThreadsData dataPackage);

		/// \brief Collects a list of public archived Threads from a given Channel.
		/// \param dataPackage A GetPublicArchivedThreadsData structure.
		/// \returns A CoRoutine containing a ArchivedThreadsData.
		static CoRoutine<ArchivedThreadsData> getPublicArchivedThreadsAsync(GetPublicArchivedThreadsData dataPackage);

		/// \brief Collects a list of protected archived Threads from a given Channel.
		/// \param dataPackage A GetPrivateArchivedThreadsData structure.
		/// \returns A CoRoutine containing a ArchivedThreadsData.
		static CoRoutine<ArchivedThreadsData> getPrivateArchivedThreadsAsync(GetPrivateArchivedThreadsData dataPackage);

		/// \brief Collects a list of joined protected archived Threads from a given Channel.
		/// \param dataPackage A GetPrivateArchivedThreadsData structure.
		/// \returns A CoRoutine containing a ArchivedThreadsData.
		static CoRoutine<ArchivedThreadsData> getJoinedPrivateArchivedThreadsAsync(GetJoinedPrivateArchivedThreadsData dataPackage);

		/// \brief Lists all of the active Threads of a chosen Guild.
		/// \param dataPackage A ListActiveThreadsData structure.
		/// \returns A CoRoutine containing a vector<Channel>.
		static CoRoutine<ActiveThreadsData> getActiveGuildThreadsAsync(GetActiveGuildThreadsData dataPackage);

	  protected:
		static DiscordCoreInternal::HttpsClient* httpsClient;
	};
	/**@}*/
};
