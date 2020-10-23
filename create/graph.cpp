// @author: Asher Desai
// @file: vgraph.cpp
// @description: creates the directed graph with nodes and edges; each node has an associated string which is used to look up
// all the edges connected to that node, and consequently which nodes are reasonably accessible. We use dijkstra's
// algorithm to determine the fastest time between any nodes on this graph, and these data are used to create a full
// cost matrix representing the directed graph

#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <limits>
#include <queue>
#include <iostream>

#include "graph.hpp"

using namespace std;

Graph::Graph() {
    // Extracts data from CSV formatted text files, places them into Data objects
    Data nodeData("../gtfs/stops.txt");
    Data edgeData("../gtfs/stop_times.txt");
    Data transferData("../gtfs/transfers.txt");

    // Creates NodeMap from the associated Data
    const vector<Node>& allNodes = _getAllNodes(nodeData);
    const vector<Node>& prunedNodes = _getPrunedNodes(allNodes);
    _nodeMap = _buildNodeMap(prunedNodes);

    // Creates EdgeMap from the associated Data
    const vector<Edge>& allEdges = _getAllEdges(edgeData, transferData);
    const vector<Edge>& indexedEdges = _getIndexedEdges(_nodeMap, allEdges);
    _edgeMap = _buildEdgeMap(_nodeMap, indexedEdges);
}

vector<Node> Graph::_getAllNodes(const Data& nodeData) {
    vector<Node> allNodes;

    // Checks if the Node name in the Data is a child, omitting child nodes
    for (int i = 0; i < nodeData.getNumRows(); ++i) {
        if (nodeData.getValue(0, i).back() != 'N' && nodeData.getValue(0, i).back() != 'S')
            allNodes.emplace_back(nodeData.getValue(0, i));
    }

    return allNodes;
}

vector<Node> Graph::_getPrunedNodes(const vector<Node>& allNodes) {
    unordered_set<string> nodeBlacklist = {
        "S09", "S10", "S11", "S12", "S13",
		"S14", "S15", "S16", "S17", "S18",
		"S19", "S20", "S21", "S22", "S23",
		"S24", "S25", "S26", "S27", "S28",
		"S29", "S30", "S31", "N12", "140",
		"H19", "D13", "D20", "R09"
    };

    vector<Node> prunedNodes;

    // Checks if each Node in the full list is also in the blacklist, omitting those from the 
    // blacklist in the new list of pruned nodes
    for (unsigned i = 0; i < allNodes.size(); ++i) {
        if (nodeBlacklist.count(allNodes[i].getId()) == 0)
            prunedNodes.push_back(allNodes[i]);
    }

    return prunedNodes;
}

vector<Node> Graph::_buildNodeMap(const vector<Node>& nodes) {
    vector<Node> nodeMap;

    for (unsigned i = 0; i < nodes.size(); ++i)
        nodeMap.emplace_back(i, nodes[i]);
    
    return nodeMap;
}

vector<Edge> Graph::_getAllEdges(const Data& edgeData, const Data& transferData) {
    unordered_map<string, string> duplicatePairs = {
        {"D13", "A12"},
		{"D20", "A32"},
		{"R09", "718"}
    };

    vector<Edge> allEdges;
    allEdges.reserve(1000000);
    
    // Adds all transfers as edges
    // Checks if node at either end of edge is a duplicate, switching to the mapped node if so
    for (int i = 0; i < transferData.getNumRows(); ++i) {
        string originNode = transferData.getValue(0, i);
        string destinationNode = transferData.getValue(1, i);

        if (duplicatePairs.count(originNode) == 1)
            originNode = duplicatePairs[originNode];
        if (duplicatePairs.count(destinationNode) == 1)
            destinationNode = duplicatePairs[destinationNode];
        
        allEdges.emplace_back(originNode, destinationNode, "ANYTIME", transferData.getValue(3, i));
    }

    // Adds all weekday connections as edges, taking care to stay on the same train
    // Checks for duplicates as in transfers, removing the direction marker from the node names
    for (int i = 0; i < edgeData.getNumRows() - 1; ++i) {
        size_t foundWeekday = edgeData.getValue(0, i).find("Weekday");

        if (edgeData.getValue(4, i + 1) != "1" && foundWeekday != string::npos) {
            string originNode = edgeData.getValue(3, i);
            originNode.pop_back();
            string destinationNode = edgeData.getValue(3, i + 1);
            destinationNode.pop_back();

            // Checks both ends of edge for a duplicate, switching to the mapped node if so
            if (duplicatePairs.count(originNode) != 0) 
                originNode = duplicatePairs[originNode];
            if (duplicatePairs.count(destinationNode) != 0)
                destinationNode = duplicatePairs[destinationNode];

            allEdges.emplace_back(originNode, destinationNode, edgeData.getValue(2, i), edgeData.getValue(1, i + 1));
        }
    }

    return allEdges;
}

