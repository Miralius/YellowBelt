#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    Query() = default;

    Query(QueryType type, string bus, string stop, vector<string> stops)
    : type(type)
    , bus(std::move(bus))
    , stop(std::move(stop))
    , stops(std::move(stops))
    {}

    QueryType type{};
    string bus;
    string stop;
    vector<string> stops;
};

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
        q = Query{ type, bus, stop, stops };
    }
    return is;
}

struct BusesForStopResponse {
    std::vector<std::string /* bus */> buses;
};

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

struct StopsForBusResponse {
    string bus;
    std::vector<std::string /* stop */> stops;
    std::map<std::string /* stop */, std::vector<std::string /* bus */>> busesForStop;
};

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

struct AllBusesResponse {
    std::map<std::string /* bus */, std::vector<std::string /* stop */>> stopsForBus;
};

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

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        for (const auto& stop : stops)
        {
            busesForStop[stop].emplace_back(bus);
            stopsForBus[bus].emplace_back(stop);
        }
    }

    [[nodiscard]] BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (busesForStop.find(stop) == busesForStop.cend())
        {
            return { {} };
        }
        return { busesForStop.at(stop) };
    }

    [[nodiscard]] StopsForBusResponse GetStopsForBus(const string& bus) const {
        if (stopsForBus.find(bus) == stopsForBus.cend())
        {
            return {};
        }
        return { bus, stopsForBus.at(bus), busesForStop };
    }

    [[nodiscard]] AllBusesResponse GetAllBuses() const {
        return { stopsForBus };
    }

private:
    std::map<std::string /* stop */, std::vector<std::string /* bus */>> busesForStop;
    std::map<std::string /* bus */, std::vector<std::string /* stop */>> stopsForBus;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}