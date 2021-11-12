#pragma once
#include "NumptyBehavior.h"

class CGraph : public NumptyBehavior
{
public:
	void AddEdge(int _pos, int _value);
	void DFS(int _pos);
	void DFS();
	void BFS(int _pos);
	void BFS();
	void CleanupMaps();

private:
	std::map<int, bool> m_TraversedNodes{};
	std::map<int, std::vector<int>> m_AdjacentNodes{};
};

