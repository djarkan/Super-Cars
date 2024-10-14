#include "header/intro.hpp"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "timer/timer.hpp"
#include "bitmap/simpleanimation/animation.hpp"
#include "bitmap/animationPlayer/animationPlayer.hpp"
#include "music/music.hpp"
#include "random/random.hpp"
#include "text/bitmapfont/bitmapFont.hpp"
#include "text/bitmaptext/bitmapText.hpp"
#include "jsonfile/jsonfile.hpp"
#include "header/car.hpp"
#include "header/inputs.hpp"
#include "header/command.hpp"
#include "header/message.hpp"
#include "header/game.hpp"

extern sf::Vector2f windowRatio;

std::array<std::pair<std::string, sf::Time>, 9> bestLapsTimes = {{{"SOUT", sf::milliseconds(15000)}, {"ANDY", sf::milliseconds(18000)}, {"JEZZ", sf::milliseconds(20000)}, {"DAVE", sf::milliseconds(20000)}, {"DOUG", sf::milliseconds(25000)}, {"PETE", sf::milliseconds(25000)} , {"GARF", sf::milliseconds(30000)}, {"MARI", sf::milliseconds(30000)}, {"ANNE", sf::milliseconds(30000)}}};
std::array<mylib::Triple<std::string, int, int>, 7> bestWinnersList =  { {{"GILL", 0, 500}, {"SOUT", 3, 10000}, {"ANDY", 3, 5000}, {"JEZZ", 3, 4000}, {"DAVE", 3, 3000}, {"DOUG", 3, 2000}, {"PETE", 3, 1000}} };

Intro::Intro(unsigned int windowWidth, unsigned int windowHeight, unsigned int language) : m_language{ language }, m_window(sf::VideoMode(windowWidth, windowHeight), "Super Cars Revival", sf::Style::Close), m_players(m_window, m_language)
{
    m_window.setJoystickThreshold(70);
    loadAssets();
    mylib::JsonFile configJson("config.json");
    m_language = configJson.m_Root["language"].asInt();
    switch(m_language) {
        case 0 :
            m_languageJson.loadJsonFile("language/english/game.json");
            break;
        case 1:
            m_languageJson.loadJsonFile("language/usa/game.json");
            break;
        case 2 :
            m_languageJson.loadJsonFile("language/french/game.json");
            break;
        default :
            break;
    }
    m_window.setMouseCursorVisible(false);

    sf::Vector2u windowSize = m_window.getSize();
    windowRatio.x = windowSize.x / 640;
    windowRatio.y = windowSize.y / 400;
    unsigned int screenWidh{ sf::VideoMode::getDesktopMode().width };
    unsigned int screenHeight{ sf::VideoMode::getDesktopMode().height };
    m_window.setPosition(sf::Vector2i((screenWidh - windowWidth) / 2, (screenHeight - windowHeight) / 2));
}

void Intro::loadAssets()
{
    m_textureContaigner.loadAsset(textures::ID::loading, "graphics/intro/loading.png");
    m_textureContaigner.loadAsset(textures::ID::gremlins, "graphics/intro/gremlin.png");
    m_textureContaigner.loadAsset(textures::ID::magnetic, "graphics/intro/magnetic_fields.png");
    m_textureContaigner.loadAsset(textures::ID::super_cars, "graphics/intro/super_cars.png");
    m_textureContaigner.loadAsset(textures::ID::guyAndGirl, "graphics/intro/guy_and_girl.png");
    m_textureContaigner.loadAsset(textures::ID::spritesheet, "graphics/sprite_sheet/sprite_sheet.png");
    m_textureContaigner.loadAsset(textures::ID::ronAndNancy, "graphics/intro/ron_and_nancy.png");
    m_textureContaigner.loadAsset(textures::ID::credits_original, "graphics/intro/credits.png");
    m_textureContaigner.loadAsset(textures::ID::credits_additionnal, "graphics/intro/credits aditional.png");
    m_textureContaigner.loadAsset(textures::ID::garageFont, "graphics/bitmap_fonts/ron_and_nancy_16x16.png");
    m_textureContaigner.loadAsset(textures::ID::supercarsfont, "graphics/bitmap_fonts/super_cars_16x16.png");


    m_jsonConfig.loadJsonFile("config.json");

}

