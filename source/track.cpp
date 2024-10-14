#include "header/track.hpp"

#include <iostream>

Track::Track()
{

}

Track::Track(int trackNB, bool clockwiseRaceRotation) : m_clockwiseRaceRotation{clockwiseRaceRotation}
{
std::cout << "loading track data." << std::endl;
    loadTrackData(trackNB);

std::cout << "track data loaded." << std::endl;
}

void Track::loadTrackData(const int trackNB)
{
        m_trackData.loadJsonFile("data/tracks/track" + std::to_string(trackNB) + ".json");
//std::cout << m_trackData.m_Root << std::endl;
        resolution.x = m_trackData.m_Root["track"]["resolution"].get("width",0).asFloat();
        resolution.y = m_trackData.m_Root["track"]["resolution"].get("higth",0).asFloat();
        arrivalPortalCoords.x = m_trackData.m_Root["track"]["arrivalDrawPortal"].get("x",0).asFloat();
        arrivalPortalCoords.y = m_trackData.m_Root["track"]["arrivalDrawPortal"].get("y",0).asFloat();
        arrivalPortalOrientation = m_trackData.m_Root["track"]["arrivalDrawPortal"].get("orientation",0).asInt();
        arrivalPortalArea.left = m_trackData.m_Root["track"]["arrival"].get("x",0).asFloat();
        arrivalPortalArea.top = m_trackData.m_Root["track"]["arrival"].get("y",0).asFloat();
        arrivalPortalArea.width = m_trackData.m_Root["track"]["arrival"].get("w",0).asFloat();
        arrivalPortalArea.height = m_trackData.m_Root["track"]["arrival"].get("h",0).asFloat();
        bridgeNB = m_trackData.m_Root["track"]["bridges"].get("bridgeNb",0).asInt();
        trackLength = m_trackData.m_Root["track"]["trackLength"].asInt();
        BridgeDrawsetting bridgeDrawsetting;
        for(auto i = 0; i < bridgeNB; ++i) {
            bridgeDrawsetting.bridgeBounds.left = m_trackData.m_Root["track"]["bridges"]["locations"][i].get("x",0).asFloat();
            bridgeDrawsetting.bridgeBounds.top = m_trackData.m_Root["track"]["bridges"]["locations"][i].get("y",0).asFloat();
            bridgeDrawsetting.bridgeBounds.width = m_trackData.m_Root["track"]["bridges"]["locations"][i].get("w",0).asFloat();
            bridgeDrawsetting.bridgeBounds.height = m_trackData.m_Root["track"]["bridges"]["locations"][i].get("h",0).asFloat();
            bridgeDrawsetting.orientation = m_trackData.m_Root["track"]["bridges"]["locations"][i].get("orientation",0).asInt();
            bridgeInfo.push_back(bridgeDrawsetting);
        }
        sf::Vector2f coords;
        for(unsigned int  i = 0; i < 16; ++i) {
            coords.x = m_trackData.m_Root["track"]["hazardPossibleLocations"][i].get("x",0).asFloat();
            coords.y = m_trackData.m_Root["track"]["hazardPossibleLocations"][i].get("y",0).asFloat();
            hazardPossibleLocations.push_back(coords);
        }
        sf::FloatRect area;
        for(unsigned int i = 0; i < 3; ++i) {
            area.left = m_trackData.m_Root["track"]["antiCheat"]["antiCheatWaypoints"][i].get("x",0).asFloat();
            area.top = m_trackData.m_Root["track"]["antiCheat"]["antiCheatWaypoints"][i].get("y",0).asFloat();
            area.width = m_trackData.m_Root["track"]["antiCheat"]["antiCheatWaypoints"][i].get("w",0).asFloat();
            area.height = m_trackData.m_Root["track"]["antiCheat"]["antiCheatWaypoints"][i].get("h",0).asFloat();
            antiCheatWaypoints.push_back(area);
        }
        for(unsigned int  i = 0; i < m_trackData.m_Root["track"]["elevation"]["nearBridgearea"].size(); ++i) {
            area.left = m_trackData.m_Root["track"]["elevation"]["nearBridgearea"][i].get("x",0).asFloat();
            area.top = m_trackData.m_Root["track"]["elevation"]["nearBridgearea"][i].get("y",0).asFloat();
            area.width = m_trackData.m_Root["track"]["elevation"]["nearBridgearea"][i].get("w",0).asFloat();
            area.height = m_trackData.m_Root["track"]["elevation"]["nearBridgearea"][i].get("h",0).asFloat();
            nearBridgeArea.push_back(area);
        }
        nbRankingCoords = m_trackData.m_Root["track"].get("nbRankingCoords",0).asInt();
        for(unsigned int i = 0; i < nbRankingCoords; ++i) {
            area.left = m_trackData.m_Root["track"]["racingRankingCoordsClock"]["RankingCoords"][i].get("x",0).asFloat();
            area.top = m_trackData.m_Root["track"]["racingRankingCoordsClock"]["RankingCoords"][i].get("y",0).asFloat();
            area.width = m_trackData.m_Root["track"]["racingRankingCoordsClock"]["RankingCoords"][i].get("w",0).asFloat();
            area.height = m_trackData.m_Root["track"]["racingRankingCoordsClock"]["RankingCoords"][i].get("h",0).asFloat();
            RankingCoordsClock.push_back(area);
        }
        for(unsigned int i = 0; i < nbRankingCoords; ++i) {
            area.left = m_trackData.m_Root["track"]["racingRankingCoordsCounterClock"]["RankingCoords"][i].get("x",0).asFloat();
            area.top = m_trackData.m_Root["track"]["racingRankingCoordsCounterClock"]["RankingCoords"][i].get("y",0).asFloat();
            area.width = m_trackData.m_Root["track"]["racingRankingCoordsCounterClock"]["RankingCoords"][i].get("w",0).asFloat();
            area.height = m_trackData.m_Root["track"]["racingRankingCoordsCounterClock"]["RankingCoords"][i].get("h",0).asFloat();
            RankingCoordsCounterClock.push_back(area);
        }
}

