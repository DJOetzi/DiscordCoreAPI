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
/// ApplicationCommandEntities.hpp - Header for the ApplicationCommand classes
/// and structs. Aug 25, 2021 Chris M.
/// https://discordcoreapi.com
/// \file ApplicationCommandEntities.hpp

#pragma once

#include <discordcoreapi/FoundationEntities.hpp>
#include <discordcoreapi/Https.hpp>

namespace DiscordCoreAPI {

	/**
	 * \addtogroup foundation_entities
	 * @{
	*/

	/// \brief For getting all of the Global Application Commands.
	struct DiscordCoreAPI_Dll GetGlobalApplicationCommandsData {
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		bool withLocalizations{};///< Do we collect the name-and-description localizations?
	};

	/// \brief For collecting a single global ApplicationCommand.
	struct DiscordCoreAPI_Dll GetGlobalApplicationCommandData {
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		std::string commandId{};///< The id of the command which you would like to collect.
	};

	/// \brief For creating an application command.
	struct DiscordCoreAPI_Dll CreateApplicationCommandData : public ApplicationCommandData {
		friend class DiscordCoreClient;

	  protected:
		bool alwaysRegister{};
	};

	/// \brief For creating a single global ApplicationCommand.
	struct DiscordCoreAPI_Dll CreateGlobalApplicationCommandData : public CreateApplicationCommandData {};

	/// \brief For editing a single global ApplicationCommand.
	struct DiscordCoreAPI_Dll EditGlobalApplicationCommandData {
		std::unordered_map<std::string, std::string>
			descriptionLocalizations{};///< Dictionary with keys in available locales Localization dictionary for the description field.
		std::unordered_map<std::string, std::string>
			nameLocalizations{};///< Dictionary with keys in available locales Localization dictionary for the name field.
		std::vector<ApplicationCommandOptionData> options{};///< The options for the ApplicationCommand.
		Permissions defaultMemberPermissions{};///< Set of permissions represented as a bit set. only for globally - scoped commands.
		std::string description{};///< A description of the command.
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		bool dmPermission{};///< Indicates whether the command is available in DMs with the app.
		std::string name{};///< A name for the new command.
	};

	/// \brief For deleting a single global ApplicationCommand.
	struct DiscordCoreAPI_Dll DeleteGlobalApplicationCommandData {
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		std::string name{};///< The name of the command to delete.
	};

	/// \brief For bulk-overwriting a collection of global ApplicationCommands.
	struct DiscordCoreAPI_Dll BulkOverwriteGlobalApplicationCommandsData {
		std::vector<CreateGlobalApplicationCommandData> responseData{};///< A vector of the options for the ApplicationCommands.
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
	};

	/// \brief For acquiring all of the Guild ApplicationCommands of a single Guild.
	struct DiscordCoreAPI_Dll GetGuildApplicationCommandsData {
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		bool withLocalizations{};///< Do we collect the name-and-description localizations?
		Snowflake guildId{};///< The id of the Guild for which you would like to acquire the ApplicationCommands from.
	};

	/// \brief For creating a single Guild ApplicationCommand.
	struct DiscordCoreAPI_Dll CreateGuildApplicationCommandData : public CreateGlobalApplicationCommandData {};

	/// \brief For acquiring a single Guild ApplicationCommand.
	struct DiscordCoreAPI_Dll GetGuildApplicationCommandData {
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		uint64_t commandId{};///< The command id which you would like to acquire.
		Snowflake guildId{};///< The id of the Guild from which you would like to acquire the ApplicationCommand from.
	};

	/// \brief For editing a single Guild ApplicationCommand.
	struct DiscordCoreAPI_Dll EditGuildApplicationCommandData {
		std::unordered_map<std::string, std::string> descriptionLocalizations{};///< Dictionary with keys in available locales.
		std::unordered_map<std::string, std::string> nameLocalizations{};///< Dictionary with keys in available locales.
		std::vector<ApplicationCommandOptionData> options{};///< The options for the ApplicationCommand.
		Permissions defaultMemberPermissions{};///< Set of permissions represented as a bit set. only for globally - scoped commands.
		std::string description{};///< A description of the command.
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		bool dmPermission{};///< Indicates whether the command is available in DMs with the app.
		Snowflake guildId{};///< The id of the Guild which you would like to add the new command to.
		std::string name{};///< A name for the new command.
	};

