#pragma once
#include "SDL.h"
#include "Vector2.h"
class CurvaBezier
{
private: 

	float x, y;
public:
	CurvaBezier();
	CurvaBezier(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, SDL_Renderer* gRenderer);
	//void BezierCurve(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4);
};
