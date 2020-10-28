// @author: Asher Desai
// @file: path.cpp
// @description: Defines Path member functions

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <chrono>

#include "path.hpp"
#include "cmatrix.hpp"
#include "pmatrix.hpp"
#include "constants.hpp"

using namespace std;

// Picks next node based on probability distribution function for each node from a given node at a certain time, depending on which 
// nodes have been visited previously, taking pheromone levels into account
int Path::_pickNext(int i, int t, const vector<bool>& visited, CostMatrix* costMatrix, PheromoneMatrix* phMatrix) {
    vector<double> probs(NUM_NODES, 0);
    double tau;
    double eta;
    for (int j = 0; j < NUM_NODES; ++j) {
        if (visited[j] == 1) {
            continue;
        }
        else {
            tau = phMatrix->get(i, j);
            eta = (double)1 / costMatrix->get(i, j, t);
            probs[j] = pow(tau, ALPHA) * pow(eta, BETA);
        }
    }
    double sum = 0;
    for (int n = 0; n < NUM_NODES; ++n)
        sum += probs[n];
    double z = rand() / (double)RAND_MAX * sum;
    sum = 0;
    int j = 0;
    for (int n = 0; n < NUM_NODES; ++n) {
        sum += probs[n];
        if (sum >= z) {
            j = n;
            break;
        }
    }
    return j;
}

// Default constructor for Path
Path::Path() {
    _path.assign(NUM_NODES, -1);
    _dist = 1500000;
}

// Uses Nearest Neighbor to create a path
Path::Path(CostMatrix* costMatrix) {
    _path.assign(NUM_NODES, 0);
    _path[0] = startNode;
    vector<bool> visited(NUM_NODES, false);
    int dist = 0;
    int t = startTime;
    int i, j, dt = 0;
    for (int m = 0; m < NUM_NODES - 1; ++m) {
        i = _path[m];
        j = _path[m + 1];
        visited[i] = true;
        int minCost = numeric_limits<int>::max();
        for (int k = 0; k < NUM_NODES; ++k) {
            if (visited[k] == 1) {
                continue;
            }
            int cost = costMatrix->get(i, k, t);
            if (cost < minCost) {
                minCost = cost;
                j = k;
            }
        }
        _path[m + 1] = j;
        dt = costMatrix->get(i, j, t);
        dist += dt;
        t += dt;
    }
    _dist = dist;
}

// Models individual ant behavior when creating a path, calling the probability distribution function
// and using a random sample to choose the next node in the path; also sets path distance
Path::Path(CostMatrix* costMatrix, PheromoneMatrix* phMatrix) {
    _path.assign(NUM_NODES, 0);
    _path[0] = startNode;
    vector<bool> visited(NUM_NODES, false);
    int t = startTime;
    int i, j = 0;
    for (int m = 0; m < NUM_NODES - 1; ++m) {
        i = _path[m];
        visited[i] = true;
        j = _pickNext(i, t, visited, costMatrix, phMatrix);
        _path[m + 1] = j;
        t += costMatrix->get(i, j, t);
    }
    _dist = t - startTime;
}

// Returns the path vector
vector<int> Path::getPath() const {
    return _path;
}

// Return the path distance/duration
int Path::getDist() const {
    return _dist;
}