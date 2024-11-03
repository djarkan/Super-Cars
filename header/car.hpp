#ifndef CAR_HPP
#define CAR_HPP

#include <cmath>
#include <array>
#include <iostream>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "header/carUpgrade.hpp"

class Car : public CarUpgrade, public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
	public:
        enum                                        Type { Taraco_Neoroder = 0, Taraco_Neoroder1, Vaug_Interceptor2, Vaug_Interceptor3, Retron_Parsec_Turbo5, Retron_Parsec_Turbo6, Retron_Parsec_Turbo8 };

                                                    Car();
        Type                                        getType() const;
        sf::FloatRect                               getShape() const;
        float                                       getMaxSpeed() const;    
        float                                       getBodyState() const;
        float                                       getEngineState() const;
        float                                       getTyresState() const;
        float                                       getFuelState() const;
        unsigned int                                getColor() const;     
        unsigned int                                getCurrentFrame() const;

        void                                        setType(Type type);
        void                                        setShape(sf::FloatRect& rect);    
        void                                        setMaxSpeed(float maxSpeed);    
        void                                        setBodyState(float body);
        void                                        setEngineState(float engine);
        void                                        setTyresState(float tyres);
        void                                        setFuelState(float fuel);
        void                                        setColor(unsigned int color);
        void                                        setCurrentFrame(const unsigned int frame);
        void                                        setStartFrame(const float angle);
        void                                        setVertices();
        void                                        setTexture(sf::Texture* carTexture);

        void                                        consumeTyres(bool isHandBreacking);
        void                                        consumeFuel();
        void                                        consumeEngine();
        void                                        consumeBody();
        bool                                        isBroken() const;

        virtual void			                    draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::VertexArray                             m_vertices;                         // texture corners

	private:
        float                                       m_body;                             // % body health
        float                                       m_engine;                           // % engine usury
        float                                       m_tyres;                            // % tyres usury
        float                                       m_fuel;                             // % fuel tank level
        Car::Type                                   m_type;                             // car model type
        sf::FloatRect                               m_shape;                            // car length and width    
        float                                       m_maxSpeed;                         // max car speed
        unsigned int                                m_color;                            // current car color
        sf::Texture*                                m_carTexture;                       // car grahics location    
        unsigned int                                m_frame;                            // graphics car for that angle
        bool                                        m_isBroken;                         // true : race over, false: can play
        
};

#endif
