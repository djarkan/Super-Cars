#ifndef INPUTS_HPP
#define INPUTS_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>

#include "header/command.hpp"
#include "header/commandqueue.hpp"
#include "header/player.hpp"

class Inputs {
    public:
                                            Inputs(sf::RenderWindow& window);
        void                                readInput(unsigned int joystickID);                                                    // push m_commandQueue
        Command                             getInput();                                                     // pop m_commandQueue
        bool                                isCommandAvailable();
        void                                clearCommand(Command& command);

    private:
        sf::RenderWindow&                   m_window;
        Queue                               m_commandQueue;
        unsigned int                        m_currentJoystickButton;
        unsigned int                        m_currentJoysstickID;
        unsigned int                        m_currentJoystickID;
        sf::Vector2f                        m_windowRatio;

        void                                checkAxis(Command& command, unsigned int joystickID);
        void                                checkLastJoystickButtonUsed(Command& command);
        unsigned int                        whatJoystickUsed();
};
#endif


