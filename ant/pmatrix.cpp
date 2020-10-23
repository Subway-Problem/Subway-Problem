// @author: Asher Desai
// @file: pheromone.cpp
// @description: 

#include <vector>
#include <limits>

#include "pmatrix.hpp"

using namespace std;

constexpr int NUM_NODES = 231;
constexpr double EVAP = 0.01;
constexpr double TAU_MAX = 100;
constexpr double TAU_MIN = (double)1 / TAU_MAX;

PheromoneMatrix::PheromoneMatrix() {
    _M_p.assign(NUM_NODES * NUM_NODES, TAU_MAX);
}

void PheromoneMatrix::setPheromoneLevel(int i, int j, double pheromone) {
    _M_p[NUM_NODES * i + j] = pheromone;
}

void PheromoneMatrix::addPheromone(int i, int j, double p_new) {
    if (_M_p[NUM_NODES * i + j] + p_new < TAU_MAX) _M_p[NUM_NODES * i + j] += p_new;
}

void PheromoneMatrix::updatePheromoneLevel() {
    for (int i = 0; i < NUM_NODES * NUM_NODES; ++i) {
        if (_M_p[i] * ((double)1 - EVAP) > TAU_MIN) _M_p[i] *= ((double)1 - EVAP);
        else continue;
    }
}

double PheromoneMatrix::getPheromoneLevel(int i, int j) {
    return _M_p[NUM_NODES * i + j];
}