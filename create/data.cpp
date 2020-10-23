#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "data.hpp"

using namespace std;

Data::Data(string filename) {
    _data = _readFile(filename);
}

vector<pair<string, vector<string>>> Data::_readFile(string filename) {
    vector<pair<string, vector<string>>> data;    
    ifstream ifile(filename);
    if (!ifile.is_open()) throw runtime_error("Could not open file");
    string line, value, colName;

    if (ifile.good()) {
        getline(ifile, line);
        stringstream ss1(line);
        while (getline(ss1, colName, ',')) {
            data.push_back({ colName, vector<string> {} });
        }
    }

    while (getline(ifile, line)) {
        stringstream ss2(line);
        int columnIndex = 0;
        while (getline(ss2, value, ',')) {
            data.at(columnIndex).second.push_back(value);
            columnIndex++;
        }
    }
    
    ifile.close();
    return data;
}

string Data::getValue(int col, int row) const {
    return _data[col].second[row];
}

int Data::getNumRows() const {
    return _data[0].second.size();
}