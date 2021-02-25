#pragma once

#include "common.h"

using namespace std;

void ReadDataset(Task& task, vector<Car>& cars, vector<Ride>& rides, string filename) {
    ifstream in_file(filename);
    in_file >> task.rows >> task.columns >> task.cars >> task.rides >> task.bonus >> task.steps;
    rides.resize(task.rides);
    for (int i = 0; i < task.rides; ++i) {
        in_file >> rides[i].start.row >> rides[i].start.column >> rides[i].finish.row >>
                rides[i].finish.column >> rides[i].earliest_time >> rides[i].latest_finish;
        rides[i].id = i;
    }
    cars.resize(task.cars);
    for (int i = 0; i < task.cars; ++i) {
        cars[i].id = i;
    }
}