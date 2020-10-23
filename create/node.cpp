// @author: Asher Desai
// @file: edge.cpp
// @description: 

#include <string>

#include "node.hpp"

Node::Node(string id) {
    _index = 0;
    _id = id;
}

Node::Node(int index, string id) {
    _index = index;
    _id = id;
}

Node::Node(int index, const Node& other) {
    _index = index;
    _id = other._id;
}

string Node::getId() const {
    return _id;
}

int Node::getIndex() const {
    return _index;
}