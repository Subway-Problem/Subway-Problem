// @author: Asher Desai
// @file: graph.cpp
// @description: loads the cost matrix from full_matrix.bin (or select_matrix.bin) into the Matrix object, representing a cost matrix
// that gives the time it takes to get from any node to any other node at a given time. Also defines a function to access the cost
// matrix, which is used by the algorithm (genetic, ant colony, or other)

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "matrix.hpp"

using namespace std;

Matrix::Matrix(string filename) {
    _matrix.resize(NUM_TIMES, vector<int>(NUM_SELECT * NUM_SELECT));
    ifstream fin(filename, ios::in | ios::binary);
    
    if (fin.good()) {
        for (int i = 0; i < NUM_TIMES; ++i) {
            fin.read((char*)&_matrix[i][0], NUM_SELECT * NUM_SELECT * sizeof(int));
        }
    }
    fin.close();
}

void Matrix::printMatrix(int time) {
    for (unsigned i = 0; i < NUM_SELECT; ++i) {
        for (unsigned j = 0; j < NUM_SELECT; ++j) {
            cout << _matrix[time][NUM_SELECT * i + j] << '\t';
        }
        cout << '\n';
    }
    cout << '\n';
}

int Matrix::getArrivalTime(int time, int origin, int destination) {
    int arrivalTime = _matrix[(time % 86400) / 30][NUM_SELECT * (size_t)origin + (size_t)destination];
    return arrivalTime - (time % 86400);
}