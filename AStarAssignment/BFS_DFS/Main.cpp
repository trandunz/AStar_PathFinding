#include "CGraph.h"

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8

std::string RemoveLastChar(std::string _string);
void GrabEdgeValues();
void GrabNodes();
void GrabEdgeCount();
void PrintNodes();
void PrintNumberOfEdges();
void PrintEdges();
void ProcessEdgeInputsIntoGraph(CGraph& _graph);
bool IsInputInNodes();

char m_Input = 0;
std::vector<char> m_Nodes;
std::vector<std::pair<char, char>> m_Edges;
std::string m_InputString = "";
int m_EdgeCount = 0;

int main()
{
	CGraph m_Graph;
	m_Graph.AddEdge(A, B);
	m_Graph.AddEdge(A, I);
	m_Graph.AddEdge(B, F);
	m_Graph.AddEdge(C, D);
	m_Graph.AddEdge(C, H);
	m_Graph.AddEdge(C, G);
	m_Graph.AddEdge(E, F);
	m_Graph.AddEdge(E, I);
	m_Graph.AddEdge(F, G);
	m_Graph.AddEdge(F, I);
	m_Graph.AddEdge(G, H);

	m_Graph.BFS();

	/*GrabNodes();
	GrabEdgeCount();
	GrabEdgeValues();
	ProcessEdgeInputsIntoGraph(m_Graph);
	
	std::cout << "The DFS sequence in the graph - ";
	m_Graph.DFS();

	m_Graph.CleanupMaps();
	ProcessEdgeInputsIntoGraph(m_Graph);
	std::cout << std::endl << "The BFS sequence in the graph - ";
	m_Graph.BFS();*/


	return NULL;
}

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

void GrabEdgeValues()
{
	m_Input = 0;

	for (int i = 0; i < m_EdgeCount; i++)
	{
		m_Edges.push_back(std::make_pair(0, 0));
	}

	for (int i = 0; i < m_EdgeCount; i++)
	{
		m_Input = 0;
		std::cout << "Edge " << i + 1 << ": ";
		while (IsInputInNodes() == false)
		{
			m_Input = _getch();
		}
		m_Edges[i].first = m_Input;
		std::cout << m_Edges[i].first << ",";
		m_Input = 0;
		while (IsInputInNodes() == false)
		{
			m_Input = _getch();
		}
		m_Edges[i].second = m_Input;
		
		std::cout << m_Edges[i].second << std::endl;
	}
}

void GrabNodes()
{
	m_Input = 0;
	std::cout << "Nodes: ";
	while (m_Input != 13)
	{
		m_Input = _getch();
		if ((m_Input >= 65 && m_Input <= 90) || (m_Input >= 97 && m_Input <= 122))
		{
			m_Nodes.push_back(m_Input);
			std::cout << m_Nodes.back() << ", ";
		}

		if (m_Input == 13 && m_Nodes.size() == 0)
		{
			m_Input = 0;
		}
	}
	std::cout << std::endl;
}

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
			RemoveLastChar(m_InputString);
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

void PrintNodes()
{
	std::cout << "Nodes: ";
	for (auto& item : m_Nodes)
	{
		if (item == *m_Nodes.end())
		{
			std::cout << item << std::endl;
		}
		else
		{
			std::cout << item << ", ";
		}
	}
	std::cout << std::endl;
}

void PrintNumberOfEdges()
{
	std::cout << "Number Of Edges: " << m_EdgeCount << std::endl;
}

void PrintEdges()
{
	int it = 1;
	for (auto& item : m_Edges)
	{
		std::cout << "Edge " << it << ": " << item.first << "," << item.second << std::endl;
		it++;
	}
}

void ProcessEdgeInputsIntoGraph(CGraph& _graph)
{
	for (auto& item : m_Edges)
	{
		_graph.AddEdge((int)item.first - ASCIIOFFSET, (int)item.second - ASCIIOFFSET);
	}
}

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
