#ifndef TRACKREWORK_HPP
#define TRACKREWORK_HPP

#include <jsonfile/jsonfile.hpp>
#include <SFML/Graphics/Image.hpp>
#include <string>

class Track
{
    public :
        enum class              flowDirection {west = 0, northWest, north, northEast, east, southEast, south, southWest};

        sf::Color               getTrackColor(int, int);


        bool                    loadImage(const std::string&);
        bool                    saveImage(const std::string&);
        void                    createTrackShadowFile(int, int);
        void                    unniformiseTrackShadowFile(int, int);
        void                    createTrackRoadFile(int, int);
        void                    reworkTrackShadowFile(int width, int higth);

    private :
        sf::Image               trackImage;

        bool                    isColorEqualTo(sf::Color, sf::Color);
        bool                    isColorNotEqualTo(sf::Color, sf::Color);
        bool                    isColorGrey(sf::Color color);
};
#endif // TRACKREWORK_HPP
