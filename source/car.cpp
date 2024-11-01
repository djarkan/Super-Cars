#include "header/car.hpp"

#include <cmath>


Car::Car() : m_body{1}, m_engine{1}, m_tyres{1}, m_fuel{1}, m_frontMissile{false}, m_rearMissile{false},m_highSpeedKit{false}, m_turboCharger{false}, m_spinAssist{false},
             m_sideArmour{ false }, m_powerSteering{ false }, m_retro{ false }, m_type{ Car::Type::Taraco_Neoroder }, m_angle{ 0 }, m_sideAngle{ 0 }, m_shiftingAngle{ 0 },  m_speed { 0 }, m_topRaceSpeed{ 0 }, 
             m_maxSpeed{ 0 }, m_sideSpeed{ 0 }, m_speedLimiter{ 1.f }, m_acceleration{ 2 }, m_elevation{ 1 }, m_carTexture{nullptr}, m_frame{0}, m_accelerationOn{false}, m_accelerationTime{0}, m_isBroken{false}, 
             m_turnIntensity{0}, m_shifting{false}, m_nearBridgeArea{false}, m_inSand{false}, m_waypointTarget{0}
{
    m_color = 1;
    m_interaction.type = Interaction::None;
    m_interaction.angle = 0;
    m_interaction.intensity = 0;
}

