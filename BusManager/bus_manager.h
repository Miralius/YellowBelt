//
// Created by F-Mir on 3/19/2024.
//

#ifndef YELLOWBELT_BUS_MANAGER_H
#define YELLOWBELT_BUS_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include "responses.h"

using namespace std;

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops);

    [[nodiscard]] BusesForStopResponse GetBusesForStop(const string& stop) const;

    [[nodiscard]] StopsForBusResponse GetStopsForBus(const string& bus) const;

    [[nodiscard]] AllBusesResponse GetAllBuses() const;

private:
    std::map<std::string /* stop */, std::vector<std::string /* bus */>> busesForStop;
    std::map<std::string /* bus */, std::vector<std::string /* stop */>> stopsForBus;
};


#endif //YELLOWBELT_BUS_MANAGER_H
