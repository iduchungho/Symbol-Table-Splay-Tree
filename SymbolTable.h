#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "main.h"
struct _function{
    string type1 , var1;
    string type2 , var2;
    string returnType;
    _function()
        :type1(""), var1(""), type2(""), var2(""), returnType(""){}
};
struct Node{
    string var;
    string type;
    _function func;
    bool gloScope;
    bool isfunc;
    Node(string v , string t , bool scope)
        : var(v), type(t), gloScope(scope), isfunc(0){}
    Node(string v, string type1 , string type2 , string returnType){
        this->var = v;
        this->func.type1 = type1;
        this->func.type2 = type2;
        this->func.returnType = returnType;
        this->isfunc = 1;
    }
    Node(){
        this->gloScope = true;
        this->isfunc = 0;
    }
};
struct TreeNode{
    Node key;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Node k , TreeNode* p, TreeNode* l , TreeNode* r){
        this->key = k;
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

    void splay(TreeNode*);
public:
    void inpRoot(TreeNode*);
    TreeNode* returnRoot();
    void find(TreeNode* , const Node&);
    void _delete(TreeNode* , const Node&);
    void insert(TreeNode* , const Node&);
    void print(TreeNode*);

};
class SymbolTable
{
public:
    SymbolTable() {}
    void run(string filename);
    void INSERT(string &);
    void ASSIGN(string &);
    void LOOKUP(string &);
    void PRINT(string &);
};
void DestroySplayTree(TreeNode*);
void cSyntaxLine(const string &);
string cutString(string &, const string&);
TreeNode* newTreeNode(TreeNode*);
bool const_number(const string &);
bool const_string(const string &);
#endif