void Intro::launchIntro()
{
    if(m_players.getHumanJoystick() == 99 ) { return; }

    bool won{false};
    initView();
    sf::Sound floppySound;
    sf::SoundBuffer soundBuffer;
    soundBuffer.loadFromFile("sound/floppy.ogg");
    floppySound.setBuffer(soundBuffer);
    floppySound.setLoop(true);
    floppySound.setVolume(100);
    floppySound.play();
 //   gremlins();
    floppySound.setVolume(0);
 //   magneticFields();
    mylib::Music music;
    music.loadMusic("music/intro.wav");
    music.setMusicLoop(true);
    music.setMusicVolume(100);
  //  music.playMusic();
    floppySound.setVolume(0);
    if(!won) {
   //     floppySound.setVolume(100);
   //     superCars();
    }
   // loading(2500);
    floppySound.setVolume(0);
    bool displayIntro{true};
    while(1) {
        bool enteredPseudo{false};
        displayIntro = true;
        while(!enteredPseudo) {
            while(displayIntro)
            {
                if(displayIntro) { displayIntro = guyAndGirl(); }
                if(displayIntro) {
                    floppySound.setVolume(100);
                    loading(2500);
                    floppySound.setVolume(0);
                }
                if(displayIntro) { displayIntro = ronAndNancy(); }
                if(displayIntro) {
                    floppySound.setVolume(100);
                    loading(1000);
                    floppySound.setVolume(0);
                }
                if(displayIntro) { displayIntro = creditsOriginal(); }
                if(displayIntro) {
                    floppySound.setVolume(100);
                    loading(1000);
                    floppySound.setVolume(0);
                }
                if(displayIntro) { displayIntro = creditsAdditionnal(); }
         //       floppySound.setVolume(100);
         //       loading(3000);
                floppySound.setVolume(0);
            }
         //   floppySound.setVolume(100);
         //   loading(3000);
            floppySound.setVolume(0);
            music.stopMusic();
            music.loadMusic("music/pseudo.wav");
         //   music.playMusic();
            enteredPseudo = m_players.setHumanName(won);
            if(!enteredPseudo) {
                music.stopMusic();
                displayIntro = true;
                floppySound.setVolume(100);
                loading(3000);
                music.loadMusic("music/intro.wav");
                floppySound.setVolume(0);
           //     music.playMusic();
            }

        }
        won = launchGame(music);
        initView();
        floppySound.setVolume(100);
        loading(2500);
        floppySound.setVolume(0);
    }
}

void Intro::gremlins()
{
    sf::Sprite gremlins;
    gremlins.setTexture(m_textureContaigner.getAsset(textures::ID::gremlins));
    gremlins.setTextureRect(sf::IntRect(0, 0, 640, 400));
    mylib::Timer timer(3000);
    timer.start();
    m_window.clear();
    m_window.draw(gremlins);
    m_window.display();
    while(!timer.isTimeElapsed())
        ;
}

void Intro::magneticFields()
{
    mylib::Music music;
    music.loadMusic("music/magnetic fields.wav");
    music.setMusicVolume(100);
    sf::Sprite background;
    background.setTexture(m_textureContaigner.getAsset(textures::ID::magnetic));
    background.setPosition(sf::Vector2f(320, 200));
    background.setTextureRect(sf::IntRect(0, 0, 640, 400));
    background.setOrigin(sf::Vector2f(320, 200));
    float factorX{10};
    float factorY{10};
    background.setScale(factorX, factorY);
    mylib::Timer timer(30);
    timer.start();
    while(factorX >= 1.f)
    {
        m_window.clear();
        m_window.draw(background);
        while(!timer.isTimeElapsed())
        ;
        timer.restart();
        factorX -= 0.2f;
        factorY -= 0.2f;
        background.setScale(factorX, factorY);
        m_window.display();
    }
    timer.setDuration(9500);
    timer.restart();
    music.playMusic();
    while(!timer.isTimeElapsed())
        ;
}

void Intro::superCars()
{
    sf::Sprite background;
    background.setTexture(m_textureContaigner.getAsset(textures::ID::super_cars));
    background.setTextureRect(sf::IntRect(0, 0, 640, 400));
    mylib::Timer timer(5000);
    timer.start();
    m_window.clear();
    m_window.draw(background);
    m_window.display();
    while(!timer.isTimeElapsed())
        ;
}

