
#include "Bresenham.h"
Bresenham::Bresenham()
{

}
void Bresenham::bresenham(int xa, int ya, int xb, int yb, SDL_Renderer* gRenderer)
{
	int signx;
	int signy;
	int x;
	int y;
	int i;
	int p;

	x = xa;
	y = ya;

	int dx = xb - xa;
	int dy = yb - ya;

	if (dx >= 0) {
		signx = +1;
	}
	else {
		signx = -1;
	}
	if (dy >= 0) {
		signy = 1;
	}
	else {
		signy = -1;
	}
	SDL_SetRenderDrawColor(gRenderer, 0x23, 0x54, 0x66, 0xFF);
	if (x == xb)
	{
		SDL_RenderDrawLine(gRenderer, x, y, xb, yb);
	}
	if (abs(dy) <= abs(dx)) {

		p = 2 * dy * signy - dx * signx;
		for (i = 0; i <= dx * signx; i++)
		{
			SDL_RenderDrawPoint(gRenderer, x, y);
			if (p < 0) {

				x = x + signx;
				y = y;
				p = p + signy * 2 * dy;
			}
			else {

				x = x + signx;
				y = y + signy;
				p = p + 2 * dy * signy - 2 * dx * signx;
			}
		}
	}
	else if (abs(dy) > abs(dx)) {

		p = signx * 2 * dx - signy * dy;
		i = 0;

		for (i = 0; i <= dy * signy; i++)
		{
			SDL_RenderDrawPoint(gRenderer, x, y);
			if (p < 0)
			{
				x = x;
				y = y + signy;
				p = p + signx * 2 * dx;
			}
			else
			{
				x = x + signx;
				y = y + signy;
				p = p + signx * 2 * dx - signy * 2 * dy;
			}
		}
	}

	SDL_SetRenderDrawColor(gRenderer, 0x57, 0xFF, 0xFF, 0xFF);
}

void Bresenham::DrawLine4(Vector2 v1, Vector2 v2, SDL_Renderer* gRenderer)
{
	bresenham(v1.getX(), v1.getY(), v2.getX(), v2.getY(), gRenderer);
}

void Bresenham::Poly(const std::vector<Vector2>& vertex, SDL_Renderer* gRenderer)
{
	for (auto it = vertex.begin(); it != vertex.end(); it++)
	{
		if (it + 1 != vertex.end())
		{
			DrawLine4(*it, *(it + 1), gRenderer);
		}
		else if (it + 1 == vertex.end())
		{
			DrawLine4(*it, vertex.front(), gRenderer);
		}
	}
}
