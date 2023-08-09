#include "includes.hpp"

Server::Server(): client_max_body_size(-1)
{}

std::string Server::get_host()
{
	return convertToIPAddress(listen.first);
}

std::string Server::get_port()
{
	return convertPortToString(listen.second);
}
