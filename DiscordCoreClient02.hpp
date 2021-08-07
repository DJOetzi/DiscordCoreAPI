// DiscordCoreClient02.hpp - Second header for the DiscordCoreClient class.
// Aug 7, 2021
// Chris M.
// https://github.com/RealTimeChris

#pragma once

#ifndef _DISCORD_CORE_CLIENT_02_
#define _DISCORD_CORE_CLIENT_02_

#include "EventHandler.hpp"

namespace DiscordCoreAPI {

    void DiscordCoreClient::finalSetup(string botToken) {
        try {
            DiscordCoreInternal::ThreadManager::intialize();
            shared_ptr<DiscordCoreClient> pDiscordCoreClient = make_shared<DiscordCoreClient>(to_hstring(botToken));
            DiscordCoreClient::thisPointer = pDiscordCoreClient;
            EventHandler::discordCoreClient = pDiscordCoreClient;
            pDiscordCoreClient->initialize().get();
            executeFunctionAfterTimePeriod([]() {
                cout << "Heart beat!" << endl << endl;
                }, 60000, true);
            pDiscordCoreClient->eventManager->onChannelCreation(&EventHandler::onChannelCreation);
            pDiscordCoreClient->eventManager->onChannelUpdate(&EventHandler::onChannelUpdate);
            pDiscordCoreClient->eventManager->onChannelDeletion(&EventHandler::onChannelDeletion);
            pDiscordCoreClient->eventManager->onGuildCreation(&EventHandler::onGuildCreation);
            pDiscordCoreClient->eventManager->onGuildUpdate(&EventHandler::onGuildUpdate);
            pDiscordCoreClient->eventManager->onGuildDeletion(&EventHandler::onGuildDeletion);
            pDiscordCoreClient->eventManager->onGuildMemberAdd(&EventHandler::onGuildMemberAdd);
            pDiscordCoreClient->eventManager->onGuildMemberRemove(&EventHandler::onGuildMemberRemove);
            pDiscordCoreClient->eventManager->onGuildMemberUpdate(&EventHandler::onGuildMemberUpdate);
            pDiscordCoreClient->eventManager->onRoleCreation(&EventHandler::onRoleCreation);
            pDiscordCoreClient->eventManager->onRoleUpdate(&EventHandler::onRoleUpdate);
            pDiscordCoreClient->eventManager->onRoleDeletion(&EventHandler::onRoleDeletion);
            pDiscordCoreClient->eventManager->onInteractionCreation(&EventHandler::onInteractionCreation);
            pDiscordCoreClient->eventManager->onVoiceStateUpdate(&EventHandler::onVoiceStateUpdate);
            CommandCenter::registerFunction("botinfo", new BotInfo);
            CommandCenter::registerFunction("play", new Play);
            CommandCenter::registerFunction("test", new Test);
        }
        catch (exception& e) {
            cout << "DiscordCoreAPI::finalSetup Error: " << e.what() << endl;
        }
    };
}

#endif
