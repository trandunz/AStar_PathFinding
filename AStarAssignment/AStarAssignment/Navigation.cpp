#include "Navigation.h"

Navigation::Navigation(sf::RenderWindow* _renderWindow)
{
	m_RenderWindow = _renderWindow;
	LoadFont(m_Font, "Fonts/ANDYB.TTF");
	memset(m_ClosedList, false, sizeof(m_ClosedList));
}

Navigation::~Navigation()
{
	CleanupContainers();
	memset(m_ClosedList, false, sizeof(m_ClosedList));
	m_SourceNode = nullptr;
	m_DestinationNode = nullptr;
	m_RenderWindow = nullptr;
}

void Navigation::Start()
{
	Initnodes();

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{

			InitShapes(i, j);
		}
	}
}

void Navigation::Update(sf::Vector2f _mouserPos)
{
	AStarTraversal(*m_SourceNode, *m_DestinationNode);
	UpdateText();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (IsMouseOverTile(_mouserPos))
		{
			sf::Vector2i index = GetMousedOverTile(_mouserPos);
			if (!m_Nodes[index.x][index.y].m_bDestination && !m_Nodes[index.x][index.y].m_bSource)
			{
				ChangeTileType(index);
			}
		}
	}
}

void Navigation::PolledUpdate(sf::Event* _event, sf::Vector2f _mouserPos)
{
	if (_event->type == sf::Event::KeyPressed)
	{
		if (_event->key.code == sf::Keyboard::Tab)
		{
			ToggleDebug();
		}
		else if (_event->key.code == sf::Keyboard::F1)
		{
			m_bEraser = !m_bEraser;
		}
	}
	else if (_event->type == sf::Event::MouseButtonPressed)
	{
		if (IsMouseOverTile(_mouserPos))
		{
			if (_event->key.code == sf::Mouse::Middle)
			{
				sf::Vector2i index = GetMousedOverTile(_mouserPos);

				if (!m_Nodes[index.x][index.y].m_bSource && !m_Nodes[index.x][index.y].m_bObstical)
				{
					m_Nodes[index.x][index.y].m_bDestination = true;
					m_DestinationNode = &m_Nodes[index.x][index.y];
				}
			}
			else if (_event->key.code == sf::Mouse::Right)
			{
				sf::Vector2i index = GetMousedOverTile(_mouserPos);
				if (!m_Nodes[index.x][index.y].m_bDestination && !m_Nodes[index.x][index.y].m_bObstical)
				{
					m_Nodes[index.x][index.y].m_bSource = true;
					m_SourceNode = &m_Nodes[index.x][index.y];
				}
			}
		}
	}
}

void Navigation::Render()
{
	m_RenderWindow->clear();

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			RenderShapes(i, j);
		}
	}

	if (m_bDebug)
	{
		RenderText();
	}

	m_RenderWindow->display();
}

void Navigation::RenderShapes(int _i, int _j)
{
	SetNodeColourToType(_i, _j);

	m_RenderWindow->draw(m_Shapes[_i][_j]);
}

void Navigation::RenderText()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m_Nodes[i][j].m_bTraversed && !m_Nodes[i][j].m_bSource && !m_Nodes[i][j].m_bDestination)
			{
				m_RenderWindow->draw(m_Nodes[i][j].m_FText);
				m_RenderWindow->draw(m_Nodes[i][j].m_GText);
				m_RenderWindow->draw(m_Nodes[i][j].m_HText);
			}
		}
	}
}

void Navigation::UpdateText()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			m_Nodes[i][j].m_GText.setString(std::to_string(m_Nodes[i][j].G));
			m_Nodes[i][j].m_HText.setString(std::to_string(m_Nodes[i][j].H));
			m_Nodes[i][j].m_FText.setString(std::to_string(m_Nodes[i][j].F));
		}
	}
}

void Navigation::Initnodes()
{
	for (int i = 0; i < SIZE; i++) 
	{
		for (int j = 0; j < SIZE; j++) 
		{
			m_Nodes[i][j].m_Position = std::make_pair(i,j);

			LoadTextWithFont(m_Nodes[i][j].m_FText, m_Font, sf::Color::Black);
			LoadTextWithFont(m_Nodes[i][j].m_GText, m_Font, sf::Color::Black);
			LoadTextWithFont(m_Nodes[i][j].m_HText, m_Font, sf::Color::Black);
		}
	}
}