	/// \brief For deleting a single Guild ApplicationCommand.
	struct DiscordCoreAPI_Dll DeleteGuildApplicationCommandData {
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		Snowflake guildId{};///< The id of the Guild which you would like to delete the command from.
		std::string name{};///< A name of the command which you would like to delete.
	};

	/// \brief For bulk-overwriting a collection of Guild ApplicationCommands.
	struct DiscordCoreAPI_Dll BulkOverwriteGuildApplicationCommandsData {
		std::vector<CreateGuildApplicationCommandData> responseData{};///< A vector of the options for the ApplicationCommands.
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		Snowflake guildId{};///< The id of the Guild which you would like to overwrite the commands of.
	};

	/// \brief For acquiring the permissions of a collection of Guild ApplicationCommands.
	struct DiscordCoreAPI_Dll GetGuildApplicationCommandPermissionsData {
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		Snowflake guildId{};///< The id of the Guild from which you would like to acquire the command permissions.
	};

	/// \brief For acquiring the permissions of a single Guild ApplicationCommand.
	struct DiscordCoreAPI_Dll GetApplicationCommandPermissionsData {
		std::string commandName{};///< The name of the command which you would like to collect the permissions of.
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		Snowflake guildId{};///< The id of the Guild from which you would like to acquire the command permissions.
	};

	/// \brief For editing the permissions of a single Guild ApplicationCommand.
	struct DiscordCoreAPI_Dll EditGuildApplicationCommandPermissionsData {
		std::vector<ApplicationCommandPermissionData> permissions{};///< A vector of ApplicationCommand permissions.
		std::string commandName{};///< The command name which you would like to edit the permissions of.
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		uint64_t commandId{};///< The command id which you would like to edit the permissions of.
		Snowflake guildId{};///< The Guild id of the Guild for which you would like to edit the command permissions.
	};

	/// \brief For batch editing the permissions of a collection of Guild ApplicationCommands.
	struct DiscordCoreAPI_Dll BatchEditGuildApplicationCommandPermissionsData {
		std::vector<GuildApplicationCommandPermissionsData> permissions{};///< A vector of edit-Guild-application-permissions responseData to edit.
		Snowflake applicationId{};///< The current application's Snowflake (The Bot's User Snowflake).
		Snowflake guildId{};///< The Guild id of the Guild for which you would like to batch edit Guild application permissions.
	};

	/**@}*/

	/**
	 * \addtogroup main_endpoints
	 * @{
	 */
	/// \brief An interface class for the ApplicationCommand related Discord endpoints.
	class DiscordCoreAPI_Dll ApplicationCommands {
	  public:
		static void initialize(DiscordCoreInternal::HttpsClient*);

		/// \brief Get all of the global ApplicationCommands for this bot.
		/// \returns A CoRoutine containing a vector<ApplicationCommand>.
		static CoRoutine<std::vector<ApplicationCommand>> getGlobalApplicationCommandsAsync(GetGlobalApplicationCommandsData dataPackage);

		/// \brief Create a global ApplicationCommand for this bot.
		/// \param dataPackage A CreateGlobalApplicationCommandData structure.
		/// \returns A CoRoutine containing an ApplicationCommand.
		static CoRoutine<ApplicationCommand> createGlobalApplicationCommandAsync(CreateGlobalApplicationCommandData dataPackage);

		/// \brief Get a single global ApplicationCommand for this bot.
		/// \param dataPackage A GetGlobalApplicationCommandData structure.
		/// \returns A CoRoutine containing an ApplicationCommand.
		static CoRoutine<ApplicationCommand> getGlobalApplicationCommandAsync(GetGlobalApplicationCommandData dataPackage);

		/// \brief Edit a global ApplicationCommand for this bot.
		/// \param dataPackage An EditGlobalApplicationCommandData structure.
		/// \returns A CoRoutine containing an ApplicationCommand.
		static CoRoutine<ApplicationCommand> editGlobalApplicationCommandAsync(EditGlobalApplicationCommandData dataPackage);

