// include libraries here
#include <iostream>
#include <string>
#include "graph.h"

#include <cassert>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cctype>

using namespace std;


int main(){

    cityNetworkGraph graph{};       // create an instance of the cityNetworkGraph class that makes the table

    string inputString{};           // entire input command
    string command{};               // just the text command (first part of input string)
    string argumentString{};        // rest of the inputstring (arguments for each command)
    string arguments[4];            // size 4 array to store the arguments from the argument string
    
    // your code goes here...
    while (true){

        getline(cin, inputString);                          // get the input from the inputString that user enters
        int spaceIndex{inputString.find(" ")};              // find the space that separates the command and arguments
        command = inputString.substr(0, spaceIndex);        // parse the command from the inputString (text before the space)
        int inputStringLength = inputString.length();       // find the length of the entire inputString
        argumentString = inputString.substr(spaceIndex + 1, inputStringLength - spaceIndex - 1);    // find the part of the inputString that is the arguments

        if (command == "insert"){                                   // insert function
            istringstream individualArgument(argumentString);       // parse the argumentString to individual arguments
            int index{0};                                           // set the starting index to 0
            while (individualArgument >> arguments[index]){         // for each separate argument, copy it into an index of the arguments array
                index++;
            }
            int arg1{stoi(arguments[0])};                           // store the arguments in each index to int and double according to the respective arguments
            int arg2{stoi(arguments[1])};
            double arg3{stod(arguments[2])};
            double arg4{stod(arguments[3])};

            bool insertResult = graph.insertNode(arg1, arg2, arg3, arg4);      // run the insert Node function and store the result (T/F)

            assert(insertResult == true);               // the result of inserting will always be true
            if (insertResult == true){                  
                cout << "success" << endl;              // print success once inserting is completed
            }

        } else if (command == "load"){                          // load function    
            string lineString{};                                // set a string var for the inidvidual lines of the load file
            ifstream inputFile(argumentString);                 // parse each line in the loading file  
            while (!inputFile.eof()){                           // while we dont' reach the end of the file...
                getline(inputFile, lineString);                 // get each line of inputFile and temp store on the lineString var
                istringstream argumentOnLine(lineString);       // parse the indiivdual arguments on each line
                
                int index{};
                while (argumentOnLine >> arguments[index]){     // for each line, parse in the arguments into the array to use later
                    index++;
                }
                int arg1{stoi(arguments[0])};           // store the string arguments as int or double depending on the respective arguments
                int arg2{stoi(arguments[1])};
                double arg3{stod(arguments[2])};
                double arg4{stod(arguments[3])};

                graph.insertNode(arg1, arg2, arg3, arg4);       // for each line in the file, insert the arguments into the graph
            }
            inputFile.close();      // close the input File once all the lines are parsed and inserted into the graph

            cout << "success" << endl;          // print success once all the arguments in all the line are inserted

        } else if (command == "traffic"){                           // traffic function
            istringstream individualArgument(argumentString);       // parse the argument string into separate arguments
            int index{0};                                       
            while (individualArgument >> arguments[index]){         // iterate through each argument and parse into the array
                index++;
            }
            int arg1{stoi(arguments[0])};               // store the arguments are ints and double for respective arguments
            int arg2{stoi(arguments[1])};
            double arg3{stod(arguments[2])};

            bool implementTrafficResult = graph.implementTraffic(arg1, arg2, arg3);     // implement traffice with the arguments

            if (implementTrafficResult == true){            // if the adjustment factor gets changed, print success
                cout << "success" << endl;
            } else {                                        // if adjustment factor doesn't get updated, print failure
                cout << "failure" << endl;
            }

        } else if (command == "update"){                // update (traffic function but with a large file)
            bool valuesUpdated{false};                  // initialize the variable of having 1+ value update to false
            string lineString{};                        // var to store the lines of the files
            ifstream inputFile(argumentString);         // parse the inputFile to get individual argument strings for each line of the file
            while (!inputFile.eof()){                   // while we're not at the end of the file...
                getline(inputFile, lineString);         // get the inputFile's lines on each line String
                istringstream argumentOnLine(lineString);       // parse the argument strings to get separate arguments
                
                int index{};
                while (argumentOnLine >> arguments[index]){     // iterate through the arguments that we parsed and copy it into array
                    index++;
                }
                int arg1{stoi(arguments[0])};           // store arguments as int and double respectively depending on argument
                int arg2{stoi(arguments[1])};
                double arg3{stod(arguments[2])};

                bool trafficResult = graph.implementTraffic(arg1, arg2, arg3); // implement the traffic for each line of the update file
               
                if (trafficResult == true){         // if the result of any of the updating is true, the valuesUpdated gets changed to true
                    valuesUpdated = true;
                } else {                            // if result of traffic updating is false, don't do anything and go to next iteration
                    continue;
                }
            }
            inputFile.close();                  // once updating done, close the update file
            if (valuesUpdated == true){         // if there was a value udpated, print success
                cout << "success" << endl;
            } else {                            // if no files updated, print failure
                cout << "failure" << endl;
            }

        } else if (command == "print"){                 // print function (prints all adjacent nodes)
            int arg1 = stoi(argumentString);            // since only one argument take the argument string and turn it into an int
            bool printAdjacent = graph.printAdjacentVertices(arg1);     // run and store result of printing the given point

            if (printAdjacent == true){         // if everything printed, don't do anything exit fucntion
                continue;
            } else {                            // if nothing was printed (invalid node) print failure
                cout << "failure" << endl;
            }

        } else if (command == "delete"){                        // delete function (deleting a point)
            int arg1 = stoi(argumentString);                    // only one argument so turn string argument to int
            bool deleteResult = graph.deleteVertex(arg1);       // run and store rseult of deleting the given point

            if (deleteResult == true){              // if deletion was successful, print success
                cout << "success" << endl;
            } else {                                // if deletion not successful, print failure
                cout << "failure" << endl;
            }   
        } else if (command == "path"){                          // shortest path function
            istringstream individualArgument(argumentString);   // we need two arguments so parse argument string for individual arguments
            int index{0};                                       
            while (individualArgument >> arguments[index]){     // iterate through the indiviaul arguments and store it into the arguments array
                index++;
            }
            int arg1{stoi(arguments[0])};               // change the arguments to integers
            int arg2{stoi(arguments[1])};

            bool printShortestPathResult = graph.printShortestPath(arg1, arg2);     // find and store result of the shortest path between the two points
            if (printShortestPathResult == true){               // if a shortest path found, it would have gotten print -> continue to leave function
                continue;   
            } else {                                            // if not shortest path found, print failure
                cout << "failure" << endl;
            }

        } else if (command == "lowest"){                           //lowest weight path function    
            istringstream individualArgument(argumentString);       // parse argument strings to get two arguments
            int index{0};
            while (individualArgument >> arguments[index]){         // iterate through both arguments and temp store in array
                index++;
            }
            int arg1{stoi(arguments[0])};                           // store arguments (strings) as integers
            int arg2{stoi(arguments[1])};

            bool printLowestWeightPathResult = graph.printLowestWeightPath(arg1, arg2);     // find the lowest weight path between the two points (arguments)
            if (printLowestWeightPathResult == true){       // if a lowest path found, it already got printed to exit the loop through "continue"
                continue;
            } else {
                cout << "failure" << endl;                  // if not lowest path found (edge doesn't exit) print failure
            }
            
        } else if (command == "exit"){                  // exit function
            break;                                      // use break to leave the while loop to end the entire run of the code
        }
    }  
}