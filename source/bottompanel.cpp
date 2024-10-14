#include "header/bottompanel.hpp"
#include "header/car.hpp"

#include <iostream>

BottomPanel::BottomPanel(Player& player, sf::RenderWindow& window, unsigned int language) : m_player{player}, m_window{window}, m_language{language}, m_font(16,16)
{
    loadTextures();
    spriteConfiguration();
    switch(language) {
        case 0 :
            m_languageJson.loadJsonFile("language/english/bottompanel.json");
            break;
        case 1:
            m_languageJson.loadJsonFile("language/usa/bottompanel.json");
            break;
        case 2 :
            m_languageJson.loadJsonFile("language/french/bottompanel.json");
            break;
        default :
            break;
    }
    textConfiguration();
}

 void BottomPanel::loadTextures()
 {
    m_textureContaigner.loadAsset(textures::ID::supercarsfont, "graphics/bitmap_fonts/super_cars_16x16.png");
    m_textureContaigner.loadAsset(textures::ID::spritesheet, "graphics/sprite_sheet/sprite_sheet.png");
 }

void BottomPanel::spriteConfiguration()
{
    for(auto i = 0; i < 5; ++i) {
        sf::Sprite sprite;
        sprite.setTexture(m_textureContaigner.getAsset(textures::ID::spritesheet));
        sprite.setTextureRect(sf::IntRect(0, 150, 46, 10));
        m_sprites[i] = std::make_unique<sf::Sprite>(sprite);
    }
    m_sprites[0]->setTextureRect(sf::IntRect(0, 1940, 640, 40));
    m_sprites[0]->setPosition(0, 0);
    m_sprites[1]->setPosition(384, 24);
    m_sprites[2]->setPosition(448, 24);
    m_sprites[3]->setPosition(512, 24);
    m_sprites[4]->setPosition(576, 24);
    updateUsury();
}

void BottomPanel::textConfiguration()
{

    m_font.setTexture(m_textureContaigner.getAsset(textures::ID::supercarsfont));
    m_font.setSize(16, 16);
    m_Text.setFont(&m_font);
    std::string text = m_languageJson.m_Root["bottomScreen"]["text"].asString();
    std::string money;
    if(m_language < 2) {  money = m_languageJson.m_Root["bottomScreen"]["currency"].asString() + std::to_string(m_player.getMoney()); }
    else { money = std::to_string(m_player.getMoney()) + m_languageJson.m_Root["bottomScreen"]["currency"].asString(); }
    while(money.size() < 7) { money += ' '; }
    text.replace(39, 7, money);
    std::string model = m_languageJson.m_Root["bottomScreen"]["carModel"][static_cast<unsigned int>(m_player.getCarType())].asString();
    text.replace(47, 14, model);
    m_Text.setText(text);
    m_Text.setPosition(16, 4);
}

void BottomPanel::updateMoney()
{
    std::string text{m_Text.getText()};
    std::string money;
    if(m_language < 2) {  money = m_languageJson.m_Root["bottomScreen"]["currency"].asString() + std::to_string(m_player.getMoney()); }
    else { money = std::to_string(m_player.getMoney()) + m_languageJson.m_Root["bottomScreen"]["currency"].asString(); }
    while(money.size() < 7) { money += " "; }
    text.replace(39, 7, money);
    m_Text.setText(text);
}

void BottomPanel::updateCarModel(Car::Type type)
{
    std::string text{m_Text.getText()};
    text.replace(47, 24, "                        ");
    std::string model = m_languageJson.m_Root["bottomScreen"]["carModel"][static_cast<unsigned int>(type)].asString();
    text.replace(47, model.size(), model);
}

void BottomPanel::updateUsury()
{
    m_sprites[1]->setTextureRect(sf::IntRect(0, 150, static_cast<int>(46 * m_player.getCarEngineState()), 10));
    m_sprites[2]->setTextureRect(sf::IntRect(0, 150, static_cast<int>(46 * m_player.getCarBodyState()), 10));
    m_sprites[3]->setTextureRect(sf::IntRect(0, 150, static_cast<int>(46 * m_player.getCarFuelState()), 10));
    m_sprites[4]->setTextureRect(sf::IntRect(0, 150, static_cast<int>(46 * m_player.getCarTyresState()), 10));
}

void BottomPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& elem : m_sprites) {
        target.draw(*elem, states);
    }
    target.draw(m_Text, states);
}
