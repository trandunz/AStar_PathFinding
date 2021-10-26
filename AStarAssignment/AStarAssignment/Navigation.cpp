#include "Navigation.h"

Navigation::Navigation(sf::RenderWindow* _renderWindow)
{
	m_RenderWindow = _renderWindow;
	LoadFont(m_Font, "Fonts/ANDYB.TTF");
}

Navigation::~Navigation()
{
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

	AStarTraversal(m_nodes[0][0], m_nodes[16][16]);
}

void Navigation::Update()
{
	UpdateText();
}

void Navigation::PolledUpdate()
{
	
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
	m_RenderWindow->draw(m_Shapes[_i][_j]);
}

void Navigation::RenderText()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m_nodes[i][j].m_bTraversed)
			{
				m_RenderWindow->draw(m_nodes[i][j].m_FText);
				m_RenderWindow->draw(m_nodes[i][j].m_GText);
				m_RenderWindow->draw(m_nodes[i][j].m_HText);
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
			m_nodes[i][j].m_GText.setString(std::to_string(m_nodes[i][j].G));
			m_nodes[i][j].m_HText.setString(std::to_string(m_nodes[i][j].H));
			m_nodes[i][j].m_FText.setString(std::to_string(m_nodes[i][j].F));
		}
	}
}

void Navigation::Initnodes()
{
	for (int i = 0; i < SIZE; i++) 
	{
		for (int j = 0; j < SIZE; j++) 
		{
			m_nodes[i][j].m_Position = std::make_pair(i,j);

			LoadTextWithFont(m_nodes[i][j].m_FText, m_Font, sf::Color::Cyan);
			LoadTextWithFont(m_nodes[i][j].m_GText, m_Font, sf::Color::Cyan);
			LoadTextWithFont(m_nodes[i][j].m_HText, m_Font, sf::Color::Cyan);
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
	m_Shapes[_i][_j].setPosition(m_nodes[_i][_j].m_Position.first * NODE_DIFFERENCE, m_nodes[_i][_j].m_Position.second * NODE_DIFFERENCE);

	m_nodes[_i][_j].m_FText.setScale(0.12f, 0.12f);
	m_nodes[_i][_j].m_GText.setScale(0.12f, 0.12f);
	m_nodes[_i][_j].m_HText.setScale(0.12f, 0.12f);

	m_nodes[_i][_j].m_FText.setOrigin(m_nodes[_i][_j].m_FText.getGlobalBounds().width/2 , m_nodes[_i][_j].m_FText.getGlobalBounds().height / 2);
	m_nodes[_i][_j].m_GText.setOrigin(m_nodes[_i][_j].m_GText.getGlobalBounds().width / 2, m_nodes[_i][_j].m_GText.getGlobalBounds().height / 2);
	m_nodes[_i][_j].m_HText.setOrigin(m_nodes[_i][_j].m_HText.getGlobalBounds().width / 2, m_nodes[_i][_j].m_HText.getGlobalBounds().height / 2);

	m_nodes[_i][_j].m_FText.setPosition(m_Shapes[_i][_j].getPosition().x + 1, m_Shapes[_i][_j].getPosition().y - 3.5f);
	m_nodes[_i][_j].m_GText.setPosition(m_Shapes[_i][_j].getPosition().x - 3.5f, m_Shapes[_i][_j].getPosition().y + 1.5);
	m_nodes[_i][_j].m_HText.setPosition(m_Shapes[_i][_j].getPosition().x + 1, m_Shapes[_i][_j].getPosition().y + 1.5);
}

void Navigation::CalculatePath(node& _destination)
{
	int row = _destination.m_Position.first;
	int col = _destination.m_Position.second;

	while (!(m_nodes[row][col].m_Parent.first == row && m_nodes[row][col].m_Parent.second == col)) 
	{
		path.push(std::make_pair(row, col));
		int temp_row = m_nodes[row][col].m_Parent.first;
		int temp_col = m_nodes[row][col].m_Parent.second;
		row = temp_row;
		col = temp_col;
	}

	path.push(std::make_pair(row, col));
	while (!path.empty()) 
	{
		std::pair<int, int> p = path.top();
		path.pop();
		m_nodes[p.first][p.second].m_bTraversed = true;
	}
}

void Navigation::AStarTraversal(node& _source, node& _destination)
{
	while (!path.empty())
	{
		path.pop();
	}
	path = std::stack<std::pair<int, int>>();
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			m_nodes[i][j].H = INT_MAX;
			m_nodes[i][j].G = INT_MAX;
			m_nodes[i][j].F = INT_MAX;
			m_nodes[i][j].m_bTraversed = false;
		}
	}
	

	std::set<std::pair<int, std::pair<int, int>>> m_OpenList;
	bool m_ClosedList[SIZE][SIZE];
	memset(m_ClosedList, false, sizeof(m_ClosedList));

	m_nodes[_source.m_Position.first][_source.m_Position.second].m_Parent = _source.m_Parent;
	
	int i = 0;
	int j = 0;

	i = _source.m_Position.first;
	j = _source.m_Position.second;

	m_nodes[i][j].F = 0.0;
	m_nodes[i][j].G = 0.0;
	m_nodes[i][j].H = 0.0;
	m_nodes[i][j].m_Parent.first = i;
	m_nodes[i][j].m_Parent.second = j;

	m_OpenList.insert(std::make_pair(0, std::make_pair(i,j)));

	bool reachedDestination = false;

	while (!m_OpenList.empty())
	{
		std::pair<int, std::pair<int, int>> p = *m_OpenList.begin();
		m_OpenList.erase(m_OpenList.begin());

		i = p.second.first;
		j = p.second.second;

		m_ClosedList[i][j] = true;


		CalculateNeighbors(i,j, -1, 0, _destination, reachedDestination, m_OpenList, m_ClosedList);
		CalculateNeighbors(i, j, 1, 0, _destination, reachedDestination, m_OpenList, m_ClosedList);
		CalculateNeighbors(i, j, 0, -1, _destination, reachedDestination, m_OpenList, m_ClosedList);
		CalculateNeighbors(i, j, 0, 1, _destination, reachedDestination, m_OpenList, m_ClosedList);

		CalculateNeighbors(i, j, -1, -1, _destination, reachedDestination, m_OpenList, m_ClosedList);
		CalculateNeighbors(i, j, 1, -1, _destination, reachedDestination, m_OpenList, m_ClosedList);
		CalculateNeighbors(i, j, -1, 1, _destination, reachedDestination, m_OpenList, m_ClosedList);
		CalculateNeighbors(i, j, 1, 1, _destination, reachedDestination, m_OpenList, m_ClosedList);
	}
}

