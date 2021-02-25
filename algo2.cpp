
#include <queue>

#include "common.h"
#include "input.h"
#include "output.h"
#include "scoring.h"

using namespace std;

struct OrderEnd {
    int car_id;
    Point location;
    int end_time;
};

void Algo2(vector<Car>& cars, vector<Ride> rides, const Task& task) {
    sort(rides.begin(), rides.end(), [](const Ride& left, const Ride& right) {
      return left.earliest_time < right.earliest_time;
    });
    auto my_comp = [](OrderEnd o1, OrderEnd o2) {
      return o1.end_time < o2.end_time;
    };

    priority_queue<OrderEnd, vector<OrderEnd>, decltype(my_comp)> status(my_comp);
    for (auto& car : cars) {
        status.push({ car.id, { 0, 0 }, 0 });
    }
    int n = 0;
    while (!status.empty()) {
        cout << "n: " << n << endl;
        ++n;
        auto trip = status.top();
        status.pop();
        if (trip.end_time == task.steps) {
            continue;
        }
        int wait_time = 100000000;
        int best_ride = -1;
        int i = 0;
        for (auto& ride : rides) {
            if (ride.used) {
                continue;
            }
            int wait = ride.earliest_time - (trip.end_time + PointDist(trip.location, ride.start));
            if (wait >= 0 && wait < wait_time) {
                best_ride = i;
                wait_time = wait;
            }
            ++i;
        }

        if (best_ride == -1) {
            continue;
        }
        rides[best_ride].used = true;
        status.push({
                        trip.car_id,
                        rides[best_ride].finish,
                        rides[best_ride].earliest_time + PointDist(rides[best_ride].start, rides[best_ride].finish)});
        cars[trip.car_id].rides.push_back(rides[best_ride].id);
    }
}

int main() {
    Task task;
    vector<Car> cars;
    vector<Ride> rides;

    ReadDataset(task, cars, rides, "../in/b_should_be_easy.in");
    Algo2(cars, rides, task);
    cout << TaskScore(cars, rides, task);
    WriteOutput(cars, "../out2/b_should_be_easy.out");
}
