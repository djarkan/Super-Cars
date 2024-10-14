#ifndef TRACK_HPP
#define TRACK_HPP

#include <jsonfile/jsonfile.hpp>
#include <SFML/Graphics/Image.hpp>

#include <string>
#include <vector>
#include <array>

class Track {
    public :
                                                                        Track();
                                                                        Track(int trackNB, bool clockwiseRaceRotation);

        void                                                            loadTrackData(const int trackNB);
        sf::Vector2f                                                    getCarSpawnCoords(const unsigned int ranking) const;
        float                                                           getCarSpawnangle(const unsigned int ranking) const;
        unsigned int                                                    getCarSpawnElevation(const unsigned int ranking) const;
        const std::vector<sf::FloatRect>&                               getNearBridgearea() const;
        unsigned int                                                    getBridgeNumber() const;
        const sf::FloatRect&                                            getBridgeBounds(const unsigned int index) const;
        unsigned int                                                    getBridgeOrientation(const unsigned int index) const;
        unsigned int                                                    getArrivalPortalOrientation() const;
        const sf::Vector2f&                                             getArrivalPortalCoords() const;
        const sf::FloatRect&                                            getArrivalPortalArea() const;
        const sf::Vector2f&                                             getHazard(const unsigned int index) const;
        const sf::FloatRect&                                            getAnticheatWaypoint(const unsigned int index) const;
        sf::Vector2f                                                    getCountdownCoords() const;
        const sf::FloatRect&                                            getRankingArea(const unsigned int index) const;
        unsigned int                                                    getRankingAreaNumber() const;
        unsigned int                                                    getTrackLength() const;

    private :
        mylib::JsonFile                                                 m_trackData;
        bool                                                            m_clockwiseRaceRotation;
        sf::Vector2f                                                    resolution;
        sf::Vector2f                                                    arrivalPortalCoords;
        unsigned int                                                    arrivalPortalOrientation;
        sf::FloatRect                                                   arrivalPortalArea;
        int                                                             bridgeNB;
        struct BridgeDrawsetting {
           sf::FloatRect    bridgeBounds;
           unsigned int     orientation;
        };
        std::vector<BridgeDrawsetting>                                  bridgeInfo;
        std::vector<sf::Vector2f>                                       hazardPossibleLocations;
        struct CarSpawnLocation {
            float x;
            float y;
            float angle;
            unsigned int elevation;
        };
        std::vector<CarSpawnLocation>                                   carsSpawnLocationsClock;
        std::vector<CarSpawnLocation>                                   carsSpawnLocationsCounterClock;
        std::vector<sf::FloatRect>                                      antiCheatWaypoints;
        std::vector<sf::FloatRect>                                      nearBridgeArea;
        unsigned int                                                    nbRankingCoords;
        std::vector<sf::FloatRect>                                      RankingCoordsClock;
        std::vector<sf::FloatRect>                                      RankingCoordsCounterClock;
        unsigned int                                                    autoPilotNbWaypoints;
        unsigned int                                                    autoPilotWaypointRadius;
        std::array<std::vector<sf::Vector2f>, 3>                        waypointsLines;
        std::array<unsigned int, 7>                                     firstWaypointClockForComputerCars;
        std::array<unsigned int, 7>                                     firstWaypointCounterClockForComputerCars;
        std::vector<sf::Vector2f>                                       waypointsLinesCoords;
        unsigned int                                                    trackLength;
};

#endif // TRACK_HPP
