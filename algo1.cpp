#include "common.h"
#include "input.h"
#include "output.h"
#include "scoring.h"
#include <queue>
#include <utility>



using namespace std;

struct order_end {
    int      car_id;
    Point    location;
    uint16_t end_time; // IS NIGH
};

double k[3] = {0, 2, 1};

double RideScore(int time, Point location, Ride ride, int B) {
    double score = 0.;

    int dist = PointDist(location, ride.start);
    int len  = PointDist(ride.start, ride.finish);
    if (time + dist + len >= ride.latest_finish) return 0.;

    score -= k[0] * (ride.earliest_time - time);
    if (time + dist <= ride.earliest_time)
        score += k[1] * B;
    score += k[2] * len;

    return score;
}

int FindRide(int time, Point location, const vector<Ride>& rides, int B) {
    double highscore = 0.;
    int ride_id = -1;
    for (auto& ride: rides) {
        if (ride.used) continue;

        double score = RideScore(time, location, ride, B);
        if  (score > highscore) {
            ride_id = ride.id;
            highscore = score;
        }
    }
    return ride_id;
}

void SimpleAlg(vector<Car>& cars, vector<Ride>& rides, Task& task) {
    auto my_comp = [](order_end o1, order_end o2) {
      return o1.end_time > o2.end_time;
    };

    priority_queue<order_end, vector<order_end>, decltype(my_comp)> status(my_comp);
    for (auto& car: cars) {
        status.push({car.id, {0, 0}, 0});
    }

    unsigned int T = 0;
    while (status.size() > 0 && T < task.steps) {
        order_end o = status.top();
        status.pop();

        int r_id = FindRide(o.end_time, o.location, rides, task.bonus);
        if (r_id < 0) {
            continue;
        }
        auto& r = rides[r_id];

        r.used = true;

        //cout << "Adding order " << r_id << " to car " << o.car_id << "\n";
        cars[o.car_id].rides.push_back(r_id);
        o.end_time += PointDist(o.location, r.start);
        o.end_time += PointDist(r.start, r.finish);
        o.location = r.finish;

        T = o.end_time;
        status.push(o);
    }
}

int main(int argc, char** argv) {
    Task task;
    vector<Car> cars;
    vector<Ride> rides;

    const vector<string> input = {"../in/a_example.in", "../in/b_should_be_easy.in", "../in/c_no_hurry.in", "../in/d_metropolis.in", "../in/e_high_bonus.in"};
    const vector<string> output = {"a.out", "b.out", "c.out", "d.out", "e.out"};
    const vector<char> id = {'A', 'B', 'C', 'D', 'E'};

    int task_id = 4;

    if (argc > 1) {
        task_id = atoi(argv[1]);
    }

    if (argc > 4) {
        k[0] = atof(argv[2]);
        k[1] = atof(argv[3]);
        k[2] = atof(argv[4]);
    }

    ReadDataset(task, cars, rides, input[task_id]);

    SimpleAlg(cars, rides, task);

    WriteOutput(cars, output[task_id]);

    cout << "Score " << id[task_id] << " " << TaskScore(cars, rides, task) << "\n";
}