bool Intro::guyAndGirl()
{
    m_window.setMouseCursorVisible(false);
    sf::Sprite background;
    background.setTexture(m_textureContaigner.getAsset(textures::ID::guyAndGirl));
    background.setTextureRect(sf::IntRect(0, 0, 640, 400));
    sf::Sprite foreground;
    foreground.setTexture(m_textureContaigner.getAsset(textures::ID::guyAndGirl));
    foreground.setTextureRect(sf::IntRect(640, 0, 640, 400));
    sf::Sprite car;
    car.setTexture(m_textureContaigner.getAsset(textures::ID::spritesheet));
    mylib::Timer timer(17000);
    timer.start();
    bool exitIntro{false};
    mylib::Random <sf::Int32>randomTime;
    float carHight{ 0 };
    mylib::Random <int>randomCarModel;
    sf::Vector2f carCoord(700, 310);
    mylib::Random <int>distanceToGo;
    mylib::Timer timerCarMovement(randomTime.randomNumber(4, 8));
    timerCarMovement.start();
    int distance{distanceToGo.randomNumber(1200, 1500)};
    int carModel{randomCarModel.randomNumber(0, 2)};
    while(!timer.isTimeElapsed() && !exitIntro)
    {
        if(carCoord.x >= distance  ) {

            timerCarMovement.setDuration(randomTime.randomNumber(4, 8));
            distance = distanceToGo.randomNumber(1500, 2000);
            int oldCarModel{carModel};
            do
                carModel = randomCarModel.randomNumber(0, 2);
            while(carModel == oldCarModel);
            switch(carModel) {
                case 0 :
                    carHight = 83;
                    car.setTextureRect(sf::IntRect(0, 390, 253, static_cast<int>(carHight)));

                    break;
                case 1 :
                    carHight = 80;
                    car.setTextureRect(sf::IntRect(0, 480, 296, static_cast<int>(carHight)));
                    break;
                case 2 :
                    carHight = 85;
                    car.setTextureRect(sf::IntRect(0, 580, 302, static_cast<int>(carHight)));
                    break;
                default :
                    break;
            }
            carCoord.x = 0 - 400.f;
            carCoord.y =  310.f - carHight;
        }
        m_window.clear(sf::Color::Cyan);
        m_window.draw(background);
        car.setPosition(carCoord);
        m_window.draw(car);
        m_window.draw(foreground);
        m_window.display();
        if(timerCarMovement.isTimeElapsed()) {
            carCoord.x += 5;
            timerCarMovement.restart();
        }
        if(isIntroSkipped()) { exitIntro = true; }
    }
    if(exitIntro) { return false; }
    else { return true; }
}

