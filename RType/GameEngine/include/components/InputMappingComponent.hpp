//Maps inputs to actions (std::function<void()>), enabling runtime reconfiguration.

#ifndef INPUTMAPPINGCOMPONENT_HPP_
#define INPUTMAPPINGCOMPONENT_HPP_

#include <unordered_map>
#include <cstdint>
#include <functional>
#include "InputComponent.hpp"

struct InputMappingComponent {
    using Action = std::function<void()>;

    std::unordered_map<InputCommand, Action> inputToActionMap;
};

#endif /* !INPUTMAPPINGCOMPONENT_HPP_ */
