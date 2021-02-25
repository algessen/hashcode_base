#include "common.h"
#include "input.h"
#include "output.h"

using namespace std;

int main() {
    Task task;
    vector<Car> cars;
    vector<Ride> rides;

    ReadDataset(task, cars, rides, "../in/a_example.in");
    cout << cars.size() << " " << rides.size();
    cars[0].rides = {0, 2};
    cars[1].rides = {1};
    WriteOutput(cars, "../out1/a.out");
}
