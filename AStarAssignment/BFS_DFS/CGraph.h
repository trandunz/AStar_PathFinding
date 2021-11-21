//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CGraph.h
// Description : CGraph Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#include "NumptyBehavior.h"

class CGraph
{
public:
    inline CGraph(std::vector<NumptyBehavior::Edge>& _edges, int _numberOfNodes)
    {
        m_AdjacentNodes.resize(_numberOfNodes);

        for (auto& item : _edges)
        {
            m_AdjacentNodes[item.m_Parent].emplace_back(item.m_Child);
            m_AdjacentNodes[item.m_Child].emplace_back(item.m_Parent);
        }
    }


    inline void DFS(int _currentNode, std::vector<bool>& _traversed)
    {
        _traversed[_currentNode] = true;
        if (!IsNodeSingular(_currentNode))
        {
            std::cout << (char)(_currentNode + ASCIIOFFSET);
        }

        for (auto& item : m_AdjacentNodes[_currentNode])
        {
            if (_traversed[item] == false)
            {
                DFS(item, _traversed);
            }
        }
    }

    inline void BFS(std::queue<int>& _bfsQueue, std::vector<bool>& _traversed)
    {
        if (_bfsQueue.empty())
        {
            return;
        }

        int currentNode = _bfsQueue.front();
        _bfsQueue.pop();
        
        if (!IsNodeSingular(currentNode))
        {
            std::cout << (char)(currentNode + ASCIIOFFSET);
        }

        for (auto& item : m_AdjacentNodes[currentNode])
        {
            if (_traversed[item] == false)
            {
                _traversed[item] = true;
                _bfsQueue.push(item);
            }
        }

        BFS(_bfsQueue, _traversed);
    }

private:
    inline bool IsNodeSingular(int _node)
    {
        for (int i = 0; i < m_AdjacentNodes.size(); i++)
        {
            for (auto& item : m_AdjacentNodes[i])
            {
                if (item == _node)
                {
                    return false;
                }
            }
        }
        return true;
    }

    std::vector<std::vector<int>> m_AdjacentNodes;
};
