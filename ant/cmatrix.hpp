// @author: Asher Desai
// @file: graph.hpp
// @description: defines the Matrix class, which is a full cost matrix representing the cost from any node to any other node
// at a given time

#pragma once

#include <vector>
#include <string>

using namespace std;

class CostMatrix {
private:
    vector<vector<int>> _M_c;

public:
    CostMatrix(string filename);
    int getCost_ijt(int i, int j, int t) const;
    void printMatrix(int time);
};