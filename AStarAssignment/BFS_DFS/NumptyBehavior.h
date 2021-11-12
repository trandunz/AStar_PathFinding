#pragma once

#ifndef _NUMPTYBEHAVIOR_
#define _NUMPTYBEHAVIOR_

#define ASCIIOFFSET 97

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <stack>
#include <set>
#include <conio.h>
#include <ctype.h>
#include <list>

class NumptyBehavior
{
public:
	typedef std::pair<int, int> Vector2;

	virtual void Start() {}
	virtual void Update() {}
	virtual void PolledUpdate() {}
	virtual void Render() {}

	static inline float Mag(Vector2 _vec1, Vector2 _vec2)
	{
		float dx = (float)(_vec2.first - _vec1.first);
		float dy = (float)(_vec2.second - _vec1.second);

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
};
#endif