vector<Edge> Graph::_getIndexedEdges(const vector<Node>& nodeMap, const vector<Edge>& allEdges) {
    vector<Edge> indexedEdges;
    indexedEdges.reserve(1000000);

    string originId;
    string destinationId;
    int originIndex = 0;
    int destinationIndex = 0;

    // Converts the edges from referencing nodes by string to referencing them by an integer index
    for (unsigned i = 0; i < allEdges.size(); ++i) {
        originId = allEdges[i].getOriginId();
        destinationId = allEdges[i].getDestinationId();

        for (int j = 0; j < NUM_NODES; ++j) {
            if (nodeMap[j].getId() == originId)
                originIndex = j;
            if (nodeMap[j].getId() == destinationId)
                destinationIndex = j;
        }
        
        indexedEdges.emplace_back(originIndex, destinationIndex, allEdges[i]);
    }

    return indexedEdges;
}

vector<vector<Edge>> Graph::_buildEdgeMap(const vector<Node>& nodeMap, const vector<Edge>& allEdges) {
    vector<vector<Edge>> edgeMap;
    
    for (int i = 0; i < NUM_NODES; ++i) {
        vector<Edge> edgesForNode;

        for (unsigned j = 0; j < allEdges.size(); ++j) {
            if (allEdges[j].getOriginIndex() == nodeMap[i].getIndex())
                edgesForNode.push_back(allEdges[j]);
        }

        edgeMap.push_back(edgesForNode);
    }

    return edgeMap;
}

vector<Edge> Graph::getEdgesAfterTime(int index, int time) const {
    // Returns a vector of all edges accessible at a given time from the specified node

    const vector<Edge>& edgesForNode = _edgeMap[index];
    vector<Edge>edgesAfterTime;
    int wait;

    for (unsigned i = 0; i < edgesForNode.size(); ++i) {
        wait = (edgesForNode[i].getDepartureTime(time) - time);

        if (wait >= 0 && wait < 3600) {
            edgesAfterTime.push_back(edgesForNode[i]);
        }
    }

    return edgesAfterTime;
}

vector<Edge> Graph::getEdgesForNode(int index) const {
    return _edgeMap[index];
}

Node Graph::getNodeForNode(int index) const {
    return _nodeMap[index];
}

vector<int> Graph::getTimesFromNode(int originIndex, const vector<int>& selectNodes, int originTime) const {
    int NUM_SELECT = selectNodes.size();
    vector<int> arrivalTimes(NUM_NODES, INFIN);
    arrivalTimes[originIndex] = 0;
    
    set<pair<int, int>> active;
    active.insert({ 0, originIndex });

    int currentNode, currentTime, neighborNode, timeToNeighbor;

    while (!active.empty()) {
        currentNode = active.begin()->second;
        currentTime = active.begin()->first + originTime;
        active.erase(active.begin());

        const vector<Edge>& edges = getEdgesAfterTime(currentNode, currentTime);

        for (unsigned i = 0; i < edges.size(); ++i) {
            neighborNode = edges[i].getDestinationIndex();
            timeToNeighbor = edges[i].getArrivalTime(currentTime) - currentTime;

            if (arrivalTimes[neighborNode] > arrivalTimes[currentNode] + timeToNeighbor) {
                active.erase({ arrivalTimes[neighborNode], neighborNode });
                arrivalTimes[neighborNode] = arrivalTimes[currentNode] + timeToNeighbor;
                active.insert({ arrivalTimes[neighborNode], neighborNode });
            }
        }
    }

    vector<int> selectArrivalTimes(NUM_SELECT, 0);
    for (int i = 0; i < NUM_SELECT; ++i)
        selectArrivalTimes[i] = arrivalTimes[selectNodes[i]];

    return selectArrivalTimes;

    return arrivalTimes;
}

vector<int> Graph::getCostMatrixForTime(const vector<int>& selectNodes, int originTime) const {
    int NUM_SELECT = selectNodes.size();
    vector<int> timesMatrix(NUM_SELECT * NUM_SELECT, 0);
    vector<int> arrivalTimes;
    for (int i = 0; i < NUM_SELECT; ++i) {
        arrivalTimes = getTimesFromNode(selectNodes[i], selectNodes, originTime);
        for (int j = 0; j < NUM_SELECT; ++j) {
            timesMatrix[(i * NUM_SELECT) + j] = arrivalTimes[j];
        }
    }

    return timesMatrix;
}