#include "header/race.hpp"

#include <string>
#include <array>
#include <algorithm>
#include <cmath>

#include <SFML/Graphics/Sprite.hpp>

#include "timer/timer.hpp"
#include "header/inputs.hpp"
#include "header/command.hpp"
#include "random/random.hpp"
#include "header/players.hpp"

extern std::array<std::pair<std::string, sf::Time>, 9>          bestLapsTimes;
extern std::array<mylib::Triple<std::string, int, int>, 7>      bestWinnersList;

unsigned int prizeMoneyComputing(const unsigned int levelDifficulty, const unsigned int ranking)
{
    switch (levelDifficulty) {
    case Player::LevelDifficulty::Normal:
        if (ranking == 1) { return 20000; }
        if (ranking == 2) { return 12000; }
        if (ranking == 3) { return 5000; }
        break;
    case Player::LevelDifficulty::Medium:
        if (ranking == 1) { return 25000; }
        if (ranking == 2) { return 15000; }
        if (ranking == 3) { return 8000; }
        break;
    case Player::LevelDifficulty::Hard:
        if (ranking == 1) { return 30000; }
        if (ranking == 2) { return 20000; }
        if (ranking == 3) { return 10000; }
        break;
    default:
        break;
    }
    return 0;
}

Race::Race(sf::RenderWindow& window, const unsigned int trackNb, Players& players, const unsigned int language, const bool clockwiseRaceRotation) :
                                                                                    m_window(window), m_clockwiseRaceRotation{clockwiseRaceRotation}, m_trackData(trackNb + 1, clockwiseRaceRotation),
                                                                                    m_textureContaigner(), m_trackNb{trackNb}, m_players{players}, m_language{language}, m_raceBottomPanel(m_language),
                                                                                    m_currentLap{1}, m_raceLapsNb{5}, m_arrivedRacersNumber{0}
{
    loadTextures(trackNb);
    loadSounds();
std::cout << "race files loaded " << std::endl;
}

void Race::loadTextures(const unsigned int trackNb)
{
    std::string rotation{""};
    if(m_clockwiseRaceRotation) { rotation = "clock"; }
    else { rotation = "counterclock"; }
    //m_textureContaigner.loadAsset(textures::ID::track, "graphics/tracks/races/track" + std::to_string(trackNb + 1) + ".png");
 m_textureContaigner.loadAsset(textures::ID::track, "graphics/tracks/roads/track" + std::to_string(trackNb + 1) + " up " + rotation + ".png");
    m_textureContaigner.loadAsset(textures::ID::spritesheet, "graphics/sprite_sheet/sprite_sheet.png");
    m_textureContaigner.loadAsset(textures::ID::shadows, "graphics/tracks/shadows/track" + std::to_string(trackNb + 1) + " shadows.png");
    m_textureContaigner.loadAsset(textures::ID::win, "graphics/race/win animation.png");
    m_textureContaigner.loadAsset(textures::ID::podium, "graphics/race/podium animation .png");
    m_textureContaigner.loadAsset(textures::ID::loose, "graphics/race/loose animation.png");
    m_textureContaigner.loadAsset(textures::ID::end, "graphics/race/win.png");
    m_TrackLimits[0].loadFromFile("graphics/tracks/roads/track" + std::to_string(trackNb + 1) + " down " + rotation + ".png");
    m_TrackLimits[1].loadFromFile("graphics/tracks/roads/track" + std::to_string(trackNb + 1) + " up " + rotation + ".png");
}

void Race::loadSounds()
{
     m_audioPlayer.loadSound(sounds::ID::applause, "sound/applause.ogg");
     m_audioPlayer.loadSound(sounds::ID::bouncingWheel, "sound/bouncing wheel.ogg");
     m_audioPlayer.loadSound(sounds::ID::bump, "sound/bump.ogg");
     m_audioPlayer.loadSound(sounds::ID::gameOver, "sound/game over.ogg");
     m_audioPlayer.loadSound(sounds::ID::hornCountdown, "sound/horn countdown.ogg");
     m_audioPlayer.loadSound(sounds::ID::tyresLong, "sound/tyres long.ogg");
     m_audioPlayer.loadSound(sounds::ID::tyresShort, "sound/tyres short.ogg");
     m_audioPlayer.loadSound(sounds::ID::tyresWater, "sound/tyres water.ogg");
}

void Race::loadMusic(const unsigned int completedRaces)
{                                                                  //////////////////   music suivant circuit ou ??????????????
    unsigned int race{0};
    if(completedRaces >=18) { race = completedRaces -18; }
    else
        if(completedRaces >=9) { race = completedRaces -9; }
    switch(race) {
        case 1:
        case 5:
        case 9:
            m_audioPlayer.loadMusic("music/track1.wav");
            break;
        case 2:
        case 6:
            m_audioPlayer.loadMusic("music/track2.wav");
            break;
        case 3:
        case 7:
            m_audioPlayer.loadMusic("music/track3.wav");
            break;
        case 4:
        case 8:
            m_audioPlayer.loadMusic("music/track4.wav");
            break;
        default :
            break;
    }
}
void Race::initViews()
{
    m_topView.setSize(sf::Vector2f(512.f, 350.f));
    m_topView.setViewport(sf::FloatRect(0.1f, 0.f, 0.8f, 0.885f));
    m_bottomView.setSize(sf::Vector2f(512.f, 40.f));
    m_bottomView.setCenter(256, 20);
    m_bottomView.setViewport(sf::FloatRect(0.1f, 0.9f, 0.8f, 0.1f));
std::cout << "init views ok " << std::endl;
}

void Race::initSprites()
{
    m_track.setTexture(m_textureContaigner.getAsset(textures::ID::track));
    m_track.setTextureRect(sf::IntRect(0, 0, 1280, 800));
    m_track.setPosition(0, 0);
    m_shadows.setTexture(m_textureContaigner.getAsset(textures::ID::shadows));
    m_shadows.setTextureRect(sf::IntRect(0, 0, 1280, 800));
    m_shadows.setPosition(0, 0);
    m_bridge.setTexture(m_textureContaigner.getAsset(textures::ID::spritesheet));
    m_hazard.setTexture(m_textureContaigner.getAsset(textures::ID::spritesheet));
    m_arrival.setTexture(m_textureContaigner.getAsset(textures::ID::spritesheet));
    if(m_trackData.getArrivalPortalOrientation() == 0) { m_arrival.setTextureRect(sf::IntRect(40, 1570, 160, 22)); }
    else { m_arrival.setTextureRect(sf::IntRect(0, 1570, 22, 161));}
    m_arrival.setPosition(m_trackData.getArrivalPortalCoords());
std::cout << "init sprites ok " << std::endl;
}

void Race::setTopViewCenter()
{
    sf::Vector2f humanCarCoords{m_players.getHumanCarPosition()};
    if(humanCarCoords.x < 256) { humanCarCoords.x = 256; }
    else
        if(humanCarCoords.x > 1024) { humanCarCoords.x = 1024; }
    if(humanCarCoords.y < 175) { humanCarCoords.y = 175; }
    else
        if(humanCarCoords.y > 625) { humanCarCoords.y = 625; }
    m_topView.setCenter(humanCarCoords);
}

