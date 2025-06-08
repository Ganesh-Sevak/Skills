//partner: kasli
#include "anagram.h"
#include <iostream>
#include <fstream>

/***
An AnagramDict constructor. This Constructor takes in a filepath
and then creates a binary tree out of all the words inside the
binary tree.

Input:
std::string filename - the path to the file

Output:
N/A
***/
AnagramDict::AnagramDict(std::string filename) {
    filename_ = filename;
    std::string path = "dictionaries/" + filename_;
    std::ifstream file;
    file.open(path.c_str());
   
    std::string word;
    while (file >> word) {
        addWord(word);
    }

    file.close();
}

/***
An AnagramDict member function. This function sorts the given word in
lexicographical order

Input:
std::string word - the word that needs to be sorted

Output:
std::string - the sorted version of the input
***/
std::string AnagramDict::sortWord(std::string word) {
    std::sort(word.begin(), word.end());
    return word;
}

/***
An AnagramDict member function. This function adds a word to the tree.
If the words sorted version already exists in the tree add it to the linked
list of that node. If the sorted word does not exist in the tree create a new
node and insert it into the tree
Duplicated words should not be added to the tree.
Input:
std::string word - the word that needs to inserted

Output:
N/A
***/
void AnagramDict::addWord(std::string word) {
    std::string sorted_word = sortWord(word);

    if (tree.find_node(sorted_word) == NULL) { // the key does not already exist in the tree
        std::list<std::string> data;
        data.push_back(word);
        Node<std::string, std::list<std::string> > *new_node = new Node<std::string, std::list<std::string> > (sorted_word, data);
        tree.insert_node(tree.getRoot(), new_node);
    }
    else { // the key already exists in the tree
        Node<std::string, std::list<std::string> > *node = tree.find_node(sorted_word);
        std::list<std::string>::iterator it;
        std::list<std::string> new_data = node->getData();
        for (it = new_data.begin(); it != new_data.end(); it++) {
            if (*it == word) { // the word already exists in the node's linked list
                return;
            }
        }
        new_data.push_back(word);
        node->setData(new_data);
    }
}

/***
An AnagramDict member function. Does a preorder, postorder, or inorder traversal
and then prints out all the anagrams and words.

The output file should be the traversal order of the tree, but only the data on each line.
View on wiki for more information.

Input:
std::string order - The type of order you want to traverse. Can be "pre", "post", "in"

Output:
N/A
***/
void AnagramDict::saveAnagrams(std::string order) {
    std::string path = "output/" + order+"_"+ filename_;
    std::ofstream file;
    file.open(path.c_str());
    if(!file.is_open()) {
        //create new file
        file.open(path.c_str(),std::ios::out);
    }

    std::list<Node<std::string, std::list<std::string> > > list_of_nodes;
    if (order == "pre") {
        tree.pre_order(tree.getRoot(), list_of_nodes);
    }
    else if (order == "post") {
        tree.post_order(tree.getRoot(), list_of_nodes);
    }
    else if (order == "in") {
        tree.in_order(tree.getRoot(), list_of_nodes);
    }
    std::list<Node<std::string, std::list<std::string> > >::iterator it1;
    std::list<std::string>::iterator it2;

    for (it1 = list_of_nodes.begin(); it1 != list_of_nodes.end(); it1++) {
        std::list<std::string> data = (*it1).getData();
        for (it2 = data.begin(); it2 != data.end(); it2++) {
            file << *it2 << " ";
        }
        file << std::endl;
    }

    file.close();
}