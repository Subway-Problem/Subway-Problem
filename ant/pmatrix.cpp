// @author: Asher Desai
// @file: pheromone.cpp
// @description: Defines PheromoneMatrix member functions

#include <vector>
#include <limits>
#include <cmath>

#include "pmatrix.hpp"
#include "constants.hpp"

using namespace std;

// Constructor for PheromoneMatrix
PheromoneMatrix::PheromoneMatrix() {
    _phMatrix.assign(NUM_NODES * NUM_NODES, 1);
}

// Returns pheromone values between two nodes
double PheromoneMatrix::get(int i, int j) const {
    return _phMatrix[NUM_NODES * i + j];
}

// Adds specified amount of pheromone between two nodes
void PheromoneMatrix::add(int i, int j, double p_new) {
    _phMatrix[NUM_NODES * i + j] += p_new;
}

// Updates the pheromone matrix after each iteration by evaporating pheromones, constrained by TAU_MIN/TAU_MAX
void PheromoneMatrix::update(double tau_max, double tau_min) {
    // If a pheromone level is greater than TAU_MAX, it is set to TAU_MAX
    // If the pheromone would evaporate to a value above TAU_MIN, it proceeds with the evaporation
    for (int i = 0; i < NUM_NODES * NUM_NODES; ++i) {
        if (_phMatrix[i] > tau_max) _phMatrix[i] = tau_max;
        if (_phMatrix[i] * (1.0 - RHO) > tau_min) _phMatrix[i] *= (1.0 - RHO);
    }
}

// Resets the pheromone levels using a certain method **not yet determined which is best**
void PheromoneMatrix::reset() {
    // If there has not been enough change, pheromone levels are recalibrated to be more uniform
    for (int i = 0; i < NUM_NODES * NUM_NODES; ++i) {
        //_phMatrix[i] = pow(_phMatrix[i], RESET_FACTOR);
        _phMatrix[i] = 1;
    }
}