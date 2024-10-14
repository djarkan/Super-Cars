#ifndef CAR_HPP
#define CAR_HPP

#include <cmath>
#include <array>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Car : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
	public:
	    enum                                        Type {Taraco_Neoroder = 0, Taraco_Neoroder1, Vaug_Interceptor2, Vaug_Interceptor3, Retron_Parsec_Turbo5, Retron_Parsec_Turbo6, Retron_Parsec_Turbo8};
	    enum                                        Interaction {None = 0, Bumping, waterShifting, Spining, Pushed};
	    enum                                        Direction{Left = 0, Right};

                                                    Car();
        const sf::Vector2f&                         getCarLimit(unsigned int index) const;
        Type                                        getType() const;
        sf::FloatRect                               getShape() const;
        float                                       getAngle() const;
        float                                       getSideAngle() const;
        float                                       getShiftingAngle() const;
        float                                       getSpeed() const;
        float                                       getTopRaceSpeed()  const;
        float                                       getMaxSpeed() const;
        float                                       getSideSpeed() const;
        int                                         getAcceleration() const;
        float                                       getSpeedLimiter() const;
        sf::Vector2f                                getCenter() const;
        int                                         getElevation() const;
        float                                       getBodyState() const;
        float                                       getEngineState() const;
        float                                       getTyresState() const;
        float                                       getFuelState() const;
        bool                                        getIsFrontMissileEquiped() const;
        bool                                        getIsRearMissileEquiped() const;
        bool                                        getIsHighSpeedKitEquiped() const;
        bool                                        getIsTurboChargerKitEquiped() const;
        bool                                        getIsRetrorKitEquiped() const;
        bool                                        getIsSpinAssistKitEquiped() const;
        bool                                        getIsSideArmourKitEquiped() const;
        bool                                        getIsPowerSteeringKitEquiped() const;
        unsigned int                                getColor() const;
        bool                                        getNearBridgeArea();
        sf::FloatRect                               getLocalBounds() const;
        sf::FloatRect                               getGlobalBounds() const;
        Interaction                                 getInteractionType() const;
        unsigned int                                getFrame() const;
        const sf::Vector2f&                         getCornerCoords(const unsigned int whatCorner) const;
        const sf::Vector2f&                         getOldPosition() const;

        void                                        setType(Type type);
        void                                        setShape(sf::FloatRect& rect);
        void                                        setPosition(const sf::Vector2f& coords);
        void                                        setAngle(float angle);
        void                                        setSpeed(float speed);
        void                                        setTopRaceSpeed(float sideSpeed);
        void                                        setSideSpeed(float sideSpeed);
        void                                        setMaxSpeed(float maxSpeed);
        void                                        setAcceleration(int acceleration);
        void                                        setSpeedLimiter(float speedLimiter);
        void                                        setElevation(unsigned int elevation);
        void                                        setBodyState(float body);
        void                                        setEngineState(float engine);
        void                                        setTyresState(float tyres);
        void                                        setFuelState(float fuel);
        void                                        setIsFrontMissileEquiped(bool frontMissile);
        void                                        setIsRearMissileEquiped(bool rearMissile);
        void                                        setIsHighSpeedKitEquiped(bool highSpeed);
        void                                        setIsRetroKitEquiped(bool retro);
        void                                        setIsTurboChargerKitEquiped(bool turboCharger);
        void                                        setIsSpinAssistKitEquiped(bool spinAssist);
        void                                        setIsSideArmourKitEquiped(bool sideArmour);
        void                                        setIsPowerSteeringKitEquiped(bool powerSteering);
        void                                        setColor(unsigned int color);
        void                                        setNearBridgeArea(bool nearBridgeArea);
        void                                        setTexture(sf::Texture* carTexture);
        void                                        setVertices();
        void                                        setFrame();
        void                                        setInSand(bool inSand);
        void                                        setInteraction(Interaction type,float angle, unsigned int intensity, float speed);


        void                                        move();
        void                                        turn(Direction direction);
        void                                        accelerate();
        void                                        decelerate();
        void                                        updateCarLimits();
        void                                        consumeTyres();
        void                                        consumeFuel();
        void                                        consumeEngine();
        void                                        consumeBody();
        bool                                        isBroken() const;
        bool                                        isAcceleration();
        bool                                        isShifting() const;

	private:
        float                                       m_body;                             // % body health
        float                                       m_engine;                           // % engine usury
        float                                       m_tyres;                            // % tyres usury
        float                                       m_fuel;                             // % fuel tank level
        sf::Vector2f                                m_center;
        bool                                        m_frontMissile;                     // you can only buy one per race.
        bool                                        m_rearMissile;                      // you can only buy one per race.
        bool                                        m_highSpeedKit;                     // Increases your maximum speed - Invaluable on the straights!
        bool                                        m_turboCharger;                     // Use this to increase your acceleration rate. This option is particularly useful when running into patches of mud which slow your car down.
        bool                                        m_spinAssist;                       // Spin Assist will always point your car in the right direction.
        bool                                        m_sideArmour;                       // Use this to send any other vehicle into an uncontrollable spin simply by ramming it.
        bool                                        m_powerSteering;                    // Essential for decreasing your turning circle and allowing for faster corner-taking.
        bool                                        m_retro;                            // Use this for faster braking.

        Car::Type                                   m_type;                             // car model type
        sf::FloatRect                               m_shape;                            // car length and width
        float                                       m_angle;                            // current car speed
        float                                       m_sideAngle;                        // deviation angle
        float                                       m_speed;                            // current car speed
        float                                       m_topRaceSpeed;                     // highest speed reached in race
        float                                       m_maxSpeed;                         // max car speed
        float                                       m_sideSpeed;                        // deviation speed
        float                                       m_speedLimiter;                     // limiter for computer car
        int                                         m_acceleration;                     // 2 : normal acceleration, 3 : turbo charger kit bought
        std::array<sf::Vector2f, 8>                 m_carLimits;                        // corners for collisions and tracks limit detection
        unsigned int                                m_elevation;                        // altitude to know if car is on or under the bridges
        unsigned int                                m_color;                            // current car color
        sf::Texture*                                m_carTexture;                       // car grahics location
        sf::VertexArray                             m_vertices;                         // texture corners
        unsigned int                                m_frame;                            // graphics car for that angle
        bool                                        m_accelerationOn;                   // true : car in acceleration false: car in deceleration or stopped
        float                                       m_accelerationTime;                 // length of the acceleration
        bool                                        m_isBroken;                         // true : race over, false: can play
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

        virtual void			                    draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void                                        handbrakeTurn();
        void                                        interaction();
};

#endif
