#ifndef INTRO_HPP
#define INTRO_HPP

#include <array>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include "assetcontainer/assetcontainer.hpp"
#include "triple/triple.hpp"
#include "header/assetkey.hpp"
#include "jsonfile/jsonfile.hpp"
#include "header/inputs.hpp"
#include "header/players.hpp"
#include "music/music.hpp"

class Intro
{
    public :
                                                                Intro(unsigned int windowWidth, unsigned int windowHeight, unsigned int language);
        void                                                    loadAssets();
        void                                                    launchIntro();
        bool                                                    launchGame(mylib::Music& music);

    private :

        mylib::AssetContainer<textures::ID, sf::Texture>        m_textureContaigner;
        mylib::JsonFile                                         m_jsonConfig;
        sf::RenderWindow                                        m_window;
   //     std::array<std::pair<std::string, int32_t>, 9>          m_bestLapsTimes;
   //     std::array<mylib::Triple<std::string, int, int>, 6>     m_bestWinnersList;
        unsigned int                                            m_language;
        Players                                                 m_players;
        mylib::JsonFile                                         m_languageJson;
        sf::View                                                m_view;

        void                                                    gremlins();
        void                                                    magneticFields();
        void                                                    superCars();
        bool                                                    guyAndGirl();
        bool                                                    ronAndNancy();
        bool                                                    creditsOriginal();
        bool                                                    creditsAdditionnal();
        void                                                    loading(const sf::Int32 delay);
        void                                                    buildRonAndNancySpeech(std::array<std::string, 21>& speechArray);
        bool                                                    isIntroSkipped();
        void                                                    initView();
};
#endif // PLAYER_HPP
