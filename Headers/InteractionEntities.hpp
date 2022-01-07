// InteractionEntities.hpp - Header for the interaction related classes and structs.
// May 28, 2021
// Chris M.
// https://github.com/RealTimeChris

#pragma once

#include "IndexInitial.hpp"
#include "FoundationEntities.hpp"
#include "JSONIFier.hpp"
#include "MessageEntities.hpp"

namespace DiscordCoreAPI {
    /**
    * \addtogroup foundation_entities
    * @{
    */

    class DiscordCoreAPI_Dll InteractionResponse {
    public:

        /// Adds a button to the response Message. \brief Adds a button to the response Message.
        /// \param disabled Whether the button is active or not.
        /// \param customId A custom id to give for identifying the button.
        /// \param buttonLabel A visible label for the button.
        /// \param buttonStyle The style of the button.
        /// \param emojiName An emoji name, if desired.        
        /// \param emojiId An emoji id, if desired.
        /// \param url A url, if applicable.
        /// \returns void
        void addButton(bool disabled, string customId, string buttonLabel, DiscordCoreAPI::ButtonStyle buttonStyle, string emojiName = "", string emojiId = "", string url = "") {
            if (this->data.data.components.size() == 0) {
                ActionRowData actionRowData;
                this->data.data.components.push_back(actionRowData);
            }
            if (this->data.data.components.size() < 5) {
                if (this->data.data.components.at(this->data.data.components.size() - 1).components.size() < 5) {
                    ComponentData component;
                    component.type = ComponentType::Button;
                    component.emoji.name = emojiName;
                    component.label = buttonLabel;
                    component.style = buttonStyle;
                    component.customId = customId;
                    component.disabled = disabled;
                    component.emoji.id = emojiId;
                    component.url = url;
                    this->data.data.components.at(this->data.data.components.size() - 1).components.push_back(component);
                }
                else if (this->data.data.components.at(this->data.data.components.size() - 1).components.size() == 5) {
                    ActionRowData actionRowData;
                    this->data.data.components.push_back(actionRowData);
                }
            }
        }

        /// Adds a select-menu to the response Message. \brief Adds a select-menu to the response Message.
        /// \param disabled Whether the select-menu is active or not.
        /// \param customId A custom id to give for identifying the select-menu.
        /// \param options A vector of select-menu-options to offer.
        /// \param placeholder Custom placeholder text if nothing is selected, max 100 characters.
        /// \param maxValues Maximum number of selections that are possible.
        /// \param minValues Minimum required number of selections that are required.
        /// \returns void
        void addSelectMenu(bool disabled, string customId, vector<SelectOptionData> options, string placeholder, int32_t maxValues, int32_t minValues) {
            if (this->data.data.components.size() == 0) {
                ActionRowData actionRowData;
                this->data.data.components.push_back(actionRowData);
            }
            if (this->data.data.components.size() < 5) {
                if (this->data.data.components.at(this->data.data.components.size() - 1).components.size() < 5) {
                    ComponentData componentData;
                    componentData.type = ComponentType::SelectMenu;
                    componentData.placeholder = placeholder;
                    componentData.maxValues = maxValues;
                    componentData.minValues = minValues;
                    componentData.disabled = disabled;
                    componentData.customId = customId;
                    componentData.options = options;
                    this->data.data.components.at(this->data.data.components.size() - 1).components.push_back(componentData);
                }
                else if (this->data.data.components.at(this->data.data.components.size() - 1).components.size() == 5) {
                    ActionRowData actionRowData;
                    this->data.data.components.push_back(actionRowData);
                }

            }
        }

        /// For setting the allowable mentions in a response. \brief For setting the allowable mentions in a response.
        /// \param dataPackage An AllowedMentionsData structure.
        /// \returns void
        void addAllowedMentions(AllowedMentionsData dataPackage) {
            this->data.data.allowedMentions = dataPackage;
        }

        /// For setting the components in a response. \brief For setting the components in a response. 
        /// \param dataPackage An ActionRowData structure.
        /// \returns void
        void addComponentRow(ActionRowData dataPackage) {
            this->data.data.components.push_back(dataPackage);
        }

