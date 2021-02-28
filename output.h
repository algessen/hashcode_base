#pragma once

#include "common.h"

using namespace std;

void WriteOutput(const vector<Intersection>& intersections, const vector<Street>& streets, string filename) {
    ofstream out_file;
    out_file.open (filename);

    size_t ans_len = 0;
    for (auto& intersection : intersections) {
        if (!intersection.schedule.empty()) {
            ans_len++;
        }
    }
    out_file << ans_len << endl;

    for (auto& intersection : intersections) {
        if (!intersection.schedule.empty()) {
            out_file << intersection.id << endl;
            out_file << intersection.schedule.size() << endl;
            for (auto& sched : intersection.schedule) {
                out_file << streets[sched.first].name << " " << sched.second << endl;
            }
        }
    }
    out_file.close();
}
