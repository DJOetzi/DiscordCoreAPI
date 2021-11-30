// StageInstanceEntities.hpp - Source file for the Stage Instance related stuff.
// Nov 29, 2021
// Chris M.
// https://github.com/RealTimeChris

#pragma once

#include "IndexInitial.hpp"
#include "FoundationEntities.hpp"

namespace DiscordCoreAPI {

	/// For creating a StageInstance. \brief For creating a StageInstance.
	struct DiscordCoreAPI_Dll CreateStageInstanceData {
		StageInstancePrivacyLevel privacyLevel{};///< The privacy level of the Stage instance(default GUILD_ONLY).
		string channelId{ "" };///< The id of the Stage channel.
		string reason{ "" };///< The reason for starting it.
		string topic{ "" };///< The topic of the Stage instance(1 - 120 characters).
	};
	
	/// For collecting a single StageInstance. \brief For collecting a single StageInstance.
	struct DiscordCoreAPI_Dll GetStageInstanceData {
		string channelId{ "" };///< The channel id from which you would like to collect the StageInstance.
	};

	/// For modifying a single StageInstance. \brief For modifying a single StageInstance.
	struct DiscordCoreAPI_Dll ModifyStageInstanceData {
		StageInstancePrivacyLevel privacyLevel{};///< The privacy level of the Stage instance.
		string channelId{ "" };///< The channel Id of the StageInstance.
		string reason{ "" };///< Reason for modifying the StageInstance.
		string topic{ "" };///< The topic of the Stage instance(1 - 120 characters).
	};

	/// For deleting a single StageInstance. \brief For deleting a single StageInstance.
	struct DeleteStageInstanceData {
		string channelId{ "" };///< The channel Id of the StageInstance.
		string reason{ "" };///< Reason for deleting the StageInstance.
	};

	/// A single StageInstance. \brief A single StageInstance.
	class DiscordCoreAPI_Dll StageInstance : public StageInstanceData {
	public:

		friend class DiscordCoreInternal::HttpRequestAgent;
		friend class DiscordCoreInternal::DataParser;
		template<typename returnValueType>
		friend class CoRoutine;
		friend class DiscordCoreClient;
		friend class StageInstances;
		friend class Guild;

		StageInstance();

		virtual ~StageInstance() {};

	protected:

		StageInstance(StageInstanceData dataNew);

	};
	
	/**
	* \addtogroup discord_core_client
	* @{
	*/
	/// An interface class for the StageInstance related Discord endpoints. \brief An interface class for the StageInstance related Discord endpoints.
	class DiscordCoreAPI_Dll StageInstances {
	public:

		/// Creates a StageInstance. \brief Creates a StageInstance.
		/// \param dataPackage A CreateStageInstanceData structure.
		/// \returns A CoRoutine containing a StageInstance.
		static CoRoutine<StageInstance> createStageInstanceAsync(CreateStageInstanceData dataPackage);

		/// Collects a StageInstance. \brief Collects a StageInstance.
		/// \param dataPackage A GetStageInstanceData structure.
		/// \returns A CoRoutine containing a StageInstance.
		static CoRoutine<StageInstance> getStageInstanceAsync(GetStageInstanceData dataPackage);

		/// Modifies a StageInstance. \brief Modifies a StageInstance.
		/// \param dataPackage A ModifyStageInstanceData structure.
		/// \returns A CoRoutine containing a StageInstance.
		static CoRoutine<StageInstance> modifyStageInstanceAsync(ModifyStageInstanceData dataPackage);
		
		/// Deletes a StageInstance. \brief Deletes a StageInstance.
		/// \param dataPackage A DeleteStageInstanceData structure.
		/// \returns A CoRoutine containing void.
		static CoRoutine<void> deleteStageInstanceAsync(DeleteStageInstanceData dataPackage);

	};

	/**@}*/
}