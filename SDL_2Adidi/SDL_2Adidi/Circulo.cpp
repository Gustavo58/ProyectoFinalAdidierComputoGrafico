
#include "Circulo.h"
Circulo::Circulo()
{

}

void Circulo::Circle(int r, int xc, int yc, SDL_Renderer* gRenderer)
{
	int p, x, y;
	p = 1 - r;
	x = 0;
	y = r;
	
	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0x00, 0x98, 0xFF);
	for (; x <= y;)
	{
		if (p <= 0)
		{
			x = x + 1;
			y = y;
			p = p + (4 * x) + 6;
		}
		else
		{
			x = x + 1;
			y = y - 1;
			p = p + 4 * (x - y) + 10;
		}
		SDL_RenderDrawPoint(gRenderer, x + xc, y + yc);
		SDL_RenderDrawPoint(gRenderer, -x + xc, y + yc);
		SDL_RenderDrawPoint(gRenderer, -x + xc, -y + yc);
		SDL_RenderDrawPoint(gRenderer, x + xc, -y + yc);
		SDL_RenderDrawPoint(gRenderer, y + xc, x + yc);
		SDL_RenderDrawPoint(gRenderer, -y + xc, x + yc);
		SDL_RenderDrawPoint(gRenderer, -y + xc, -x + yc);
		SDL_RenderDrawPoint(gRenderer, y + xc, -x + yc);


	}
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

}
