//
// GROButton.cpp for  in /home/elliott/rendu/gomoku/GUI
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Wed Nov  4 18:18:32 2015 Elliott
// Last update Wed Nov  4 21:39:16 2015 Elliott
//

#include	<SDL2/SDL.h>
#include	"GROButton.hh"

GROButton::GROButton(void) : AGRenderObject()
{
  this->surf = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
  SDL_FillRect(this->surf, NULL, SDL_MapRGB(this->surf->format, 255, 0, 0));
}

GROButton::GROButton(Uint32 _col, Uint32 _row) : AGRenderObject(_col, _row)
{
  this->surf = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
  SDL_FillRect(this->surf, NULL, SDL_MapRGB(this->surf->format, 255, 0, 0));
}

GROButton::~GROButton(void)
{
  SDL_FreeSurface(this->surf);
}

SDL_Surface*	GROButton::render(void)
{
  return (this->surf);
}