		/// \brief Delete a global ApplicationCommand for this bot.
		/// \param dataPackage A DeleteGlobalApplicationCommandData structure.
		/// \returns A CoRoutine containing void.
		static CoRoutine<void> deleteGlobalApplicationCommandAsync(DeleteGlobalApplicationCommandData dataPackage);

		/// \brief Bulk overwrites a collection of global ApplicationCommands.
		/// \param dataPackage A BulkOverwriteGlobalApplicationCommandsData structure.
		/// \returns A CoRoutine containing a vector<ApplicationCommand>.
		static CoRoutine<std::vector<ApplicationCommand>> bulkOverwriteGlobalApplicationCommandsAsync(
			BulkOverwriteGlobalApplicationCommandsData dataPackage);

		/// \brief Get all of the Guild ApplicationCommands for a single Guild for this bot.
		/// \param dataPackage A GetGuildApplicationCommandsData structure.
		/// \returns A CoRoutine containing a vector<ApplicationCommand>.
		static CoRoutine<std::vector<ApplicationCommand>> getGuildApplicationCommandsAsync(GetGuildApplicationCommandsData dataPackage);

		/// \brief Create a Guild ApplicationCommand for a single server for this bot.
		/// \param dataPackage A CreateGuildApplicationCommandData structure.
		/// \returns A CoRoutine containing an ApplicationCommand.
		static CoRoutine<ApplicationCommand> createGuildApplicationCommandAsync(CreateGuildApplicationCommandData dataPackage);

		/// \brief Get a single Guild ApplicationCommand for a single server for this bot.
		/// \param dataPackage A GetGuildApplicationCommandData structure.
		/// \returns A CoRoutine containing an ApplicationCommand.
		static CoRoutine<ApplicationCommand> getGuildApplicationCommandAsync(GetGuildApplicationCommandData dataPackage);

		/// \brief Edit a single Guild ApplicationCommand for a single server for this bot.
		/// \param dataPackage An EditGuildApplicationCommandData structure.
		/// \returns A CoRoutine containing an ApplicationCommand.
		static CoRoutine<ApplicationCommand> editGuildApplicationCommandAsync(EditGuildApplicationCommandData dataPackage);

		/// \brief Delete a single Guild ApplicationCommand for a single server for this bot.
		/// \param dataPackage A DeleteGuildApplicationCommandData structure.
		/// \returns A CoRoutine containing void.
		static CoRoutine<void> deleteGuildApplicationCommandAsync(DeleteGuildApplicationCommandData dataPackage);

		/// \brief Bulkoverwrites some Guild ApplicationCommands for this bot.
		/// \param dataPackage A BulkOverwriteGuildApplicationCommandsData structure.
		/// \returns A CoRoutine containing a vector<ApplicationCommand>.
		static CoRoutine<std::vector<ApplicationCommand>> bulkOverwriteGuildApplicationCommandsAsync(
			BulkOverwriteGuildApplicationCommandsData dataPackage);

		/// \brief Gets Guild ApplicationCommand permissions for a single server on this bot.
		/// \param dataPackage A GetGuildApplicationCommandPermissionsData structure.
		/// \returns A CoRoutine containing a vector<GuildApplicationCommandPermissionsData>.
		static CoRoutine<std::vector<GuildApplicationCommandPermissionsData>> getGuildApplicationCommandPermissionsAsync(
			GetGuildApplicationCommandPermissionsData dataPackage);

		/// \brief Get ApplicationCommand permissions for a single command on this bot.
		/// \param dataPackage A GetApplicationCommandPermissionsData structure.
		/// \returns A CoRoutine containing a GuildApplicationCommandPermissionsData.
		static CoRoutine<GuildApplicationCommandPermissionsData> getApplicationCommandPermissionsAsync(
			GetApplicationCommandPermissionsData dataPackage);

		/// \brief Edit Guild ApplicationCommand permissions for a server on this bot.
		/// \param dataPackage An EditGuildApplicationCommandPermissionsData structure.
		/// \returns A CoRoutine containing a GuildApplicationCommandPermissionsData.
		static CoRoutine<GuildApplicationCommandPermissionsData> editGuildApplicationCommandPermissionsAsync(
			EditGuildApplicationCommandPermissionsData dataPackage);

	  protected:
		static DiscordCoreInternal::HttpsClient* httpsClient;
	};

	/**@}*/

}