        /// Sets the response type of the current Message. \brief Sets the response type of the current Message.
        /// \param type Interaction callback type.
        /// \returns void
        void setResponseType(InteractionCallbackType type) {
            this->data.type = type;
        }

        /// For setting the embeds in a response. \brief For setting the embeds in a response.
        /// \param dataPackage An EmbedData structure.
        /// \returns void
        void addMessageEmbed(EmbedData dataPackage) {
            this->data.data.embeds.push_back(dataPackage);
        }

        /// For setting the Message content in a response. \brief For setting the Message content in a response.
        /// \param dataPackage A string, containing the content.
        /// \returns void
        void addContent(string dataPackage) {
            this->data.data.content = dataPackage;
        }

        /// For setting the tts status of a response. \brief For setting the tts status of a response.
        /// \param enabledTTs A bool.
        /// \returns void
        void setTTSStatus(bool enabledTTs) {
            this->data.data.tts = enabledTTs;
        }

        virtual ~InteractionResponse() {};

    protected:

        InteractionPackageData interactionPackage{};
        MessagePackageData messagePackage{};
        InteractionResponseData data{};
        string requesterId{ "" };
    };

    /// For deferring a component response. \brief For deferring a component response.
    class DiscordCoreAPI_Dll DeferComponentResponseData : public InteractionResponse {
    public:

        friend class  CreateInteractionResponseData;
        friend class  InputEvents;

        DeferComponentResponseData(RespondToInputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.interactionToken;
            this->responseType = InputEventResponseType::DeferredResponse;
            this->interactionPackage.applicationId = dataPackage.applicationId;
            this->interactionPackage.interactionId = dataPackage.interactionId;
            this->type = InteractionCallbackType::DeferredUpdateMessage;
        }

        DeferComponentResponseData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->responseType = InputEventResponseType::DeferredResponse;
            this->type = InteractionCallbackType::DeferredUpdateMessage;
        }

        virtual ~DeferComponentResponseData() {};

    protected:

