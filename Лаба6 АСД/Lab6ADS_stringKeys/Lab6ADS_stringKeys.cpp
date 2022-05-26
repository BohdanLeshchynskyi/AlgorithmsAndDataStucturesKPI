#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <unordered_map>
#include <cmath>

using namespace std;

long long generateRandLong() {
    long long generated = rand() % 9 + 1;
    for (int i = 1; i < 10; i++) {
        generated *= 10;
        generated += rand() % 10;
    }
    return generated;
}

string generate_string_key() {

    string randStr = "";
    for (int i = 0; i < 10; i++) 
        randStr = randStr + char(rand() % 23 + 97);
    return randStr;
}

string possibleNames[] = { "KPI", "Sheva", "Mogila", "UKU" };

struct Data {
    string uniName;
    int numberStudents;
    bool tyrnicety;
    Data() {
        uniName = possibleNames[rand() % 4];
        numberStudents = rand() % 10001;
        tyrnicety = rand() % 2;
    }
};

struct HashNode {
    Data uni;
    string key;
    HashNode* next;
    HashNode* previous;
};

struct LinkedList {
    int entitiesList = 0;
    HashNode* first = nullptr;
    HashNode* last = nullptr;

    void push_back(string& key, Data uni) {
        HashNode* newLast = new HashNode;
        (newLast->uni).numberStudents = uni.numberStudents;
        (newLast->uni).tyrnicety = uni.tyrnicety;
        (newLast->uni).uniName = uni.uniName;
        newLast->key = key;
        if (entitiesList == 0) {
            newLast->next = nullptr;
            newLast->previous = nullptr;
            first = newLast;
            last = newLast;
        }
        else {
            last->next = newLast;
            newLast->previous = last;
            newLast->next = nullptr;
            last = newLast;
        }
        entitiesList++;
    }

    Data* get_byKey(string& key) {
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

    bool delete_byKey(string&  key) {
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
    long M = 1000;

    LinkedList* bucketsArray = new LinkedList[M];
    int entities = 0;

    int a = rand() % 52 + 1;
    int b = rand() % 52 + 1;
    /*long long hash(string& key) {
       
        long len = key.length();
        int newK = key[0] * key[len / 4] * key[len - 1] * a;
        return newK % M;
    }*/

    long long hash(string key) {
        const int p = 31;
        const int m = 1e9 + 9;
        long long hash = 0;
        long long p_pow = 1;
        for (int i = 0; i < key.length();i++) {
            hash = (hash + (key[i] - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hash % M;
    }

  
    void insert(string& key, Data value) {
        if (size() >= M * loadFactor) {
            reshapeTable();
        }

        long long hashInd = hash(key);
        if (bucketsArray[hashInd].delete_byKey(key)) {
            bucketsArray[hashInd].push_back(key, value);
        }
        else {
            bucketsArray[hashInd].push_back(key, value);
            entities++;
        }
    }

    Data* find(string& key) {
        long long findHashInd = hash(key);
        return bucketsArray[findHashInd].get_byKey(key);
    }

    void erase(string& key) {
        long long eraseHashInd = hash(key);
        if (bucketsArray[eraseHashInd].delete_byKey(key)) {
            entities--;
        }
    }

    int size() {
        return entities;
    }

    void reshapeTable() {
        M *= 2;
        LinkedList* reshapedBuckets = new LinkedList[M];
        HashNode* transNode = new HashNode;
        for (int i = 0; i < M / 2; i++) {
            while (bucketsArray[i].entitiesList != 0) {
                transNode = bucketsArray[i].pop_front();
                long long new_hashInd = hash(transNode->key);
                reshapedBuckets[new_hashInd].push_back(transNode->key, transNode->uni);
            }
        }
        delete[] bucketsArray;
        bucketsArray = reshapedBuckets;
    }
};

bool testHashTable()
{
    const int iters = 500000;
    const int keysAmount = iters * 1;
    string* keys = new string[keysAmount];
    string* keysToInsert = new string[iters];
    string* keysToErase = new string[iters];
    string* keysToFind = new string[iters];
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = generate_string_key();
    }
    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[generateRandLong() % keysAmount];
        keysToErase[i] = keys[generateRandLong() % keysAmount];
        keysToFind[i] = keys[generateRandLong() % keysAmount];
    }

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
   for (int i = 0; i < iters; i++)
    {
        if (hashTable.find(keysToFind[i]) != NULL)
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    unordered_map<std::string, Data> unorderedMap;
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
    cout << "Time: " << myTime << ", size: " << myInsertSize << " -" << myEraseSize << ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " -" << stlEraseSize << ", found amount: " << stlFoundAmount << endl
        << endl;
    delete[] keys;
    delete[] keysToInsert;
    delete[] keysToErase;
    delete[] keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount)
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