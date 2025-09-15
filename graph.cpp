#include "graph.h"
#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <iomanip>

#include <cassert>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cmath>

using namespace std;

// implement classes' member functions here...

graphNode::graphNode(double d = 0.0, double s= 0.0, double A = 1.0){ // initilaize the default values when a new graph node (edge) is created
    intersectionDistance = d;
    speedLimit = s;
    adjustmentFactor = A;
}
graphNode::~graphNode(){}

cityNetworkGraph::cityNetworkGraph(){};
cityNetworkGraph::~cityNetworkGraph(){};

double graphNode::findweight() {
    return (intersectionDistance)/(speedLimit * adjustmentFactor);      // finds the weight of the edge between two points
}

bool cityNetworkGraph::checkValidNodeAndEdge(int pointOne, int pointTwo){
    if ((trafficGraph.find(pointOne) != trafficGraph.end()) && (trafficGraph.find(pointTwo) != trafficGraph.end())){        // checks taht points one and two exits in the grpah
        if (trafficGraph[pointOne].find(pointTwo) != trafficGraph[pointOne].end()){     // checks that point two to point one has an edge
            return true;        // return true is edge exists and both nodes exits
        } else {
            return false;       // return false if both nodes exist but there's no edge between them
        }
    } else {
        return false;           // return false if that either point one or two doesn't exist
    } 
}

bool cityNetworkGraph::checkValidNode(int pointToCheck){
    if (trafficGraph.find(pointToCheck) != trafficGraph.end()){     // checks that the point given is inside the table
        return true;        // return true if it exists
    } else {
        return false;       // return false if it doesn't exist
    }
}

bool cityNetworkGraph::insertNode(int pointOne, int pointTwo, double distance, double speedLimit){

    // START DEBUGGING
    // cout << trafficGraph[pointOne][pointTwo].intersectionDistance << endl;
    // cout << trafficGraph[pointTwo][pointOne].intersectionDistance << endl;
    // cout << trafficGraph[pointTwo][pointOne].speedLimit << endl;
    // cout << trafficGraph[pointOne][pointTwo].speedLimit << endl;
    // END DEBUGGING

    trafficGraph[pointOne][pointTwo].intersectionDistance = distance;       // insert the distance and speed between point one and two in both directions
    trafficGraph[pointTwo][pointOne].intersectionDistance = distance;
    trafficGraph[pointOne][pointTwo].speedLimit = speedLimit;
    trafficGraph[pointTwo][pointOne].speedLimit = speedLimit;

    /* NOTE
        here we are able to take advantage of the way that STL works as it checks whether at the specific point there is a value
        if there's not value, it will create the value and set the two values that we want
        if there is a value at that point, it will simply update the values
    */

    return true;                // return true once the value is inserted or updated    
}

bool cityNetworkGraph::implementTraffic(int pointOne, int pointTwo, double adjustmentFactor){
    if (checkValidNodeAndEdge(pointOne, pointTwo) == true){     // checks that there is a edge between the two points and that both points actually exist
            
            // START DEBUGGING -> CHECK IF ADJUSTMENT FACTOR IS UPDATED TO NEW VALUE OR KEEPS SAME
            // cout << trafficGraph[pointOne][pointTwo].adjustmentFactor << endl;
            // cout << trafficGraph[pointTwo][pointOne].adjustmentFactor << endl;
            // END DEBUGGING

            // *NOTE* as long as adjustmentFactor is a valid double between 0.0 and 1.0 (even if it's the same as the one already present),
            //        we will return true and print "success" since we are technically updating it either way (updating with diff num vs updating with same value)
            
            trafficGraph[pointOne][pointTwo].adjustmentFactor = adjustmentFactor;       // update the adjustmentfactor fo the edge in both directions in the table
            trafficGraph[pointTwo][pointOne].adjustmentFactor = adjustmentFactor;
            return true;        // if the adjustmentfacotr (traffic) gets updated, then return true
    } else {
        
        // START DEBUGGING
        // cout << "reaches this point (0)" << end;
        // END DEBUGGING

        return false;           // if there is not edge between the two points or if one of the two points don't exist
    }
}

