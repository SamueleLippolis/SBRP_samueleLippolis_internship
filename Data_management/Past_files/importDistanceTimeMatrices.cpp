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
// It can be used for both the distanceMatrix and the timeMatrix 
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

int main() {
    try {
        std::string distanceMaterixPath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_distanceMatrix.csv";
        std::string timeMatrixPath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_timeMatrix.csv";

        std::vector<std::vector<double>> distanceMatrix = readMatrixCSV(distanceMaterixPath);
        std::vector<std::vector<double>> timeMatrix = readMatrixCSV(timeMatrixPath);

        // Print the distanceMatrix
        for (const std::vector<double>& row : distanceMatrix) {
            for (double value : row) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }

        // Print an empty line
        std::cout << std::endl;


        // Print the timeMatrix
        for (const std::vector<double>& row : timeMatrix) {
            for (double value : row) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
