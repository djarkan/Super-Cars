#include "header/office.hpp"

#include <SFML/Window/Mouse.hpp>

#include "random/random.hpp"
#include "bitmap/simpleAnimation/animation.hpp"
#include "header/inputs.hpp"
#include "triple/triple.hpp"

extern sf::Vector2f windowRatio;
extern std::array<mylib::Triple<std::string, int, int>, 7>     bestWinnersList;

Office::Office(sf::RenderWindow& window, Player& player, BottomPanel& bottomPanel, const unsigned int language) :   m_window{window}, m_player{player}, m_bottomPanel{bottomPanel}, m_language{language}, m_firstTimeIn{true},
                                                                                                                    m_door(sf::FloatRect(0, 0, 87, 240)), m_font(16, 16), m_inputs(window)
{
    loadTextures();
    m_font.setTexture(m_textureContaigner.getAsset(textures::ID::supercarsfont));
    m_font.setSize(16, 16);
    m_text.setFont(&m_font);
    m_text.setPosition(16, 253);
    setSprites();
    loadAnimations();
    m_officeSoundBuffer.loadFromFile("sound/cashdrawer.ogg");
    m_cashDrawerSound.setBuffer(m_officeSoundBuffer);
    initViews();
    switch(m_language) {
        case 0 :
            m_languageJson.loadJsonFile("language/english/office.json");
            break;
        case 1:
            m_languageJson.loadJsonFile("language/usa/office.json");
            break;
        case 2 :
            m_languageJson.loadJsonFile("language/french/office.json");
            break;
        default :
            break;
    }
}

void Office::initViews()
{
    m_topView.setSize(sf::Vector2f(640.f, 360.f));
    m_topView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.90f));
    m_topView.setCenter(sf::Vector2f(320, 180));
    m_bottomView.setSize(sf::Vector2f(640.f, 40.f));
    m_bottomView.setViewport(sf::FloatRect(0.f, 0.9f, 1.f, 0.1f));
    m_bottomView.setCenter(320, 20);

}

void Office::loadTextures()
{
    m_textureContaigner.loadAsset(textures::ID::office, "graphics/office/office.png");
    m_textureContaigner.loadAsset(textures::ID::supercarsfont, "graphics/bitmap_fonts/super_cars_16x16.png");
    m_textureContaigner.loadAsset(textures::ID::spritesheet, "graphics/sprite_sheet/sprite_sheet.png");
    m_textureContaigner.loadAsset(textures::ID::cars, "graphics/cars/cars.png");
}

void Office::setSprites()
{
    m_background.setTexture(m_textureContaigner.getAsset(textures::ID::office));
    m_background.setTextureRect(sf::IntRect(0, 0, 640, 360));
    m_background.setPosition(0, 0);
    m_visualSelector.setTexture(m_textureContaigner.getAsset(textures::ID::spritesheet));
    m_visualSelector.setTextureRect(sf::IntRect(0, 843, 640, 14));
    m_visualSelector.setPosition(3000, 253);
    m_blueCar.setTexture(m_textureContaigner.getAsset(textures::ID::cars));
    m_blueCar.setPosition(190, 303);
    m_redCar.setTexture(m_textureContaigner.getAsset(textures::ID::cars));
    m_redCar.setPosition(290, 300);
    m_whiteCar.setTexture(m_textureContaigner.getAsset(textures::ID::cars));
    m_whiteCar.setPosition(395, 300);
}

void Office::loadAnimations()
{
    mylib::JsonFile jsonAnimations("data/animations/office.json");
    sf::Vector2f animationcoord;
    std::vector<sf::IntRect> frames;
    for(auto i = 0; i < 5; ++i) {
        frames.resize(0);
        animationcoord.x = jsonAnimations.m_Root["office"][i]["destination"].get("x", 100).asFloat();
        animationcoord.y = jsonAnimations.m_Root["office"][i]["destination"].get("y", 100).asFloat();
        bool loop = jsonAnimations.m_Root["office"][i].get("loop", true).asBool();
        bool randomisedLoop = jsonAnimations.m_Root["office"][i].get("randomisedLoop", false).asBool();
        sf::Int32 frameRate =  jsonAnimations.m_Root["office"][i].get("frameRate", 200).asInt();
        sf::IntRect rect;
        for(auto elem : jsonAnimations.m_Root["office"][i]["frames"]){
            rect.left = elem.get("x", 0).asInt();
            rect.top = elem.get("y", 0).asInt();
            rect.width = elem.get("w", 0).asInt();
            rect.height = elem.get("h", 0).asInt();
            frames.push_back(rect);
        }
        mylib::Animation animation(m_textureContaigner.getAsset(textures::ID::spritesheet), animationcoord, loop, randomisedLoop, frames);
        animation.setFrameRate(frameRate);
        mylib::Animation* animPtr = new mylib::Animation (animation);
        *animPtr = std::move(animation);
        m_animPlayer.addAnimation(animPtr);
    }
    m_animPlayer.start();
}