void Navigation::InitShapes(int _i, int _j)
{
	m_Shapes[_i][_j] = sf::RectangleShape(sf::Vector2f(10, 10));
	m_Shapes[_i][_j].setSize(sf::Vector2f(10, 10));
	m_Shapes[_i][_j].setFillColor(sf::Color::Transparent);
	m_Shapes[_i][_j].setOutlineThickness(0.1);
	m_Shapes[_i][_j].setOutlineColor(sf::Color::Green);
	m_Shapes[_i][_j].setOrigin(5, 5);
	m_Shapes[_i][_j].setPosition(m_Nodes[_i][_j].m_Position.first * NODE_DIFFERENCE, m_Nodes[_i][_j].m_Position.second * NODE_DIFFERENCE);

	m_Nodes[_i][_j].m_FText.setScale(0.12f, 0.12f);
	m_Nodes[_i][_j].m_GText.setScale(0.12f, 0.12f);
	m_Nodes[_i][_j].m_HText.setScale(0.12f, 0.12f);

	m_Nodes[_i][_j].m_FText.setOrigin(m_Nodes[_i][_j].m_FText.getGlobalBounds().width/2 , m_Nodes[_i][_j].m_FText.getGlobalBounds().height / 2);
	m_Nodes[_i][_j].m_GText.setOrigin(m_Nodes[_i][_j].m_GText.getGlobalBounds().width / 2, m_Nodes[_i][_j].m_GText.getGlobalBounds().height / 2);
	m_Nodes[_i][_j].m_HText.setOrigin(m_Nodes[_i][_j].m_HText.getGlobalBounds().width / 2, m_Nodes[_i][_j].m_HText.getGlobalBounds().height / 2);

	m_Nodes[_i][_j].m_FText.setPosition(m_Shapes[_i][_j].getPosition().x + 1, m_Shapes[_i][_j].getPosition().y - 3.5f);
	m_Nodes[_i][_j].m_GText.setPosition(m_Shapes[_i][_j].getPosition().x - 3.5f, m_Shapes[_i][_j].getPosition().y + 1.5);
	m_Nodes[_i][_j].m_HText.setPosition(m_Shapes[_i][_j].getPosition().x + 1, m_Shapes[_i][_j].getPosition().y + 1.5);
}

void Navigation::CalculatePath(Node& _destination)
{
	int row = _destination.m_Position.first;
	int col = _destination.m_Position.second;

	while (!(m_Nodes[row][col].m_Parent.first == row && m_Nodes[row][col].m_Parent.second == col)) 
	{
		m_Path.push(std::make_pair(row, col));
		int temp_row = m_Nodes[row][col].m_Parent.first;
		int temp_col = m_Nodes[row][col].m_Parent.second;
		row = temp_row;
		col = temp_col;
	}

	m_Path.push(std::make_pair(row, col));
	while (!m_Path.empty()) 
	{
		std::pair<int, int> p = m_Path.top();
		m_Path.pop();
		m_Nodes[p.first][p.second].m_bTraversed = true;
	}
}

void Navigation::AStarTraversal(Node& _source, Node& _destination)
{
	if (m_SourceNode != nullptr && m_DestinationNode != nullptr)
	{
		CleanupContainers();
		std::set<std::pair<int, std::pair<int, int>>> m_OpenList;

		m_Nodes[_source.m_Position.first][_source.m_Position.second].m_Parent = _source.m_Parent;

		int i = 0;
		int j = 0;

		i = _source.m_Position.first;
		j = _source.m_Position.second;

		m_Nodes[i][j].F = 0;
		m_Nodes[i][j].G = 0;
		m_Nodes[i][j].H = 0;
		m_Nodes[i][j].m_Parent.first = i;
		m_Nodes[i][j].m_Parent.second = j;
		m_Nodes[i][j].m_bSource = true;
		m_Nodes[i][j].m_bDestination = false;

		m_OpenList.insert(std::make_pair(0, std::make_pair(i, j)));

		bool reachedDestination = false;

		while (!m_OpenList.empty())
		{
			std::pair<int, std::pair<int, int>> p = *m_OpenList.begin();
			m_OpenList.erase(m_OpenList.begin());

			i = p.second.first;
			j = p.second.second;

			m_ClosedList[i][j] = true;

			CalculateNeighbors(i, j, -1, 0, _destination, reachedDestination, m_OpenList, m_ClosedList);
			CalculateNeighbors(i, j, 1, 0, _destination, reachedDestination, m_OpenList, m_ClosedList);
			CalculateNeighbors(i, j, 0, -1, _destination, reachedDestination, m_OpenList, m_ClosedList);
			CalculateNeighbors(i, j, 0, 1, _destination, reachedDestination, m_OpenList, m_ClosedList);

			CalculateNeighbors(i, j, -1, -1, _destination, reachedDestination, m_OpenList, m_ClosedList);
			CalculateNeighbors(i, j, 1, -1, _destination, reachedDestination, m_OpenList, m_ClosedList);
			CalculateNeighbors(i, j, -1, 1, _destination, reachedDestination, m_OpenList, m_ClosedList);
			CalculateNeighbors(i, j, 1, 1, _destination, reachedDestination, m_OpenList, m_ClosedList);
		}
	}
}

