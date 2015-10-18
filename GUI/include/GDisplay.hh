//
// GDisplay.hh for  in /home/elliott/rendu/gomoku/GUI/include
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Wed Oct 14 17:45:26 2015 Elliott
// Last update Mon Oct 19 01:08:05 2015 Elliott
//

#ifndef GDisplay_HH__
# define GDisplay_HH__

# include	<map>
# include	<SDL2/SDL.h>

class	GDisplay
{
private:
  SDL_Window	*win;
  SDL_Renderer	*renderer;
  SDL_Surface	*surface;

  Uint32	grid_x;
  Uint32	grid_y;

  std::map<SDL_Keycode , void *> bounded_keys;
  
public:
  GDisplay(void);
  ~GDisplay(void);

  bool		set_grid(Uint32 _grid_x, Uint32 _grid_y);
  SDL_Window	*create_win(std::string _title, Uint32 _h, Uint32 _w);
  SDL_Window	*create_win(std::string _title, Uint32 _h, Uint32 _w, Uint32 _grid_x, Uint32 _grid_y);

  bool		update(void);

  bool		register_key(SDL_Keycode keycode, void *user);
};

#endif /* GDisplay_HH__ */
