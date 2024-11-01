#include "header/player.hpp"
#include "header/message.hpp"

#include "timer/timer.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

Player::Player() : m_playerType{ PlayerType::Computer }, m_gameDifficulty{ LevelDifficulty::Normal }, m_name{ "" }, m_money{ 5000 }, m_car(),
                    m_carInArrivalArea{false}, m_carInRankingArea{false}, m_checkedRankingAreaNumber{0}, m_startRanking{false}
{

}

Player::Player(const PlayerType playerType, const std::string pseudo, unsigned int language, sf::RenderWindow& window) :    m_playerType{ playerType }, m_joystickID{ 99 },m_gameDifficulty { LevelDifficulty::Normal }, m_name{ pseudo }, 
                                                                                                                            m_language{ language }, m_money { 5000 }, m_car(), m_carInArrivalArea{false}, m_carInRankingArea{false}, 
                                                                                                                            m_checkedRankingAreaNumber{0}, m_startRanking{false}
{
    if(m_playerType == PlayerType::Human) { setJoystickID(window); }
}

bool Player::isHuman() const
{
    return m_playerType == PlayerType::Human;
}

bool Player::isComputer() const
{
    return m_playerType == PlayerType::Computer;
}

bool Player::isCarBroken() const
{
    return m_car.isBroken();
}

bool Player::isCarShifting() const
{
    return m_car.isShifting();
}

void Player::setGameDifficulty()
{
    if(m_name == "ODIE") {
        m_gameDifficulty = LevelDifficulty::Medium;
        setCarType(Car::Type::Vaug_Interceptor2);
        m_money = 20000;
    }
    else {
        if(m_name == "BIGC") {
            m_gameDifficulty = LevelDifficulty::Hard;
            setCarType(Car::Type::Retron_Parsec_Turbo5);
            m_money = 50000;
        }
        else {
            m_gameDifficulty = LevelDifficulty::Normal;
            setCarType(Car::Type::Taraco_Neoroder);
            if(m_name == "RICH") { m_money = 500000; }
            else { m_money = 5000; }
        }
    }
}

void Player::levelupGameDifficulty()
{
    if(m_gameDifficulty == LevelDifficulty::Normal) { m_gameDifficulty = LevelDifficulty::Medium; }
    else {
        if(m_gameDifficulty == LevelDifficulty::Medium) { m_gameDifficulty = LevelDifficulty::Hard; }
    }
}

void Player::setJoystickID(sf::RenderWindow& window)
{
    sf::View view;
    view.setSize(sf::Vector2f(640.f, 400.f));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    view.setCenter(sf::Vector2f(320, 200));
    window.setView(view);
    unsigned int pluggedJoystickNumber{0};
    mylib::Timer duration(100);
    duration.start();
    while(pluggedJoystickNumber == 0) {
        sf::Joystick::update();
        for (auto i = 0; i < sf::Joystick::Count; ++i) {
            if (sf::Joystick::isConnected(i)) { ++pluggedJoystickNumber; }
        }
        sf::Event event;
        if (pluggedJoystickNumber == 0) {
            Message message(m_language, Message::Messages::NoJoystick);
            window.clear();
            window.draw(message);
            window.display();
            while (!duration.isTimeElapsed()) {
                sf::sleep(sf::milliseconds(10));
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::JoystickConnected) {
                        ++pluggedJoystickNumber;
                        m_joystickID = 0;
                    }
                }
            }
            duration.restart();
        }
        if(pluggedJoystickNumber > 1) {
            bool JoystickButtonPressed{false};
            while (!JoystickButtonPressed) {
                sf::Joystick::update();
                Message message(m_language, Message::Messages::sevaralJoystick);
                window.clear();
                window.draw(message);
                window.display();
                while (!duration.isTimeElapsed())
                    sf::sleep(sf::milliseconds(10));
                duration.restart();
                sf::Joystick::update();
                for (unsigned int id = 0; id < pluggedJoystickNumber; ++id) {
                    for (auto button = 0; button < sf::Joystick::ButtonCount; ++button) {
                        if (sf::Joystick::isButtonPressed(id, button)) {
                            JoystickButtonPressed = true;
                            m_joystickID = id;
                        }
                    }
                }
            }
        }
        if (pluggedJoystickNumber == 1) { m_joystickID = 0; }
    }
}

void Player::setName(const std::string& name)
{
    m_name = name;
}

unsigned int Player::getMoney() const
{
    return m_money;
}

const std::string& Player::getName() const
{
    return m_name;
}

unsigned int Player::getJoystickID() const
{
    return m_joystickID;
}

unsigned int Player::getGameDifficulty() const
{
    return m_gameDifficulty;
}

Car::Type Player::getCarType() const
{
    return m_car.getType();
}

float Player::getCarAngle() const
{
    return m_car.getAngle();
}

float Player::getCarSideAngle() const
{
    return m_car.getSideAngle();
}

float Player::getCarShiftingAngle() const
{
    return m_car.getShiftingAngle();
}