bool Intro::ronAndNancy()
{
    sf::Sprite background;
    background.setTexture(m_textureContaigner.getAsset(textures::ID::ronAndNancy));
    background.setTextureRect(sf::IntRect(0, 0, 640, 400));
    bool exitIntro{false};
    bool speechEnded(false);
    mylib::BitmapFont font;
    font.setTexture(m_textureContaigner.getAsset(textures::ID::garageFont));
    font.setSize(16, 16);
    mylib::BitmapText bitmapText;
    bitmapText.setFont(&font);
    bitmapText.setLineSpacing(4.f);
    std::array<std::string, 21> RonAndNancySpeechArray;
    buildRonAndNancySpeech(RonAndNancySpeechArray);
    bool scroling{true};
    mylib::Timer timer(5000);
    mylib::Timer scrollingRate(47);
    scrollingRate.start();
    float x{16};
    float watchingY{351};
    float y =  watchingY;
    int speechArrayIndex{0};
    bitmapText.setText(RonAndNancySpeechArray[speechArrayIndex] + RonAndNancySpeechArray[speechArrayIndex + 1]);
    mylib::JsonFile jsonAnimations("data/animations/intro.json");
    mylib::AnimationPlayer animPlayer;
    sf::Vector2f animationcoord;
    std::vector<sf::IntRect> frames;
    for(auto i = 0; i < 4; ++i) {
        frames.resize(0);
        animationcoord.x = jsonAnimations.m_Root["ronAndNancy"][i]["destination"].get("x", 100).asFloat();
        animationcoord.y = jsonAnimations.m_Root["ronAndNancy"][i]["destination"].get("y", 100).asFloat();
        bool loop = jsonAnimations.m_Root["ronAndNancy"][i].get("loop", true).asBool();
        bool randomisedLoop = jsonAnimations.m_Root["ronAndNancy"][i].get("randomisedLoop", false).asBool();
        sf::IntRect rect;
        for(auto elem : jsonAnimations.m_Root["ronAndNancy"][i]["frames"]){
            rect.left = elem.get("x", 0).asInt();
            rect.top = elem.get("y", 0).asInt();
            rect.width = elem.get("w", 0).asInt();
            rect.height = elem.get("h", 0).asInt();
            frames.push_back(rect);
        }
        mylib::Animation animation(m_textureContaigner.getAsset(textures::ID::spritesheet), animationcoord, loop, randomisedLoop, frames);
        mylib::Animation* animPtr = new mylib::Animation (animation);
        *animPtr = std::move(animation);
        animPlayer.addAnimation(animPtr);
    }
    animPlayer.m_player[0]->play();
    animPlayer.m_player[2]->play();
    mylib::Random<sf::Int32> randomiser;
    mylib::Timer ronEyesDelay(randomiser.randomNumber(1000,3000));
    ronEyesDelay.start();
    mylib::Timer someoneMouthDelay(1000);
    someoneMouthDelay.start();
    bool ronEyesDelayState{false};
    bool someoneSpeaking{false};
    bool ronSpeech{true};
    mylib::Timer nancyEyesDelay(randomiser.randomNumber(1000,3000));
    nancyEyesDelay.start();
    bool nancyEyesDelayState{false};
    mylib::Timer speechLength(49000);
    speechLength.start();
    while(!speechEnded && !exitIntro) {
        m_window.clear();                       // texte visible coord 16, 351 step 4

        for(auto elem : animPlayer.m_player) {
            elem->animate();
        }
        if(animPlayer.m_player[0]->getState() == mylib::Animation::State::stopped && ronEyesDelayState == false ) {
            ronEyesDelayState = true;
            ronEyesDelay.setDuration(randomiser.randomNumber(1000,3000));
            ronEyesDelay.start();
        }
        if(ronEyesDelay.isTimeElapsed()) {
            ronEyesDelayState = false;
            animPlayer.m_player[0]->play();
        }
        if(animPlayer.m_player[2]->getState() == mylib::Animation::State::stopped && nancyEyesDelayState == false ) {
            nancyEyesDelayState = true;
            nancyEyesDelay.setDuration(randomiser.randomNumber(1000,3000));
            nancyEyesDelay.start();
        }
        if(nancyEyesDelay.isTimeElapsed()) {
            nancyEyesDelayState = false;
            animPlayer.m_player[2]->play();
        }
        if(!someoneSpeaking && someoneMouthDelay.isTimeElapsed()) {
            if(ronSpeech) { animPlayer.m_player[1]->play(); }
            else { animPlayer.m_player[3]->play(); }
            someoneSpeaking = true;
            someoneMouthDelay.setDuration(5000);
            someoneMouthDelay.restart();
        }
        if(someoneSpeaking && someoneMouthDelay.isTimeElapsed()) {
            if(ronSpeech) { animPlayer.m_player[1]->stop(); }
            else { animPlayer.m_player[3]->stop(); }
            someoneSpeaking = false;
            someoneMouthDelay.setDuration(1000);
            someoneMouthDelay.restart();
        }
        if(!ronSpeech && speechLength.isTimeElapsed()) { exitIntro = false; }
        if(speechLength.isTimeElapsed()) {
            ronSpeech = false;
            speechLength.setDuration(66000);
            speechLength.restart();
        }
        if(scroling) {
            if(y > 309) {
                if(scrollingRate.isTimeElapsed()) {
                    y -= 2;
                    scrollingRate.restart();
                }
                else {}
            }
            else {
                scroling = false;
                timer.restart();
                speechArrayIndex++;
                if(speechArrayIndex == 20) {speechEnded = true; }
            }
        }
        else {
            y = watchingY;
            if(timer.isTimeElapsed()) {
                scroling = true;
                scrollingRate.restart();
            }
        }
        bitmapText.setText(RonAndNancySpeechArray[speechArrayIndex] + RonAndNancySpeechArray[speechArrayIndex + 1]);
        bitmapText.setPosition(x, y);
        m_window.draw(bitmapText);
        m_window.draw(background);
        m_window.draw(animPlayer);
        m_window.display();
        if(isIntroSkipped()) { exitIntro = true;  }
    }
    if(!exitIntro) { return true; }
    else { return false; }
}

