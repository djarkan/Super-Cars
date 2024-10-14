#include "header/players.hpp"

#include <SFML/Graphics/Texture.hpp>

#include "text/bitmapfont/bitmapFont.hpp"
#include "text/bitmaptext/bitmapText.hpp"
#include "timer/timer.hpp"
#include "header/command.hpp"
#include "header/commandqueue.hpp"
#include "header/inputs.hpp"
#include "music/music.hpp"

Players::Players(sf::RenderWindow& window, unsigned int language) : m_language{ language }, m_window { window }, m_humanPlayer(Player::PlayerType::Human, "SOUT", m_language, m_window)  ////////////////////////////  REMETTRE SOUT APRES LES TESTS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
    if(!m_carsTexture.loadFromFile("graphics/cars/cars.png")) { std::cout << m_languageJson.m_Root["error"].asString() << std::endl; }
}

Players::~Players()
{
    if(m_players.size() > 0) {
        for(auto& elem : m_players) { delete(elem); }
    }
}

std::string Players::enterPseudo()
{
    std::string pseudo = m_humanPlayer.getName();
    sf::Sprite background;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("graphics/intro/enter_name.png");
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, 640, 400));
    sf::Sprite clearedGlyph;
    clearedGlyph.setTexture(backgroundTexture);
    clearedGlyph.setTextureRect(sf::IntRect(250, 335, 32, 32));
    mylib::BitmapFont font;
    sf::Texture glyphTexture;
    font.loadTexture("graphics/bitmap_fonts/golden_font_32x32.png");
    font.setSize(32, 32);
    mylib::BitmapText bitmapText;
    bitmapText.setFont(&font);
    mylib::Timer flashingLetter(100);
    unsigned int currentLetter{0};
    flashingLetter.start();
    bool clearGlyph{false};
    Inputs inputs(m_window);
    Command command;
    mylib::Timer commandTimer(200);
    commandTimer.start();
    while(command.action != CommandType::joystiskButtonPressed && command.action != CommandType::mouseLeftButtonPressed) {
        if(commandTimer.isTimeElapsed()) {
            inputs.readInput(m_humanPlayer.getJoystickID());
            commandTimer.restart();
        }
        if(inputs.isCommandAvailable()) { command = inputs.getInput(); }

        if(static_cast<int>(command.letter) == 27) { return ""; }
        m_window.clear();
        m_window.draw(background);
        bitmapText.setText(m_languageJson.m_Root["pseudo"][0].asString());
        sf::FloatRect bounds = bitmapText.getLocalBounds();
        bitmapText.setPosition(320.f - (bounds.width / 2.f), 242.f);
        m_window.draw(bitmapText);
        bitmapText.setText(m_languageJson.m_Root["pseudo"][1].asString());
        bounds = bitmapText.getLocalBounds();
        bitmapText.setPosition(320.f - (bounds.width / 2.f), 278.f);
        m_window.draw(bitmapText);
        bitmapText.setText(pseudo);
        bitmapText.setPosition(257, 335);
        m_window.draw(bitmapText);
        if(command.action == CommandType::joystiskMoved) {
            if(command.offsetX > 75) {
                currentLetter++;
                if(currentLetter > 3) { currentLetter = 0; }
            }
            if(command.offsetX < -75) {
                if(currentLetter == 0) { currentLetter = 3; }
                else { currentLetter--; }
            }
            if(command.offsetY < -75) {
                if(pseudo[currentLetter] == 'Z') { pseudo[currentLetter] = 'A';}
                else { pseudo[currentLetter] = static_cast<char>(pseudo[currentLetter] + 1); }
                bitmapText.setText(pseudo);
            }
            if(command.offsetY > 75) {
                if(pseudo[currentLetter] == 'A') { pseudo[currentLetter] = 'Z';}
                else { pseudo[currentLetter] = static_cast<char>(pseudo[currentLetter] - 1); }
                bitmapText.setText(pseudo);
            }
        inputs.clearCommand(command);
        }
        if(clearGlyph) {
            clearedGlyph.setPosition(257.f + (static_cast<float>(currentLetter) * 32.f), 335);
            m_window.draw(clearedGlyph);
        }
        if(flashingLetter.isTimeElapsed()) {
            if(clearGlyph) { clearGlyph = false; }
            else { clearGlyph = true; }
            flashingLetter.restart();
        }
        m_window.display();
    }
    m_window.draw(bitmapText);
    m_window.display();
    return pseudo;
}

Player& Players::getHumanPlayer()
{
    return m_humanPlayer;
}

unsigned int Players::getHumanJoystick() const
{
    return m_humanPlayer.getJoystickID();
}

sf::Vector2f Players::getHumanCarPosition() const
{
    return m_humanPlayer.getCarPosition();
}

unsigned int Players::getHumanRanking() const
{
    return m_humanPlayer.getRaceRanking();
}

float Players::getHumanTopRaceSpeed() const
{
    return m_humanPlayer.getCarTopRaceSpeed();
}

sf::Time Players::getHumanRaceTime() const
{
    return m_humanPlayer.getRaceTime();
}

