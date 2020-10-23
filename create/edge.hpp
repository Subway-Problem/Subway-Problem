// @author: Asher Desai
// @file: edge.hpp
// @description: 

#pragma once

#include <string>

using namespace std;

class Edge {
private:
    string _originId;
    string _destinationId;

    int _originIndex;
    int _destinationIndex;
    
    int _departureTime;
    int _arrivalTime;

public:
    Edge(string origin, string destination, string departureTime, string arrivalTime);
    Edge(int originIndex, int destinationIndex, const Edge& other);

    int getDepartureTime(int currentTime) const;
    int getArrivalTime(int currentTime) const;

    int getOriginIndex() const;
    int getDestinationIndex() const;

    string getOriginId() const;
    string getDestinationId() const;
    
    void setOriginIndex(int index);
    void setDestinationIndex(int index);
};