#include "CGraph.h"

void CGraph::AddEdge(int _pos, int _value)
{
	m_AdjacentNodes[_pos].push_back(_value);
}

void CGraph::DFS(int _pos)
{
	m_TraversedNodes[_pos] = true;
	std::cout << (char)(_pos + ASCIIOFFSET);
	//std::cout << _pos;

	for (auto& item : m_AdjacentNodes[_pos])
	{
		if (m_TraversedNodes[item] == false)
		{
			DFS(item);
		}
	}
}

void CGraph::DFS()
{
	for (auto& item : m_AdjacentNodes)
	{
		if (m_TraversedNodes[item.first] == false)
		{
			DFS(item.first);
		}
	}
}

void CGraph::BFS(int _pos)
{
	std::queue<int> bfsQueue;

	m_TraversedNodes[_pos] = true;
	bfsQueue.push(_pos);
	int m_TraversedNode = 0;
	while (bfsQueue.empty() == false)
	{
		m_TraversedNode = bfsQueue.front();
		std::cout << (char)(m_TraversedNode + ASCIIOFFSET);
		//std::cout << m_TraversedNode;
		bfsQueue.pop();

		for (auto& item : m_AdjacentNodes[m_TraversedNode])
		{
			if (!m_TraversedNodes[item])
			{
				m_TraversedNodes[item] = true;
				bfsQueue.push(item);
			}
		}
	}
}

void CGraph::BFS()
{
	for (auto& item : m_AdjacentNodes)
	{
		if (m_TraversedNodes[item.first] == false)
		{
			BFS(item.first);
		}
	}
}

void CGraph::CleanupMaps()
{
	m_TraversedNodes.clear();
	for (auto& item : m_AdjacentNodes)
	{
		m_AdjacentNodes[item.first].clear();
	}
	m_AdjacentNodes.clear();
}
