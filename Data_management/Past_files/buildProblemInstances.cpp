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
    double longitude;
    double latitude;
    std::string type;
    int value1;
    int value2;
    int value3;
    int value4;
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
            row.longitude = std::stod(tokens[3]);
            row.latitude = std::stod(tokens[4]);
            row.type = tokens[5];
            row.value1 = std::stoi(tokens[6]);
            row.value2 = std::stoi(tokens[7]);
            row.value3 = std::stoi(tokens[8]);
            row.value4 = std::stoi(tokens[9]);
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
                  << row.longitude << " " << row.latitude << " "
                  << row.type << " " << row.value1 << " " << row.value2 << " "
                  << row.value3 << " " << row.value4 << std::endl;
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

// ----------------- Problem instance class -----------------

// Class to encapsulate problem instance
class ProblemInstance {
public:
    std::vector<std::vector<double>> distancesMatrix;
    std::vector<std::vector<double>> timesMatrix;
    std::vector<NodeDataRow> nodesMatrix;
    std::vector<EdgeDataRow> edgesMatrix;

    ProblemInstance(const std::string& folderPath, 
                    const std::string& distanceMatrixFile,
                    const std::string& timeMatrixFile,
                    const std::string& nodesMatrixFile,
                    const std::string& edgesMatrixFile) 
    {
        distancesMatrix = readSquaredCSV(folderPath + "/" + distanceMatrixFile);
        timesMatrix = readSquaredCSV(folderPath + "/" + timeMatrixFile);
        nodesMatrix = readNodesCSV(folderPath + "/" + nodesMatrixFile);
        edgesMatrix = readEdgesCSV(folderPath + "/" + edgesMatrixFile);
    }

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
};

// ----------------- MAIN -----------------

int main() {
    try {
        // Paths for the matrices
        std::string folderPath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO";
        std::string distanceMatrixFile = "buttrio_distanceMatrix.csv";
        std::string timeMatrixFile = "buttrio_timeMatrix.csv";
        std::string nodesMatrixFile = "buttrio_nodes.csv";
        std::string edgesMatrixFile = "buttrio_edges.csv";

        // Create an instance of ProblemInstance
        ProblemInstance problemInstance(folderPath, distanceMatrixFile, timeMatrixFile, nodesMatrixFile, edgesMatrixFile);

        // Print all the matrices
        problemInstance.printMatrices();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}



