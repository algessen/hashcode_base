#pragma once

#include "common.h"

using namespace std;

void WriteOutput(const vector<Car>& cars, string filename) {
    ofstream out_file;
    out_file.open (filename);

    for (auto& car : cars) {
        out_file << car.rides.size();
        for (auto& ride : car.rides) {
            out_file << " " << ride;
        }
        out_file << endl;
    }
    out_file.close();
}
