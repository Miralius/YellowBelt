//
// Created by F-Mir on 3/19/2024.
//

#ifndef YELLOWBELT_RESPONSES_H
#define YELLOWBELT_RESPONSES_H

#include <vector>
#include <string>
#include <map>

using namespace std;

struct BusesForStopResponse {
    std::vector<std::string /* bus */> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    string bus;
    std::vector<std::string /* stop */> stops;
    std::map<std::string /* stop */, std::vector<std::string /* bus */>> busesForStop;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    std::map<std::string /* bus */, std::vector<std::string /* stop */>> stopsForBus;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);


#endif //YELLOWBELT_RESPONSES_H
