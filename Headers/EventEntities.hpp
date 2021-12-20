/// EventEntities.hpp - Header for the "Event-related stuff".
/// Dec 12, 2021
/// Chris M.
/// https://github.com/RealTimeChris

#pragma once

#include "IndexInitial.hpp"
#include "FoundationEntities.hpp"
#include "CoRoutine.hpp"

namespace DiscordCoreAPI {

    struct DiscordCoreAPI_Dll EventDelegateToken {

        template<typename R, typename ...Args>
        friend class Event;

        template<typename R, typename ...Args>
        friend class EventDelegate;

        friend inline bool operator==(const EventDelegateToken& lhs, const EventDelegateToken& rhs);

        friend inline bool operator<(const EventDelegateToken& lhs, const EventDelegateToken& rhs);

        friend inline bool operator>(const EventDelegateToken& lhs, const EventDelegateToken& rhs);

    protected:

        EventDelegateToken() = default;

        string handlerId{ "" };
        string eventId{ "" };

    };

    bool operator==(const EventDelegateToken& lhs, const EventDelegateToken& rhs) {
        if (lhs.eventId == rhs.eventId && lhs.handlerId == rhs.handlerId) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator<(const EventDelegateToken& lhs, const EventDelegateToken& rhs) {
        if (lhs.handlerId < rhs.handlerId) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator>(const EventDelegateToken& lhs, const EventDelegateToken& rhs) {
        if (lhs < rhs) {
            return false;
        }
        else {
            return true;
        }
    }

    template<typename R, typename ...Args>
    class EventDelegate {
    public:

        template<typename R, typename... A>
        friend class Event;

        EventDelegate<R, Args...>& operator=(EventDelegate<R, Args...>&& other) {
            this->theFunction = move(other.theFunction);
            return *this;
        }

        EventDelegate(EventDelegate<R, Args...>&& other) {
            *this = move(other);
        }

        EventDelegate<R, Args...>& operator=(const EventDelegate<R, Args...>& other) = delete;

        EventDelegate(const EventDelegate<R, Args...>& other) = delete;

        EventDelegate(function<R(Args...)> theFunctionNew) {
            this->theFunction = theFunctionNew;
        }

        EventDelegate(R(*theFunctionNew)(Args...)) {
            this->theFunction = theFunctionNew;
        }

    protected:
        function<R(Args...)>theFunction{};
    };

    template<typename R, typename  ...Args>
    class DiscordCoreAPI_Dll Event {
    public:

        Event<R, Args...>& operator=(Event<R, Args...>&& other) {
            this->theFunctions = move(other.theFunctions);
            this->eventId = other.eventId;
            return *this;
        }

        Event(Event<R, Args...>&& other) {
            *this = move(other);
        }

        Event<R, Args...>& operator=(const Event<R, Args...>&) = delete;

        Event(const Event<R, Args...>&) = delete;

        Event() {
            this->eventId = to_string(chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count());
        }

        EventDelegateToken add(EventDelegate<R, Args...> eventDelegate) {
            EventDelegateToken eventToken{};
            eventToken.handlerId = to_string(chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count());
            eventToken.eventId = this->eventId;
            this->theFunctions.insert_or_assign(eventToken, move(eventDelegate));
            return eventToken;
        }

        void remove(EventDelegateToken  eventToken) {
            if (this->theFunctions.contains(eventToken)) {
                this->theFunctions.erase(eventToken);
            }
        }

        void operator()(Args... args) {
            for (auto& [key, value] : this->theFunctions) {
                value.theFunction(args...);
            }
        }

    protected:
        map<EventDelegateToken, EventDelegate<R, Args...>> theFunctions{};
        string eventId{ "" };
    };

    template<typename ...Args>
    class EventDelegate<void, Args...> {
    public:

        friend class Event<void, Args...>;

        EventDelegate<void, Args...>& operator=(EventDelegate<void, Args...>&& other) {
            this->theFunction = move(other.theFunction);
            return *this;
        }

        EventDelegate(EventDelegate<void, Args...>&& other) {
            *this = move(other);
        }

        EventDelegate<void, Args...>& operator=(const EventDelegate<void, Args...>& other) = delete;

        EventDelegate(const EventDelegate<void, Args...>& other) = delete;

        EventDelegate(function<void(Args...)> theFunctionNew) {
            this->theFunction = theFunctionNew;
        }

        EventDelegate(void(*theFunctionNew)(Args...)) {
            this->theFunction = theFunctionNew;
        }

    protected:
        function<void(Args...)>theFunction{};
    };

    template<typename ...Args>
    class DiscordCoreAPI_Dll Event<void, Args...> {
    public:

        Event<void, Args...>& operator=(Event<void, Args...>&& other) {
            this->theFunctions = move(other.theFunctions);
            this->eventId = other.eventId;
            return *this;
        }

        Event(Event<void, Args...>&& other) {
            *this = move(other);
        }

        Event<void, Args...>& operator=(const Event<void, Args...>&) = delete;

        Event(const Event<void, Args...>&) = delete;

        Event() {
            this->eventId = to_string(chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count());
        }

        EventDelegateToken add(EventDelegate<void, Args...> eventDelegate) {
            EventDelegateToken eventToken{};
            eventToken.handlerId = to_string(chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count());
            eventToken.eventId = this->eventId;
            this->theFunctions.insert_or_assign(eventToken, move(eventDelegate));
            return eventToken;
        }

        void remove(EventDelegateToken  eventToken) {
            if (this->theFunctions.contains(eventToken)) {
                this->theFunctions.erase(eventToken);
            }
        }

        void operator()(Args... args) {
            for (auto& [key, value] : this->theFunctions) {
                value.theFunction(args...);
            }
        }

    protected:

        map<EventDelegateToken, EventDelegate<void, Args...>> theFunctions{};
        string eventId{ "" };

    };

    struct DiscordCoreAPI_Dll EventCore {

        friend class Event<void, void>;

        EventCore& operator=(EventCore&) = delete;

        EventCore(EventCore&) = delete;

        EventCore() = default;

    protected:

        static map<string, unique_ptr<EventCore>> theEvents;
        static map<string, uint32_t> refCounts;

        shared_ptr<bool> theEventState{ make_shared<bool>(false) };

    };

    template<>
    class DiscordCoreAPI_Dll Event<void, void> {
    public:

        shared_ptr<bool> theEventState{ make_shared<bool>(false) };
        string eventId{ "" };

        Event<void, void>& operator=(Event<void, void>&&) = delete;

        Event(Event<void, void>&&) = delete;

        Event<void, void>& operator=(const Event<void, void>&) = delete;

        Event(const Event<void, void>&) = delete;

        Event<void, void>& operator=(Event<void, void>& other) {
            this->theEventState = other.theEventState;
            this->eventId = other.eventId;
            return *this;
        }

        Event(Event<void, void>& other) {
            *this = other;
            EventCore::refCounts.at(this->eventId) += 1;
        }

        Event() {
            this->eventId = to_string(chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count());
            EventCore::theEvents.insert_or_assign(this->eventId, make_unique<EventCore>());
            EventCore::refCounts.insert_or_assign(this->eventId, 1);
            this->theEventState = EventCore::theEvents.at(this->eventId)->theEventState;
        }

        uint32_t wait(uint64_t millisecondsMaxToWait = UINT64_MAX, string testString = "") {
            uint32_t millisecondsWaited{ 0 };
            while (true) {
                if (*this->theEventState) {
                    return 0;
                }
                else {
                    this_thread::sleep_for(chrono::microseconds(1000));
                    millisecondsWaited += 1;
                }
                if (millisecondsWaited >= millisecondsMaxToWait) {
                    return 1;
                }
            }
        }

        void set(string testValue = "") {
            *this->theEventState = true;
        }

        void reset() {
            *this->theEventState = false;
        }

        ~Event() {
            if (EventCore::refCounts.contains(this->eventId)) {
                if (EventCore::refCounts.at(this->eventId) > 0) {
                    EventCore::refCounts.at(this->eventId) -= 1;

                }
                if (EventCore::refCounts.at(this->eventId) == 0) {
                    EventCore::refCounts.erase(this->eventId);
                    EventCore::theEvents.erase(this->eventId);
                }
            }
        }
    };


}