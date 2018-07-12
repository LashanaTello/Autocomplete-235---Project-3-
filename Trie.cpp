/***************************************************************
Title:						Trie.cpp
Author:						Lashana Tello
Date Created:			4/3/2017
Class:						Spring 2017, CSCI 235-03, Mon & Wed 5:35pm-6:50pm
Professor:				Aarsh Vora
Purpose:					Project #3
Description:			Contains the definitions of the Trie class methods
***************************************************************/

#include <iostream>
#include <utility>
#include <map>
#include <queue>
#include "Trie.h"

Trie::Trie() {
	root_ = new TrieNode;
	word_count_ = 0;
}

Trie::Trie(std::ifstream& word_list) {
	root_ = new TrieNode;
	word_count_ = 0;
	std::string word;
	while (word_list >> word) {
		insert(word);
	}
}

Trie::~Trie() {
	clear();
}

void Trie::make_lowercase(std::string& word) {
  for (unsigned int i = 0; i < word.length(); ++i) {
    if (isupper(word[i])) {
      word[i] = tolower(word[i]);
    } else if (ispunct(word[i])) {
      word.erase(i, 1);
			//	after erasing the punctuation, check if the letter that replaced the
			//	puctuation is uppercase
			if (isupper(word[i])) {
      	word[i] = tolower(word[i]);
			}
    }
  }
}

int Trie::get_number_of_nodes() const {
	int count = 0;
	return get_number_of_nodes(root_, count) - 1;	//	to exclude the root
}

int Trie::number_of_words() const {
	return word_count_;
}

void Trie::clear() {
	word_count_ = 0;
	delete_tree(root_);
}

bool Trie::insert(std::string& word) {
	make_lowercase(word);
	TrieNode* traverse = root_;
	TrieNode* new_node;
	bool word_already_exists = true;

	for (unsigned int i = 0; i < word.length(); ++i) {
		if (traverse->children.count(word[i]) == 0) {
			if (i != word.length() - 1) {
				new_node = new TrieNode;
			} else {
				new_node = nullptr;	//	the end of a word is a nullptr or end_of_word
														//	is true. When you reach the end of word, put a
														//	nullptr in the last letter's position in the map
			}
			traverse->children[word[i]] = new_node;
			traverse = new_node;
			word_already_exists = false;
		} else {
			//	if you reach a nullptr and you're not at the end of word, it means a
			//	prefix of word exists in the Trie. That nullptr must be changed to a
			//	new TrieNode so we can continue inserting word. We also must set the
			//	new node's end_of_word to true so we don't lose a word in the Trie
			if (traverse->children[word[i]] == nullptr && i != word.length() - 1) {
				traverse->children[word[i]] = new TrieNode;
				traverse = traverse->children[word[i]];
				traverse->end_of_word = true;
			} else {
				traverse = traverse->children[word[i]];
			}
		}
	}
	if (word_already_exists == true) {
		if (traverse == nullptr || traverse->end_of_word == true) {
			return false;
		} else if (traverse->end_of_word == false) {
			traverse->end_of_word = true;	//	word is a prefix of another word in Trie
			++word_count_;								//	but word didn't officially exist
			return true;
		}
	}
	++word_count_;
	return true;
}

bool Trie::remove(std::string& word) {
	if (root_ == nullptr || root_->children.empty()) {
		return false;
	}
	int position = 0;
	make_lowercase(word);
	int word_length = word.length();
	int result = remove(root_, word, word_length, position);
	if (result == 0) {
		return false;
	} else {
		return true;
	}
}

bool Trie::contains(std::string& word) {
	if (root_ == nullptr || root_->children.empty()) {
		return false;
	}

	make_lowercase(word);
	TrieNode* traverse = root_;
	for (unsigned int i = 0; i < word.length(); ++i) {
		if (traverse == nullptr || traverse->children.count(word[i]) == 0) {
			return false;
		}
		traverse = traverse->children[word[i]];
	}
	if (traverse == nullptr || traverse->end_of_word == true) {
		return true;
	} else {
		return false;
	}
}

