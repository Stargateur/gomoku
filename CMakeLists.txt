cmake_minimum_required(VERSION 3.4)
project(gomoku)
set(CMAKE_MODULE_PATH "C:/SFML-2.3.2/cmake/Modules/" ${CMAKE_MODULE_PATH})
if(WIN32)
	set(Boost_USE_STATIC_LIBS ON)
	set(Boost_USE_MULTITHREADED ON)
	set(BOOST_ROOT "C:/Boost/")
	set(BOOST_LIBRARYDIR "C:/Boost/lib/")
	set(BOOST_INCLUDEDIR "C:/Boost/include/boost-1_60/")
endif()
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(Boost COMPONENTS program_options REQUIRED)
find_package (Threads)
if(!WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
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
	source/isocket/TCP_server.cpp
	include/isocket/ASocket.hpp
	include/isocket/ISelect.hpp
	include/isocket/ISocket.hpp
	include/isocket/ITCP_client.hpp
	include/isocket/ITCP_server.hpp
	include/isocket/Select.hpp
	include/isocket/TCP_client.hpp
	include/isocket/TCP_server.hpp
)
target_compile_features(isocket PUBLIC cxx_range_for)
target_include_directories(isocket PUBLIC include/isocket include/itime)
if(WIN32)
  target_link_libraries(isocket PUBLIC ws2_32)
endif()

add_library(itime
	STATIC
	source/itime/ITime.cpp
	source/itime/Time.cpp
	include/itime/ITime.hpp
	include/itime/Time.hpp
)
target_compile_features(itime PUBLIC cxx_range_for)
target_include_directories(itime PUBLIC include/itime)

add_library(iprotocol
	STATIC
	source/iprotocol/ITCP_protocol.cpp
	source/iprotocol/ATCP_packet.cpp
	source/iprotocol/TCP_packet_recv.cpp
	source/iprotocol/TCP_packet_send.cpp
	include/iprotocol/ACallback.hpp
	include/iprotocol/ATCP_packet.hpp
	include/iprotocol/ITCP_protocol.hpp
	include/iprotocol/TCP_packet_recv.hpp
	include/iprotocol/TCP_packet_send.hpp
	include/iprotocol/TCP_protocol.hpp
)
target_compile_features(iprotocol PUBLIC cxx_range_for)
target_include_directories(iprotocol PUBLIC include/iprotocol include/itime include/isocket)

add_executable(gomoku_client
	source/client/Client.cpp
	source/client/GameInfo.cpp
	source/client/GomokuGraphics.cpp
	source/client/GView.cpp
	source/client/GVOButton.cpp
	source/client/PlayerInfo.cpp
	source/client/main.cpp
	include/client/Client.hpp
	include/client/GameInfo.hpp
	include/client/GomokuGraphics.hpp
	include/client/GView.hpp
	include/client/IGVObject.hpp
	include/client/GVOButton.hpp
	include/client/PlayerInfo.hpp
)
target_compile_features(gomoku_client PUBLIC cxx_range_for)
target_include_directories(gomoku_client PUBLIC include/iprotocol include/itime include/isocket include/client)
target_link_libraries(gomoku_client PUBLIC isocket iprotocol itime)
target_include_directories(gomoku_client PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(gomoku_client PUBLIC ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_custom_command(TARGET gomoku_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/Sprite/"
        $<TARGET_FILE_DIR:gomoku_client>/Sprite)

add_executable(gomoku_ai
	source/ai/Client.cpp
	source/ai/main.cpp
	include/ai/Client.hpp
)
target_compile_features(gomoku_ai PUBLIC cxx_range_for)
target_include_directories(gomoku_ai PUBLIC include/iprotocol include/itime include/isocket include/ai)
target_link_libraries(gomoku_ai PUBLIC isocket iprotocol itime)

add_executable(gomoku_server
	source/server/Arbitre.cpp
	source/server/Black.cpp
	source/server/White.cpp
	source/server/Client.cpp
	source/server/Game.cpp
	source/server/Server.cpp
	source/server/Options.cpp
	source/server/Utils.cpp
	source/server/main.cpp
	include/server/Arbitre.hpp
	include/server/Black.hpp
	include/server/White.hpp
	include/server/Client.hpp
	include/server/Game.hpp
	include/server/Server.hpp
	include/server/Options.hpp
	include/server/Utils.hpp
)
target_compile_features(gomoku_server PUBLIC cxx_range_for)
target_include_directories(gomoku_server PUBLIC include/iprotocol include/itime include/isocket include/server)
target_link_libraries(gomoku_server PUBLIC isocket iprotocol itime)
target_link_libraries(gomoku_server PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(gomoku_server PUBLIC ${Boost_LIBRARIES})
target_include_directories(gomoku_server PUBLIC ${Boost_INCLUDE_DIR})
