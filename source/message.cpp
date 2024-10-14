#include "c:/Users/djarkan/Documents/C++/visual c++/Super Cars/header/message.hpp"

#include <iostream>

Message::Message(const unsigned int language, const Messages message) : m_messageToDisplay{message}, m_language{language}
{

    switch (m_language) {
        case 0:
            m_languageJson.loadJsonFile("language/english/messages.json");
            break;
        case 1:
            m_languageJson.loadJsonFile("language/usa/messages.json");
            break;
        case 2:
            m_languageJson.loadJsonFile("language/french/messages.json");
            break;
        default:
            break;
    }
    loadFont();
    setFontSize(16, 16);
    initBackground();
    setText();
}

bool Message::loadFont()
{
    bool success{ m_font.loadTexture("c:/Users/djarkan/Documents/C++/visual c++/Super Cars/graphics/bitmap_fonts/super_cars_16x16.png") };
    m_text.setFont(&m_font);
    return success;
}

void Message::initBackground()
{
    m_background.setPosition(sf::Vector2f(125, 152));
    m_background.setSize(sf::Vector2f(390, 100));
    m_background.setFillColor(sf::Color(0x000099FF));
}

void Message::setText()
{
    switch (m_messageToDisplay) {
        case Messages::Loading:
            m_text.setText(m_languageJson.m_Root["loading"].asString());
            break;
        case Messages::WonStage1:
            m_text.setText(m_languageJson.m_Root["wonStage1"].asString());
            break;
        case Messages::WonStage2:
            m_text.setText(m_languageJson.m_Root["wonStage2"].asString());
            break;
        case Messages::RaceWon:
            m_text.setText(m_languageJson.m_Root["raceWon"].asString());
            break;
        case Messages::RaceLost:
            m_text.setText(m_languageJson.m_Root["raceLost"].asString());
            break;
        case Messages::TyresBroken:
            m_text.setText(m_languageJson.m_Root["tyresBroken"].asString());
            break;
        case Messages::FuelEmpty:
            m_text.setText(m_languageJson.m_Root["fuelEmpty"].asString());
            break;
        case Messages::EngineBroken:
            m_text.setText(m_languageJson.m_Root["engineBroken"].asString());
            break;
        case Messages::BodyBroken:
            m_text.setText(m_languageJson.m_Root["bodyBroken"].asString());
            break;
        case Messages::NoJoystick:
            m_text.setText(m_languageJson.m_Root["noJoystick"].asString());
            break;
        case Messages::sevaralJoystick:
            m_text.setText(m_languageJson.m_Root["sevaralJoystick"].asString());
            break;
        case Messages::loadSavedGame:
            m_text.setText(m_languageJson.m_Root["loadSavedGame"].asString());
            break;
        default:
            break;
    }
    sf::FloatRect bounds{m_text.getLocalBounds()};
    sf::Vector2f rectSize{ m_background.getSize()};
    sf::Vector2f position{ m_background.getPosition()};
    m_text.setPosition(sf::Vector2f(position .x + ((rectSize.x - bounds.width) / 2), position .y + ((rectSize.y - bounds.height) / 2)));
}

void Message::setFontSize(unsigned int glyphWidth, unsigned int glyphHigth)
{
    m_font.setSize(glyphWidth, glyphHigth);
}

void Message::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_background, states);
    target.draw(m_text, states);
}
