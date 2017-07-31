#include "utilities.h"
void draw_bar(float fillPercentage, const sf::Vector2f& position)
{
	sf::RectangleShape barOfPowerUnder(sf::Vector2f(200, 15));
	barOfPowerUnder.setOrigin(sf::Vector2f(barOfPowerUnder.getSize().x*0.5, barOfPowerUnder.getSize().y*0.5));
	barOfPowerUnder.setPosition(sf::Vector2f(position.x, position.y - 120));
	barOfPowerUnder.setFillColor(sf::Color(150, 150, 150, 180));
	cam.draw(barOfPowerUnder);

	sf::RectangleShape barOfPower(sf::Vector2f(fillPercentage * 200, 15));
	barOfPower.setOrigin(sf::Vector2f(barOfPower.getSize().x*0.5, barOfPower.getSize().y*0.5));
	barOfPower.setPosition(sf::Vector2f(position.x, position.y - 120));
	barOfPower.setFillColor(sf::Color(75, 20, 20, 220));
	cam.draw(barOfPower);
}

void draw_interact(const sf::Vector2f& position)
{
	sf::RectangleShape barOfPowerUnder(sf::Vector2f(15, 15));
	barOfPowerUnder.setOrigin(sf::Vector2f(barOfPowerUnder.getSize().x*0.5, barOfPowerUnder.getSize().y*0.5));
	barOfPowerUnder.setPosition(sf::Vector2f(position));
	barOfPowerUnder.setFillColor(sf::Color(0, 0, 220, 100));
	cam.draw(barOfPowerUnder);

}