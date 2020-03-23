
#include "CurvaBezier.h"
CurvaBezier::CurvaBezier()
{

}

CurvaBezier::CurvaBezier(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, SDL_Renderer* gRenderer) {

	Vector2 Vect = Vector2(x, y);
	for (float t = 0; t <= 1; t += .001)
	{
		x = pow(1 - t, 3) * v1.getX() + 3 * t * pow(1 - t, 2) * v2.getX() + 3 * pow(t, 2) * (1 - t) * v3.getX() + pow(t, 3) * v4.getX();
		y = pow(1 - t, 3) * v1.getY() + 3 * t * pow(1 - t, 2) * v2.getY() + 3 * pow(t, 2) * (1 - t) * v3.getY() + pow(t, 3) * v4.getY();
		SDL_RenderDrawPoint(gRenderer, x, y);
	}
	SDL_SetRenderDrawColor(gRenderer, 0x44, 0x44, 0x44, 0xFF);
}

