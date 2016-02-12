//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/server
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Mon Jan 25 18:31:09 2016 Antoine Plaskowski
// Last update Thu Jan 28 16:33:33 2016 Antoine Plaskowski
//

#include    <iostream>
#include    <csignal>
#include	<chrono>
# define _WIN32_WINNT 0xA000
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
#include	"Server.hpp"

static sig_atomic_t g_keep_running = 1;

static void    sigint(int)
{
    std::signal(SIGINT, &sigint);
    g_keep_running = 0;
}

enum lol
{
    XD
};

int     aux_connect(struct addrinfo const *rp)
{
	int   fd;

	if (rp == NULL)
		return -1;
	if ((fd = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1)
		return (aux_connect(rp->ai_next));
	if (::connect(fd, rp->ai_addr, rp->ai_addrlen) == -1)
	{
		::closesocket(fd);
		return (aux_connect(rp->ai_next));
	}
	return (fd);
}

int     connect(std::string const &host, std::string const &port)
{
	struct addrinfo const hints =
	{
		0,
		AF_UNSPEC,
		SOCK_DGRAM,
		IPPROTO_UDP,
		0,
		NULL,
		NULL,
		NULL };
	struct addrinfo       *result;
	int   status = ::getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
	if (status != 0)
		return -1;

	int fd = aux_connect(result);
	::freeaddrinfo(result);
	return (fd);
}

int	main(void)
{
	WSADATA wsaData;
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);

	auto fd = connect("localhost", "4242");
	uint8_t data[42] = "bonjour";
	::send(fd, reinterpret_cast<const char *>(&data), 42, 0);
	::recv(fd, reinterpret_cast<char *>(&data), 42, 0);
	std::cout << data << std::endl;

	auto start = std::chrono::steady_clock::now();
	Server	server;
    std::signal(SIGINT, sigint);
    while (g_keep_running != 0)
    try
    {
        server.pre_run();
        server.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	auto lol = std::chrono::duration_cast<std::chrono::seconds>(diff);
	diff -= lol;
	std::cout << lol.count() << " s" << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count() << " n" << std::endl;
    return 0;
}
