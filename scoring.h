#pragma once

#include "common.h"

using namespace std;

inline unsigned int RideScore(const Ride& r, int start_time) {
    return PointDist(r.start, r.finish);
}

unsigned long int CarScore(const Car& c, const vector<Ride>& rides, int bonus) {
    unsigned long int res = 0;
    unsigned long int time = 0;
    Point loc = {0, 0};

    for (auto& ride : c.rides) {
        auto& r = rides[ride];
        time += PointDist(loc, r.start);

        if (time <= r.earliest_time) {
            res += bonus;
        }

        res += PointDist(r.start, r.finish);
        loc = r.finish;
    }

    return res;
}

int TaskScore(const vector<Car>& cars, const vector<Ride>& rides, const Task& t) {
    unsigned long int res = 0;

    for (auto& car: cars) {
        res += CarScore(car, rides, t.bonus);
    }

    return res;
}