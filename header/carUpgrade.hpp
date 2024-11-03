#ifndef CARUPGRADE_HPP
#define CARUPGRADE_HPP

class CarUpgrade {
public:
                                                CarUpgrade();
    bool                                        getIsFrontMissileEquiped() const;
    bool                                        getIsRearMissileEquiped() const;
    bool                                        getIsHighSpeedKitEquiped() const;
    bool                                        getIsTurboChargerKitEquiped() const;
    bool                                        getIsRetrorKitEquiped() const;
    bool                                        getIsSpinAssistKitEquiped() const;
    bool                                        getIsSideArmourKitEquiped() const;
    bool                                        getIsPowerSteeringKitEquiped() const;

    void                                        setIsFrontMissileEquiped(bool frontMissile);
    void                                        setIsRearMissileEquiped(bool rearMissile);
    void                                        setIsHighSpeedKitEquiped(bool highSpeed);
    void                                        setIsRetroKitEquiped(bool retro);
    void                                        setIsTurboChargerKitEquiped(bool turboCharger);
    void                                        setIsSpinAssistKitEquiped(bool spinAssist);
    void                                        setIsSideArmourKitEquiped(bool sideArmour);
    void                                        setIsPowerSteeringKitEquiped(bool powerSteering);

private:
    bool                                        m_frontMissile;                     // you can only buy one per race.
    bool                                        m_rearMissile;                      // you can only buy one per race.
    bool                                        m_highSpeedKit;                     // Increases your maximum speed - Invaluable on the straights!
    bool                                        m_turboCharger;                     // Use this to increase your acceleration rate. This option is particularly useful when running into patches of mud which slow your car down.
    bool                                        m_spinAssist;                       // Spin Assist will always point your car in the right direction.
    bool                                        m_sideArmour;                       // Use this to send any other vehicle into an uncontrollable spin simply by ramming it.
    bool                                        m_powerSteering;                    // Essential for decreasing your turning circle and allowing for faster corner-taking.
    bool                                        m_retro;                            // Use this for faster braking.

#endif
};
