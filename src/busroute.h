#ifndef ROUTE_H
#define ROUTE_H

#include <map>
#include <set>
#include <string>

/**
 * @brief The BusRoute class, for loading and finding a route
 */
class BusRoute
{
public:
    using RouteId = int;
    using StationList = std::set<int>;

    /**
     * @brief The RouteData struct, holds a route id and
     * a station list of all stations on this route.
     *
     * @note It should be noted that the station list here is a set.
     * This means that the order of the stations no longer hold true,
     * However this allows for fast sorted lookup O(log(n)).
     * If order needs to be maintained then the set needs to be a vector instead.
     * Lookup will be slower then (O(n)).
     * The routeid is not essential for the task here, but it is here as a way to verify
     * that the method is looking at the correct route data, as well as being useful if
     * more information was wanted.
     * Extending this struct with more information for specific station lists is quick and easy.
     */
    struct RouteData
    {
        RouteId m_routeid;
        StationList m_stations;
    };

    using LowRangeValue = int;
    using HighRangeValue = LowRangeValue;

    /**
     * Upon loading the route information, the lower and upper bounds of the station data is stored
     * in 2 multimaps. This allows for skipping looking into a route if that route is outside of the
     * range specified by the user.
     * Additionally as the limits are multimaps, the values are all stored in binary trees.
     */
    using BusRouteInformation =
            std::multimap<LowRangeValue, std::multimap<HighRangeValue, RouteData>>;

    /**
     * @brief load_routes, loads a bus route file
     * @param filename, the filename of the routefile
     */
    void load_routes(std::string filename);

    /**
     * @brief check_route, checks if a route is available within a range
     * @param low, the lower bound of the range
     * @param high, the upper bound of the range
     * @return
     */
    bool check_route(int low, int high);

private:
    BusRouteInformation m_bus_route_information;
};

#endif // ROUTE_H
