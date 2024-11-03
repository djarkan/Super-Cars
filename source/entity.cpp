#include "header/entity.hpp"

#include <cmath>

Entity::Entity() : m_angle{ 0 }, m_sideAngle{ 0 }, m_shiftingAngle{ 0 }, m_speed{ 0 }, m_topRaceSpeed{ 0 }, m_sideSpeed{ 0 }, m_speedLimiter{ 1.f }, m_acceleration{ 2 }, m_elevation{ 1 },
                   m_accelerationOn{ false }, m_accelerationTime{ 0 }, m_turnIntensity{ 0 }, m_shifting{ false }, m_nearBridgeArea{ false }, m_inSand{ false }, m_waypointTarget{ 0 }
{
    m_interaction.type = Interaction::None;
    m_interaction.angle = 0;
    m_interaction.intensity = 0;
}

void Entity::updateCarLimits()
{
    unsigned int frame = getCurrentFrame();
    m_center = getPosition();
    sf::Vector2f origin{ getOrigin() };
    if (frame == 22 || frame == 23 || frame <= 2) {
        m_carLimits[0].x = m_center.x - origin.x + 1;                               // middle back
        m_carLimits[1].x = m_center.x + origin.x - 2;                               // middle front
        m_carLimits[2].x = m_center.x - origin.x + 2;                               // back left
        m_carLimits[3].x = m_center.x + origin.x - 6;                               // front left
        m_carLimits[4].x = m_center.x + origin.x - 6;                               // front right
        m_carLimits[5].x = m_center.x - origin.x + 2;                               // back right
        m_carLimits[6].x = m_center.x + origin.x - 2;                               // <- right light
        m_carLimits[7].x = m_center.x + origin.x - 2;                               // <- left light

        m_carLimits[0].y = m_center.y;                                              // middle back
        m_carLimits[1].y = m_center.y;                                              // middle front
        m_carLimits[2].y = m_center.y - origin.y + 4;                               // back left
        m_carLimits[3].y = m_center.y - origin.y + 4;                               // front left
        m_carLimits[4].y = m_center.y + origin.y - 6;                               // front right
        m_carLimits[5].y = m_center.y + origin.y - 6;                               // back right
        m_carLimits[6].y = m_center.y - origin.y + 10;                              // <- right light
        m_carLimits[7].y = m_center.y + origin.y - 12;                              // <- left light

    }
    else
        if ((frame >= 3 && frame <= 8)) {
            m_carLimits[0].x = m_center.x - origin.x;                               // middle back
            m_carLimits[1].x = m_center.x + origin.x - 2;                           // middle front
            m_carLimits[2].x = m_center.x - origin.x + 2;                           // back left
            m_carLimits[3].x = m_center.x + origin.x - 6;                           // front left
            m_carLimits[4].x = m_center.x + origin.x - 6;                           // front right
            m_carLimits[5].x = m_center.x - origin.x + 2;                           // back right
            m_carLimits[6].x = m_center.x + origin.x - 2;                           // <- right light
            m_carLimits[7].x = m_center.x + origin.x - 2;                           // <- left light

            m_carLimits[0].y = m_center.y + 2;                                      // middle back
            m_carLimits[1].y = m_center.y + 2;                                      // middle front
            m_carLimits[2].y = m_center.y + 2 - origin.y + 4;                       // back left
            m_carLimits[3].y = m_center.y + 2 - origin.y + 4;                       // front left
            m_carLimits[4].y = m_center.y + 2 + origin.y - 6;                       // front right
            m_carLimits[5].y = m_center.y + 2 + origin.y - 6;                       // back right
            m_carLimits[6].y = m_center.y + 2 - origin.y + 10;                      // <- right light
            m_carLimits[7].y = m_center.y + 2 + origin.y - 12;                      // <- left light
        }
        else
            if (frame >= 9 && frame <= 15) {
                m_carLimits[0].x = m_center.x + 2 - origin.x;                       // middle back
                m_carLimits[1].x = m_center.x + 2 + origin.x - 2;                   // middle front
                m_carLimits[2].x = m_center.x + 2 - origin.x + 2;                   // back left
                m_carLimits[3].x = m_center.x + 2 + origin.x - 6;                   // front left
                m_carLimits[4].x = m_center.x + 2 + origin.x - 6;                   // front right
                m_carLimits[5].x = m_center.x + 2 - origin.x + 2;                   // back right
                m_carLimits[6].x = m_center.x + 2 + origin.x - 2;                   // <- right light
                m_carLimits[7].x = m_center.x + 2 + origin.x - 2;                   // <- left light

                m_carLimits[0].y = m_center.y + 2;                                  // middle back
                m_carLimits[1].y = m_center.y + 2;                                  // middle front
                m_carLimits[2].y = m_center.y + 2 - origin.y + 4;                   // back left
                m_carLimits[3].y = m_center.y + 2 - origin.y + 4;                   // front left
                m_carLimits[4].y = m_center.y + 2 + origin.y - 6;                   // front right
                m_carLimits[5].y = m_center.y + 2 + origin.y - 6;                   // back right
                m_carLimits[6].y = m_center.y + 2 - origin.y + 10;                  // <- right light
                m_carLimits[7].y = m_center.y + 2 + origin.y - 12;                  // <- left light

            }
            else
                if (frame >= 16 && frame <= 21) {
                    m_carLimits[0].x = m_center.x + 2 - origin.x;                   // middle back
                    m_carLimits[1].x = m_center.x + 2 + origin.x - 2;               // middle front
                    m_carLimits[2].x = m_center.x + 2 - origin.x + 2;               // back left
                    m_carLimits[3].x = m_center.x + 2 + origin.x - 4;               // front left
                    m_carLimits[4].x = m_center.x + 2 + origin.x - 4;               // front right
                    m_carLimits[5].x = m_center.x + 2 - origin.x + 2;               // back right
                    m_carLimits[6].x = m_center.x + 2 + origin.x - 2;               // <- right light
                    m_carLimits[7].x = m_center.x + 2 + origin.x - 2;               // <- left light

                    m_carLimits[0].y = m_center.y;                                  // middle back
                    m_carLimits[1].y = m_center.y;                                  // middle front
                    m_carLimits[2].y = m_center.y - origin.y + 4;                   // back left
                    m_carLimits[3].y = m_center.y - origin.y + 4;                   // front left
                    m_carLimits[4].y = m_center.y + origin.y - 6;                   // front right
                    m_carLimits[5].y = m_center.y + origin.y - 6;                   // back right
                    m_carLimits[6].y = m_center.y - origin.y + 10;                  // <- right light
                    m_carLimits[7].y = m_center.y + origin.y - 12;                  // <- left light

                }
    float sinusAngle = sinf(m_angle);
    float cosinusAngle = cosf(m_angle);
    for (auto& point : m_carLimits) {
        sf::Vector2f m;
        m.x = point.x - m_center.x;
        m.y = point.y - m_center.y;
        point.x = (m.x * cosinusAngle) - (m.y * sinusAngle) + m_center.x;
        point.y = (m.x * sinusAngle) + (m.y * cosinusAngle) + m_center.y;
    }
}

