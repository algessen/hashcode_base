#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <utility>
#include <bitset>
#include <random>

using namespace std;

struct Point {
    int column;
    int row;
};

struct Ride {
    int id;
    Point start;
    Point finish;
    int earliest_time;
    int latest_finish;
    bool used = false;
};

struct Car {
    int id;
    vector<int> rides;
};

struct Task {
    int rows;
    int columns;
    int cars;
    int rides;
    int bonus;
    int steps;
};

int PointDist(Point a, Point b) { return abs(a.row-b.row) + abs(a.column-b.column); }