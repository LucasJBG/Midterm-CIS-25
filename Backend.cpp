#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void loadRecipes(const string& filename, Recipe recipes[], int& count) {
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open recipes file.\n";
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;

        Recipe r;
        r.setName(line.substr(0, colonPos));

        string ingredientsStr = line.substr(colonPos + 1);
        size_t start = 0, end = 0;
        while ((end = ingredientsStr.find(',', start)) != string::npos) {
            r.addIngredient(ingredientsStr.substr(start, end - start));
            start = end + 1;
        }
        r.addIngredient(ingredientsStr.substr(start));

        recipes[count++] = r;
    }
    file.close();
}