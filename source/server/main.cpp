//
// main.cpp for main in /home/plasko_a/projet/gomoku/source/server
//
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
//
// Started on  Mon Jan 25 18:31:09 2016 Antoine Plaskowski
// Last update Sat Feb 13 02:24:46 2016 Antoine Plaskowski
//

#include    <iostream>
#include    <csignal>
#include	<chrono>
#include    <boost/program_options/options_description.hpp>
#include    <boost/program_options/positional_options.hpp>
#include    <boost/program_options/variables_map.hpp>
#include    <boost/program_options/value_semantic.hpp>
#include    <boost/program_options/parsers.hpp>
#include    "Server.hpp"
#include    "Options.hpp"

static sig_atomic_t g_keep_running = 1;

static void    sigint(int)
{
    std::signal(SIGINT, &sigint);
    g_keep_running = 0;
}

int	main(int argc, char **argv)
{
    Options options;
    boost::program_options::options_description desc;
    desc.add_options()
        ("help,h", "produce help message")
        ("port,p", boost::program_options::value<std::string>(&options.port), "the port used by the server (tcp)")
    ;

    boost::program_options::positional_options_description pos_desc;

    boost::program_options::basic_command_line_parser<char> bclp(argc, argv);
    bclp.options(desc).positional(pos_desc);
    
    boost::program_options::variables_map vm;
    boost::program_options::store(bclp.run(), vm);
    boost::program_options::notify(vm);
    if (vm.count("help") != 0)
    {
        std::cout << desc << std::endl;
        return 1;
    }

    auto start = std::chrono::steady_clock::now();

    Server	server(options);
    std::signal(SIGINT, &sigint);
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