//	This method does a level order traversal of the Trie starting from the node
//	associated with the last letter of the prefix in order to get suffix
//	suggestions. If we have the last letter's node, we can go through
//	all its children and return the closest words to the prefix. We store a
//	possible word in a pair that stores a string and a TrieNode pointer that is
//	associated with the last letter of the word. We use the possible_word
//	pair to push possible suggestions and its children into a queue
std::vector<std::string> Trie::autocomplete(std::string& prefix,
																						const int& num_of_words) {
	std::vector<std::string> suggestions;
	std::string new_word = prefix;
	std::queue< std::pair<std::string, TrieNode*> > queue;
	std::pair<std::string, TrieNode*> possible_word;
	std::map<char, TrieNode*>::iterator it;
	unsigned int word_count = num_of_words;

	TrieNode* last_letter_of_prefix_node = find_prefix(prefix);
	if (last_letter_of_prefix_node == nullptr) {
		return suggestions;	//	return empty vector if prefix wasn't found
	}

	possible_word.first = new_word;
	possible_word.second = last_letter_of_prefix_node;
	queue.push(possible_word);

	while (!queue.empty() && suggestions.size() < word_count) {
		possible_word = queue.front();
		if (possible_word.second == nullptr ||
				possible_word.second->end_of_word == true) {
			suggestions.push_back(possible_word.first);
		}
		last_letter_of_prefix_node = possible_word.second;
		new_word = possible_word.first;

		//	Go through last_letter_of_prefix_node's children to push possible words 
		//	into the queue. The keys of last_letter_of_prefix_node's children are 
		//	all possible next letters for the prefix. We use the keys of the map to 
		//	form new words by adding them onto new_word (which is equal to 
		//	possible_word's string member). We then make possible_word's string 
		//	member equal to new_word and set possible_word's TrieNode pointer member
		//	equal to the key's corresponding node to push that prefix and its 
		//	possible next letters into the queue. Before we move on to the next key, 
		//	we remove the last letter of new_word to restore it to its original 
		//	state so we can make prefixes with the other keys
		if (last_letter_of_prefix_node != nullptr) {
			for (it = last_letter_of_prefix_node->children.begin(); 
					 it != last_letter_of_prefix_node->children.end(); ++it) {
				new_word += it->first;
				possible_word.first = new_word;
				possible_word.second = it->second;
				queue.push(possible_word);
				new_word.pop_back();
			}
		}
		queue.pop();
	}
	return suggestions;
}

void Trie::load(std::string& file_name) {
	std::ifstream word_list;
	word_list.open(file_name.c_str());
	std::string word;
	if (!root_->children.empty()) {
		clear();
	}
	while (word_list >> word) {
		insert(word);
	}
	word_list.close();
}

int Trie::get_number_of_nodes(TrieNode* node, int& count) const {
	if (node == nullptr) {
		return count;
	} else {
		//	Go through each node's map to count all of their children and increase
		//	count to count this node once you've gone through all of this node's
		//	children
		std::map<char, TrieNode*>::iterator it;
		for (it = node->children.begin(); it != node->children.end(); ++it) {
			get_number_of_nodes(it->second, count);
		}
		++count;
		return count;
	}
}

int Trie::remove(TrieNode*& node, const std::string& word, int& length_of_word,
								 int position) {
	if (position == length_of_word) {
		if (node != nullptr && node->end_of_word == true) {
			node->end_of_word = false;
			--word_count_;
			return 1;	//	word was deleted without removing nodes. Do nothing more
		} else if (node == nullptr) {
			--word_count_;
			return 2;	//	indicator to erase letter from previous node's map
		} else {
			return 0;	//	word does not exist in Trie
		}
	}

	if (node == nullptr || node->children.count(word[position]) == 0) {
		return 0;
	}
	int last_node_deleted = remove(node->children[word[position]], word,
																 length_of_word, position + 1);
	if (last_node_deleted == 2) {
		node->children.erase(word[position]);
		if (node->children.empty()) {
			if (node->end_of_word == false) {
				delete node;
				node = nullptr;
				return 2;
				//	if end_of_word is true, we don't want to delete any more nodes
				//	because it would effect another word. But we delete this last node
				//	to set the last letter's corresponding node to nullptr to indicate
				//	the end of a word
			} else if (node->end_of_word == true) {
				delete node;
				node = nullptr;
				return 1;	//	returning 1 tells function to stop erasing letters from
									//	previous node's map and to stop deleting nodes
			}
		} else {
			return 1;
		}
	} else if (last_node_deleted == 1) {
		return 1;
	}
	return 0;
}

TrieNode* Trie::find_prefix(std::string& prefix) {
	if (root_ == nullptr || root_->children.empty()) {
		return nullptr;
	}

	make_lowercase(prefix);
	TrieNode* current = root_;
	for (unsigned int i = 0; i < prefix.length(); ++i) {
		if (current == nullptr || current->children.count(prefix[i]) == 0) {
			return nullptr;
		}
		current = current->children[prefix[i]];
	}
	return current;
}

void Trie::delete_tree(TrieNode*& node) {
	if (node == nullptr) {
		return;
	}

	std::map<char, TrieNode*>::iterator it;
	for (it = node->children.begin(); it != node->children.end(); ++it) {
		delete_tree(it->second);
		node->children.erase(it);
	}

	if (node != root_) {
		delete node;
		node = nullptr;
	}
	return;
}

