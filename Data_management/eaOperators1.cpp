/**
 * @file importData.cpp
 * @brief This file contains the code for importing data from external sources.
 * 
 * This file includes the necessary libraries for importing data, such as:
 * - iostream: Provides basic input/output operations.
 * - fstream: Provides file input/output operations.
 * - vector: Provides dynamic array functionality.
 * - string: Provides string manipulation operations.
 * - sstream: Provides string stream functionality.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath> // For std::isnan
#include <algorithm> // For std::next_permutation
#include <random> // For std::mt19937
#include <ctime> // For std::time
#include <iomanip>   // For std::fixed, std::setprecision
#include <numeric> // for std::accumulate


// ----------------- For all matrices -----------------

// Function to split a string by a delimiter and return a vector of substrings
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


// ----------------- Distance and Time matrices -----------------

// Function to read a matrix CSV file and return a matrix of doubles
std::vector<std::vector<double>> readSquaredCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    std::vector<std::vector<double>> matrix;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        std::vector<double> row;
        for (const std::string& token : tokens) {
            row.push_back(std::stod(token));
        }
        matrix.push_back(row);
    }

    file.close();
    return matrix;
}

// Function to print a squared matrix
void printSquaredMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const std::vector<double>& row : matrix) {
        for (double value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

// ----------------- Node matrix -----------------

// Define a struct to hold the data for each row
struct NodeDataRow {
    int id1;
    int id2;
    int id3;
    double latitude;
    double longitude;
    std::string type;
    int children_to_cluster_1; // Number of children to cluster 1
    int children_to_cluster_2; // Number of children to cluster 2
    int children_to_cluster_3; // Number of children to cluster 3
    int children_to_cluster_4; // Number of children to cluster 4
};

// Function to read the CSV file and return a vector of DataRow structs
std::vector<NodeDataRow> readNodesCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    std::vector<NodeDataRow> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() == 10) {
            NodeDataRow row;
            row.id1 = std::stoi(tokens[0]);
            row.id2 = std::stoi(tokens[1]);
            row.id3 = std::stoi(tokens[2]);
            row.latitude = std::stod(tokens[3]);
            row.longitude = std::stod(tokens[4]);
            row.type = tokens[5];
            row.children_to_cluster_1 = std::stoi(tokens[6]);
            row.children_to_cluster_2 = std::stoi(tokens[7]);
            row.children_to_cluster_3 = std::stoi(tokens[8]);
            row.children_to_cluster_4 = std::stoi(tokens[9]);
            data.push_back(row);
        }
    }

    file.close();
    return data;
}

// Function to print the data matrix
void printNodesMatrix(const std::vector<NodeDataRow>& dataMatrix) {
    for (const NodeDataRow& row : dataMatrix) {
        std::cout << row.id1 << " " << row.id2 << " " << row.id3 << " "
                  << row.latitude << " " << row.longitude << " "
                  << row.type << " " << row.children_to_cluster_1 << " " << row.children_to_cluster_2 << " "
                  << row.children_to_cluster_3 << " " << row.children_to_cluster_4 << std::endl;
    }
}

// ----------------- Edges matrix -----------------

// Define a struct to hold the data for each row
struct EdgeDataRow {
    int source;
    int target;
    double weight;
    double time;
};

// Function to read the CSV file and return a vector of Edge structs
std::vector<EdgeDataRow> readEdgesCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    std::vector<EdgeDataRow> data;
    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() == 4) {
            EdgeDataRow edge;
            edge.source = std::stoi(tokens[0]);
            edge.target = std::stoi(tokens[1]);
            edge.weight = std::stod(tokens[2]);
            edge.time = std::stod(tokens[3]);
            data.push_back(edge);
        }
    }

    file.close();
    return data;
}


// Function to print the edge matrix
void printEdgesMatrix(const std::vector<EdgeDataRow>& edgeMatrix) {
    for (const EdgeDataRow& edge : edgeMatrix) {
        std::cout << edge.source << " " << edge.target << " "
                  << edge.weight << " " << edge.time << std::endl;
    }
}

// ----------------- Write on csv functions -----------------

// Function to write a matrix to a CSV file
void writeSquaredCSV(const std::string& filePath, const std::vector<std::vector<double>>& matrix) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file for writing");
    }

    for (const auto& row : matrix) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i != row.size() - 1) {
                file << ",";
            }
        }
        file << std::endl;
    }

    file.close();
}

// Function to write the NodeDataRow vector to a CSV file
void writeNodesCSV(const std::string& filePath, const std::vector<NodeDataRow>& dataMatrix) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file for writing");
    }

    for (const auto& row : dataMatrix) {
        file << row.id1 << "," << row.id2 << "," << row.id3 << ","
             << row.latitude << "," << row.longitude << ","
             << row.type << "," << row.children_to_cluster_1 << "," << row.children_to_cluster_2 << ","
             << row.children_to_cluster_3 << "," << row.children_to_cluster_4 << std::endl;
    }

    file.close();
}

// Function to write the EdgeDataRow vector to a CSV file
void writeEdgesCSV(const std::string& filePath, const std::vector<EdgeDataRow>& edgeMatrix) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file for writing");
    }

    file << "source,target,weight,time" << std::endl; // Write header line

    for (const auto& edge : edgeMatrix) {
        file << edge.source << "," << edge.target << ","
             << edge.weight << "," << edge.time << std::endl;
    }

    file.close();
}

// ----------------- Problem instance class -----------------

// Class to encapsulate problem instance
class ProblemInstance {
public:
    std::vector<std::vector<double>> distancesMatrix;
    std::vector<std::vector<double>> timesMatrix;
    std::vector<NodeDataRow> nodesMatrix;
    std::vector<EdgeDataRow> edgesMatrix;
    int numberOfBuses;  // New variable: number of available buses
    std::vector<int> busCapacities;  // New variable: capacity of each bus

    ProblemInstance(const std::string& folderPath, 
                    const std::string& distanceMatrixFile,
                    const std::string& timeMatrixFile,
                    const std::string& nodesMatrixFile,
                    const std::string& edgesMatrixFile,
                    int numBuses,
                    const std::vector<int>& capacities) 
    {
        distancesMatrix = readSquaredCSV(folderPath + "/" + distanceMatrixFile);
        timesMatrix = readSquaredCSV(folderPath + "/" + timeMatrixFile);
        nodesMatrix = readNodesCSV(folderPath + "/" + nodesMatrixFile);
        edgesMatrix = readEdgesCSV(folderPath + "/" + edgesMatrixFile);
        numberOfBuses = numBuses;
        busCapacities = capacities;
    }

    // Method to print all the matrices
    void printMatrices() const {
        std::cout << "Distance Matrix:" << std::endl;
        printSquaredMatrix(distancesMatrix);

        std::cout << std::endl; // Print an empty line

        std::cout << "Time Matrix:" << std::endl;
        printSquaredMatrix(timesMatrix);

        std::cout << std::endl; // Print an empty line

        std::cout << "Nodes Matrix:" << std::endl;
        printNodesMatrix(nodesMatrix);

        std::cout << std::endl; // Print an empty line

        std::cout << "Edges Matrix:" << std::endl;
        printEdgesMatrix(edgesMatrix);
    }

    // Getter and setter methods for distancesMatrix
    const std::vector<std::vector<double>>& getDistancesMatrix() const {
        return distancesMatrix;
    }

    void setDistancesMatrix(const std::vector<std::vector<double>>& newMatrix) {
        distancesMatrix = newMatrix;
    }

    // Getter and setter methods for timesMatrix
    const std::vector<std::vector<double>>& getTimesMatrix() const {
        return timesMatrix;
    }

    void setTimesMatrix(const std::vector<std::vector<double>>& newMatrix) {
        timesMatrix = newMatrix;
    }

    // Getter and setter methods for nodesMatrix
    const std::vector<NodeDataRow>& getNodesMatrix() const {
        return nodesMatrix;
    }

    void setNodesMatrix(const std::vector<NodeDataRow>& newData) {
        nodesMatrix = newData;
    }

    // Getter and setter methods for edgesMatrix
    const std::vector<EdgeDataRow>& getEdgesMatrix() const {
        return edgesMatrix;
    }

    void setEdgesMatrix(const std::vector<EdgeDataRow>& newData) {
        edgesMatrix = newData;
    }

    // Additional methods to write matrices to CSV files
    void writeDistancesMatrix(const std::string& filePath) const {
        writeSquaredCSV(filePath, distancesMatrix);
    }

    void writeTimesMatrix(const std::string& filePath) const {
        writeSquaredCSV(filePath, timesMatrix);
    }

    void writeNodesMatrix(const std::string& filePath) const {
        writeNodesCSV(filePath, nodesMatrix);
    }

    void writeEdgesMatrix(const std::string& filePath) const {
        writeEdgesCSV(filePath, edgesMatrix);
    }

    // Getter method for numberOfBuses
    int getNumberOfBuses() const {
        return numberOfBuses;
    }

    // Setter method for numberOfBuses
    void setNumberOfBuses(int numBuses) {
        numberOfBuses = numBuses;
    }

    // Getter method for busesCapacity
    const std::vector<int>& getBusesCapacity() const {
        return busCapacities;
    }

    // Setter method for busesCapacity
    void setBusesCapacity(const std::vector<int>& capacities) {
        busCapacities = capacities;
    }
    

};

// ----------------- Initialization -----------------


// Given a node ID, find the sum of children to clusters
int sumChildrenToClusters(const std::vector<NodeDataRow>& nodesMatrix, int nodeId) {
    for (const auto& node : nodesMatrix) {
        if (node.id1 == nodeId || node.id2 == nodeId || node.id3 == nodeId) {
            return node.children_to_cluster_1 + 
                   node.children_to_cluster_2 + 
                   node.children_to_cluster_3 + 
                   node.children_to_cluster_4;
        }
    }
    // If the node is not found, you might want to handle it
    // For example, return -1 or throw an exception
    return -1; // Indicating the node was not found
}

// Struct to represent a Route
struct Route {
    int busIndex;
    std::vector<int> visitedNodes; // Stores visited nodes
    
    // New fields to store the number of children to each cluster
    int childrenToCluster1;
    int childrenToCluster2;
    int childrenToCluster3;
    int childrenToCluster4;

    // Constructor to initialize the variables
    Route(int index) 
        : busIndex(index), 
          childrenToCluster1(0),
          childrenToCluster2(0),
          childrenToCluster3(0),
          childrenToCluster4(0) {}
};

// Print the route
void printRoute(const Route& route) {

    std::cout << "\nBus " << route.busIndex << std::endl;
    std::cout << "Visited Nodes: ";
    for (int node : route.visitedNodes) {
        std::cout << node << " ";
    }
    std::cout << "\nChildren to cluster 1: " << route.childrenToCluster1 << std::endl;
    std::cout << "Children to cluster 2: " << route.childrenToCluster2 << std::endl;
    std::cout << "Children to cluster 3: " << route.childrenToCluster3 << std::endl;
    std::cout << "Children to cluster 4: " << route.childrenToCluster4 << std::endl;
}

// Function to count the total number of children taken up by a bus in a route
int countTotalChildrenToClusters(const Route& route) {
    return route.childrenToCluster1 + route.childrenToCluster2 + route.childrenToCluster3 + route.childrenToCluster4;
}

// Function to find the integer ID of the node where type = "cluster"
int findClusterID(const std::vector<NodeDataRow>& nodesMatrix, int x) {
    int count = 0; // Counter to track how many "cluster" types have been found
    int size = nodesMatrix.size();

    for (int i = 0; i < size; ++i) {
        if (nodesMatrix[i].type == "cluster") {
            ++count;
            if (count == x) {
                return nodesMatrix[i].id1; // Return id1 of the x-th "cluster" type row
            }
        }
    }

    // If x is greater than the number of "cluster" types found, return -1 or handle as needed
    return -1; // Or any suitable error code indicating x-th "cluster" type not found
}

// Function to find all cluster IDs
std::vector<int> findAllClusterIDs(const std::vector<NodeDataRow>& nodesMatrix) {
    std::vector<int> clusterIDs;

    for (const auto& node : nodesMatrix) {
        if (node.type == "cluster") {
            clusterIDs.push_back(node.id1);
        }
    }

    return clusterIDs;
}


// Function to build routes ot the following kind: depot -> bus stop -> cluster(s)
// Moreover, it returns unserved nodes (if the number of buses is not enough to serve all bus stops)
std::pair<std::vector<Route>, std::vector<int>> buildRoutes(const ProblemInstance& problemInstance, const std::vector<int>& busesCapacities) {
    std::vector<Route> routes;

    // Access nodes from the instance
    const auto& nodes = problemInstance.getNodesMatrix();

    // Find depot and all bus stops
    int depotNodeIndex = -1;
    std::vector<int> busStopNodeIndices;
    std::vector<std::vector<int>> clusters; // To store children counts for each cluster

    // Assuming nodesMatrix structure based on provided data
    for (const auto& node : nodes) {
        if (node.type == "deposito") {
            depotNodeIndex = node.id1;
        } else if (node.type == "fermata") {
            busStopNodeIndices.push_back(node.id1);
            std::vector<int> childrenCounts;
            childrenCounts.push_back(node.children_to_cluster_1);
            childrenCounts.push_back(node.children_to_cluster_2);
            childrenCounts.push_back(node.children_to_cluster_3);
            childrenCounts.push_back(node.children_to_cluster_4);
            clusters.push_back(childrenCounts);
        }
    }

    // If no bus stops found, return empty routes and unserved nodes
    if (busStopNodeIndices.empty()) {
        return {routes, busStopNodeIndices};
    }

    int busIndex = 1; // Start bus index from 1
    std::vector<int> unservedBusStops;

    for (int busStopIndex : busStopNodeIndices) {
        int totalChildren = clusters[busStopIndex - 1][0] + clusters[busStopIndex - 1][1] + clusters[busStopIndex - 1][2] + clusters[busStopIndex - 1][3];
        int currentCapacity = 0;
        bool served = false;

        // Assign buses to this bus stop until the capacity constraint is satisfied
        while (currentCapacity < totalChildren && busIndex <= busesCapacities.size()) {
            int remainingCapacity = busesCapacities[busIndex - 1] - currentCapacity;
            Route route(busIndex);

            // Add nodes needed for this bus stop
            std::vector<int> visitedNodes;
            visitedNodes.push_back(depotNodeIndex); // Start from depot
            visitedNodes.push_back(busStopIndex); // Visit the bus stop itself

            // Add clusters needed for this bus stop
            for (size_t clusterIndex = 0; clusterIndex < clusters[busStopIndex - 1].size(); ++clusterIndex) {
                if (clusters[busStopIndex - 1][clusterIndex] > 0) {
                    // Find the node ID corresponding to the cluster index
                    int clusterNodeId = -1;
                    // Assuming nodesMatrix has node ID corresponding to cluster indices
                    for (const auto& node : nodes) {
                        if (node.id1 == clusterIndex + 1) { // Assuming cluster indices are 1-based
                            clusterNodeId = node.id1;
                            break;
                        }
                    }
                    if (clusterNodeId != -1) {
                        int realClusterNodeId = findClusterID(problemInstance.getNodesMatrix(), clusterNodeId);
                        visitedNodes.push_back(realClusterNodeId);
                    }
                }
            }

            route.visitedNodes = visitedNodes;

            // Distribute children to clusters according to bus capacity
            for (size_t clusterIndex = 0; clusterIndex < clusters[busStopIndex - 1].size(); ++clusterIndex) {
                int childrenCount = clusters[busStopIndex - 1][clusterIndex];
                if (childrenCount > 0) {
                    if (childrenCount <= remainingCapacity) {
                        // Entire cluster fits into this bus
                        switch (clusterIndex) {
                            case 0:
                                route.childrenToCluster1 = childrenCount;
                                break;
                            case 1:
                                route.childrenToCluster2 = childrenCount;
                                break;
                            case 2:
                                route.childrenToCluster3 = childrenCount;
                                break;
                            case 3:
                                route.childrenToCluster4 = childrenCount;
                                break;
                            default:
                                break;
                        }
                        currentCapacity += childrenCount;
                    } else {
                        // Distribute as much as possible to this cluster
                        switch (clusterIndex) {
                            case 0:
                                route.childrenToCluster1 = remainingCapacity;
                                break;
                            case 1:
                                route.childrenToCluster2 = remainingCapacity;
                                break;
                            case 2:
                                route.childrenToCluster3 = remainingCapacity;
                                break;
                            case 3:
                                route.childrenToCluster4 = remainingCapacity;
                                break;
                            default:
                                break;
                        }
                        currentCapacity += remainingCapacity;
                        // Remaining children go to the next bus
                        clusters[busStopIndex - 1][clusterIndex] -= remainingCapacity;
                    }
                }
            }

            routes.push_back(route);
            busIndex++;
            served = true;
        }

        // Check if the bus stop was served
        if (!served) {
            unservedBusStops.push_back(busStopIndex);
        }
    }

    // Return routes and unserved bus stops
    return {routes, unservedBusStops};
}


// Function to check if adding a node's children to a route is within bus capacity
bool canAddNodeToRoute(const std::vector<NodeDataRow>& nodesMatrix, const Route& route, int nodeId, const std::vector<int>& busesCapacities) {
    int busCapacity = busesCapacities[route.busIndex - 1]; // Assuming busIndex is 1-based

    for (const auto& node : nodesMatrix) {
        if (node.id1 == nodeId || node.id2 == nodeId || node.id3 == nodeId) {
            int routeTotalChildren = route.childrenToCluster1 + route.childrenToCluster2 + route.childrenToCluster3 + route.childrenToCluster4; 
            int nodeTotalChildren = node.children_to_cluster_1 + node.children_to_cluster_2 + node.children_to_cluster_3 + node.children_to_cluster_4;

            std::cout << "\nNode selected " << nodeId << std::endl;
            std::cout << "Bus selected " << route.busIndex << std::endl;
            std::cout << "Bus capacity: " << busCapacity << std::endl;
            std::cout << "Route total children: " << routeTotalChildren << std::endl;
            std::cout << "Node total children: " << nodeTotalChildren << std::endl;
            std::cout << std::endl;

            return routeTotalChildren + nodeTotalChildren <= busCapacity;
        }
    }

    // If the node is not found, return false
    return false;
}



// Function to calculate the total distance based on visited nodes and distance matrix
double calculateTotalDistance(const std::vector<int>& visitedNodes, const std::vector<std::vector<double>>& distanceMatrix) {
    double totalDistance = 0.0;

    for (size_t i = 0; i < visitedNodes.size() - 1; ++i) {
        int fromNode = visitedNodes[i];
        int toNode = visitedNodes[i + 1];
        totalDistance += distanceMatrix[fromNode+1][toNode+1]; // Assuming distanceMatrix is 1-based
    }

    return totalDistance;
}

// Function to generate permutations of elements
void generatePermutations(const std::vector<int>& elements, std::vector<std::vector<int>>& permutations) {
    std::vector<int> temp = elements;

    // Sort the elements in ascending order initially
    std::sort(temp.begin(), temp.end());

    do {
        permutations.push_back(temp);
    } while (std::next_permutation(temp.begin(), temp.end()));
}

// Function to find the route with the smallest total distance
void findOptimalRoute(Route& route, const std::vector<int>& clusterIDs, const std::vector<std::vector<double>>& distanceMatrix) {
    // Extract visited nodes from route
    std::vector<int>& visitedNodes = route.visitedNodes;

    // Split visitedNodes into depot, bus stops, and clusters
    int depot = visitedNodes[0];
    std::vector<int> busStops;
    std::vector<int> clusters;

    for (size_t i = 1; i < visitedNodes.size(); ++i) {
        if (std::find(clusterIDs.begin(), clusterIDs.end(), visitedNodes[i]) != clusterIDs.end()) {
            clusters.push_back(visitedNodes[i]);
        } else {
            busStops.push_back(visitedNodes[i]);
        }
    }

    // Generate permutations of bus stops and clusters
    std::vector<std::vector<int>> busStopPermutations;
    std::vector<std::vector<int>> clusterPermutations;

    // Ensure all permutations of bus stops and clusters are generated
    generatePermutations(busStops, busStopPermutations);
    generatePermutations(clusters, clusterPermutations);

    // Combine permutations of bus stops and clusters and find the route with the smallest distance
    std::vector<int> optimalRoute;
    double minDistance = std::numeric_limits<double>::max();

    int permutationCounter = 0; // Counter for permutations

    for (const auto& busStopPerm : busStopPermutations) {
        for (const auto& clusterPerm : clusterPermutations) {
            std::vector<int> currentRoute = { depot };
            currentRoute.insert(currentRoute.end(), busStopPerm.begin(), busStopPerm.end());
            currentRoute.insert(currentRoute.end(), clusterPerm.begin(), clusterPerm.end());
            double distance = calculateTotalDistance(currentRoute, distanceMatrix);

            // Print permutation and its distance
            std::cout << "\nPermutation " << ++permutationCounter << ": ";
            for (size_t i = 0; i < currentRoute.size(); ++i) {
                std::cout << currentRoute[i];
                if (i < currentRoute.size() - 1) std::cout << " -> ";
            }
            std::cout << ", Distance: " << std::fixed << std::setprecision(2) << distance << std::endl;

            // Update route's visitedNodes if current route has smaller distance
            if (distance < minDistance) {
                minDistance = distance;
                route.visitedNodes = currentRoute;
            }
        }
    }
    std::cout << std::endl;
}



// Function to select a random route from a vector of routes
Route getRandomRoute(const std::vector<Route>& routes) {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    // Generate a random index in the range [0, routes.size()-1]
    int randomIndex = std::rand() % routes.size();
    
    // Return the route at the random index
    return routes[randomIndex];
}


// Function to add a node to a route after the depot
void addNodeToRoute(Route& route, int nodeId, const std::vector<NodeDataRow>& nodesMatrix) {
    // Find the node with the given nodeId in the nodes matrix
    auto it = std::find_if(nodesMatrix.begin(), nodesMatrix.end(), 
                           [nodeId](const NodeDataRow& node) { return node.id1 == nodeId; });

    if (it == nodesMatrix.end()) {
        std::cerr << "Node with ID " << nodeId << " not found in the nodes matrix.\n";
        return;
    }

    const NodeDataRow& node = *it;

    // Insert the node after the depot (which is the first element in visitedNodes)
    if (route.visitedNodes.size() > 1) {
        route.visitedNodes.insert(route.visitedNodes.begin() + 1, node.id1);
    } else {
        route.visitedNodes.push_back(node.id1);
    }

    // Check and add clusters if needed
    if (node.children_to_cluster_1 > 0 && route.childrenToCluster1 == 0) {
        int clusterID = findClusterID(nodesMatrix, 1);
        if (clusterID != -1) {
            route.visitedNodes.push_back(clusterID);
        }
    }
    if (node.children_to_cluster_2 > 0 && route.childrenToCluster2 == 0) {
        int clusterID = findClusterID(nodesMatrix, 2);
        if (clusterID != -1) {
            route.visitedNodes.push_back(clusterID);
        }
    }
    if (node.children_to_cluster_3 > 0 && route.childrenToCluster3 == 0) {
        int clusterID = findClusterID(nodesMatrix, 3);
        if (clusterID != -1) {
            route.visitedNodes.push_back(clusterID);
        }
    }
    if (node.children_to_cluster_4 > 0 && route.childrenToCluster4 == 0) {
        int clusterID = findClusterID(nodesMatrix, 4);
        if (clusterID != -1) {
            route.visitedNodes.push_back(clusterID);
        }
    }

    // Update the children counts for the route
    route.childrenToCluster1 += node.children_to_cluster_1;
    route.childrenToCluster2 += node.children_to_cluster_2;
    route.childrenToCluster3 += node.children_to_cluster_3;
    route.childrenToCluster4 += node.children_to_cluster_4;
}

 // Function to add a node to a random route from routes and find its optimal configuration
static void addNodeAndFindOptimal(std::vector<Route>& routes, int nodeId, const std::vector<NodeDataRow>& nodesMatrix,
                                  const std::vector<int>& busesCapacities, const std::vector<int>& clusterIDs,
                                  const std::vector<std::vector<double>>& distanceMatrix)
                                  {
    bool canAdd = false;
    // Loop until we find a route where we can add the node within bus capacity
    while (!canAdd) {
        // Select a random index in the range [0, routes.size()-1]
        int randomIndex = std::rand() % routes.size();

        // Check if we can add the node's children to rPrime within bus capacity
        canAdd = canAddNodeToRoute(nodesMatrix, routes[randomIndex], nodeId, busesCapacities);
        // If we can add the node, update rPrime's visitedNodes and find its optimal configuration
        if (canAdd) {
            addNodeToRoute(routes[randomIndex], nodeId, nodesMatrix);
            findOptimalRoute(routes[randomIndex], clusterIDs, distanceMatrix);
        }
    }
}


// Function to add a list of nodes to routes and find their optimal configurations
void addNodesAndFindOptimal(std::vector<Route>& routes, const std::vector<int>& nodeIds, const std::vector<NodeDataRow>& nodesMatrix,
                            const std::vector<int>& busesCapacities, const std::vector<int>& clusterIDs,
                            const std::vector<std::vector<double>>& distanceMatrix) {
    for (int nodeId : nodeIds) {
        bool canAdd = false;
        // Loop until we find a route where we can add the node within bus capacity
        while (!canAdd) {
            // Select a random index in the range [0, routes.size()-1]
            int randomIndex = std::rand() % routes.size();

            // Check if we can add the node's children to rPrime within bus capacity
            canAdd = canAddNodeToRoute(nodesMatrix, routes[randomIndex], nodeId, busesCapacities);
            // If we can add the node, update rPrime's visitedNodes and find its optimal configuration
            if (canAdd) {
                addNodeToRoute(routes[randomIndex], nodeId, nodesMatrix);
                findOptimalRoute(routes[randomIndex], clusterIDs, distanceMatrix);
            }
        }
    }
}

// Function to add a list of nodes to routes and find their optimal configurations (giving less pr do be chosen to larger routes)
void addNodesUsingProbabilityAndFindOptimal(std::vector<Route>& routes, const std::vector<int>& nodeIds, const std::vector<NodeDataRow>& nodesMatrix,
                            const std::vector<int>& busesCapacities, const std::vector<int>& clusterIDs,
                            const std::vector<std::vector<double>>& distanceMatrix) {

    // Calculate inverse of visitedNodes sizes
    // E.g. [3, 4, 5] -> [1/4, 1/5, 1/6]
    std::vector<double> inverseVisitedNodesSizes(routes.size()); // Initialize with zeros a vector of size routes.size()
    for (size_t i = 0; i < routes.size(); ++i) { // Loop over routes
        inverseVisitedNodesSizes[i] = 1.0 / (routes[i].visitedNodes.size() + 1); // Calculate inverse of size of visitedNodes (adding 1 to avoid division by zero)
    }

    // Normalize inverseVisitedNodesSizes to form a probability distribution
    // E.g. 0.1, 0.2, 0.3 -> 0.1/0.6, 0.2/0.6, 0.3/0.6 -> 0.1667, 0.3333, 0.5 (which sum is 1.0)
    double totalInverse = std::accumulate(inverseVisitedNodesSizes.begin(), inverseVisitedNodesSizes.end(), 0.0); // Calculate the sum of inverseVisitedNodesSizes
    std::transform(inverseVisitedNodesSizes.begin(), inverseVisitedNodesSizes.end(), inverseVisitedNodesSizes.begin(), 
                   [totalInverse](double inv) { return inv / totalInverse; }); // Normalize inverseVisitedNodesSizes

    for (int nodeId : nodeIds) {
        bool canAdd = false;
        // Loop until we find a route where we can add the node within bus capacity
        while (!canAdd) {
            // Randomly select a route index based on inverseVisitedNodesSizes
            double randVal = static_cast<double>(std::rand()) / RAND_MAX; // Generate a random value in the range [0, 1)
            double cumulativeProb = 0.0;
            size_t randomIndex = 0;
            for (; randomIndex < routes.size(); ++randomIndex) { // Loop over routes
                cumulativeProb += inverseVisitedNodesSizes[randomIndex]; // Add the probability of the current route
                if (randVal <= cumulativeProb) { // Check if the random value is less than or equal to the cumulative probability
                    break;
                }
            }

            // Check if we can add the node's children to routes[randomIndex] within bus capacity
            canAdd = canAddNodeToRoute(nodesMatrix, routes[randomIndex], nodeId, busesCapacities);
            // If we can add the node, update routes[randomIndex]'s visitedNodes and find its optimal configuration
            if (canAdd) {
                addNodeToRoute(routes[randomIndex], nodeId, nodesMatrix);
                findOptimalRoute(routes[randomIndex], clusterIDs, distanceMatrix);
            }
        }
    }
}






// ----------------- MAIN -----------------


int main() {
    // Seed the random number generator once at the beginning of the program
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create an instance of ProblemInstance
    std::vector<int> busesCapacities = {10, 10, 20, 20, 20, 20, 20, 20, 20, 20};
    int numberOfBuses = busesCapacities.size();

    std::cout << "Number of buses: " << numberOfBuses << std::endl;
    for (int i = 0; i < numberOfBuses; ++i) {
        std::cout << "Bus " << i + 1 << " capacity: " << busesCapacities[i] << std::endl;
    }
    
    std::string folderPath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO";
    std::string distanceMatrixFile = "buttrio_distanceMatrix.csv";
    std::string timeMatrixFile = "buttrio_timeMatrix.csv";
    std::string nodesMatrixFile = "buttrio_nodes.csv";
    std::string edgesMatrixFile = "buttrio_edges.csv";
    
    ProblemInstance problemInstance(folderPath, distanceMatrixFile, timeMatrixFile, nodesMatrixFile, edgesMatrixFile, numberOfBuses, busesCapacities);

    // Build routes and get unserved nodes, print the routes and unserved nodes
    auto [routes, unservedNodes] = buildRoutes(problemInstance, problemInstance.busCapacities);

    for (const Route& route : routes) {
        printRoute(route);
    }
    
    if (!unservedNodes.empty()) {
        std::cout << "Unserved Bus Stops:" << std::endl;
        for (int node : unservedNodes) {
            std::cout << "- Bus Stop " << node << std::endl;
        }
    }

   // add unserved nodes to routes 
   addNodesUsingProbabilityAndFindOptimal(
    routes,
    unservedNodes,
    problemInstance.getNodesMatrix(), 
    problemInstance.getBusesCapacity(), 
    findAllClusterIDs(problemInstance.getNodesMatrix()),
    problemInstance.getDistancesMatrix()
    );

    // Print the updated routes
    for (const Route& route : routes) {
        printRoute(route);
    }

    return 0;
}



