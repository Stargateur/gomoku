##
## source.mk for source in /home/plasko_a/projet/gomoku
## 
## Made by Antoine Plaskowski
## Login   <plasko_a@epitech.eu>
## 
## Started on  Mon Jan 25 18:27:08 2016 Antoine Plaskowski
## Last update Mon Feb  8 16:56:35 2016 Antoine Plaskowski
##

DIR		=	source

DIR_SERVER	=	$(DIR)/server

DIR_CLIENT	=	$(DIR)/client

DIR_ITIME	=	$(DIR)/itime

DIR_ISOCKET	=	$(DIR)/isocket

DIR_IPROTOCOL	=	$(DIR)/iprotocol

SRC		=

SRC		+=	$(DIR_ISOCKET)/ISelect.cpp
SRC		+=	$(DIR_ISOCKET)/Select.cpp
SRC		+=	$(DIR_ISOCKET)/ISocket.cpp
SRC		+=	$(DIR_ISOCKET)/ASocket.cpp
SRC		+=	$(DIR_ISOCKET)/ITCP_client.cpp
SRC		+=	$(DIR_ISOCKET)/TCP_client.cpp
SRC		+=	$(DIR_ISOCKET)/ITCP_server.cpp
SRC		+=	$(DIR_ISOCKET)/TCP_server.cpp

SRC		+=	$(DIR_IPROTOCOL)/ITCP_protocol.cpp
SRC		+=	$(DIR_IPROTOCOL)/ATCP_packet.cpp
SRC		+=	$(DIR_IPROTOCOL)/TCP_packet_recv.cpp
SRC		+=	$(DIR_IPROTOCOL)/TCP_packet_send.cpp

SRC		+=	$(DIR_ITIME)/ITime.cpp
SRC		+=	$(DIR_ITIME)/Time.cpp

SRC_SERVER	=	$(DIR_SERVER)/main.cpp
SRC_SERVER	+=	$(DIR_SERVER)/Server.cpp
SRC_SERVER	+=	$(DIR_SERVER)/Client.cpp
SRC_SERVER	+=	$(DIR_SERVER)/Game.cpp
SRC_SERVER	+=	$(DIR_SERVER)/Arbitre.cpp
SRC_SERVER	+=	$(DIR_SERVER)/White.cpp
SRC_SERVER	+=	$(DIR_SERVER)/Black.cpp

SRC_CLIENT	=	$(DIR_CLIENT)/main.cpp
SRC_CLIENT	+=	$(DIR_CLIENT)/Client.cpp
SRC_CLIENT	+=	$(DIR_CLIENT)/PlayerInfo.cpp
SRC_CLIENT	+=	$(DIR_CLIENT)/GameInfo.cpp
SRC_CLIENT	+=	$(DIR_CLIENT)/GView.cpp
SRC_CLIENT	+=	$(DIR_CLIENT)/GomokuGraphics.cpp