void Intro::buildRonAndNancySpeech(std::array<std::string, 21>& speechArray)
{
    mylib::JsonFile jsonRonAndNancy;
    switch(m_language) {
        case 0 :
            jsonRonAndNancy.loadJsonFile("language/english/RonAndNancy.json");
            break;
        case 1 :
            jsonRonAndNancy.loadJsonFile("language/usa/RonAndNancy.json");
            break;
        case 2 :
            jsonRonAndNancy.loadJsonFile("language/french/RonAndNancy.json");
            break;
        default :
            break;
    }
    mylib::Random <int>speechRandimiser;
    speechArray[0] = "\n\n";
    speechArray[1] = jsonRonAndNancy.m_Root["Ron&Nancy"]["intro"][speechRandimiser.randomNumber(0, 5)].asString();
    speechArray[2] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestDrivers"][0][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[3] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestDrivers"][1][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[4] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestDrivers"][2][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[5] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestDrivers"][3][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[6] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestDrivers"][4][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[7] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestDrivers"][5][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[8] = jsonRonAndNancy.m_Root["Ron&Nancy"]["ronToNancy"][speechRandimiser.randomNumber(0, 4)].asString();
    speechArray[9] = jsonRonAndNancy.m_Root["Ron&Nancy"]["startNancy"][speechRandimiser.randomNumber(0, 4)].asString();
    speechArray[10] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestTracks"][0][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[11] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestTracks"][1][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[12] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestTracks"][2][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[13] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestTracks"][3][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[14] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestTracks"][4][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[15] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestTracks"][5][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[16] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestTracks"][6][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[17] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestTracks"][7][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[18] = jsonRonAndNancy.m_Root["Ron&Nancy"]["bestTracks"][8][speechRandimiser.randomNumber(0, 3)].asString();
    speechArray[19] = jsonRonAndNancy.m_Root["Ron&Nancy"]["outro"][speechRandimiser.randomNumber(0, 5)].asString();
    speechArray[20] = "                        \n                                   ";
    auto j{0};
    if(bestWinnersList[0].second < 3) { j = 1; }
    size_t position{0};
    for(size_t i = 2; i < 8; ++i, ++j) {
        position = static_cast<int>(speechArray[i].find("NAME"));
        speechArray[i].replace(position, 4, bestWinnersList[j].first);
        position = speechArray[i].find("X");
        speechArray[i].replace(position, 1, std::to_string(bestWinnersList[j].second));
        position = speechArray[i].find("MONEY");
        speechArray[i].replace(position, 5, std::to_string(bestWinnersList[j].third));
    }
    j = 0;
    std::string convert;
    for(size_t i = 10; i < 19; ++i, ++j) {
        position = speechArray[i].find("NAME");
        speechArray[i].replace(position, 4, bestLapsTimes[j].first);
        position = speechArray[i].find("TIMES");
        convert = std::to_string(bestLapsTimes[j].second.asSeconds());
        convert.resize(5);
        speechArray[i].replace(position, 5, convert);
    }
}

bool Intro::creditsOriginal()
{
    sf::Sprite background;
    background.setTexture(m_textureContaigner.getAsset(textures::ID::credits_original));
    background.setTextureRect(sf::IntRect(0, 0, 640, 400));
    mylib::Timer timer(6000);
    timer.start();
    m_window.clear();
    m_window.draw(background);
    m_window.display();
    bool exitIntro{false};
    while(!timer.isTimeElapsed() && !exitIntro) {
        sf::sleep(sf::milliseconds(100));
        if(isIntroSkipped()) { exitIntro = true; }
    }
    if(!exitIntro) { return true; }
    else { return false; }
}

bool Intro::creditsAdditionnal()
{
    sf::Sprite background;
    background.setTexture(m_textureContaigner.getAsset(textures::ID::credits_additionnal));
    background.setTextureRect(sf::IntRect(0, 0, 640, 400));
    mylib::Timer timer(6000);
    timer.start();
    m_window.clear();
    m_window.draw(background);
    m_window.display();
    bool exitIntro{false};
    while(!timer.isTimeElapsed() && !exitIntro) {
        sf::sleep(sf::milliseconds(100));
        if(isIntroSkipped()) { exitIntro = true; }
    }
    if(exitIntro) { return false; }
    else { return true; }
}

void Intro::loading(const sf::Int32 delay)
{
    Message message(m_language, Message::Messages::Loading);
    m_window.clear();
    m_window.draw(message);
    m_window.display();
    mylib::Timer duration(delay);
    duration.start();
    while(!duration.isTimeElapsed())
        ;
}

bool Intro::launchGame(mylib::Music& music)
{
    Game game(m_window, m_language, m_players);
    return game.launch(music);
}

bool Intro::isIntroSkipped()
{
    sf::Joystick::update();
    bool skipIntro{false};
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {  skipIntro = true; }
    else {
        for(auto joystickID = 0; joystickID < 8; ++joystickID) {
            if(sf::Joystick::isConnected(joystickID)) {
                for(unsigned int button =0; button < sf::Joystick::getButtonCount(joystickID); ++button) {
                    if(sf::Joystick::isButtonPressed(joystickID, button)) { skipIntro = true; }
                }
            }
        }
    }
    if(skipIntro) {
        sf::Event event;
        while(m_window.pollEvent(event)) { }
        return true;
    }
    else { return false; }
}

void Intro::initView()
{
    m_view.setSize(sf::Vector2f(640.f, 400.f));
    m_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    m_view.setCenter(sf::Vector2f(320, 200));
    m_window.setView(m_view);
}

