#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <unordered_map>

using namespace std;

long long generateRandLong() {
    long long generated = rand() % 9 + 1;
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
        numberStudents = rand() % 10001;
        tyrnicety = rand() % 2;
    }
};

int greatest_common_divider(long long a, long long b) {
    if (a == 1 || b == 1 || a==0 || b==0 ) {
        return 1;
    }
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return greatest_common_divider(a % b, b);
    return greatest_common_divider(a, b % a);
}

struct HashTable {
    struct DataContainer {
        long long key;
        Data* uni = nullptr;
        bool isDeleted = false;
    };

    long M = 2;
    long entities = 0;

    DataContainer* bucketsArray = new DataContainer[M];

    long long p1 = 9149658775000477;
    int a1 = rand() % 1000;
    int b1 = rand() % 1000;

    long long hash1(long long key) {
        return ((a1 * key + b1) % p1) % M;
    }

    long long p2 = 7775194452319117;
    int a2 = rand() % 1000;
    int b2 = rand() % 1000;

    long long hash2(long long key) {
        long long hashVal1 = hash1(key);
        long long hashVal2 = ((a2 * key + b2) % p2) %M;
        if (greatest_common_divider(hashVal1, hashVal2) != 1) {
            hashVal2 /= greatest_common_divider(hashVal1, hashVal2);
        }
        return hashVal2;
    }

    void insert(long long key, Data univer) {
        if (entities >= M) {
            reshapeTable();
        }

        int hashInd = hash1(key);

        if (find(key) != NULL) return;
        else if (bucketsArray[hashInd].isDeleted == false && bucketsArray[hashInd].uni == nullptr) {
            bucketsArray[hashInd].uni = new Data;
            *(bucketsArray[hashInd].uni) = univer;
            bucketsArray[hashInd].key = key;
            entities++;
        }
        else {
            long long step = hash2(key);
            int i = 0;
            do {
                i++;
                hashInd = (hashInd + i * step) % M;
            } while (bucketsArray[hashInd].uni != nullptr || bucketsArray[hashInd].isDeleted == true);

            bucketsArray[hashInd].uni = new Data;
            *(bucketsArray[hashInd].uni) = univer;
            bucketsArray[hashInd].key = key;
            entities++;
        }
    }

    Data* find(long long key) {
        int hashInd = hash1(key);
        if (bucketsArray[hashInd].key == key && bucketsArray[hashInd].isDeleted == true) return NULL;
        else if (bucketsArray[hashInd].key == key && bucketsArray[hashInd].isDeleted == false) {
            return bucketsArray[hashInd].uni;
        }
        else {
            long long startedInd = hashInd;
            long long step = hash2(key);
            hashInd = (hashInd + step) % M;
            int i = 1;
            do {
                if (bucketsArray[hashInd].key == key && bucketsArray[hashInd].isDeleted == false) return bucketsArray[hashInd].uni;
                else if(bucketsArray[hashInd].key == key && bucketsArray[hashInd].isDeleted == true) return NULL;
                i++;
                hashInd = (hashInd + i*step) % M;
            } while (bucketsArray[hashInd].uni != nullptr && hashInd != startedInd);

            return NULL;
        }
    }

    void erase(long long key) {
        if (find(key) == NULL) return;
        else {
            int hashInd = hash1(key);
            if (bucketsArray[hashInd].key == key && bucketsArray[hashInd].isDeleted == false) {
                bucketsArray[hashInd].isDeleted = true;
                entities--;
            }
            else {
                long long step = hash2(key);
                hashInd = (hashInd + step) % M;
                int i = 1;
                do {
                    if (bucketsArray[hashInd].key == key && bucketsArray[hashInd].isDeleted == false) {
                        bucketsArray[hashInd].isDeleted = true;
                        entities--;
                    }
                    i++;
                    hashInd = (hashInd + i * step) % M;
                } while (bucketsArray[hashInd].uni != nullptr);
            }
        }
    }

    long size() {
        return entities;
    }

    void reshapeTable(){
        M *= 2;
        entities = 0;
        DataContainer* oldBucketsArray = bucketsArray;
        bucketsArray = new DataContainer[M];
        for (int i = 0; i < M / 2; i++) {
            DataContainer currentContainer = oldBucketsArray[i];
            if (currentContainer.isDeleted == true) continue;
            else {
                insert(currentContainer.key, *currentContainer.uni); /// *current uni
            }
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

int main()
{
    srand(time(NULL));

    testHashTable();
    
    return 0;
}