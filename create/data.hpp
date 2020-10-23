// @author: Asher Desai
// @file: data.h
// defines the Data class, which stores information from CSV format

#pragma once

#include <string>
#include <vector>

using namespace std;

class Data {
private:
    vector<pair<string, vector<string>>> _data;
    vector<pair<string, vector<string>>> _readFile(string filename);
public:
    Data(string filename);
    string getValue(int col, int row) const;
    int getNumRows() const;
};