#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <string>

#include "text/bitmapfont/bitmapFont.hpp"
#include "text/bitmaptext/bitmapText.hpp"
#include "jsonfile/jsonfile.hpp"

class Message : public sf::Drawable {
    public :
        enum class                          Messages { Loading = 0, WonStage1, WonStage2, WonStage3, RaceWon, RaceLost, TyresBroken, FuelEmpty, EngineBroken, BodyBroken, NoJoystick, sevaralJoystick, loadSavedGame };
                                            Message(const unsigned int language, const Messages message);
        bool                                loadFont();
        void                                initBackground();
        void                                setText();
        void                                setFontSize(unsigned int glyphWidth, unsigned int glyphHigth);


    private :
        Messages                            m_messageToDisplay;
        unsigned int                        m_language;
        mylib::JsonFile                     m_languageJson;
        sf::RectangleShape                  m_background;
        mylib::BitmapFont                   m_font;
        mylib::BitmapText                   m_text;

        virtual void                        draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // MESSAGE_HPP
