#include "MovieTree.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Query movies" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Average Rating of movies" << endl;
    cout << "5. Print Movies at Distance k" << endl;
    cout << "6. Quit" << endl;
    cout << "> ";
}

bool isValidInteger(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

bool isValidFloat(const string& str) {
    istringstream iss(str);
    float f;
    return iss >> f && iss.eof();
}

int main() {
    MovieTree* tree = new MovieTree();

    cout << "Enter file name:" << endl;
    string fileName;
    getline(cin, fileName);

    ifstream iFile(fileName);
    if (!iFile.is_open()) {
        cout << "Failed to open the file." << endl;
        delete tree;
        return 1;
    }

    string line;
    while (getline(iFile, line)) {
        if (line.empty()) {
            continue; // Skip blank lines
        }

        stringstream ss(line);
        string field;
        int ranking = -1, year = -1;
        float rating = -1.0f;
        string title;

        // Parse and validate fields
        getline(ss, field, ',');
        if (isValidInteger(field)) {
            ranking = stoi(field);
        } else {
            cerr << "Invalid ranking in line: " << line << endl;
            continue;
        }

        getline(ss, title, ',');
        if (title.empty()) {
            cerr << "Invalid title in line: " << line << endl;
            continue;
        }

        getline(ss, field, ',');
        if (isValidInteger(field)) {
            year = stoi(field);
        } else {
            cerr << "Invalid year in line: " << line << endl;
            continue;
        }

        getline(ss, field, ',');
        if (isValidFloat(field)) {
            rating = stof(field);
        } else {
            cerr << "Invalid rating in line: " << line << endl;
            continue;
        }

        // Add the movie to the tree
        tree->addMovieNode(ranking, title, year, rating);
    }
    iFile.close();

    int input;
    displayMenu();
    cin >> input;

    while (input != 6) {
        cin.ignore(); // Clear leftover newline in the input buffer

        if (input == 1) {
            cout << "Enter title:" << endl;
            string title;
            getline(cin, title);
            tree->findMovie(title);
        } else if (input == 2) {
            cout << "Enter minimum rating:" << endl;
            float rating;
            cin >> rating;
            cout << "Enter minimum year:" << endl;
            int year;
            cin >> year;
            tree->queryMovies(rating, year);
        } else if (input == 3) {
            tree->printMovieInventory();
        } else if (input == 4) {
            tree->averageRating();
        } else if (input == 5) {
            cout << "Enter Level k: " << endl;
            int level;
            cin >> level;
            tree->printLevelNodes(level);
        }

        displayMenu();
        cin >> input;
    }

    cout << "Goodbye!" << endl;
    delete tree;
    return 0;
}
