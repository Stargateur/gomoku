//
// GDisplay.hh for  in /home/elliott/rendu/gomoku/GUI/include
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Wed Oct 14 17:45:26 2015 Elliott
// Last update Wed Nov  4 21:16:13 2015 Elliott
//

#ifndef GDisplay_HH__
# define GDisplay_HH__

# include	<map>
# include	<list>
# include	<SDL2/SDL.h>
# include	"AGRenderObject.hh"
# include	"GROButton.hh"

class GDisplay
{
public:
  struct	s_reg_event
  {
    void	(*func)(void *);
    void	*user;
  };
  typedef	s_reg_event	t_reg_event;

private:
  SDL_Window	*win;
  SDL_Renderer	*renderer;
  SDL_Surface	*surface;

  Uint32	grid_col;
  Uint32	grid_row;
  Uint32	cell_w;
  Uint32	cell_h;

  std::map<SDL_Keycode , t_reg_event>	bounded_keys;
  std::list<AGRenderObject *>		objects;
  
public:
  GDisplay(void);
  ~GDisplay(void);

  bool		set_grid(Uint32 _grid_x, Uint32 _grid_y);
  SDL_Window	*create_win(std::string _title, Uint32 _h, Uint32 _w);
  SDL_Window	*create_win(std::string _title, Uint32 _h, Uint32 _w, Uint32 _grid_col, Uint32 _grid_row);

  bool	        resolve_events(void);
  bool		draw(GROButton *btn);

  bool		register_key(SDL_Keycode _keycode, void (*_func)(void *), void *_user);

private:
  void		calculate_grid(void);
};

#endif /* GDisplay_HH__ */