        InputEventResponseType responseType{};
        InteractionCallbackType type{};

    };

    /// For creating an ephemeral Interaction response. \brief For creating an ephemeral Interaction response.
    class DiscordCoreAPI_Dll CreateEphemeralInteractionResponseData : public InteractionResponse {
    public:

        friend class  CreateInteractionResponseData;
        friend class  Interactions;
        friend class  InputEvents;

        CreateEphemeralInteractionResponseData(RespondToInputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.interactionToken;
            this->data.type = InteractionCallbackType::ChannelMessageWithSource;
            this->interactionPackage.applicationId = dataPackage.applicationId;
            this->interactionPackage.interactionId = dataPackage.interactionId;
            this->data.data.allowedMentions = dataPackage.allowedMentions;
            this->data.data.components = dataPackage.components;
            this->data.data.content = dataPackage.content;
            this->data.data.embeds = dataPackage.embeds;
            this->requesterId = dataPackage.requesterId;
            this->data.data.tts = dataPackage.tts;
            this->data.data.flags = 64;
        }

        CreateEphemeralInteractionResponseData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
            this->data.type = InteractionCallbackType::ChannelMessageWithSource;
            this->requesterId = dataPackage.getRequesterId();
            this->data.data.flags = 64;
        }

        virtual ~CreateEphemeralInteractionResponseData() {};

    };

    /// For creating an Interaction response. \brief For creating an Interaction response.
    class DiscordCoreAPI_Dll CreateInteractionResponseData : public InteractionResponse {
    public:

        friend string DiscordCoreInternal::JSONIFY(DiscordCoreAPI::CreateInteractionResponseData dataPackage);
        friend class  SelectMenuCollector;
        friend class  ButtonCollector;
        friend class  Interactions;
        friend class  InputEvents;        

        CreateInteractionResponseData(DeferComponentResponseData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.interactionPackage.interactionToken;
            this->interactionPackage.interactionId = dataPackage.interactionPackage.interactionId;
            this->interactionPackage.applicationId = dataPackage.interactionPackage.applicationId;
            this->data.type = dataPackage.type;
        }

        CreateInteractionResponseData(CreateEphemeralInteractionResponseData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.interactionPackage.interactionToken;
            this->interactionPackage.applicationId = dataPackage.interactionPackage.applicationId;
            this->interactionPackage.interactionId = dataPackage.interactionPackage.interactionId;
            this->data.data.components = dataPackage.data.data.components;
            this->requesterId = dataPackage.requesterId;
            this->data.type = dataPackage.data.type;
            this->data = dataPackage.data;
            this->data.data.flags = 64;
        }

        CreateInteractionResponseData(RespondToInputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.interactionToken;
            this->data.type = InteractionCallbackType::ChannelMessageWithSource;
            this->interactionPackage.applicationId = dataPackage.applicationId;
            this->interactionPackage.interactionId = dataPackage.interactionId;
            this->data.data.allowedMentions = dataPackage.allowedMentions;
            this->data.data.components = dataPackage.components;
            this->data.data.content = dataPackage.content;
            this->data.data.embeds = dataPackage.embeds;
            this->requesterId = dataPackage.requesterId;
            this->data.data.flags = dataPackage.flags;
            this->data.data.tts = dataPackage.tts;
        }

        CreateInteractionResponseData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
            this->data.type = InteractionCallbackType::ChannelMessageWithSource;
            this->requesterId = dataPackage.getRequesterId();
        }

        CreateInteractionResponseData(InteractionData dataPackage) {
            this->data.type = InteractionCallbackType::ChannelMessageWithSource;
            this->interactionPackage.interactionToken = dataPackage.token;
            this->interactionPackage.interactionId = dataPackage.id;
            if (dataPackage.member.user.id != "") {
                this->requesterId = dataPackage.message.member.user.id;
            }
            else {
                this->requesterId = dataPackage.user.id;
            }
        }

        virtual ~CreateInteractionResponseData() {};

    };

    /// For creating a deferred Interaction response. \brief For creating a deferred Interaction response.
    class DiscordCoreAPI_Dll CreateDeferredInteractionResponseData : public InteractionResponse {
    public:

        friend string DiscordCoreInternal::JSONIFY(DiscordCoreAPI::CreateDeferredInteractionResponseData dataPackage);
        friend class  Interactions;
        friend class  InputEvents;

        CreateDeferredInteractionResponseData(RespondToInputEventData dataPackage) {
            this->data.type = InteractionCallbackType::DeferredChannelMessageWithSource;
            this->interactionPackage.interactionToken = dataPackage.interactionToken;
            this->interactionPackage.applicationId = dataPackage.applicationId;
            this->interactionPackage.interactionId = dataPackage.interactionId;
            this->data.data.allowedMentions = dataPackage.allowedMentions;
            this->data.data.components = dataPackage.components;
            this->data.data.content = dataPackage.content;
            this->data.data.embeds = dataPackage.embeds;
            this->requesterId = dataPackage.requesterId;
            this->data.data.flags = dataPackage.flags;
            this->data.data.tts = dataPackage.tts;
        }
        CreateDeferredInteractionResponseData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->data.type = InteractionCallbackType::DeferredChannelMessageWithSource;
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
            this->requesterId = dataPackage.getAuthorId();
            this->channelId = dataPackage.getChannelId();
            this->data.data.flags = 64;
        }

        virtual ~CreateDeferredInteractionResponseData() {};

    protected:

        string channelId{ "" };
    };

    /// For getting an Interaction response. \brief For getting an Interaction response.
    struct DiscordCoreAPI_Dll GetInteractionResponseData {
        string interactionToken{ "" }; ///< Interaction token.
        string applicationId{ "" }; ///< application id.
    };

    /// For editing an Interaction response. \brief For editing an Interaction response.
    class DiscordCoreAPI_Dll EditInteractionResponseData : public InteractionResponse {
    public:

        friend string DiscordCoreInternal::JSONIFY(DiscordCoreAPI::EditInteractionResponseData dataPackage);
        friend class  Interactions;
        friend class  InputEvents;

        EditInteractionResponseData(RespondToInputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.interactionToken;
            this->interactionPackage.applicationId = dataPackage.applicationId;
            this->interactionPackage.interactionId = dataPackage.interactionId;
            this->data.data.allowedMentions = dataPackage.allowedMentions;
            this->data.type = InteractionCallbackType::UpdateMessage;
            this->data.data.components = dataPackage.components;
            this->data.data.content = dataPackage.content;
            this->data.data.embeds = dataPackage.embeds;
            this->requesterId = dataPackage.requesterId;
            this->data.data.flags = dataPackage.flags;
            this->data.data.tts = dataPackage.tts;
        }

        EditInteractionResponseData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->data.type = InteractionCallbackType::UpdateMessage;
            this->requesterId = dataPackage.getRequesterId();
        }

        virtual ~EditInteractionResponseData() {};

    };

    /// For deleting an Interaction response. \brief For deleting an Interaction response.
    struct DiscordCoreAPI_Dll DeleteInteractionResponseData {

        friend void deleteInteractionResponseToBeWrapped(DiscordCoreAPI::DeleteInteractionResponseData dataPackage);
        friend class  InputEvents;
        friend class  Interactions;

        DeleteInteractionResponseData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
        }

    protected:
        InteractionPackageData interactionPackage{};
        uint32_t timeDelay{ 0 };
    };

    /// For creating an ephemeral follow up Message. \brief For creating an ephemeral follow up Message.
    class DiscordCoreAPI_Dll CreateEphemeralFollowUpMessageData : public InteractionResponse {
    public:

        friend class  CreateFollowUpMessageData;
        friend class  Interactions;
        friend class  InputEvents;

        CreateEphemeralFollowUpMessageData(RespondToInputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.interactionToken;
            this->data.type = InteractionCallbackType::ChannelMessageWithSource;
            this->interactionPackage.applicationId = dataPackage.applicationId;
            this->interactionPackage.interactionId = dataPackage.interactionId;
            this->data.data.allowedMentions = dataPackage.allowedMentions;
            this->data.data.components = dataPackage.components;
            this->data.data.content = dataPackage.content;
            this->data.data.embeds = dataPackage.embeds;
            this->requesterId = dataPackage.requesterId;
            this->data.data.tts = dataPackage.tts;
            this->data.data.flags = 64;
        }

        CreateEphemeralFollowUpMessageData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
            this->data.type = InteractionCallbackType::ChannelMessageWithSource;
            this->requesterId = dataPackage.getRequesterId();
            this->data.data.flags = 64;
        }

        virtual ~CreateEphemeralFollowUpMessageData() {};
    };

    /// For creating a follow up Message. \brief For creating a follow up Message.
    class DiscordCoreAPI_Dll CreateFollowUpMessageData : public InteractionResponse {
    public:

        friend string DiscordCoreInternal::JSONIFY(DiscordCoreAPI::CreateFollowUpMessageData dataPackage);
        friend class  Interactions;
        friend class  InputEvents;

        CreateFollowUpMessageData(CreateEphemeralFollowUpMessageData dataPackage) {
            this->interactionPackage = dataPackage.interactionPackage;
            this->requesterId = dataPackage.requesterId;
            this->data = dataPackage.data;
        }

        CreateFollowUpMessageData(RespondToInputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.interactionToken;
            this->data.type = InteractionCallbackType::ChannelMessageWithSource;
            this->interactionPackage.applicationId = dataPackage.applicationId;
            this->interactionPackage.interactionId = dataPackage.interactionId;
            this->data.data.allowedMentions = dataPackage.allowedMentions;
            this->data.data.components = dataPackage.components;
            this->data.data.content = dataPackage.content;
            this->data.data.embeds = dataPackage.embeds;
            this->requesterId = dataPackage.requesterId;
            this->data.data.flags = dataPackage.flags;
            this->data.data.tts = dataPackage.tts;
        }

        CreateFollowUpMessageData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
            this->data.type = InteractionCallbackType::ChannelMessageWithSource;
            this->requesterId = dataPackage.getRequesterId();
        }

        virtual ~CreateFollowUpMessageData() {};

    };

    /// For getting a follow-up Message. \brief For getting a follow-up Message.
    struct DiscordCoreAPI_Dll GetFollowUpMessageData {
        string messageId{ "" };///< Message id.
        string interactionToken{ "" }; ///< Interaction token.
        string applicationId{ "" }; ///< application id.
    };

    /// For editing a follow up Message. \brief For editing a follow up Message.
    class DiscordCoreAPI_Dll EditFollowUpMessageData : public InteractionResponse {
    public:

        friend string DiscordCoreInternal::JSONIFY(DiscordCoreAPI::EditFollowUpMessageData dataPackage);
        friend class  Interactions;
        friend class  InputEvents;
        EditFollowUpMessageData(RespondToInputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.interactionToken;
            this->interactionPackage.applicationId = dataPackage.applicationId;
            this->interactionPackage.interactionId = dataPackage.interactionId;
            this->data.data.allowedMentions = dataPackage.allowedMentions;
            this->data.type = InteractionCallbackType::UpdateMessage;
            this->messagePackage.channelId = dataPackage.channelId;
            this->messagePackage.messageId = dataPackage.messageId;
            this->data.data.components = dataPackage.components;
            this->data.data.content = dataPackage.content;
            this->data.data.embeds = dataPackage.embeds;
            this->requesterId = dataPackage.requesterId;
            this->data.data.flags = dataPackage.flags;
            this->data.data.tts = dataPackage.tts;
        }
        EditFollowUpMessageData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
            this->messagePackage.messageId = dataPackage.getMessageId();
            this->data.type = InteractionCallbackType::UpdateMessage;
            this->requesterId = dataPackage.getRequesterId();
        }

        virtual ~EditFollowUpMessageData() {};
    };

    /// For deleting a follow up Message. \brief For deleting a follow up Message.
    struct DiscordCoreAPI_Dll DeleteFollowUpMessageData {

        friend void deleteFollowUpMessageToBeWrapped(DiscordCoreAPI::DeleteFollowUpMessageData dataPackage);
        friend class  InputEvents;
        friend class  Interactions;
        
        DeleteFollowUpMessageData(InputEventData dataPackage) {
            this->interactionPackage.interactionToken = dataPackage.getInteractionToken();
            this->interactionPackage.applicationId = dataPackage.getApplicationId();
            this->interactionPackage.interactionId = dataPackage.getInteractionId();
            this->messagePackage.messageId = dataPackage.getMessageId();
        }
    protected:
        InteractionPackageData interactionPackage{};
        MessagePackageData messagePackage{};
        uint32_t timeDelay{ 0 };
    };

    /// A single Interaction.
    struct DiscordCoreAPI_Dll Interaction : public InteractionData {
    public:
        
        Interaction(InteractionData dataPackage);

        virtual ~Interaction() {};
    };
    /**@}*/

    /**
    * \addtogroup main_endpoints
    * @{
    */
    /// An interface class DiscordCoreAPI_Dll for the Interaction related Discord endpoints. \brief An interface class DiscordCoreAPI_Dll for the Interaction related Discord endpoints.
    class DiscordCoreAPI_Dll Interactions {
    public:

        friend class  DiscordCoreInternal::WebSocketAgent;
        friend class  DiscordCoreClient;
        friend class  EventHandler;
        friend class  EventManager;        

        /// Creates a deferred response to an input Interaction. \brief Creates a deferred response to an input Interaction.
        /// \param dataPackage A CreateDeferredInteractionResponseData structure.
        /// \returns A CoRoutine containing void.
        static CoRoutine<void> createDeferredInteractionResponseAsync(CreateDeferredInteractionResponseData dataPackage);

        /// Creates a response to an input Interaction. \brief Creates a response to an input Interaction.
        /// \param dataPackage A CreateInteractionResponseData structure.
        /// \returns A CoRoutine containing a MessageData.
        static CoRoutine<Message> createInteractionResponseAsync(CreateInteractionResponseData dataPackage);

        /// Collects an Interaction response. \brief Collects an Interaction response.
        /// \param dataPackage A GetInteractionResponseData structure.
        /// \returns A CoRoutine containing an InteractionResponseData.
        static CoRoutine<InteractionResponseData> getInteractionResponseAsync(GetInteractionResponseData dataPackage);

        /// Edits an Interaction response. \brief Edits an Interaction response.
        /// \param dataPackage A EditInteractionResponseData structure.
        /// \returns A CoRoutine containing a MessageData.
        static CoRoutine<Message> editInteractionResponseAsync(EditInteractionResponseData dataPackage);

        /// Deletes an Interaction respnose. \brief Deletes an Interaction respnose.
        /// \param dataPackage A DeleteInteractionResponseData structure.
        /// \returns A CoRoutine containing void.
        static CoRoutine<void> deleteInteractionResponseAsync(DeleteInteractionResponseData dataPackage);

        /// Creates a follow up Message to an input Interaction. \brief Creates a follow up Message to an input Interaction.
        /// \param dataPackage A CreateFollowUpMessageData structure.
        /// \returns A CoRoutine containing a MessageData.
        static CoRoutine<Message> createFollowUpMessageAsync(CreateFollowUpMessageData dataPackage);

        /// Creates a follow up Message to an input Interaction. \brief Creates a follow up Message to an input Interaction.
        /// \param dataPackage A CreateFollowUpMessageData structure.
        /// \returns A CoRoutine containing a MessageData.
        static CoRoutine<Message> getFollowUpMessageAsync(GetFollowUpMessageData dataPackage);

        /// Edits a follow up Message. \brief Edits a follow up Message.
        /// \param dataPackage A EditFollowUpMessageData structure.
        /// \returns A CoRoutine containing a MessageData.
        static CoRoutine<Message> editFollowUpMessageAsync(EditFollowUpMessageData dataPackage);

        /// Deletes a follow up Message. \brief Deletes a follow up Message.
        /// \param dataPackage A DeleteFollowUpMessageData structure.
        /// \returns A CoRoutine containing void.
        static CoRoutine<void> deleteFollowUpMessageAsync(DeleteFollowUpMessageData dataPackage);

    protected:
        static map<string, unique_ptr<UnboundedMessageBlock<DiscordCoreAPI::MessageData>>> collectMessageDataBuffers;
    };
    /**@}*/

    /**
    * \addtogroup utilities
    * @{
    */

    /// Select menu response data. \brief Select menu response data.
    struct DiscordCoreAPI_Dll SelectMenuResponseData {
        InteractionData interactionData{};///< Interaction data.
        string selectionId{ "" };///< Selection id.
        vector<string> values{};///< A vector of the chosen values.
        string channelId{ "" };///< The Channel id where it took place.
        string messageId{ "" };///< The Message id where it took place.
        string userId{ "" };///< The User id who selected the menu options.
    };

    /// SelectMenuCollector, for collecting select-menu input from one or more Users. \brief SelectMenuCollector, for collecting select-menu input from one or more Users.
    class DiscordCoreAPI_Dll SelectMenuCollector {
    public:
        friend class  DiscordCoreClient;

        static map<string, UnboundedMessageBlock<InteractionData>*>selectMenuInteractionBufferMap;

        /// Constructor. \brief Constructor.
        /// \param dataPackage An InputEventData structure, from the response that came from the submitted select-menu.
        /// \returns void
        SelectMenuCollector(InputEventData dataPackage);

        /// Used to collect the select-menu inputs from one or more users. \brief Used to collect the select-menu inputs from one or more users.
        /// \param getSelectMenuDataForAllNew Whether or not to collect select-menu input from a single target User or all potential users.
        /// \param maxWaitTimeInMsNew The maximum amount of time to wait for new inputs, in milliseconds.
        /// \param maxCollectedSelectMenuCountNew The maximum number of inputs to collect before stopping
        /// \param targetUserId The id of the single User to collect inputs from, if getSelectMenuDataForAllNew is set to false.
        /// \param doWeSendInitialResponse Whether or not we send a "Being updated" message in response to the selection.
        /// \returns A vector of SelectMenuResponseData.
        CoRoutine<vector<SelectMenuResponseData>>collectSelectMenuData(bool getSelectMenuDataForAllNew, int32_t maxWaitTimeInMsNew, int32_t maxCollectedSelectMenuCountNew, string targetUserId = "", bool doWeSendInitialResponse = true);

        ~SelectMenuCollector();

    protected:

        unique_ptr<UnboundedMessageBlock<DiscordCoreAPI::InteractionData>> selectMenuIncomingInteractionBuffer{ nullptr };
        DiscordCoreAPI::InteractionData interactionData{};
        vector<SelectMenuResponseData> responseVector{};
        int32_t currentCollectedSelectMenuCount{ 0 };
        int32_t maxCollectedSelectMenuCount{ 0 };
        bool doWeSendInitialResponse{ false };
        bool getButtonDataForAll{ false };
        uint32_t maxTimeInMs{ 0 };
        string selectMenuId{ "" };
        vector<string> values{};
        bool doWeQuit{ false };
        string channelId{ "" };
        string messageId{ "" };
        string userId{ "" };

        void run();
    };

    /// Button response data. \brief Button response data.
    struct DiscordCoreAPI_Dll ButtonResponseData {
        InteractionData interactionData{};///< Interaction data.
        string emojiName{ "" };///< The emoji name, if applicable.
        string channelId{ "" };///< The Channel id where it took place.
        string messageId{ "" };///< The Message id where it took place.
        string buttonId{ "" };///< The id of the button, for identification.
        string userId{ "" };///< The User id who selected the menu options.
    };

    /// ButtonCollector, for collecting button input from one or more Users. \brief ButtonCollector, for collecting button input from one or more Users.
    class DiscordCoreAPI_Dll ButtonCollector {
    public:
        friend class  DiscordCoreClient;

        static map<string, UnboundedMessageBlock<InteractionData>*> buttonInteractionBufferMap;

        /// Constructor. \brief Constructor.
        /// \param dataPackage An InputEventData structure, from the response that came from the submitted button.
        /// \returns void
        ButtonCollector(InputEventData dataPackage);

        /// Used to collect the button inputs from one or more users. \brief Used to collect the button inputs from one or more users.
        /// \param getButtonDataForAllNew Whether or not to collect input from a single target User or all potential users.
        /// \param maxWaitTimeInMsNew The maximum amount of time to wait for new inputs, in milliseconds.
        /// \param maxNumberOfPressesNew The maximum number of inputs to collect before stopping.
        /// \param targetUserId The id of the single User to collect inputs from, if getButtonDataForAllNew is set to false.
        /// \param doWeSendInitialResponse Whether or not we send a "Being updated" message in response to the button press.
        /// \returns A vector of ButtonResponseData.
        CoRoutine<vector<ButtonResponseData>> collectButtonData(bool getButtonDataForAllNew, int32_t maxWaitTimeInMsNew, int32_t maxNumberOfPressesNew, string targetUserId = "", bool doWeSendInitialResponse = true);

        ~ButtonCollector();

    protected:

        unique_ptr<UnboundedMessageBlock<DiscordCoreAPI::InteractionData>> buttonIncomingInteractionBuffer{ nullptr };
        vector<ButtonResponseData> responseVector{};
        bool doWeSendInitialResponse{ false };
        bool getButtonDataForAll{ false };
        InteractionData interactionData{};
        int32_t maxNumberOfPresses{ 0 };
        uint32_t maxTimeInMs{ 0 };
        string channelId{ "" };
        string messageId{ "" };
        bool doWeQuit{ false };
        string buttonId{ "" };
        string userId{ "" };

        void run();
    };
    /**@}*/
};