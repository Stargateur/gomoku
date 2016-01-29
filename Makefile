##
## Makefile for makefile in /home/plasko_a/projet/gomoku
##
## Made by Antoine Plaskowski
## Login   <plasko_a@epitech.eu>
##
## Started on  Mon Jan 25 18:21:00 2016 Antoine Plaskowski
## Last update Fri Jan 29 17:34:54 2016 Antoine Plaskowski
##

ifeq ($(OS), Windows_NT)
CLIENT		=	gomoku_client.exe
else
CLIENT		=	gomoku_client
endif


ifeq ($(OS), Windows_NT)
SERVER		=	gomoku_server.exe
else
SERVER		=	gomoku_server
endif

CXX		?=	g++

ifeq ($(OS), Windows_NT)
RM		=	cmd /c del
else
RM		=	rm
endif

ifeq ($(OS), Windows_NT)
RM_FLAG		=	/f
else
RM_FLAG		=	-f
endif
MAKE		?=	make
CMAKE		?=	cmake

DEBUG		?=	yes

LEVEL		?=	3

COLOR		?=	no

LIB_SERVER	=

ifeq ($(OS), Windows_NT)
LIB_CLIENT	=	-L SFML/lib -lsfml-main -lsfml-graphics -lsfml-window -lsfml-system
else
LIB_CLENT	=	$(shell pkg-config --libs sfml-graphics sfml-window sfml-system sfml-network)
endif

INCLUDE		=	-I include -I include/itime -I include/isocket -I include/iprotocol
ifeq ($(OS), Windows_NT)
else
INCLUDE		+=	$(shell pkg-config --cflags sfml-graphics sfml-window sfml-system sfml-network)
endif

CXXFLAGS	+=	-Wall -Wextra -Wno-unknown-pragmas
CXXFLAGS	+=	-ansi -pedantic -std=c++11
CXXFLAGS	+=	$(INCLUDE)

ifeq ($(OS), Windows_NT)
CXXFLAGS		+=	-D _WIN32
endif

ifeq ($(CXX), clang++)
CXXFLAGS	+=	-Weverything -Wno-c++98-compat -Wno-padded -Wno-c++98-compat-pedantic
endif

ifneq ($(DEBUG), no)
CXXFLAGS	+=	-g -D DEBUG
else
CXXFLAGS	+=	-O$(LEVEL)
endif

ifneq ($(COLOR), no)
CXXFLAGS	+=	-fdiagnostics-color
endif

ifeq ($(OS), Windows_NT)
LDFLAGS		= -l ws2_32
else
LDFLAGS		=
endif

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

all		:	$(SERVER) $(CLIENT) lib


lib		:
			$(CMAKE) -G "MinGW Makefiles" -DSFML_ROOT="SFML" SFML
			$(MAKE) -C SFML

$(SERVER)	:	CXXFLAGS += -I include/server
$(SERVER)	:	$(OBJ) $(OBJ_SERVER)
			$(CXX) $(OBJ) $(OBJ_SERVER) -o $(SERVER) $(LDFLAGS) $(LIB_SERVER)

$(CLIENT)	:	CXXFLAGS += -I include/client
$(CLIENT)	:	$(OBJ) $(OBJ_CLIENT)
			$(CXX) $(OBJ) $(OBJ_CLIENT) -o $(CLIENT) $(LDFLAGS) $(LIB_CLIENT)

$(DPD_SERVER)	:	CXXFLAGS += -I include/server
$(DPD_CLIENT)	:	CXXFLAGS += -I include/client

clean		:
ifeq ($(OS), Windows_NT)
			$(RM) $(RM_FLAG) $(subst /,\,$(OBJ))
			$(RM) $(RM_FLAG) $(subst /,\,$(DPD))
			$(RM) $(RM_FLAG) $(subst /,\,$(OBJ_SERVER))
			$(RM) $(RM_FLAG) $(subst /,\,$(DPD_SERVER))
			$(RM) $(RM_FLAG) $(subst /,\,$(OBJ_CLIENT))
			$(RM) $(RM_FLAG) $(subst /,\,$(DPD_CLIENT))
else
			$(RM) $(RM_FLAG) $(OBJ)
			$(RM) $(RM_FLAG) $(DPD)
			$(RM) $(RM_FLAG) $(OBJ_SERVER)
			$(RM) $(RM_FLAG) $(DPD_SERVER)
			$(RM) $(RM_FLAG) $(OBJ_CLIENT)
			$(RM) $(RM_FLAG) $(DPD_CLIENT)
endif

fclean		:	clean
ifeq ($(OS), Windows_NT)
			$(RM) $(RM_FLAG) $(subst /,\,$(SERVER))
			$(RM) $(RM_FLAG) $(subst /,\,$(CLIENT))
else
			$(RM) $(RM_FLAG) $(SERVER)
			$(RM) $(RM_FLAG) $(CLIENT)
endif

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

.PHONY		:	all clean fclean re %.dpd %.o lib

.SUFFIXES	:	.o.c .dpd.c .o.cpp .dpd.cpp

include			$(DPD) $(DPD_SERVER) $(DPD_CLIENT)
