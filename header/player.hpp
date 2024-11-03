#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Joystick.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include <string>

#include "header/entity.hpp"
#include "header/car.hpp"

class Player : public Entity
{
    public :
        enum                                        LevelDifficulty {Normal = 1, Medium, Hard};
        enum                                        PlayerType {Human, Computer, Network};
                                                    Player();
                                                    Player(const PlayerType playerType, const std::string name, unsigned int language, sf::RenderWindow& window);

        bool                                        isHuman() const;
        bool                                        isComputer() const;
        unsigned int                                getJoystickID() const;
        unsigned int                                getMoney() const;
        unsigned int                                getGameDifficulty() const;
        const std::string&                          getName() const;
        bool                                        getCarInArrivalAreaState() const;
        unsigned int                                getRaceCurrentLap() const;
        sf::Time                                    getBestLapTime() const;
        sf::Time                                    getCurrentLapTime() const;
        unsigned int                                getRaceRanking() const;
        bool                                        getStartRanking() const;
        unsigned int                                getCheckedRankingAreaNumber() const;
        bool                                        getAnticheatWaypointState(const unsigned int index) const;
        bool                                        getcarInRankingAreaState() const;
        const sf::Color&                            getRoadColor() const;
        sf::Time                                    getRaceTime() const;

        void                                        setHuman(PlayerType playerType);
        void                                        setJoystickID(sf::RenderWindow& window);
        void                                        setGameDifficulty();
        void                                        levelupGameDifficulty();
        void                                        setName(const std::string& name);
        void                                        setMoney(unsigned int money);
        void                                        setAnticheatWaypointValidated(const unsigned int index, bool validated);
        void                                        setCarInArrivalAreaState(bool state);
        void                                        setRaceCurrentLap( const unsigned int lap);
        void                                        setBestLapTime(sf::Time lapTime);
        void                                        setRaceRanking(unsigned int ranking);
        void                                        setStartRanking(bool startRanking);
        void                                        setCheckedRankingAreaNumber(unsigned int areaNumber);
        void                                        setcarInRankingAreaState(bool startRanking);
        void                                        setRoadColor(const sf::Color color);

        bool                                        areAllAnticheatWaypointValidated();
        void                                        resetAnticheatWaypointValidation();
        void                                        startLapTimeClock();
        void                                        resetRaceTime();
        void                                        updateRaceTime(const sf::Time elapsedTime);

    private :
        PlayerType                                  m_playerType;
        unsigned int                                m_joystickID;
        LevelDifficulty                             m_gameDifficulty;               //   repercuter sur les autres en muti
        std::string                                 m_name;
        unsigned int                                m_language;
        unsigned int                                m_money;
       // Car                                         m_car;
       // Entity                                      m_entity;
        std::array<bool, 3>                         m_anticheatWaypoint;
        bool                                        m_carInArrivalArea;
        unsigned int                                m_raceCurrentLap;
        unsigned int                                m_currentRaceRanking;
        sf::Clock                                   m_lapClock;
        sf::Time                                    m_RaceTime;
        sf::Time                                    m_bestLapTime;
        unsigned int                                m_raceRanking;
        bool                                        m_carInRankingArea;
        unsigned int                                m_checkedRankingAreaNumber;
        bool                                        m_startRanking;
        sf::Color                                   m_roadColor;

        //virtual void			                    draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif // PLAYER_HPP
