#include "common.h"
#include "input.h"
#include "output.h"
//#include "scoring.h"

using namespace std;

void SimpleSolution(vector<Street>& streets, vector<Intersection>& intersections) {
    for (auto& intersection : intersections) {
        for (auto& street : streets) {
            intersection.schedule.push_back({street.id, 1});
        }
    }
}

int main(int argc, char** argv) {
    const vector<string> input = {"../in/a.txt", "../in/b.txt", "../in/c.txt", "../in/d.txt", "../in/e.txt"};
    const vector<string> output = {"a.out", "b.out", "c.out", "d.out", "e.out"};
    const vector<char> id = {'A', 'B', 'C', 'D', 'E'};
    int duration;
    vector<Car> cars;
    vector<Street> streets;
    vector<Intersection> intersections;
    int bonus;


    int task_id = 1;

    if (argc > 1) {
        task_id = atoi(argv[1]);
    }

    cout << "read started\n";
    ReadDataset(duration, cars, streets, intersections, bonus, input[task_id]);
    cout << "read complete\n";

    SimpleSolution(streets, intersections);
    cout << "solution complete\n";

    WriteOutput(intersections, streets, output[task_id]);
    cout << "write complete\n";

    //cout << "Score " << id[task_id] << " " << Score() << "\n";
}
