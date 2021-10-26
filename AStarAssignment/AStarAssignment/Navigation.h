#pragma once

#include "NumptyBehavior.h"

#define NODE_DIFFERENCE 10
#define SIZE 20

#include "node.h"

class Navigation : public NumptyBehavior
{
public:
	Navigation(sf::RenderWindow* _renderWindow);
	~Navigation();

	virtual void Start() override;
	virtual void Update() override;
	virtual void PolledUpdate() override;
	virtual void Render() override;

	void RenderShapes(int _i, int _j);
	void RenderText();
	void UpdateText();
	void Initnodes();
	void InitShapes(int _i, int _j);

	void CalculatePath(node& _destination);
	void AStarTraversal(node& _source, node& _destination);

	void CalculateNeighbors(int _i, int _j, int _offsetI, int _offsetJ, node& _destination, bool& _reachedDestination, std::set<std::pair<int, std::pair<int, int>>>& _openList, bool m_ClosedList[SIZE][SIZE]);

	void ToggleDebug();

	sf::Vector2i GetMousedOverTile(sf::Vector2f _mousePos);
	void ChangeTileColour(sf::Vector2i _index);

	node m_nodes[SIZE][SIZE]{};
protected:

	inline int CalculateHValue(std::pair<int, int> _node, std::pair<int, int> _destination)
	{
		int dx = _node.first - _destination.first;
		int dy = _node.second - _destination.second;

		int h = abs(dx) + abs(dy);
		
		return  h;
	}

	inline bool IsValid(int _i , int _j)
	{
		if (_i >= 0 && _j >= 0 && _i < SIZE && _j < SIZE)
		{
			return true;
		}
		return false;
	}

	inline bool IsBlocked(std::pair<int, int> _position)
	{
		if (m_nodes[_position.first][_position.second].m_bObstical == true)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}

	inline bool IsDestination(std::pair<int, int> _position, std::pair<int, int> _destination)
	{
		if (_position.first == _destination.first && _position.second == _destination.second)
			return (true);
		else
			return (false);
	}

	bool m_bDebug = false;

	sf::RectangleShape m_Shapes[SIZE][SIZE];

	std::stack<std::pair<int, int>> path;

	sf::Font m_Font;
	sf::RenderWindow* m_RenderWindow = nullptr;

	int bestMove = 8000;
	int previousMove = 7000;
};

