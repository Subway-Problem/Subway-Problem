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

using namespace std;

constexpr int NUM_NODES = 472;
constexpr int NUM_ANTS = 25;
constexpr int NUM_ITER = 20000;

constexpr int Q = 50000;

int main() {

    srand(time(NULL));

    cout << "Loading Cost Matrix" << endl;
    CostMatrix* M_c = new CostMatrix("../matrix/full_matrix.bin");
    cout << "Finished loading Cost Matrix" << endl;
    PheromoneMatrix* M_p = new PheromoneMatrix();

    Path best;

    for (int x = 0; x < NUM_ITER; ++x) {
        // Loops through each ant, each generating an associated path, adding it to an iteration list
        vector<Path> paths;
        for (int k = 0; k < NUM_ANTS; ++k) {
            paths.emplace_back(M_c, M_p); // problem here
        }
        sort(paths.begin(), paths.end(),
        [] (const Path& p1, const Path& p2) -> bool {
            return p1.getDist() < p2.getDist();
        });
        int L_k = paths[0].getDist();
        const vector<int>& path = paths[0].getPath();
        cout << "it: " << x << "\tL_k: " << L_k << endl;

        double ph_new = Q / (double)L_k;
        for (int m = 0; m < NUM_NODES - 1; ++m) {
            M_p->addPheromone(path[m], path[m + 1], ph_new);
        }
        M_p->updatePheromoneLevel();

        best = paths[0];
    }

    // int node = 0;
    // for (int j = 0; j < NUM_NODES; ++j) {
    //     cout << node << " -> " << j << ": " << M_p->getPheromoneLevel(node, j) << "\n";
    // }

    vector<int> bestPath = best.getPath();
    for (int i = 0; i < NUM_NODES; ++i) {
        cout << bestPath[i] << endl;
    }

    cout << "done" << endl;

    return 0;
}