void Entity::move()
{
    m_oldPosition = Transformable::getPosition();
    sf::Vector2f SideCoords{ sf::Vector2f(0, 0) };
    if (m_sideSpeed > 1) {
        SideCoords.x = ((cosf(m_sideAngle) * (m_sideSpeed / 6.f)) / 7.2f);    // radians
        SideCoords.y = ((sinf(m_sideAngle) * (-m_sideSpeed / 6.f)) / 7.2f);    // radians
    }
    float angle{ m_angle };
    if (m_shifting) { angle = m_shiftingAngle; }
    if (getIsPowerSteeringKitEquiped()) { angle += 0.15f; }
    sf::Vector2f coords{ getPosition() };
    coords.x += ((cosf(angle) * (m_speed / 6.f)) / 7.2f) + SideCoords.x;    // radians
    coords.y -= ((sinf(angle) * (-m_speed / 6.f)) / 7.2f) + SideCoords.y;    // radians
    setPosition(coords);
}

void Entity::turn(Direction direction)
{
    unsigned int frame{ getCurrentFrame() };
    if (m_interaction.type == Interaction::waterShifting || m_interaction.type == Interaction::Spining) { return; }
    if (direction == Direction::Right) {
        setAngle(m_angle + 0.261799f);
        m_turnIntensity++;
        if (frame == 23) { setCurrentFrame(0); }
        else { setCurrentFrame(++frame); }
    }
    else {
        setAngle(m_angle - 0.261799f);
        m_turnIntensity++;
        if (frame == 0) { setCurrentFrame(23); }
        else { setCurrentFrame(--frame); }
    }
    if (getColor() != 0) {
        if (m_speed > 80.f && m_accelerationOn && m_turnIntensity % 4 == 0) {                                        // decrease speed in turns
            m_speed -= 15;
            m_accelerationOn = false;
        }
        else { handbrakeTurn(); }
    }
    updateCarLimits();
}

