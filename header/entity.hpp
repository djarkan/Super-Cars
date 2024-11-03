#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "header/car.hpp"

class Entity : public Car
{
public:
	enum                                        Interaction { None = 0, Bumping, waterShifting, Spining, Pushed };
	enum                                        Direction { Left = 0, Right };

                                                Entity();
    const sf::Vector2f&                         getCarLimit(unsigned int index) const;
    float                                       getAngle() const;
    float                                       getSideAngle() const;
    float                                       getShiftingAngle() const;
    float                                       getSpeed() const;
    float                                       getTopRaceSpeed()  const;
    float                                       getSideSpeed() const;
    int                                         getAcceleration() const;
    float                                       getSpeedLimiter() const;
    sf::Vector2f                                getCenter() const;
    int                                         getElevation() const;
    bool                                        getNearBridgeArea();
    sf::FloatRect                               getLocalBounds() const;
    sf::FloatRect                               getGlobalBounds() const;
    Interaction                                 getInteractionType() const;
    const sf::Vector2f&                         getCornerCoords(const unsigned int whatCorner) const;
    const sf::Vector2f&                         getOldPosition() const;

    void                                        setPosition(const sf::Vector2f& coords);
    void                                        setAngle(float angle);
    void                                        setSpeed(float speed);
    void                                        setTopRaceSpeed(float sideSpeed);
    void                                        setSideSpeed(float sideSpeed);
    void                                        setAcceleration(int acceleration);
    void                                        setSpeedLimiter(float speedLimiter);
    void                                        setElevation(unsigned int elevation);
    void                                        setNearBridgeArea(bool nearBridgeArea);
    
    
    void                                        setInSand(bool inSand);
    void                                        setInteraction(Interaction type, float angle, unsigned int intensity, float speed);

    void                                        updateCarLimits();
    void                                        move();
    void                                        turn(Direction direction);
    void                                        accelerate();
    void                                        decelerate();
    bool                                        isAcceleration();
    bool                                        isShifting() const;

private:
    sf::Vector2f                                m_center;
    float                                       m_angle;                            // current car speed
    float                                       m_sideAngle;                        // deviation angle
    float                                       m_speed;                            // current car speed
    float                                       m_topRaceSpeed;                     // highest speed reached in race
    float                                       m_sideSpeed;                        // deviation speed
    float                                       m_speedLimiter;                     // limiter for computer car
    std::array<sf::Vector2f, 8>                 m_carLimits;                        // corners for collisions and tracks limit detection
    int                                         m_acceleration;                     // 2 : normal acceleration, 3 : turbo charger kit bought
    unsigned int                                m_elevation;                        // altitude to know if car is on or under the bridges
    bool                                        m_accelerationOn;                   // true : car in acceleration false: car in deceleration or stopped
    float                                       m_accelerationTime;                 // length of the acceleration
    unsigned int                                m_turnIntensity;                    // turn length
    bool                                        m_shifting;                         // car is in shifting
    float                                       m_shiftingAngle;                    // angle to shift
    bool                                        m_nearBridgeArea;
    bool                                        m_inSand;
    struct {
        Interaction     type;
        unsigned int    intensity;
        float           angle;
        float           speed;
    }                                           m_interaction;
    sf::Vector2f                                m_oldPosition;
    unsigned int                                m_waypointTarget;

    void                                        handbrakeTurn();
    void                                        interaction();

};

#endif