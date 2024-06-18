#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Define a struct to hold the data for each row
struct Edge {
    int source;
    int target;
    double weight;
    double time;
};

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

// Function to read the CSV file and return a vector of Edge structs
std::vector<Edge> readCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    std::vector<Edge> data;
    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() == 4) {
            Edge edge;
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

int main() {
    try {
        std::string filePath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_edges.csv";

        std::vector<Edge> data = readCSV(filePath);

        // Print the data
        for (const Edge& edge : data) {
            std::cout << edge.source << " " << edge.target << " "
                      << edge.weight << " " << edge.time << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
