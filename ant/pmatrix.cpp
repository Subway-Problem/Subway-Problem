// @author: Asher Desai
// @file: pheromone.cpp
// @description: 

#include <vector>
#include <limits>

#include "pmatrix.hpp"

using namespace std;

constexpr int NUM_NODES = 472;
constexpr double EVAP = 0.01;
constexpr double TAU_MAX = 50;
constexpr double TAU_MIN = 0.1;

PheromoneMatrix::PheromoneMatrix() {
    _M_p.assign(NUM_NODES * NUM_NODES, TAU_MAX);
}

void PheromoneMatrix::setPheromoneLevel(int i, int j, double pheromone) {
    _M_p[NUM_NODES * i + j] = pheromone;
}

void PheromoneMatrix::addPheromone(int i, int j, double p_new) {
    if (_M_p[NUM_NODES * i + j] + p_new < TAU_MAX) _M_p[NUM_NODES * i + j] += p_new;
}

double PheromoneMatrix::getPheromoneLevel(int i, int j) const {
    return _M_p[NUM_NODES * i + j];
}

void PheromoneMatrix::updatePheromoneLevel() {
    for (int i = 0; i < NUM_NODES * NUM_NODES; ++i) {
        if (_M_p[i] * ((double)1 - EVAP) > TAU_MIN) _M_p[i] *= ((double)1 - EVAP);
    }
}