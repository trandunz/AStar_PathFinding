#pragma once
#include "NumptyBehavior.h"
class node : public NumptyBehavior
{
public:
	std::pair<int, int> m_Position{ 0 , 100 };

	int F = INT_MAX;
	int G = INT_MAX;
	int H = INT_MAX;

	std::pair<int, int> m_Parent{-1,-1};

	sf::Text m_FText;
	sf::Text m_GText;
	sf::Text m_HText;

	bool m_bObstical = false;
	bool m_bTraversed = false;
};

