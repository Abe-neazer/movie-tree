#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->ranking = rank;
    nn->title = t;
    nn->year = y;
    nn->rating = r;
    return nn;
}

void MovieTree::deleteTree(MovieNode* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

MovieTree::MovieTree() {
    root = nullptr;
}

MovieTree::~MovieTree() {
    deleteTree(root);
}

void MovieTree::printMovieInventory() {
    if (root == nullptr) {
        cout << "Tree is Empty. Cannot print." << endl;
    } else {
        printInventoryHelper(root);
    }
}

void MovieTree::printInventoryHelper(MovieNode* node) {
    if (node == nullptr) return;
    printInventoryHelper(node->left);
    cout << "Movie: " << node->title << " (" << node->rating << ")" << endl;
    printInventoryHelper(node->right);
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
    MovieNode* newNode = getMovieNode(ranking, title, year, rating);
    if (root == nullptr) {
        root = newNode;
    } else {
        addMovieHelper(root, newNode);
    }
}

void MovieTree::addMovieHelper(MovieNode* current, MovieNode* newNode) {
    if (newNode->title < current->title) {
        if (current->left == nullptr) {
            current->left = newNode;
        } else {
            addMovieHelper(current->left, newNode);
        }
    } else {
        if (current->right == nullptr) {
            current->right = newNode;
        } else {
            addMovieHelper(current->right, newNode);
        }
    }
}

void MovieTree::findMovie(string title) {
    MovieNode* result = searchMovie(root, title);
    if (result == nullptr) {
        cout << "Movie not found." << endl;
    } else {
        cout << "Movie Info:" << endl;
        cout << "==================" << endl;
        cout << "Ranking:" << result->ranking << endl;
        cout << "Title  :" << result->title << endl;
        cout << "Year   :" << result->year << endl;
        cout << "Rating :" << result->rating << endl;
    }
}

MovieNode* MovieTree::searchMovie(MovieNode* current, string title) {
    if (current == nullptr || current->title == title) return current;
    if (title < current->title) return searchMovie(current->left, title);
    return searchMovie(current->right, title);
}

void MovieTree::queryMovies(float rating, int year) {
    if (root == nullptr) {
        cout << "Tree is Empty. Cannot query Movies." << endl;
        return;
    }
    cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
    queryMoviesHelper(root, rating, year);
}

void MovieTree::queryMoviesHelper(MovieNode* node, float rating, int year) {
    if (node == nullptr) return;
    if (node->rating >= rating && node->year > year) {
        cout << node->title << " (" << node->year << ") " << node->rating << endl;
    }
    queryMoviesHelper(node->left, rating, year);
    queryMoviesHelper(node->right, rating, year);
}

void MovieTree::averageRating() {
    if (root == nullptr) {
        cout << "Average rating:0.0" << endl;
        return;
    }
    float sum = 0.0;
    int count = 0;
    averageRatingHelper(root, sum, count);
    cout << "Average rating:" << (sum / count) << endl;
}

void MovieTree::averageRatingHelper(MovieNode* node, float &sum, int &count) {
    if (node == nullptr) return;
    sum += node->rating;
    count++;
    averageRatingHelper(node->left, sum, count);
    averageRatingHelper(node->right, sum, count);
}

void MovieTree::printLevelNodes(int level) {
    if (level < 0) return;
    printLevelNodesHelper(root, level, 0);
}

void MovieTree::printLevelNodesHelper(MovieNode* node, int targetLevel, int currentLevel) {
    if (node == nullptr) return;
    if (currentLevel == targetLevel) {
        cout << "Movie: " << node->title << " (" << node->rating << ")" << endl;
    } else {
        printLevelNodesHelper(node->left, targetLevel, currentLevel + 1);
        printLevelNodesHelper(node->right, targetLevel, currentLevel + 1);
    }
}