void Entity::handbrakeTurn()
{
    if (m_speed > 50.f && !m_accelerationOn) {                                                                      // handbrake turn
        m_speed -= 15;
        m_accelerationOn = false;
        consumeTyres(true);
        if (!m_shifting) {
            //std::cout << "m_shifting = true " << std::endl;
            m_shifting = true;
            m_shiftingAngle = m_angle;
        }
    }
}

bool Entity::isAcceleration()
{
    return m_accelerationOn;
}

void Entity::accelerate()
{
    float maxSpeed{ getMaxSpeed() };
    if (m_interaction.type != Interaction::None) {
        interaction();
        return;
    }
    if (m_sideSpeed > 3.f) {
        float retro{ 0 };
        if (getIsRetrorKitEquiped()) { retro = 0.25f; }
        if (m_sideSpeed > maxSpeed / 2) { m_sideSpeed -= 5.f + (5.f * retro); }
        else { m_sideSpeed -= 2.f + (2.f * retro); }
    }
    else { m_sideSpeed = 0; }
    m_shifting = false;
    //std::cout << "m_shifting = false " << std::endl;
    float factor{ 0.f };
    if (!m_accelerationOn) {
        m_accelerationOn = true;
        if (m_speed > 5.F) {
            factor = m_speed / maxSpeed;
            m_accelerationTime = logf(1 - factor) / (-m_acceleration);
        }
        else { m_accelerationTime = 0.F; }
    }
    factor = 1.f - expf(-m_acceleration * m_accelerationTime);
    m_speed = maxSpeed * m_speedLimiter * factor;
    if (m_speed > m_topRaceSpeed) { m_topRaceSpeed = m_speed; }
    if (m_inSand && m_speed > maxSpeed / 3.f) {
        m_speed = maxSpeed / 3.f;
        factor = m_speed / maxSpeed;
        m_accelerationTime = logf(1 - factor) / (-m_acceleration);
    }
    m_accelerationTime += 0.03f;
    consumeTyres(false);
    consumeFuel();
    consumeEngine();
    if (m_sideSpeed > 3.f) {
        if (m_sideSpeed > maxSpeed / 2) { m_sideSpeed -= 6.f + (6.f * static_cast<float>(getIsRetrorKitEquiped())); }
        else { m_sideSpeed -= 3.f + (3.f * static_cast<float>(getIsRetrorKitEquiped())); }
    }
    else { m_sideSpeed = 0; }
}

void Entity::decelerate()
{
    float maxSpeed{ getMaxSpeed() };
    if (m_interaction.type != Interaction::None) {
        interaction();
        return;
    }
    m_accelerationOn = false;
    if (m_speed > 3.f) {
        if (m_speed > maxSpeed / 2) { m_speed -= 7.f + (7.f * static_cast<float>(getIsRetrorKitEquiped())); }
        else { m_speed -= 3.f + (3.f * static_cast<float>(getIsRetrorKitEquiped())); }
    }
    else { m_speed = 0.f; }
    if (m_sideSpeed > 3.f) {
        if (m_sideSpeed > maxSpeed / 2) { m_sideSpeed -= 6.f + (6.f * static_cast<float>(getIsRetrorKitEquiped())); }
        else { m_sideSpeed -= 3.f + (3.f * static_cast<float>(getIsRetrorKitEquiped())); }
    }
    else { m_sideSpeed = 0; }
    //if (m_sideSpeed > 1.f)
    //std::cout << "deceleration side speed: " << m_sideSpeed << std::endl;
}

////////////////////////////////////////////////////////////////////  getters ///////////////////////////////////////////////
const sf::Vector2f& Entity::getCarLimit(unsigned int index) const
{
    return m_carLimits[index];
}

float Entity::getAngle() const
{
    return m_angle;
}

float Entity::getSideAngle() const
{
    return m_sideAngle;
}

float Entity::getShiftingAngle() const
{
    return m_shiftingAngle;
}

