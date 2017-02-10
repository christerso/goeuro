#ifndef ROUTEHANDLER_H
#define ROUTEHANDLER_H

#include "busroute.h"

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/router.h>

#include <memory>
#include <string>

namespace Net
{
class RouteHandler
{
public:
    RouteHandler(Net::Address address, BusRoute& busroutes);
    ~RouteHandler();

    void route_request(const Http::Request& request, Http::ResponseWriter response);

    void init(unsigned int threads);

    void start();

    void shutdown();

private:
    void setup_routes();
    void build_response(std::string arrival_station,
                        std::string departure_station,
                        Http::ResponseWriter& response);

    Net::Rest::Router m_router;
    std::shared_ptr<Net::Http::Endpoint> m_http_endpoint;
    BusRoute m_bus_routes;
};
}

#endif // ROUTEHANDLER_H
