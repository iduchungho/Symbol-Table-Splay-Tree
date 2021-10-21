#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"
struct Node{
    string var;
    string type;
    string ndata;
    string funcTypeReturn;
    int levelOfBlock;
    bool isGlobal = 0;
    Node(string v , string t)
        : var(v), type(t){}
    Node(){
        this->levelOfBlock = 0;
    }
};
struct TreeNode{
    Node key;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Node *k , TreeNode* p = nullptr, TreeNode* l = nullptr , TreeNode* r = nullptr){
        this->key = *k;
        this->parent = p;
        this->left = l;
        this->right = r;
    }
    TreeNode(){
        this->key = Node();
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

};
class SplayTree{
private:
    TreeNode* root;
    void zig(TreeNode*);
    void zig_zag(TreeNode*);
    void zig_zig(TreeNode*);

    void splay(TreeNode* ,int &);

public:
    SplayTree();
    SplayTree(TreeNode*);
    void inpRoot(TreeNode*);
    TreeNode* returnRoot();
    TreeNode* find(const string& , const int& , int& , int&);
    TreeNode* find(const int&);
    bool _delete(const int&);
    void insert(Node* , int& , int& , const string&);
    void print(TreeNode* , bool);

};
class SymbolTable
{
public:
    SymbolTable() {}
    void run(string filename);
    void INSERT(string & ,const int & ,const string &, SplayTree&);
    void ASSIGN(string & , const int&  ,const string &, SplayTree&);
    void LOOKUP(string & , const int&  ,const string &, SplayTree&);
    void PRINT(SplayTree&);
    bool functionType(const string & , const string& , const int& , int& , int&, SplayTree&);
    void searchLevel(const string& , const int& , SplayTree&);
    TreeNode* findAll(const string&, const int& , int& , int& , SplayTree&);
};
void DestroySplayTree(TreeNode*);
void cSyntaxLine(const string & , SplayTree&);
string cutString(string &, const string&);
TreeNode* newTreeNode(TreeNode*);
bool const_number(const string &);
bool const_string(const string &);
void cAphabetSyntax(const string & ,const string & , SplayTree&);
TreeNode* subtreeMax(TreeNode*);
TreeNode* subtreeMin(TreeNode*);
#endif