#include "Vector2.h"
#include<vector>
#include"SDL.h"
class Bresenham
{
public:
	Bresenham();
	 void bresenham(int xa, int ya, int xb, int yb, SDL_Renderer* gRenderer);
	 void DrawLine4(Vector2 v1, Vector2 v2,SDL_Renderer* gRenderer);
	 void Poly(const std::vector<Vector2>& vertex, SDL_Renderer* gRenderer);
private:
};
