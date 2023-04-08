#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class TreeNode {            //define a simple class
    public:                 //make a basic binary node
        int Node;   
        TreeNode *left;
        TreeNode *right;

};

//functions directly related to the tree
void Decrypt(vector<int> CodeArr, string DecodedString, TreeNode* Root);        //decrypt the encoded message
TreeNode* BuildTree(vector<int> InOrd, vector<int> PreOrd, int Start, int End); //build the binary Tree from inorder and preorder travs(complete)

//functions to create necessary vectors
void BuildCodeTable(string Filename, vector<int> &arr);                       //build the code array(complete)
void BuildTraversal(string Filename, vector<int> &TraversalTable);           //build an array for either traversal(complete)

//helpful functions
int searchTraversal(vector<int> Traversal, int NodeVal);                    //search a traversal array to find an index(complete)
TreeNode* BuildNode(int Val);                                               //create a new node for the tree(complete)

int main(int argc, char *argv[]) {
    string FileName = argv[3];
    vector<int> codeArray;
    BuildCodeTable(FileName, codeArray);                    //build the encoded table
    vector<int> InTrav;
    vector<int> PreTrav;
    FileName = argv[1];
    BuildTraversal(FileName, InTrav);
    FileName = argv[2];
    BuildTraversal(FileName, PreTrav);                                      //build both traversals
    TreeNode* Root = BuildTree(InTrav, PreTrav, 0, InTrav.size() - 1);          //build the tree
    string DecodedMessage;
    Decrypt(codeArray, DecodedMessage, Root);                               //decrypt and build the message
    cout << DecodedMessage;

    return 0;
}

void BuildCodeTable(string Filename, vector<int> &arr) {
    string tempCode;                                    //function to build an array to use when decoding
    string tempLine;                                    //array will be digit by digit of encoded message
    ifstream File;                                      //first store all digits as one large string
    File.open(Filename);                                //then convert to integers in the array
    while(getline(File, tempLine)) {
        tempCode = tempCode + tempLine;
    }
    File.close();
    int size = tempCode.length();
    arr.resize(size);
    for(int i = 0; i < size; i++) {
        arr.at(i) = tempCode.at(i) - '0';
    }
}

void BuildTraversal(string Filename, vector<int> &TraversalTable) {
    ifstream File;                                      //build an array from a traversal input
    File.open(Filename);                                //store each individual value to be a node value
    int tempInt;                                        //read these in from given files
    int size = 0;                                       //make sure each int has a spot in the vector (so resize to build)
    while(File >> tempInt) {
        size++;
        TraversalTable.resize(size);
        TraversalTable.at(size - 1) = tempInt;
    }
    File.close();
}

TreeNode* BuildNode(int Val) {                          //build each node for the tree
    TreeNode* New = new TreeNode();                     //allocate memory for the node
    New->right = NULL;                                  //initialize values
    New->left = NULL;
    New->Node = Val;
    return New;
}

int searchTraversal(vector<int> Traversal, int NodeVal) {
    int size = Traversal.size();                        //find an index of a value
    for(int i = 0; i < size; i++) {                     //interate through a traversal's array to find index
        if(NodeVal == Traversal.at(i)) {
            return i;
        }
    }
    return -1;
}

TreeNode* BuildTree(vector<int> InOrd, vector<int> PreOrd, int Start, int End) {
    int iInd;                                                       //build a binary tree
    static int pInd = 0;                                            //recursive call to build
    TreeNode* temp = BuildNode(PreOrd[pInd++]);                     //builds left first then right
    if(Start == End) { return temp; }                               //ends when indexes meet
    iInd = searchTraversal(InOrd, temp->Node);
    temp->left = BuildTree(InOrd, PreOrd, Start, iInd - 1);
    temp->right = BuildTree(InOrd, PreOrd, iInd + 1, End);
    return temp;
}

void Decrypt(vector<int> CodeArr, string DecodedString, TreeNode* Root) {
    int loops = CodeArr.size();                                     //decrypt the message
    TreeNode* curr = Root;                                          //follow the binary code
    char decodedChar;                                               //go down the tree, going left at 0, right at 1
    for(int i = 0; i < loops; i++) {                                //decode the character and print when hitting a leaf
        if(CodeArr.at(i) == 0) {
            curr = curr->left;
        } else if(CodeArr.at(i) == 1) {
            curr = curr->right;
        }
        if(curr->right == NULL && curr->left == NULL) {
            decodedChar = (char)curr->Node;
            cout << decodedChar;
            curr = Root;
        }
    }
    return;
}