const std::string& Players::getHumanName() const
{
    return m_humanPlayer.getName();
}

unsigned int Players::getGameDifficulty() const
{
    return m_humanPlayer.getGameDifficulty();
}

size_t Players::getRacerNumber() const
{
    return m_players.size();
}

sf::Vector2f Players::getCarPosition(const unsigned int index) const
{
    return m_players[index]->getCarPosition();
}

Player* Players::getPlayer(const size_t index)
{
    return m_players[index];
}

const Car& Players::getPlayerCar(unsigned int index)
{
    return m_players[index]->getCar();
}

unsigned int Players::getPlayerCarElevation(unsigned int index) const
{
   return m_players[index]->getCarElevation();
}

bool Players::setHumanName(bool won)
{
    std::string pseudo{enterPseudo()};
    if((pseudo.size() < 4)) { return false; }
    m_humanPlayer.setName(pseudo);
    if(!won) { m_humanPlayer.setGameDifficulty(); }
    return true;
}

 void Players::setHumanRanking(unsigned int ranking)
{
    m_humanPlayer.setRaceRanking(ranking);
}

void Players::buildPlayers(unsigned int completedRaces, unsigned int lastRaceRanking)
{
std::cout << "loading players files " << std::endl;
    mylib::JsonFile playersFileConfig("data/race/racers.json");
    mylib::JsonFile carsFileConfig("data/cars/cars.json");
    unsigned int AIracerNumber = playersFileConfig.m_Root["races"][completedRaces]["names"].size();
    unsigned int totalRacers{AIracerNumber + 1};
    unsigned int humanStartPlace{lastRaceRanking - 1};
    unsigned int AIindex{0};
std::cout << "freeing old players memory" << std::endl;
    if(m_players.size() > 0) {
int count{0};
        for(auto& elem : m_players) {
            if(!elem->isHuman()) { delete(elem); std::cout << "element " << count  << " deleted" << std::endl; ++count; }
        }
    }
std::cout << "resizing vect " << std::endl;
    m_players.resize(0);
std::cout << "vect is empty " << std::endl;
    for(unsigned int index = 0; index < totalRacers; ++index) {
        Player* ptr = new Player;
        if(index == humanStartPlace) {
            if(m_humanPlayer.getCarIsHighSpeedKitEquiped()) { m_humanPlayer.setCarMaxSpeed(carsFileConfig.m_Root["model"][m_humanPlayer.getCarType()]["maxSpeedKit"].asFloat()); }
            else { m_humanPlayer.setCarMaxSpeed(carsFileConfig.m_Root["model"][m_humanPlayer.getCarType()]["maxSpeed"].asFloat()); }
            if(m_humanPlayer.getCarIsTurboChargerKitEquiped()) { m_humanPlayer.setCarAcceleration(3); }
            else { m_humanPlayer.setCarAcceleration(2); }
            m_humanPlayer.setCarSpeedLimiter(1);
            m_humanPlayer.setRaceCurrentLap(1);
            m_humanPlayer.setCarSpeed(0);
            m_humanPlayer.setRaceRanking(totalRacers - index);
            ptr = &m_humanPlayer;
            m_players.emplace(m_players.begin(), ptr);
        }
        else {
            ptr->setName(playersFileConfig.m_Root["races"][completedRaces]["names"][AIindex].asString());
            ptr->setCarType(static_cast<Car::Type>(playersFileConfig.m_Root["races"][completedRaces]["cartype"][AIindex].asInt()));
            ptr->setCarSpeedLimiter(playersFileConfig.m_Root["races"][completedRaces]["carspeedlimiter"][AIindex].asFloat());
            ptr->setCarMaxSpeed(carsFileConfig.m_Root["model"][ptr->getCarType()]["maxSpeed"].asFloat());
            ptr->setCarColor(0);
            ptr->setHuman(Player::PlayerType::Computer);
            ptr->setCarSpeed(0);
            ptr->setRaceCurrentLap(1);
            ptr->setRaceRanking(totalRacers - index);
            m_players.emplace(m_players.begin(), ptr);
            ++AIindex;
        }
    }
    for(auto& elem : m_players) {
        elem->setBestLapTime(sf::milliseconds(60000));
        elem->resetRaceTime();
        elem->resetAnticheatWaypointValidation();
        elem->setCarSideSpeed(0);
        elem->setCarTopRaceSpeed(0); 
        elem->setcarInRankingAreaState(false);
        elem->setStartRanking(false);
        elem->setTexture(&m_carsTexture);
        elem->setCarShape(sf::FloatRect(0, 0, carsFileConfig.m_Root["model"][elem->getCarType()]["width"].asFloat(), carsFileConfig.m_Root["model"][elem->getCarType()]["heigth"].asFloat()));
        elem->setCarOrigin(carsFileConfig.m_Root["model"][elem->getCarType()]["width"].asFloat() / 2, carsFileConfig.m_Root["model"][elem->getCarType()]["heigth"].asFloat() / 2);
    }
}

void Players::levelupGameDifficulty()              // dans race ??????????????????????? --->> dans game qui connait le nb de courses deja faire
{
    m_humanPlayer.levelupGameDifficulty();
}