void Race::setRacersOnStartingPosition()
{
    for(unsigned int i = 8 - m_players.getRacerNumber(), j = 0; j < m_players.getRacerNumber(); ++i, ++j) {
        Player* player{m_players.getPlayer(j)};
        sf::Vector2f spawnCoords = m_trackData.getCarSpawnCoords(i);
        player->setPosition(spawnCoords);
        player->setAngle(m_trackData.getCarSpawnangle(i));
        player->setStartFrame(player->getAngle());
        player->setElevation(m_trackData.getCarSpawnElevation(i));
        player->updateCarLimits();
        sf::Vector2f coords{player->getPosition()};
        sf::Color color{m_TrackLimits[player->getElevation()].getPixel(static_cast<int>(coords.x), static_cast<int>(coords.y))};
        player->setRoadColor(color);
    }
}

unsigned int Race::racing(const unsigned int completedRaces, BottomPanel& bottomPanel) 
{
std::cout << "entering racing" << std::endl;
    mylib::Animation lightCountdown;
    lightCountdown.setTexture(m_textureContaigner.getAsset(textures::ID::spritesheet));
    for(auto i = 0; i < 5; ++i) {
        lightCountdown.addFrame(sf::IntRect(460, 60 + (i * 50), 160, 48));
    }
    lightCountdown.setFrameRate(1000);
    lightCountdown.setPosition(m_trackData.getCountdownCoords());
    loadMusic(completedRaces);
    initViews();
    initSprites();
std::cout << "init racing ok" << std::endl;
    setRaceLapsNumber(completedRaces);
    setRacersOnStartingPosition();
std::cout << "players on tracks" << std::endl;
    hazardsgeneration(completedRaces);
std::cout << "hazards generated" << std::endl;
    Inputs inputs(m_window);
    Command command;
    updateRaceBottomPanel(m_players.getHumanPlayer());
std::cout << "bottom panel updated" << std::endl;
    bool isRaceOver{false};
    bool humanCarBroken{ false };
    bool raceStarted{false};
raceStarted = true;
    lightCountdown.play();
//    m_audioPlayer.playSound(sounds::ID::hornCountdown, 100);
    mylib::Timer inputsTimer(33);
    unsigned int inputsTimerCounter{ 0 };
    inputsTimer.start();
    mylib::Timer gameTimer(9);
    mylib::Timer pauseTimer(120);
    gameTimer.start();
    pauseTimer.start();
std::cout << "starting race" << std::endl;
m_raceLapsNb = 5;
std::cout << "language is : " << m_language << std::endl;
    bool pause{false};
    bool gameIsOver{ false };
    while(!isRaceOver && !humanCarBroken) {
        if(raceStarted) {
            if(inputsTimer.isTimeElapsed()) {
                inputsTimer.restart();
                ++inputsTimerCounter;
                if (!pause) { driveComputerCars(); }
                if (inputsTimerCounter == 4) {
                    inputsTimerCounter = 0;
                    inputs.readInput(m_players.getHumanJoystick());
                    if (!pause) {                                                                                               // read player inputs
                        while (inputs.isCommandAvailable()) {
                            command = inputs.getInput();
                            if (command.letter == ' ') {
                                pause == true ? pause = false : pause = true;
                            }
                            if (command.letter == 27) { return 3; }
                            driveHumanCar(command);                                                                             // move human car
                        }
                    }
                    else {
                        while (inputs.isCommandAvailable()) {
                            command = inputs.getInput();
                            if (command.letter == ' ') {
                                pause == true ? pause = false : pause = true;
                            }
                            if (command.letter == 27) { return 4; }
                        }
                    }
                }
            }
        }
        if(!pause) {
            if(gameTimer.isTimeElapsed()) {
                gameTimer.restart();
                m_window.clear();
                setTopViewCenter();
                m_window.setView(m_topView);
                m_window.draw(m_track);
                checkCarOnCarCollision();
                moveCars();
                drawHazards();
                checkPlayerCarNearBridge(m_trackData.getNearBridgearea());                                                      // check cars elevation
                checkCarsInAnicheatArea();                                                                                      // check if cars are on a anticheat waypoint
                for(unsigned int i = 0; i < m_players.getRacerNumber(); ++i) {                                                  // draw cars at floor 0
                    if(m_players.getPlayerCarElevation(i) == 0) { m_window.draw(*m_players.getPlayerCar(i)); }
                }
                drawBridge();                                                                                                   // if bridge in view draw the bridge
                for(unsigned int i = 0; i < m_players.getRacerNumber(); ++i) {                                                  // draw cars at floor 1
                    if(m_players.getPlayerCarElevation(i) == 1) { m_window.draw(*m_players.getPlayerCar(i)); }
                }
                checkCarsInHazards();
                checkCarsOnTrack();                                                                                             // check if car is in a hazard
                checkCarsRanking();
                isRaceOver = checkCarsOnArrival();
                m_window.draw(m_shadows);                                                                                       // draw frame elements
                m_window.draw(m_arrival);

                if(!raceStarted) {
                    lightCountdown.animate();
                    if(lightCountdown.getState() == mylib::Animation::State::stopped ) {
                        raceStarted = true;
            //          m_audioPlayer.playMusic(100, true);
                    }
                    m_window.draw(lightCountdown);
                }
                                                            ///////////////////////////   botoom view ////////////////////////////////////////////////////
                m_window.setView(m_bottomView);
                updateRaceBottomPanel(m_players.getHumanPlayer());
                m_window.draw(m_raceBottomPanel);
                m_window.display();
                if(isHumanCarBroken()) { 
                    humanCarBroken = true; 
                    m_players.setHumanRanking(8);
                }
            }
        }
    }
    gameIsOver = isHumanCarBroken() || m_players.getHumanRanking() > 3;
/////////////////  message gagné ou perdu !!!!!!!!!!!!!!!!!!!!!!!!!!!!


/////////////////  animation fin de course !!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::string pannelStringToDisplay{ "" };
    buildStatsString(pannelStringToDisplay);
    afterRaceAnimations(gameIsOver, isHumanCarBroken(), pannelStringToDisplay, bottomPanel);


    // triche pour phase de dev/test
    if (m_players.getHumanName() == "SOUT" && m_players.getHumanRanking() > 3) { return 1; }

std::cout << pannelStringToDisplay << std::endl;
    return m_players.getHumanRanking();                                                                                                             // return la place human player à la fin de la course
}

