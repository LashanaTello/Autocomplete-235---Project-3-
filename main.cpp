#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"
using namespace std;

int main() {
	ifstream word_file;
	string word;
	int num_of_suggestions;
	vector<string> suggestions;

	string name_of_file;
	cout << "Enter the name of the word file." << endl;
	cin >> name_of_file;
	word_file.open(name_of_file.c_str());
	Dictionary dictionary(word_file);
	word_file.close();
	bool word_contains_num = false;

	while (1) {
		cout << "Enter a string to be autocompleted:" << endl;
		cin >> word;
		for (unsigned int i = 0; i < word.length(); ++i) {
			if (isdigit(word[i])) {
				word_contains_num = true;
				break;
			}
		}
		cout << "Enter number of suggestions:" << endl;
		cin >> num_of_suggestions;
		while (cin.fail()) {
			cout << "ERROR. Enter a valid number:" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> num_of_suggestions;
		}

		if (word_contains_num == true) {
			cout << "ERROR. Autocomplete failed." << endl;
		} else {
			suggestions = dictionary.suggest(word, num_of_suggestions);
			if (suggestions.empty()) {
				cout << "No suggestions!" << endl;
			} else {
				cout << "Suggestions:" << endl;
				for (unsigned int i = 0; i < suggestions.size(); ++i) {
					cout << suggestions[i] << endl;
				}
			}
		}
		word_contains_num = false;
	}

	return 0;
}
