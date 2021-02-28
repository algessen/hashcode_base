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
    int ideal_time = 0;
};

void Algo1(vector<Car>& cars, vector<Street>& streets, vector<Intersection>& intersections, int duration, double part, int min_interval, int max_interval) {
    vector<CountedIntersection> counted_intersections(intersections.size());
    vector<OrderedCar> ordered_cars(cars.size());
    for (auto& car : cars) {
        ordered_cars[car.id].id = car.id;
        for (int i = 1; i < car.streets.size(); ++i) {
            ordered_cars[car.id].ideal_time += streets[car.streets[i]].time;
        }
    }

    sort(ordered_cars.begin(), ordered_cars.end(), [](const OrderedCar& left, const OrderedCar& right) {
        return left.ideal_time < right.ideal_time;
    });

    auto it = remove_if(ordered_cars.begin(), ordered_cars.end(), [duration](const OrderedCar& car) {return car.ideal_time > duration;});
    ordered_cars.erase(it, ordered_cars.end());

    for (int i = ordered_cars.size() * part; i < ordered_cars.size(); ++i) {
        cars[ordered_cars[i].id].use = false;
    }

    for (auto& intersection : intersections) {
        counted_intersections[intersection.id].id = intersection.id;
        for (auto& street : intersection.streets) {
            counted_intersections[intersection.id].streets[street] = 0;
        }
    }
    for (auto& car : cars) {
        if (!car.use) {
            continue;
        }
        for (auto& street : car.streets) {
            ++counted_intersections[streets[street].to].streets[street];
            ++counted_intersections[streets[street].to].cars_num;
        }
    }
    for (auto& intersection : counted_intersections) {
        int minn = 1000000;
        for (auto& street : intersection.streets) {
            if (street.second != 0) {
                if (street.second < minn) {
                    minn = street.second;
                }
            }
        }
        if (minn == 1000000) {
            continue;
        }
        for (auto& street : intersection.streets) {
            if (street.second != 0) {
                street.second = min(street.second / minn * min_interval, max_interval);
                intersections[intersection.id].schedule.push_back({street.first, street.second});
            }
        }
    }
    return;
    for (auto& intersection : intersections) {
        cout << intersection.id << ": ";
        for (auto& street : intersection.schedule) {
            cout << street.first << "-" << street.second << ", ";
        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
    const vector<string> input = {"../in/a.txt", "../in/b.txt", "../in/c.txt",
                                  "../in/d.txt", "../in/e.txt", "../in/f.txt"};
    const vector<string> output = {"a.out", "b.out", "c.out", "d.out", "e.out", "f.out"};
    const vector<char> id = {'A', 'B', 'C', 'D', 'E', 'F'};

    int task_id = 4;

    if (argc > 1) {
        task_id = atoi(argv[1]);
    }

    int best_min;
    int best_max;
    float best_part;
    int best_score = 0;

    for (float part = 0.7; part < 1.1; part += 0.1) {
        for (int min_interval = 1; min_interval < 3; ++min_interval) {
            for (int max_interval = min_interval; max_interval <= 15; ++max_interval) {
                int duration;
                vector<Car> cars;
                vector<Street> streets;
                vector<Intersection> intersections;
                int bonus;

                ReadDataset(duration, cars, streets, intersections, bonus, input[task_id]);

                Algo1(cars, streets, intersections, duration, part, min_interval, max_interval);

                int score = Score(duration, bonus, streets, intersections, cars);

                if (score > best_score) {
                    best_score = score;
                    best_min = min_interval;
                    best_max = max_interval;
                    best_part = part;
                    cout << "updated\n" << best_part << ' ' << best_min << ' ' << best_max << ' ' << score << endl;
                    WriteOutput(intersections, streets, output[task_id]);
                }
            }
        }
    }

   //  cout << best_part << ' ' << best_min << ' ' << best_max << endl;

    // cout << "Score " << id[task_id] << " " << Score() << "\n";
}