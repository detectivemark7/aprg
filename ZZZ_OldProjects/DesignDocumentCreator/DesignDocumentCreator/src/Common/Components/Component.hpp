#pragma once

#include <Common/Events/Events.hpp>
#include <Common/Events/OtherEvent.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <deque>
#include <string>

namespace DesignDocumentCreator {

class Component {
public:
    Component(ComponentName const componentName);
    Component(Component const&) = delete;
    Component& operator=(Component const&) = delete;
    void pushBackEvent(Event const& event);
    void handleOneEvent();
    void handleAllEvents();
    void send(ComponentName const receiver, GenericMessage const& message) const;
    bool isEventQueueEmpty() const;
    GenericMessage peekMessageAtStartOfTheEventQueue() const;
    ComponentName getComponentName() const;
    std::string getComponentNameInString() const;
    std::string getQueueAsString() const;
    void log(std::string const& line) const;
    void logNoteOnPreviousMessage(std::string const& note) const;
    void logNoteOnComponent(std::string const& note) const;
    void logNoteOnComponents(ComponentNames const& componentNames, std::string const& note) const;

protected:
    virtual void handleEvent(Event const& event);
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    virtual void handleOtherEvent(OtherEvent const& timer);

    ComponentName m_componentName;
    std::string m_componentNameInString;
    std::deque<Event> m_eventQueue;
};

}  // namespace DesignDocumentCreator
