#ifndef RACEBOTTOMPANEL_HPP
#define RACEBOTTOMPANEL_HPP

#include <iostream>
#include <string>
#include <array>
#include <memory.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "header/car.hpp"
#include "header/player.hpp"
#include "text/bitmaptext/bitmapText.hpp"
#include "jsonfile/jsonfile.hpp"
#include "header/assetkey.hpp"
#include "assetContainer/assetContainer.hpp"

class RaceBottomPanel : public sf::Drawable
{
    public :
                                                                RaceBottomPanel(const unsigned int language);
        void                                                    loadTextures();
        void                                                    spriteConfiguration();
        void                                                    initSpeedMeter();
        void                                                    textConfiguration();
        void                                                    updateSpeedMeter(const float speed);
        void                                                    updateCarUsury(const float engine, const float body, const float fuel, const float tyres);
        void                                                    updatePosition(const unsigned int position, const size_t totalRacers);
        void                                                    updateLaps(const unsigned int lap, const unsigned int lapNb);
        void                                                    updateLap(const unsigned int lap);

    private:
        unsigned int                                            m_language;
        mylib::AssetContainer<textures::ID, sf::Texture>        m_textureContaigner;
        std::array<std::unique_ptr<sf::Sprite>, 5>              m_sprites;
        mylib::BitmapText                                       m_Text;
        mylib::BitmapFont                                       m_font;
        mylib::JsonFile                                         m_languageJson;
        sf::RectangleShape                                      m_speedMeter;

        virtual void                                            draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif
