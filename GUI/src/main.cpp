//
// main.cpp for  in /home/elliott/rendu/gomoku/GUI
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Tue Oct 13 13:26:35 2015 Elliott
// Last update Tue Oct 13 17:57:58 2015 Elliott
//

#include	<iostream>
#include	<SDL2/SDL.h>

void		print_button(SDL_Surface *dest)
{
  SDL_Surface	*surface;
  SDL_Rect	src_rec;
  SDL_Rect	dest_rec;

  if (dest == NULL)
    std::cerr << "no surface to copy." << std::endl;
  surface = SDL_LoadBMP("img/jouer.bmp");
  if (surface == NULL)
    std::cerr << "load img failed." << std::endl;
  src_rec.x = 0;
  src_rec.y = 0;
  src_rec.h = 128;
  src_rec.w = 128;
  dest_rec.x = 50;
  dest_rec.y = 150;
  dest_rec.h = 32;
  dest_rec.w = 32;
  SDL_BlitScaled(surface, &src_rec, dest, &dest_rec);
}

int		create_win(void)
{
  SDL_Window	*win;
  SDL_Renderer	*render;
  bool		end = false;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "Couldn't init SDL." << std::endl;
      return (1);
    }

  win = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 400, SDL_WINDOW_OPENGL);

  if (win == NULL)
    {
      std::cerr << "Couldn't create window." << std::endl;
      SDL_Quit();
      return (1);
    }

  render = SDL_CreateRenderer(win, -1, 0);
  SDL_SetRenderDrawColor(render, 0, 0, 0, 1);
  SDL_RenderClear(render);
  print_button(SDL_GetWindowSurface(win));
  SDL_UpdateWindowSurface(win);

  while (!end)
    {
      SDL_Event event;
      SDL_WaitEvent(&event);
      if (event.type != SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_ESCAPE)
	    end = true;
	}
    }

  SDL_DestroyWindow(win);
  SDL_Quit();
  return (0);
}

int		main(void)
{
  create_win();
  return (0);
}
