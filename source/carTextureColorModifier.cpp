#include "header/carTextureColorModifier.hpp"

#include <SFML/Graphics/Image.hpp>
#include <iostream>

void CarTextureColorModifier::changeColors(sf::Color darkColor, sf::Color mediumColor, sf::Color lightColor)
{
    sf::Image carImage;
    if(!carImage.loadFromFile("graphics/cars/cars.png")) {
       std::cout << "Loading image file error." << std::endl;
    }
    sf::Color color;
    for(auto y = 4; y < 110; ++y) {
        for(auto x = 0; x < 1370; ++x) {
            color = carImage.getPixel(x, y);
            if(color == sf::Color(0x664400FF)) { carImage.setPixel(x, y, darkColor); }
            else
                if(color == sf::Color(0x886600FF)) { carImage.setPixel(x, y, mediumColor); }
                else
                    if(color == sf::Color(0xAA8800FF)) { carImage.setPixel(x, y, lightColor); }
        }
    }
    carImage.saveToFile("graphics/cars/recoloredcars.png");
}
