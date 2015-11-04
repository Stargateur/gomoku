//
// AGRenderObject.cpp for  in /home/elliott/rendu/gomoku/GUI/src/RenderObject
// 
// Made by Elliott
// Login   <zwertv_e@epitech.net>
// 
// Started on  Wed Nov  4 20:58:06 2015 Elliott
// Last update Wed Nov  4 21:00:35 2015 Elliott
//

#include	<SDL2/SDL.h>
#include	"AGRenderObject.hh"

AGRenderObject::AGRenderObject(void) : col(0), row(0) { }
AGRenderObject::AGRenderObject(Uint32 _col, Uint32 _row) : col(_col), row(_row) { }

Uint32	AGRenderObject::getCol(void)
{
  return (this->col);
}

Uint32	AGRenderObject::getRow(void)
{
  return (this->row);
}
