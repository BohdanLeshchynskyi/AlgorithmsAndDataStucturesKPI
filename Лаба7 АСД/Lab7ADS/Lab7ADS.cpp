#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

struct Data {
    int PatientId;
    int SurvivingChance;
    int Degree;

    Data() {
        PatientId = rand() % 1001;
        SurvivingChance = rand() % 100;
        Degree = rand() % 10;
    }

    bool operator <(const Data other ) const {
        return (this->SurvivingChance + this->Degree) < (other.SurvivingChance + other.Degree);
    }

	bool operator >(const Data other) const {
		return !(*this < other);
	}

    bool operator ==(const Data other) const {
		return (this->SurvivingChance + this->Degree) == (other.SurvivingChance + other.Degree);
    }
};

int getParent(int ind) {
	return (ind - 1) / 2;
}

int getLeftChild(int ind) {
	return ind * 2 + 1;
}

int getRightChild(int ind) {
	return ind * 2 + 2;
}

struct PriorityQueue {
	Data* heapArr = new Data[1];

	int entities = 0;
	int Size = 1;

	void siftUp(int ind) {
		while(ind!=0 && heapArr[ind] > heapArr[getParent(ind)]){
			Data swap = heapArr[getParent(ind)];
			heapArr[getParent(ind)] = heapArr[ind];
			heapArr[ind] = swap;
			ind = getParent(ind);
		}
	}

	void siftDown(int ind) {
		while (ind < entities / 2) {
			int maxInd = getLeftChild(ind);
			if (getRightChild(ind) < entities && heapArr[getRightChild(ind)] > heapArr[getLeftChild(ind)]) {
				maxInd = getRightChild(ind);
			}
			if (heapArr[ind] > heapArr[maxInd] || heapArr[ind] == heapArr[maxInd]) {
				return;
			}
			Data swap = heapArr[maxInd];
			heapArr[maxInd] = heapArr[ind];
			heapArr[ind] = swap;
			ind = maxInd;
		}
	}

	void push(Data patient) {
		if (entities + 1 == Size) {
			Data* newArr = new Data[Size * 2];
			for (int i = 0; i < entities; i++) {
				newArr[i] = heapArr[i];
			}
			delete[] heapArr;
			heapArr = newArr;
			Size *= 2;
		}
		heapArr[entities] = patient;
		siftUp(entities);
		entities++;
	}

	Data top() {
		return heapArr[0];
	}

	void pop() {
		Data swap = heapArr[0];
		heapArr[0] = heapArr[entities - 1];
		heapArr[entities - 1] = swap;
		entities--;
		siftDown(0);
	}

	int size() {
		return entities;
	}

	bool empty() {
		return entities == 0;
	}
};

template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue)
{
	const int iters = 100000;
	clock_t timeStart = clock();
	for (int i = 0; i < iters; i++)
	{
		int insertDataAmount = rand() % 6 + 5;
		for (int j = 0; j < insertDataAmount; j++)
		{
			priorityQueue.push(Data());
		}
		priorityQueue.top();
		priorityQueue.pop();
	}
	clock_t timeEnd = clock();
	float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
	return time;
}
bool testPriorityQueue()
{
	srand(time(NULL));
	const int iters = 20000;
	PriorityQueue myPriorQueue;
	priority_queue<Data> stlPriorQueue;
	bool isDataEqual = true;
	for (int i = 0; i < iters; i++)
	{
		int insertDataAmount = rand() % 6 + 5;
		for (int j = 0; j < insertDataAmount; j++)
		{
			Data randData = Data();
			myPriorQueue.push(randData);
			stlPriorQueue.push(randData);
		} 
		if (!(myPriorQueue.top() == stlPriorQueue.top()))
		{
			isDataEqual = false;
			cerr << "Comparing failed on iteration " << i << endl << endl;
			break;
		}
		int removeDataAmount = rand() % insertDataAmount;
		for (int j = 0; j < removeDataAmount; j++)
		{
			myPriorQueue.pop();
			stlPriorQueue.pop();
		}
	}
	int myQueueSize = myPriorQueue.size();
	int stlQueueSize = stlPriorQueue.size();
	float stlTime =
		testPriorityQueueSpeed<priority_queue<Data>>(priority_queue<Data>());
	float myTime = testPriorityQueueSpeed<PriorityQueue>(PriorityQueue());
	cout << "My PriorityQueue:" << endl;
	cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
	cout << "STL priority_queue:" << endl;
	cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;
	if (isDataEqual && myQueueSize == stlQueueSize)
	{
		cout << "The lab is completed" << endl << endl;
		return true;
	}
	cerr << ":(" << endl << endl;
	return false;
}

void siftDown(int* arr, int arrSize, int ind) {
	while (ind < arrSize / 2) {
		int maxInd = getLeftChild(ind);
		if (getRightChild(ind) < arrSize && arr[getRightChild(ind)] > arr[getLeftChild(ind)]) {
			maxInd = getRightChild(ind);
		}
		if (arr[ind] > arr[maxInd] || arr[ind] == arr[maxInd]) {
			return;
		}
		int swap = arr[maxInd];
		arr[maxInd] = arr[ind];
		arr[ind] = swap;
		ind = maxInd;
	}
}

void HeapSort(int* arr, int arrSize) {
	//building heap:
	for (int i = arrSize / 2 - 1; i >= 0; i--) {
		//siftDown for each vertice that has at least one successor
		siftDown(arr, arrSize, i);
	}

	//sorting itself:
	for (int i = 0; i < arrSize - 1; i++) {
		int swap1 = arr[0];
		arr[0] = arr[arrSize - 1 - i];
		arr[arrSize - 1 - i] = swap1;

		siftDown(arr, arrSize - i - 1, 0);
	}
}

bool arrEqual(int* arr1, int* arr2, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		if (arr1[i] != arr2[i]) {
			cout << "Not equal on iteration: " << i << endl;
			return false;
		}
	}

	cout << "The given arrays are equal";
	return true;
}

int main(){
	double sTime, fTime, resultTime = 0;
	srand(time(NULL));

	testPriorityQueue();

	int arr1[100000];
	int arr2[100000];

	for (int i = 0; i < 100000; i++) {
		arr1[i] = arr2[i] = (i % 500 == 0) ? i + 50 : i;//i; //rand(); //(i % 500 == 0) ? i + 50 : i; <--- different cases of starting data
	}

	cout << "Testing handmade heapSort against STL stable_sort() function on the array \nfilled with the same random elements (size 100000 elem.): \n";
	cout << endl;

	sTime = double(clock());
	HeapSort(arr1, 100000);
	fTime = double(clock());
	resultTime += (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "Heap array sorting time: " << resultTime << endl;

	cout << endl;

	sTime = double(clock());
	stable_sort(begin(arr2), end(arr2));//sort(begin(arr2), end(arr2));
	fTime = double(clock());
	resultTime = (fTime - sTime) / CLOCKS_PER_SEC;
	cout << "STL sort() time: " << resultTime << endl;

	cout << endl;

	cout << "Checking arrays` equality elementwise after sortings: \n";
	arrEqual(arr1, arr2, 20);
	cout << endl;
		
    return 0;
}
