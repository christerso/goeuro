#include "busroute.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

void BusRoute::load_routes(std::string filename)
{
    std::ifstream busroutes(filename, std::ios::in);
    if (busroutes.is_open())
    {
        int value;
        int route_id;
        std::string route;
        std::set<int> stations;
        std::getline(busroutes, route);
        int number_of_routes;
        std::stringstream buffer(route);
        buffer >> number_of_routes;
        std::cout << "Loading " << number_of_routes << " routes" << std::endl;
        int count;
        for (count = 0; count < number_of_routes; ++count)
        {
            std::getline(busroutes, route);
            std::stringstream buffer(route);
            if (buffer.eof())
            {
                break;
            }
            if (buffer >> route_id)
            {
                int low = std::numeric_limits<int>::max();
                int high = std::numeric_limits<int>::min();
                while (buffer >> value)
                {
                    value < low ? low = value : low;
                    value > high ? high = value : high;

                    stations.insert(value);
                }

                RouteData data;
                data.m_routeid = route_id;
                data.m_stations = std::move(stations);
                std::multimap<HighRangeValue, RouteData> high_data;
                high_data.insert(std::make_pair(high, data));
                m_bus_route_information.insert(std::make_pair(low, std::move(high_data)));
            }
            else
            {
                if (count != number_of_routes)
                {
                    std::cout << "Warning: route count mismatch, wanted " << number_of_routes
                              << " found " << count << std::endl;
                    break;
                }
            }
            if (m_bus_route_information.empty())
            {
                std::cout << "No bus station data found!" << std::endl;
                std::exit(1);
            }
        }
    }
    else
    {
        std::cout << "Unable to open bus route file: " << filename << std::endl;
        std::exit(1);
    }
}

bool BusRoute::check_route(int low, int high)
{
    auto upper = m_bus_route_information.lower_bound(low + 1);
    auto pos = m_bus_route_information.begin();

    while (pos != upper)
    {
        auto top = pos->second.lower_bound(high);
        while (top != pos->second.end())
        {
            auto enditer = top->second.m_stations.end();
            if (top->second.m_stations.find(low) != enditer
                && top->second.m_stations.find(high) != enditer)
            {
                return true;
            }
            ++top;
        }
        ++pos;
    }
    return false;
}