float Player::getCarSpeed() const
{
    return m_car.getSpeed();
}

float Player::getCarTopRaceSpeed() const
{
    return m_car.getTopRaceSpeed();
}

float Player::getCarMaxSpeed() const
{
    return m_car.getMaxSpeed();
}

float Player::getCarSideSpeed() const
{
    return m_car.getSideSpeed();
}

int Player::getCarAcceleration() const
{
    return m_car.getAcceleration();
}

float Player::getCarSpeedLimiter() const
{
   return m_car.getSpeedLimiter();
}

sf::Vector2f Player::getCarPosition() const
{
    return m_car.getPosition();
}

sf::Vector2f Player::getCarCenter() const
{
    return m_car.getCenter();
}

sf::FloatRect Player::getCarShape() const
{
    return m_car.getShape();
}

int Player::getCarElevation() const
{
    return m_car.getElevation();
}

float Player::getCarBodyState() const
{
    return m_car.getBodyState();
}

float Player::getCarEngineState() const
{
    return m_car.getEngineState();
}

float Player::getCarTyresState() const
{
    return m_car.getTyresState();
}

float Player::getCarFuelState() const
{
    return m_car.getFuelState();
}

bool Player::getCarIsFrontMissileEquiped() const
{
    return m_car.getIsFrontMissileEquiped();
}

bool Player::getCarIsRearMissileEquiped() const
{
    return m_car.getIsRearMissileEquiped();
}

bool Player::getCarIsHighSpeedKitEquiped() const
{
    return m_car.getIsHighSpeedKitEquiped();
}

bool Player::getCarIsTurboChargerKitEquiped() const
{
    return m_car.getIsTurboChargerKitEquiped();
}

bool Player::getCarIsSpinAssistKitEquiped() const
{
    return m_car.getIsSpinAssistKitEquiped();
}

bool Player::getCarIsRetroKitEquiped() const
{
    return m_car.getIsRetrorKitEquiped();
}

bool  Player::getCarIsSideArmourKitEquiped() const
{
    return m_car.getIsSideArmourKitEquiped();
}

bool Player::getCarIsPowerSteeringKitEquiped() const
{
    return m_car.getIsPowerSteeringKitEquiped();
}

unsigned int Player::getCarColor() const
{
    return m_car.getColor();
}

const Car& Player::getCar() const
{
    return m_car;
}

bool Player::getCarNearBridgeArea()
{
    return m_car.getNearBridgeArea();
}

sf::FloatRect Player::getCarLocalBounds() const
{
    return m_car.getLocalBounds();
}

sf::FloatRect Player::getCarGlobalBounds() const
{
    return m_car.getGlobalBounds();
}

bool Player::getCarInArrivalAreaState() const
{
    return m_carInArrivalArea;
}

unsigned int Player::getRaceCurrentLap() const
{
    return m_raceCurrentLap;
}

const sf::Vector2f& Player::getCarLimit(const unsigned int index) const
{
    return m_car.getCarLimit(index);
}

Car::Interaction Player::getCarInteractionType() const
{
    return m_car.getInteractionType();
}

sf::Time Player::getBestLapTime() const
{
    return m_bestLapTime;
}

sf::Time Player::getCurrentLapTime() const
{
    return m_lapClock.getElapsedTime();
}

unsigned int Player::getRaceRanking() const
{
    return m_raceRanking;
}

bool Player::getStartRanking() const
{
    return m_startRanking;
}

unsigned int Player::getCheckedRankingAreaNumber() const
{
    return m_checkedRankingAreaNumber;
}

bool Player::getAnticheatWaypointState(const unsigned int index) const
{
    return m_anticheatWaypoint[index];
}

bool Player::getcarInRankingAreaState() const
{
    return m_carInRankingArea;
}

unsigned int Player::getCarFrame() const
{
    return m_car.getFrame();
}

const sf::Vector2f& Player::getCarCornerCoords(const unsigned int whatCorner) const
{
    return m_car.getCornerCoords(whatCorner);
}

const sf::Vector2f& Player::getCarOldPosition() const
{
    return m_car.getOldPosition();
}

const sf::Color& Player::getRoadColor() const
{
    return m_roadColor;
}

sf::Time Player::getRaceTime() const 
{
    return m_RaceTime;
}

                                /////////////////////////////////////////////////////////////  set

void Player::setHuman(PlayerType playerType)
{
    m_playerType = playerType;
}

void Player::setCarType(Car::Type type)
{
    m_car.setType(type);
}

void Player::setMoney(unsigned int money)
{
    m_money = money;
}

void Player::setCarShape(sf::FloatRect rect)
{
    m_car.setShape(rect);
}

void Player::setCarOrigin(float offsetX, float offsetY)
{
    m_car.setOrigin(offsetX, offsetY);
}

void  Player::setCarAngle(float angle)
{
    m_car.setAngle(angle);
}

void Player::setCarSpeed(float speed)
{
    m_car.setSpeed(speed);
}