void Navigation::CalculateNeighbors(int _i, int _j, int _offsetI, int _offsetJ, node& _destination, bool& _reachedDestination, std::set<std::pair<int, std::pair<int, int>>>& _openList, bool m_ClosedList[SIZE][SIZE])
{
	//----------- 1st Successor (North) ------------
	int newG = 0;
	int newF = 0;
	int newH = 0;
		// Only process this cell if this is a valid one
	if (IsValid(_i + _offsetI, _j + _offsetJ) == true)
	{
		// If the destination cell is the same as the
		// current successor
		if (IsDestination(std::make_pair(_i + _offsetI, _j + _offsetJ), _destination.m_Position) == true)
		{
			// Set the Parent of the destination cell
			m_nodes[_i + _offsetI][_j + _offsetJ].m_Parent.first = _i;
			m_nodes[_i + _offsetI][_j + _offsetJ].m_Parent.second = _i;
			printf("The destination cell is found\n");
			CalculatePath(_destination);
			_reachedDestination = true;
			return;
		}
		// If the successor is already on the closed
		// list or if it is blocked, then ignore it.
		// Else do the following
		else if (m_ClosedList[_i + _offsetI][_j + _offsetJ] == false && !IsBlocked(std::make_pair(_i + _offsetI, _j + _offsetJ)) == true)
		{
			newG = m_nodes[_i][_j].G + 1.0;
			newH = CalculateHValue(std::make_pair(_offsetI + _i, _offsetJ+ _j), _destination.m_Position);
			newF = newG + newH;

			// If it isn’t on the open list, add it to
			// the open list. Make the current square
			// the parent of this square. Record the
			// f, g, and h costs of the square cell
			//                OR
			// If it is on the open list already, check
			// to see if this path to that square is
			// better, using 'f' cost as the measure.
			if (m_nodes[_offsetI + _i][_j + _offsetJ].F == INT_MAX || m_nodes[_i + _offsetI][_j + _offsetJ].F > newF)
			{
				_openList.insert(std::make_pair(newF, std::make_pair(_i + _offsetI, _j + _offsetJ)));

				// Update the details of this cell
				m_nodes[_i + _offsetI][_j + _offsetJ].F = newF;
				m_nodes[_i + _offsetI][_j + _offsetJ].G = newG;
				m_nodes[_i + _offsetI][_j + _offsetJ].H = newH;
				m_nodes[_i + _offsetI][_j + _offsetJ].m_Parent.first = _i;
				m_nodes[_i + _offsetI][_j + _offsetJ].m_Parent.second = _j;
			}
		}
	}
}

void Navigation::ToggleDebug()
{
	m_bDebug = !m_bDebug;
}

sf::Vector2i Navigation::GetMousedOverTile(sf::Vector2f _mousePos)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (m_Shapes[i][j].getGlobalBounds().contains(_mousePos))
			{
				std::cout << i << " - " << j << std::endl;
				return sf::Vector2i(i,j);
				break;
			}
		}
	}
}

void Navigation::ChangeTileColour(sf::Vector2i _index)
{
	m_nodes[_index.x][_index.y].m_bObstical = !m_nodes[_index.x][_index.y].m_bObstical;
	if (m_nodes[_index.x][_index.y].m_bObstical)
	{
		m_Shapes[_index.x][_index.y].setFillColor(sf::Color::Red);
	}
	else
	{
		m_Shapes[_index.x][_index.y].setFillColor(sf::Color::Transparent);
	}

	
}
