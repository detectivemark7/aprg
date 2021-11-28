#include <Common/Utils/StringHelpers.hpp>
#include <RAN3374/Components/GRM.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator {

GRM::GRM() : m_componentName(ComponentName::EMPTY) {}

GRM::GRM(ComponentName const componentName) : m_componentName(componentName) {}

void GRM::handleMessageEvent(GenericMessage const& genericMessage) {
    MessageName messageName(genericMessage.getMessageName());
    switch (messageName) {
        case MessageName::TC_LTX_TELECOM_MSG:
            cout << "Handle Message, TC_LTX_TELECOM_MSG: \n";
        default:
            cout << "Handle Message, messageName: " << StringHelpers::genericMessage.getMessageNameInString() << "\n";
    }
}

void GRM::handleTimerEvent(Timer const& timer) {
    cout << "Handle Timer, timerType: " << StringHelpers::convertToString(timer.getType())
         << " timerId:" << (int)timer.getId() << "\n";
}

}  // namespace DesignDocumentCreator
