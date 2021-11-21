//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Main.cpp
// Description : Main Implementation file for BFS/DFS Search On An Undirected Graph.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#include "CGraph.h"

std::string RemoveLastChar(std::string _string);
void GrabEdgeValues();
void GrabNodes();
void GrabEdgeCount();
void PrintNodes(bool _endl = true);
void PrintNumberOfEdges();
void PrintEdges();
void ProcessEdgeInputsIntoGraph();
bool IsInputInNodes();
void DFS();
void BFS();

char m_Input = 0;
std::vector<char> m_Nodes;
std::vector<std::pair<char, char>> m_EdgeInputs;
std::string m_InputString = "";
int m_EdgeCount = 0;
std::vector<NumptyBehavior::Edge> m_Edges;

/// <summary>
/// Main Implementation Function For BFS/DFS
/// </summary>
int main()
{
	GrabNodes();
	GrabEdgeCount();
	GrabEdgeValues();
	ProcessEdgeInputsIntoGraph();

	std::cout << "The DFS sequence in the graph - ";
	DFS();
	std::cout << std::endl;
	std::cout << "The BFS sequence in the graph - ";
	BFS();
	std::cout << std::endl;

	/// Halts Program To See Results When Running In Release Build
	_getch();

	// Main Returns 0
	return NULL;
}

/// <summary>
/// Removes The Last Character From The Given String
/// </summary>
std::string RemoveLastChar(std::string _string)
{
	// String Is Empty Check
	if (_string == "" || _string.length() == 0)
	{
		return _string;
	}

	// Return String Minus Last Character
	return _string.std::string::substr(0, _string.length() - 1);
}

/// <summary>
/// Grabs The Edge Values Via The _getch Function And Adds Them To The m_EdgeInputs Vector
/// </summary>
void GrabEdgeValues()
{
	m_Input = 0;
	for (int i = 0; i < m_EdgeCount; i++)
	{
		m_EdgeInputs.push_back(std::make_pair(0, 0));
	}

	for (int i = 0; i < m_EdgeCount; i++)
	{
		// First Node
		m_Input = 0;
		std::cout << "Edge " << i + 1 << ": ";
		while (IsInputInNodes() == false)
		{
			m_Input = _getch();
			m_Input = std::toupper(m_Input);
		}
		m_EdgeInputs[i].first = m_Input;
		std::cout << m_EdgeInputs[i].first << ",";

		// Second Node
		m_Input = 0;
		while (IsInputInNodes() == false)
		{
			m_Input = _getch();
			m_Input = std::toupper(m_Input);
		}
		m_EdgeInputs[i].second = m_Input;
		std::cout << m_EdgeInputs[i].second << std::endl;
	}
}

/// <summary>
/// Grabs The Node Values Via The _getch Function And Adds Them To The m_Nodes Vector
/// </summary>
/// <param name="_endl"></param>
void GrabNodes()
{
	m_Input = 0;
	std::cout << "Nodes: ";
	while (m_Input != 13)
	{
		m_Input = _getch();
		if (m_Input >= 97 && m_Input <= 122)
		{
			// Lower ? convert to upper
			m_Nodes.push_back(std::toupper(m_Input));
			system("cls");
			PrintNodes(false);
		}
		else if (m_Input >= 65 && m_Input <= 90)
		{
			m_Nodes.push_back(m_Input);
			system("cls");
			PrintNodes(false);
		}
		else if (m_Input == 8)
		{
			if (m_Nodes.size() > 0)
			{
				m_Nodes.pop_back();
				system("cls");
				PrintNodes(false);
			}
		}

		if (m_Input == 13 && m_Nodes.size() == 0)
		{
			m_Input = 0;
		}
	}
	std::cout << std::endl;
}

/// <summary>
/// Grabs The Edges Count Value Via The _getch Function And Assigns It To m_EdgeCount
/// </summary>
/// <returns></returns>
void GrabEdgeCount() 
{
	m_Input = 0;
	m_InputString = "";
	std::cout << "Number Of Edges: ";
	while (m_Input != 13)
	{
		m_Input = _getch();
		if (m_Input >= 48 && m_Input <= 57)
		{
			m_InputString += m_Input;
		}
		else if (m_Input == 8)
		{
			m_InputString = RemoveLastChar(m_InputString);
		}

		system("cls");
		PrintNodes();
		std::cout << "Number Of Edges: ";
		std::cout << m_InputString;

		if (m_Input == 13 && m_InputString == "")
		{
			m_Input = 0;
		}
	}
	if (m_InputString != "")
	{
		m_EdgeCount = std::stoi(m_InputString);
	}

	std::cout << std::endl;
}

/// <summary>
/// Prints All The Nodes
/// </summary>
void PrintNodes(bool _endl)
{
	std::cout << "Nodes: ";

	if (m_Nodes.size() > 0)
	{
		std::vector<char>::iterator item = m_Nodes.begin();
		std::cout << *item;
		item++;
		for (item; item != m_Nodes.end(); item++)
		{
			std::cout << "," << *item;
		}
	}

	if (_endl)
	{
		std::cout << std::endl;
	}
}

/// <summary>
/// Prints The Number Of Edges
/// </summary>
void PrintNumberOfEdges()
{
	std::cout << "Number Of Edges: " << m_EdgeCount << std::endl;
}

/// <summary>
/// Prints The Edge Values
/// </summary>
void PrintEdges()
{
	int it = 1;
	for (auto& item : m_EdgeInputs)
	{
		std::cout << "Edge " << it << ": " << item.first << "," << item.second << std::endl;
		it++;
	}
}

/// <summary>
/// Processes m_EdgeInputs Into The Graph
/// </summary>
void ProcessEdgeInputsIntoGraph()
{
	m_Edges.clear();
	for (auto& item : m_EdgeInputs)
	{
		m_Edges.push_back({ (int)item.first - ASCIIOFFSET, (int)item.second - ASCIIOFFSET });
	}
}

/// <summary>
/// Returns A Bol Based On If A Given Input Is Of The Initial Nodes
/// </summary>
bool IsInputInNodes()
{
	for (auto& item : m_Nodes)
	{
		if (m_Input == item)
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// Handles The Recursive BFS For The Graph Created
/// </summary>
void BFS()
{
	CGraph graph(m_Edges, (int)m_Nodes.size());
	std::vector<bool> traversed;
	traversed.resize(m_Nodes.size());
	std::queue<int> bfsQueue;

	for (int i = 0; i < (int)m_Nodes.size(); i++)
	{
		if (traversed[i] == false)
		{
			traversed[i] = true;
			bfsQueue.push(i);

			graph.BFS(bfsQueue, traversed);
		}
	}
}

/// <summary>
/// Handles The Recursive DFS For The Graph Created
/// </summary>
void DFS()
{
	CGraph graph(m_Edges, (int)m_Nodes.size());
	std::vector<bool> traversed;
	traversed.resize(m_Nodes.size());

	for (int i = 0; i < (int)m_Nodes.size(); i++)
	{
		if (traversed[i] == false)
		{
			graph.DFS(i, traversed);
		}
	}
}
