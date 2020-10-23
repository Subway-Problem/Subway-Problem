// @author: Asher Desai
// @file: pheromone.hpp
// @description: 

#pragma once

#include <vector>

using namespace std;

class PheromoneMatrix {
private:
    vector<double> _M_p;

public:
    PheromoneMatrix();

public:
    void setPheromoneLevel(int i, int j, double pheromone);
    void updatePheromoneLevel();
    void addPheromone(int i, int j, double p_new);
    double getPheromoneLevel(int i, int j);
};