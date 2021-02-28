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
#include <queue>

using namespace std;

// First: street id
// Second: time
using Schedule = vector<pair<int, int>>;

struct Street {
    int id;
    int from;
    int to;
    int time;
    string name;
 //   vector<Car> probka;
};

struct Intersection {
    int id;
    vector<int> streets;
    Schedule schedule;
};

struct Car {
    int id;
    vector<int> streets;
    int pos;
    int time;
    bool use = true;
};