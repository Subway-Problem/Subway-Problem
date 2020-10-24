// @author: Asher Desai
// @file: pheromone.cpp
// @description: 

#include <vector>
#include <limits>

#include "pmatrix.hpp"
#include "constants.hpp"

using namespace std;

PheromoneMatrix::PheromoneMatrix() {
    _M_p.assign(NUM_NODES * NUM_NODES, TAU_MAX);
}

void PheromoneMatrix::setPheromoneLevel(int i, int j, double pheromone) {
    _M_p[NUM_NODES * i + j] = pheromone;
}

void PheromoneMatrix::addPheromone(int i, int j, double p_new) {
    _M_p[NUM_NODES * i + j] += p_new;
}

double PheromoneMatrix::getPheromoneLevel(int i, int j) const {
    return _M_p[NUM_NODES * i + j];
}

void PheromoneMatrix::updatePheromoneLevel() {
    // If a pheromone level is greater than TAU_MAX, it is set to TAU_MAX
    // If the pheromone would evaporate to a value above TAU_MIN, it proceeds with the evaporation
    for (int i = 0; i < NUM_NODES * NUM_NODES; ++i) {
        if (_M_p[i] > TAU_MAX) _M_p[i] = TAU_MAX;
        if (_M_p[i] * (1.0 - EVAP) > TAU_MIN) _M_p[i] *= (1.0 - EVAP);
    }
}