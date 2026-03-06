#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

char score2grade(int score) {
    if (score >= 80) return 'A';
    if (score >= 70) return 'B';
    if (score >= 60) return 'C';
    if (score >= 50) return 'D';
    return 'F';
}

string toUpperStr(string x) {
    string y = x;
    for (unsigned i = 0; i < x.size(); i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ':');
        int score1, score2, score3;
        ss >> score1 >> score2 >> score3;
        int totalScore = score1 + score2 + score3;
        names.push_back(name);
        scores.push_back(totalScore);
        grades.push_back(score2grade(totalScore));
    }
    file.close();
}

void getCommand(string &command, string &key) {
    cout << "Please input your command: " << endl; 
    string input;
    getline(cin, input);
    stringstream ss(input);
    ss >> command;
    ss >> ws;  
    getline(ss, key);
}

void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key) {
    bool found = false;
    key = toUpperStr(key);
    cout << "---------------------------------" << endl;
    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == key) {
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            found = true;
            break; 
        }
    }
    if (!found) {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key) {
    bool found = false;
    char gradeKey = toupper(key[0]);

    cout << "---------------------------------" << endl;
    for (size_t i = 0; i < names.size(); i++) {
        if (grades[i] == gradeKey) {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}

int main() {
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades;
    importDataFromFile(filename, names, scores, grades);

    do {
        string command, key;
        getCommand(command, key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if (command == "EXIT") break;
        else if (command == "GRADE") searchGrade(names, scores, grades, key);
        else if (command == "NAME") searchName(names, scores, grades, key);
        else {
            cout << "---------------------------------" << endl;
            cout << "Invalid command." << endl;
            cout << "---------------------------------" << endl;
        }
    } while (true);

    return 0;
}
