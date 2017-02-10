#include "routehandler.h"

#include <sstream>

using namespace Net;

RouteHandler::RouteHandler(Address address, BusRoute& busroutes)
    : m_http_endpoint(std::make_shared<Net::Http::Endpoint>(address)), m_bus_routes(busroutes)
{
}

RouteHandler::~RouteHandler()
{
}

void RouteHandler::start()
{
    m_http_endpoint->setHandler(m_router.handler());
    m_http_endpoint->serve();
}

void RouteHandler::shutdown()
{
    m_http_endpoint->shutdown();
}

void RouteHandler::setup_routes()
{
    Net::Rest::Routes::Get(m_router, "/api/direct",
                           Net::Rest::Routes::bind(&RouteHandler::route_request, this));
}

void RouteHandler::route_request(const Net::Http::Request& request,
                                 Net::Http::ResponseWriter response)
{
    // Only respond to http://localhost:8088/api/direct path
    if (request.resource() == "/api/direct" && request.method() == Http::Method::Get)
    {
        build_response(request.query().get("arr_sid").get(), request.query().get("dep_sid").get(),
                       response);
    }
}

void RouteHandler::init(unsigned int threads)
{
    auto opts = Net::Http::Endpoint::options()
                        .threads(static_cast<int>(threads))
                        .flags(Net::Tcp::Options::InstallSignalHandler);
    m_http_endpoint->init(opts);
    setup_routes();
}

void RouteHandler::build_response(std::string arrival_station,
                                  std::string departure_station,
                                  Http::ResponseWriter& response)
{
    int arrival = 0;
    int departure = 0;
    std::stringstream value;
    value << arrival_station;
    value >> arrival;
    value.str("");
    value.clear();
    value << departure_station;
    value >> departure;

    int low, high;
    if (arrival > departure)
    {
        low = departure;
        high = arrival;
    }
    else
    {
        low = arrival;
        high = departure;
    }

    std::string message;
    message.append("{\n");
    message.append("   \"dep_sid\": " + departure_station + ",\n");
    message.append("   \"arr_sid\": " + arrival_station + ",\n");
    std::string route(m_bus_routes.check_route(low, high) ? "true" : "false");
    message.append("   \"direct_bus_route\": " + route + "\n");
    message.append("}\n");
    response.send(Http::Code::Ok, message);
}
