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
/// AutoModerationEntities.cpp - Source file for the ApplicationCommand classes and structs.
/// Aug 25, 2021
/// https://discordcoreapi.com
/// \file AutoModerationEntities.cpp

#include <discordcoreapi/AutoModerationEntities.hpp>

namespace Jsonifier {

	template<> struct Core<DiscordCoreAPI::CreateAutoModerationRuleData> {
		using ValueType = DiscordCoreAPI::CreateAutoModerationRuleData;
		static constexpr auto parseValue = object("exemptChannels", &ValueType::exemptChannels, "exemptRoles", &ValueType::exemptRoles,
			"triggerMetadata", &ValueType::triggerMetadata, "actions", &ValueType::actions, "triggerType", &ValueType::triggerType, "eventType",
			&ValueType::eventType, "guildId", &ValueType::guildId, "name", &ValueType::name, "enabled", &ValueType::enabled);
	};

	template<> struct Core<DiscordCoreAPI::ModifyAutoModerationRuleData> {
		using ValueType = DiscordCoreAPI::ModifyAutoModerationRuleData;
		static constexpr auto parseValue = object("exemptChannels", &ValueType::exemptChannels, "exemptRoles", &ValueType::exemptRoles,
			"triggerMetadata", &ValueType::triggerMetadata, "actions", &ValueType::actions, "autoModerationRuleId", &ValueType::autoModerationRuleId,
			"eventType", &ValueType::eventType, "guildId", &ValueType::guildId, "name", &ValueType::name, "enabled", &ValueType::enabled);
	};

}

namespace DiscordCoreAPI {



	void AutoModerationRules::initialize(DiscordCoreInternal::HttpsClient* HttpsClientNew) {
		AutoModerationRules::httpsClient = HttpsClientNew;
	}

	CoRoutine<std::vector<AutoModerationRule>> AutoModerationRules::listAutoModerationRulesForGuildAsync(
		ListAutoModerationRulesForGuildData dataPackage) {
		DiscordCoreInternal::HttpsWorkloadData workload{ DiscordCoreInternal::HttpsWorkloadType::Get_Auto_Moderation_Rules };
		co_await NewThreadAwaitable<std::vector<AutoModerationRule>>();
		workload.workloadClass = DiscordCoreInternal::HttpsWorkloadClass::Get;
		workload.relativePath = "/guilds/" + dataPackage.guildId + "/auto-moderation/rules";
		workload.callStack = "AutoModerationRules::listAutoModerationRulesForGuildAsync()";
		AutoModerationRuleVector returnVector{};
		AutoModerationRules::httpsClient->submitWorkloadAndGetResult<AutoModerationRuleVector>(std::move(workload), returnVector);
		co_return std::move(returnVector);
	}

	CoRoutine<AutoModerationRule> AutoModerationRules::getAutoModerationRuleAsync(GetAutoModerationRuleData dataPackage) {
		DiscordCoreInternal::HttpsWorkloadData workload{ DiscordCoreInternal::HttpsWorkloadType::Get_Auto_Moderation_Rule };
		co_await NewThreadAwaitable<AutoModerationRule>();
		workload.workloadClass = DiscordCoreInternal::HttpsWorkloadClass::Get;
		workload.relativePath = "/guilds/" + dataPackage.guildId + "/auto-moderation/rules/" + std::to_string(dataPackage.autoModerationRuleId);
		workload.callStack = "AutoModerationRules::getAutoModerationRuleAsync()";
		AutoModerationRule returnData{};
		AutoModerationRules::httpsClient->submitWorkloadAndGetResult<AutoModerationRule>(std::move(workload), returnData);
		co_return std::move(returnData);
	}

	CoRoutine<AutoModerationRule> AutoModerationRules::createAutoModerationRuleAsync(CreateAutoModerationRuleData dataPackage) {
		DiscordCoreInternal::HttpsWorkloadData workload{ DiscordCoreInternal::HttpsWorkloadType::Post_Auto_Moderation_Rule };
		co_await NewThreadAwaitable<AutoModerationRule>();
		workload.workloadClass = DiscordCoreInternal::HttpsWorkloadClass::Post;
		workload.relativePath = "/guilds/" + dataPackage.guildId + "/auto-moderation/rules";
		parser.serializeJson(dataPackage, workload.content);
		workload.callStack = "AutoModerationRules::createAutoModerationRuleAsync()";
		AutoModerationRule returnData{};
		AutoModerationRules::httpsClient->submitWorkloadAndGetResult<AutoModerationRule>(std::move(workload), returnData);
		co_return std::move(returnData);
	}

	CoRoutine<AutoModerationRule> AutoModerationRules::modifyAutoModerationRuleAsync(ModifyAutoModerationRuleData dataPackage) {
		DiscordCoreInternal::HttpsWorkloadData workload{ DiscordCoreInternal::HttpsWorkloadType::Patch_Auto_Moderation_Rule };
		co_await NewThreadAwaitable<AutoModerationRule>();
		workload.workloadClass = DiscordCoreInternal::HttpsWorkloadClass::Patch;
		workload.relativePath = "/guilds/" + dataPackage.guildId + "/auto-moderation/rules/" + std::to_string(dataPackage.autoModerationRuleId);
		parser.serializeJson(dataPackage, workload.content);
		workload.callStack = "AutoModerationRules::modifyAutoModerationRuleAsync()";
		AutoModerationRule returnData{};
		AutoModerationRules::httpsClient->submitWorkloadAndGetResult<AutoModerationRule>(std::move(workload), returnData);
		co_return std::move(returnData);
	}

	CoRoutine<void> AutoModerationRules::deleteAutoModerationRuleAsync(DeleteAutoModerationRuleData dataPackage) {
		DiscordCoreInternal::HttpsWorkloadData workload{ DiscordCoreInternal::HttpsWorkloadType::Delete_Auto_Moderation_Rule };
		co_await NewThreadAwaitable<void>();
		workload.workloadClass = DiscordCoreInternal::HttpsWorkloadClass::Delete;
		workload.relativePath = "/guilds/" + dataPackage.guildId + "/auto-moderation/rules/" + std::to_string(dataPackage.autoModerationRuleId);
		workload.callStack = "AutoModerationRules::deleteAutoModerationRuleAsync()";
		AutoModerationRules::httpsClient->submitWorkloadAndGetResult<void>(std::move(workload));
		co_return;
	}

	DiscordCoreInternal::HttpsClient* AutoModerationRules::httpsClient{};

}
