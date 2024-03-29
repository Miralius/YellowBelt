//
// Created by F-Mir on 3/19/2024.
//

#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    for (const auto& stop : stops)
    {
        busesForStop[stop].emplace_back(bus);
        stopsForBus[bus].emplace_back(stop);
    }
}

[[nodiscard]] BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if (busesForStop.find(stop) == busesForStop.cend())
    {
        return { {} };
    }
    return { busesForStop.at(stop) };
}

[[nodiscard]] StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    if (stopsForBus.find(bus) == stopsForBus.cend())
    {
        return {};
    }
    return { bus, stopsForBus.at(bus), busesForStop };
}

[[nodiscard]] AllBusesResponse BusManager::GetAllBuses() const {
    return { stopsForBus };
}