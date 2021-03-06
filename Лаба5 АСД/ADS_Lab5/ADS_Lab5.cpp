#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

string Names[3] = { "KPIvanlav","KNU Schevchenka","Mogilyanka" };

struct University {
	string Name;
	int numberStudents;
	bool Turnikety;
};

University generateUni() {
	University randomUni = { Names[rand() % 3],rand() % 10001,(bool)(rand() % 2) };
	return randomUni;
}

struct DynamicArray {
	University *arr = new University[1];

	int entities = 0;
	int Size = 1;

	void push_back(University uni) {
		arr[entities] = uni;
		entities++;
		if (entities == Size) {
			University *newArr = new University[Size * 2];
			for (int i = 0; i < entities; i++) {
				newArr[i] = arr[i];
			}
			delete[] arr;
			arr = newArr;
			Size *= 2;
		}
	}

	University pop_back() {
		entities--;
		return arr[entities];
	}

	void push_front(University uni) {
		for (int i = entities - 1; i >= 0; i--) {
			arr[i+1] = arr[i];
		}
		arr[0] = uni;
		entities++;
		if (entities == Size) {
			University* newArr = new University[Size * 2];
			for (int i = 0; i < entities; i++) {
				newArr[i] = arr[i];
			}
			delete[] arr;
			arr = newArr;
			Size *= 2;
		}
	}

	University pop_front() {
		University front_poped = arr[0];
		for (int i = 0; i < entities - 1; i++) {
			arr[i] = arr[i + 1];
		}
		entities--;
		return front_poped;
	}

	University get(int n) {
		if (n>entities) {
			throw "Invalid index\n";
		}
		else {
			return arr[n];
		}
	}

	int size() {
		return entities;
	}

	void print() {
		for (int i = 0; i < entities; i++) {
			cout << "University #" << i + 1 << ": " << arr[i].Name << " " << "; Number of students: " << arr[i].numberStudents << "; Tyrnikety: " << arr[i].Turnikety << "\n";
		}
	}
};

struct Node {
	University uni;
	Node* next;
};

struct LinkedList {
	int entities = 0;
	Node* firstNode = nullptr;
	Node* lastNode = nullptr;

	void push_front(University uni) {
		Node* newFirst = new Node;
		newFirst->uni = uni;
		if (entities == 0) {
			firstNode = newFirst;
			lastNode = newFirst;
		}
		else {
			newFirst->next = firstNode;
			firstNode = newFirst;
		}
		entities++;
	}

	void push_back(University uni) {
		Node* newLast = new Node;
		newLast->uni = uni;
		if (entities == 0) {
			firstNode = newLast;
			lastNode = newLast;
		}
		else {
			lastNode->next = newLast;
			lastNode = newLast;
		}
		entities++;
	}

	University pop_front() {
		University poped_front = firstNode->uni;
		Node* newFirst = firstNode->next;
		delete firstNode;
		firstNode = newFirst;
		entities--;
		return poped_front;
	}
	
	University pop_back() {
		University poped_back = lastNode->uni;
		Node* currNode = firstNode;
		while (currNode->next != lastNode) {
			currNode = currNode->next;
		}
		delete lastNode;
		currNode->next = nullptr;
		lastNode = currNode;
		entities--;
		return poped_back;
	}

	University get(int n) {
		if (n > entities) throw "Invalid index!";
		Node* nNode = firstNode;
		for (int i = 0; i < n; i++) { // nor sure with number of inerations needed
			nNode = nNode->next;
		}
		return nNode->uni;
	}

	int size() {
		return entities;
	}

	void print() {
		Node* currNode = firstNode;
		for (int i = 0; i < entities; i++) {
			cout << "University #" << i + 1 << ": " << currNode->uni.Name << " " << "; Number of students: " << currNode->uni.numberStudents << "; Tyrnikety: " << currNode->uni.Turnikety << "\n";
			currNode = currNode->next;
		}
	}
};

int main(){
	srand(time(NULL));

	DynamicArray uniArr;
	LinkedList uniList;
	double sTime, fTime, resultTime = 0;

	University uni = generateUni();

	sTime = double(clock());
	for (int i = 0; i < 50000; i++) {
		uniArr.push_back(uni);
	}
	fTime = double(clock());
	resultTime += (fTime - sTime)/CLOCKS_PER_SEC;
	cout << "Dynamic array push_back 50000 element time: " << resultTime << endl;

	sTime = double(clock());
	for (int i = 0; i < 50000; i++) {
		uniList.push_back(uni);
	}
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Linked list push_back 50000 element time: " << resultTime << endl;

	cout << endl;

	sTime = double(clock());
	for (int i = 0; i < 10000; i++) {
		uniArr.push_front(uni);
	}
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Dynamic array push_front 10000 element time: " << resultTime << endl;

	sTime = double(clock());
	for (int i = 0; i < 10000; i++) {
		uniList.push_front(uni);
	}
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Linked list push_front 10000 element time: " << resultTime << endl;

	cout << endl;

	sTime = double(clock());
	for (int i = 0; i < 20000; i++) {
		uniArr.get(rand() % 60000);
	}
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Accessing 20000 random elements of dynamic array time ( get() ) : " << resultTime << endl;

	sTime = double(clock());
	for (int i = 0; i < 20000; i++) {
		uniList.get(rand() % 60000);;
	}
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Accessing 20000 random elements of linked list time ( get() ) : " << resultTime << endl;

	cout << endl;

	sTime = double(clock());
	for (int i = 0; i < 5000; i++) {
		uniArr.pop_front();
	}
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Deleting 5000 elements of dynamic array from the beginning of it ( pop_front() ) :" << resultTime << endl;

	sTime = double(clock());
	for (int i = 0; i < 5000; i++) {
		uniList.pop_front();
	}
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Deleting 5000 elements of linked list from the beginning of it ( pop_front() ) :" << resultTime << endl;

	cout << endl;

	sTime = double(clock());
	for (int i = 0; i < 5000; i++) {
		uniArr.pop_back();
	}
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Deleting 5000 elements of dynamic array from the end of it ( pop_back() ) :" << resultTime << endl;

	sTime = double(clock());
	for (int i = 0; i < 5000; i++) {
		uniList.pop_back();
	}
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Deleting 5000 elements of linked from the end of it ( pop_back() ) :" << resultTime << endl;

	return 0;
}
