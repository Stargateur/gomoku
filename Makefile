##
## Makefile for makefile in /home/plasko_a/projet/gomoku
## 
## Made by Antoine Plaskowski
## Login   <plasko_a@epitech.eu>
## 
## Started on  Mon Jan 25 18:21:00 2016 Antoine Plaskowski
## Last update Mon Jan 25 18:26:47 2016 Antoine Plaskowski
##

CLIENT		=	gomuku_client

SERVER		=	gomuku_server

CXX		?=	g++

RM		=	rm

MAKE		=	make

DEBUG		?=	yes

LEVEL		?=	3

COLOR		?=	no

LIB_SERVER	=	

LIB_CLIENT	=	$(shell pkg-config --libs sfml-graphics sfml-window sfml-system sfml-network)

INCLUDE		=	-I include -I include/itime -I include/isocket -I include/iprotocol
INCLUDE		+=	$(shell pkg-config --cflags sfml-graphics sfml-window sfml-system sfml-network)

CXXFLAGS	+=	-Wall -Wextra
CXXFLAGS	+=	-ansi -pedantic -std=c++11
CXXFLAGS	+=	$(INCLUDE)

ifeq ($(CXX), clang++)
CXXFLAGS	+=	-Weverything -Wno-c++98-compat -Wno-padded
endif

ifneq ($(DEBUG), no)
CXXFLAGS	+=	-g -D DEBUG
else
CXXFLAGS	+=	-O$(LEVEL)
endif

ifneq ($(COLOR), no)
CXXFLAGS	+=	-fdiagnostics-color
endif

LDFLAGS		=

ifeq ($(DEBUG), no)
LDFLAGS		+=	-s
endif

include			source.mk

DPD		=	$(SRC:.cpp=.dpd)
OBJ		=	$(SRC:.cpp=.o)

DPD_SERVER	=	$(SRC_SERVER:.cpp=.dpd)
OBJ_SERVER	=	$(SRC_SERVER:.cpp=.o)

DPD_CLIENT	=	$(SRC_CLIENT:.cpp=.dpd)
OBJ_CLIENT	=	$(SRC_CLIENT:.cpp=.o)

all		:	$(SERVER) $(CLIENT)

$(SERVER)	:	CXXFLAGS += -I include/server
$(SERVER)	:	$(OBJ) $(OBJ_SERVER)
			$(CXX) $(OBJ) $(OBJ_SERVER) -o $(SERVER) $(LDFLAGS) $(LIB_SERVER)

$(CLIENT)	:	CXXFLAGS += -I include/client
$(CLIENT)	:	$(OBJ) $(OBJ_CLIENT)
			$(CXX) $(OBJ) $(OBJ_CLIENT) -o $(CLIENT) $(LDFLAGS) $(LIB_CLIENT)

$(DPD_SERVER)	:	CXXFLAGS += -I include/server
$(DPD_CLIENT)	:	CXXFLAGS += -I include/client

clean		:
			$(RM) -f $(OBJ)
			$(RM) -f $(DPD)
			$(RM) -f $(OBJ_SERVER)
			$(RM) -f $(DPD_SERVER)
			$(RM) -f $(OBJ_CLIENT)
			$(RM) -f $(DPD_CLIENT)

fclean		:	clean
			$(RM) -f $(SERVER)
			$(RM) -f $(CLIENT)

re		:	fclean
			$(MAKE) -C .

%.dpd		:	%.c
			$(CC) -MM $(<) -o $(@) $(CFLAGS) -MT $(<:.c=.o)

%.o		:	%.c
			$(CC) -c $(<) -o $(@) $(CFLAGS)

%.dpd		:	%.cpp
			$(CXX) -MM $(<) -o $(@) $(CXXFLAGS) -MT $(<:.cpp=.o)

%.o		:	%.cpp
			$(CXX) -c $(<) -o $(@) $(CXXFLAGS)

.PHONY		:	all clean fclean re %.dpd %.o

.SUFFIXES	:	.o.c .dpd.c .o.cpp .dpd.cpp

include			$(DPD) $(DPD_SERVER) $(DPD_CLIENT)
