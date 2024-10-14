#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <array>
#include <vector>


#include "assetcontainer/assetcontainer.hpp"
#include "button/button/button.hpp"
#include "button/simpleclickbox/simpleclickbox.hpp"
#include "button/complexClickBox/complexClickBox.hpp"
#include "jsonfile/jsonfile.hpp"
#include "header/assetkey.hpp"
#include "header/inputs.hpp"
#include "header/players.hpp"
#include "music/music.hpp"

#include "header/bottompanel.hpp"

class Game {
    public:
                                                                        Game(sf::RenderWindow& window, unsigned int language, Players& players);
        bool                                                            launch(mylib::Music& music);
        void                                                            loadTextures();
        void                                                            loading(const sf::Int32 delay, const std::string& text);
        bool                                                            setHandCursor();

    private:
        sf::RenderWindow&                                               m_window;
        mylib::AssetContainer<textures::ID, sf::Texture>                m_textureContaigner;
        unsigned int                                                    m_gameLevel;
        unsigned int                                                    m_language;
        std::array<bool, 9>                                             m_raceListState;
        std::array<std::unique_ptr<mylib::SimpleClickBox>, 2>           m_simpleClickBoxes;
        std::array<std::unique_ptr<mylib::ComplexClickBox>, 3>          m_ComplexClickBoxes;
        std::array<std::unique_ptr<mylib::Button>, 9>                   m_racesButtonsArray;
        Players&                                                        m_players;
        Inputs                                                          m_inputs;
        Command                                                         m_command;
        mylib::JsonFile                                                 m_languageJson;
        sf::Cursor                                                      m_handCursor;
        sf::Image                                                       m_handCursorImage;
        BottomPanel                                                     m_bottomPanel;
        unsigned int                                                    m_completedRaces;
        unsigned int                                                    m_lastRaceRanking;
        bool                                                            m_clockwiseRaceRotation;
        sf::View                                                        m_topView;
        sf::View                                                        m_bottomView;

        void                                                            drawRacePannel();
        void                                                            loadClickBoxes();
        void                                                            loadButtons();
        void                                                            loadSimpleClickBoxes();
        void                                                            loadComplexClickBoxes();
        int                                                             checkButtons();
        unsigned int                                                    race(const unsigned int whatRace);
        void                                                            initViews();
        int                                                             checkHoveredButton();

};

#endif
