#include "header/carUpgrade.hpp"

CarUpgrade::CarUpgrade() : m_frontMissile{ false }, m_rearMissile{ false }, m_highSpeedKit{ false }, m_turboCharger{ false }, m_spinAssist{ false }, m_sideArmour{ false }, m_powerSteering{ false }, m_retro{ false }
{

}

bool CarUpgrade::getIsFrontMissileEquiped() const
{
    return m_frontMissile;
}

bool CarUpgrade::getIsRearMissileEquiped() const
{
    return m_rearMissile;
}

bool CarUpgrade::getIsHighSpeedKitEquiped() const
{
    return m_highSpeedKit;
}

bool CarUpgrade::getIsTurboChargerKitEquiped() const
{
    return m_turboCharger;
}

bool CarUpgrade::getIsRetrorKitEquiped() const
{
    return m_retro;
}

bool CarUpgrade::getIsSpinAssistKitEquiped() const
{
    return m_spinAssist;
}

bool  CarUpgrade::getIsSideArmourKitEquiped() const
{
    return m_sideArmour;
}

bool CarUpgrade::getIsPowerSteeringKitEquiped() const
{
    return m_powerSteering;
}

void CarUpgrade::setIsFrontMissileEquiped(bool frontMissile)
{
    m_frontMissile = frontMissile;
}

void CarUpgrade::setIsRearMissileEquiped(bool rearMissile)
{
    m_rearMissile = rearMissile;
}

void CarUpgrade::setIsHighSpeedKitEquiped(bool highSpeed)
{
    m_highSpeedKit = highSpeed;
}

void CarUpgrade::setIsTurboChargerKitEquiped(bool turboCharger)
{
    m_turboCharger = turboCharger;
}

void CarUpgrade::setIsRetroKitEquiped(bool retro)
{
    m_retro = retro;
}

void CarUpgrade::setIsSpinAssistKitEquiped(bool spinAssist)
{
    m_spinAssist = spinAssist;
}

void  CarUpgrade::setIsSideArmourKitEquiped(bool sideArmour)
{
    m_sideArmour = sideArmour;
}

void CarUpgrade::setIsPowerSteeringKitEquiped(bool powerSteering)
{
    m_powerSteering = powerSteering;
}