#include "query.h"
#include <iostream>

istream& operator >> (istream& is, Query& q) {
    string action;
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
    is >> action;

    if (action == "NEW_BUS"s)
    {
        type = QueryType::NewBus;
        is >> bus;
        size_t stopCount;
        is >> stopCount;
        stops.reserve(stopCount);
        string newBusStop;
        while (stopCount)
        {
            is >> newBusStop;
            stops.push_back(newBusStop);
            --stopCount;
        }
    }
    else if (action == "BUSES_FOR_STOP"s)
    {
        type = QueryType::BusesForStop;
        is >> stop;
    }
    else if (action == "STOPS_FOR_BUS"s)
    {
        type = QueryType::StopsForBus;
        is >> bus;
    }
    else if (action == "ALL_BUSES"s)
    {
        type = QueryType::AllBuses;
    }
    if (is)
    {
        q = { type, bus, stop, stops };
    }
    return is;
}