#include "header/trackREwork.hpp"
#include <iostream>

sf::Color Track::getTrackColor(int x, int y)
{
    return trackImage.getPixel(x, y);
}



bool Track::loadImage(const std::string& title)
{
    return trackImage.loadFromFile(title);
}

bool Track::saveImage(const std::string& title)
{
    return trackImage.saveToFile(title);
}

void Track::unniformiseTrackShadowFile(int width, int higth)
{
    sf::Color color;
    for(auto y = 0; y < higth; ++y) {
        for(auto x = 0; x < width; ++x) {
            color = trackImage.getPixel(x, y);
            if(color.r != 0x0 && color.b != 0x0 && color.g != 0x0){ trackImage.setPixel(x, y, sf::Color(0x404040FF)); }
        }
    }
    trackImage.createMaskFromColor(sf::Color(0x0000FF), 0);
}

void Track::createTrackShadowFile(int width, int higth)
{
    sf::Color color;
    for(auto y = 0; y < higth; ++y) {
        for(auto x = 0; x < width; ++x) {
            color = trackImage.getPixel(x, y);
            if(!isColorGrey(color) || (color.r != 0x10 && color.r != 0x20 && color.r != 0x30 && color.r != 0x41)) {
                trackImage.setPixel(x, y, sf::Color(0x000003FF));                                                                   // pixel is not a shadow
            }
            else {
                switch(color.r)
                {
                    case 0x20 :    // -> 7F
                        color = sf::Color(0x000000FF);
                        color.a = 0x80;
                        break;
                    case 0x30 :    // -> BF

                        color = sf::Color(0x000001FF);
                        color.a = 0x40;
                        break;
                    case 0x41 :    // -> CF
                        color = sf::Color(0x000002FF);
                        color.a = 0x30;
                        break;
                    default :
                        break;
                }
                trackImage.setPixel(x, y, color);
            }
        }
    }
    trackImage.createMaskFromColor(sf::Color(0x000003FF), 0);
}

void Track::reworkTrackShadowFile(int width, int higth)
{
    sf::Color color;
    for(auto y = 0; y < higth; ++y) {
        for(auto x = 0; x < width; ++x) {
            color = trackImage.getPixel(x, y);
            switch(color.b)
            {
                case 0x7F :
                case 0x0 :
                    color = sf::Color(0x000000FF);
                    color.a = 0x80;
                    break;
                case 0xBF :
                    color = sf::Color(0x000001FF);
                case 0x01 :
                    color.a = 0x40;
                    break;
                case 0xCF :
                    color = sf::Color(0x000002FF);
                case 0x02 :
                    color.a = 0x30;
                    break;
                case 0x03 :
                    color.a = 0x0;
                    break;
                default :
                    color = sf::Color(0x000003FF);
                    color.a = 0x0;
                    break;
            }
            trackImage.setPixel(x, y, color);
        }
    }
}

void Track::createTrackRoadFile(int width, int higth)
{
    sf::Color color;
    for(auto y = 0; y < higth; ++y) {
        for(auto x = 0; x < width; ++x) {
            color = trackImage.getPixel(x, y);
            if(!isColorGrey(color) || (color.r != 0x2F && color.r != 0x40 && color.r != 0x50)) {
                trackImage.setPixel(x, y, sf::Color::Black);                                                            // pixel is not a road
            }
            else {
                trackImage.setPixel(x, y, sf::Color::Magenta);
            }
        }
    }
}

bool Track::isColorEqualTo(sf::Color color, sf::Color colorRef)
{
    return color.r == colorRef.r && color.g == colorRef.g && color.b == colorRef.b && color.a == colorRef.a;
}

bool Track::isColorNotEqualTo(sf::Color color, sf::Color colorRef)
{
    return color.r != colorRef.r || color.g != colorRef.g || color.b != colorRef.b || color.a != colorRef.a;
}

bool Track::isColorGrey(sf::Color color)
{
    return color.r == color.g && color.g  == color.b;
}
