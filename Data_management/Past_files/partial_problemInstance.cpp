#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include "ProblemInstance.h"

using namespace std;

// Struct to represent an edge
struct Edge {
    int source;
    int target;
    double weight;
    double time;
};

// Function to parse CSV file containing edge information
vector<Edge> parseEdgesCSV(const string& filename) {
    vector<Edge> edges;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open edge file " << filename << endl;
        return edges;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        Edge edge;
        char comma;
        if (!(iss >> edge.source >> comma >> edge.target >> comma >> edge.weight >> comma >> edge.time)) {
            cerr << "Error: Invalid edge format in file " << filename << endl;
            continue;
        }
        edges.push_back(edge);
    }
    return edges;
}

// Function to parse CSV file containing distance matrix
vector<vector<double>> parseDistanceMatrixCSV(const string& filename) {
    vector<vector<double>> distanceMatrix;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open distance matrix file " << filename << endl;
        return distanceMatrix;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        vector<double> row;
        string cell;
        while (getline(iss, cell, ',')) {
            if (cell == "nan") {
                row.push_back(std::numeric_limits<double>::quiet_NaN()); // Represent 'nan' as a NaN value
            } else {
                row.push_back(stod(cell));
            }
        }
        distanceMatrix.push_back(row);
    }
    return distanceMatrix;
}

int main() {
    // Paths to CSV files
    string distanceMatrixFile = "path/to/distanceMatrix.csv";
    string edgesFile = "path/to/edges.csv";

    // Parse CSV files
    vector<vector<double>> distanceMatrix = parseDistanceMatrixCSV(distanceMatrixFile);
    vector<Edge> edges = parseEdgesCSV(edgesFile);

    // Create a problem instance
    ProblemInstance instance(distanceMatrix, edges);

    // Access data and perform operations as needed
    // Example:
    const vector<vector<double>>& parsedDistanceMatrix = instance.getDistanceMatrix();
    // Do something with parsedDistanceMatrix

    return 0;
}
