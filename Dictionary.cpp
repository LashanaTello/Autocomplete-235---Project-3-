/***************************************************************
Title:						Dictionary.cpp
Author:						Lashana Tello
Date Created:			4/3/2017
Class:						Spring 2017, CSCI 235-03, Mon & Wed 5:35pm-6:50pm
Professor:				Aarsh Vora
Purpose:					Project #3
Description:			The Dictionary class method definitions
***************************************************************/

#include "Dictionary.h"
#include "Trie.h"

Dictionary::Dictionary() {
	Trie();
}

Dictionary::Dictionary(std::ifstream& word_list) : word_tree_(word_list) {}

Dictionary::~Dictionary() {
	clear();
}

void Dictionary::clear() {
	word_tree_.clear();
}

int Dictionary::number_of_words() const {
	return word_tree_.number_of_words();
}

bool Dictionary::is_legal_word(std::string& word) {
	return word_tree_.contains(word);
}

void Dictionary::load(std::string& file_name) {
	word_tree_.load(file_name);
}

std::vector<std::string> Dictionary::suggest(std::string& prefix,
																							const int& num_of_words) {
	return word_tree_.autocomplete(prefix, num_of_words);
}
