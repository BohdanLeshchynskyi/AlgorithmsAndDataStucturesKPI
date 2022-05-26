#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
    bool isLeaf = false;
    std::unordered_map<char, Node*> children;
    std::vector<char> children_keys;
};

struct Trie {
    Node* root;
    Trie() {
        root = new Node;
        root->isLeaf = false;
    }
    
    void insert(std::string word) {
        Node* initialRoot = root;
        for (int i = 0; i < word.length(); i++) {
            if (root->children[word[i]] == 0) {
                root->children_keys.push_back(word[i]);
                root->children[word[i]] = new Node;
                if(i == word.length() - 1) {
                    root->children[word[i]]->isLeaf = true;
                    root = initialRoot;
                    return;
                }
            }
            root = root->children[word[i]];
        }
        root = initialRoot;
    }
    
    void findSuffixes(std::vector<std::string>* resultWords, Node* sub_root, std::string prefix) {
        for (int i = 0; i < sub_root->children_keys.size(); i++) {
            std::string initialPrefix = prefix;
            findSuffixes(resultWords, sub_root->children[sub_root->children_keys[i]], prefix.append(1, sub_root->children_keys[i]));
            prefix = initialPrefix;
        }
        if(sub_root->isLeaf == true) {
            resultWords->push_back(prefix);
        }
    }

    std::vector<std::string> findByPrefix(std::string prefix) {
        std::vector<std::string> resultWords;
        Node* initialRoot = root;
        for (int i = 0; i < prefix.length(); i++) {
            if(root->children[prefix[i]] == 0){
                std::cout << "No such prefix in Trie((";
                return {}; // returns an empty vector
            }
            root = root->children[prefix[i]];
        }
        findSuffixes(&resultWords, root, prefix);
        root = initialRoot;
        return resultWords;
    }
};

void fillTree(Trie* trie) {
    std::string word;
    std::ifstream file("words_alpha.txt");

    while (getline(file, word)) {
        trie->insert(word);
    }

    file.close();
}

void printOutVector(std::vector<std::string> wordsVec) {
    for (int i = 0; i < wordsVec.size(); i++) {
        std::cout << std::setw(5) << wordsVec[i] << ", ";
    }
}

int main()
{
    Trie trie;
    std::string word;
    int choise = 0;
    std::vector<std::string> foundWords;
    fillTree(&trie);

    std::cout << trie.root->children.size();
    while (true) {
        system("cls");

        std::cout << "Enter a word for autocompletion: ";
        std::cin >> word;
        foundWords = trie.findByPrefix(word);
        printOutVector(foundWords);

        std::cout << std::endl;
        std::cout << "Countinue? (1/0) :";
        std::cin >> choise;

        if (choise == 0) {
            break;
        }
    }
}