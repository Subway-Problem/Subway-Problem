// @author: Asher Desai
// @file: cmatrix.cpp
// @description: loads the cost matrix from full_matrix.bin (or select_matrix.bin) into the CostMatrix object, representing a cost matrix
// that gives the time it takes to get from any node to any other node at a given time. Also defines a function to access the cost
// matrix, which is used by the algorithm (ant colony here, but same code applies to others)

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "cmatrix.hpp"
#include "constants.hpp"

using namespace std;

// Constructor for CostMatrix, loads binary data from specified file
CostMatrix::CostMatrix(string filename) {
    _costMatrix.resize(NUM_TIMES, vector<int>(NUM_NODES * NUM_NODES));
    ifstream fin(filename, ios::in | ios::binary);
    
    if (fin.good()) {
        for (int i = 0; i < NUM_TIMES; ++i) {
            fin.read((char*)&_costMatrix[i][0], NUM_NODES * NUM_NODES * sizeof(int));
        }
    }
    fin.close();
}

// Returns the cost (duration) of going from node i to node j at time t
int CostMatrix::get(int i, int j, int t) const {
    return _costMatrix[(t % 86400) / 30][NUM_NODES * i + j];
}