/***************************************************************
Title:						Dictionary.h
Author:						Lashana Tello
Date Created:			4/3/2017
Class:						Spring 2017, CSCI 235-03, Mon & Wed 5:35pm-6:50pm
Professor:				Aarsh Vora
Purpose:					Project #3
Description:			The Dictionary class abstracts away the Trie object and acts 
									as a wrapper class for the Trie
***************************************************************/

#ifndef __CS235_DICTIONARY_H_
#define __CS235_DICTIONARY_H_

#include "Trie.h"

//	The Dictionary uses a Trie as the underlying data structure to build a
//	dictionary that uses less space and quickly finds words and autocomplete
//	a word given to it by the user

class Dictionary {

 public:
	//	Creates an empty Dictionary
	Dictionary();

	//	Creates a Dictionary given an ifstream
	Dictionary(std::ifstream& word_list);

	//	Deletes Dictionary
	~Dictionary();

	//	Deletes all words in the Dictionary
	void clear();

	//	Returns the number of words in the Dictionary
	int number_of_words() const;

	//	Returns true if word is in the Dictionary
	bool is_legal_word(std::string& word);

	//	Clears the Dictionary and creates a new one given a file containing words
	void load(std::string& file_name);

	//	Returns a vector of size num_of_words that contains all possible word 
	//	suggestions based on the given prefix
	std::vector<std::string> suggest(std::string& prefix,
																		const int& num_of_words);


 private:
	//	A Trie object that stores all the words and the word count
	Trie word_tree_;
};

#endif
