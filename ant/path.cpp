// @author: Asher Desai
// @file: path.cpp
// @description: 

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>

#include "path.hpp"
#include "cmatrix.hpp"
#include "pmatrix.hpp"

using namespace std;

constexpr int NUM_NODES = 472;
constexpr int startNode = 0;
constexpr int startTime = 26460;

constexpr double Q = 50000;
constexpr double alpha = 1.2;
constexpr double beta = 2.5;

vector<double> Path::_probs_ij(int i, int t, const vector<bool>& visited, CostMatrix* M_c, PheromoneMatrix* M_p) {
    vector<double> probs(NUM_NODES, 0);
    double tau_ij;
    double eta_ij;
    for (int j = 0; j < NUM_NODES; ++j) {
        if (visited[j] == 1) {
            continue;
        }
        else {
            tau_ij = M_p->getPheromoneLevel(i, j);
            eta_ij = (double)1 / M_c->getCost_ijt(i, j, t);
            probs[j] = pow(tau_ij, alpha) * pow(eta_ij, beta);
            //probs[j] = tau_ij * eta_ij;
        }
    }
    double sum = 0;
    for (int n = 0; n < NUM_NODES; ++n)
        sum += probs[n];
    for (int n = 0; n < NUM_NODES; ++n)
        probs[n] /= sum;
    return probs;
}

Path::Path() {
    _path.assign(NUM_NODES, 0);
    _dist = 0;
}

Path::Path(CostMatrix* M_c, PheromoneMatrix* M_p) {
    _path.assign(NUM_NODES, 0);
    _path[0] = startNode;
    vector<bool> visited(NUM_NODES, false);
    int L_k = 0;
    int t = startTime;
    int i, j, dt = 0;
    for (int m = 0; m < NUM_NODES - 1; ++m) {
        i = _path[m];
        visited[i] = true;
        //cout << "it:" << m << " i:" << i << " t:" << t << endl;
        const vector<double>& probs = _probs_ij(i, t, visited, M_c, M_p);
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
        dt = M_c->getCost_ijt(i, j, t);
        L_k += dt;
        t += dt;
    }
    _dist = L_k;
}

vector<int> Path::getPath() const {
    return _path;
}

int Path::getDist() const {
    return _dist;
}