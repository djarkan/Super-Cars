#include "header/player.hpp"
#include "header/message.hpp"

#include "timer/timer.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

Player::Player() : m_playerType{ PlayerType::Computer }, m_gameDifficulty{ LevelDifficulty::Normal }, m_name{ "" }, m_money{ 5000 },
                    m_carInArrivalArea{false}, m_carInRankingArea{false}, m_checkedRankingAreaNumber{0}, m_currentRaceRanking{ 9 }, m_raceRanking{ 9 }, m_startRanking{false}
{

}

Player::Player(const PlayerType playerType, const std::string pseudo, unsigned int language, sf::RenderWindow& window) :    m_playerType{ playerType }, m_joystickID{ 99 },m_gameDifficulty { LevelDifficulty::Normal }, m_name{ pseudo }, 
                                                                                                                            m_language{ language }, m_money { 5000 }, m_carInArrivalArea{false}, m_carInRankingArea{false},
                                                                                                                            m_checkedRankingAreaNumber{0}, m_currentRaceRanking{ 9 }, m_raceRanking{9}, m_startRanking{false}
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

void Player::setGameDifficulty()
{
    if(m_name == "ODIE") {
        m_gameDifficulty = LevelDifficulty::Medium;
        setType(Car::Type::Vaug_Interceptor2);
        m_money = 20000;
    }
    else {
        if(m_name == "BIGC") {
            m_gameDifficulty = LevelDifficulty::Hard;
            setType(Car::Type::Retron_Parsec_Turbo5);
            m_money = 50000;
        }
        else {
            m_gameDifficulty = LevelDifficulty::Normal;
            setType(Car::Type::Taraco_Neoroder);
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

bool Player::getCarInArrivalAreaState() const
{
    return m_carInArrivalArea;
}

unsigned int Player::getRaceCurrentLap() const
{
    return m_raceCurrentLap;
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

void Player::setMoney(unsigned int money)
{
    m_money = money;
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
