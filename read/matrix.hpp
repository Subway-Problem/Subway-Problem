// @author: Asher Desai
// @file: graph.hpp
// @description: defines the Matrix class, which is a full cost matrix representing the cost from any node to any other node
// at a given time

#pragma once

#include <vector>
#include <string>

constexpr int NUM_TIMES = 2880;
constexpr int NUM_NODES = 472;
constexpr int NUM_SELECT = 231;

using namespace std;

class Matrix {
private:
    vector<vector<int>> _matrix;

public:
    Matrix(string filename);

    int getArrivalTime(int time, int origin, int destination);
    void printMatrix(int time);
};