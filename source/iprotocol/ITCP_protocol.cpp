#include    "ITCP_protocol.hpp"

iprotocol::ITCP_protocol_exception::~ITCP_protocol_exception(void) noexcept
{
}

iprotocol::ITCP_protocol_exception::ITCP_protocol_exception(void) noexcept
{
}

iprotocol::ITCP_protocol_exception::ITCP_protocol_exception(ITCP_protocol_exception const &) noexcept
{
}

iprotocol::ITCP_protocol_exception   &iprotocol::ITCP_protocol_exception::operator=(ITCP_protocol_exception const &) noexcept
{
    return (*this);
}

char const  *iprotocol::ITCP_protocol_exception::what(void) const noexcept
{
    return ("ITCP_protocol_exception");
}

char const   *iprotocol::get_str_error(iprotocol::Error error)
{
    switch (error)
    {
    case iprotocol::None:
        return ("None");
    case iprotocol::Ignore:
        return ("Ignore");
    case iprotocol::Unknow:
        return ("Unknow");
    case iprotocol::Disconnected:
        return ("Disconnected");
    case iprotocol::Not_connected:
        return ("Not_connected");
    case iprotocol::Timeout:
        return ("Timeout");
    case iprotocol::Wrong_login:
        return ("Wrong_login");
    case iprotocol::Wrong_password:
        return ("Wrong password");
    case iprotocol::Wrong_version:
        return ("Wrong_version");
    case iprotocol::Login_already_use:
        return ("Login_already_use");
    case iprotocol::Game_already_exist:
        return ("Game_already_exist");
    case iprotocol::Game_not_exist:
        return ("Game_not_exist");
    case iprotocol::Already_in_game:
        return ("Already_in_game");
    case iprotocol::Not_in_game:
        return ("Not_in_game");
    case iprotocol::Packet_not_allowed:
        return ("Packet_not_allowed");
    case iprotocol::Game_param_not_exist:
        return ("Game_param_not_exist");
    case iprotocol::Game_player_param_not_exist:
        return ("Game_player_param_not_exist");
    case iprotocol::All_player_are_not_ready:
        return ("All_player_are_not_ready");
    case iprotocol::Game_stone_double_three_not_allow:
        return ("Game_stone_double_three_not_allow");
    case iprotocol::Game_stone_case_not_empty:
        return ("Game_stone_case_not_empty");
    case iprotocol::Game_stone_coordinate_not_valide:
        return ("Game_stone_coordinate_not_valide");
    case iprotocol::Game_stone_not_your_turn:
        return ("Game_stone_not_your_turn");
    };
    throw ITCP_protocol_exception();
}
iprotocol::Game_stone::Game_stone(uint8_t _x, uint8_t _y, Color _color) :
	x(_x),
	y(_y),
	color(_color)
{
}

iprotocol::Game_stone::Game_stone(void) :
	Game_stone(0, 0, None)
{
}

iprotocol::Game_stone::Color    iprotocol::Game_stone::operator!(void)
{
	if (color == Black)
		return White;
	else if (color == White)
		return Black;
	else
		return None;
}

std::ostream    &iprotocol::operator<<(std::ostream &os, Error error)
{
    return os << get_str_error(error);
}