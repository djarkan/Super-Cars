#ifndef OFFICE_HPP
#define OFFICE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "header/assetkey.hpp"
#include "assetcontainer/assetcontainer.hpp"
#include "button/simpleClickBox/simpleClickBox.hpp"
#include "text/bitmaptext/bitmapText.hpp"
#include "header/bottompanel.hpp"
#include "header/player.hpp"
#include "jsonfile/jsonfile.hpp"
#include "header/inputs.hpp"
#include "bitmap/animationPlayer/animationPlayer.hpp"

class Office {
    public:
                                                                Office(sf::RenderWindow& window, Player& player, BottomPanel& bottomPanel, const unsigned int language);
        void                                                    buy();


    private:
        sf::RenderWindow&                                       m_window;
        Player&                                                 m_player;
        BottomPanel&                                            m_bottomPanel;
        unsigned int                                            m_language;
        bool                                                    m_firstTimeIn;
        mylib::JsonFile                                         m_languageJson;
        mylib::AssetContainer<textures::ID, sf::Texture>        m_textureContaigner;
        sf::Sprite                                              m_background;
        sf::Sprite                                              m_visualSelector;
        sf::Sprite                                              m_blueCar;
        sf::Sprite                                              m_redCar;
        sf::Sprite                                              m_whiteCar;
        mylib::SimpleClickBox                                   m_door;
        mylib::BitmapFont                                       m_font;
        mylib::BitmapText                                       m_text;
        Inputs                                                  m_inputs;
        Command                                                 m_command;
        mylib::AnimationPlayer                                  m_animPlayer;
        sf::Sound                                               m_cashDrawerSound;
        sf::SoundBuffer                                         m_officeSoundBuffer;
        sf::View                                                m_topView;
        sf::View                                                m_bottomView;

        enum class                                              Mood{normal = 0, happy, unhappy, angry};

        void                                                    loadTextures();
        void                                                    setSprites();
        void                                                    loadAnimations();
        void                                                    selectVendorFace(sf::Sprite& vendorFace, Mood mood);
        void                                                    initViews();
};

#endif
