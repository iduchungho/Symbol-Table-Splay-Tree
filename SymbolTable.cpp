#include "SymbolTable.h"
TreeNode* newTreeNode(TreeNode* root){
    if(!root){
        root = new TreeNode;
    }
    return root;
}
void DestroySplayTree(TreeNode* root){

}
void cSyntaxLine(const string &line){
    int size_ = line.length();
    int space = 0;
    string syntax = line;
    for(int i = 0; i < size_; i++){
        if(line[i] == ' ') ++space;
    }
    if(space > 3)
        throw InvalidInstruction(line);
    syntax = cutString(syntax , " ");
    if(syntax == "INSERT"){
        if(space != 3) throw InvalidInstruction(line);
    }
    else if(syntax == "ASSIGN"){
        if(space != 2) throw InvalidInstruction(line);
    }
    else if(syntax == "PRINT" || syntax == "END" || syntax == "BEGIN" ){
        if(space != 0) throw InvalidInstruction(line);
    }
}
string cutString(string& line , const string& char_pos){
    size_t f = line.find(char_pos);
    if(f != string::npos){
        string s = line.substr(0 , f);
        line.erase(0 , f+ 1);
        return s;
    }
    else return line;
}
bool const_number(const string &number){
    int length = number.length();
    for(int i = 0; i < length; i++){
        if(number[i] < '0' || number[i] > '9') return false;
    }
    return true;
}
bool const_string(const string &string){
    int length = string.length();
    if(string[0] == 39 && string[length - 1] == 39){
        for(int j = 1; j < length - 1 ; ++j){
            if(string[j] == 32) continue;
            else if(string[j] < 48 || (string[j] > 57 && string[j] < 65)
                                    ||(string[j] > 90 && string[j] < 97) || string[j] > 122){
                return false;
            }
        }
    }
    else return false;
    return true;
}
void SplayTree::zig(TreeNode* current){

    /*
        zig , zag format:

            22                       15
           / \          zig         / \
         15   24     ------->     10   22
        / \          <-------         / \
       10  16          zag           16  24

    */

    TreeNode* p = current->parent;
    if(p->left = current){
        TreeNode* A = current->left;
        TreeNode* B = current->right;
        TreeNode* C = p -> right;

        current->parent = nullptr;
        current->right = p;
        p->parent = current;
        p->left = B;

        if(B) B->parent = p;
    }
    else{
        TreeNode* A = p->left;
        TreeNode* B = current->left;
        TreeNode* C = current->right;

        current->parent = nullptr;
        current->left = p;

        p->parent = current;
        p->right = B;

        if(B) B->parent = p;
    }
    
}
void SplayTree::zig_zag(TreeNode* current){
    TreeNode* par = current->parent;
    TreeNode* grand = par->parent;
    if(par -> right == current){ // zig zag
        TreeNode* A = par->left;
        TreeNode* B = current->left;
        TreeNode* C = current->right;
        TreeNode* D = grand->right;

        current -> parent = grand -> parent;
        current -> left = par;
        current -> right = grand;

        par->parent = current;
        par->right = B;

        grand -> parent = current;
        grand -> left = C;

        if(current -> parent){
            if(current -> parent -> left == current)
                current -> parent -> left = current;
            else current -> parent -> right = current;
        }
        if(B) B->parent = par;
        if(C) C->parent = grand;

    }
    else{ // zag zig
        TreeNode* A = par->left;
        TreeNode* B = current->left;
        TreeNode* C = current->right;
        TreeNode* D = grand->right;

        current -> parent = grand->parent;
        current -> left = grand;
        current -> right = par;

        grand -> right = B;
        grand->parent = current;

        par->left = C;
        par->parent = current;

        if(current -> parent){
            if(current -> parent -> left == current)
                current -> parent -> left = current;
            else current -> parent -> right = current;
        }
        if(B) B->parent = grand;
        if(C) C->parent = par;

    }
}
void SplayTree::zig_zig(TreeNode* current){
    TreeNode* par = current->parent;
    TreeNode* grand = par->parent;
    if(par -> left == current){ // zig zig
        TreeNode* A = par->left;
        TreeNode* B = current->left;
        TreeNode* C = current->right;
        TreeNode* D = grand->right;

        current -> parent = grand->parent;
        current -> right = par;
        par->parent = current;

        par -> right = grand;
        par->left = B;

        grand -> parent = par;
        grand->left = C;

        if(current -> parent){
            if(current -> parent -> left == current)
                current -> parent -> left = current;
            else current -> parent -> right = current;
        }
        if(C) C->parent = grand;
        if(B) B->parent = par;

    }
    else{ // zag zag
        TreeNode* A = par->left;
        TreeNode* B = current->left;
        TreeNode* C = current->right;
        TreeNode* D = grand->right;

        current -> parent = grand->parent;
        current -> left = par;
        par->parent = current;

        par -> left = grand;
        par->right = C;

        grand -> parent = par;
        grand->right = B;

        if(current -> parent){
            if(current -> parent -> left == current)
                current -> parent -> left = current;
            else current -> parent -> right = current;
        }
        if(C) C->parent = par;
        if(B) B->parent = grand;

    }
}
void SplayTree::find(TreeNode* root , const Node& element){

}
void SplayTree::_delete(TreeNode* root , const Node& element){

}
void SplayTree::insert(TreeNode* root , const Node& element){

}
void SplayTree::print(TreeNode* root){

}
void SplayTree::inpRoot(TreeNode* root){
    this->root = root;
}
TreeNode* SplayTree::returnRoot(){
    return this->root;
}
void SplayTree::splay(TreeNode* root){

}
void SymbolTable::run(string filename){
    SplayTree Database;
    string line;
    fstream file;
    Database.inpRoot(nullptr); // root = new TreeNode; root->key(abc ,xyz ,gmt);
    string error;
    file.open(filename , ios::in);
    while(!file.eof()){
        getline(file, line);
        cSyntaxLine(line);
        error = line;
    }
    file.close();
    DestroySplayTree(Database.returnRoot());
}