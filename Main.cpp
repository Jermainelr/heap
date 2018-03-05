//Program Created by Jermaine Lara
// 3/4/18
// Program creates a heap from a file or user input, 
// and removes it from largest to smallest outputting the result
// Based on the algorithm of java program from: http://www.sanfoundry.com/java-program-implement-max-heap/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void readFile(int* heap, int & heapSize); 
void readInput(int* heap, int & heapSize); 
void insert(int* heap, int & heapSize, int value);
void swap(int* heap, int pos1, int pos2);
void printFullTree(int* heap, int heapSize);
int removeAndPrint(int* heap, int heapSize);
void maximize(int* heap, int heapSize, int pos);
int remove(int* heap, int& heapSize);

int main () {
	int heap[101];	//1 extra because we are starting at index 1 instead of 0
	heap[0] = 1001;  //Just a number larger than maximum allowed
	int heapSize=0;
	cout << "Enter option:" << endl;
	cout << "1 to specify a file name" << endl;
	cout << "2 to enter numbers manually" << endl;
	int choice;
	cin >> choice;
	if (choice == 1) {
		readFile(heap, heapSize);
		cout << "Full Tree: " << endl;
		printFullTree(heap, heapSize);
		cout << "Removal Ordered Heap: " << endl;
		removeAndPrint(heap, heapSize);
    }
    else if (choice == 2) {
		readInput(heap, heapSize);
		cout << "Full Tree: " << endl;
		printFullTree(heap, heapSize);
		cout << "Removal Ordered Heap: " << endl;
		removeAndPrint(heap, heapSize);
	}
	else {
		cout << "Invalid option " << endl;
	}
}

// Read the numbers from a file and insert into heap
void readFile(int* heap, int & heapSize) {
	char fileName[81];
    cout << "Enter file name: " << endl;
	cin >> fileName;
    int number;
    ifstream heapFile(fileName);
    if (heapFile.is_open()) {
		while (heapFile >> number)
		{
			insert(heap, heapSize, number);
		}
		heapFile.close();
    }
    else {
		cout << "Unable to open file"; 
    }
}


// Insert a number into the heap at the  correct position
void insert(int* heap, int & heapSize, int value) {
	heap[++heapSize] = value;
	int current = heapSize;
	while(heap[current] > heap[current/2]) {
		swap(heap, current, current/2);
		current = current/2;
	}
}

// Swaps 2 values from the heap
void swap(int* heap, int pos1, int pos2) {
	int temp = heap[pos1];
	heap[pos1] = heap[pos2];
	heap[pos2] = temp;
}

// Prints the description of the heap tree			
void printFullTree(int* heap, int heapSize) {
	for(int i = 1; i <= heapSize/2; i++) {
		cout << "PARENT: " << heap[i] << " LEFT CHILD: " << heap[2*i]
			<< " RIGHT CHILD: " << heap[2*i+1] << endl;
	}
}

// Reads the numbers from the user input and insert into heap
void readInput(int* heap, int & heapSize) {
	cout << "Enter space separated numbers" << endl;
	string input;
	cin.ignore();
	getline(cin, input);
	istringstream is(input);
	int number;
	while (is >> number)
	{
		insert(heap, heapSize, number);
	}
}

// Removes the largest value from the heap
int remove(int* heap, int & heapSize) {
	int popped = heap[1];
	heap[1] = heap[heapSize--];
	maximize(heap, heapSize, 1);
	return popped;
}

//Removes and prints all values in descending order
int removeAndPrint(int* heap, int heapSize) {
	while (heapSize > 0) {
		cout << remove(heap, heapSize) << endl;
	}
}

// Recursively puts the maximum number at the top of the heap
void maximize(int* heap, int heapSize, int pos) {
	if ((pos < heapSize/2 || pos > heapSize) && (heap[pos] < heap[2*pos] || heap[pos] < heap[2*pos+1])) {
		if (heap[2*pos] > heap[2*pos +1]) {
			swap(heap, pos, 2*pos);
			maximize(heap, heapSize, 2*pos);
		}
		else {
			swap(heap, pos, 2*pos+1);
			maximize(heap, heapSize, 2*pos+1);
		}
	}
}