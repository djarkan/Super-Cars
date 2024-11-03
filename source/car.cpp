#include "header/car.hpp"

Car::Car() : m_body{ 1 }, m_engine{ 1 }, m_tyres{ 1 }, m_fuel{ 1 }, m_type{ Car::Type::Taraco_Neoroder }, m_maxSpeed{ 0 }, m_carTexture{ nullptr }, m_color{ 1 }, m_frame{ 0 }, m_isBroken { false }
{

}

bool Car::isBroken() const
{
    return m_isBroken;
}

void Car::consumeTyres(bool isHandBreacking)
{
    float usuryMultiplier{ 1 };
    if (isHandBreacking) { usuryMultiplier = 2; }
    m_tyres -= 0.0001f * usuryMultiplier;
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
    if (getIsSideArmourKitEquiped()) { m_body -= 0.001f; }
    else { (m_body) -= 0.0025f; }
    if(m_body < 0) { m_isBroken = true; }
}

Car::Type Car::getType() const
{
    return m_type;
}

float Car::getMaxSpeed() const
{
    return m_maxSpeed;
}

sf::FloatRect Car::getShape() const
{
    return m_shape;
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

unsigned int Car::getColor() const
{
    return m_color;
}

unsigned int Car::getCurrentFrame() const
{
    return m_frame;
}

void Car::setType(Type type)
{
    m_type = type;
}

void Car::setShape(sf::FloatRect& rect)
{
    m_shape = rect;
}

void Car::setMaxSpeed(float maxSpeed)
{
    m_maxSpeed = maxSpeed;
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

void Car::setColor(unsigned int color)
{
    m_color = color;
    m_frame = 0;
}

void Car::setCurrentFrame(const unsigned int frame)
{
    m_frame = frame;
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

void Car::setStartFrame(const float angle)
{
    if(angle < 1) { m_frame = 0; }
    else {
        if(angle >4.7123) { m_frame = 18; }
        else {
            if(angle > 3.1415) { m_frame = 12; }
            else {
                 if(angle > 1.5707) { m_frame = 6; }
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

void Car::setTexture(sf::Texture* carTexture)
{
    m_carTexture = carTexture;
}