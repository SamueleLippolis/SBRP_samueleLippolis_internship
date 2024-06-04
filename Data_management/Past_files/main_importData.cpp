#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "ProblemInstance.h"

int main() {
    // Paths to CSV files
    string distanceMatrixFile = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_distanceMatrix.csv";
    string timeMatrixFile = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_timeMatrix.csv";
    string nodesFile = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_nodes.csv";
    string edgesFile = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_edges.csv";

    // Check if files exist
    if (!ifstream(distanceMatrixFile) || !ifstream(timeMatrixFile) || !ifstream(nodesFile) || !ifstream(edgesFile)) {
        cerr << "Error: One or more input files do not exist." << endl;
        return 1; // Exit with error code
    }

    // Create a problem instance
    ProblemInstance instance(distanceMatrixFile, timeMatrixFile, nodesFile, edgesFile);

    // Access data and perform operations as needed
    // Example:
    const vector<vector<double>>& distanceMatrix = instance.getDistanceMatrix();
    cout << "Distance Matrix:" << endl;
    for (const auto& row : distanceMatrix) {
        for (const auto& value : row) {
            cout << value << "\t";
        }
        cout << endl;
    }

    return 0;
}