void Race::buildStatsString(std::string& pannelStringToDisplay)
{
    if (m_trackNb < 10) {
        pannelStringToDisplay += '0' + std::to_string(m_trackNb + 1); }
    else { pannelStringToDisplay = std::to_string(m_trackNb); }
    Player& player{ m_players.getHumanPlayer() };
    float speedConverter{ 1 };
    if (m_language > 1) { speedConverter = 1.609f; }                                                                                          // convert miles to km
    if (!player.isBroken()) {
        if (player.getRaceRanking() < 4) { pannelStringToDisplay += std::to_string(player.getRaceRanking()); }
        else { pannelStringToDisplay += "-"; }
    }
    else { pannelStringToDisplay += "-"; }
    if (player.getRaceRanking() > 3 || player.isBroken()) { pannelStringToDisplay += "000000----"; }
    else {
        std::string topSpeed{ std::to_string(static_cast<int>(player.getTopRaceSpeed() * speedConverter)) };
        if (topSpeed.size() > 2) { pannelStringToDisplay += topSpeed; }
        else { pannelStringToDisplay += '0' + topSpeed; }
        float totalRaceLength{ (m_raceLapsNb * m_trackData.getTrackLength()) / 1760.f };                                                          // track length in miles
        float averageSpeed{ (totalRaceLength / player.getRaceTime().asSeconds()) * 3600.f * speedConverter };
        std::string average{ std::to_string(static_cast<int>(averageSpeed)) };
        if (average.size() > 2) { pannelStringToDisplay += average; }
        else { pannelStringToDisplay += '0' + average; }

        std::string convert{ std::to_string(bestLapsTimes[m_trackNb].second.asSeconds()) };
        convert.resize(5);
        convert.erase(std::find(convert.begin(), convert.end(), '.'));
        pannelStringToDisplay += convert;
    }
    if (player.getRaceRanking() > 3 || player.isBroken()) { pannelStringToDisplay += "000000"; }
    else {
        std::string prizeMoney{ std::to_string(prizeMoneyComputing(player.getGameDifficulty(), player.getRaceRanking())) };
        if (prizeMoney.size() == 5) { pannelStringToDisplay += '0' + prizeMoney; }
        else { pannelStringToDisplay += "00" + prizeMoney; }
    }
}

void  Race::initEndingAnimations(const char ranking, mylib::Animation& backgroundAnim, mylib::Animation& gameOverAnim, mylib::Animation& carAnim, sf::Sprite& wheeSprite)
{
    unsigned int frameNb{ 9 };
    if (ranking == '1') {
        backgroundAnim.setTexture(m_textureContaigner.getAsset(textures::win));
        m_audioPlayer.playSound(sounds::applause, 100);
    }
    else {
        if (ranking == '2' || ranking == '3') {
            backgroundAnim.setTexture(m_textureContaigner.getAsset(textures::podium));
            frameNb = 7;
            m_audioPlayer.playSound(sounds::applause, 100);
        }
        else { backgroundAnim.setTexture(m_textureContaigner.getAsset(textures::loose)); }
    }
    backgroundAnim.setLoop(true);
    backgroundAnim.setFrameRate(100);
    backgroundAnim.setPosition(sf::Vector2f(0, 0));
    sf::IntRect carTextureDimension(0, 0, 640, 351);
    for (unsigned int i = 0; i < frameNb; ++i) {
        backgroundAnim.addFrame(carTextureDimension);
        carTextureDimension.top += 355;
    }
    gameOverAnim.setTexture(m_textureContaigner.getAsset(textures::spritesheet));
    gameOverAnim.setLoop(false);
    gameOverAnim.setFrameRate(100);
    gameOverAnim.setPosition(sf::Vector2f(185, 145));
    carTextureDimension.left = 0;
    carTextureDimension.top = 1221;
    carTextureDimension.width = 248;
    carTextureDimension.height = 30;
    for (auto i = 0; i < 8; ++i) {
        gameOverAnim.addFrame(carTextureDimension);
        carTextureDimension.top += 30;
    }
    carAnim.setTexture(m_textureContaigner.getAsset(textures::spritesheet));
    carAnim.setLoop(true);
    carAnim.setFrameRate(80);
    Player& player{ m_players.getHumanPlayer() };
    int offset{ 0 };
    switch (player.getType()) {
        case Car::Type::Taraco_Neoroder:
        case Car::Type::Taraco_Neoroder1:
            carTextureDimension.left = 0;
            carTextureDimension.top = 390;
            carTextureDimension.width = 253;
            carTextureDimension.height = 84;
            offset = 85;
            carAnim.setPosition(sf::Vector2f(-270, 263));
            wheeSprite.setTextureRect(sf::IntRect(125, 662, 44, 42));
            wheeSprite.setOrigin(sf::Vector2f(22, 21));
            break;
        case Car::Type::Vaug_Interceptor2:
        case Car::Type::Vaug_Interceptor3:
            carTextureDimension.left = 319;
            carTextureDimension.top = 328;
            carTextureDimension.width = 297;
            carTextureDimension.height = 80;
            offset = 83;
            carAnim.setPosition(sf::Vector2f(-310, 260));
            wheeSprite.setTextureRect(sf::IntRect(125, 709, 44, 44));
            wheeSprite.setOrigin(sf::Vector2f(22, 22));
            break;
        case Car::Type::Retron_Parsec_Turbo5:
        case Car::Type::Retron_Parsec_Turbo6:
        case Car::Type::Retron_Parsec_Turbo8:
            carTextureDimension.left = 315;
            carTextureDimension.top = 583;
            carTextureDimension.width = 302;
            carTextureDimension.height = 85;
            offset = 88;
            carAnim.setPosition(sf::Vector2f(-330, 263));
            wheeSprite.setTextureRect(sf::IntRect(125, 758, 44, 44));
            wheeSprite.setOrigin(sf::Vector2f(22, 22));
            break;
        default:
            break;
        }
    wheeSprite.setTexture(m_textureContaigner.getAsset(textures::spritesheet));
    wheeSprite.setPosition(-30, 90);
    for (auto i = 0; i < 3; ++i) {
        carAnim.addFrame(carTextureDimension);
        carTextureDimension.top += offset;
    }
    carAnim.play();
}