bool cityNetworkGraph::printAdjacentVertices(int pointToPrint){     // prints all adjacent points to the given point
    if (checkValidNode(pointToPrint) == true){          // checks that the point we want actually exists
        // int index{}; -> used for debugging
        for (auto node: trafficGraph[pointToPrint]){    // iterates through all the nodes in the column of the point we want to print adjacent points for
            int adjacentNodeInt = node.first;           // store the adjacent node int value in adjacentNodeInt Var
            cout << adjacentNodeInt;             // for each node in the column of the table corresponding to the point, print that value
            cout << " ";
            
            // index++; -> used for debugging
        }

        // START DEBUGGING
        // cout << "there are " << index << " adjacent points" << endl;
        // END DEBUGGING

        cout << endl;                                   // once all the nodes printed, create a new line for the next function
        return true;                                    // return true if the adjacent points are printed
    } else {

        // START DEBUGGING
        // cout << "node we want to print isn't valid" << endl;
        // END DEBUGGING

        return false;                                   // if the point we want to use doesn't exist return false
    }
}

bool cityNetworkGraph::deleteVertex(int pointToDelete){     // delete a given point
    if (checkValidNode(pointToDelete) == true){             // if the point exists...
        // int index{}; -> used for debugging
        for(auto node: trafficGraph[pointToDelete]){        // iterate through all the nodes in the column of the table corresponding to the point we want to delete
            int nodeIntToDelete = node.first;               // temp store the node int value
            trafficGraph[nodeIntToDelete].erase(pointToDelete);     // erase the edges from the point to the "adjacent points"
            // index++;  
        }

        // START DEBUGGING
        // cout << "gone through this loop" << index << "times and deleted those points" << endl;
        // END BUGGING

        trafficGraph.erase(pointToDelete);          // delete the point itself
        return true;                                // once everything deleted, return true
    } else {

        // START DEBUGGING
        // cout << "point we want to delete isn't valid" << endl;
        // END DEBUGGING

        return false;                               // if point never existed, then return false
    }       
}

