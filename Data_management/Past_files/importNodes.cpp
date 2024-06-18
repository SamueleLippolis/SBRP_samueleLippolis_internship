#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Define a struct to hold the data for each row
struct DataRow {
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

// Function to read the CSV file and return a vector of DataRow structs
std::vector<DataRow> readCSV(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    std::vector<DataRow> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');
        if (tokens.size() == 10) {
            DataRow row;
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

int main() {
    try {
        std::string filePath = "/home/samuele/Desktop/22_internship/SBRP_samueleLippolis_internship/Data_management/BUTTRIO/buttrio_nodes.csv";

        std::vector<DataRow> data = readCSV(filePath);

        // Print the data
        for (const DataRow& row : data) {
            std::cout << row.id1 << " " << row.id2 << " " << row.id3 << " "
                      << row.longitude << " " << row.latitude << " "
                      << row.type << " " << row.value1 << " " << row.value2 << " "
                      << row.value3 << " " << row.value4 << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
