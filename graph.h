#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;


class graphNode {           // used to store information needed for each edge
    public:
        graphNode(double d, double s, double A);        // constructor that initializes the distance, speedlimit, and adjustment factor
        ~graphNode();                                   // destructor (not used)
        double findweight();                            // takes the d,s, and A and finds the weight at that edge (when needed)

        double intersectionDistance;        // distance between two given points
        double speedLimit;                  // speed limit at the edge between the two points
        double adjustmentFactor;            // adjustment factor (essentially how much traffic there is)
        
};



class cityNetworkGraph {        // Graph class that stores the member and helper functions and makes the hash table
    public:
        cityNetworkGraph();     // constructor and destructor for cityNetworkGraph (not used)
        ~cityNetworkGraph();

        bool insertNode(int pointOne, int pointTwo, double distance, double speedLimit);        // inserts points into table
        // bool loadDataset(string filename);       -> don't need this function because we implement it in driver.cpp with insertNode function
        bool implementTraffic(int pointOne, int pointTwo, double adjustmentFactor);             // changes the adjustment factor for the edge between two points
        // bool updateTraffic(string filename);     -> don't need this function because we implement it in driver.cpp with implementTraffic function
        bool printAdjacentVertices(int pointToPrint);       // prints all adjacent vertices between two points
        bool deleteVertex(int pointToDelete);               // deletes a given vertex (point)
        bool printShortestPath(int startPoint, int destinationPoint);           // uses dijkstrasFormula to find the shortest path between 2 points and prints that path (if it exists)
        bool printLowestWeightPath(int startingPoint, int destinationPoint);    // use dijkstrasFormula to find the lowest weighted path between 2 points and prints that value (if it exists)
        
        pair <double, string> dijkstrasFormula(int startingPoint, int endingPoint);     // formula used to find shortest (and lowest weight) path between two points

    private:
        unordered_map <int, unordered_map <int, graphNode>> trafficGraph;   // create a hash map that stores the graphNodes so to store information for the edges between any 2 poitns in the table

        bool checkValidNodeAndEdge(int pointOne, int pointTwo);     // checks to see if the there is a valid edge between two points
        bool checkValidNode(int pointToCheck);                      // checks to see if the given point exists inside the graph
        bool isPriorityQueueEmpty(priority_queue <pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq); // checks to see if the given priority queue is empty or not
};