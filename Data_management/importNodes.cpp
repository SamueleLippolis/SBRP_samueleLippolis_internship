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

// Function to read the new CSV file and return a matrix of strings
std::vector<std::vector<std::string>> readNodesCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    std::vector<std::vector<std::string>> data;
    std::string line;

    // Skip the first line (headers)
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        data.push_back(tokens);
    }

    file.close();
    return data;
}

int main() {
    try {
        std::string nodesPath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_nodes.csv";
        std::vector<std::vector<std::string>> data = readNodesCSV(nodesPath);

        // Print the data
        for (const std::vector<std::string>& row : data) {
            for (const std::string& value : row) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }

        // Print a single empty line
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
