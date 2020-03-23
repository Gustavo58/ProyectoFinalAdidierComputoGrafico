
#include <SDL.h>
#include <iostream>
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
#include "Vector2.h"
#include <list>
#include <time.h>
#include "CurvaBezier.h"
#include"Bresenham.h"
#include"Circulo.h"
using namespace std;

//Screen dimension constants
int SCREEN_WIDTH = 720;
int SCREEN_HEIGHT = 480;
int tam = 30;

//Starts up SDL and creates window
bool init();


//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
Bresenham* bresenham = new Bresenham();
Circulo* circulo = new Circulo();

bool init()
{
    //Initialization flag
    bool success = true;


    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);


            }
        }
    }

    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;


    SDL_Quit();
}

void SetScreen()
{
    if (SCREEN_WIDTH == 0 || SCREEN_HEIGHT == 0)
    {
        SCREEN_WIDTH = 720;
        SCREEN_HEIGHT = 480;
    }
    if (tam == 0)
    {
        tam = 32;
    }
}

void DrawPlain()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Dibujamos en y desde la mitad
    SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    for (int i = SCREEN_HEIGHT / 2; i < SCREEN_HEIGHT;)
    {
        i += tam;
        SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT - i);
        SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
    }

    //Dibujamos en x desde la mitad
    for (int i = SCREEN_WIDTH / 2; i < SCREEN_WIDTH;)
    {
        i += tam;
        SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH - i, SCREEN_HEIGHT / 2);
        SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT / 2);
    }

    SDL_SetRenderDrawColor(gRenderer, 0x44, 0x44, 0x44, 0xFF);
    for (int i = (SCREEN_WIDTH / 2) + tam; i < SCREEN_WIDTH; i += tam)
    {
        for (int j = (SCREEN_HEIGHT / 2) + tam; j < SCREEN_HEIGHT; j += tam)
        {
            SDL_RenderDrawPoint(gRenderer, i, j);
            SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH - i, j);
            SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH - i, SCREEN_HEIGHT - j);
            SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT - j);
        }
    }


}



int main(int argc, char* args[])
{
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    bool drawing = false;

    struct Line
    {
        int x1;
        int y1;
        int x2;
        int y2;
    };
    struct Circles
    {
        int x1;
        int y1;
        int x2;
        int y2;
    };
    struct Curves
    {
        int x1;
        int y1;
        int x2;
        int y2;
    };
   
    list<Curves>curves;
    list<Circles>circles;
    list<Line>lines;

    SetScreen();
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        bool quit = false;
        bool Linea1 = false;
        bool Curva1 = false;
        bool Ciruclo1 = false;
		bool Color1 = false;

       
        SDL_Event e;

      
		while (!quit)
		{
			
			while (SDL_PollEvent(&e) != 0)
			{

				switch (e.type)
				{
				case SDL_MOUSEBUTTONDOWN:
					switch (e.button.button)
					{
					case SDL_BUTTON_LEFT:
						x1 = e.motion.x;
						y1 = e.motion.y;
						x2 = e.motion.x;
						y2 = e.motion.y;
						drawing = true;
						break;

					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch (e.button.button)
					{
					case SDL_BUTTON_LEFT:
						drawing = false;
						Line line = { x1, y1, x2, y2 };
						Circles circle = { x1,y1,x2,y2 };
						Curves curve = { x1,y1,x2,y2 };
						circles.push_back(circle);
						curves.push_back(curve);
						lines.push_back(line);
						break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (drawing)
					{
						x2 = e.motion.x;
						y2 = e.motion.y;
					}


					break;



				case SDL_QUIT:
					quit = true;
					break;
					// TODO input handling code goes here
				}
			}

			if (e.motion.x >= 0 && e.motion.x <= 15 && e.motion.y >= 0 && e.motion.y <= 15)
			{
				Linea1 = true;
				Curva1 = false;
				Ciruclo1 = false;
				Color1 = false;
			}
			if (e.motion.x >= 0 && e.motion.x <= 15 && e.motion.y >= 465 && e.motion.y <= 480)
			{
				Linea1 = false;
				Curva1 = true;
				Ciruclo1 = false;
				Color1 = false;
			}
			if (e.motion.x >= 0 && e.motion.x <= 15 && e.motion.y >= 225 && e.motion.y <= 240)
			{
				Linea1 = false;
				Curva1 = false;
				Ciruclo1 = true;
				Color1 = false;
			}
			if (e.motion.x >= 0 && e.motion.x <= 15 && e.motion.y >= 300 && e.motion.y <= 300) {
				Linea1 = false;
				Curva1 = false;
				Ciruclo1 = false;
				Color1 = true;
			}

			SDL_RenderClear(gRenderer);
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xF6, 0xFF);
			DrawPlain();
			SDL_SetRenderDrawColor(gRenderer, 128, 128, 128, 255);
			if (Linea1 == true)
			{
				for (std::list<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i)
				{
					Line line = *i;
					bresenham->bresenham(x1, y1, x2, y2, gRenderer);
				}
			}
			if (Curva1 == true)
			{
				for (std::list<Circles>::const_iterator i = circles.begin(); i != circles.end(); ++i)
				{
					Circles circles = *i;
					circulo->Circle(x2 - x1, x1, y1,gRenderer);
				}
			}
			if (Ciruclo1 == true)
			{
				for (std::list<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i)
				{
					Line line = *i;
					CurvaBezier(Vector2(x1, y1), Vector2(x2, y2), Vector2(0, 0), Vector2(0, 0), gRenderer);
				}
			}
			if (Color1 == true) 
			{
				SDL_RenderClear(gRenderer);
			}
			std::vector<Vector2> a = std::vector<Vector2>(4);
            a[0] = Vector2(0,480);
            a[1] = Vector2(15,480);
            a[2] = Vector2(15,465);
            a[3] = Vector2(0, 465);

            std::vector<Vector2> e = std::vector<Vector2>(4);            
            e[0] = Vector2(0, 0);
            e[1] = Vector2(0, 15);
            e[2] = Vector2(15, 15);
            e[3] = Vector2(15, 0);

            std::vector<Vector2> d = std::vector<Vector2>(4);
            d[0] = Vector2(0, 240);
            d[1] = Vector2(15, 240);
            d[2] = Vector2(15, 225);
            d[3] = Vector2(0, 225);

			std::vector<Vector2> w = std::vector<Vector2>(4);
            w[0] = Vector2(0, 290);
            w[1] = Vector2(15, 290);
            w[2] = Vector2(15, 330);
            w[3] = Vector2(0, 330);

			bresenham->Poly(e,gRenderer);
            bresenham->Poly(a,gRenderer);
            bresenham->Poly(d,gRenderer);
			bresenham->Poly(w,gRenderer);
            SDL_RenderPresent(gRenderer);
        }
    }
    close();
    return 0;
}