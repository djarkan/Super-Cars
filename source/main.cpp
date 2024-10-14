#include <header/intro.hpp>
#include "jsonfile/jsonfile.hpp"

sf::Vector2f windowRatio(1, 1);

int main()
{
    mylib::JsonFile configJson("config.json");
    int windowSize{ configJson.m_Root["windowSize"].asInt() };
    Intro intro(640 * windowSize, 400 * windowSize, configJson.m_Root["language"].asInt());
    intro.launchIntro();
    return 0;
}

