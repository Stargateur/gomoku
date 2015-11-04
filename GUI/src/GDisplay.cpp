//
// GDisplay.cpp for  in /home/elliott/rendu/gomoku/GUI/include
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Wed Oct 14 17:34:02 2015 Elliott
// Last update Wed Nov  4 22:08:33 2015 Elliott
//

#include	<stdexcept>
#include	"GDisplay.hh"
#include	<iostream>

GDisplay::GDisplay() : win(NULL), renderer(NULL), surface(NULL), grid_col(12), grid_row(12)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    throw new std::runtime_error("Failed init SDL");
}

GDisplay::~GDisplay(void)
{
  if (win != NULL)
    SDL_DestroyWindow(win);
  SDL_Quit();
}

void		GDisplay::calculate_grid(void)
{
  this->cell_w = SDL_GetWindowSurface(this->win)->w / this->grid_col;
  this->cell_h = SDL_GetWindowSurface(this->win)->h / this->grid_row;
}

bool		GDisplay::set_grid(Uint32 _grid_col, Uint32 _grid_row)
{
  if (_grid_col < 1 || _grid_row < 1)
    return (false);
  if (_grid_col > 15 || _grid_row > 15)
    return (false);
  this->grid_col = _grid_col;
  this->grid_row = _grid_row;
  this->calculate_grid();
  return (true);
}

SDL_Window	*GDisplay::create_win(std::string _title, Uint32 _h, Uint32 _w)
{
  Uint32	flags;

  flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
  if (_h < 1 || _w < 1)
    flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
  this->win = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _h, _w, flags);
  return (this->win);
}

SDL_Window	*GDisplay::create_win(std::string _title, Uint32 _h, Uint32 _w, Uint32 _grid_x, Uint32 _grid_y)
{
  this->create_win(_title, _h, _w);
  this->set_grid(_grid_x, _grid_y);
  return (this->win);
}

bool		GDisplay::resolve_events(void)
{
  SDL_Event	event;
  t_reg_event	ev;

  while (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_KEYDOWN)
	{
	  if (this->bounded_keys.find(event.key.keysym.sym) != this->bounded_keys.end())
	    {
	      ev = this->bounded_keys[event.key.keysym.sym];
	      (*ev.func)(ev.user);
	    }
	}
      else if (event.type == SDL_WINDOWEVENT)
	{
	  if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	    this->calculate_grid();
	}
    }
  return (true);
}

bool		GDisplay::draw(GROButton *btn)
{
  SDL_Surface	*tmp;
  SDL_Rect	src_rec;
  SDL_Rect	dest_rec;

  tmp = btn->render();
  src_rec.x = 0;
  src_rec.y = 0;
  src_rec.h = tmp->h;
  src_rec.w = tmp->w;
  dest_rec.x = 0 + cell_w * (btn->getCol() - 1);
  dest_rec.y = 0 + cell_h * (btn->getRow() - 1);
  dest_rec.h = this->cell_h;
  dest_rec.w = this->cell_w;
  SDL_BlitScaled(tmp, &src_rec, SDL_GetWindowSurface(this->win), &dest_rec);
  SDL_UpdateWindowSurface(this->win);
  return (true);
}

bool		GDisplay::register_key(SDL_Keycode _keycode, void (*_func)(void *), void *_user)
{
  t_reg_event	ev;

  ev.func = _func;
  ev.user = _user;
  this->bounded_keys[_keycode] = ev;
  return (true);
}
