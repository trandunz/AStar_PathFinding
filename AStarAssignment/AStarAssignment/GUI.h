#pragma once
#include "NumptyBehavior.h"
#include "CButtons.h"
#include "CInputField.h"
#include "RichText.hpp"
#include "Navigation.h"
class GUI :	public NumptyBehavior
{
public:
	GUI(sf::RenderWindow* _renderWindow, sf::View& _worldView, sf::View& _UIView, Navigation* _navigation);
	~GUI();

	void InitNavigationUI();
	void NavigationUI();

private:
	sf::Font m_Font;
	std::vector<sf::Text> m_NavigationElements;
	std::vector<sf::RectangleShape> m_NavigationShapeElements;
	Navigation* m_AStarAgent = nullptr;
	sfe::RichText m_ObsticleText;
	sfe::RichText m_OptimizeCornersText;
	sf::RenderWindow* m_RenderWindow = nullptr;
	sf::View* m_UIView = nullptr;
	sf::View* m_WorldView = nullptr;
};