void Race::afterRaceAnimations(const bool gameOver, const bool carIsBroken, const std::string& panelStringToDisplay, BottomPanel& botomPanel)
{
    m_topView.reset(sf::FloatRect(0, 0, 640, 350));
    m_topView.setViewport(sf::FloatRect(0, 0, 1, 0.885f));
    m_bottomView.reset(sf::FloatRect(0, 0, 640, 40));
    m_bottomView.setViewport(sf::FloatRect(0.f, 0.9f, 1.f, 0.1f));
    InfoPanel infoPanel(panelStringToDisplay, &m_textureContaigner.getAsset(textures::spritesheet));
    mylib::Animation backgroundAnim;
    mylib::Animation gameOverAnim;
    mylib::Animation carAnim;
    sf::Sprite wheelSprite;
    mylib::Timer pause;
    initEndingAnimations(panelStringToDisplay[2], backgroundAnim, gameOverAnim, carAnim, wheelSprite);
    backgroundAnim.play();
    bool animationsOn{ true };
    bool gameOverLaunched{ false };
    bool carIsMoving{ true };
    bool pauseFinished{ false };
    sf::Vector2f coords(0, 0);
    if (carIsBroken) { carIsMoving = false; }
    mylib::Timer movingTimer(10);
    float carMovement{ 0.95f };
    if (!carIsBroken) { 
        coords = carAnim.getPosition();
        if (coords.x < -329) { carMovement = 1.1f; }
        else 
            if (coords.x < -309) { carMovement = 1.05f; }
    }
    movingTimer.start();
    bool wheelDown{ true };
    float maxWheelHeight{ 262 };
    while (animationsOn) {
        m_window.clear();
        m_window.setView(m_topView);
        backgroundAnim.animate();
        infoPanel.update();
        if(carIsMoving && !infoPanel.isFinished() ) {                                                                               // if win or podium move the car to the midle 
            if (movingTimer.isTimeElapsed()) {
                coords = carAnim.getPosition();
                carAnim.setPosition(sf::Vector2f(coords.x + carMovement, coords.y));
                movingTimer.restart(); 
            }
            carAnim.animate();
        }
        if (!gameOver && !carIsBroken && infoPanel.isFinished() && !pause.isTimerStarted() && !pauseFinished) {                     // if win or podium and car at the middle start the pause
            pause.setDuration(3000);
            pause.start();
            carIsMoving = false;
        }
        if (!gameOver && !carIsBroken && pause.isTimeElapsed()) {                                                                   // if win or podium and pause finished allow the car to move
            carIsMoving = true;
            movingTimer.restart();
            pauseFinished = true;
        }
        if (!gameOver && !carIsBroken && carIsMoving && pauseFinished) {                                                            // if win or podium mover the car out of the screen                                                    
            if (movingTimer.isTimeElapsed()) {
                coords = carAnim.getPosition();
                carAnim.setPosition(sf::Vector2f(coords.x + carMovement, coords.y));
                movingTimer.restart();
                if (coords.x > 680) { animationsOn = false; }
            }
            carAnim.animate();
        }
        if (!carIsBroken && gameOver && !gameOverLaunched && infoPanel.isFinished()) {                                              // if game over launch gamer over animation
            m_audioPlayer.playSound(sounds::gameOver, 100);
            gameOverAnim.play();
            gameOverLaunched = true;
        }
        if (gameOverLaunched) { gameOverAnim.animate(); }                                                                           // if game over animate game over animation
        if (gameOver && !carIsBroken && gameOverAnim.getState() == mylib::Animation::State::stopped && !pause.isTimerStarted()) {   // if game over and game over animation finished start pause
            pause.setDuration(5000);
            pause.start(); 
        }
        if (gameOver && !carIsBroken && pause.isTimeElapsed()) { animationsOn = false; }                                            // if game over and pause finished ending animation is over
        sf::Vector2f wheelCoords{ wheelSprite.getPosition() };                                                                      
        if (carIsBroken && movingTimer.isTimeElapsed()) {                                                                           // if car is broken move and animate the bouncing wheel
            movingTimer.restart();
            if (wheelDown) {
                if (wheelCoords.y < 322) { wheelSprite.setPosition(sf::Vector2f(wheelCoords.x + 0.7f, wheelCoords.y + 1)); }
                else  { 
                    wheelDown = false; 
                    if(wheelCoords.x < 640) { m_audioPlayer.playSound(sounds::bouncingWheel, 100); }
                    maxWheelHeight /= 1.6f;
                }
            }
            else {
                if (wheelCoords.y > 322 - maxWheelHeight) { wheelSprite.setPosition(sf::Vector2f(wheelCoords.x + 0.7f, wheelCoords.y - 1)); }
                else  { wheelDown = true; }
            }
            wheelSprite.rotate(3);
        }
        if (carIsBroken && wheelCoords.x > 670 && !pause.isTimerStarted()) { pause.start(); }                                       // if car broken and wheel out of the screen start the pause
        if (carIsBroken && pause.isTimeElapsed() && gameOverAnim.getState() == mylib::Animation::State::idle) {                     // if car broken and wheel out of th escreen and pause finished launch gameover animation
            gameOverAnim.play(); 
            gameOverLaunched = true;
            m_audioPlayer.playSound(sounds::gameOver, 100);
        }
        if (carIsBroken && pause.isTimeElapsed() && gameOverAnim.getState() != mylib::Animation::State::running) { gameOverAnim.animate(); }  // animate game over animation
        if (carIsBroken && gameOverAnim.getState() == mylib::Animation::State::stopped) {                                           // if car broken and game over animation finished launch pause and stop ending animation
            animationsOn = false; 
            sf::sleep(sf::milliseconds(5000));
        }
        m_window.draw(backgroundAnim);
        m_window.draw(infoPanel);
        if (!carIsBroken) { m_window.draw(carAnim); }
        if(carIsBroken) { m_window.draw(wheelSprite); }
        if (gameOverLaunched) { m_window.draw(gameOverAnim); }
        m_window.setView(m_bottomView);
        botomPanel.updateMoney();
        m_window.draw(botomPanel);
        m_window.display();
    }
}

bool Race::isHumanCarBroken() const
{
    Player& player{ m_players.getHumanPlayer() };
    return player.isBroken();
}

void Race::updateRaceBottomPanel(const Player& player)
{
    m_raceBottomPanel.updateSpeedMeter(player.getSpeed());
    m_raceBottomPanel.updateLaps(player.getRaceCurrentLap(), m_raceLapsNb);
    m_raceBottomPanel.updatePosition(player.getRaceRanking(), m_players.getRacerNumber());
    m_raceBottomPanel.updateCarUsury(player.getEngineState(), player.getBodyState(), player.getFuelState(), player.getTyresState());
}

void Race::setRaceLapsNumber(unsigned int completedRaces)
{
    if(completedRaces > 17) { m_raceLapsNb = 9; }
    else {
        if(completedRaces > 8) { m_raceLapsNb = 7; }
        else { m_raceLapsNb = 5; }
    }
}

void Race::drawBridge()
{
    sf::Vector2f viewcenter{m_topView.getCenter()};
        sf::Vector2f viewsize{m_topView.getSize()};
        sf::FloatRect viewBounds{viewcenter.x - (viewsize.x / 2), viewcenter.y - (viewsize.y / 2), viewsize.x, viewsize.y};
        for(unsigned int i = 0; i < m_trackData.getBridgeNumber(); ++i) {
            sf::FloatRect bridgebounds{m_trackData.getBridgeBounds(i)};
            if(m_collisioner.isRectangleIntersectRectangle(viewBounds, bridgebounds)) {
                if(m_trackData.getBridgeOrientation(i) == 0) { m_bridge.setTextureRect(sf::IntRect(220, 1570, 161, 152)); }
                else { m_bridge.setTextureRect(sf::IntRect(400, 1570, 168, 127)); }
                m_bridge.setPosition(sf::Vector2f(bridgebounds.left, bridgebounds.top));
                m_window.draw(m_bridge);
            }
        }
}

