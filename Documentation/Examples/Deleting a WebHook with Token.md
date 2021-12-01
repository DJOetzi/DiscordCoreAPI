### **Deleting a WebHook with Token:**
---
- Access within the `DiscordCoreAPI` namespace, the `WebHooks` class.
- Populate a data structure of type `DiscordCoreAPI::DeleteWebHookWithTokenData`.
- Select, from the `WebHooks` class, the `deleteWebHookWithTokenAsync()` function and execute it, with a return value of type `void`, while passing it the created data structure.
- Call the function with `.get()` added to the end in order to wait for the results now.

```cpp
// Test.hpp - Header for the "test" command.
// https://github.com/RealTimeChris

#pragma once

#include "Index.hpp"

namespace DiscordCoreAPI {

	class Test : public BaseFunction {
	public:
		Test() {
			this->commandName = "test";
			this->helpDescription = "Testing purposes!";
			EmbedData msgEmbed{};
			msgEmbed.setDescription("------\nSimply enter !test or /test!\n------");
			msgEmbed.setTitle("__**Test Usage:**__");
			msgEmbed.setTimeStamp(getTimeAndDate());
			msgEmbed.setColor("FeFeFe");
			this->helpEmbed = msgEmbed;
		}

		unique_ptr<BaseFunction> create() {
			return make_unique<Test>();
		}

		virtual CoRoutine<void> executeAsync(BaseFunctionArguments args) {
			try {

				GetGuildWebHooksData dataPackage{};
				dataPackage.guildId = args.eventData.getGuildId();

				auto newWebHooks = WebHooks::getGuildWebHooksAsync(dataPackage).get();
 
				DeleteWebHookWithTokenData dataPackage01{};
				dataPackage01.webhookId = newWebHooks[0].id;
				dataPackage01.webhookToken = newWebHooks[0].token;

				WebHooks::deleteWebHookWithTokenAsync(dataPackage01).get();

				co_return;
			}
			catch (...) {
				rethrowException("Test::executeAsync Error: ");
			}
		}

		virtual ~Test() {};
	};
}
```