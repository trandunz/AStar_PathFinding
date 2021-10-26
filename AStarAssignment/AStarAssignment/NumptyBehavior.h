#pragma once

#ifndef _NUMPTYBEHAVIOR_
#define _NUMPTYBEHAVIOR_

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <SFML/Graphics.hpp>
#include <string>
#include <stack>
#include <set>

class NumptyBehavior
{
public:
	struct Vector2
	{
		float x = 0;
		float y = 0;
	};

	virtual void Start() {}
	virtual void Update() {}
	virtual void PolledUpdate() {}
	virtual void Render() {}

	static inline float Mag(Vector2 _vec1, Vector2 _vec2)
	{
		float dx = _vec2.x - _vec1.x;
		float dy = _vec2.y - _vec1.y;

		return sqrt((dx * dx) + (dy * dy));
	}

	template <typename A>
	static inline void DeletePointer(A* _pointer)
	{
		if (_pointer != nullptr)
		{
			delete _pointer;
		}
	}

	static inline sf::Font& LoadFont(sf::Font& _font, std::string _path)
	{
		_font.loadFromFile(_path);
		return _font;
	}

	static inline void LoadTextWithFont(sf::Text& _text, sf::Font& _font, sf::Color _colour = sf::Color::White, unsigned _characterSize = 12)
	{
		_text.setFont(_font);
		_text.setCharacterSize(_characterSize);
		_text.setFillColor(_colour);
	}
};
#endif
