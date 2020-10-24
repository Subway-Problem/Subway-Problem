// @author: Asher Desai
// @file: path.hpp
// @description: Defines Path class, controls behavior for single ants

#pragma once

#include <vector>

#include "pmatrix.hpp"
#include "cmatrix.hpp"

using namespace std;

class Path {
private:
    vector<int> _path;
    int _dist;

    vector<double> _probs(int i, int t, const vector<bool>& visited, CostMatrix* costMatrix, PheromoneMatrix* phMatrix);

public:
    Path();
    Path(CostMatrix* costMatrix, PheromoneMatrix* phMatrix);
    vector<int> getPath() const;
    int getDist() const;
};