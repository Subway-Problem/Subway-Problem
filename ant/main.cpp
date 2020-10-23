// @author: Asher Desai
// @file: main.cpp
// @description: 

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <random>
#include <limits>

#include "cmatrix.hpp"
#include "pmatrix.hpp"

using namespace std;

constexpr int NUM_NODES = 231;
constexpr int NUM_ANTS = 100;
constexpr int NUM_ITER = 1000;
constexpr int startTime = 26460;
constexpr int startNode = 176;

constexpr double Q = 5000;
constexpr double alpha = 2;
constexpr double beta = 1.5;

vector<double> probs_ij(int i, int time, const vector<bool>& visited, CostMatrix* M_c, PheromoneMatrix* M_p) {
    vector<double> probs(NUM_NODES, 0);
    double tau_ij;
    double eta_ij;
    for (int j = 0; j < NUM_NODES; ++j) {
        if (visited[j] == 1) {
            continue;
        }
        else {
            tau_ij = (double)(M_p->getPheromoneLevel(i, j));
            eta_ij = (double)1 / (double)(M_c->getCost_ijt(time, i, j));
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

int main() {
    cout << "Loading Cost Matrix" << endl;
    CostMatrix* M_c = new CostMatrix("../matrix/select_matrix.bin");
    cout << "Finished loading Cost Matrix" << endl;
    PheromoneMatrix* M_p = new PheromoneMatrix();

    int totalBest = numeric_limits<int>::max();
    for (int x = 0; x < NUM_ITER; ++x) {
        int best = numeric_limits<int>::max();
        for (int k = 0; k < NUM_ANTS; ++k) {
            vector<int> path(NUM_NODES, 0);
            path[0] = startNode;
            vector<bool> visited(NUM_NODES, false);
            int L_k = 0;
            int t = startTime;
            int i, j, dt;

            for (int m = 0; m < NUM_NODES; ++m) {
                i = path[m];
                visited[i] = true;
                const vector<double>& probs = probs_ij(i, t, visited, M_c, M_p);
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
                if (m != NUM_NODES - 1) path[m + 1] = j;
                dt = M_c->getCost_ijt(t, i, j);
                L_k += dt;
                t += dt;
            }
            
            double p_new = Q / L_k;
            for (int m = 0; m < NUM_NODES - 1; ++m) {
                M_p->addPheromone(path[m], path[m + 1], p_new);
            }
            if (best > L_k) best = L_k;

        }
        cout << x << ": " << best << endl;
        if (totalBest > best) totalBest = best;
        M_p->updatePheromoneLevel();
    }
    int node = 0;
    for (int j = 0; j < NUM_NODES; ++j) {
        cout << node << " -> " << j << ": " << M_p->getPheromoneLevel(node, j) << "\n";
    }
    cout << "\n" << endl;
    cout << "BEST: " << totalBest << endl;

    int i, j, dt;
    i = startNode;
    int L_t = 0;
    int t = startTime;
    vector<int> bestPath(NUM_NODES, 0);
    vector<bool> visited(NUM_NODES, false);
    bestPath[0] = i;
    visited[0] = true;
    for (int m = 0; m < NUM_NODES; ++m) {
        double p_max = 0;
        double p_ij;
        for (int x = 0; x < NUM_NODES; ++x) {
            if (visited[x] == 0) {
                p_ij = M_p->getPheromoneLevel(i, x);
                if (p_ij > p_max) {
                    p_max = p_ij;
                    j = x;
                }
            }
        }
        dt = M_c->getCost_ijt(t, i, j);
        L_t += dt;
        t += dt;
        bestPath[m + 1] = j;
        visited[j] = true;
        cout << i << "\t";
        i = j;
    }
    cout << endl;
    cout << "global pheromone path best: " << L_t << endl;

    cout << "done" << endl;

    return 0;
}