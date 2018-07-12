/***************************************************************
Title:						TrieNode.cpp
Author:						Lashana Tello
Date Created:			4/3/2017
Class:						Spring 2017, CSCI 235-03, Mon & Wed 5:35pm-6:50pm
Professor:				Aarsh Vora
Purpose:					Project #3
Description:			The TrieNode struct contains a map that stores pointers to all
									its children and uses a character as the key. The struct also
									conains a boolean value. This file contains the TrieNode 
									struct and the definition for a default constructor
***************************************************************/

#ifndef __CS235_TRIENODE_H_
#define __CS235_TRIENODE_H_

#include <map>

//	The TrieNode contains a map that uses a character as the key and TrieNode 
//	pointers as the value. It also contains a boolean value that indicates 
//	whether or not this node is the end of a word. TrieNodes are used to 
//	implement a Trie

struct TrieNode {
	//	Map that stores pointers to children nodes
	std::map<char, TrieNode*> children;

	//	Boolean value that indicates end of word
	bool end_of_word;

	TrieNode() {
		end_of_word = false;
	}
};

#endif
