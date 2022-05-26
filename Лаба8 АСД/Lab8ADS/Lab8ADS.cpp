#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

long long generateRandLong() {
    long long generated = rand() % 9 + 1;
    for (int i = 1; i < 10; i++) {
        generated *= 10;
        generated += rand() % 10;
    }
    return generated;
}

std::string possibleNicks[] = { "User111","Skired","MonsterKiller","CatBoiCami" };

struct Data {
    std::string username;
    int rank;
    int experience;
    int communityConr;

    Data() {
        username = possibleNicks[rand() % 3];
        rank = rand() % 10 + 1;
        experience = rand() % 2001;
        communityConr = rand() % 101;
    }

    bool operator< (const Data other) const {
        return (this->rank + this->experience + this->communityConr) < (other.rank + other.experience + other.communityConr);
    }

    bool operator> (const Data other) const {
        return !(*this < other);
    }

    bool operator== (const Data other) const {
        return (this->rank + this->experience + this->communityConr) == (other.rank + other.experience + other.communityConr);
    }
};

struct TreeNode {
    Data player;
    TreeNode* parent = nullptr;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

struct BinarySearchTree {
    TreeNode* root = nullptr;
    int entities = 0;

    bool search(Data somePlayer, TreeNode* currentNode) {
        if (currentNode == nullptr) return false;
        if (currentNode->player == somePlayer) return true;
        if (currentNode->player < somePlayer)
            return search(somePlayer, currentNode->right);
        else return search(somePlayer, currentNode->left);
    }

    bool find(Data somePlayer) {
        return search(somePlayer, root);
    }

    void insert(Data newPlayer) {
        if (find(newPlayer)) return; //unique check

        TreeNode* playerToInsert = new TreeNode;
        playerToInsert->player = newPlayer;

        if (root == nullptr) {       //empty tree case
            root = playerToInsert;
            entities++;
            return;
        }

        TreeNode* initialRoot = root;
        entities++;
        while (root != nullptr) {
            if (newPlayer > root->player) {
                if (root->right != nullptr) root = root->right;
                else {
                    playerToInsert->parent = root;
                    root->right = playerToInsert;
                    root = initialRoot;
                    break;
                }
            }
            else {
                if (root->left != nullptr) root = root->left;
                else {
                    playerToInsert->parent = root;
                    root->left = playerToInsert;
                    root = initialRoot;
                    break;
                }
            }
        }
    }

    //functions needed for erase()
    TreeNode* searchToGet(Data somePlayer, TreeNode* currentNode) {
        if (currentNode == nullptr) return currentNode;
        if (currentNode->player == somePlayer) return currentNode;
        if (currentNode->player < somePlayer)
            return searchToGet(somePlayer, currentNode->right);
        else return searchToGet(somePlayer, currentNode->left);
    }

    TreeNode* getPlayer(Data somePlayer) {
        return searchToGet(somePlayer, root);
    }

    TreeNode* minimum(TreeNode* someTree) {
        if (someTree->left == nullptr) return someTree;
        else return minimum(someTree->left);
    }

    TreeNode* nextToReplace(TreeNode* someNode) {
        return minimum(someNode->right);
    }
 
    void erase(Data deletePlayer) {
        TreeNode* playerToErase = getPlayer(deletePlayer);
        if (playerToErase == nullptr) return;

        entities--;
        
        if (playerToErase->left == nullptr && playerToErase->right == nullptr) {
            if (playerToErase->parent == nullptr) root = nullptr;
            else if (playerToErase->parent->left == playerToErase) playerToErase->parent->left = nullptr;
            else playerToErase->parent->right = nullptr;
        }

        else if (playerToErase->left == nullptr || playerToErase->right == nullptr) {
            if (playerToErase->left == nullptr) {
                if (playerToErase->parent == nullptr) {
                    root = playerToErase->right;
                    playerToErase->right->parent = nullptr;
                }
                else if (playerToErase->parent->left == playerToErase) playerToErase->parent->left = playerToErase->right;
                else playerToErase->parent->right = playerToErase->right;
                playerToErase->right->parent = playerToErase->parent;
            }
            else {
                if (playerToErase->parent == nullptr) {
                    root = playerToErase->left;
                    playerToErase->left->parent = nullptr;
                }
                else if (playerToErase->parent->left == playerToErase) playerToErase->parent->left = playerToErase->left;
                else playerToErase->parent->right = playerToErase->left;
                playerToErase->left->parent = playerToErase->parent;
            }
        }

        else {
            TreeNode* successor = nextToReplace(playerToErase);
            playerToErase->player = successor->player;
            if (successor->parent->left == successor) {
                successor->parent->left = successor->right;
                if (successor->right != nullptr) successor->right->parent = successor->parent;
            }
            else {
                successor->parent->right = successor->right;
                if (successor->right != nullptr) successor->right->parent = successor->parent;
            }
        }
    }

    int size() { return entities; }

