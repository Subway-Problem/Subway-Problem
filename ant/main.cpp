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

    // Path bestPath(costMatrix);
    Path bestPath;
    vector<int> p0 = bestPath.getPath();
    int bestDist = bestPath.getDist();
    vector<int> last10(10, 1500000);
    int stallCount = 0;

    // double ph_new = Q / (double)bestDist;
    // for (int k = 0; k < NUM_NODES - 1; ++k) {
    //     phMatrix->add(p0[k], p0[k + 1], pow(ph_new, ALPHA));
    // }

    for (int i = 0; i < NUM_ITER; ++i) {
        // Loops through each ant, each generating an associated path, adding it to a list of paths per iteration
        vector<Path> paths;
        for (int k = 0; k < NUM_ANTS; ++k)
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
        double tau_max = 1.0 / (bestDist * RHO);
        double tau_factor = pow(P_BEST, 1.0 / NUM_NODES);
        double tau_min = (tau_max * (1 - tau_factor)) / ((NUM_NODES / 2.0 - 1) * tau_factor);

        phMatrix->update(tau_max, tau_min);
        double ph_new = 1 / (double)dist;
        for (int k = 0; k < NUM_NODES - 1; ++k) {
            phMatrix->add(path[k], path[k + 1], pow(ph_new, ALPHA));
        }

        // Keeps a running average of the last 10 iteration bests
        for (int i = 1; i < 10; ++i)
            last10[i - 1] = last10[i];
        last10[9] = dist;
        int sum = 0;
        for (int i = 0; i < 10; ++i)
            sum += last10[i];
        int avg = sum / 10;

        // Handles the recalibration count
        if (dist < bestDist) {
            bestDist = dist;
            stallCount = 0;
        }
        else ++stallCount;

        // Records best overall path
        int best_gl = bestPath.getDist();
        if (dist < bestPath.getDist())
            bestPath = paths[0];

        printf("%6d; dist: %7d; best: %7d; 10avg: %7d; stall: %4d \n", i, dist, best_gl, avg, stallCount);

        // If there has been no change in the best path duration for 2500 iterations, pheromones are reset
        if (stallCount > RESET_COUNT) {
            phMatrix->reset();
            bestDist = 1500000;
            stallCount = 0;
        }
    }

    // Prints out the overall best path and its duration
    vector<int> p = bestPath.getPath();
    cout << bestPath.getDist() << flush;
    cout << "," << startTime << flush;
    for (int i = 0; i < NUM_NODES; ++i) {
        cout << "," << p[i] << flush;
    }
    cout << endl;

    return 0;
}