//
// main.cpp for  in /home/elliott/rendu/gomoku/GUI
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Tue Oct 13 13:26:35 2015 Elliott
// Last update Tue Oct 13 14:41:02 2015 Elliott
//

#include	<iostream>
#include	<SDL2/SDL.h>

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

  win = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

  if (win == NULL)
    {
      std::cerr << "Couldn't create window." << std::endl;
      SDL_Quit();
      return (1);
    }

  render = SDL_CreateRenderer(win, -1, 0);
  SDL_SetRenderDrawColor(render, 0, 0, 0, 1);
  SDL_RenderClear(render);
  SDL_RenderPresent(render);

  while (!end)
    {
      SDL_Event event;
      if (SDL_WaitEvent(NULL) && SDL_HasEvent(SDL_KEYDOWN) == true)
	{
	  while (SDL_PollEvent(&event))
	    {
	      if (event.key.keysym.sym == SDLK_ESCAPE)
		end = true;
	    }
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
