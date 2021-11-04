#pragma once
#include "NumptyBehavior.h"
typedef std::pair<int, bool> intboolPair;
class Graph : public NumptyBehavior
{
public:
	Graph();
	~Graph();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	void AddEdge(int _i, int _j);
	void DFS();
	void BFS();

private:
	std::map<int, bool> m_TraversedNodes{};
	std::map<int, std::vector<int>> m_AdjacentNodes{};
};

