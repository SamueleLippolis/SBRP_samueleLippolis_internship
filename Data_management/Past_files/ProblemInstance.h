#ifndef PROBLEMINSTANCE_H
#define PROBLEMINSTANCE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

// Define a struct to represent node data
struct Node {
    vector<double> pos;
    string locazione;
    string tipologia;
    vector<int> ragazzi;
    int id;
    int label;
};

// Define a struct to represent edge data
struct Edge {
    int source;
    int target;
    double weight;
    double time;
};

// Define a class to represent the problem instance
class ProblemInstance {
private:
    vector<vector<double>> distanceMatrix;
    vector<vector<double>> timeMatrix;
    vector<Node> nodes;
    vector<Edge> edges;

public:
    // Constructor
    ProblemInstance(const string& distanceMatrixFile, const string& timeMatrixFile, const string& nodesFile, const string& edgesFile) {
        // Read distance matrix from CSV
        readDistanceMatrix(distanceMatrixFile);

        // Read time matrix from CSV
        readTimeMatrix(timeMatrixFile);

        // Read nodes from CSV
        readNodes(nodesFile);

        // Read edges from CSV
        readEdges(edgesFile);
    }

void readDistanceMatrix(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening distance matrix file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            if (cell == "nan") {
                row.push_back(std::numeric_limits<double>::quiet_NaN()); // Represent 'nan' as a NaN value
            } else {
                stringstream cell_ss(cell);
                double value;
                if (cell_ss >> value) {
                    row.push_back(value);
                } else {
                    cerr << "Invalid argument: " << cell << endl;
                    row.push_back(std::numeric_limits<double>::quiet_NaN());
                }
            }
        }

        distanceMatrix.push_back(row);
    }

    file.close();
}

void readTimeMatrix(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening time matrix file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            if (cell == "nan") {
                row.push_back(std::numeric_limits<double>::quiet_NaN()); // Represent 'nan' as a NaN value
            } else {
                stringstream cell_ss(cell);
                double value;
                if (cell_ss >> value) {
                    row.push_back(value);
                } else {
                    cerr << "Invalid argument: " << cell << endl;
                    row.push_back(std::numeric_limits<double>::quiet_NaN());
                }
            }
        }

        timeMatrix.push_back(row);
    }

    file.close();
}



    // Member function to read nodes from CSV
    void readNodes(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening nodes file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Skip header line

        while (getline(file, line)) {
            Node node;
            stringstream ss(line);
            string cell;

            getline(ss, cell, ','); // pos
            cell = cell.substr(1, cell.size() - 2); // Remove brackets
            stringstream pos_ss(cell);
            while (getline(pos_ss, cell, ' ')) {
                node.pos.push_back(stod(cell));
            }

            getline(ss, node.locazione, ',');
            getline(ss, node.tipologia, ',');
            
            getline(ss, cell, '['); // ragazzi
            cell = cell.substr(1, cell.size() - 2); // Remove brackets
            stringstream ragazzi_ss(cell);
            while (getline(ragazzi_ss, cell, ',')) {
                node.ragazzi.push_back(stoi(cell));
            }

            getline(ss, cell, ','); // id
            node.id = stoi(cell);

            getline(ss, cell); // label
            node.label = stoi(cell);

            nodes.push_back(node);
        }

        file.close();
    }

    // Helper function to check if a string is a valid double
bool isValidDouble(const string& str) {
    try {
        stod(str);
        return true;
    } catch (const std::invalid_argument& e) {
        return false;
    }
}

// Member function to read edges from CSV
void readEdges(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening edges file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        Edge edge;
        stringstream ss(line);
        string cell;

        getline(ss, cell, ',');
        try {
            edge.source = stoi(cell);
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument for source in line: " << line << endl;
            continue; // Skip this line
        }

        getline(ss, cell, ',');
        try {
            edge.target = stoi(cell);
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument for target in line: " << line << endl;
            continue; // Skip this line
        }

        getline(ss, cell, ',');
        try {
            edge.weight = stod(cell);
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument for weight in line: " << line << endl;
            continue; // Skip this line
        }

        getline(ss, cell);
        try {
            edge.time = stod(cell);
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument for time in line: " << line << endl;
            continue; // Skip this line
        }

        edges.push_back(edge);
    }

    file.close();
}






    // Member functions to access data

    // Getter for distance matrix
    const vector<vector<double>>& getDistanceMatrix() const {
        return distanceMatrix;
    }

    // Getter for time matrix
    const vector<vector<double>>& getTimeMatrix() const {
        return timeMatrix;
    }

    // Getter for nodes
    const vector<Node>& getNodes() const {
        return nodes;
    }

    // Getter for edges
    const vector<Edge>& getEdges() const {
        return edges;
    }
};


#endif