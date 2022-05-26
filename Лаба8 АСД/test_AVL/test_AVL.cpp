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
        rank = rand() % 10000 + 1;
        experience = rand() % 10000;
        communityConr = rand() % 1000;
    }

    bool operator< (const Data other) const {
        return (this->rank + this->experience + this->communityConr) < (other.rank + other.experience + other.communityConr);
    }

    bool operator> (const Data other) const {
        return (this->rank + this->experience + this->communityConr) > (other.rank + other.experience + other.communityConr);
    }

    bool operator== (const Data other) const {
        return (this->rank + this->experience + this->communityConr) == (other.rank + other.experience + other.communityConr);
    }
};

struct TreeNode {
    int player;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int height = 1;
};

struct BinarySearchTree {
    TreeNode* root = nullptr;
    int entities = 0;

    //
    bool search(int& somePlayer, TreeNode*& currentNode) {
        if (currentNode == nullptr) return false;
        if (currentNode->player == somePlayer) return true;
        if (currentNode->player < somePlayer)
            return search(somePlayer, currentNode->right);
        else return search(somePlayer, currentNode->left);
    }

    bool find(int& somePlayer) {
        return search(somePlayer, root);
    }
    //

    //
    TreeNode* avl_insert(TreeNode*& sub_root, TreeNode*& insertingPlayer) {
        if (insertingPlayer->player > sub_root->player) {
            if (sub_root->right == nullptr) {
                sub_root->right = insertingPlayer;
            }
            else {
                sub_root->right = avl_insert(sub_root->right, insertingPlayer);
            }
        }
        else {
            if (sub_root->left == nullptr) {
                sub_root->left = insertingPlayer;
            }
            else {
                sub_root->left = avl_insert(sub_root->left, insertingPlayer);
            }
        }
        return balanceNode(sub_root);
    }

    void insert(int& newPlayer) {
        if (find(newPlayer)) return; //unique check

        TreeNode* playerToInsert = new TreeNode;
        playerToInsert->player = newPlayer;

        entities++;
        if (root == nullptr) {       //empty tree case
            root = playerToInsert;
            return;
        }
        else {
            root = avl_insert(root, playerToInsert);
        }
    }
    //

    //functions needed for erase() (now in AVL-tree)

    TreeNode* minimum(TreeNode*& someTree) {
        if (someTree->left == nullptr) return someTree;
        else return minimum(someTree->left);
    }

    TreeNode* removeMinimal(TreeNode*& node) {
        if (node->left == nullptr) {
            return node->right;
        }
        node->left = removeMinimal(node->left);
        return balanceNode(node);
    }

    TreeNode* avl_erase(TreeNode*& sub_root, int& deletePlayer) {
        if (sub_root == nullptr) return 0;
        if (deletePlayer < sub_root->player) sub_root->left = avl_erase(sub_root->left, deletePlayer);
        else if (deletePlayer > sub_root->player) sub_root->right = avl_erase(sub_root->right, deletePlayer);
        else {
            TreeNode* rightChild = sub_root->right;
            TreeNode* leftChild = sub_root->left;
            delete sub_root;
            sub_root = nullptr;
            if (rightChild == nullptr) return leftChild;
            TreeNode* minimal = minimum(rightChild);
            minimal->right = removeMinimal(rightChild);
            minimal->left = leftChild;
            return balanceNode(minimal);
        }
        return balanceNode(sub_root);
    }

    void erase(int& deletePlayer) {
        if (!find(deletePlayer)) return;
        root = avl_erase(root, deletePlayer);
        entities--;
    }
    //

    int size() { return entities; }

    //
    void inorderTraversal(TreeNode*& currNode) {
        if (currNode != nullptr) {
            inorderTraversal(currNode->left);
            std::cout << std::setw(15) << "id: " << currNode->player<<"\n";
            inorderTraversal(currNode->right);
        }
    }

    void print() {
        inorderTraversal(root);
    }
    //

    //
    int maxDepth(TreeNode*& treeRoot) {
        if (treeRoot == nullptr) {
            return 0;
        }
        else {
            int leftDepth = maxDepth(treeRoot->left);
            int rightDepth = maxDepth(treeRoot->right);

            if (leftDepth > rightDepth) return leftDepth + 1;
            else return rightDepth + 1;
        }
    }

    int height() {
        return maxDepth(root);
    }
    //