void Office::buy()                                ///// 16,252   16, 268   16,284   16,300   16,316   16,332
{
    bool inOffice{true};                        /////////// mettre les inputs
    sf::Sprite vendorFace;
    vendorFace.setTexture(m_textureContaigner.getAsset(textures::ID::spritesheet));
    vendorFace.setPosition(417, 6);
    Mood vendorMood{Mood::normal};
    unsigned int currentColor{m_player.getCarColor()};
    mylib::Timer commandLimiter(10);
    commandLimiter.start();
    mylib::Timer scrollLimiter(350);
    unsigned int color{m_player.getCarColor()};
    int step{1};                                                                                // 1/ hello /2 choose color 3/choose car model 4/ price announce 5/ negociation until 5 lowering or raising price 6/ buy yes-no 7/ get out
    mylib::Random<int> intGenerator;
    bool chooseDialog{true};
    bool carBought{false};
    std::array<int, 5> loweringPriceChoices{0,0,0,0,0};
    std::string price{""};
    int uppingNumber{0};
    int loweringNumber{0};
    int upLowNumber{0};
    unsigned int carModelNumber{0};
    Car::Type carToBuy;
    int carPrice{0};
    unsigned int playerCash{m_player.getMoney()};
    int line{0};
    sf::Vector2i mouseCoords;
    while(inOffice) {
        if(commandLimiter.isTimeElapsed()) {
            commandLimiter.restart();
            m_inputs.readInput(m_player.getJoystickID());
        }
        if(m_inputs.isCommandAvailable()) { 
            m_command = m_inputs.getInput(); 
            if (m_command.action == CommandType::joystiskMoved && step != 2) {
                sf::Vector2i mouseCoords = sf::Mouse::getPosition(m_window);
                mouseCoords.x += ((static_cast<int>(m_command.offsetX) / 100) * 4);
                mouseCoords.y += ((static_cast<int>(m_command.offsetY) / 100) * 4);
                sf::Mouse::setPosition(mouseCoords, m_window);
            }
        }
        switch(step){
            case 1 :                                                            // welcome
                if(chooseDialog) {
                    m_text.setText("");
                    if(m_language < 2) { price = m_languageJson.m_Root["office"]["currency"].asString() + "500."; }
                    else { price = "500" + m_languageJson.m_Root["office"]["currency"].asString() + "."; }
                    m_text.setText(m_languageJson.m_Root["office"]["welcome"][intGenerator.randomNumber(0, 7)].asString() + " \n\nOr new color for your car for " + price);
                    vendorMood = Mood::happy;
                    chooseDialog = false;
                }
                else {
                    std::string text{m_text.getText()};
                    mouseCoords = sf::Mouse::getPosition(m_window);
                    mouseCoords.x /= windowRatio.x;
                    mouseCoords.y /= windowRatio.y;
                    if(mouseCoords.y >= 253 && mouseCoords.y < 253 + ((6 - static_cast<int>(carModelNumber)) * 16)) {
                        line = (mouseCoords.y - 253) /16;
                        if(line < 3) { m_visualSelector.setPosition(0, 253 + 16); }
                        else { m_visualSelector.setPosition(0, 253 + (4 * 16)); }
                    }
                    else {
                        m_visualSelector.setPosition(3000, 253);
                        line = -1;
                    }
                    if(m_command.action == CommandType::joystiskButtonPressed || m_command.action == CommandType::mouseLeftButtonPressed) {
                        if(m_command.coords.x >= 16 && m_command.coords.x <= 608 && m_command.coords.y >= 253 && m_command.coords.y <= 301) {
                            if(m_player.getCarType() == Car::Type::Retron_Parsec_Turbo8 || carBought) {
                                m_visualSelector.setPosition(3000, 253);
                                break;
                            }
                            step = 3;
                            vendorMood = Mood::normal;
                            chooseDialog = true;
                            m_visualSelector.setPosition(3000, 253);
                        }
                        else {
                            if(m_command.coords.x >= 16 && m_command.coords.x <= 608 && m_command.coords.y >= 301 && m_command.coords.y <= 347) {
                                step = 2;
                                vendorMood = Mood::normal;
                                chooseDialog = true;
                                m_visualSelector.setPosition(3000, 253);
                            }
                        }
                    }
                }
                break;
            case 2 :                                                            // recolor the car
                if(chooseDialog) {
                    scrollLimiter.start();
                    m_window.setMouseCursorVisible(false);
                    m_text.setText("");
                    m_text.setText(m_languageJson.m_Root["office"]["coloring"].asString());
                    chooseDialog = false;
                }
                else {
                    if(m_command.action == CommandType::joystiskMoved) {
                        if(scrollLimiter.isTimeElapsed()) {
                            scrollLimiter.restart();
                            if(m_command.offsetX < 0) {
                                if(color == 1) { color = 13; }
                                else { --color; }
                            }
                            else {
                                if(m_command.offsetX > 0) {
                                    if(color == 13) { color = 1; }
                                    else { ++color; }
                                }
                            }
                        }
                    }
                }
                if(m_command.action == CommandType::joystiskButtonPressed || m_command.action == CommandType::mouseLeftButtonPressed) {
                    m_window.setMouseCursorVisible(true);
                    if(m_player.getMoney() >= 500) {
                        if(color == currentColor) {
                            step = 1;
                            chooseDialog = true;
                            vendorMood = Mood::happy;
                            break;
                        }
                        else {
                            m_player.setCarColor(color);
                            m_player.setMoney(m_player.getMoney() - 500);
                            m_bottomPanel.updateMoney();
                            m_cashDrawerSound.play();
                            chooseDialog = true;
                            step = 1;
                        }
                    }
                    else {
                        m_text.setText(m_languageJson.m_Root["office"]["notEnoughMoney"][intGenerator.randomNumber(0, 8)].asString());
                        vendorMood = Mood::angry;
                        step = 7;
                    }
                }
                break;
            case 3 :                                                    // choose model to buy
                if(chooseDialog) {
                    carModelNumber = static_cast<unsigned int>(m_player.getCarType());
                    if(carModelNumber < 6) {
                        std::string text{""};
                        for(auto i = carModelNumber + 1; i < m_languageJson.m_Root["office"]["cars"].size(); ++i) {
                            text += m_languageJson.m_Root["office"]["cars"][i]["model2"].asString() + '\n';
                        }
                        chooseDialog = false;
                        m_text.setText(text);
                    }
                    else {
                        chooseDialog = true;
                        step = 1;
                    }
                }
                else {
                    mouseCoords = sf::Mouse::getPosition(m_window);
                    mouseCoords.x /= windowRatio.x;
                    mouseCoords.y /= windowRatio.y;
                    if(mouseCoords.y >= 253 && mouseCoords.y < 253 + ((6 - static_cast<int>(carModelNumber)) * 16)) {
                        line = (mouseCoords.y - 253) /16;
                        m_visualSelector.setPosition(0, 253 + (line * 16));
                    }
                    else {
                        m_visualSelector.setPosition(3000, 253);
                        line = -1;
                    }
                    if(m_command.action == CommandType::joystiskButtonPressed || m_command.action == CommandType::mouseLeftButtonPressed) {
                        if(line == -1) { break; }
                        carToBuy = static_cast<Car::Type>(carModelNumber + line + 1);
                        step = 4;
                        vendorMood = Mood::normal;
                        chooseDialog = true;
                        m_visualSelector.setPosition(3000, 253);
                    }
                }
                break;
            case 4 :                                                    // price announce
                if(chooseDialog) {
                    std::string text{""};
                    vendorMood = Mood::happy;
                    m_player.setMoney(m_player.getMoney() + m_languageJson.m_Root["office"]["cars"][static_cast<unsigned int>(m_player.getCarType())]["price"].asInt());
                    m_bottomPanel.updateMoney();
                    carPrice = 48500 + (30000 * static_cast<unsigned int>(carToBuy)) + (intGenerator.randomNumber(1, 140) * 50);
                    int rand = intGenerator.randomNumber(0, 7);
                    text = m_languageJson.m_Root["office"]["priceAnnounce"][rand].asString();
                    if(m_language < 2) { price = m_languageJson.m_Root["office"]["currency"].asString() + std::to_string(carPrice); }
                    else { price = std::to_string(carPrice) + m_languageJson.m_Root["office"]["currency"].asString(); }
                    auto pos = text.find("PRICE");
                    text.erase(pos, 5);
                    text.insert(pos, price);
                    pos = text.find("MODEL1");
                    if(pos != std::string::npos) {
                        text.erase(pos, 6);
                        text.insert(pos, m_languageJson.m_Root["office"]["cars"][static_cast<unsigned int>(carToBuy)]["model1"].asString());
                    }
                    else {
                        pos = text.find("MODEL2");
                        if(pos != std::string::npos) {
                            text.erase(pos, 6);
                            text.insert(pos, m_languageJson.m_Root["office"]["cars"][static_cast<unsigned int>(carToBuy)]["model2"].asString());
                        }
                    }
                    std::string oldCarValue{""};
                    if(m_language < 2) { oldCarValue = m_languageJson.m_Root["office"]["currency"].asString() + m_languageJson.m_Root["office"]["cars"][static_cast<unsigned int>(m_player.getCarType())]["sellPrice"].asString(); }
                    else { oldCarValue = m_languageJson.m_Root["office"]["cars"][static_cast<unsigned int>(m_player.getCarType())]["sellPrice"].asString() + m_languageJson.m_Root["office"]["currency"].asString(); }
                    pos = text.find("MONEY");
                    text.erase(pos, 5);
                    text.insert(pos, oldCarValue);
                    m_text.setText(text);
                    chooseDialog = false;
                }
                else {
                    if(m_command.action == CommandType::joystiskButtonPressed || m_command.action == CommandType::mouseLeftButtonPressed) {
                        step = 5;
                        chooseDialog = true;
                        m_visualSelector.setPosition(3000, 253);
                    }
                }
                break;
            case 5 :                                                        // negociation
                if(chooseDialog) {
                    std::string text{""};
                    vendorMood = Mood::normal;
                    text = m_languageJson.m_Root["office"]["buy"].asString();
                    auto pos = text.find("PRICE");
                    text.erase(pos, 5);
                    text.insert(pos, price);
                    for(int i = 0; i < 5; ++i) {
                        int randomNumber{0};
                        do {
                            randomNumber = intGenerator.randomNumber(0, 183);
                        }
                        while(randomNumber == loweringPriceChoices[0] || randomNumber == loweringPriceChoices[1] || randomNumber == loweringPriceChoices[2] || randomNumber == loweringPriceChoices[3] || randomNumber == loweringPriceChoices[4]);
                        loweringPriceChoices[i] = randomNumber;
                        text += '\n' + m_languageJson.m_Root["office"]["negociate"][randomNumber]["proposition"].asString();
                    }
                    m_text.setText(text);
                    chooseDialog = false;
                }
                else {                  //////////////////////// selector est décalé verticalement de 4 5 pixels et apparait disparait vite fait quand memonte ou descend hors de la dernière ligne selectionnable
                    mouseCoords = sf::Mouse::getPosition(m_window);
                    mouseCoords.x /= windowRatio.x;
                    mouseCoords.y /= windowRatio.y;
                    if(mouseCoords.y >= 253 && mouseCoords.y <= 253 + (6 * 16)) {
                        line = (mouseCoords.y - 253) /16;
                        m_visualSelector.setPosition(0, 253 + (line * 16));
                    }
                    else {
                        m_visualSelector.setPosition(3000, 253);
                        line = -1;
                    }
                    if(m_command.action == CommandType::joystiskButtonPressed || m_command.action == CommandType::mouseLeftButtonPressed) {
                        if(line == -1) { break; }
                        if(line == 0) {                                                             // buying
                            if(m_player.getMoney() >= static_cast<unsigned int>(carPrice)) {                                   // player has the money
                                vendorMood = Mood::happy;
                                m_player.setMoney(m_player.getMoney() - carPrice);
                                m_player.setCarType(carToBuy);
                                m_player.setCarBodyState(1);
                                m_player.setCarEngineState(1);
                                m_player.setCarTyresState(1);
                                m_player.setCarFuelState(1);
                                m_bottomPanel.updateUsury();
                                m_bottomPanel.textConfiguration();
                                step = 8;
                                carBought = true;
                                m_cashDrawerSound.play();
                                m_visualSelector.setPosition(3000, 253);
                                break;
                            }
                            else {                                                                  // player has not enough money
                                vendorMood = Mood::angry;
                                std::string text{""};
                                text = m_languageJson.m_Root["office"]["notEnoughMoney"][intGenerator.randomNumber(0, 9)].asString();
                                auto pos = text.find("PRICE");
                                if(pos != std::string::npos) {
                                    text.erase(pos, 5);
                                    text.insert(pos, price);
                                    if(pos != std::string::npos) {
                                        text.erase(pos, 5);
                                        text.insert(pos, price);
                                    }
                                }
                                m_text.setText(text);
                                step = 9;                                                           // only action is the door
                            }
                        }
                        m_visualSelector.setPosition(3000, 253);
                        int proposition = loweringPriceChoices[line -1];
                        if(proposition < 97) {
                            step = 9;
                            vendorMood = static_cast<Mood>(m_languageJson.m_Root["office"]["negociate"][proposition]["mood"].asInt());
                            m_text.setText(m_languageJson.m_Root["office"]["negociate"][proposition]["answer"].asString());
                        }
                        else {
                            upLowNumber++;
                            if(proposition < 152) {
                                switch(uppingNumber) {
                                    case 0 :
                                        carPrice -= intGenerator.randomNumber(160, 300) * 50;
                                        break;
                                    case 1 :
                                        carPrice -= intGenerator.randomNumber(80, 160) * 50;
                                        break;
                                    case 2 :
                                        carPrice -= intGenerator.randomNumber(40, 80) * 50;
                                        break;
                                    case 3 :
                                        carPrice -= intGenerator.randomNumber(20, 40) * 50;
                                        break;
                                    case 4 :
                                        carPrice -= intGenerator.randomNumber(2, 20) * 50;
                                        break;
                                    default :
                                        break;
                                }
                                ++uppingNumber;
                            }
                            else {
                                switch(loweringNumber) {
                                    case 0 :
                                        if(uppingNumber > 0) { carPrice += intGenerator.randomNumber(120, 240) * 50; }
                                        else {
                                            carPrice += intGenerator.randomNumber(2, 30) * 50;
                                            --uppingNumber;
                                        }
                                        break;
                                    case 1 :
                                        carPrice += intGenerator.randomNumber(60, 120) * 50;
                                        break;
                                    case 2 :
                                        carPrice += intGenerator.randomNumber(30, 60) * 50;
                                        break;
                                    case 3 :
                                        carPrice += intGenerator.randomNumber(2, 30) * 50;
                                        break;
                                    case 4 :
                                        carPrice += intGenerator.randomNumber(2, 30) * 50;
                                        break;
                                    default :
                                        break;

                                }
                                ++uppingNumber;
                            }
                            chooseDialog = true;
                            if(m_language < 2) { price = m_languageJson.m_Root["office"]["currency"].asString() + std::to_string(carPrice); }
                            else { price = std::to_string(carPrice) + m_languageJson.m_Root["office"]["currency"].asString(); }
                            vendorMood = static_cast<Mood>(m_languageJson.m_Root["office"]["negociate"][proposition]["mood"].asInt());
                            std::string text{""};
                            if(upLowNumber < 5) {
                                text = m_languageJson.m_Root["office"]["negociate"][proposition]["answer"].asString();
                                step = 6;
                            }
                            else {
                                text = m_languageJson.m_Root["office"]["buyOrNotBuy"].asString();
                                step = 7;
                            }
                            auto pos = text.find("PRICE");
                            text.erase(pos, 5);
                            text.insert(pos, price);
                            m_text.setText(text);
                        }
                    }
                }
                break;
            case 6 :                                                   // vendor answer validation
                if(m_command.action == CommandType::joystiskButtonPressed || m_command.action == CommandType::mouseLeftButtonPressed) {
                    step = 5;
                }
                break;
            case 7 :
                                                                        // buy or not after attempted 5 times
                mouseCoords = sf::Mouse::getPosition(m_window);
                mouseCoords.x /= windowRatio.x;
                mouseCoords.y /= windowRatio.y;
                if(mouseCoords.y >= 253 && mouseCoords.y <= 253 + + 32) {
                    line = (mouseCoords.y - 253) /16;
                    m_visualSelector.setPosition(0, 253 + (line * 16));
                }
                else {
                    m_visualSelector.setPosition(3000, 253);
                    line = -1;
                }
                if(m_command.action == CommandType::joystiskButtonPressed || m_command.action == CommandType::mouseLeftButtonPressed) {
                    if(m_command.coords.y >= 253 &&  m_command.coords.y <= 268 ) {  // buy the car
                         if(m_player.getMoney() >= static_cast<unsigned int>(carPrice)) {                                   // player has the money
                                vendorMood = Mood::happy;
                                m_player.setMoney(m_player.getMoney() - carPrice);
                                m_player.setCarType(carToBuy);
                                m_player.setCarBodyState(1);
                                m_player.setCarEngineState(1);
                                m_player.setCarTyresState(1);
                                m_player.setCarFuelState(1);
                                m_bottomPanel.updateUsury();
                                m_bottomPanel.textConfiguration();
                                step = 8;
                                carBought = true;
                                m_cashDrawerSound.play();
                            }
                            else {                                                                  // player has not enough money
                                vendorMood = Mood::angry;
                                std::string text{""};
                                text = m_languageJson.m_Root["office"]["notEnoughMoney"][intGenerator.randomNumber(0, 9)].asString();
                                auto pos = text.find("PRICE");
                                if(pos != std::string::npos) {
                                    text.erase(pos, 5);
                                    text.insert(pos, price);
                                    pos = text.find("PRICE");
                                    if(pos != std::string::npos) {
                                        text.erase(pos, 5);
                                        text.insert(pos, price);
                                    }
                                }
                                m_text.setText(text);
                                step = 9;                                                           // only action is the door
                            }
                    }
                    if(m_command.coords.y >= 269 &&  m_command.coords.y <= 286 ) {
                        step = 9;
                    }
                }
                break;
            case 8 :

                if(m_language < 2) { price = m_languageJson.m_Root["office"]["currency"].asString() + "500."; }
                else { price = "500" + m_languageJson.m_Root["office"]["currency"].asString() + "."; }
                m_text.setText(m_languageJson.m_Root["office"]["thanks"][intGenerator.randomNumber(0, 7)].asString() + " \n\n\nOr new color for your car for " + price);
                vendorMood = Mood::happy;
                chooseDialog = false;
                step = 1;
                break;
            default:
                break;
        }
        if((m_command.action == CommandType::joystiskButtonPressed || m_command.action == CommandType::mouseLeftButtonPressed) && m_door.isPressed(m_command.coords)) {
            inOffice = false;
            if(m_player.getCarType() != carToBuy) {                                                 // player doesn't steal money whey quiting the office
                m_player.setMoney(playerCash);
                m_bottomPanel.updateMoney();
            }
        }
        m_window.clear();
        m_window.setView(m_topView);
        m_window.draw(m_background);
        m_animPlayer.update();
        m_window.draw(m_animPlayer);
        selectVendorFace(vendorFace, vendorMood);
        m_window.draw(vendorFace);
        m_window.draw(m_text);
        m_window.draw(m_visualSelector);
        if(step == 2) {
            m_blueCar.setTextureRect(sf::IntRect(2, 117 + ((static_cast<int>(color) -1) * 113), 47, 31));
            m_redCar.setTextureRect(sf::IntRect(2, 152 + ((static_cast<int>(color) -1) * 113), 48, 35));
            m_whiteCar.setTextureRect(sf::IntRect(2, 191 + ((static_cast<int>(color) -1) * 113), 52, 35));
            m_window.draw(m_blueCar);
            m_window.draw(m_redCar);
            m_window.draw(m_whiteCar);
        }
        m_window.setView(m_bottomView);
        m_window.draw(m_bottomPanel);
        m_window.display();
    }
    bestWinnersList[0].second = m_player.getMoney();
}

void Office::selectVendorFace(sf::Sprite& vendorFace, Mood mood)
{
    switch(mood) {
        case Mood::happy :
            vendorFace.setTextureRect(sf::IntRect(0, 860, 65, 92));
            break;
        case Mood::normal :
            vendorFace.setTextureRect(sf::IntRect(80, 860, 65, 92));
            break;
        case Mood::unhappy :
            vendorFace.setTextureRect(sf::IntRect(160, 860, 65, 92));
            break;
        case Mood::angry :
            vendorFace.setTextureRect(sf::IntRect(550, 860, 65, 92));
            break;
        default :
            break;
    }
}
