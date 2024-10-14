#ifndef RACEBOTTOMPANEL_HPP
#define RACEBOTTOMPANEL_HPP

#include <iostream>
#include <string>
#include <array>
#include <memory.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "header/car.hpp"
#include "header/player.hpp"
#include "text/bitmaptext/bitmapText.hpp"
#include "jsonfile/jsonfile.hpp"
#include "header/assetkey.hpp"
#include "assetContainer/assetContainer.hpp"

class RaceBottomPanel : public sf::Drawable
{
    public :
                                                                BottomPanel(Player& player, sf::RenderWindow& window, unsigned int language);
        void                                                    loadTextures();
        void                                                    spriteConfiguration();
        void                                                    textConfiguration();
        void                                                    updateCarModel(Car::Type type);
        void                                                    updateMoney();
        void                                                    updateUsury();
        void			                                        draw();

    private:
        Player&                                                 m_player;
        sf::RenderWindow&                                       m_window;
        unsigned int                                            m_language;
        mylib::AssetContainer<textures::ID, sf::Texture>        m_textureContaigner;
        std::array<std::unique_ptr<sf::Sprite>, 5>              m_sprites;
        mylib::BitmapText                                       m_Text;
        mylib::BitmapFont                                       m_font;
        mylib::JsonFile                                         m_languageJson;

        virtual void                                            draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif
