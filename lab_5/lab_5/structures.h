#pragma once
class Point
{
public:
	float x;
	float y;
};

class Rect 
{
public:
	float x1;
	float y1;
	float x2;
	float y2;
};

class Path
{
public:
	Point lineP1;
	Point lineP2;
	int turnDirection;
	int movingDirection;
};