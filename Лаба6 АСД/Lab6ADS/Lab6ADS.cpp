#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <unordered_map>

using namespace std;

long long generateRandLong() {
    long long generated = rand()%9 + 1;
    for (int i = 1; i < 10; i++) {
        generated *= 10;
        generated += rand() % 10;
    }
    return generated;
}

string possibleNames[] = { "KPI", "Sheva", "Mogila", "UKU" };

struct Data {
    string uniName;
    int numberStudents;
    bool tyrnicety;
    Data() {
        uniName = possibleNames[rand() % 4];
        numberStudents = rand()%10001;
        tyrnicety = rand() % 2;
    }
};

struct HashNode {
    Data uni;
    long long key;
    HashNode* next;
    HashNode* previous;
};

struct LinkedList {
    int entitiesList = 0;
    HashNode* first = nullptr;
    HashNode* last = nullptr;

    void push_back(long long key, Data uni) {
        HashNode* newLast = new HashNode;
        newLast->uni = uni;
        newLast->key = key;
        if (entitiesList == 0) {
            newLast->next = nullptr;
            newLast->previous = nullptr;
            first = newLast;
            last = newLast;
        }
        else{
            last->next = newLast;
            newLast->previous = last;
            newLast->next = nullptr;
            last = newLast;
        }
        entitiesList++;
    }

    Data* get_byKey(long long key) {
        HashNode* searchNode = first;
        if (searchNode == nullptr) return NULL;
        for (int i = 0; i < entitiesList; i++) {
            if (searchNode->key == key) {
                return &searchNode->uni;
            }
            else {
                searchNode = searchNode->next;
            }
        }
        return NULL;
    }

    bool delete_byKey(long long key) {
        HashNode* popingNode = first;
        if (popingNode == nullptr) return NULL;
        for (int i = 0; i < entitiesList; i++) {
            if (popingNode->key == key) {
                if (entitiesList == 1) {
                    delete popingNode;
                    first = nullptr;
                    last = nullptr;
                    entitiesList--;
                    return true;
                }
                else if (popingNode->previous == nullptr) {
                    popingNode->next->previous = nullptr;
                    first = popingNode->next;
                    delete popingNode;
                    entitiesList--;
                    return true;
                }
                else if (popingNode->next == nullptr) {
                    popingNode->previous->next = nullptr;
                    last = popingNode->previous;
                    delete popingNode;
                    entitiesList--;
                    return true;
                }
                else {
                    popingNode->previous->next = popingNode->next;
                    popingNode->next->previous = popingNode->previous;
                    delete popingNode;
                    entitiesList--;
                    return true;
                }
            }
            else {
                popingNode = popingNode->next;
            }
        }
        return false;
    }

    HashNode* pop_front() {
        if (entitiesList == 0) {
            return NULL;
        }
        else if (entitiesList == 1) {
            HashNode* popedNode = first;
            first = nullptr;
            last = nullptr;
            entitiesList--;
            return popedNode;
        }
        else {
            HashNode* popedNode = first;
            popedNode->next->previous = nullptr;
            first = popedNode->next;
            entitiesList--;
            return popedNode;
        }
    }
};

struct HashTable {
    double loadFactor = 0.8;
    long M = 1024;

    LinkedList* bucketsArray = new LinkedList[M];
    int entities = 0;

    long long p = 9149658775000477;
    int a = rand() % 1000;
    int b = rand() % 1000;
    int hash(long long key) {
        return ((a * key + b) % p) % M;
    }

    void insert(long long key, Data value) {
        if (size() >= loadFactor * (double)M) {
            reshapeTable();
        }

        int hashInd = hash(key);
        if (bucketsArray[hashInd].delete_byKey(key)) {
            bucketsArray[hashInd].push_back(key, value);
        }
        else {
            bucketsArray[hashInd].push_back(key, value);
            entities++;
        }
    }

    Data* find(long long key) {
        int findHashInd = hash(key);
        return bucketsArray[findHashInd].get_byKey(key);
    }

    void erase(long long key) {
        int eraseHashInd = hash(key);
        if(bucketsArray[eraseHashInd].delete_byKey(key)){
            entities--;
        }
    }

    int size() {
        return entities;
    }

    void reshapeTable() {
        M *= 2;
        entities = 0;
        LinkedList* oldBucketsArray = bucketsArray;
        bucketsArray = new LinkedList[M];
        for (int i = 0; i < M / 2; i++)
        {
            HashNode* currentNode = oldBucketsArray[i].first;
            if (currentNode == nullptr) continue;
            do {
                insert(currentNode->key, currentNode->uni);
                if (currentNode->next != nullptr)
                    currentNode = currentNode->next;
                else break;
            } while (true);
        }
        delete[] oldBucketsArray;
    }
};

bool testHashTable()
{
    const int iters = 500000;
    const int keysAmount = iters * 1;
    // generate random keys:
    long long* keys = new long long[keysAmount];
    long long* keysToInsert = new long long[iters];
    long long* keysToErase = new long long[iters];
    long long* keysToFind = new long long[iters];
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = generateRandLong();
    }
    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[generateRandLong() % keysAmount];
        keysToErase[i] = keys[generateRandLong() % keysAmount];
        keysToFind[i] = keys[generateRandLong() % keysAmount];
    }
    // test my HashTable:
    HashTable hashTable;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        hashTable.insert(keysToInsert[i], Data());
    }
    int myInsertSize = hashTable.size();
    for (int i = 0; i < iters; i++)
    {
        hashTable.erase(keysToErase[i]);
    }
    int myEraseSize = hashTable.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++) {
        if (hashTable.find(keysToFind[i]) != NULL)
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    // test STL hash table:
    unordered_map<long long, Data> unorderedMap;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({ keysToInsert[i], Data() });
    }
    int stlInsertSize = unorderedMap.size();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.erase(keysToErase[i]);
    }
    int stlEraseSize = unorderedMap.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    cout << "My HashTable:" << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize <<
        ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize
        << ", found amount: " << stlFoundAmount << endl << endl;
    delete keys;
    delete keysToInsert;
    delete keysToErase;
    delete keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount ==
        stlFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

int main(){
    srand(time(NULL));

    testHashTable();

    return 0;
}