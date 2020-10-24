// @author: Asher Desai
// @file: main.cpp
// @description: 

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <random>
#include <limits>
#include <algorithm>

#include "cmatrix.hpp"
#include "pmatrix.hpp"
#include "path.hpp"
#include "constants.hpp"

using namespace std;

int main() {
    srand(time(NULL));
    string matrixFile = "full_matrix.bin";

    cout << "Loading Cost Matrix" << endl;
    CostMatrix* M_c = new CostMatrix("../matrix/" + matrixFile);
    cout << "Finished loading Cost Matrix" << endl;
    PheromoneMatrix* M_p = new PheromoneMatrix();

    Path best;

    for (int x = 0; x < NUM_ITER; ++x) {
        // Loops through each ant, each generating an associated path, adding it to a list of paths per iteration
        vector<Path> paths;
        for (int k = 0; k < NUM_ANTS; ++k) {
            paths.emplace_back(M_c, M_p);
        }

        // Sorts the list of paths by their duration
        sort(paths.begin(), paths.end(),
        [] (const Path& p1, const Path& p2) -> bool {
            return p1.getDist() < p2.getDist();
        });

        // Acquires the duration and vector of nodes for the best path of the iteration
        int L_k = paths[0].getDist();
        const vector<int>& path = paths[0].getPath();
        cout << "it: " << x << "\tL_k: " << L_k << endl;

        // Uses the duration and path to update the global pheromone matrix
        double ph_new = Q / (double)L_k;
        for (int m = 0; m < NUM_NODES - 1; ++m) {
            M_p->addPheromone(path[m], path[m + 1], ph_new);
        }
        M_p->updatePheromoneLevel();

        best = paths[0];
    }

    // Prints out the overall best path and its duration
    vector<int> bestPath = best.getPath();
    for (int i = 0; i < NUM_NODES; ++i) {
        cout << bestPath[i] << endl;
    }
    cout << "Duration: " << best.getDist() << endl;

    return 0;
}