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
class queueString{
public:
    string que[1000];
    int level;
    queueString(){
        level = 0;
    }
    void __pop();
    void __push(const string&);
    string __front();
    void __clear();
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
    void print(TreeNode* , bool&);
    void insert(Node*, int& , int& , const string&);
    bool _delete(const string& , const int&);
    TreeNode* returnRoot();
    TreeNode* findLocal(const string& , const int& , int& , int&);
    TreeNode* find(const int&);
    TreeNode* findGlobal(const string& ,const int & , int& , int&);
    static int numComp(TreeNode* , TreeNode*);

};
class SymbolTable
{
public:
    SymbolTable() {}
    void run(string filename);
    void INSERT(string & ,const int & ,const string &, SplayTree& , queueString&);
    void ASSIGN(string & , const int&  ,const string &, SplayTree&);
    void LOOKUP(string & , const int&  ,const string &, SplayTree&);
    void PRINT(SplayTree&);
    bool functionType(const string & , const string& , const int& , int& , int&, SplayTree&);
    //void searchLevel(const string& , const int& , SplayTree&);
};
void DestroySplayTree(TreeNode*);
void cSyntaxLine(const string & , SplayTree&);
void cAphabetSyntax(const string & ,const string & , SplayTree&);
void preOrder(TreeNode* , TreeNode*,const string&);
void __delete(queueString& , const int& , SplayTree&);
bool const_number(const string &);
bool const_string(const string &);
string cutString(string &, const string&);
TreeNode* newTreeNode(TreeNode*);
TreeNode* subtreeMax(TreeNode*);
TreeNode* subtreeMin(TreeNode*);

#endif