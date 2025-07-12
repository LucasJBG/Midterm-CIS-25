#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_INGREDIENTS = 100;

class Pantry {
private:
    string* ingredients;
    int size;

    // Helper: binary search
    bool binarySearch(const string& item) {
        int left = 0, right = size - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (ingredients[mid] == item)
                return true;
            else if (ingredients[mid] < item)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return false;
    }

public:
    Pantry() {
        ingredients = new string[MAX_INGREDIENTS];
        size = 0;
    }

    ~Pantry() {
        delete[] ingredients;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Failed to open pantry file.\n";
            exit(1);
        }
        string line;
        while (getline(file, line)) {
            ingredients[size++] = line;
        }
        file.close();

        // Sort for binary search
        sort(ingredients, ingredients + size);
    }

    bool hasIngredient(const string& item) {
        return binarySearch(item);
    }

    void print() {
        cout << "Your Pantry Ingredients:\n";
        for (int i = 0; i < size; ++i) {
            cout << "- " << ingredients[i] << endl;
        }
    }
};;;;

class Recipe {
private:
    string name;
    string ingredients[MAX_INGREDIENTS];
    int ingredientCount;

public:
    Recipe() {
        ingredientCount = 0;
    }

    void setName(const string& n) {
        name = n;
    }

    void addIngredient(const string& ing) {
        ingredients[ingredientCount++] = ing;
    }

    bool canMake(Pantry* pantry) {
        for (int i = 0; i < ingredientCount; ++i) {
            if (!pantry->hasIngredient(ingredients[i])) {
                return false;
            }
        }
        return true;
    }

    string getName() {
        return name;
    }
};

