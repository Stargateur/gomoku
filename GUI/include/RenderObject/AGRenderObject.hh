//
// AGRenderObject.hh for  in /home/elliott/rendu/gomoku/GUI/include/RenderObject
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Wed Nov  4 20:36:04 2015 Elliott
// Last update Wed Nov  4 21:14:26 2015 Elliott
//

#ifndef AGRenderObject_HH__
# define AGRenderObject_HH__

# include	<SDL2/SDL.h>

class AGRenderObject
{
protected:
  Uint32	col;
  Uint32	row;

public:
  AGRenderObject(void);
  AGRenderObject(Uint32 _col, Uint32 _row);

  virtual Uint32	getCol(void);
  virtual Uint32	getRow(void);
  virtual SDL_Surface	*render(void) = 0;
};

#endif /* AGRenderObject_HH__ */
