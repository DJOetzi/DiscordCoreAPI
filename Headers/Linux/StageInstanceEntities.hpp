// StageInstanceEntities.hpp - Source file for the Stage Instance related stuff.
// Nov 29, 2021
// Chris M.
// https://github.com/RealTimeChris

#ifndef STAGE_INSTANCE_ENTITIES
#define STAGE_INSTANCE_ENTITIES

#include "FoundationEntities.hpp"

namespace DiscordCoreAPI {

	/// For creating a StageInstance. \brief For creating a StageInstance.
	struct CreateStageInstanceData {
		StageInstancePrivacyLevel privacyLevel{};///< The privacy level of the Stage instance(default Guild_Only).
		std::string channelId{ "" };///< The id of the Stage channel.
		std::string reason{ "" };///< The reason for starting it.
		std::string topic{ "" };///< The topic of the Stage instance(1 - 120 characters).
	};
	
	/// For collecting a single StageInstance. \brief For collecting a single StageInstance.
	struct GetStageInstanceData {
		std::string channelId{ "" };///< The channel id from which you would like to collect the StageInstance.
	};

	/// For modifying a single StageInstance. \brief For modifying a single StageInstance.
	struct ModifyStageInstanceData {
		StageInstancePrivacyLevel privacyLevel{};///< The privacy level of the Stage instance.
		std::string channelId{ "" };///< The channel Id of the StageInstance.
		std::string reason{ "" };///< Reason for modifying the StageInstance.
		std::string topic{ "" };///< The topic of the Stage instance(1 - 120 characters).
	};

	/// For deleting a single StageInstance. \brief For deleting a single StageInstance.
	struct DeleteStageInstanceData {
		std::string channelId{ "" };///< The channel Id of the StageInstance.
		std::string reason{ "" };///< Reason for deleting the StageInstance.
	};

	/// A single StageInstance. \brief A single StageInstance.
	class StageInstance : public StageInstanceData {
	public:

		StageInstance();

		StageInstance(StageInstanceData dataNew);

	};
	
	/**
	* \addtogroup main_endpoints
	* @{
	*/
	/// An interface class for the StageInstance related Discord endpoints. \brief An interface class for the StageInstance related Discord endpoints.
	class StageInstances {
	public:

		static void initialize(DiscordCoreInternal::HttpClient*);

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

	protected:

		static DiscordCoreInternal::HttpClient* httpClient;
	};

	/**@}*/
}
#endif