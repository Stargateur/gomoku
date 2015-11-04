//
// GDisplay.cpp for  in /home/elliott/rendu/gomoku/GUI/include
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Wed Oct 14 17:34:02 2015 Elliott
// Last update Wed Nov  4 15:32:01 2015 Elliott
//

#include	<stdexcept>
#include	"GDisplay.hh"

GDisplay::GDisplay() : win(NULL), renderer(NULL), surface(NULL), grid_x(12), grid_y(12)
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

bool		GDisplay::set_grid(Uint32 _grid_x, Uint32 _grid_y)
{
  if (_grid_x < 1 || _grid_y < 1)
    return (false);
  if (_grid_x > 15 || _grid_y > 15)
    return (false);
  this->grid_x = _grid_x;
  this->grid_y = _grid_y;
  return (true);
}

SDL_Window	*GDisplay::create_win(std::string _title, Uint32 _h, Uint32 _w)
{
  this->win = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _h, _w, SDL_WINDOW_OPENGL);
  return (this->win);
}

SDL_Window	*GDisplay::create_win(std::string _title, Uint32 _h, Uint32 _w, Uint32 _grid_x, Uint32 _grid_y)
{
  this->set_grid(_grid_x, _grid_y);
  return (this->create_win(_title, _h, _w));
}

bool		GDisplay::update(void)
{
  SDL_Event	event;
  t_reg_event	ev;

  SDL_WaitEvent(&event);
  if (event.type != SDL_KEYDOWN)
    {
      if (this->bounded_keys.find(event.key.keysym.sym) != this->bounded_keys.end())
	{
	  ev = this->bounded_keys[event.key.keysym.sym];
	  (*ev.func)(ev.user);
	}
    }
  return (false);
}

bool		GDisplay::register_key(SDL_Keycode _keycode, void (*_func)(void *), void *_user)
{
  t_reg_event	ev;

  ev.func = _func;
  ev.user = _user;
  this->bounded_keys[_keycode] = ev;
  return (true);
}
