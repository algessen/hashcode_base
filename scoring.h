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
            if (intersections[its].schedule.empty()) {
                continue;
            }
//            cout << "[" << time << "] Processing intersection " << its << endl;
            int str = green_street(intersections[its].schedule, time);
//            cout << "    Green on street " << str << endl;
            if (probki[str].size() > 0) {
                int car = probki[str].front();
                if (cars[car].time <= time) {
//                    cout << "Car " << cars[car].id << " ready to drive, pos " << cars[car].pos << endl;
                    probki[str].pop();
                    cars[car].pos++;
                    cars[car].time = time + streets[cars[car].streets[cars[car].pos]].time;
//                    cout << "    Next street stop scheduled to " << cars[car].time << endl;
                    if (cars[car].pos == cars[car].streets.size() - 1) {                       
                        if (cars[car].time <= D) {
                            score += bonus + D - cars[car].time;
//                            cout << "    Route will end, B=" << bonus << ", T=" << D - cars[car].time << endl;
                        } else {
//                            cout << "    Route will end, no score" << endl;
                        }
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
