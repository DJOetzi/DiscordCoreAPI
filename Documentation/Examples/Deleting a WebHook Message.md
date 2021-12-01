### **Deleting a WebHook Message:**
---
- Access within the `DiscordCoreAPI` namespace, the `WebHooks` class.
- Populate a data structure of type `DiscordCoreAPI::DeleteWebHookMessageData`.
- Select, from the `WebHooks` class, the `deleteWebHookMessageAsync()` function and execute it, with a return value of type `void`, while passing it the created data structure.
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

				ExecuteWebHookData dataPackage01{ newWebHooks[0] };
				dataPackage01.addContent("TEST CONTENT");
				dataPackage01.wait = true;

				auto newMessage = WebHooks::executeWebHookAsync(dataPackage01).get();

				DeleteWebHookMessageData dataPackage03{};
				dataPackage03.webhookId = newWebHooks[0].id;
				dataPackage03.webhookToken = newWebHooks[0].token;
				dataPackage03.messageId = newMessage.id;

				WebHooks::deleteWebHookMessageAsync(dataPackage03).get();

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