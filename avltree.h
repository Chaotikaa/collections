#include <cmath>
#include <iostream>

template <class T>
class avlnode {
public:
	avlnode(T * data) {
		this->data = data;
		height = 0;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		treeroot = nullptr;
	}

	~avlnode(){
		delete data;
	}
	void setHeight(long height) {
		this->height = height;
	} 

	long insert(avlnode<T> * insert) {
		if (*data == *insert->data) {
			return 0;
		}
		else if (*insert->data > *data) {
			if (right == nullptr) {
				right = insert;
				right->parent = this;
				if (right->height + 1 > height)
					height = right->height + 1;

			}
			else if (right->insert(insert) == 0) {
				if (right->height + 1 > height)
					height = right->height + 1;
			}
			else return 1;

		}
		else if (*insert->data < *data) {
			if (left == nullptr) {
				left = insert;
				left->parent = this;
				if (left->height + 1 > height)
					height = left->height + 1;
			}
			else if (left->insert(insert) == 0) {
				if (left->height + 1 > height)
					height = left->height + 1;
			}
			else return 1;
		}

		rebalance();

		return 0;
	}

	long remove(T * data){
		if (*this->data == *data) {
			
			if (!left && !right) {
				delete this;
				return 0;
			}
			else if (left){
				if (!left->right){
					*this->data = *left->data;
					if (left->left){
						left->left->parent = this;
						avlnode<T> * todelete = left;
						left = left->left;
						delete todelete;

					}
					else {
						delete left;
						left = nullptr;
					}
				}
				else
					left->findRightmostAndReplace(this);
			}
			else if (right){
				*this->data = *right->data;
				delete right;
				right = nullptr;
			}
			rebalance();
			return 0;
		}
		else if (*data < *this->data) {
			if (left)
				return left->remove(data);
			else return 1;
		}
		else if (*data > *this->data) {
			if (right)
				return right->remove(data);
			else return 1;
		}

		rebalance();
		return 0;

	}

	void findRightmostAndReplace(avlnode<T> * toReplace) {
		std::cerr << "Findign rigthmost";
		if (right) {
			right->findRightmostAndReplace(toReplace);
		}
		else {
			*toReplace->data = *this->data;
			std::cerr << "Replaced data";
			if (left)
				parent->right = left;
			delete this;
			return;
		}

		rebalance();
	}

	void write(std::ostream& out) {
		out << "Node: height=" << height << "; data=" << *data;
	}

	void writeAll(std::ostream& out) {
		if (left != nullptr) {
			left->writeAll(out);
		}
		out << "\tNode: height=" << height << "; data=" << *data << "\n";
		if (right != nullptr) {
			right->writeAll(out);
		}
	}

	void writeAllParentNodes(std::ostream& out) {
		if (left != nullptr) {
			left->writeAllParentNodes(out);
		}
		out << "\tNode: height=" << height << "; data=" << *data << "; Parent: ";
		if (parent)
			out << "height=" << parent->height << "; data=" << *parent->data << "\n";
		else out << "none\n";
		if (right != nullptr) {
			right->writeAllParentNodes(out);
		}
	}

	long getBalance() {
		long rightHeight = right ? right->height : -1;
		long leftHeight = left ? left->height : -1;
		return rightHeight - leftHeight;
	}

	void rotateRight(avlnode<T> ** posInParent) {
		avlnode<T> * pivot = this->left;
		if (pivot) {
			
			this->left = pivot->right;
			if(this->left)
				this->left->parent = this;

			pivot->right = this;

			pivot->parent = parent;
			parent = pivot;

			*posInParent = pivot;

			if (!this->left && !this->right) {
				height = 0;
			}
			else if (!this->right) {
				height = left->height + 1;
			}
			else if (!this->left) {
				height = right->height + 1;
			}
			else
				height = left->height + 1 > right->height + 1 ? left->height + 1 : right->height + 1;

			if (!pivot->left && !pivot->right) {
				pivot->height = 0;
			}
			else if (!pivot->right){
				pivot->height = pivot->left->height + 1;
			}
			else if (!pivot->left) {
				pivot->height = pivot->right->height + 1;
			}
			else
				pivot->height = pivot->left->height + 1 > pivot->right->height + 1 ? 
				  pivot->left->height + 1 : pivot->right->height + 1;

		}
	}

