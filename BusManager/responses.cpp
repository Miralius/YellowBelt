//
// Created by F-Mir on 3/19/2024.
//

#include "responses.h"
#include <iostream>

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty())
    {
        os << "No stop";
    }
    else
    {
        for (const auto& bus : r.buses)
        {
            os << bus << ' ';
        }
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty())
    {
        os << "No bus";
    }
    else
    {
        for (const auto& stop : r.stops)
        {
            os << "Stop " << stop << ':';
            if (r.busesForStop.at(stop).size() > 1)
            {
                for (const auto& busOfStop : r.busesForStop.at(stop))
                {
                    if (busOfStop != r.bus)
                    {
                        os << ' ' << busOfStop;
                    }
                }
            }
            else
            {
                os << " no interchange";
            }
            os << '\n';
        }
    }
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (!r.stopsForBus.empty())
    {
        for (const auto& [bus, stops] : r.stopsForBus)
        {
            std::cout << "Bus " << bus << ':';
            for (const auto& stop : stops)
            {
                std::cout << ' ' << stop;
            }
            std::cout << '\n';
        }
    }
    else
    {
        std::cout << "No buses";
    }
    return os;
}