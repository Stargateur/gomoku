cmake_minimum_required(VERSION 3.4)
set(CMAKE_MODULE_PATH "C:/SFML-2.3.2/cmake/Modules/" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package (Threads)
add_library(isocket
	STATIC
	source/isocket/ITCP_server.cpp
	source/isocket/ITCP_client.cpp
	source/isocket/ASocket.cpp
	source/isocket/ISelect.cpp
	source/isocket/ISocket.cpp
	source/isocket/ITCP_client.cpp
	source/isocket/ITCP_server.cpp
	source/isocket/Select.cpp
	source/isocket/TCP_client.cpp
	source/isocket/TCP_server.cpp)
target_compile_features(isocket PUBLIC cxx_range_for)
target_include_directories(isocket PUBLIC include/isocket include/itime)
if(WIN32)
  target_link_libraries(isocket PUBLIC ws2_32)
endif()
add_library(itime
	STATIC
	source/itime/ITime.cpp
	source/itime/Time.cpp)
target_compile_features(itime PUBLIC cxx_range_for)
target_include_directories(itime PUBLIC include/itime)
add_library(iprotocol
	STATIC
	source/iprotocol/ITCP_protocol.cpp
	source/iprotocol/ATCP_packet.cpp
	source/iprotocol/TCP_packet_recv.cpp
	source/iprotocol/TCP_packet_send.cpp)
target_compile_features(iprotocol PUBLIC cxx_range_for)
target_include_directories(iprotocol PUBLIC include/iprotocol include/itime include/isocket)
add_executable(gomoku_client
	source/client/Client.cpp
	source/client/GameInfo.cpp
	source/client/GomokuGraphics.cpp
	source/client/GView.cpp
	source/client/GVOButton.cpp
	source/client/PlayerInfo.cpp
	source/client/main.cpp)
target_compile_features(gomoku_client PUBLIC cxx_range_for)
target_include_directories(gomoku_client PUBLIC include/iprotocol include/itime include/isocket include/client)
target_link_libraries(gomoku_client PUBLIC isocket iprotocol itime)
target_include_directories(gomoku_client PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(gomoku_client PUBLIC ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_executable(gomoku_server
	source/server/Arbitre.cpp
	source/server/Black.cpp
	source/server/White.cpp
	source/server/Client.cpp
	source/server/Game.cpp
	source/server/Server.cpp
	source/server/Utils.cpp
	source/server/main.cpp)
target_compile_features(gomoku_server PUBLIC cxx_range_for)
target_include_directories(gomoku_server PUBLIC include/iprotocol include/itime include/isocket include/server)
target_link_libraries(gomoku_server PUBLIC isocket iprotocol itime)
target_link_libraries(gomoku_server PUBLIC ${CMAKE_THREAD_LIBS_INIT})
