#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Classes.h"
#include "Backend.cpp"

using namespace std;

int main() {
    Pantry pantry;
    pantry.loadFromFile("pantry.txt");
    pantry.print();

    Recipe recipes[50];
    int recipeCount = 0;
    loadRecipes("Recipes.txt", recipes, recipeCount);

    cout << "\nAvailable recipes:\n";
    for (int i = 0; i < recipeCount; ++i) {
        cout << i + 1 << ". " << recipes[i].getName() << endl;
    }

    int choice;
    do {
        cout << "\nEnter the number of the recipe you want to make (1-" << recipeCount << "): ";
        cin >> choice;

        if (choice < 1 || choice > recipeCount) {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice < 1 || choice > recipeCount);

    Recipe selected = recipes[choice - 1];

    cout << "\nChecking if you can make: " << selected.getName() << endl;

    if (selected.canMake(&pantry)) {
        cout <<  "You have all the ingredients to make " << selected.getName() << "!\n";
    }
    else {
        cout << " Sorry, you do not have all the ingredients for " << selected.getName() << ".\n";
    }

    return 0;
}