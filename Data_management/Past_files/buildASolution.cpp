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

// Struct to represent a Route
// Struct to represent a Route
struct Route {
    int busIndex;
    std::string routeDescription;
    std::vector<int> visitedNodes; // New field to store visited nodes
};

std::vector<Route> buildRoutes(const ProblemInstance& problemInstance) {
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

    // If no bus stops found, handle error
    if (busStopNodeIndices.empty()) {
        throw std::runtime_error("No bus stops found.");
    }

    // Create routes for each bus stop
    int routeNumber = 1;

    for (int busStopIndex : busStopNodeIndices) {
        std::string routeDescription = "Route " + std::to_string(routeNumber) + ": Depot -> Bus Stop " + std::to_string(busStopIndex) + " -> ";
        std::vector<int> visitedNodes;

        // Add nodes needed for this bus stop
        visitedNodes.push_back(depotNodeIndex); // Start from depot
        visitedNodes.push_back(busStopIndex); // Visit the bus stop itself

        // Add clusters needed for this bus stop
        bool clustersVisited = false;
        for (size_t clusterIndex = 0; clusterIndex < clusters[busStopIndex - 1].size(); ++clusterIndex) {
            if (clusters[busStopIndex - 1][clusterIndex] > 0) {
                visitedNodes.push_back(clusterIndex + 1); // Cluster indices are 1-based
                routeDescription += "Cluster " + std::to_string(clusterIndex + 1) + " -> ";
                clustersVisited = true;
            }
        }

        // If no clusters visited, remove " -> Clusters: End" from routeDescription
        if (!clustersVisited) {
            routeDescription.erase(routeDescription.find_last_of("->"), std::string::npos);
        } else {
            // Remove the last " -> " from routeDescription
            routeDescription.erase(routeDescription.length() - 4, 4);
        }

        routes.push_back({ routeNumber, routeDescription, visitedNodes });
        ++routeNumber;
    }

    return routes;
}








// ----------------- MAIN -----------------


int main() {
    std::vector<int> busesCapacities = {30,25, 20, 20, 20, 20, 20, 20, 20, 20};
    try {
        int numberOfBuses = 10;
        // Paths for the matrices
        std::string folderPath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO";
        std::string distanceMatrixFile = "buttrio_distanceMatrix.csv";
        std::string timeMatrixFile = "buttrio_timeMatrix.csv";
        std::string nodesMatrixFile = "buttrio_nodes.csv";
        std::string edgesMatrixFile = "buttrio_edges.csv";

        // Create an instance of ProblemInstance
        ProblemInstance problemInstance(folderPath, distanceMatrixFile, timeMatrixFile, nodesMatrixFile, edgesMatrixFile, numberOfBuses, busesCapacities);


        // Build the routes
        std::vector<Route> routes = buildRoutes(problemInstance);

        // Print each route
        for (const auto& route : routes) {
            std::cout << "Bus " << route.busIndex << " - " << route.routeDescription << std::endl;
            std::cout << "Visited Nodes: ";
            for (int node : route.visitedNodes) {
                std::cout << node << " ";
            }
            std::cout << std::endl << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }



    return 0;
}



