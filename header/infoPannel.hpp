#ifndef INFOPANNEL_HPP
#define INFOPANNEL_HPP

#include <string>
#include <array>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>


#include "header/assetkey.hpp"
#include "timer/timer.hpp"

class InfoPanel : public sf::Drawable
{
public :
															InfoPanel(const std::string& infoToDispaly, sf::Texture* gfxTexture);
	void													update();
	bool													isFinished() const;
	

private:
	mylib::Timer											m_rollingLettersTimer;
	sf::Texture*											m_texture;                       
	sf::VertexArray											m_vertices;                          
	unsigned int											m_counter;
	void													initInfoPanel(const std::string& infoToDispaly);
	virtual void											draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif