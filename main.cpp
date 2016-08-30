#include <iostream>

#include "avltree.h"

#define EOF_CODE 4
#define CHOICE_AVL 1


using namespace std;

int main() {

	int structType;
	

	while (cin) {

		cout << "What type of data structure would you like to use?\n";
		cout << "(1) AVL Tree\n";

		if (!(cin >> structType)) {
			cout << "Please enter a number!\n";
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		break;

	}

	if (structType == CHOICE_AVL){

		avltree<int> tree;

		char operation;

		while (cin) {

			cout << "Please enter an operation: i(n)sert, (d)elete, (l)ookup, (o)ccupancy,\n";
		    cout << "(w)rite to stream, test rotate (r)ight, test rotate l(e)ft\n";

			cin >> operation;
			if (operation == EOF_CODE) {
				break;
			}
			cin.clear();
			cin.ignore(10000, '\n');

			switch (operation) {
			case 'n': {
				int data;

				cout << "Enter a number to insert: ";
				cin >> data;
				cout << "Inserting " << data << "...\n";
				tree.insert(new int(data));
				break;
			}
			case 'd': {
				int data;

				cout << "Enter a number to delete: ";
				cin >> data;
				cout << "Deleting " << data << "...\n";
				if (tree.remove(&data) == 0){
					cout << data << " was removed!\n";
				}
				else cout << data << " not found!\n";

				break;
			}
			case 'l': 
				int data;

				cout << "Enter a number to find: ";
				cin >> data;
				if (tree.lookup(&data) == 0){
					cout << data << " was found!\n";
				}
				else cout << data << " not found!\n";
				break;
			case 'w':

				char option;
				cout << "Write parent nodes? (y/n)";
				cin >> option;
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Writing to stream using in-order traversal...\n";
				if (option == 'y') {
					tree.writeParentNodes(cout);
				}
				
				else tree.write(cout);
				break;
			case 'o':
				cout << "Occupancy of tree: " << tree.occupancy << "\n";
				break;
			case 'r':
				cout << "Rotating right at root...\n";
				tree.rotateRightAtRoot();
				break;
			case 'e':
				cout << "Rotating left at root...\n";
				tree.rotateLeftAtRoot();
				break;
			default:
				cout << "Invalid operation!\n";
				break;
			}
		}
	}
}