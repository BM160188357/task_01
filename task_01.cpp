#include <iostream>
#include <cstdlib>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


class ast_tree{

    private:
        string key;
        ast_tree *leftChild;
        ast_tree *rightChild;
    public:
        ast_tree(string rootObj){
            this->key = rootObj;
            this->leftChild = NULL;
            this->rightChild = NULL;
        }

        void insertLeft(string newNode){
            if (this->leftChild == NULL){
            this->leftChild = new ast_tree(newNode);
            }
            else {
            ast_tree *t = new ast_tree(newNode);
            t->leftChild = this->leftChild;
            this->leftChild = t;
            }
        }

        void insertRight(string newNode){
            if (this->rightChild == NULL){
            this->rightChild = new ast_tree(newNode);
            }
            else {
            ast_tree *t = new ast_tree(newNode);
            t->rightChild = this->rightChild;
            this->rightChild = t;
            }
        }

        ast_tree *getRightChild(){
            return this->rightChild;
        }

        ast_tree *getLeftChild(){
            return this->leftChild;
        }

        void setRootVal(string obj){
            this->key = obj;
        }

        string getRootVal(){
            return this->key;
        }
};

ast_tree *buildParseTree(string qfpexp){
    string buf;
    stringstream ss(qfpexp);
    vector<string>qflist;
    while (ss >> buf){
        qflist.push_back(buf);
    }
    stack<ast_tree*> pStack;
    ast_tree *eTree = new ast_tree(" ");
    pStack.push(eTree);
    ast_tree *currentTree = eTree;

    string arr[] = { "+", "*", "/", "-" };
    vector<string> vect(arr,arr+(sizeof(arr)/ sizeof(arr[0])));

    string arr1[] = { "+", "*", "/", "-" };
    vector<string> vect1(arr1,arr1+(sizeof(arr1)/ sizeof(arr1[0])));

    for (unsigned int i = 0; i<qflist.size(); i++){

        if (qflist[i] == " ( "){
            currentTree->insertLeft(" ) ");
            pStack.push(currentTree);
            currentTree = currentTree->getLeftChild();
        }

        else if (find(vect.begin(), vect.end(), qflist[i]) != vect.end()){
            currentTree->setRootVal(qflist[i]);
            currentTree->insertRight(" ( ");
            pStack.push(currentTree);
            currentTree = currentTree->getRightChild();
        }

        else if (qflist[i] == " ) "){
            currentTree = pStack.top();
            pStack.pop();
        }

        else if (find(vect1.begin(), vect.end(), qflist[i]) == vect.end()) {
            try {
                currentTree->setRootVal(qflist[i]);
                ast_tree *parent = pStack.top();
                pStack.pop();
                currentTree = parent;
            }

            catch (string ValueError ){
                cerr << " token " << qflist[i] << " is not a valid integer"<<endl;
            }
        }
    }
    return eTree;
}

void postorder(ast_tree *tree){
    if (tree != NULL){
        postorder(tree->getLeftChild());
        postorder(tree->getRightChild());
        cout << tree->getRootVal() << endl;
    }
}

int main() {

    ast_tree *pt = buildParseTree(" 4 + 5 + 7 / 2 ");
 
    postorder(pt);

    return 0;
}

