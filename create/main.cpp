// @author: Asher Desai
// @name: main.cpp

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>

#include "data.hpp"
#include "graph.hpp"

using namespace std;

int main() {
    cout << "\n";
    cout << "Creating initial maps...\n";
    Graph g;
    cout << "Finished mapping, starting cost matrix creation...\n";

    // To change to the 231-node matrix, uncomment the next 5 lines and comment out the following 4. 

    // Data selectData("../gtfs/select_stops.txt");
    // vector<int> selectNodes(selectData.getNumRows(), 0);
    // int NUM_SELECT = selectNodes.size();
    // for (int i = 0; i < NUM_SELECT; ++i)
    //     selectNodes[i] = stoi(selectData.getValue(1, i));
    // string fileName = "select_matrix.bin";

    vector<int> selectNodes(NUM_NODES, 0);
    int NUM_SELECT = NUM_NODES;
    for (int i = 0; i < NUM_NODES; ++i)
        selectNodes[i] = i;
    string fileName = "full_matrix.bin";

    vector<vector<int>> costMatrix;
    costMatrix.resize(NUM_TIMES, vector<int>(NUM_SELECT * NUM_SELECT));

    double progress;
    int barWidth = 100;

    auto t3 = chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_TIMES; ++i) {
        auto t1 = chrono::high_resolution_clock::now();
        costMatrix[i] = g.getCostMatrixForTime(selectNodes, i * 30);
        auto t2 = chrono::high_resolution_clock::now();
        auto d1 = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
        int time = d1.count();

        progress = (double)i / (double)NUM_TIMES;
        cout << "[";
        int pos = progress * barWidth;
        for (int i= 0; i < barWidth; ++i) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }
        cout << "]" << int(progress * 100.0) << "%\t" << "time matrix completed in " << time << " ms\r";
        cout.flush();
    }
    auto t4 = chrono::high_resolution_clock::now();
    auto d2 = chrono::duration_cast<chrono::seconds>(t4 - t3);
    cout << "\rCost matrix completed in " << d2.count() << " seconds!";
    for (int i = 0; i < 120; ++i) cout << " ";
    cout.flush();
    usleep(500000);

    cout << "\nWriting matrix to file..." << endl;

    auto t5 = chrono::high_resolution_clock::now();
    ofstream fout("../graph/" + fileName, ios::out | ios::binary);
    for (int i = 0; i < NUM_TIMES; ++i) {
        fout.write((char*)&costMatrix[i][0], NUM_SELECT * NUM_SELECT * sizeof(int));
        costMatrix[i].clear();
    }
    costMatrix.clear();
    fout.close();
    auto t6 = chrono::high_resolution_clock::now();
    auto d3 = chrono::duration_cast<chrono::milliseconds>(t6 - t5);
    cout << "File written in " << d3.count() << " ms!" << endl;

    return 0;
}