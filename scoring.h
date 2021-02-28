#pragma once

#include "common.h"

using namespace std;

int green_street(Schedule s, int time) {
    int i;

    int cycle = 0;
    for (i = 0; i < s.size(); i++) {
        cycle += s[i].second;
    }

    time = time % cycle;
    for (i = 0; i < s.size() && time >= 0; i++) {
        time -= s[i].second;
    }

    return  s[i-1].first;
}

int Score(int D, int bonus, vector<Street> streets, vector<Intersection> intersections, vector<Car>& cars) {
    vector<queue<int>> probki;
    probki.resize(streets.size());

    for (auto& car: cars) {
        //cout << "Processing car " << car.id << endl;
        //cout << "On street " << car.streets[0] << endl;
        car.pos = 0;
        car.time = 0;
        probki[car.streets[0]].push(car.id);
    }

    int score = 0;
    int time = 0;
    while (time < D) {
        for (int its = 0; its < intersections.size(); its++) {
            //cout << "Processing intersection " << its << endl;
            if (intersections[its].schedule.empty()) {
                continue;
            }
            int str = green_street(intersections[its].schedule, time);
            if (probki[str].size() > 0) {
                int car = probki[str].front();
                if (cars[car].time <= time) {
                    probki[str].pop();
                    cars[car].pos++;
                    cars[car].time = time + streets[str].time;
                    if (cars[car].pos == cars[car].streets.size()) {
                        if (cars[car].time <= D)
                            score += bonus + D - cars[car].time;
                    } else {
                        probki[cars[car].streets[cars[car].pos]].push(car);
                    }
                }
            }
        }

        time++;
    }

    return score;
}