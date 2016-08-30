#pragma once

#ifndef HEAP_H
#define HEAP_H

#define MIN 0
#define MAX 1
#define DEFAULT_SIZE 11

using namespace std;

template <class T>
class heap {
public:


	heap() : mode (MIN), size(DEFAULT_SIZE), occupancy(0), next_index(0) {
		elements = new T[size];
	}
	heap(long mod, long siz, long (*compare)(const T& t1, const T& t2)) : mode(mod), size(siz), occupancy(0), next_index(0) {
		elements = new T[size];
		comparator = compare;
	}

	unsigned long push (const T& data) {
		
		if (next_index == size)
			return 1;

		elements[next_index] = data;

		int ind = next_index;

		if (mode == MIN) {
			while ((ind != 0) && comparator(elements[ind], elements[(ind - 1) / 2]) < 0) {
				T copy = elements[(ind - 1) / 2];
				elements[(ind - 1) / 2] = elements[ind];
				elements[ind] = copy;
				ind = (ind - 1) / 2;
			}
		}
		else if (mode == MAX) {
			while ((ind != 0) && comparator(elements[ind], elements[(ind - 1) / 2]) > 0) {
				T copy = elements[(ind - 1) / 2];
				elements[(ind - 1) / 2] = elements[ind];
				elements[ind] = copy;
				ind = (ind - 1) / 2;

			}
		}

		next_index++;
		occupancy++;

		return 0;

	}

	unsigned long peek (T& ret) {
		if (next_index == 0) return 1;

		ret = elements[0];

		return 0;
	}
	unsigned long pop (T& ret) {
		if (next_index == 0) return 1;

		ret = elements[0];

		elements[0] = elements[next_index - 1];

		occupancy--;
		next_index--;

		int ind = 0;
		
		if (occupancy != 0) {
			while (true) {

                /* left child of current node does not exist; break */
				if (2 * ind + 1 >= occupancy) {
					break;
				}

				/* get left child */
				T left = elements[2 * ind + 1];

				if (mode == MIN) {

					long rep_ind;
					T rep;
					
					/* right child of current node does not exist; replace current node with left child if current node greater */
					if (2 * ind + 2 >= occupancy) {

						
						rep = elements[2 * ind + 1];
						rep_ind = 2 * ind + 1;
						if (comparator(elements[ind], rep) <= 0)
							break;
					}

					/* both left and right child exist; find min between the two */
					else {

						T right = elements[2 * ind + 2];

						rep = comparator(left, right) <= 0 ? left : right;
						rep_ind = comparator(left, right) <= 0 ? 2 * ind + 1 : 2 * ind + 2;

						/* if current node is still less than the lesser of both children, break */
						if (comparator(elements[ind], rep) <= 0)
							break;
					}

					/* swap child and current node */
					elements[rep_ind] = elements[ind];
					elements[ind] = rep;

					/* update index */
					ind = rep_ind;
				}
			}
		}

		return 0;
		
	}
	unsigned long delete_root () {}
	unsigned long replace_root (const T& data) {}

	void print() {
		cout << "Heap: occupancy=" << occupancy << "; next_index=" << next_index << "\n";
		for (long l = 0; l < next_index; l++) {
			cout << (string)elements[l] << "\n";
		}
	}

	const long size;

private:
	const long mode;
	long occupancy;
	long next_index;
	T * elements;
	long(*comparator) (const T& t1, const T& t2);
	
};

#endif