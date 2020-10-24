// @author: Asher Desai
// @file: graph.cpp
// @description: loads the cost matrix from full_matrix.bin (or select_matrix.bin) into the Matrix object, representing a cost matrix
// that gives the time it takes to get from any node to any other node at a given time. Also defines a function to access the cost
// matrix, which is used by the algorithm (genetic, ant colony, or other)

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "cmatrix.hpp"

using namespace std;

constexpr int NUM_TIMES = 2880;
constexpr int NUM_NODES = 472;

CostMatrix::CostMatrix(string filename) {
    _M_c.resize(NUM_TIMES, vector<int>(NUM_NODES * NUM_NODES));
    ifstream fin(filename, ios::in | ios::binary);
    
    if (fin.good()) {
        for (int i = 0; i < NUM_TIMES; ++i) {
            fin.read((char*)&_M_c[i][0], NUM_NODES * NUM_NODES * sizeof(int));
        }
    }
    fin.close();
}

void CostMatrix::printMatrix(int time) {
    for (unsigned i = 0; i < NUM_NODES; ++i) {
        for (unsigned j = 0; j < NUM_NODES; ++j) {
            cout << _M_c[time][NUM_NODES * i + j] << '\t';
        }
        cout << '\n';
    }
    cout << '\n';
}

int CostMatrix::getCost_ijt(int i, int j, int t) const {
    return _M_c[(t % 86400) / 30][NUM_NODES * i + j];
}