pair<double, string> cityNetworkGraph::dijkstrasFormula(int startingPoint, int endingPoint){
    if ((checkValidNode(startingPoint) == true) && (checkValidNode(endingPoint) == true)){      // Checks if the given points are valid nodes
        priority_queue <pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> toDo;    // create a priority queue to implement dijkstras Formula
        unordered_set <int> visitedNodes;       // create a set
        pair<double, string> currentPath;       // create a pair to store the current Path
        
        string startingPointString = to_string(startingPoint);
        toDo.push({0, startingPointString + " "});       // push the starting point onto the priority queue

        while (isPriorityQueueEmpty(toDo) == false){        // while the priority queue isn't emtpy...
            currentPath = toDo.top();                       // set the current path to be the top of the priority queue
            toDo.pop();                                     // pop the top of the priority queue
            

            int currentPathLength = currentPath.second.length();            // find the length of the current path string
            string currentPathNoTrailingSpace = currentPath.second.substr(0, currentPathLength - 1);    // get rid of the trailing space to let us find the last space (space between text)

            int lastSpaceIndex = currentPathNoTrailingSpace.find_last_of(" ");  // find the last space (space in between points)
            if (lastSpaceIndex == -1){      // if there is only one number, then the last space index will be -1 and break the code
                lastSpaceIndex = 0;         // set the last space index to 0 to not break the code
            }
            string currentNodeString = currentPathNoTrailingSpace.substr(lastSpaceIndex, currentPathLength - lastSpaceIndex - 1);   // find the current node (most recently added one)
            int currentNode = stoi(currentNodeString);          // change the current (mot recent) node to an integer to use to compare with the endingPoint we want

            if (currentNode == endingPoint){        // if you've reached your end point...

                // START DEBUGGING
                // cout << "reaches this point (1)" << end;
                // END DEBUGGING
                return currentPath;                 // return the currentPath string
            }
            
            if (visitedNodes.find(currentNode) != visitedNodes.end()){   // if the current node you're at has been visited, continue to next iteration
                continue;
            } else {
                
                // START DEBUGGING
                // cout << "reaches this point (2)" << end;
                // END DEBUGGING

                visitedNodes.insert(currentNode);       // if it hasn't been visited, add it to the visitedNodes set
            }

            for (auto edge: trafficGraph[currentNode]){     // iterate through the adjacent nodes to the point
                double weightToAdd = currentPath.first + edge.second.findweight();      // find the weight of the edge between the two points
                if (isinf(weightToAdd)){        // if the edge weight is inifite (bloced bc of traffic) continue to next iteration of for loop
                    // START DEBUGGING
                    // cout << "weight we want to add is inifinte" << endl;
                    // END DEBUGGING
                    continue;   
                }
                string currentPathString = currentPath.second + to_string(edge.first) + " ";  // if weight isn't inifinite, add the current path string to the entire string for total path
                toDo.push({weightToAdd, currentPathString});        // not push that point that we just iterate to the priority queue and continue to next iteration 
            }
        }

        // START DEBUGGING
        // cout << "reaches this point (3)" << end;
        // END DEBUGGING

        return {-99, "fail"};       // at the end if we never reach the destination point, return some arbitrary unreasonable value that we check later
    } else {

        // START DEBUGGING
        // cout << "priority queue is empty" << endl;
        // END DEBUGGING

        return {-99, "fail"};       // if 1+ of the points didn't exists return aribtrary failure value to test for later
    }
}

bool cityNetworkGraph::isPriorityQueueEmpty(priority_queue <pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq){
    if (pq.empty() == true){        // check if the priority queue is empty if it is, return true
        return true;
    } else {                        // if pq isn't empty, return false
        return false;
    }
}

bool cityNetworkGraph::printShortestPath(int startPoint, int destinationPoint){
    pair<double, string> dijkstrasResult = dijkstrasFormula(startPoint, destinationPoint); // find the dijkstra's shortest path
    if (dijkstrasResult.first == -99 || dijkstrasResult.second == "fail"){  // if dijkstras failed, then you return false

        // START DEBUGGING
        // cout << "reaches this point (4)" << end;
        // END DEBUGGING

        return false;
    } else {
        assert(dijkstrasResult.first >= 0);     // if dijkstras didn't fail, we must have gotten a positive weight value

        // START DEBUGGING
        // cout << "valid result from dijkstras formula" << endl;
        // END DEBUGGING

        cout << dijkstrasResult.second << endl;                   // once all printed, make a new line
        return true;
    }
}

bool cityNetworkGraph::printLowestWeightPath(int startingPoint, int destinationPoint){
    pair<double, string> dijkstrasResult = dijkstrasFormula(startingPoint, destinationPoint);       // get the resulting node from dijkstra
    if (dijkstrasResult.first == -99 || dijkstrasResult.second == "fail"){        // if shortest path couldn't be found then return false
        
        // START DEBUGGING
        // cout << "reaches this point (5)" << end;
        // END DEBUGGING

        return false;
    } else {

        // START DEBUGGING
        // cout << "shortest path weight from dijkstras formula is is a valid value" << endl;
        // END DEBUGGING

        double lowestWeight = dijkstrasResult.first;        // store the lowest weight path in a temp storage var
        cout << fixed << showpoint;                     // code provided from piazza to display the lowest weight with 3 decimal precision
        cout << setprecision(3);
        cout << lowestWeight << endl;               // print out the lowest weight path value wiht 3 decimal precision
        return true;                                // return true to indicate that lowest weight was printed
    }
}