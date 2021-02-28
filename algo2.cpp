#include "common.h"
#include "input.h"
#include "output.h"
#include "scoring.h"
#include <queue>
#include <utility>

using namespace std;


struct CountedIntersection {
    int id;
    int cars_num = 0;
    map<int, int> streets = {};
};

struct OrderedCar {
    int id;
    int ideal_time;
};

int min_interval = 1;
int max_interval = 2;

void Algo2(vector<Car>& cars, vector<Street>& streets, vector<Intersection>& intersections) {
    vector<vector<vector<int>>> its_stat;
    its_stat.resize(intersections.size());
    for (int i = 0; i < its_stat.size(); i++) {
        its_stat[i].resize(intersections[i].streets.size());
    }
    cout << "Start Algo 2" << endl;

    for (auto& car: cars) {
        int time = - streets[car.streets[0]].time;
        for (auto& str: car.streets) {
            time += streets[car.streets[0]].time;
            int its = streets[str].to;
            int lstr = find(intersections[its].streets.begin(), intersections[its].streets.end(), str) - intersections[its].streets.begin();
            its_stat[its][lstr].push_back(time);
            time += 1;
        }
    }
    cout << "Created intersection usage statistics" << endl;

    for (int its = 0; its < intersections.size(); its++) {
        vector<int> k; k.resize(intersections[its].streets.size());
        vector<int> c; c.resize(intersections[its].streets.size());
        for (int str = 0; str < intersections[its].streets.size(); str++) {
            int min = 100000000000;
            for (int t = 0; t < its_stat[its][str].size() - 1; t++) {
                int minloc = its_stat[its][str][t+1] - its_stat[its][str][t];
                if (minloc < min)
                    min = minloc;
            }
            k[str] = min;
            c[str] = its_stat[its][str][0] % min;
            cout << "k=" << k[str] << " c=" << c[str] << ", ";
        }
        int period = 0;
        for (int& ki: k) if (ki > period) period = ki;
        for (int str = 0; str < intersections[its].streets.size(); str++) {
            intersections[its].schedule.push_back({str, c[str]});
        }
        sort(intersections[its].schedule.begin(), intersections[its].schedule.end(),
             [](const pair<int, int>& left, const pair<int, int>& right) {
                return left.second < right.second;
        });
        cout << endl << "Its " << its << " full period " << period << endl;
        for (auto& street : intersections[its].schedule) {
            cout << street.first << "-" << street.second << ", ";
        }
        if (intersections[its].schedule.size() == 1) {
            intersections[its].schedule[0].second = 1;
        } else {
            for (int i = 0; i < intersections[its].schedule.size() - 1; i++) {
                intersections[its].schedule[i].second = intersections[its].schedule[i + 1].second -
                                                        intersections[its].schedule[i].second;
            }
        }
        cout << endl << "Scheduled intersection " << its << endl;
    }
    cout << "Finished scheduling" << endl;

    for (auto& intersection : intersections) {
        cout << intersection.id << ": ";
        for (auto& street : intersection.schedule) {
            cout << street.first << "-" << street.second << ", ";
        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
    const vector<string> input = {"../in/a.txt", "../in/b.txt", "../in/c.txt", "../in/d.txt", "../in/e.txt", "../in/f.txt"};
    const vector<string> output = {"a.out", "b.out", "c.out", "d.out", "e.out", "f.out"};
    const vector<char> id = {'A', 'B', 'C', 'D', 'E', 'F'};

    int task_id = 2;

    if (argc > 1) {
        task_id = atoi(argv[1]);
    }

    int duration;
    vector<Car> cars;
    vector<Street> streets;
    vector<Intersection> intersections;
    int bonus;

    ReadDataset(duration, cars, streets, intersections, bonus, input[task_id]);

    Algo2(cars, streets, intersections);

    cout << "End" << endl;

    cout << Score(duration, bonus, streets, intersections, cars);

    WriteOutput(intersections, streets, output[task_id]);

    cout << "Score: " << Score(duration, bonus, streets, intersections, cars) << endl;
}