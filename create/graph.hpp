// @author: Asher Desai
// @file: vgraph.hpp
// @description: defines Graph class, which is a directed graph

#pragma once

#include <vector>
#include <string>

#include "node.hpp"
#include "edge.hpp"
#include "data.hpp"

constexpr int INFIN = numeric_limits<int>::max();
constexpr int UNDEF = -101010101;
constexpr int NUM_NODES = 472;
constexpr int NUM_TIMES = 2880;

class Graph {
private:
    vector<Node> _nodeMap;
    vector<vector<Edge>> _edgeMap;

public:
    Graph();

private:
    vector<Node> _getAllNodes(const Data& nodeData);
    vector<Node> _getPrunedNodes(const vector<Node>& allNodes);
    vector<Node> _buildNodeMap(const vector<Node>& nodes);

    vector<Edge> _getAllEdges(const Data& edgeData, const Data& transferData);
    vector<Edge> _getIndexedEdges(const vector<Node>& nodeMap, const vector<Edge>& allEdges);
    vector<vector<Edge>> _buildEdgeMap(const vector<Node>& nodeMap, const vector<Edge>& allEdges);

public:
    vector<Edge> getEdgesAfterTime(int index, int time) const;
    vector<Edge> getEdgesForNode(int index) const;
    Node getNodeForNode(int index) const;
    
    vector<int> getTimesFromNode(int originIndex, const vector<int>& selectNodes, int originTime) const;
    vector<int> getCostMatrixForTime(const vector<int>& selectNodes, int originTime) const;
};