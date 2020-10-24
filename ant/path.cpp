// @author: Asher Desai
// @file: path.cpp
// @description: Defines Path member functions

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits>

#include "path.hpp"
#include "cmatrix.hpp"
#include "pmatrix.hpp"
#include "constants.hpp"

using namespace std;

// Generates probability distribution function for each node from a given node at a certain time, depending on which 
// nodes have been visited previously, taking pheromone levels into account
vector<double> Path::_probs(int i, int t, const vector<bool>& visited, CostMatrix* costMatrix, PheromoneMatrix* phMatrix) {
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
    for (int n = 0; n < NUM_NODES; ++n)
        probs[n] /= sum;
    return probs;
}

// Default constructor for Path
Path::Path() {
    _path.assign(NUM_NODES, -1);
    _dist = 999999999;
}

// Models individual ant behavior when creating a path, calling the probability distribution function
// and using a random sample to choose the next node in the path; also sets path distance
Path::Path(CostMatrix* costMatrix, PheromoneMatrix* phMatrix) {
    _path.assign(NUM_NODES, 0);
    _path[0] = startNode;
    vector<bool> visited(NUM_NODES, false);
    int L_k = 0;
    int t = startTime;
    int i, j, dt = 0;
    for (int m = 0; m < NUM_NODES - 1; ++m) {
        i = _path[m];
        j = _path[m + 1];
        visited[i] = true;
        const vector<double>& probs = _probs(i, t, visited, costMatrix, phMatrix);
        vector<double> distribution(NUM_NODES, 0);
        distribution[0] = probs[0];
        for (int n = 1; n < NUM_NODES; ++n) {
            distribution[n] = distribution[n - 1] + probs[n];
        }
        double z = (double)rand() / RAND_MAX;
        for (int n = 0; n < NUM_NODES; ++n) {
            if (distribution[n] > z) {
                j = n;
                break;
            }
        }
        _path[m + 1] = j;
        dt = costMatrix->get(i, j, t);
        L_k += dt;
        t += dt;
    }
    _dist = L_k;
}

// Returns the path vector
vector<int> Path::getPath() const {
    return _path;
}

// Return the path distance/duration
int Path::getDist() const {
    return _dist;
}