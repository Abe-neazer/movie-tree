#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP
#include <string>

using namespace std;

struct MovieNode {
    int ranking;
    string title;
    int year;
    float rating;
    MovieNode* left = nullptr;
    MovieNode* right = nullptr;
};

class MovieTree {
private:
    MovieNode* root;

    void deleteTree(MovieNode* node);
    void printInventoryHelper(MovieNode* node);
    void addMovieHelper(MovieNode* current, MovieNode* newNode);
    MovieNode* searchMovie(MovieNode* current, string title);
    void queryMoviesHelper(MovieNode* node, float rating, int year);
    void averageRatingHelper(MovieNode* node, float &sum, int &count);
    void printLevelNodesHelper(MovieNode* node, int targetLevel, int currentLevel);

public:
    MovieTree();
    ~MovieTree();
    void printMovieInventory();
    void addMovieNode(int ranking, string title, int year, float rating);
    void findMovie(string title);
    void queryMovies(float rating, int year);
    void averageRating();
    void printLevelNodes(int level);
};

#endif