void Navigation::CalculateNeighbors(int _i, int _j, int _offsetI, int _offsetJ, Node& _destination, bool& _reachedDestination, std::set<std::pair<int, std::pair<int, int>>>& _openList, bool m_ClosedList[SIZE][SIZE])
{
	int newG = 0;
	int newF = 0;
	int newH = 0;

	if (IsValid(_i + _offsetI, _j + _offsetJ) == true)
	{
		if (IsDestination(std::make_pair(_i + _offsetI, _j + _offsetJ), _destination.m_Position) == true)
		{
			m_Nodes[_i + _offsetI][_j + _offsetJ].m_Parent.first = _i;
			m_Nodes[_i + _offsetI][_j + _offsetJ].m_Parent.second = _j;
			CalculatePath(_destination);
			_reachedDestination = true;
			m_Nodes[_i + _offsetI][_j + _offsetJ].m_bDestination = true;
			return;
		}
		else if (m_ClosedList[_i + _offsetI][_j + _offsetJ] == false && !IsBlocked(std::make_pair(_i + _offsetI, _j + _offsetJ)) == true)
		{
			newG = m_Nodes[_i][_j].G + 1.0;
			newH = CalculateHValue(std::make_pair(_offsetI + _i, _offsetJ+ _j), _destination.m_Position);
			newF = newG + newH;

			if (m_Nodes[_offsetI + _i][_j + _offsetJ].F == INT_MAX || m_Nodes[_i + _offsetI][_j + _offsetJ].F > newF)
			{
				_openList.insert(std::make_pair(newF, std::make_pair(_i + _offsetI, _j + _offsetJ)));

				m_Nodes[_i + _offsetI][_j + _offsetJ].F = newF;
				m_Nodes[_i + _offsetI][_j + _offsetJ].G = newG;
				m_Nodes[_i + _offsetI][_j + _offsetJ].H = newH;
				m_Nodes[_i + _offsetI][_j + _offsetJ].m_Parent.first = _i;
				m_Nodes[_i + _offsetI][_j + _offsetJ].m_Parent.second = _j;
			}
		}
		return;
	}
}

void Navigation::ToggleDebug()
{
	m_bDebug = !m_bDebug;
}

bool Navigation::IsMouseOverTile(sf::Vector2f _mousePos)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m_Shapes[i][j].getGlobalBounds().contains(_mousePos))
			{
				return true;
			}
		}
	}
	return false;
}

sf::Vector2i Navigation::GetMousedOverTile(sf::Vector2f _mousePos)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m_Shapes[i][j].getGlobalBounds().contains(_mousePos))
			{
				return sf::Vector2i(i,j);
			}
		}
	}
}

void Navigation::ChangeTileType(sf::Vector2i _index)
{
	m_Nodes[_index.x][_index.y].m_bObstical = m_bEraser;
	
	if (m_Nodes[_index.x][_index.y].m_bSource)
	{
		m_Nodes[_index.x][_index.y].m_bSource = false;
		m_SourceNode = nullptr;
	}

	SetNodeColourToType(_index.x, _index.y);
}

void Navigation::CleanupContainers()
{
	// Path Stack Cleanup
	m_Path = std::stack<std::pair<int, int>>();

	// Node Value Reset
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			m_Nodes[i][j].H = INT_MAX;
			m_Nodes[i][j].G = INT_MAX;
			m_Nodes[i][j].F = INT_MAX;

			m_Nodes[i][j].m_bTraversed = false;
			m_Nodes[i][j].m_bSource = false;
			m_Nodes[i][j].m_bDestination = false;
			m_Nodes[i][j].m_Parent = std::make_pair(-1, -1);
		}
	}

	// Closed List Value Reset
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			m_ClosedList[i][j] = false;
		}
	}
}

void Navigation::SetNodeColourToType(int _i, int _j)
{
	if (m_Nodes[_i][_j].m_bTraversed)
	{
		m_Shapes[_i][_j].setFillColor(sf::Color::Green);
	}
	if (m_Nodes[_i][_j].m_bSource)
	{
		m_Shapes[_i][_j].setFillColor(sf::Color::Cyan);
	}
	if (m_Nodes[_i][_j].m_bObstical)
	{
		m_Shapes[_i][_j].setFillColor(sf::Color::Red);
	}
	if (m_Nodes[_i][_j].m_bDestination)
	{
		m_Shapes[_i][_j].setFillColor(sf::Color::Magenta);
	}
	if (!m_Nodes[_i][_j].m_bObstical && !m_Nodes[_i][_j].m_bTraversed && !m_Nodes[_i][_j].m_bSource && !m_Nodes[_i][_j].m_bDestination)
	{
		m_Shapes[_i][_j].setFillColor(sf::Color::Transparent);
	}
}

Node& Navigation::GetSourceNode()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m_Nodes[i][j].m_bSource)
			{
				return m_Nodes[i][j];
			}
		}
	}
}

Node& Navigation::GetDestinationNode()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m_Nodes[i][j].m_bDestination)
			{
				return m_Nodes[i][j];
			}
		}
	}
}