    //
    void lookInRange(int& minObj, int& maxObj, TreeNode*& treeRoot, int& inRange) {
        if (treeRoot != nullptr) {
            if (treeRoot->player < minObj) lookInRange(minObj, maxObj, treeRoot->right, inRange);
            if (treeRoot->player > maxObj) lookInRange(minObj, maxObj, treeRoot->left, inRange);
            if ((treeRoot->player > minObj || treeRoot->player == minObj) && (treeRoot->player < maxObj || treeRoot->player == maxObj)) {
                lookInRange(minObj, maxObj, treeRoot->left, inRange);
                inRange++;
                lookInRange(minObj, maxObj, treeRoot->right, inRange);
            }
        }
    }

    int findInRange(int& minObj, int& maxObj) {
        int numberInrange = 0;
        lookInRange(minObj, maxObj, root, numberInrange);
        return numberInrange;
    }
    //

    //balancing methods(ritations for AVL tree)

    int getHeight(TreeNode*& node) {
        return node ? node->height : 0;
    }

    int balanceFactor(TreeNode*& node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    void fixHeight(TreeNode*& node) {
        int rightH = getHeight(node->right);
        int leftH = getHeight(node->left);
        node->height = (rightH > leftH ? rightH : leftH) + 1;
    }

    TreeNode* rotateRight(TreeNode*& node) {
        TreeNode* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        if (node == root) {
            root = leftChild;
        }
        fixHeight(node);
        fixHeight(leftChild);
        return leftChild;
    }

    TreeNode* rotateLeft(TreeNode*& node) {
        TreeNode* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        if (node == root) {
            root = rightChild;
        }
        fixHeight(node);
        fixHeight(rightChild);
        return rightChild;
    }

    TreeNode* balanceNode(TreeNode*& node) {
        fixHeight(node);

        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->right) < 0) node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->left) > 0) node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
        // otherwise it is already balanced
        return node;
    }
    //

    // some additional methods:

    //
    void deleteRange(int& minObj, int& maxObj, TreeNode*& treeRoot) {
        if (treeRoot != nullptr) {
            if (treeRoot->player < minObj) deleteRange(minObj, maxObj, treeRoot->right);
            if (treeRoot->player > maxObj) deleteRange(minObj, maxObj, treeRoot->left);
            if ((treeRoot->player > minObj || treeRoot->player == minObj) && (treeRoot->player < maxObj || treeRoot->player == maxObj)) {
                erase(treeRoot->player);
                deleteRange(minObj, maxObj, root);
            }
        }
    }

    void eraseRange(int& minObj, int& maxObj) {
        deleteRange(minObj, maxObj, root);
    }
    //

    void inorderAdding(TreeNode*& currNode) {
        if (currNode != nullptr) {
            inorderAdding(currNode->left);
            insert(currNode->player);
            inorderAdding(currNode->right);
        }
    }

    void merge(BinarySearchTree& otherTree) {
        inorderAdding(otherTree.root);
    }

    void spliting(TreeNode* sub_root, int& obj, BinarySearchTree* tree1, BinarySearchTree* tree2) {
        if (sub_root != nullptr) {
            spliting(sub_root->left, obj, tree1, tree2);
            if (sub_root->player < obj) tree1->insert(sub_root->player);
            else tree2->insert(sub_root->player);
            spliting(sub_root->right, obj, tree1, tree2);
        }
    }

    pair<BinarySearchTree*, BinarySearchTree*> split(int& obj) {
        BinarySearchTree* tree1 = new BinarySearchTree;
        BinarySearchTree* tree2 = new BinarySearchTree;
        spliting(root, obj, tree1, tree2);
        return { tree1, tree2 };
    }
};

/*bool testBinarySearchTree()
{
    srand(time(NULL));
    const int iters = 1000;
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
    cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount << endl << endl;
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
}*/

int main()
{
    srand(time(NULL));

    //testBinarySearchTree();


    std::vector<int> players(20);
    for (int i = 0; i < 20; i++) {
        players[i] = i;
    }

    BinarySearchTree playersTree1;
    BinarySearchTree playersTree2;

    for (int i = 0; i < 10; i++) {
        playersTree1.insert(players[i]);
    }

    for (int i = 10; i < 20; i++) {
        playersTree2.insert(players[i]);
    }

    playersTree1.print();

    std::cout << std::endl;

    playersTree2.print();

    std::cout << std::endl;

    playersTree1.merge(playersTree2);

    playersTree1.print();

    std::cout << std::endl;

    int splitNum = 8;
    pair<BinarySearchTree*, BinarySearchTree*> treees = playersTree1.split(splitNum);

    treees.first->print();

    std::cout << std::endl;

    treees.second->print();
    /*playersTree.print();

    std::cout << std::endl;



    std::cout <<"PlayersTree size: " <<playersTree.size()<<"\tHeight: "<<playersTree.height()<<"\n";

    int min = 4;
    int max = 7;
    playersTree.eraseRange(min, max);

    playersTree.print();*/

}
