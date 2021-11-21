//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : GUI.h
// Description : GUI Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

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
	void SourceNodeGUI(sf::Text& _text);
	void DestinationNodeGUI(sf::Text& _text);
	void ToggleDebugGUI(sf::Text& _text);
	sfe::Outline InitRichTextOutline(sf::Text& _text);
	void InitObsticleGUI(sf::Text& _text);
	void InitGUIBackgrond(sf::Text& _text);

	void RenderNavigationElements();
	void HandleNavigationUIRichText();

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