void Player::setCarTopRaceSpeed(float speed)
{
    m_car.setTopRaceSpeed(speed);
}

void Player::setCarSideSpeed(float sideSpeed)
{
    m_car.setSideSpeed(sideSpeed);
}

void Player::setCarMaxSpeed(float maxSpeed)
{
    m_car.setMaxSpeed(maxSpeed);
}

void Player::setCarAcceleration(int acceleration)
{
    m_car.setAcceleration(acceleration);
}

void Player::setCarElevation(int elevation)
{
    m_car.setElevation(elevation);
}

void Player::setCarSpeedLimiter(float speedLimiter)
{
    m_car.setSpeedLimiter(speedLimiter);
}

void Player::setCarBodyState(float body)
{
    m_car.setBodyState(body);
}

void Player::setCarEngineState(float engine)
{
    m_car.setEngineState(engine);
}

void Player::setCarTyresState(float tyres)
{
    m_car.setTyresState(tyres);
}

void Player::setCarFuelState(float fuel)
{
    m_car.setFuelState(fuel);
}

void Player::setCarFrontMissile(bool frontMissile)
{
    m_car.setIsFrontMissileEquiped(frontMissile);
}

void Player::setCarRearMissile(bool rearMissile)
{
    m_car.setIsRearMissileEquiped(rearMissile);
}

void Player::setCarHighSpeedKit(bool highSpeed)
{
    m_car.setIsHighSpeedKitEquiped(highSpeed);
}

void Player::setCarTurboChargerKit(bool turboCharger)
{
    m_car.setIsTurboChargerKitEquiped(turboCharger);
}

void Player::setCarSpinAssistKit(bool spinAssist)
{
    m_car.setIsSpinAssistKitEquiped(spinAssist);
}

void Player::setCarRetroKit(bool retro)
{
     m_car.setIsRetroKitEquiped(retro);
}

void  Player::setCarSideArmourKit(bool sideArmour)
{
    m_car.setIsSideArmourKitEquiped(sideArmour);
}

void Player::setCarPowerSteeringKit(bool powerSteering)
{
    m_car.setIsPowerSteeringKitEquiped(powerSteering);
}

void Player::setCarColor(unsigned int color)
{
    m_car.setColor(color);
}

void Player::setTexture(sf::Texture* carTexture)
{
    m_car.setTexture(carTexture);
}

void Player::setCarPosition(const sf::Vector2f& position)
{
    m_car.setPosition(position);
}

void Player::setCarFrame()
{
    m_car.setFrame();
}

void Player::setCarNearBridgeArea(bool nearBridgeArea)
{
    m_car.setNearBridgeArea(nearBridgeArea);
}

void Player::setAnticheatWaypointValidated(const unsigned int index, bool validated)
{
    m_anticheatWaypoint[index] = validated;
}

void Player::setCarInArrivalAreaState(bool state)
{
    m_carInArrivalArea = state;
}

void Player::setRaceCurrentLap(const unsigned int lap)
{
    m_raceCurrentLap = lap;
}

void Player::setCarInSand(bool inSand)
{
    m_car.setInSand(inSand);
}

void Player::setCarInteraction(Car::Interaction type, float angle, unsigned int intensity, float speed)
{
    m_car.setInteraction(type, angle, intensity, speed);
}

void Player::setBestLapTime(sf::Time lapTime)
{
    m_bestLapTime = lapTime;
    m_lapClock.restart();
}

void Player::setRaceRanking(unsigned int ranking)
{
    m_raceRanking = ranking;
}

void Player::setStartRanking(bool startRanking )
{
    m_startRanking = startRanking;
}

void Player::setCheckedRankingAreaNumber(unsigned int areaNumber)
{
    m_checkedRankingAreaNumber = areaNumber;
}

void Player::setcarInRankingAreaState(bool carInRankingArea)
{
    m_carInRankingArea = carInRankingArea;
}

void Player::setRoadColor(const sf::Color color)
{
    m_roadColor = color;
}

void Player::moveCar()
{
    m_car.move();
}

void Player::turnCar(Car::Direction direction)
{
    m_car.turn(direction);
}

void Player::accelerate()
{
    m_car.accelerate();
}

void Player::decelerate()
{
    m_car.decelerate();
}

void Player::updateCarLimits()
{
    m_car.updateCarLimits();
}

bool Player::areAllAnticheatWaypointValidated()
{
    bool check{true};
    for(auto elem : m_anticheatWaypoint) {
        check &= elem;
    }
    return check;
}

void Player::resetAnticheatWaypointValidation()
{
    for(auto& elem : m_anticheatWaypoint) {
        elem = false;
    }
}

void Player::startLapTimeClock()
{
    m_lapClock.restart();
}

void Player::resetRaceTime()
{
    m_RaceTime *= 0.f;
}

void Player::updateRaceTime(const sf::Time elapsedTime)
{
    m_RaceTime += elapsedTime;
}