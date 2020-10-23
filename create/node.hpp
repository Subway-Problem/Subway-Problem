// @author: Asher Desai
// @file: node.hpp
// @description: 

#pragma once

#include <vector>
#include <string>

using namespace std;

class Node {
private:
    int _index;
    string _id;
public:
    Node(string id);                        
    Node(int index, string id);
    Node(int index, const Node& other);

    string getId() const;
    int getIndex() const;
};