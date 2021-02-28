#pragma once

#include "common.h"

using namespace std;

void ReadDataset(int& duration, vector<Car>& cars, vector<Street>& streets, vector<Intersection>& intersections, int& bonus, string filename) {
    int intersection_num;
    int street_num;
    int car_num;
    ifstream in_file(filename);
    in_file >> duration >> intersection_num >> street_num >> car_num >> bonus;
    // cout << duration << ' ' << intersection_num << ' ' << street_num << ' ' << car_num << ' ' << bonus << endl;
    cars.resize(car_num);
    //streets.resize(street_num);
    intersections.resize(intersection_num);
    map<string, int> street_map;

    int next_street =0;

    for (int i = 0; i < intersection_num; ++i) {
        intersections[i].id = i;
    }

    for (int i = 0; i < street_num; ++i) {
        int start;
        int end;
        string name;
        int time;
        in_file >> start >> end >> name >> time;
        street_map[name] = next_street;
        streets.push_back({next_street, start, end, time, name});
        intersections[end].streets.push_back(next_street);
        next_street++;
    }

    for (int i = 0; i < car_num; ++i) {
        cars[i].id = i;
        int str_num;
        in_file >> str_num;
        for (int j = 0; j < str_num; ++j) {
            string street;
            in_file >> street;
            cars[i].streets.push_back(street_map[street]);
        }
    }

    in_file.close();

    // cout << cars.size() << ' ' << streets.size() << ' ' << intersections.size() << endl;
}