#include "routehandler.h"

#include <iostream>
#include <iostream>

int main(int argc, char** argv)
{
	std::string bus_route_file;
    if (argc >= 2)
    {
        bus_route_file = argv[1];
    }
	else
	{
		std::cout << "Need a bus route file as argument" << std::endl;
		exit(1);
	}

    Net::Port port(8088);
    unsigned int threads = std::thread::hardware_concurrency();
    Net::Address addr(Net::Ipv4::any(), port);

    // Prepare the bus routes
    BusRoute busroutes;
    busroutes.load_routes(bus_route_file);

    Net::RouteHandler route_server(addr, busroutes);

    route_server.init(threads);
    route_server.start();
    route_server.shutdown();
}
