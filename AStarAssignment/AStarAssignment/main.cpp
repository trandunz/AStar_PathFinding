//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Main.cpp
// Description : Main Implementation file for AStarPathfinding.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#include "Navigation.h"
#include "GUI.h"

void Start();
void Update();
void PolledUpdate();
void Render();

void CreateWindow(sf::Uint32 _style);
void CleanupPointers();

sf::RenderWindow* m_RenderWindow = nullptr;
sf::Event* m_Event;
sf::View m_WorldView;
sf::View m_UIView;

Navigation* m_Navigation = nullptr;
GUI* m_GUI = nullptr;

sf::Vector2f m_MousePos;

/// <summary>
/// Main Function For The AStarPathfinding Program
/// </summary>
/// <returns></returns>
int main()
{
	CreateWindow(sf::Style::Close + sf::Style::Titlebar);

	Start();
	Update();
	Render();

	CleanupPointers();

	return NULL;
}

/// <summary>
/// Creates A RenderWindow With The Specified Style (Close Button enabled?, Title enabled?, e.t.c)
/// </summary>
/// <param name="_style"></param>
void CreateWindow(sf::Uint32 _style)
{
	if (m_RenderWindow == nullptr)
	{
		m_RenderWindow = new sf::RenderWindow();
	}

	if (m_Event == nullptr)
	{
		m_Event = new sf::Event;
	}

	// Render Window Settings
	sf::ContextSettings m_Settings;
	m_Settings.antialiasingLevel = 8;

	m_RenderWindow->create(sf::VideoMode(1310, 1310), "A* Pathfinding", _style, m_Settings);
	m_RenderWindow->setFramerateLimit(60);
	m_RenderWindow->setVerticalSyncEnabled(true);
	m_RenderWindow->setKeyRepeatEnabled(false);
	m_RenderWindow->setMouseCursorVisible(true);

	m_UIView = sf::View(sf::Vector2f((SIZE * 5) - 5, (SIZE * 5) - 5), sf::Vector2f(1310, 1310));
	m_WorldView = sf::View(sf::Vector2f((SIZE * 5) - 5, (SIZE * 5) - 5), sf::Vector2f(1310, 1310));
	float zoomfactor = SIZE / 130.f;
	m_WorldView.zoom(zoomfactor);
	m_RenderWindow->setView(m_WorldView);
}

/// <summary>
/// Start Function (Should Be Called On Start)
/// Creates A New Navigation Instance And Initializes The GUI
/// </summary>
void Start()
{
	m_Navigation = new Navigation(m_RenderWindow);
	m_Navigation->Start();

	m_RenderWindow->setView(m_UIView);
	m_GUI = new GUI(m_RenderWindow, m_WorldView, m_UIView, m_Navigation);
	m_GUI->InitNavigationUI();
	m_RenderWindow->setView(m_WorldView);
}

/// <summary>
/// RUNS EVERY FRAME
/// Main Update Loop
/// </summary>
void Update()
{
	while (m_RenderWindow->isOpen())
	{
		m_MousePos = m_RenderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_RenderWindow), m_WorldView);
		m_Navigation->Update(m_MousePos);

		PolledUpdate();

		Render();
	}
}

/// <summary>
/// Polled Update Loop
/// Handles Inputs Such As Mouse Up And Mouse Down
/// </summary>
void PolledUpdate()
{
	while (m_RenderWindow->pollEvent(*m_Event))
	{
		if (m_Event->type == sf::Event::Closed)
		{
			m_RenderWindow->close();
			break;
		}

		m_Navigation->PolledUpdate(m_Event, m_MousePos);
	}
}

/// <summary>
/// Main Render Function
/// Handles Rendering Everything To The sf::RenderWindow
/// </summary>
void Render()
{
	m_RenderWindow->clear();
	m_Navigation->Render();

	m_GUI->NavigationUI();
	m_RenderWindow->display();
}

/// <summary>
/// Cleans Up All Pointers And Deletes Them If They Point To A Memory Location
/// </summary>
void CleanupPointers()
{
	NumptyBehavior::DeletePointer(m_GUI);
	m_GUI = nullptr;
	NumptyBehavior::DeletePointer(m_Navigation);
	m_Navigation = nullptr;
	NumptyBehavior::DeletePointer(m_RenderWindow);
	m_RenderWindow = nullptr;
}
