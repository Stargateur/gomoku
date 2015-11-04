##
## Makefile for  in /home/elliott/rendu/gomoku
## 
## Made by Elliott
## Login   <zwertv_e@epitech.net>
## 
## Started on  Tue Oct 13 11:25:44 2015 Elliott
## Last update Wed Nov  4 20:35:39 2015 Elliott
##

NAME		=	gui_client

CXX		?=	g++

RM		=	rm -f

DEBUG		?=	no

LIB		=	-lSDL2

INCLUDE		=	-I include/ -I include/RenderObject/

CXXFLAGS	+=	-Wall -Wextra
CXXFLAGS	+=	-Wno-padded
CXXFLAGS	+=	$(INCLUDE)

ifeq ($(CXX), clang)
CXXFLAGS	+=	-Weverything
endif

ifneq ($(DEBUG), no)
CXXFLAGS	+=	-g
endif

LDFLAGS		+=	$(LIB)

SRC		=
include		source.mk

OBJ		=	$(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean	all

%.o:		%.cpp
		$(CXX) -c $(<) -o $(@) $(CXXFLAGS)

.PHONY:		all clean fclean re %.o

.SUFFIXES:	.o.cpp