float Entity::getSpeed() const
{
    return m_speed;
}

float Entity::getTopRaceSpeed() const
{
    return m_topRaceSpeed;
}

bool Entity::getNearBridgeArea()
{
    return m_nearBridgeArea;
}

sf::FloatRect Entity::getLocalBounds() const
{
    sf::FloatRect shape(getShape());
    return sf::FloatRect(0.f, 0.f, std::abs(shape.width), std::abs(shape.height));
}

sf::FloatRect Entity::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

Entity::Interaction Entity::getInteractionType() const
{
    return m_interaction.type;
}

const sf::Vector2f& Entity::getCornerCoords(const unsigned int whatCorner) const
{
    return m_carLimits[whatCorner];
}

const sf::Vector2f& Entity::getOldPosition() const
{
    return m_oldPosition;
}

bool Entity::isShifting() const
{
    return m_shifting;
}

float Entity::getSideSpeed() const
{
    return m_sideSpeed;
}

float Entity::getSpeedLimiter() const
{
    return m_speedLimiter;
}

int Entity::getAcceleration() const
{
    return m_acceleration;
}

sf::Vector2f Entity::getCenter() const
{
    return m_center;
}

int Entity::getElevation() const
{
    return m_elevation;
}

////////////////////////////////////////////////////////////////////  setters ///////////////////////////////////////////////

void Entity::setPosition(const sf::Vector2f& coords)
{
    Transformable::setPosition(coords);
    updateCarLimits();
}

void  Entity::setAngle(float angle)
{
    m_angle = angle;
    if (m_angle > 6.27f) { m_angle = 0; }
    setRotation(m_angle / 0.017453f);
}

void Entity::setSpeed(float speed)
{
    m_speed = speed;
    m_accelerationOn = false;
}

void Entity::setSideSpeed(float sideSpeed)
{
    m_sideSpeed = sideSpeed;
}

void Entity::setTopRaceSpeed(float sideSpeed)
{
    m_topRaceSpeed = sideSpeed;
}

void Entity::setSpeedLimiter(float speedLimiter)
{
    m_speedLimiter = speedLimiter;
}

void Entity::setAcceleration(int acceleration)
{
    m_acceleration = acceleration;
}

void Entity::setElevation(unsigned int elevation)
{
    m_elevation = elevation;
}

void Entity::setNearBridgeArea(bool nearBridgeArea)
{
    m_nearBridgeArea = nearBridgeArea;
}

void Entity::setInteraction(Interaction type, float angle, unsigned int intensity, float speed)
{
    if (m_interaction.type != Interaction::Pushed) {
        std::cout << "setting interaction" << std::endl;
        m_interaction.type = type;
        m_interaction.angle = angle;
        m_interaction.intensity = intensity;
        m_interaction.speed = speed;
        m_shiftingAngle = angle;
        m_shifting = true;
        interaction();
    }
}

void Entity::setInSand(bool inSand)
{
    m_inSand = inSand;
}

void Entity::interaction()
{
    unsigned int frame{ getCurrentFrame() };
    switch (m_interaction.type) {
    case Interaction::Bumping:
        consumeBody();
        m_sideSpeed = m_interaction.speed;
        m_speed = 0;
        m_sideAngle = m_interaction.angle;
        m_interaction.intensity = 1;
        break;
    case Interaction::Spining:
        setAngle(m_angle + (0.261799f * 2));
        if (frame >= 22) { setCurrentFrame(0); }
        else { setCurrentFrame(frame + 2); }
        m_speed = 50;
        break;
    case Interaction::waterShifting:
        if (m_interaction.intensity == 0) { m_speed = 60; }
        break;
    case Interaction::Pushed:
        if (m_interaction.intensity == 3) {
            consumeBody();
            if (m_interaction.speed > m_sideSpeed) { m_sideSpeed = m_interaction.speed; }
            if (m_sideSpeed < 30) { m_sideSpeed = 30; }
            m_sideAngle = m_interaction.angle;
            std::cout << "speed transmited : " << m_sideSpeed << std::endl;
        }
        break;
    case Interaction::None:
    default:
        break;
    }
    m_accelerationOn = false;
    --m_interaction.intensity;
    if (m_interaction.intensity == 0) {
        m_interaction.type = Interaction::None;
        m_shifting = false;
    }
}