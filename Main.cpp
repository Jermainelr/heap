//Program Created by Jermaine Lara
// 3/4/18
// Program creates a heap from a file or user input, 
// and removes it from largest to smallest outputting the result
// Based on the algorithm from the book: Data Structures and Analysis in Java By: Clifford A. Shaffer
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
bool isLeaf(int heapSize, int pos);
int parent(int pos);
int leftChild(int pos);
int rightChild(int pos);

int main () {
	int heap[100];
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
	int current = heapSize++;
	//Start at the end of the heap
	heap[current] = value;
	//Sift up until parent > current
	while(current != 0 && heap[current] > heap[parent(current)]) {
		swap(heap, current, parent(current));
		current = parent(current);
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
	for(int i = 0; i < heapSize/2; i++) {
		cout << "PARENT: " << heap[i] << " LEFT CHILD: " << heap[leftChild(i)];
		if (rightChild(i) < heapSize) {
			cout << " RIGHT CHILD: " << heap[rightChild(i)];
		}
		cout << endl;
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
	//Swap max with last value
	swap(heap, 0, --heapSize);
	if(heapSize != 0) {
		//Put new heap root value in correct place 
		maximize(heap, heapSize, 0); 
	}
	return heap[heapSize];
}


//Removes and prints all values in descending order
int removeAndPrint(int* heap, int heapSize) {
	while (heapSize > 0) {
		cout << remove(heap, heapSize) << endl;
	}
}

//Tells if a given position is a leaf 
bool isLeaf(int heapSize, int pos) {
	return pos >= heapSize/2 && pos < heapSize;
}

//Tells the parent of a given position
int parent(int pos) {
	return (pos-1)/2;
}

//Tells the left child of a given position
int leftChild(int pos) {
	return 2*pos + 1;
}

//Tells the right child of a given position
int rightChild(int pos) {
	return 2*pos + 2;
}

// Recursively puts the maximum number at the top of the heap
void maximize(int* heap, int heapSize, int pos) {
	while (!isLeaf(heapSize, pos)){
		int j= 2*pos + 1;
		if(j < (heapSize-1) && heap[j] < heap[j+1]) {
			//Index of child with greater value
			j++;
		}
		if (heap[pos] >= heap[j]) {
			return;
		}
		swap(heap, pos, j);
		//Move down 
		pos = j;
	}
}