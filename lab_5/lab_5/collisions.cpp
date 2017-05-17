#include "collisions.h"
#include "structures.h"

bool Collisions::RectCollision(Rect rect1, Rect rect2)
{
	if (rect1.x1 < rect2.x2 && rect1.x2 > rect2.x1 &&
		rect1.y1 > rect2.y2 && rect1.y2 < rect2.y1)
	{
		return true;
	}
	return false;
}
