#include <header/inputs.hpp>

extern sf::Vector2f windowRatio;

Inputs::Inputs(sf::RenderWindow& window): m_window{window}, m_commandQueue(), m_currentJoystickButton{0}, m_currentJoystickID{0}
{

}

void Inputs::readInput(unsigned int joystickID)
{
    sf::Joystick::update();
    Command command;
    command.coords = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
    sf::Event event;
     while(m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed :
                    m_window.close();
                    break;
                case sf::Event::LostFocus :
                    command.action = CommandType::lostFocus;
                    break;
                case sf::Event::GainedFocus :
                    command.action = CommandType::gainFocus;
                    break;
                case sf::Event::KeyPressed :
                    command.action = CommandType::keyboardPressed;
                    if(event.key.code == sf::Keyboard::Key::Space) { command.letter = ' '; }
                    break;
                case sf::Event::KeyReleased :
                    command.action = CommandType::keyboardReleased;
                    if(event.key.code == sf::Keyboard::Key::Escape) { command.letter = 27; }
                    break;
                case sf::Event::JoystickButtonPressed :
                    if(event.joystickButton.joystickId == joystickID) {
                        command.coords = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
                        command.action = CommandType::joystiskButtonPressed;
                        command.joystickButtonID = event.joystickButton.button;
                        m_currentJoystickButton = event.joystickButton.button;
                        m_currentJoystickID = joystickID;
                    }
                    break;
                case sf::Event::JoystickButtonReleased :
                    if(event.joystickButton.joystickId == joystickID) {
                        command.coords = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
                        command.action = CommandType::joystiskButtonReleased;
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Button::Left){
                        command.coords = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
                        command.action = CommandType::mouseLeftButtonPressed;
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button == sf::Mouse::Button::Left){
                        command.coords = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
                        command.action = CommandType::mouseLeftButtonReleased;
                    }
                    break;
                default:
                    break;
            }
            command.coords.x /= windowRatio.x;
            command.coords.y /= windowRatio.y;
            m_commandQueue.push(command);
            clearCommand(command);
        }
        checkLastJoystickButtonUsed(command);
        checkAxis(command, joystickID);
}

Command Inputs::getInput()
{
    if(!m_commandQueue.isEmpty()) { return m_commandQueue.pop(); }
    else {
        Command command;
        command.action = CommandType::noAction;
        return command;
    }
}

bool Inputs::isCommandAvailable()
{
    return !m_commandQueue.isEmpty();
}

void Inputs::checkAxis(Command& command, unsigned int joystickID)
{
    if(sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::X) < -70 || sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::X) > 70) {
            command.offsetX = sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::X);
            command.action = CommandType::joystiskMoved;
        }
        if(sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::Y) < -70 || sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::Y) > 70) {
            command.offsetY = sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::Y);
            command.action = CommandType::joystiskMoved;
        }
        if (sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::V) < -70 || sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::V) > 70) {
            command.offsetX = sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::V);
            command.action = CommandType::joystiskMoved;
        }
        if (sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::U) < -70 || sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::U) > 70) {
            command.offsetY = sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::U);
            command.action = CommandType::joystiskMoved;
        }
        if (sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::Z) < -70 || sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::Z) > 70) {
            command.offsetX = sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::Z);
            command.action = CommandType::joystiskMoved;
        }
        if(sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::R) < -70 || sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::R) > 70) {
            command.offsetY = sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::R);
            command.action = CommandType::joystiskMoved;
        }

        if(sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::PovX) < -70 || sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::PovX) > 70) {
            command.offsetX = sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::PovX);
            command.action = CommandType::joystiskMoved;
        }

        if(sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::PovY) < -70 || sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::PovY) > 70) {
            command.offsetY = sf::Joystick::getAxisPosition(joystickID, sf::Joystick::Axis::PovY);
            command.action = CommandType::joystiskMoved;
        }
        command.coords.x /= windowRatio.x;
        command.coords.y /= windowRatio.y;
        m_commandQueue.push(command);
        clearCommand(command);
}

void Inputs::checkLastJoystickButtonUsed(Command& command)
{
    if (sf::Joystick::isButtonPressed(m_currentJoystickID, m_currentJoystickButton) && command.action != CommandType::joystiskButtonPressed) {
        command.action = CommandType::joystiskButtonPushed;
        command.joystickButtonID = m_currentJoystickButton;
    }
    else {
        command.action = CommandType::joystiskButtonReleased;
    }
    m_commandQueue.push(command);
    clearCommand(command);
}

void Inputs::clearCommand(Command& command)
{
    command.action = CommandType::noAction;
    command.coords = sf::Vector2f(0, 0);
    command.joystickButtonID = 99;
    command.letter = 0;
    command.offsetX = 0;
    command.offsetY = 0;
}

