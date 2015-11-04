##
## source.mk for  in /home/elliott/rendu/gomoku
## 
## Made by Elliott
## Login   <zwertv_e@epitech.net>
## 
## Started on  Tue Oct 13 11:52:28 2015 Elliott
## Last update Wed Nov  4 22:13:07 2015 Elliott
##

PATH_SRC	=	src/
OBJECT_SRC	=	$(PATH_SRC)RenderObject/

SRC		+=	$(PATH_SRC)main.cpp		\
			$(PATH_SRC)GDisplay.cpp		\
			$(PATH_SRC)GError.cpp		\
			$(OBJECT_SRC)GROButton.cpp	\
			$(OBJECT_SRC)AGRenderObject.cpp
