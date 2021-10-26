#include <iostream>

#include "Navigation.h"

void Start();
void Update();
void PolledUpdate();
void Render();

void CreateWindow(sf::Uint32 _style);
void CleanupPointers();

sf::RenderWindow* m_RenderWindow = nullptr;
sf::Event* m_Event;
sf::View m_View;

Navigation* m_Navigation = nullptr;

sf::Vector2f m_MousePos;

int main()
{
	CreateWindow(sf::Style::Default);

	Start();
	Update();
	Render();

	CleanupPointers();

	return NULL;
}

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

	m_RenderWindow->create(sf::VideoMode(1010, 1010), "A* Pathfinding", _style, m_Settings);
	m_RenderWindow->setFramerateLimit(60);
	m_RenderWindow->setVerticalSyncEnabled(true);
	m_RenderWindow->setKeyRepeatEnabled(false);
	m_RenderWindow->setMouseCursorVisible(true);

	m_View = sf::View(sf::Vector2f((SIZE * 5) - 5, (SIZE * 5) - 5), sf::Vector2f(1010, 1010));
	float zoomfactor = SIZE / 100.f;
	m_View.zoom(zoomfactor);
	m_RenderWindow->setView(m_View);
}

void Start()
{
	m_Navigation = new Navigation(m_RenderWindow);
	m_Navigation->Start();
}

void Update()
{
	while (m_RenderWindow->isOpen())
	{
		m_MousePos = m_RenderWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_RenderWindow), m_View);

		m_Navigation->Update();

		PolledUpdate();

		Render();
	}
}

void PolledUpdate()
{
	while (m_RenderWindow->pollEvent(*m_Event))
	{
		if (m_Event->type == sf::Event::Closed)
		{
			m_RenderWindow->close();
			break;
		}
		else if (m_Event->type == sf::Event::KeyPressed)
		{
			if (m_Event->key.code == sf::Keyboard::Tab)
			{
				m_Navigation->ToggleDebug();
			}
			else if (m_Event->key.code == sf::Keyboard::F1)
			{
				m_Navigation->AStarTraversal(m_Navigation->m_nodes[16][16], m_Navigation->m_nodes[2][2]);
			}

			break;
		}
		else if (m_Event->type == sf::Event::MouseButtonPressed)
		{
			if (m_Event->key.code == sf::Mouse::Left)
			{
				sf::Vector2i index = m_Navigation->GetMousedOverTile(m_MousePos);
				m_Navigation->ChangeTileColour(index);
			}

			break;
		}
	}
}

void Render()
{
	m_Navigation->Render();
}

void CleanupPointers()
{
	NumptyBehavior::DeletePointer(m_RenderWindow);
	m_RenderWindow = nullptr;
	NumptyBehavior::DeletePointer(m_Navigation);
	m_Navigation = nullptr;
}
