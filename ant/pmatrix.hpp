// @author: Asher Desai
// @file: pheromone.hpp
// @description: Defines the PheromoneMatrix class

#pragma once

#include <vector>

using namespace std;

class PheromoneMatrix {
private:
    vector<double> _phMatrix;

public:
    PheromoneMatrix();

    double get(int i, int j) const;
    void add(int i, int j, double p_new);
    void update(double tau_max, double tau_min);
    void reset();
};