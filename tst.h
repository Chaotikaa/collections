#pragma once

#ifndef TST_H
#define TST_H

#include <string>

using namespace std;

template <class T>
struct TSTNode {
	T * data;
	char charKey;
	TSTNode * eq_kid;
	TSTNode * lo_kid;
	TSTNode * hi_kid;
};

template <class T>
class TST {
public:
	TSTNode<T> * root;
	long count;
	TST() {
		count = 0;
	}
	~TST() {}

	/**
	Inserts the specified data into the TST using the specified key string.
	Iterative implementation.

	@param data The data to insert.
	@param key  The key corresponding to the inserted data.
	*/
	void insert_itr(T * data, char * key) {
		char * itr = key;

		/* no elements, initial insertion */
		if (count == 0) {

			/* insert root */
			root = newNode();
			root->charKey = *key;
			if (strlen(key) == 1) {
				root->data = data;
				return;
			}

			insert_remainder(data, key + 1, root);

			count++;


			return;
		}

		TSTNode<T> * working = root;
		while (*itr != '\0') {

			if (*itr < working->charKey) {
				if (working->lo_kid == nullptr) {
					working->lo_kid = newNode();
					working->lo_kid->charKey = *itr;
					if (*(itr + 1) == '\0')
						working->lo_kid->data = data;
					else
						insert_remainder(data, itr + 1, working->lo_kid);

					count++;
					break;
				}
				working = working->lo_kid;
			}

			else if (*itr > working->charKey) {
				if (working->hi_kid == nullptr) {
					working->hi_kid = newNode();
					working->hi_kid->charKey = *itr;
					if (*(itr + 1) == '\0')
						working->hi_kid->data = data;
					else
						insert_remainder(data, itr + 1, working->hi_kid);

					count++;
					break;
				}
				working = working->hi_kid;
			}

			else if (*itr == working->charKey) {
				if (*(itr + 1) == '\0') {
					working->data = data;
					count++;
					break;
				}
				if (working->eq_kid == nullptr) {
					insert_remainder(data, itr + 1, working);
					count++;
					break;
				}

				working = working->eq_kid;
				itr++;
			}
		}
	}

	/**
	Removes the data corresponding to the key, if it exists, and returns it.
	Recursive implementation.

	@param key The key corresponding to the data.
	@return A pointer to the removed data; NULL if not found.
	*/
	const T * remove_rec(char * key){}
	const T * remove_itr(char * key){}

	/**
	Retrieves the data corresponding to the key, if it exists, and returns it.

	@param key The key corresponding to the data.
	@return A pointer to the removed data; NULL if not found.
	*/
	T * get(char * key) {

		if (!root)
			return nullptr;

		char * itr = key;

		TSTNode<T> * working = root;
		while (*itr != '\0') {

			if (*itr < working->charKey) {
				if (working->lo_kid == nullptr) {
					return nullptr;
				}
				working = working->lo_kid;
			}

			else if (*itr > working->charKey) {
				if (working->hi_kid == nullptr) {
					return nullptr;
				}
				working = working->hi_kid;
			}

			else if (*itr == working->charKey) {
				if (*(itr + 1) == '\0') {
					return working->data;
				}
				if (working->eq_kid == nullptr) {
					return nullptr;
				}

				working = working->eq_kid;
				itr++;
			}
		}

		return nullptr;
	}
	void print() {
		if (root) {
			printAllKeys(root, "");
		}
	}
private:
	
	TSTNode<T> * newNode() {
		TSTNode<T> * n = new TSTNode<T>;
		n->charKey = 0;
		n->data = nullptr;
		n->lo_kid = nullptr;
		n->eq_kid = nullptr;
		n->hi_kid = nullptr;
		return n;
	}
	void insert_remainder(T * data, char * keyrem, TSTNode<T> * loc) {
		for (unsigned int i = 0; i < strlen(keyrem); i++) {
			TSTNode<T> * n = newNode();
			n->charKey = *(keyrem + i);
			if (*(keyrem + i + 1) == '\0') {
				n->data = data;
			}
			loc->eq_kid = n;
			loc = n;
		}
	}
	void printAllKeys(TSTNode<T> * node, string keyStr) {
		if (node->lo_kid) {
			printAllKeys(node->lo_kid, keyStr);
		}

		if (node->data) {
			string concat = keyStr + string(1, node->charKey);
			cout << "Node: key = " << concat << ", data = " << (string) *node->data << "\n";
		}

		if (node->eq_kid) {
			printAllKeys(node->eq_kid, keyStr + string(1, node->charKey));
		}

		if (node->hi_kid) {
			printAllKeys(node->hi_kid, keyStr);
		}
	}
};


#endif