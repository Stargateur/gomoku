##
## source.mk for source in /home/plasko_a/projet/gomoku
## 
## Made by Antoine Plaskowski
## Login   <plasko_a@epitech.eu>
## 
## Started on  Mon Jan 25 18:27:08 2016 Antoine Plaskowski
## Last update Mon Jan 25 18:31:56 2016 Antoine Plaskowski
##

DIR		=	source

DIR_SERVER	=	$(DIR)/server

DIR_CLIENT	=	$(DIR)/client

DIR_ITIME	=	$(DIR)/itime

DIR_ISOCKET	=	$(DIR)/isocket

DIR_IPROTOCOL	=	$(DIR)/iprotocol

SRC		=

SRC		+=	 $(DIR_ISOCKET)/ISelect.cpp
SRC		+=	 $(DIR_ISOCKET)/Select.cpp
SRC		+=	 $(DIR_ISOCKET)/ISocket.cpp
SRC		+=	 $(DIR_ISOCKET)/ASocket.cpp
SRC		+=	 $(DIR_ISOCKET)/IStandard.cpp
SRC		+=	 $(DIR_ISOCKET)/Standard.cpp
SRC		+=	 $(DIR_ISOCKET)/ITCP_client.cpp
SRC		+=	 $(DIR_ISOCKET)/TCP_client.cpp
SRC		+=	 $(DIR_ISOCKET)/ITCP_server.cpp
SRC		+=	 $(DIR_ISOCKET)/TCP_server.cpp
SRC		+=	 $(DIR_ISOCKET)/IUDP_server.cpp
SRC		+=	 $(DIR_ISOCKET)/UDP_server.cpp
SRC		+=	 $(DIR_ISOCKET)/IUDP_client.cpp
SRC		+=	 $(DIR_ISOCKET)/UDP_client.cpp

SRC		+=	 $(DIR_IPROTOCOL)/ITCP_protocol.cpp
SRC		+=	 $(DIR_IPROTOCOL)/TCP_protocol.cpp
SRC		+=	 $(DIR_IPROTOCOL)/ATCP_packet.cpp
SRC		+=	 $(DIR_IPROTOCOL)/TCP_packet_recv.cpp
SRC		+=	 $(DIR_IPROTOCOL)/TCP_packet_send.cpp
SRC		+=	 $(DIR_IPROTOCOL)/IUDP_protocol.cpp
SRC		+=	 $(DIR_IPROTOCOL)/UDP_protocol.cpp
SRC		+=	 $(DIR_IPROTOCOL)/AUDP_packet.cpp
SRC		+=	 $(DIR_IPROTOCOL)/UDP_packet_recv.cpp
SRC		+=	 $(DIR_IPROTOCOL)/UDP_packet_send.cpp

SRC		+=	 $(DIR_ITIME)/ITime.cpp
SRC		+=	 $(DIR_ITIME)/Time.cpp

SRC_SERVER	=	$(DIR_SERVER)/main.cpp

SRC_CLIENT	=	$(DIR_CLIENT)/main.cpp
