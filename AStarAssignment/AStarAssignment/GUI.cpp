//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : GUI.cpp
// Description : GUI Implementation file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#include "GUI.h"

/// <summary>
/// GUI Constructor
/// Initializes Params
/// </summary>
/// <param name="_renderWindow"></param>
/// <param name="_worldView"></param>
/// <param name="_UIView"></param>
/// <param name="_navigation"></param>
GUI::GUI(sf::RenderWindow* _renderWindow, sf::View& _worldView, sf::View& _UIView, Navigation* _navigation)
{
	m_RenderWindow = _renderWindow;
	m_WorldView = &_worldView;
	m_UIView = &_UIView;
	m_AStarAgent = _navigation;
}

/// <summary>
/// GUI Destructtor
/// Nullptr's All Contructor Params
/// </summary>
GUI::~GUI()
{
	m_UIView = nullptr;
	m_WorldView = nullptr;
	m_RenderWindow = nullptr;
	m_AStarAgent = nullptr;
}

/// <summary>
/// Initializes The Navigation UI
/// </summary>
void GUI::InitNavigationUI()
{
	m_Font.loadFromFile("Fonts/ANDYB.TTF");
	sf::Text m_SourceControls;

	SourceNodeGUI(m_SourceControls);
	DestinationNodeGUI(m_SourceControls);
	ToggleDebugGUI(m_SourceControls);
	InitObsticleGUI(m_SourceControls);
	InitGUIBackgrond(m_SourceControls);
}


/// <summary>
/// Handles The Navigation GUI
/// Meant To Be Called In Update
/// </summary>
void GUI::NavigationUI()
{
	HandleNavigationUIRichText();
//  Render
	////// 
	m_RenderWindow->setView(*m_UIView);
	RenderNavigationElements();
	m_RenderWindow->setView(*m_WorldView);
	//////
}

/// <summary>
/// Initializes The Source Node GUI
/// </summary>
/// <param name="_text"></param>
void GUI::SourceNodeGUI(sf::Text& _text)
{
	_text.setFont(m_Font);
	_text.setCharacterSize((unsigned)28);
	_text.setString("Source Node - Middle Mouse");
	_text.setFillColor(sf::Color::Cyan);
	_text.setOutlineColor(sf::Color::Black);
	_text.setOutlineThickness(2.0f);
	_text.setOrigin(_text.getGlobalBounds().width / 2, _text.getGlobalBounds().height / 2);
	_text.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.9f, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1f);
	m_NavigationElements.push_back(_text);
}

/// <summary>
/// Initializes The Destination Node GUI
/// </summary>
/// <param name="_text"></param>
void GUI::DestinationNodeGUI(sf::Text& _text)
{
	_text.setFont(m_Font);
	_text.setCharacterSize((unsigned)28);
	_text.setString("Destination Node - Right Mouse");
	_text.setFillColor(sf::Color::Magenta);
	_text.setOutlineColor(sf::Color::Black);
	_text.setOutlineThickness(2.0f);
	_text.setOrigin(_text.getGlobalBounds().width / 2, _text.getGlobalBounds().height / 2);
	_text.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.9f, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1f + _text.getGlobalBounds().height * 2.f);
	m_NavigationElements.push_back(_text);
}

/// <summary>
/// Initalizes The Debug GUI Toggle Text
/// </summary>
/// <param name="_text"></param>
void GUI::ToggleDebugGUI(sf::Text& _text)
{
	_text.setFont(m_Font);
	_text.setCharacterSize((unsigned)28);
	_text.setString("Toggle Debug - TAB");
	_text.setFillColor(sf::Color::White);
	_text.setOutlineColor(sf::Color::Black);
	_text.setOutlineThickness(2.0f);
	_text.setOrigin(_text.getGlobalBounds().width / 2, _text.getGlobalBounds().height / 2);
	_text.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.9f, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1f + _text.getGlobalBounds().height * 6.f);
	m_NavigationElements.push_back(_text);
}

/// <summary>
/// Initializes All Rich Text With Black Outline
/// </summary>
/// <param name="_text"></param>
/// <returns></returns>
sfe::Outline GUI::InitRichTextOutline(sf::Text& _text)
{
	sfe::Outline m_Outline;
	m_OptimizeCornersText.setFont(m_Font);
	m_OptimizeCornersText.setCharacterSize((unsigned)28);
	m_OptimizeCornersText << m_Outline;
	m_OptimizeCornersText.setOrigin(_text.getGlobalBounds().width / 2, _text.getGlobalBounds().height / 2);
	m_OptimizeCornersText.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.8f, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1f + _text.getGlobalBounds().height * 8.f);
	return m_Outline;
}

/// <summary>
/// Initalizes The Obsticle GUI
/// </summary>
/// <param name="_text"></param>
void GUI::InitObsticleGUI(sf::Text& _text)
{
	m_ObsticleText.setFont(m_Font);
	m_ObsticleText.setCharacterSize((unsigned)28);
	m_ObsticleText << InitRichTextOutline(_text);
	m_ObsticleText.setOrigin(_text.getGlobalBounds().width / 2, _text.getGlobalBounds().height / 2);
	m_ObsticleText.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.6f, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1f + _text.getGlobalBounds().height * 4.f);

}

/// <summary>
/// Initializes The GUI Background sf::RectangleShape
/// </summary>
void GUI::InitGUIBackgrond(sf::Text& _text)
{
	sf::RectangleShape m_ControlsBG;
	m_ControlsBG.setSize(sf::Vector2f(360.0f, 300.0f));
	m_ControlsBG.setOrigin(360.0f / 2.0f, 300.0f / 2.0f);
	m_ControlsBG.setFillColor(sf::Color::Black);
	m_ControlsBG.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.9f, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1f + _text.getGlobalBounds().height * 4.25f);
	m_NavigationShapeElements.push_back(m_ControlsBG);
}

/// <summary>
/// Renders All Navigation Elements
/// </summary>
void GUI::RenderNavigationElements()
{
	for (auto& item : m_NavigationShapeElements)
	{
		m_RenderWindow->draw(item);
	}
	for (auto& item : m_NavigationElements)
	{
		m_RenderWindow->draw(item);
	}
	m_RenderWindow->draw(m_ObsticleText);
	m_RenderWindow->draw(m_OptimizeCornersText);
}

/// <summary>
/// Handles The Rich Text Colour Changes
/// </summary>
void GUI::HandleNavigationUIRichText()
{
	if (m_AStarAgent->m_bEraser)
	{
		m_ObsticleText.clear();
		m_ObsticleText << sf::Color::Red << "Toggle " << sf::Color::White << "Eraser " << sf::Color::Red << "/ " << "Obsticle " << "- " << "F1";
	}
	else
	{
		m_ObsticleText.clear();
		m_ObsticleText << sf::Color::Red << "Toggle " << sf::Color::Red << "Eraser " << sf::Color::Red << "/ " << sf::Color::White << "Obsticle " << sf::Color::Red << "- " << "F1";
	}

	if (m_AStarAgent->m_bOptimizeCorners)
	{
		m_OptimizeCornersText.clear();
		m_OptimizeCornersText << sf::Color::Yellow << "Optimize Corners " << sf::Color::White << "- " << "F2";
	}
	else
	{
		m_OptimizeCornersText.clear();
		m_OptimizeCornersText << sf::Color::White << "Optimize Corners " << sf::Color::White << "- " << "F2";
	}
}
