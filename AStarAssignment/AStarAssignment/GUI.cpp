#include "GUI.h"

GUI::GUI(sf::RenderWindow* _renderWindow, sf::View& _worldView, sf::View& _UIView, Navigation* _navigation)
{
	m_RenderWindow = _renderWindow;
	m_WorldView = &_worldView;
	m_UIView = &_UIView;
	m_AStarAgent = _navigation;
}

GUI::~GUI()
{
	m_UIView = nullptr;
	m_WorldView = nullptr;
	m_RenderWindow = nullptr;
	m_AStarAgent = nullptr;
}

void GUI::InitNavigationUI()
{
	m_Font.loadFromFile("Fonts/ANDYB.TTF");
	sf::Text m_SourceControls;
	m_SourceControls.setFont(m_Font);
	m_SourceControls.setCharacterSize(28);
	m_SourceControls.setString("Source Node - Middle Mouse");
	m_SourceControls.setFillColor(sf::Color::Cyan);
	m_SourceControls.setOutlineColor(sf::Color::Black);
	m_SourceControls.setOutlineThickness(2);
	m_SourceControls.setOrigin(m_SourceControls.getGlobalBounds().width / 2, m_SourceControls.getGlobalBounds().height / 2);
	m_SourceControls.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.9, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1);
	m_NavigationElements.push_back(m_SourceControls);

	m_SourceControls.setFont(m_Font);
	m_SourceControls.setCharacterSize(28);
	m_SourceControls.setString("Destination Node - Right Mouse");
	m_SourceControls.setFillColor(sf::Color::Magenta);
	m_SourceControls.setOutlineColor(sf::Color::Black);
	m_SourceControls.setOutlineThickness(2);
	m_SourceControls.setOrigin(m_SourceControls.getGlobalBounds().width / 2, m_SourceControls.getGlobalBounds().height / 2);
	m_SourceControls.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.9, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1 + m_SourceControls.getGlobalBounds().height * 2);
	m_NavigationElements.push_back(m_SourceControls);

	m_SourceControls.setFont(m_Font);
	m_SourceControls.setCharacterSize(28);
	m_SourceControls.setString("Toggle Debug - TAB");
	m_SourceControls.setFillColor(sf::Color::White);
	m_SourceControls.setOutlineColor(sf::Color::Black);
	m_SourceControls.setOutlineThickness(2);
	m_SourceControls.setOrigin(m_SourceControls.getGlobalBounds().width / 2, m_SourceControls.getGlobalBounds().height / 2);
	m_SourceControls.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.9, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1 + m_SourceControls.getGlobalBounds().height * 6);
	m_NavigationElements.push_back(m_SourceControls);

	
	sfe::Outline m_Outline;
	m_ObsticleText.setFont(m_Font);
	m_ObsticleText.setCharacterSize(28);
	
	m_ObsticleText << m_Outline;
	m_ObsticleText.setOrigin(m_SourceControls.getGlobalBounds().width / 2, m_SourceControls.getGlobalBounds().height / 2);
	m_ObsticleText.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.6, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1 + m_SourceControls.getGlobalBounds().height * 4);

	sf::RectangleShape m_ControlsBG;
	m_ControlsBG.setSize(sf::Vector2f(360, 240));
	m_ControlsBG.setOrigin(360/2, 240 /2);
	m_ControlsBG.setFillColor(sf::Color::Black);
	m_ControlsBG.setPosition(m_RenderWindow->getView().getCenter().x - m_RenderWindow->getView().getSize().x / 2.9, m_RenderWindow->getView().getCenter().y - m_RenderWindow->getView().getSize().y / 2.1 + m_SourceControls.getGlobalBounds().height * 3.35);
	m_NavigationShapeElements.push_back(m_ControlsBG);
}

void GUI::NavigationUI()
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
	
	m_RenderWindow->setView(*m_UIView);
	for (auto& item : m_NavigationShapeElements)
	{
		m_RenderWindow->draw(item);
	}
	for (auto& item : m_NavigationElements)
	{
		m_RenderWindow->draw(item);
	}
	m_RenderWindow->draw(m_ObsticleText);
	m_RenderWindow->setView(*m_WorldView);
}