sf::Vector2f Track::getCarSpawnCoords(const unsigned int ranking) const
{
    if(m_clockwiseRaceRotation) { return sf::Vector2f(m_trackData.m_Root["track"]["carsSpawnLocationsClock"][ranking]["x"].asFloat(), m_trackData.m_Root["track"]["carsSpawnLocationsClock"][ranking]["y"].asFloat()); }
    else { return sf::Vector2f(m_trackData.m_Root["track"]["carsSpawnLocationsCounterClock"][ranking]["x"].asFloat(), m_trackData.m_Root["track"]["carsSpawnLocationsCounterClock"][ranking]["y"].asFloat()); }
}

float Track::getCarSpawnangle(const unsigned int ranking) const
{
    if(m_clockwiseRaceRotation) { return m_trackData.m_Root["track"]["carsSpawnLocationsClock"][ranking]["angle"].asFloat(); }
    else { return m_trackData.m_Root["track"]["carsSpawnLocationsCounterClock"][ranking]["angle"].asFloat(); }
}

unsigned int Track::getCarSpawnElevation(const unsigned int ranking) const
{
    if(m_clockwiseRaceRotation) { return m_trackData.m_Root["track"]["carsSpawnLocationsClock"][ranking]["elevation"].asInt(); }
    else { return m_trackData.m_Root["track"]["carsSpawnLocationsCounterClock"][ranking]["elevation"].asInt(); }
}

const std::vector<sf::FloatRect>& Track::getNearBridgearea() const
{
    return nearBridgeArea;
}

unsigned int Track::getBridgeNumber() const
{
    return bridgeNB;
}

const sf::FloatRect& Track::getBridgeBounds(const unsigned int index) const
{
    return bridgeInfo[index].bridgeBounds;
}

unsigned int Track::getBridgeOrientation(const unsigned int index) const
{
    return bridgeInfo[index].orientation;
}

unsigned int Track::getArrivalPortalOrientation() const
{
    return arrivalPortalOrientation;
}

const sf::Vector2f& Track::getArrivalPortalCoords() const
{
    return arrivalPortalCoords;
}

const sf::FloatRect& Track::getArrivalPortalArea() const
{
    return arrivalPortalArea;
}

const sf::Vector2f& Track::getHazard(const unsigned int index) const
{
    return hazardPossibleLocations[index];
}

const sf::FloatRect& Track::getAnticheatWaypoint(const unsigned int index) const
{
    return antiCheatWaypoints[index];
}

sf::Vector2f Track::getCountdownCoords() const
{
    sf::Vector2f countdownCoords(0, 0);
    if(m_clockwiseRaceRotation) {
        countdownCoords.x = m_trackData.m_Root["track"]["countdownCoordsClock"].get("x",0).asFloat();
        countdownCoords.y = m_trackData.m_Root["track"]["countdownCoordsClock"].get("y",0).asFloat();
    }
    else {
        countdownCoords.x = m_trackData.m_Root["track"]["countdownCoordsCounterClock"].get("x",0).asFloat();
        countdownCoords.y = m_trackData.m_Root["track"]["countdownCoordsCounterClock"].get("y",0).asFloat();
    }
    return countdownCoords;
}

const sf::FloatRect& Track::getRankingArea(const unsigned int index) const
{
    if(m_clockwiseRaceRotation) { return RankingCoordsClock[index]; }
    else { return RankingCoordsCounterClock[index]; }
}

unsigned int Track::getRankingAreaNumber() const
{
    return nbRankingCoords;
}

unsigned int Track::getTrackLength() const
{
    return trackLength;
}