// @author: Asher Desai
// @file: main.cpp
// @description: 

#include <vector>
#include <string>
#include <iostream>

#include "graph.hpp"

int main() {
    cout << "Reading Graph" << endl;

    Graph g("../graph/select_graph.bin");

    int dist = g.getArrivalTime(0, 0, 1);
    cout << dist << endl;

    return 0;
}