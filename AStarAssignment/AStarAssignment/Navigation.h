#pragma once

#include "NumptyBehavior.h"

#define NODE_DIFFERENCE 10
#define SIZE 40

#include "node.h"

class Navigation : public NumptyBehavior
{
public:
	Navigation(sf::RenderWindow* _renderWindow);
	~Navigation();

	virtual void Start() override;
	virtual void Update(sf::Vector2f _mouserPos);
	virtual void PolledUpdate(sf::Event* _event, sf::Vector2f _mouserPos);
	virtual void Render() override;

	void RenderShapes(int _i, int _j);
	void RenderText();
	void UpdateText();
	void Initnodes();
	void InitShapes(int _i, int _j);

	void CalculatePath(Node& _destination);
	void AStarTraversal(Node& _source, Node& _destination);

	void CalculateNeighbors(int _i, int _j, int _offsetI, int _offsetJ, Node& _destination, bool& _reachedDestination, std::set<std::pair<int, std::pair<int, int>>>& _openList, bool m_ClosedList[SIZE][SIZE]);

	void ToggleDebug();

	bool IsMouseOverTile(sf::Vector2f _mousePos);
	sf::Vector2i GetMousedOverTile(sf::Vector2f _mousePos);
	void ChangeTileType(sf::Vector2i _index);

	Node& GetSourceNode();
	Node& GetDestinationNode();

	void CleanupContainers();

	void SetNodeColourToType(int _i, int _j);
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
		if (m_Nodes[_position.first][_position.second].m_bObstical == true)
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

	Node m_Nodes[SIZE][SIZE]{};
	std::stack<std::pair<int, int>> m_Path;
	sf::RectangleShape m_Shapes[SIZE][SIZE];
	bool m_ClosedList[SIZE][SIZE];

	bool m_bDebug = false;
	bool m_bEraser = false;

	sf::Font m_Font;
	sf::RenderWindow* m_RenderWindow = nullptr;

	int bestMove = 8000;
	int previousMove = 7000;

	Node* m_SourceNode = nullptr;
	Node* m_DestinationNode = nullptr;
};

