#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
#include <ctime>
using namespace std;

// Simple structure to hold one joke
struct Joke {
    string setup;
    string punchline;
};

// Reads all the jokes from the text file
vector<Joke> loadJokes(string filename) {
    vector<Joke> jokes;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open the jokes file" << endl;
        return jokes;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find('?');
        if (pos != string::npos) {
            Joke j;
            j.setup = line.substr(0, pos + 1);
            j.punchline = line.substr(pos + 1);

            if (!j.punchline.empty() && j.punchline[0] == ' ') {
                j.punchline = j.punchline.substr(1);
            }
            jokes.push_back(j);
        }
    }
    file.close();
    return jokes;
}

// Checks if the user input contains the key words
bool wantsJoke(string input) {
    // Convert everything to lowercase first
    for (auto& c : input) {
    c = tolower(c);
}
    // Look for the required key words
    bool hasAnother = input.find("another") != string::npos;
    bool hasJoke = input.find("joke") != string::npos;
    bool hasMore = input.find("more") != string::npos;

    return hasAnother || hasJoke || hasMore;
}


// Main function 
int main() {
    srand(time(0));

    vector<Joke> jokes = loadJokes("randomJokes.txt");

    if (jokes.empty()) {
        cout << "No jokes were found." << endl;
        return 1;
    }

    cout << "Type something like \"Alexa, tell me a joke\" to hear a joke" << endl;
    cout << "Type \"quit\" to exit" << endl << endl;

    string input;
    while (true) {
        cout << "> ";
        getline(cin, input);

        // Convert to lowercase 
        string lower = input;
        for (auto& c : lower) {
            if (c >= 'A' && c <= 'Z') {
                c = c + 32;
            }
        }

        if (lower == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }

        if (wantsJoke(input)) {
            // Pick a random joke
            int index = rand() % jokes.size();
            Joke chosen = jokes[index];

            cout << endl << chosen.setup << endl;
            cout << "Press Enter to see the punchline...";
            cin.get();

            cout << chosen.punchline << endl << endl;
        }
        else {
            cout << "Please ask me to tell a joke, or type \"quit\"" << endl;
        }
    }

    return 0;
}