void Race::hazardsgeneration(const unsigned int completedRaces)
{
    std::array<unsigned int, 16> hazardCoordsChoice{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    mylib::Random<unsigned int> randomizer;
    std::shuffle(hazardCoordsChoice.begin(), hazardCoordsChoice.end(), randomizer.getUniformGenerator());
    unsigned int hazardNumber{0};
    if(completedRaces >= 23) { hazardNumber = 8; }
    else
        if(completedRaces >= 19) { hazardNumber = 7; }
        else
            if(completedRaces >= 14) { hazardNumber = 6; }
            else
                if(completedRaces >= 10) { hazardNumber = 5; }
                else
                    if(completedRaces >= 7) { hazardNumber = 4; }
                    else
                        if(completedRaces >= 4) { hazardNumber = 3; }
                        else
                            if(completedRaces >= 2) { hazardNumber = 2; }
                            else
                                if(completedRaces == 1) { hazardNumber = 1; }
                                else { return; }
    Hazard hazard;
    for(unsigned int i = 0; i < hazardNumber; ++i) {
        sf::Vector2f coords = m_trackData.getHazard(hazardCoordsChoice[i]);
        hazard.bounds.left = coords.x;
        hazard.bounds.top = coords.y;
        hazard.type = static_cast<HazardType>(randomizer.randomNumber(0,5));
        switch (hazard.type) {
            case HazardType::big_water:
                hazard.bounds.width = 64;
                hazard.bounds.height = 46;
                break;
            case HazardType::small_water:
                hazard.bounds.width = 48;
                hazard.bounds.height = 34;
                break;
            case HazardType::big_sand:
                hazard.bounds.width = 64;
                hazard.bounds.height = 54;
                break;
            case HazardType::small_sand:
                hazard.bounds.width = 50;
                hazard.bounds.height = 42;
                break;
            case HazardType::big_oil:
                hazard.bounds.width = 64;
                hazard.bounds.height = 48;
                break;
            case HazardType::small_oil:
                hazard.bounds.width = 46;
                hazard.bounds.height = 32;
                break;
            default:
                break;
        }
//std::cout << "hazard " << i << " : x " <<  hazard.bounds.left <<  "  y " <<  hazard.bounds.top <<  "  w " <<  hazard.bounds.width << "  h " <<  hazard.bounds.height <<  std::endl;
        m_hazards.push_back(hazard);
    }
}

void Race::drawHazards()
{
    sf::Vector2f viewcenter{m_topView.getCenter()};
        sf::Vector2f viewsize{m_topView.getSize()};
        sf::FloatRect viewBounds{viewcenter.x - (viewsize.x / 2), viewcenter.y - (viewsize.y / 2), viewsize.x, viewsize.y};
        for(unsigned int i = 0; i < m_hazards.size(); ++i) {
            if(m_collisioner.isRectangleIntersectRectangle(viewBounds, m_hazards[i].bounds)) {
                switch (m_hazards[i].type) {
                    case HazardType::big_water:
                        m_hazard.setTextureRect(sf::IntRect(0, 161, static_cast<int>(m_hazards[i].bounds.width), static_cast<int>(m_hazards[i].bounds.height)));
                        break;
                    case HazardType::small_water:
                        m_hazard.setTextureRect(sf::IntRect(81, 161, static_cast<int>(m_hazards[i].bounds.width), static_cast<int>(m_hazards[i].bounds.height)));
                        break;
                    case HazardType::big_sand:
                        m_hazard.setTextureRect(sf::IntRect(160, 161, static_cast<int>(m_hazards[i].bounds.width), static_cast<int>(m_hazards[i].bounds.height)));
                        break;
                    case HazardType::small_sand:
                        m_hazard.setTextureRect(sf::IntRect(240, 161, static_cast<int>(m_hazards[i].bounds.width), static_cast<int>(m_hazards[i].bounds.height)));
                        break;
                    case HazardType::big_oil:
                        m_hazard.setTextureRect(sf::IntRect(320, 161, static_cast<int>(m_hazards[i].bounds.width), static_cast<int>(m_hazards[i].bounds.height)));
                        break;
                    case HazardType::small_oil:
                        m_hazard.setTextureRect(sf::IntRect(400, 161, static_cast<int>(m_hazards[i].bounds.width), static_cast<int>(m_hazards[i].bounds.height)));
                        break;
                    default:
                        break;
                }
                m_hazard.setPosition(sf::Vector2f(m_hazards[i].bounds.left, m_hazards[i].bounds.top));
                m_window.draw(m_hazard);
            }
        }
}

void Race::checkCarsInHazards()
{
    std::vector<sf::Vector2f> carCornerCoords;
    std::vector<sf::Vector2f> hazardConers(4);
    sf::FloatRect HazardShape;
    bool carInHazard{false};
    for(unsigned int h = 0; h < m_players.getRacerNumber(); ++h) {
        bool inSand{false};
        Player* player{m_players.getPlayer(h)};
        sf::Vector2f cornerCoord;
        carCornerCoords.resize(0);
        for(auto i = 2; i < 6; ++i) {
            cornerCoord = player->getCornerCoords(i);
            carCornerCoords.push_back(cornerCoord);
        }
        for(unsigned int j = 0; j < m_hazards.size(); ++j) {
            HazardShape = m_hazards[j].bounds;
            HazardShape.left += 2;                                                                                // 2 pixels margin for player
            HazardShape.top += 2;
            HazardShape.width -= 4;
            HazardShape.height -= 4;
            hazardConers[0] = sf::Vector2f(HazardShape.left, HazardShape.top);
            hazardConers[1] = sf::Vector2f(HazardShape.left + HazardShape.width, HazardShape.top);
            hazardConers[2] = sf::Vector2f(HazardShape.left + HazardShape.width, HazardShape.top + HazardShape.height);
            hazardConers[3] = sf::Vector2f(HazardShape.left, HazardShape.top + HazardShape.height);
            sf::Vector2f coords1{player->getPosition()};
            sf::Vector2f coords2{HazardShape.left + (HazardShape.width / 2), HazardShape.top + (HazardShape.height / 2)};
            float distance{std::sqrt(std::pow(coords2.x - coords1.x, 2.f) + std::pow(coords2.y - coords1.y, 2.f))};
            carInHazard = false;
            if(distance < 74) {
                carInHazard = m_collisioner.isDotInRectangle(player->getPosition(), HazardShape);
                if(!carInHazard)
                    carInHazard = m_collisioner.isPolygonIntersectPolygon(hazardConers, carCornerCoords);
            }
            if(carInHazard) {
                switch (m_hazards[j].type) {
                    case HazardType::big_water:
                    case HazardType::small_water:
                        if(player->getSpeed() > 60) {
                            if(player->getInteractionType() != Entity::Interaction::waterShifting) {
                                float angle{player->getAngle()};
                                if(!player->getIsSpinAssistKitEquiped()) {
                                    player->turn(Entity::Direction::Right);
                                    player->turn(Entity::Direction::Right);
                                }
                                player->setInteraction(Entity::Interaction::waterShifting, angle, 8, 0);
                                m_audioPlayer.playSound(sounds::tyresWater, 100);
                            }
                        }
                        break;
                    case HazardType::big_sand:
                    case HazardType::small_sand:
                        player->setInSand(true);
                        inSand = true;
                        break;
                    case HazardType::big_oil:
                    case HazardType::small_oil:
                        if(player->getSpeed() > 60) {
                            if(player->getInteractionType() != Entity::Interaction::Spining) {
                                if(!player->getIsSpinAssistKitEquiped()) { player->setInteraction(Entity::Interaction::Spining, player->getAngle(), 11, 0); }
                                else { player->setInteraction(Entity::Interaction::Spining, player->getAngle(), 12, 0); }

                                m_audioPlayer.playSound(sounds::tyresLong, 100);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        player->setInSand(inSand);
    }
}

void Race::driveHumanCar(const Command& command)
{
    for(unsigned int i = 0; i < m_players.getRacerNumber(); ++i) {
        Player* player{m_players.getPlayer(i)};
        if(player->isHuman()) {
            switch(command.action) {
                case CommandType::joystiskButtonPushed :
                    player->accelerate();
                    break;
                case CommandType::joystiskButtonReleased :
                    player->decelerate();
                    break;
                case CommandType::joystiskMoved :
                    if(command.offsetX < 50) { player->turn(Entity::Direction::Left); }
                    else { player->turn(Entity::Direction::Right); }
                    if(command.offsetY > 50 && player->getIsFrontMissileEquiped()) {
                        // FIRE FRONT MISSILE
                    }
                    if(command.offsetY < 0 && player->getIsRearMissileEquiped()) {
                         /*FIRE REAR MISSILE*/
                    }
                    break;
                case CommandType::noAction :
                default :
                    break;
            }
        }
    }
}

void Race::driveComputerCars()
{
    for (unsigned int i = 0; i < m_players.getRacerNumber(); ++i) {
        Player* player{ m_players.getPlayer(i) };
        if (player->isComputer()) {
            sf::Vector2f carCenterCoords{ player->getPosition() };
            sf::Color color{ m_TrackLimits[player->getElevation()].getPixel(static_cast<int>(carCenterCoords.x), static_cast<int>(carCenterCoords.y)) };
            unsigned int  carFrame{ player->getCurrentFrame() };
            if (color == sf::Color(0xFFAEC9FF)) {
                if (carFrame >= 1 && carFrame <= 12) { player->turn(Entity::Direction::Left); }
                if (carFrame > 12) { player->turn(Entity::Direction::Right); }
            }
            else
                if (color == sf::Color(0x99D9EAFF)) {
                    if (carFrame >= 4 && carFrame <= 15) { player->turn(Entity::Direction::Left); }
                    if (carFrame > 15 || carFrame < 3) { player->turn(Entity::Direction::Right); }
                }
                else
                    if (color == sf::Color(0xC8BFE7FF)) {
                        if (carFrame >= 7 && carFrame <= 18) { player->turn(Entity::Direction::Left); }
                        if ((carFrame > 18 && carFrame <= 23) || carFrame < 6) { player->turn(Entity::Direction::Right); }
                    }
                    else
                        if (color == sf::Color(0x880015FF)) {
                            if (carFrame >= 10 && carFrame <= 21) { player->turn(Entity::Direction::Left); }
                            if ((carFrame > 21 && carFrame <= 23) || carFrame < 9) { player->turn(Entity::Direction::Right); }
                        }
                        else
                            if (color == sf::Color(0xF09B59FF)) {
                                if (carFrame > 12) { player->turn(Entity::Direction::Left); }
                                if (carFrame < 12) { player->turn(Entity::Direction::Right); }
                            }
                            else
                                if (color == sf::Color(0x75FA8DFF)) {
                                    if (carFrame >= 16 || carFrame < 3) { player->turn(Entity::Direction::Left); }
                                    if (carFrame < 15 && carFrame >= 3) { player->turn(Entity::Direction::Right); }
                                }
                                else
                                    if (color == sf::Color(0x7F7F7FFF)) {
                                        if (carFrame >= 19 || carFrame < 6) { player->turn(Entity::Direction::Left); }
                                        if (carFrame < 18 && carFrame >= 6) { player->turn(Entity::Direction::Right); }
                                    }
                                    else
                                        if (color == sf::Color(0xFFF200FF)) {
                                            if (carFrame >= 22 || carFrame < 9) { player->turn(Entity::Direction::Left); }
                                            if (carFrame < 21 && carFrame >= 9) { player->turn(Entity::Direction::Right); }
                                        }
            player->accelerate();
            //player->decelerate();
        }
    }
}

void Race::checkPlayerCarNearBridge(const std::vector<sf::FloatRect>&  areas)
{
    sf::Vector2f coordsToCheck;
    for(unsigned int j = 0; j < m_players.getRacerNumber(); ++j) {
        Player* player{m_players.getPlayer(j)};
        coordsToCheck = player->getPosition();
        bool carInArea{false};
        for(unsigned int i = 0; i < areas.size(); ++i) {
           carInArea |= coordsToCheck.x >= areas[i].left && coordsToCheck.x <= areas[i].left + areas[i].width && coordsToCheck.y >= areas[i].top && coordsToCheck.y <= areas[i].top + areas[i].height;
        }
        if(carInArea) {
            if(player->getElevation() == 0  && !player->getNearBridgeArea()) {
                player->setElevation(1);
                player->setNearBridgeArea(true);
            }
            if(player->getElevation() == 1  && !player->getNearBridgeArea()) {
                player->setElevation(0);
                player->setNearBridgeArea(true);
            }
        }
        else { player->setNearBridgeArea(false); }
    }
}

void Race::checkCarsInAnicheatArea()
{
    sf::Vector2f coordsToCheck;
    sf::FloatRect area;
    for(unsigned int i = 0; i < m_players.getRacerNumber(); ++i) {
        Player* player{m_players.getPlayer(i)};
        coordsToCheck = player->getPosition();
        for(unsigned int j = 0; j < 3; ++j) {
           area = m_trackData.getAnticheatWaypoint(j);
            if(coordsToCheck.x >= area.left && coordsToCheck.x <= area.left + area.width && coordsToCheck.y >= area.top && coordsToCheck.y <= area.top + area.height) {
                if(m_clockwiseRaceRotation) {
                    switch(j) {
                        case 0:
                            if(!player->getAnticheatWaypointState(1) && !player->getAnticheatWaypointState(2)) { player->setAnticheatWaypointValidated(j, true); }
                            break;
                        case 1:
                            if(player->getAnticheatWaypointState(0) && !player->getAnticheatWaypointState(2)) { player->setAnticheatWaypointValidated(j, true); }
                            break;
                        case 2:
                            if(player->getAnticheatWaypointState(0) && player->getAnticheatWaypointState(1)) { player->setAnticheatWaypointValidated(j, true); }
                            break;
                        default:
                            break;
                    }
                }
                else {
                    switch(j) {
                        case 0:
                            if(player->getAnticheatWaypointState(1) && player->getAnticheatWaypointState(2)) { player->setAnticheatWaypointValidated(j, true); }
                            break;
                        case 1:
                            if(!player->getAnticheatWaypointState(0) && player->getAnticheatWaypointState(2)) { player->setAnticheatWaypointValidated(j, true); }
                            break;
                        case 2:
                            if(!player->getAnticheatWaypointState(0) && !player->getAnticheatWaypointState(1)) { player->setAnticheatWaypointValidated(j, true); }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

bool Race::checkCarsOnArrival()
{
    sf::Vector2f coordsToCheck;
    sf::FloatRect area;
    for(unsigned int i = 0; i < m_players.getRacerNumber(); ++i) {
        Player* player{m_players.getPlayer(i)};
        coordsToCheck = player->getPosition();
        area = m_trackData.getArrivalPortalArea();
        sf::Time thisLapTime;
        if(coordsToCheck.x >= area.left && coordsToCheck.x <= area.left + area.width && coordsToCheck.y >= area.top && coordsToCheck.y <= area.top + area.height) {
            if(!player->getCarInArrivalAreaState()) {                                                       // player penetrate arrival area
                player->setStartRanking(true);
                player->setCarInArrivalAreaState(true);
                unsigned int currentLap{player->getRaceCurrentLap()};
                if(player->areAllAnticheatWaypointValidated()) {
                    player->resetAnticheatWaypointValidation();
                    ++currentLap;
                    player->setRaceCurrentLap(currentLap);
                    m_raceBottomPanel.updateLap(currentLap);
                    thisLapTime = player->getCurrentLapTime();
                    player->updateRaceTime(thisLapTime);
                    if(thisLapTime < player->getBestLapTime()) {
                        player->setBestLapTime(thisLapTime);
                        if(thisLapTime < bestLapsTimes[m_trackNb].second) {
                            bestLapsTimes[m_trackNb].first = player->getName();
                            bestLapsTimes[m_trackNb].second = thisLapTime;
                        }
                    }
                }
                if(currentLap > m_raceLapsNb) {                                                               // it was the last lap for this player
                    if(player->isHuman()) {
                        if(player->getRaceRanking() == 1) {
                            bestWinnersList[0].first = player->getName();
                            ++bestWinnersList[0].second;
                        }
                        unsigned int money{ prizeMoneyComputing(player->getGameDifficulty(), player->getRaceRanking()) };
                        player->setMoney(player->getMoney() + money);
                        bestWinnersList[0].third = player->getMoney();
                        return true;
                    }
                    else {
                        ++m_arrivedRacersNumber;
                        if(m_arrivedRacersNumber == 3) {
                            Player& humanPlayer{ m_players.getHumanPlayer() };
                            if (humanPlayer.isHuman()) {
                                thisLapTime = humanPlayer.getCurrentLapTime();
                                humanPlayer.updateRaceTime(thisLapTime);
                                return true;
                            }
                        }
                    }
                }
            }
            player->startLapTimeClock();
        }
        else {player->setCarInArrivalAreaState(false); }
    }
    return false;
}

void Race::checkCarsOnTrack()
{
    sf::Vector2f cornerToCheck;
sf::CircleShape circle(1);
circle.setFillColor(sf::Color::Red);
    for(unsigned int playerIndex = 0; playerIndex < m_players.getRacerNumber(); ++playerIndex) {
        Player* player{m_players.getPlayer(playerIndex)};
circle.setPosition(player->getPosition());
m_window.draw(circle);
        for(unsigned int carLimitNb = 0; carLimitNb < 8; ++carLimitNb) {
            cornerToCheck = player->getCarLimit(carLimitNb);
circle.setPosition(cornerToCheck);
m_window.draw(circle);
            sf::Color color{m_TrackLimits[player->getElevation()].getPixel(static_cast<int>(cornerToCheck.x), static_cast<int>(cornerToCheck.y))};
            if (color == sf::Color(0xED1C24FF) || color == sf::Color(0x22B14CFF) || color == sf::Color(0x3F48CCFF) || color == sf::Color(0xA349A4FF) ||
                color == sf::Color(0xFF7F27FF) || color == sf::Color(0xEFE4B0FF) || color == sf::Color(0xB5E61DFF) || color == sf::Color(0xB97A57FF)) {
                if (player->getInteractionType() != Entity::Interaction::Bumping) {
                    if(player->isHuman()) { m_audioPlayer.playSound(sounds::ID::bump, 100); }
                    float angle{ 0 };
                    if (color == sf::Color(0xED1C24FF) || color == sf::Color(0xB5E61DFF)) { angle = 5.4978f; }
                    else
                        if (color == sf::Color(0x22B14CFF) || color == sf::Color(0xEFE4B0FF)) { angle = 0.785398f; }
                        else
                            if (color == sf::Color(0x3F48CCFF) || color == sf::Color(0xFF7F27FF)) { angle = 2.3562f; }
                            else
                                if (color == sf::Color(0xA349A4FF) || color == sf::Color(0xB97A57FF)) { angle = 3.927f; }
                    player->setInteraction(Entity::Interaction::Bumping, angle, 1, 25);
                    return;
                }
            }

        }
    }
}

void Race::checkCarsRanking()
{
    sf::FloatRect area;
    bool inAnArea{false};
    for(unsigned int playerIndex = 0; playerIndex < m_players.getRacerNumber(); ++playerIndex) {
        Player* player{m_players.getPlayer(playerIndex)};
        sf::Vector2f coordsToCheck = player->getPosition();
        inAnArea = false;
        for(unsigned int i = 0; i < m_trackData.getRankingAreaNumber(); ++i) {
            area = m_trackData.getRankingArea(i);
            if(coordsToCheck.x >= area.left && coordsToCheck.x <= area.left + area.width && coordsToCheck.y >= area.top && coordsToCheck.y <= area.top + area.height) {
                inAnArea = true;
                if(player->getStartRanking() && !player->getcarInRankingAreaState()) {
                    player->setcarInRankingAreaState(true);
                    player->setCheckedRankingAreaNumber(player->getCheckedRankingAreaNumber() + 1);
                    std::pair<std::string, int> data;
                    std::vector<std::pair<std::string, int>> ranking;
                    for(unsigned int index = 0; index < m_players.getRacerNumber(); ++index) {
                        Player* player1{m_players.getPlayer(index)};
                        data.first = player1->getName();
                        data.second = player1->getCheckedRankingAreaNumber();
                        ranking.push_back(data);
                    }
                    std::sort(ranking.begin(), ranking.end(), [](auto &left, auto &right) { return left.second > right.second; });
                    for(unsigned int index = 0; index < m_players.getRacerNumber(); ++index) {
                        Player* player1{m_players.getPlayer(index)};
                        for(unsigned int index2 = 0; index2 < m_players.getRacerNumber(); ++index2) {
                            if(ranking[index2].first == player1->getName()) { player1->setRaceRanking(index2 + 1); }
                        }
                    }
                }
            }
        }
        if(!inAnArea)  { player->setcarInRankingAreaState(false); }
    }
}

void Race::moveCars()
{
    for(unsigned int playerIndex = 0; playerIndex < m_players.getRacerNumber(); ++playerIndex) {
        Player* player{m_players.getPlayer(playerIndex)};
// std::cout << player->getName() << " speed: " << player->getCarSpeed() << std::endl;
        player->move();
        sf::Vector2f coords{player->getPosition()};
        sf::Color color{m_TrackLimits[player->getElevation()].getPixel(static_cast<int>(coords.x), static_cast<int>(coords.y))};
        player->setRoadColor(color);
    }
}

void Race::checkCarOnCarCollision()
{
    for(unsigned int playerIndex1 = 0; playerIndex1 < m_players.getRacerNumber(); ++playerIndex1) {
        Player* player1{m_players.getPlayer(playerIndex1)};
        for(unsigned int playerIndex2 = 0; playerIndex2 < m_players.getRacerNumber(); ++playerIndex2) {
            Player* player2{m_players.getPlayer(playerIndex2)};
            if(player1->getName() != player2->getName()) {                                                                  // possible collision ?
                if (player1->getElevation() == player2->getElevation()) {
                    sf::Vector2f coords1{ player1->getPosition() };
                    sf::Vector2f coords2{ player2->getPosition() };
                    float distance{ std::pow(coords2.x - coords1.x, 2.f) + std::pow(coords2.y - coords1.y, 2.f) };
                    if (distance < 46 * 46) {
                        sf::FloatRect player1Shape{ player1->getShape() };
                        sf::FloatRect player2Shape{ player1->getShape() };
                        if (sqrt(distance) < ((player1Shape.height - 4) / 2 + (player2Shape.height - 4) / 2) - 2) {
                            if (player1->getSpeed() > player2->getSpeed()) {
                                player2->setInteraction(Entity::Interaction::Pushed, player2->getSideAngle(), 3, player1->getSpeed() * 0.5f * 0.8f);
                                player1->setSpeed(player1->getSpeed() * 0.5f);
                            }
                            else {
                                player1->setInteraction(Entity::Interaction::Pushed, player1->getSideAngle(), 3, player2->getSpeed() * 0.5f * 0.8f);
                                player2->setSpeed(player2->getSpeed() * 0.5f);
                            }
                            if (player1->isHuman() || player2->isHuman())
                                m_audioPlayer.playSound(sounds::ID::bump, 100);
                            return;
                        }
                        bool isCollision{ false };
                        std::vector<unsigned int> triangleSegment{ 2, 3, 4, 5, 2 };
                        for (unsigned int corner = 0; corner < 8; ++corner) {                                                       // for player1 all front car corners
                            sf::Vector2f coordsToCheck{ player1->getCornerCoords(corner) };
                            std::vector<sf::Vector2f> triangleVertices;
                            for (unsigned j = 0; j < 4; ++j) {                                                                      // test triangles side right, back, side left
                                triangleVertices.resize(0);
                                triangleVertices.push_back(player2->getPosition());
                                triangleVertices.push_back(player2->getCornerCoords(triangleSegment[j]));
                                triangleVertices.push_back(player2->getCornerCoords(triangleSegment[j + 1]));
                                if (!isCollision) {
                                    isCollision = m_collisioner.isDotInConvexPolygon(coordsToCheck, triangleVertices);
                                    if (isCollision) {
                                        if (player1->getSpeed() > 1 || player2->getSpeed() > 1 || player1->getSideSpeed() > 1 || player2->getSideSpeed() > 1) {
                                            if (player1->isHuman() || player2->isHuman())
                                                m_audioPlayer.playSound(sounds::ID::bump, 100);                                     // meme son que bump dans mur ?????????????
                                            float angle{ 0 }, speed{ 0 };
                                            Player* fasterCar{ nullptr };
                                            Player* slowerCar{ nullptr };
                                            if (player1->getSpeed() + player1->getSideSpeed() > player2->getSpeed() + player2->getSideSpeed()) {
                                                fasterCar = player1;
                                                slowerCar = player2;
                                            }
                                            else {
                                                fasterCar = player2;
                                                slowerCar = player1;
                                            }
                                            switch (j) {
                                            case 0:                                                                                 // player1 in player2 left side
                                            case 2:                                                                                 // player1 in player2 right side
                                                if (player1->getSpeed() + player1->getSideSpeed() > 1) {
                                                    if (corner == 1 || corner == 4 || corner == 7 || corner == 3 || corner == 6) {
std::cout << "player1 front " << player1->getName() << " in player2 " << player2->getName() << " side" << std::endl;
                                                        if (player1->getSideSpeed() > 1) { angle = player1->getSideAngle(); }
                                                        else {
                                                            if (player1->isShifting()) { angle = player1->getShiftingAngle(); }
                                                            else { angle = player1->getAngle(); }
                                                        }
                                                        speed = player1->getSpeed() + player1->getSideSpeed();
                                                        player1->setSpeed(player1->getSpeed() * 0.15f);
                                                        player1->setSideSpeed(player1->getSpeed() * 0.15f);
                                                        player2->setInteraction(Entity::Interaction::Pushed, angle, 3, speed * 0.4f);
                                                    }
                                                    else
                                                        if (corner == 2 || corner == 5 || corner == 0) {
std::cout << "player1 back " << player1->getName() << " in player2 " << player2->getName() << " side" << std::endl;
                                                            if (player1->getSideSpeed() > 1) { angle = player1->getSideAngle(); }
                                                            else {
                                                                if (player1->isShifting()) { angle = 3.14159265358f * 2 - player1->getShiftingAngle(); }
                                                                else { angle = 3.14159265358f * 2 - player1->getAngle(); }
                                                            }
                                                            speed = player1->getSpeed() + player1->getSideSpeed();
                                                            player1->setSpeed(player1->getSpeed() * 0.15f);
                                                            player1->setSideSpeed(player1->getSpeed() * 0.15f);
                                                            player2->setInteraction(Entity::Interaction::Pushed, angle, 3, speed * 0.4f);
                                                        }
                                                }
                                                else {
std::cout << "player1 standing still " << player1->getName() << " in player2 " << player2->getName() << " side" << std::endl;
                                                    if (player2->getSideSpeed() > 1) { angle = player2->getSideAngle(); }
                                                    else {
                                                        if (player2->isShifting()) { angle = player2->getShiftingAngle(); }
                                                        else { angle = player2->getAngle(); }
                                                    }
                                                    speed = player2->getSpeed() + player2->getSideSpeed();
                                                    player2->setSpeed(player2->getSpeed() * 0.15f);
                                                    player2->setSideSpeed(player2->getSpeed() * 0.15f);
                                                    player1->setInteraction(Entity::Interaction::Pushed, angle, 3, speed * 0.8f);
                                                }
                                                player1->setPosition(player1->getOldPosition());
                                                return;
                                            case 1:                                                                             // player1 in player2 front
                                                if (corner == 1 || corner == 4 || corner == 7 || corner == 3 || corner == 6) {
std::cout << "player1 front " << player1->getName() << " in player2 " << player2->getName() << " front" << std::endl;
                                                    if (slowerCar->getSpeed() > 1) { fasterCar->setInteraction(Entity::Interaction::Pushed, slowerCar->getAngle(), 3, slowerCar->getSpeed() * 0.3f); }
                                                    if (fasterCar->getSpeed() > 1) { slowerCar->setInteraction(Entity::Interaction::Pushed, fasterCar->getAngle(), 3, fasterCar->getSpeed() * 0.3f); }
                                                    fasterCar->setPosition(fasterCar->getOldPosition());
                                                    slowerCar->setPosition(slowerCar->getOldPosition());

                                                }
                                                else {
std::cout << "player1 back " << player1->getName() << " in player2 " << player2->getName() << " front" << std::endl;
                                                    if (fasterCar->isShifting()) { angle = fasterCar->getShiftingAngle(); }
                                                    else { angle = fasterCar->getAngle(); }
                                                    speed = fasterCar->getSideSpeed();
                                                    slowerCar->setInteraction(Entity::Interaction::Pushed, angle, 3, speed);
                                                    fasterCar->setSpeed(fasterCar->getSpeed() * 0.15f);
                                                    fasterCar->setSideSpeed(fasterCar->getSpeed() * 0.15f);
                                                    fasterCar->setPosition(fasterCar->getOldPosition());
                                                 }
                                                return;
                                            case 3:
std::cout << "player1 front or back " << player1->getName() << " in player2 " << player2->getName() << " back" << std::endl;
                                                if (fasterCar->getSideSpeed() > 1) {
                                                    angle = fasterCar->getSideAngle();
                                                    speed = fasterCar->getSideSpeed();
                                                }
                                                else {
                                                    if (fasterCar->isShifting()) { angle = fasterCar->getShiftingAngle(); }
                                                    else { angle = fasterCar->getAngle(); }
                                                    speed = fasterCar->getSpeed();
                                                }
std::cout << "speed: " << speed << std::endl;
                                                slowerCar->setInteraction(Entity::Interaction::Pushed, angle, 3, speed * 0.15);
                                                fasterCar->setSpeed(fasterCar->getSpeed() * 0.15f);
                                                fasterCar->setPosition(fasterCar->getOldPosition());
                                                return;
                                            default:
std::cout << "Unknown collision: " << j << " corner " << corner << std::endl; 
                                                break;

                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool Race::canTurn(Player* wantToTurn)
{
    return true;
}
