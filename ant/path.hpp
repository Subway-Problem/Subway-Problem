// @author: Asher Desai
// @file: path.hpp
// @description: 

#pragma once

#include <vector>

#include "pmatrix.hpp"
#include "cmatrix.hpp"

using namespace std;

class Path {
private:
    vector<int> _path;
    int _dist;

    vector<double> _probs_ij(int i, int time, const vector<bool>& visited, CostMatrix* M_c, PheromoneMatrix* M_p);

public:
    Path();
    Path(CostMatrix* M_c, PheromoneMatrix* M_p);
    vector<int> getPath() const;
    int getDist() const;
};