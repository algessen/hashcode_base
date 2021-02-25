#include "common.h"
#include "input.h"
#include "output.h"
#include "scoring.h"

using namespace std;

int main(int argc, char** argv) {
    const vector<string> input = {"../in/a.in", "../in/b.in", "../in/c.in", "../in/d.in", "../in/e.in"};
    const vector<string> output = {"a.out", "b.out", "c.out", "d.out", "e.out"};
    const vector<char> id = {'A', 'B', 'C', 'D', 'E'};

    int task_id = 4;

    if (argc > 1) {
        task_id = atoi(argv[1]);
    }

    ReadDataset(input[task_id]);


    WriteOutput(output[task_id]);

    cout << "Score " << id[task_id] << " " << Score() << "\n";
}
