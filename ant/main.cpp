// @author: Asher Desai
// @file: main.cpp
// @description: Main, controls iteration and calls the ant functions

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
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
    CostMatrix* costMatrix = new CostMatrix("../matrix/" + matrixFile);
    cout << "Finished loading Cost Matrix" << endl;
    PheromoneMatrix* phMatrix = new PheromoneMatrix();

    Path bestPath;
    int bestDist = 999999999;
    int stallCount = 0;

    for (int i = 0; i < NUM_ITER; ++i) {
        // Loops through each ant, each generating an associated path, adding it to a list of paths per iteration
        vector<Path> paths;
        for (int j = 0; j < NUM_ANTS; ++j)
            paths.emplace_back(costMatrix, phMatrix);

        // Sorts the list of paths by their duration
        sort(paths.begin(), paths.end(),
        [] (const Path& p1, const Path& p2) -> bool {
            return p1.getDist() < p2.getDist();
        });

        // Acquires the duration and vector of nodes for the best path of the iteration
        int dist = paths[0].getDist();
        
        const vector<int>& path = paths[0].getPath();

        // Uses the duration and path to update the global pheromone matrix
        double ph_new = Q / (double)dist;
        for (int k = 0; k < NUM_NODES - 1; ++k) {
            phMatrix->add(path[k], path[k + 1], pow(ph_new, ALPHA));
        }
        phMatrix->update();


        // Handles the recalibration count
        if (dist < bestDist) {
            bestDist = dist;
            stallCount = 0;
        }
        else ++stallCount;

        // Records best overall path
        if (dist < bestPath.getDist())
            bestPath = paths[0];

        cout << setfill('0') << setw(6) << i 
            << "  dist: " << setfill('0') << setw(6) << dist 
            << "  best: " << setfill('0') << setw(6) << bestPath.getDist() << endl;

        // If there has been no change in the best path duration for 2500 iterations, pheromones are reset
        if (stallCount > RESET_COUNT) {
            cout << "RESETTING PHEROMONE" << endl;
            phMatrix->reset();
            bestDist = 999999999;
            stallCount = 0;
        }
    }

    // Prints out the overall best path and its duration
    vector<int> p = bestPath.getPath();
    cout << bestPath.getDist() << flush;
    for (int i = 0; i < NUM_NODES; ++i) {
        cout << "," << p[i] << flush;
    }
    cout << endl;

    return 0;
}