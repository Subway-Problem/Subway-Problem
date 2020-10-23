// @author: Asher Desai
// @file: edge.cpp
// @description: 

#include <vector>
#include <sstream>
#include <string>

#include "edge.hpp"

using namespace std;

const int ANYTIME = -999999;

vector<string> splitString(const string& s, const char& delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

int secondsPastMidnight(const string& time) {
    vector<string> timeParts = splitString(time, ':');
    return (stoi(timeParts[0]) * 3600) + (stoi(timeParts[1]) * 60) + (stoi(timeParts[2]));
}

Edge::Edge(string origin, string destination, string departureTime, string arrivalTime) {
    if (origin.back() == 'N' || origin.back() == 'S')
        origin.pop_back();
    _originId = origin;
    
    if (destination.back() == 'N' || destination.back() == 'S')
        destination.pop_back();
    _destinationId = destination;

    if (departureTime == "ANYTIME") {
        _departureTime = ANYTIME;
        _arrivalTime = stoi(arrivalTime);
    }
    else {
        _departureTime = secondsPastMidnight(departureTime);
        _arrivalTime = secondsPastMidnight(arrivalTime);
    }
}

Edge::Edge(int originIndex, int destinationIndex, const Edge& other) {
    _originId = other._originId;
    _destinationId = other._destinationId;

    _originIndex = originIndex;
	_destinationIndex = destinationIndex;

	_departureTime = other._departureTime;
	_arrivalTime = other._arrivalTime;


}

int Edge::getDepartureTime(int currentTime) const {
    if ((_departureTime - currentTime) % 86400 >= 0)
        return currentTime + ((_departureTime - currentTime) % 84600);
    else if (_departureTime == ANYTIME)
        return currentTime;
    else
        return currentTime + ((_departureTime - currentTime) % 86400) + 86400;
}

int Edge::getArrivalTime(int currentTime) const {
    if ((_arrivalTime - currentTime) % 86400 >= 0)
        return currentTime + ((_arrivalTime - currentTime) % 86400);
    else if (_departureTime == ANYTIME)
        return currentTime + _arrivalTime;
    else
        return currentTime + ((_arrivalTime - currentTime) % 86400) + 86400;
}

int Edge::getOriginIndex() const {
    return _originIndex;
}

int Edge::getDestinationIndex() const {
    return _destinationIndex;
}

string Edge::getOriginId() const {
    return _originId;
}

string Edge::getDestinationId() const {
    return _destinationId;
}

void Edge::setOriginIndex(int index) {
    _originIndex = index;
}

void Edge::setDestinationIndex(int index) {
    _destinationIndex = index;
}