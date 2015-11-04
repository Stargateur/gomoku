//
// GROButton.hh for  in /home/elliott/rendu/gomoku/GUI
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Wed Nov  4 16:17:37 2015 Elliott
// Last update Wed Nov  4 20:47:31 2015 Elliott
//

#ifndef GROButton_HH__
# define GROButton_HH__

# include	<SDL2/SDL.h>
# include	"AGRenderObject.hh"

class GROButton : public AGRenderObject
{
private:
  SDL_Surface	*surf;

public:
  GROButton(void);
  GROButton(Uint32 _col, Uint32 _row);
  ~GROButton(void);

  SDL_Surface	*render(void);
};

#endif /* GROButton_HH__ */
