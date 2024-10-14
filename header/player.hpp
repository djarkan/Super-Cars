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

#include "header/car.hpp"

class Player : public sf::NonCopyable
{
    public :
        enum                                        LevelDifficulty {Normal = 1, Medium, Hard};
        enum                                        PlayerType {Human, Computer, Network};
                                                    Player();
                                                    Player(const PlayerType playerType, const std::string name, unsigned int language, sf::RenderWindow& window);

        bool                                        isHuman() const;
        bool                                        isComputer() const;
        bool                                        isCarBroken() const;
        bool                                        isCarShifting() const;
        unsigned int                                getJoystickID() const;
        unsigned int                                getMoney() const;
        unsigned int                                getGameDifficulty() const;
        const std::string&                          getName() const;
        Car::Type                                   getCarType() const;
        sf::FloatRect                               getCarShape() const;
        float                                       getCarAngle() const;
        float                                       getCarSideAngle() const;
        float                                       getCarShiftingAngle() const;
        float                                       getCarSpeed() const;
        float                                       getCarTopRaceSpeed() const;
        float                                       getCarMaxSpeed() const;
        float                                       getCarSideSpeed() const;
        int                                         getCarAcceleration() const;
        float                                       getCarSpeedLimiter() const;
        sf::Vector2f                                getCarPosition() const;
        sf::Vector2f                                getCarCenter() const;
        int                                         getCarElevation() const;
        float                                       getCarBodyState() const;
        float                                       getCarEngineState() const;
        float                                       getCarTyresState() const;
        float                                       getCarFuelState() const;
        bool                                        getCarIsFrontMissileEquiped() const;
        bool                                        getCarIsRearMissileEquiped() const;
        bool                                        getCarIsHighSpeedKitEquiped() const;
        bool                                        getCarIsTurboChargerKitEquiped() const;
        bool                                        getCarIsRetroKitEquiped() const;
        bool                                        getCarIsSpinAssistKitEquiped() const;
        bool                                        getCarIsSideArmourKitEquiped() const;
        bool                                        getCarIsPowerSteeringKitEquiped() const;
        unsigned int                                getCarColor() const;
        const Car&                                  getCar() const;
        bool                                        getCarNearBridgeArea();
        sf::FloatRect                               getCarLocalBounds() const;
        sf::FloatRect                               getCarGlobalBounds() const;
        bool                                        getCarInArrivalAreaState() const;
        unsigned int                                getRaceCurrentLap() const;
        const sf::Vector2f&                         getCarLimit(const unsigned int index) const;
        Car::Interaction                            getCarInteractionType() const;
        sf::Time                                    getBestLapTime() const;
        sf::Time                                    getCurrentLapTime() const;
        unsigned int                                getRaceRanking() const;
        bool                                        getStartRanking() const;
        unsigned int                                getCheckedRankingAreaNumber() const;
        bool                                        getAnticheatWaypointState(const unsigned int index) const;
        bool                                        getcarInRankingAreaState() const;
        unsigned int                                getCarFrame() const;
        const sf::Vector2f&                         getCarCornerCoords(const unsigned int whatCorner) const;
        const sf::Vector2f&                         getCarOldPosition() const;
        const sf::Color&                            getRoadColor() const;
        sf::Time                                    getRaceTime() const;

        void                                        setHuman(PlayerType playerType);
        void                                        setJoystickID(sf::RenderWindow& window);
        void                                        setGameDifficulty();
        void                                        levelupGameDifficulty();
        void                                        setName(const std::string& name);
        void                                        setMoney(unsigned int money);
        void                                        setCarType(Car::Type type);
        void                                        setCarShape(sf::FloatRect rect);
        void                                        setCarAngle(float angle);
        void                                        setCarSpeed(float speed);
        void                                        setCarTopRaceSpeed(float speed);
        void                                        setCarSideSpeed(float sideSpeed);
        void                                        setCarMaxSpeed(float maxSpeed);
        void                                        setCarAcceleration(int acceleration);
        void                                        setCarSpeedLimiter(float speedLimiter);
        void                                        setCarOrigin(float offsetX, float offsetY);
        void                                        setCarElevation(int elevation);
        void                                        setCarBodyState(float body);
        void                                        setCarEngineState(float engine);
        void                                        setCarTyresState(float tyres);
        void                                        setCarFuelState(float fuel);
        void                                        setCarFrontMissile(bool frontMissile);
        void                                        setCarRearMissile(bool rearMissile);
        void                                        setCarHighSpeedKit(bool highSpeed);
        void                                        setCarRetroKit(bool retro);
        void                                        setCarTurboChargerKit(bool turboCharger);
        void                                        setCarSpinAssistKit(bool spinAssist);
        void                                        setCarSideArmourKit(bool sideArmour);
        void                                        setCarPowerSteeringKit(bool powerSteering);
        void                                        setCarColor(unsigned int color);
        void                                        setTexture(sf::Texture* carTexture);
        void                                        setCarPosition(const sf::Vector2f& position);
        void                                        setCarFrame();
        void                                        setCarNearBridgeArea(bool nearBridgeArea);
        void                                        setAnticheatWaypointValidated(const unsigned int index, bool validated);
        void                                        setCarInArrivalAreaState(bool state);
        void                                        setRaceCurrentLap( const unsigned int lap);
        void                                        setCarInSand(bool inSand);
        void                                        setCarInteraction(Car::Interaction type, float angle, unsigned int intensity, float speed);
        void                                        setBestLapTime(sf::Time lapTime);
        void                                        setRaceRanking(unsigned int ranking);
        void                                        setStartRanking(bool startRanking);
        void                                        setCheckedRankingAreaNumber(unsigned int areaNumber);
        void                                        setcarInRankingAreaState(bool startRanking);
        void                                        setRoadColor(const sf::Color color);

        void                                        moveCar();
        void                                        turnCar(Car::Direction direction);
        void                                        accelerate();
        void                                        decelerate();
        void                                        updateCarLimits();
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
        Car                                         m_car;
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
};
#endif // PLAYER_HPP
