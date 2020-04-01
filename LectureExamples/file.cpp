#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream jab("jabberwocky");  // constructor
    if (!jab) {
        cerr << "failed to open jabberwocky";
        exit(1);
    }

    string line;
    vector<string> lines;

    while (getline(jab, line)) {
        lines.push_back(line);
    }
    jab.close();

    for (size_t i = 0; i < lines.size(); ++i) {
        for (size_t j = 0; j < lines[i].size(); ++j) {
            cout << lines[i][j] << endl;
        }
    }
}
