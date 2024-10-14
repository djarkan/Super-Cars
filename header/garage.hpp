#ifndef GARAGE_HPP
#define GARAGE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "header/assetkey.hpp"
#include "assetcontainer/assetcontainer.hpp"
#include "button/simpleClickBox/simpleClickBox.hpp"
#include "header/car.hpp"
#include "header/player.hpp"
#include "text/bitmaptext/bitmapText.hpp"
#include "header/bottompanel.hpp"
#include "jsonfile/jsonfile.hpp"
#include "header/inputs.hpp"
#include "header/command.hpp"

class Garage  {
    public :
                                                                Garage(sf::RenderWindow& window, Player& player, BottomPanel& bottomPanel, const unsigned int language);
        void                                                    carUpdate();
        int                                                     checkClickboxes();
        void                                                    setInitGarage(bool init);
        void                                                    action(int choice, Player& player);

    private :
        sf::RenderWindow&                                       m_window;
        unsigned int                                            m_language;
        sf::Sprite                                              m_background;
        sf::Sprite                                              m_smiling;
        mylib::AssetContainer<textures::ID, sf::Texture>        m_textureContaigner;
        sf::Sound                                               m_cashDrawerSound;
        sf::SoundBuffer                                         m_garageSoundBuffer;
        sf::SoundBuffer                                         m_soundbuffer;
        sf::Sound                                               m_whatryoudoing;
        std::array<std::unique_ptr<mylib::SimpleClickBox>, 19>  m_clickBoxes;
        std::array<bool, 8>                                     m_OptionsBought;
        std::array<unsigned int, 12>                            m_prices;
        BottomPanel&                                            m_bottomPanel;
        bool                                                    m_switch;
        bool                                                    m_inGarage;
        mylib::JsonFile                                         m_coordsJson;
        mylib::JsonFile                                         m_languageJson;
        bool                                                    m_initGrage;
        mylib::BitmapFont                                       m_font;
        mylib::BitmapText                                       m_text;
        Player&                                                 m_player;
        Inputs                                                  m_inputs;
        Command                                                 m_command;
        sf::View                                                m_topView;
        sf::View                                                m_bottomView;

        void                                                    loadClickBoxes();
        void                                                    loadTextures();
        void                                                    setBackground();
        void                                                    definePrices();
        void                                                    drawlabels();
        void                                                    drawPrices();
        void                                                    whatareyoudoing();
        void                                                    initViews();
};
#endif
