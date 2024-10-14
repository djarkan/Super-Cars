#include "header/racebottompanel.hpp"
#include "header/car.hpp"

#include <iostream>

RaceBottomPanel::RaceBottomPanel(const unsigned int language) : m_language{language}, m_speedMeter(sf::Vector2f(80, 10))
{
    loadTextures();
    spriteConfiguration();
    switch(language) {
        case 0 :
            m_languageJson.loadJsonFile("language/english/racebottompanel.json");
            break;
        case 1:
            m_languageJson.loadJsonFile("language/usa/racebottompanel.json");
            break;
        case 2 :
            m_languageJson.loadJsonFile("language/french/racebottompanel.json");
            break;
        default :
            break;
    }
    textConfiguration();
    initSpeedMeter();
}

void RaceBottomPanel::initSpeedMeter()
{
    m_speedMeter.setPosition(16, 24);
    m_speedMeter.setFillColor(sf::Color(0x004499FF));
}

 void RaceBottomPanel::loadTextures()
 {
    m_textureContaigner.loadAsset(textures::ID::supercarsfont, "graphics/bitmap_fonts/super_cars_16x16.png");
    m_textureContaigner.loadAsset(textures::ID::spritesheet, "graphics/sprite_sheet/sprite_sheet.png");
 }

void RaceBottomPanel::spriteConfiguration()
{
    for(auto i = 0; i < 5; ++i) {
        sf::Sprite sprite;
        sprite.setTexture(m_textureContaigner.getAsset(textures::ID::spritesheet));
        sprite.setTextureRect(sf::IntRect(0, 150, 46, 10));
        m_sprites[i] = std::make_unique<sf::Sprite>(sprite);
    }
    m_sprites[0]->setTextureRect(sf::IntRect(0, 0, 512, 40));
    m_sprites[0]->setPosition(0, 0);
    m_sprites[1]->setPosition(256, 24);
    m_sprites[2]->setPosition(320, 24);
    m_sprites[3]->setPosition(384, 24);
    m_sprites[4]->setPosition(448, 24);
}

void RaceBottomPanel::textConfiguration()
{

    m_font.setTexture(m_textureContaigner.getAsset(textures::ID::supercarsfont));
    m_font.setSize(16, 16);
    m_Text.setFont(&m_font);
    m_Text.setLineSpacing(2);
    m_Text.setText(m_languageJson.m_Root["text"].asString());
    m_Text.setPosition(16, 4);
}

void RaceBottomPanel::updateCarUsury(const float engine, const float body, const float fuel, const float tyres)
{
    m_sprites[1]->setTextureRect(sf::IntRect(0, 150, static_cast<int>(46 * engine), 10));
    m_sprites[2]->setTextureRect(sf::IntRect(0, 150, static_cast<int>(46 * body), 10));
    m_sprites[3]->setTextureRect(sf::IntRect(0, 150, static_cast<int>(46 * fuel), 10));
    m_sprites[4]->setTextureRect(sf::IntRect(0, 150, static_cast<int>(46 * tyres), 10));
}

void RaceBottomPanel::updateSpeedMeter(const float speed)
{
    if(speed > 0) { m_speedMeter.setSize(sf::Vector2f(80 * (speed / 260), 10.f)); }
    else { m_speedMeter.setSize(sf::Vector2f(0, 10.f)); }

}

void RaceBottomPanel::updatePosition(const unsigned int position, const size_t totalRacers)
{
    std::string text{m_Text.getText()};
    text.replace(37, 3, std::to_string(position) + "/" + std::to_string(totalRacers));
    m_Text.setText(text);
}

void RaceBottomPanel::updateLaps(const unsigned int lap, const unsigned int lapNb)
{
    std::string text{m_Text.getText()};
    text.replace(41, 3, std::to_string(lap) + "/" + std::to_string(lapNb));
    m_Text.setText(text);
}

void RaceBottomPanel::updateLap(const unsigned int lap)
{
    std::string text{m_Text.getText()};
    text.replace(41, 1, std::to_string(lap));
    m_Text.setText(text);
}

void RaceBottomPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& elem : m_sprites) {
        target.draw(*elem, states);
    }
    target.draw(m_Text, states);
    target.draw(m_speedMeter, states);
}
