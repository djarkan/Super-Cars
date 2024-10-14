#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System/Vector2.hpp>

enum class                         CommandType { noAction = 0,
                                                 keyboardPressed,
                                                 keyboardReleased,
                                                 joystiskButtonPressed,
                                                 joystiskButtonPushed,
                                                 joystiskButtonReleased,
                                                 mouseLeftButtonPressed,
                                                 mouseLeftButtonReleased,
                                                 joystiskMoved,
                                                 lostFocus,
                                                 gainFocus};

struct Command {
    CommandType                     action;
    unsigned int                    joystickButtonID;
    char                            letter;
    sf::Vector2f                    coords;
    float                           offsetX;
    float                           offsetY;
    Command() : action{CommandType::noAction}, joystickButtonID{99}, letter{0}, coords{sf::Vector2f(0.f, 0.f)}, offsetX{0.f}, offsetY{0.f}
    {}
};

#endif