	void rotateLeft(avlnode<T> ** posInParent) {

		avlnode<T> * pivot = this->right;
		if (pivot) {
			
			this->right = pivot->left;
			if (this->right)
				this->right->parent = this;

			pivot->left = this;

			pivot->parent = parent;
			parent = pivot;

			*posInParent = pivot;


			if (!this->left && !this->right) {
				height = 0;
			}
			else if (!this->right) {
				height = left->height + 1;
			}
			else if (!this->left) {
				height = right->height + 1;
			}
			else
				height = left->height + 1 > right->height + 1 ? left->height + 1 : right->height + 1;

			if (!pivot->left && !pivot->right) {
				pivot->height = 0;
			}
			else if (!pivot->right){
				pivot->height = pivot->left->height + 1;
			}
			else if (!pivot->left) {
				pivot->height = pivot->right->height + 1;
			}
			else
				pivot->height = pivot->left->height + 1 > pivot->right->height + 1 ?
				pivot->left->height + 1 : pivot->right->height + 1;
		}
	}


	void rebalance() {
		long balance = getBalance();
		if (std::abs(balance) > 1) {
			std::cerr << "[Need to rebalance at "; write(std::cout); std::cout << "]\n";

			avlnode<T> ** ptrParent;

			if (parent == nullptr)
				ptrParent = treeroot;
			else
				ptrParent = this == parent->left ? &parent->left : &parent->right;

			/* zig-left */
			if (balance < 0) {

				/* zig-left */
				if (left->getBalance() < 0) {
					std::cerr << "[Single rotate right]\n";
					rotateRight(ptrParent);
				}
				/* zag-right */
				else if (left->getBalance() > 0){
					std::cerr << "[Double rotate right]\n";
					left->rotateLeft(&left);
					rotateRight(ptrParent);
				}

			}

			/* zig-right */
			else if (balance > 0) {

				/* zig-right*/
				if (right->getBalance() > 0) {
					std::cerr << "[Single rotate left]\n";
					rotateLeft(ptrParent);
				}

				/* zag-right */
				else if (right->getBalance() < 0) {
					std::cerr << "[Double rotate left]\n";
					right->rotateRight(&right);
					rotateLeft(ptrParent);
				}
			}
		}
	}

	T * data;
	long height;
	avlnode<T> * left;
	avlnode<T> * right;
	avlnode<T> * parent;
	avlnode<T> ** treeroot;


};

template <class T>
class avltree {

public:
	avltree() {
		root = nullptr;
		occupancy = 0;
	}

	avlnode<T> * root;
	long occupancy;

	long insert(T * data) {

		avlnode<T> * insert = new avlnode<T>(data);

		if (root == nullptr) {
			root = insert;
			root->treeroot = &root;
			occupancy++;
			return 0;
		}

		long retVal = root->insert(insert);

		if (retVal == 0) {
			occupancy++;
			return 0;
			
		}
		return 1;
		
	}

	long lookup(T * data) {
		
		avlnode<T> * working = root;

		if (working == nullptr)
			return 1;

		while (working != nullptr) {
			if (*working->data == *data)
				return 0;
			else if (*data < *working->data)
				working = working->left;
			else if (*data > *working->data)
				working = working->right;
		}
		return 1;
	}

	long remove(T * data) {
		
		if (occupancy == 0) {
			return 1;
		}

		if (root->remove(data) == 0) {
			occupancy--;
			if (occupancy == 0)
				root = nullptr;
			return 0;
		
		}
		return 1;

	}

	void write(std::ostream& out) {
		cout << "Tree: occupancy=" << occupancy << "\n";
		if (occupancy != 0) {
			root->writeAll(out);

		}
	}

	void writeParentNodes(std::ostream& out) {
		cout << "Tree: occupancy=" << occupancy << "\n";
		if (occupancy != 0) {
			root->writeAllParentNodes(out);

		}
	}

	void rotateRightAtRoot(){
		root->rotateRight(&root);
	}

	void rotateLeftAtRoot(){
		root->rotateLeft(&root);
	}

	
};