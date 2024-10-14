#include "header/infoPannel.hpp"

#include <SFML/Graphics/Vertex.hpp>

#include "jsonfile/jsonfile.hpp"

InfoPanel::InfoPanel(const std::string& infoToDispaly, sf::Texture* gfxTexture) : m_texture{ gfxTexture }, m_counter{ 0 }
{
    initInfoPanel(infoToDispaly);
    m_rollingLettersTimer.setDuration(50);
    m_rollingLettersTimer.start();
}

void InfoPanel::initInfoPanel(const std::string& infoToDispaly)
{
    m_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
    mylib::JsonFile lettersCoords("data/race/info panel.json");
    sf::FloatRect frame(623, 0, 16, 16);
    sf::Vertex vertex;
    int y{ 0 }, offset{ 48 };
    for (auto i = 0; i < 19; ++i) {
        switch (infoToDispaly[i]) {
        case '0':
            frame.top = 5;
            break;
        case '1':
            frame.top = 21;
            break;
        case '2':
            frame.top = 37;
            break;
        case '3':
            frame.top = 53;
            break;
        case '4':
            frame.top = 69;
            break;
        case '5':
            frame.top = 85;
            break;
        case '6':
            frame.top = 101;
            break;
        case '7':
            frame.top = 117; 
            break;
        case '8':
            frame.top = 133;
            break;
        case '9':
            frame.top = 149;
            break;
        case '-':
            frame.top = 181;
            break;
        default:
            break;
        }
        offset += 16;
        sf::Vector2f letterCoords(lettersCoords.m_Root["charCoords"][i]["x"].asFloat(), lettersCoords.m_Root["charCoords"][i]["y"].asFloat());
        vertex.position = letterCoords;
        vertex.texCoords = sf::Vector2f(frame.left, frame.top + offset);
        m_vertices.append(vertex);
        vertex.position = sf::Vector2f(letterCoords.x + frame.width, letterCoords.y);
        vertex.texCoords = sf::Vector2f(frame.left + frame.width, frame.top + offset);
        m_vertices.append(vertex);
        vertex.position = sf::Vector2f(letterCoords.x + frame.width, letterCoords.y + frame.height);
        vertex.texCoords = sf::Vector2f(frame.left + frame.width, frame.top + frame.height + offset);
        m_vertices.append(vertex);
        vertex.position = sf::Vector2f(letterCoords.x, letterCoords.y + frame.height);
        vertex.texCoords = sf::Vector2f(frame.left, frame.top + frame.height + offset);
        m_vertices.append(vertex);
    }
}

void InfoPanel::update()
{
    if (m_rollingLettersTimer.isTimeElapsed()) {
        m_rollingLettersTimer.restart();
        unsigned int CurrentLetter{ 0 };
        if (m_counter >= 12) { CurrentLetter = (m_counter - 12) / 4; }
        for (auto i = 0; i < 19 * 4; ++i) {
            if (i >= CurrentLetter * 4) {
               sf::Vector2f vertexTextureVector = m_vertices[i].texCoords;
               vertexTextureVector.y -= 4;
               m_vertices[i].texCoords = vertexTextureVector;
            }
        }
        ++m_counter;
    }
}

bool InfoPanel::isFinished() const
{
    return m_counter > 95;

}

void InfoPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = m_texture;
    for (size_t i = 0; i < 19; ++i) {
        target.draw(&m_vertices[i * 4], 4, sf::Quads, states);
    }
}