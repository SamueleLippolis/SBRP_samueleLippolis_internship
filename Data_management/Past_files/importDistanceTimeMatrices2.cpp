#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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

// Function to read a matrix CSV file and return a matrix of doubles
std::vector<std::vector<double>> readMatrixCSV(const std::string& filePath) {
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

// Function to print a matrix
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const std::vector<double>& row : matrix) {
        for (double value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    try {
        std::string distanceMatrixPath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_distanceMatrix.csv";
        std::string timeMatrixPath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_timeMatrix.csv";

        std::vector<std::vector<double>> distanceMatrix = readMatrixCSV(distanceMatrixPath);
        std::vector<std::vector<double>> timeMatrix = readMatrixCSV(timeMatrixPath);

        // Print the distanceMatrix
        std::cout << "Distance Matrix:" << std::endl;
        printMatrix(distanceMatrix);

        // Print an empty line
        std::cout << std::endl;

        // Print the timeMatrix
        std::cout << "Time Matrix:" << std::endl;
        printMatrix(timeMatrix);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