void Car::updateCarLimits()
{
    m_center = getPosition();
    sf::Vector2f origin{getOrigin()};
    if (m_frame == 22 || m_frame == 23 || m_frame <= 2) {
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
        if ((m_frame >= 3 && m_frame <= 8)) {
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
            if (m_frame >= 9 && m_frame <= 15) {
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
                if (m_frame >= 16 && m_frame <= 21) {
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

const sf::Vector2f& Car::getCarLimit( unsigned int index) const
{
    return m_carLimits[index];
}

void Car::move()
{
    m_oldPosition = Transformable::getPosition();
    sf::Vector2f SideCoords{sf::Vector2f(0, 0)};
    if(m_sideSpeed > 1) {
        SideCoords.x = ((cosf(m_sideAngle) * (m_sideSpeed / 6.f)) / 7.2f);    // radians
        SideCoords.y = ((sinf(m_sideAngle) * (-m_sideSpeed / 6.f)) / 7.2f);    // radians
    }
    float angle{m_angle};
    if(m_shifting) { angle = m_shiftingAngle; }
    if (m_powerSteering) { angle += 0.15f; }
    sf::Vector2f coords{getPosition()};
    coords.x += ((cosf(angle) * (m_speed / 6.f)) / 7.2f) + SideCoords.x;    // radians
    coords.y -= ((sinf(angle) * (-m_speed / 6.f)) / 7.2f) + SideCoords.y;    // radians
    setPosition(coords);
}

bool Car::isBroken() const
{
    return m_isBroken;
}

void Car::turn(Direction direction)
{
    if (m_interaction.type == Interaction::waterShifting || m_interaction.type == Interaction::Spining) { return; }
    if (direction == Direction::Right) {
        setAngle(m_angle + 0.261799f);
        m_turnIntensity++;
        if (m_frame == 23) { m_frame = 0; }
        else { ++m_frame; }
    }
    else {
        setAngle(m_angle - 0.261799f);
        m_turnIntensity++;
        if (m_frame == 0) { m_frame = 23; }
        else { --m_frame; }
    }
    if(m_color != 0) {
        if (m_speed > 80.f && m_accelerationOn && m_turnIntensity % 4 == 0) {                                        // decrease speed in turns
            m_speed -= 15;
            m_accelerationOn = false;
        }
        else { handbrakeTurn(); }
    }
    updateCarLimits();
}

void Car::handbrakeTurn()
{
    if (m_speed > 50.f && !m_accelerationOn) {                                                               // handbrake turn
        m_speed -= 15;
        m_accelerationOn = false;
        if (m_tyres > 0.002f) { m_tyres -= 0.002f; }
        else { m_isBroken = true; }
        if (!m_shifting) {
 //std::cout << "m_shifting = true " << std::endl;
            m_shifting = true;
            m_shiftingAngle = m_angle;
        }
    }
}

bool Car::isAcceleration()
{
    return m_accelerationOn;
}

void Car::accelerate()
{
    if(m_interaction.type != Interaction::None) {
        interaction();
        return;
    }
    if(m_sideSpeed > 3.f) {
        float retro{0};
        if(m_retro) { retro = 0.25f; }
        if(m_sideSpeed > m_maxSpeed / 2) { m_sideSpeed -= 5.f + (5.f * retro); }
        else { m_sideSpeed -= 2.f + (2.f * retro); }
    }
    else { m_sideSpeed = 0; }
    m_shifting = false;
 //std::cout << "m_shifting = false " << std::endl;
    float factor{0.f};
    if(!m_accelerationOn) {
        m_accelerationOn = true;
        if(m_speed > 5.F) {
            factor = m_speed / m_maxSpeed;
            m_accelerationTime = logf(1 - factor) / (-m_acceleration);
        }
        else { m_accelerationTime = 0.F; }
    }
    factor = 1.f - expf(-m_acceleration * m_accelerationTime);
    m_speed = m_maxSpeed * m_speedLimiter * factor;
    if (m_speed > m_topRaceSpeed) { m_topRaceSpeed = m_speed; }
    if(m_inSand && m_speed > m_maxSpeed / 3.f) {
        m_speed = m_maxSpeed / 3.f;
        factor = m_speed / m_maxSpeed;
        m_accelerationTime = logf(1 - factor) / (-m_acceleration);
    }
    m_accelerationTime += 0.03f;
    consumeTyres();
    consumeFuel();
    consumeEngine();
    if (m_sideSpeed > 3.f) {
        if (m_sideSpeed > m_maxSpeed / 2) { m_sideSpeed -= 6.f + (6.f * static_cast<float>(m_retro)); }
        else { m_sideSpeed -= 3.f + (3.f * static_cast<float>(m_retro)); }
    }
    else { m_sideSpeed = 0; }
}

void Car::decelerate()
{
    if(m_interaction.type != Interaction::None) {
        interaction();
        return;
    }
    m_accelerationOn = false;
    if(m_speed > 3.f) {
        if (m_speed > m_maxSpeed / 2) { m_speed -= 7.f + (7.f * static_cast<float>(m_retro)); }
        else { m_speed -= 3.f + (3.f * static_cast<float>(m_retro)); }
    }
    else { m_speed = 0.f; }
    if (m_sideSpeed > 3.f) {
        if (m_sideSpeed > m_maxSpeed / 2) { m_sideSpeed -= 6.f + (6.f * static_cast<float>(m_retro)); }
        else { m_sideSpeed -= 3.f + (3.f * static_cast<float>(m_retro)); }
    }
    else { m_sideSpeed = 0; }
//if (m_sideSpeed > 1.f)
//std::cout << "deceleration side speed: " << m_sideSpeed << std::endl;
}

void Car::consumeTyres()
{
    m_tyres -= 0.0001f; 
    if(m_tyres < 0) { m_isBroken = true; }
}

void Car::consumeFuel()
{
    switch (m_type) {
        case Type::Taraco_Neoroder:
        case Type::Taraco_Neoroder1:
            m_fuel -= 0.0001f;
            break;
        case Type::Vaug_Interceptor2:
        case Type::Vaug_Interceptor3:
            m_fuel -= 0.00013f;
            break;
        case Type::Retron_Parsec_Turbo5:
        case Type::Retron_Parsec_Turbo6:
        case Type::Retron_Parsec_Turbo8:
            m_fuel -= 0.00016f;
            break;
        default:
            break;
    }
    if (m_fuel < 0) {  m_isBroken = true; }
}

void Car::consumeEngine()
{
    m_engine -= 0.0001f; 
    if (m_engine <  0.01f) { m_isBroken = true; }
}

void Car::consumeBody()
{
    if (m_sideArmour) { m_body -= 0.001f; }
    else { (m_body) -= 0.0025f; }
    if(m_body < 0) { m_isBroken = true; }
}

Car::Type Car::getType() const
{
    return m_type;
}

float Car::getAngle() const
{
    return m_angle;
}

float Car::getSideAngle() const
{
    return m_sideAngle;
}

float Car::getShiftingAngle() const
{
    return m_shiftingAngle;
}

float Car::getSpeed() const
{
    return m_speed;
}

float Car::getTopRaceSpeed() const
{
    return m_topRaceSpeed;
}

float Car::getMaxSpeed() const
{
    return m_maxSpeed;
}

float Car::getSideSpeed() const
{
    return m_sideSpeed;
}

float Car::getSpeedLimiter() const
{
    return m_speedLimiter;
}

int Car::getAcceleration() const
{
    return m_acceleration;
}

sf::Vector2f Car::getCenter() const
{
    return m_center;
}

sf::FloatRect Car::getShape() const
{
    return m_shape;
}

int Car::getElevation() const
{
    return m_elevation;
}

float Car::getBodyState() const
{
    return m_body;
}

float Car::getEngineState() const
{
    return m_engine;
}

float Car::getTyresState() const
{
    return m_tyres;
}

float Car::getFuelState() const
{
    return m_fuel;
}

bool Car::getIsFrontMissileEquiped() const
{
    return m_frontMissile;
}

bool Car::getIsRearMissileEquiped() const
{
    return m_rearMissile;
}

bool Car::getIsHighSpeedKitEquiped() const
{
    return m_highSpeedKit;
}

bool Car::getIsTurboChargerKitEquiped() const
{
    return m_turboCharger;
}

bool Car::getIsRetrorKitEquiped() const
{
    return m_retro;
}

bool Car::getIsSpinAssistKitEquiped() const
{
    return m_spinAssist;
}

bool  Car::getIsSideArmourKitEquiped() const
{
    return m_sideArmour;
}

bool Car::getIsPowerSteeringKitEquiped() const
{
    return m_powerSteering;
}

unsigned int Car::getColor() const
{
    return m_color;
}

bool Car::getNearBridgeArea()
{
    return m_nearBridgeArea;
}

sf::FloatRect Car::getLocalBounds() const
{
    return sf::FloatRect(0.f, 0.f, std::abs(m_shape.width), std::abs(m_shape.height));
}

sf::FloatRect Car::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

Car::Interaction Car::getInteractionType() const
{
    return m_interaction.type;
}

unsigned int Car::getFrame() const
{
    return m_frame;
}

const sf::Vector2f& Car::getCornerCoords(const unsigned int whatCorner) const
{
    return m_carLimits[whatCorner];
}

const sf::Vector2f& Car::getOldPosition() const
{
    return m_oldPosition;
}

bool Car::isShifting() const
{
    return m_shifting;
}

void Car::setType(Type type)
{
    m_type = type;
}

void Car::setShape(sf::FloatRect& rect)
{
    m_shape = rect;
}

void Car::setPosition(const sf::Vector2f& coords)      
{
    Transformable::setPosition(coords);
    updateCarLimits();
}

void  Car::setAngle(float angle)
{
    m_angle = angle;
   if(m_angle > 6.27f) { m_angle = 0; }
    setRotation(m_angle  / 0.017453f);
}

void Car::setSpeed(float speed)
{
    m_speed = speed;
    m_accelerationOn = false;
}

void Car::setSideSpeed(float sideSpeed)
{
    m_sideSpeed = sideSpeed;
}

void Car::setTopRaceSpeed(float sideSpeed)
{
    m_topRaceSpeed = sideSpeed;
}

void Car::setMaxSpeed(float maxSpeed)
{
    m_maxSpeed = maxSpeed;
}

void Car::setSpeedLimiter(float speedLimiter)
{
    m_speedLimiter = speedLimiter;
}

void Car::setAcceleration(int acceleration)
{
    m_acceleration = acceleration;
}

void Car::setElevation(unsigned int elevation)
{
    m_elevation = elevation;
}

void Car::setBodyState(float body)
{
    m_body = body;
}

void Car::setEngineState(float engine)
{
    m_engine = engine;
}

void Car::setTyresState(float tyres)
{
    m_tyres = tyres;
}

void Car::setFuelState(float fuel)
{
    m_fuel = fuel;
}

void Car::setIsFrontMissileEquiped(bool frontMissile)
{
    m_frontMissile = frontMissile;
}

void Car::setIsRearMissileEquiped(bool rearMissile)
{
    m_rearMissile = rearMissile;
}

void Car::setIsHighSpeedKitEquiped(bool highSpeed)
{
    m_highSpeedKit = highSpeed;
}

void Car::setIsTurboChargerKitEquiped(bool turboCharger)
{
    m_turboCharger = turboCharger;
}

void Car::setIsRetroKitEquiped(bool retro)
{
    m_retro = retro;
}

void Car::setIsSpinAssistKitEquiped(bool spinAssist)
{
    m_spinAssist = spinAssist;
}

void  Car::setIsSideArmourKitEquiped(bool sideArmour)
{
    m_sideArmour = sideArmour;
}

void Car::setIsPowerSteeringKitEquiped(bool powerSteering)
{
    m_powerSteering = powerSteering;
}

void Car::setColor(unsigned int color)
{
    m_color = color;
    m_frame = 0;
}

void Car::setNearBridgeArea(bool nearBridgeArea)
{
    m_nearBridgeArea = nearBridgeArea;
}

void Car::setInteraction(Interaction type, float angle, unsigned int intensity, float speed)
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

void Car::setInSand(bool inSand)
{
    m_inSand = inSand;
}

void Car::setTexture(sf::Texture* carTexture)
{
    m_carTexture = carTexture;
}

void Car::setVertices()      /////////////////////////// set les vertices par rapport au model et la couleur
{
    m_vertices.setPrimitiveType(sf::Quads);
    sf::FloatRect carTextureCoords;
        if(m_type == Type::Taraco_Neoroder ||  m_type ==  Type::Taraco_Neoroder1)
            carTextureCoords = sf::FloatRect(0, 0, m_shape.width, m_shape.height);
        if(m_type == Type::Vaug_Interceptor2 ||  m_type ==  Type::Vaug_Interceptor3)
            carTextureCoords = sf::FloatRect(0, 35, m_shape.width, m_shape.height);
        if(m_type == Type::Retron_Parsec_Turbo5 ||  m_type ==  Type::Retron_Parsec_Turbo6  || m_type == Type::Retron_Parsec_Turbo8)
            carTextureCoords = sf::FloatRect(0, 74, 57, 39);
    carTextureCoords.top += m_color * 113;
    float width = carTextureCoords.width;
    float heigth = carTextureCoords.height;
    float LeftX = carTextureCoords.left;
    float topY = carTextureCoords.top;
    float RightX = LeftX + width;
    float bottomY = topY + heigth;
    sf::Vertex vertex;
    m_vertices.resize(0);
    for(auto i = 0; i < 24; ++i) {
        vertex.position = sf::Vector2f(0,0);
        vertex.texCoords = sf::Vector2f(LeftX + (i * width), topY);
        m_vertices.append(vertex);
        vertex.position = sf::Vector2f(width,0);
        vertex.texCoords = sf::Vector2f(RightX + (i * width), topY);
        m_vertices.append(vertex);
        vertex.position = sf::Vector2f(width,heigth);
        vertex.texCoords = sf::Vector2f(RightX + (i * width), bottomY);
        m_vertices.append(vertex);
        vertex.position = sf::Vector2f(0,heigth);
        vertex.texCoords = sf::Vector2f(LeftX + (i * width), bottomY);
        m_vertices.append(vertex);
    }
}

void Car::setFrame()
{
    if(m_angle < 1) { m_frame = 0; }
    else {
        if(m_angle >4.7123) { m_frame = 18; }
        else {
            if(m_angle > 3.1415) { m_frame = 12; }
            else {
                 if(m_angle > 1.5707) { m_frame = 6; }
            }
        }
    }
    setVertices();
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = m_carTexture;
    target.draw(&m_vertices[m_frame * 4], 4, sf::Quads, states);
}

void Car::interaction()
{
    switch (m_interaction.type) {
        case Interaction::Bumping :
            consumeBody();
            m_sideSpeed = m_interaction.speed;
            m_speed = 0;
            m_sideAngle = m_interaction.angle;
            m_interaction.intensity = 1;
            break;
        case Interaction::Spining :
            setAngle(m_angle + (0.261799f * 2));
            if(m_frame >= 22) { m_frame = 0; }
            else { m_frame += 2; }
            m_speed = 50;
            break;
        case Interaction::waterShifting :
            if (m_interaction.intensity == 0) { m_speed = 60; }
            break;
        case Interaction::Pushed:
            if (m_interaction.intensity == 3) {
                consumeBody();
                if (m_interaction.speed > m_sideSpeed) { m_sideSpeed = m_interaction.speed; }
                if (m_sideSpeed < 15) { m_sideSpeed = 15; }
                m_speed = 0;
                m_sideAngle = m_interaction.angle;
std::cout << "speed transmited : " << m_sideSpeed << std::endl;
            }
            break;
        case Interaction::None:
        default :
            break;
    }
    m_accelerationOn = false;
    --m_interaction.intensity;
    if (m_interaction.intensity == 0) {
        m_interaction.type = Interaction::None;
        m_shifting = false;
    }
}