    void inorderTraversal(TreeNode* currNode) {
        if (currNode != nullptr) {
            inorderTraversal(currNode->left);
            std::cout << std::setw(15) << "username:" << currNode->player.username << "\trank:" << currNode->player.rank << "\texpetience:" << currNode->player.experience << "\tcommunity contribution:" << currNode->player.communityConr << std::endl;
            inorderTraversal(currNode->right);
        }
    }

    void print() {
        inorderTraversal(root);
    }

    int maxDepth(TreeNode* treeRoot) {
        if (treeRoot == nullptr) {
            return 0;
        }
        else{
            int leftDepth = maxDepth(treeRoot->left);
            int rightDepth = maxDepth(treeRoot->right);

            if (leftDepth > rightDepth) return leftDepth + 1;
            else return rightDepth + 1;
        }
    }

    int height() {
        return maxDepth(root);
    }

    void lookInRange(Data minObj, Data maxObj, TreeNode* treeRoot, int& inRange) {
        if (treeRoot != nullptr){
            if (treeRoot->player < minObj) lookInRange(minObj, maxObj, treeRoot->right, inRange);
            if (treeRoot->player > maxObj) lookInRange(minObj, maxObj, treeRoot->left, inRange);
            if ((treeRoot->player > minObj || treeRoot->player == minObj) && (treeRoot->player < maxObj || treeRoot->player == maxObj)) {
                lookInRange(minObj, maxObj, treeRoot->left, inRange);
                inRange++;
                lookInRange(minObj, maxObj, treeRoot->right, inRange);
            }
        }
    }

    int findInRange(Data minObj, Data maxObj) {
        int numberInrange = 0;
        lookInRange(minObj, maxObj, root, numberInrange);
        return numberInrange;
    }

};

bool testBinarySearchTree()
{
    srand(time(NULL));
    const int iters = 80000;
    const int keysAmount = iters * 2;
    const int itersToRangeQueries = 1000;
    vector<Data> data(keysAmount);
    vector<Data> dataToInsert(iters);
    vector<Data> dataToErase(iters);
    vector<Data> dataToFind(iters);
    vector<pair<Data, Data>> dataToRangeQueries; for (int i = 0; i < iters; i++)
    {
        dataToInsert[i] = data[generateRandLong() % keysAmount];
        dataToErase[i] = data[generateRandLong() % keysAmount];
        dataToFind[i] = data[generateRandLong() % keysAmount];
    }
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        Data minData = Data();
        Data maxData = Data();
        if (maxData < minData)
        {
            swap(minData, maxData);
        }
        dataToRangeQueries.push_back({ minData, maxData });
    }
    BinarySearchTree myTree;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        myTree.insert(dataToInsert[i]);
    }
    int myInsertSize = myTree.size();
    int myTreeHeight = myTree.height();
    int optimalTreeHeight = log2(myInsertSize) + 1;
    for (int i = 0; i < iters; i++)
    {
        myTree.erase(dataToErase[i]);
    }
    int myEraseSize = myInsertSize - myTree.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (myTree.find(dataToFind[i]))
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    set<Data> stlTree;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        stlTree.insert(dataToInsert[i]);
    }
    int stlInsertSize = stlTree.size();
    for (int i = 0; i < iters; i++)
    {
        stlTree.erase(dataToErase[i]);
    }
    int stlEraseSize = stlInsertSize - stlTree.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (stlTree.find(dataToFind[i]) != stlTree.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC; clock_t myRangeStart = clock();
    int myRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        myRangeFoundAmount += myTree.findInRange(dataToRangeQueries[i].first,
            dataToRangeQueries[i].second);
    }
    clock_t myRangeEnd = clock();
    float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;
    clock_t stlRangeStart = clock();
    int stlRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        const auto& low = stlTree.lower_bound(dataToRangeQueries[i].first);
        const auto& up = stlTree.upper_bound(dataToRangeQueries[i].second);
        stlRangeFoundAmount += distance(low, up);
    }
    clock_t stlRangeEnd = clock();
    float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;
    cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " << optimalTreeHeight << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount : " << myFoundAmount << endl;
    cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount<< endl << endl;
    cout << "STL Tree:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << endl;
    cout << "Range time: " << stlRangeTime << ", range found amount: " << stlRangeFoundAmount << endl << endl;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
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

    testBinarySearchTree();
    /*std::vector<Data> players(10000);
    for (int i = 0; i < 10000; i++) {
        players[i] = Data();
    }

    BinarySearchTree playersTree;

    for (int i = 0; i < 10000; i++) {
        playersTree.insert(players[i]);
    }

    //playersTree.print();

    std::cout << std::endl;

    for (int i = 0; i < 2000; i++) {
        playersTree.erase(players[i]);
    }

    std::cout <<"PlayersTree size: " <<playersTree.size()<<"\tHeight: "<<playersTree.height()<<"\n";*/


}
