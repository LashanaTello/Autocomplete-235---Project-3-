/***************************************************************
Title:						Trie.h
Author:						Lashana Tello
Date Created:			4/3/2017
Class:						Spring 2017, CSCI 235-03, Mon & Wed 5:35pm-6:50pm
Professor:				Aarsh Vora
Purpose:					Project #3
Description:			The Trie class abstracts away the pointer to the root of the
									Trie which contains the first letter of all the words in the 
									Trie and the number of words in the Trie
***************************************************************/

#ifndef __CS235_TRIE_H_
#define __CS235_TRIE_H_

#include <fstream>
#include <vector>
#include <string>
#include "TrieNode.cpp"

//	The Trie class uses TrieNodes to store each letter of a word and pointers
//	to each letter's possible next letter. The root of the Trie stores the
//	first letter of each word in the Trie and the private member variable 
//	word_count_ stores the number of words in the Trie. Many words have the
//	same prefix, so using a Trie minimizes the space required to store an entire
//	dictionary. In this Trie, the end of a word in indicated with either a
//	boolean value inside the TrieNode or if a TrieNode is null. A Trie can also
//	be used to quickly predict the rest of any word that someone types

class Trie {
 public:
	//	Creates a Trie by making root_ point to a new TrieNode and setting 
	//	word_count_ to 0
	Trie();

	//	Creates a Trie object given an ifstream to a word file and inserts all
	//	the words from the file into the Trie
	Trie(std::ifstream& word_list);

	//	Deletes a Trie
	~Trie();

	//	Changes a word into all lowercase letters and removes all punctuation
	//	from the word
	void make_lowercase(std::string& word);

	//	Returns the number of nodes a Trie object contains
	int get_number_of_nodes() const;

	//	Returns the number of words in a Trie
	int number_of_words() const;

	//	Sets word_count_ to 0, clears the map in all of the nodes and deletes all
	//	nodes in the Trie except root_
	void clear();

	//	Calls the make_lowercase method to make word all lowercase and adds word
	//	to Trie. Returns true if word is added or false if the word already exists
	//	in Trie
	bool insert(std::string& word);

	//	Returns true if word was succesfully removed from Trie
	bool remove(std::string& word);

	//	Returns true if word is found in Trie
	bool contains(std::string& word);

	//	Returns a vector of size num_of_words that contains all possible word 
	//	suggestions based on the given prefix
	std::vector<std::string> autocomplete(std::string& prefix,
																				 const int& num_of_words);

	//	Removes all the words in the Trie and creates an ifstream that reads all
	//	words from the given file and adds those words to the Trie
	void load(std::string& file_name);


 private:
	//	Pointer to the node that contains the first letter of every word in Trie
	TrieNode* root_;

	//	Stores the number of words in the Trie
	int word_count_;

	//	Helper function that returns the number of nodes in the Trie given a node
	int get_number_of_nodes(TrieNode* node, int& count) const;

	int get_number_of_words(TrieNode* node, int& count) const;

	//	A helper function that returns an int that indicates whether or not the
	//	word was removed from the Trie. The position parameter keeps track of the
	//	position we are at in word
	int remove(TrieNode*& node, const std::string& word, int& length_of_word,
						 int position);

	//	Returns a pointer to the node of the last letter in the prefix if the
	//	prefix exists in the Trie. If the prefix does not exist, returns nullptr
	TrieNode* find_prefix(std::string& prefix);

	//	Deletes all nodes in the Trie except the root and empties	root_'s map
	void delete_tree(TrieNode*& node);

};


#endif
