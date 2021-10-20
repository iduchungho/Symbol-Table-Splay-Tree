#include "SymbolTable.h"
TreeNode* newTreeNode(TreeNode* root){
    if(!root){
        root = new TreeNode;
    }
    return root;
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
void cAphabetSyntax (const string &line , const string& error){
    if(line[0] < 65 || (line[0] > 90 && line[0] < 97) || line[0] > 122)
        throw InvalidInstruction(error);

    int size_ = line.length();

    for(int j = 1; j < size_  ; ++j){
        if(line[j] == 95) continue;
        else if(line[j] < 48 || (line[j] > 57 && line[j] < 65)
                ||(line[j] > 90 && line[j] < 97) || line[j] > 122){
            throw InvalidInstruction(error);
        }
    }
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
    if(p->left == current){
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
            if(current -> parent -> left == grand)
                current -> parent -> left = current;
            else current -> parent -> right = current;
        }
        if(B) B->parent = par;
        if(C) C->parent = grand;

    }
    else{ // zag zig
        TreeNode* A = grand->left;
        TreeNode* B = current->left;
        TreeNode* C = current->right;
        TreeNode* D = par->right;

        current -> parent = grand->parent;
        current -> left = grand;
        current -> right = par;

        grand -> right = B;
        grand->parent = current;

        par->left = C;
        par->parent = current;

        if(current -> parent){
            if(current -> parent -> left == grand)
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
        TreeNode* A = current->left;
        TreeNode* B = current->right;
        TreeNode* C = par->right;
        TreeNode* D = grand->right;

        current -> parent = grand->parent;
        current -> right = par;
        par->parent = current;

        par -> right = grand;
        par->left = B;

        grand -> parent = par;
        grand->left = C;

        if(current -> parent){
            if(current -> parent -> left == grand)
                current -> parent -> left = current;
            else current -> parent -> right = current;
        }
        if(C) C->parent = grand;
        if(B) B->parent = par;

    }
    else{ // zag zag
        TreeNode* A = grand->left;
        TreeNode* B = par->left;
        TreeNode* C = current->left;
        TreeNode* D = current->right;

        current -> parent = grand->parent;
        current -> left = par;
        par->parent = current;

        par -> left = grand;
        par->right = C;

        grand -> parent = par;
        grand->right = B;

        if(current -> parent){
            if(current -> parent -> left == grand)
                current -> parent -> left = current;
            else current -> parent -> right = current;
        }
        if(C) C->parent = par;
        if(B) B->parent = grand;

    }
}
void SplayTree::inpRoot(TreeNode* root){
    this->root = root;
}
TreeNode* SplayTree::returnRoot(){
    return this->root;
}
SplayTree::SplayTree(){
    this->root = NULL;
}
SplayTree::SplayTree(TreeNode* rt){
    this->root = rt;
}
void DestroySplayTree(TreeNode* root){

}
TreeNode* SplayTree::find(const string& element, const int& level , int& num_comp , int& num_splay){
    TreeNode* cur = this->root;
    TreeNode* ret = nullptr;
    while(cur){
        if(level < cur->key.levelOfBlock){
            ++num_comp;
            cur = cur->left;
        }
        else if(level > cur->key.levelOfBlock){
            ++num_comp;
            cur = cur->right;
        }
        else{
            if(element < cur->key.var){
                ++num_comp;
                cur = cur->left;
            }
            else if(element > cur->key.var){
                ++num_comp;
                cur = cur->right;
            }
            else{
                ++num_comp;
                ret = cur;
                break;
            }
            
        }
    }
    //int num_splay = 0;
    if(ret) splay(ret, num_splay);
    return ret;

}
void SplayTree::_delete(TreeNode* root , const Node& element){

}
void SplayTree::insert(Node* element , int& num_comp , int& num_splay , const string& error){
    if(!root){
        root = new TreeNode(element);
        return;
    }
    TreeNode* cur = this->root;
    while(cur){
        if(element->levelOfBlock < cur ->key.levelOfBlock){
            ++num_comp;
            if(!cur->left){
                TreeNode* newNode = new TreeNode(element);
                cur->left = newNode;
                newNode->parent = cur;
                splay(newNode , num_splay);
                return;
            }
            else cur = cur->left;
        }
        else if (element->levelOfBlock > cur ->key.levelOfBlock){
            ++num_comp;
            if(!cur->right){
                TreeNode* newTNode = new TreeNode(element);
                cur->right = newTNode;
                newTNode->parent = cur;
                splay(newTNode , num_splay);
                return;
            }
            else cur = cur->right;
        }
        else{

            if(element->var.compare(cur->key.var) < 0){
                ++num_comp;
                if(!cur->left){
                    TreeNode* newTNode = new TreeNode(element);
                    cur->left = newTNode;
                    newTNode->parent = cur;
                    splay(newTNode , num_splay);
                    return;
                }
                else cur = cur->left;
            }
            else if (element->var.compare(cur->key.var) > 0){
                ++num_comp;
                if(!cur->right){
                    TreeNode* newTNode = new TreeNode(element);
                    cur->right = newTNode;
                    newTNode->parent = cur;
                    splay(newTNode , num_splay);
                    return;
                }
                else cur = cur->right;
            }
            else{
                ++num_comp;
                throw Redeclared(error);
                //++num_comp;
                splay(cur , num_splay);
                return;
            }
        }
    }
}
void SplayTree::print(TreeNode* root){

}
void SplayTree::splay(TreeNode* cur , int& num_splay){
    while(cur->parent){
        TreeNode* p = cur->parent;
        TreeNode* g = p->parent;
        if(!g) zig(cur);
        else if(g->left == p && p->left == cur) zig_zig(cur);
        else if(g->right == p && p->right == cur) zig_zig(cur);
        else zig_zag(cur);
    }
    if(cur != this->root) ++num_splay;
    this->root = cur;
}
void SymbolTable::INSERT(string& line ,const int &level, const string & error, SplayTree& data){
    string identifier_name = cutString(line ," ");
    string type = cutString(line ," ");// check syntax
    string _static = cutString(line ," "); // check syntax
    bool isStatic = 1;

    if(_static == "true") isStatic = 1;
    else if(_static == "false") isStatic = 0;

    int num_comp = 0;
    int num_splay = 0;

    cAphabetSyntax(identifier_name , error);
    Node* newNode;

    if(type[0] == '('){
        if(!isStatic && level != 0) throw InvalidDeclaration(error);

        string retype;
        size_t f = type.find("->");
        if(f != string::npos){
            retype = type.substr(f + 2, type.length());
            type.erase(f , type.length());
        }

        newNode = new Node(identifier_name , type);
        newNode->funcTypeReturn = retype;
        if(isStatic) newNode->levelOfBlock = 0;
        else newNode->levelOfBlock = level;
    }
    else{
        newNode = new Node(identifier_name , type);
        if(isStatic) newNode->levelOfBlock = 0;
        else newNode->levelOfBlock = level;
    }

    data.insert(newNode , num_comp , num_splay , error);
    delete newNode;

    cout << num_comp << " " << num_splay << endl;
}
bool SymbolTable::functionType(const string& line , const int& level ,int& num_comp , int& num_splay , SplayTree& data){
    
    string curline = line;
    string identifier_name = cutString(curline ," ");
    string value = cutString(curline ," ");
    string funcName;

    size_t f = value.find("(");
    if(f != string::npos){
        funcName = value.substr(f);
        value.erase(0 , f);
    }

    TreeNode* is_found = data.find(funcName , level , num_comp , num_splay);
    if(!is_found) return 0;

    string fVarName = value;
    string fTypeName = is_found->key.type;
    string funcTypeRet = is_found->key.funcTypeReturn;
    return 1;
}
void SymbolTable::ASSIGN(string& line, const int& level, const string& error , SplayTree& data){
    string identifier_name = cutString(line ," ");
    string value = cutString(line ," ");

    // TreeNode* is_found = data.find(identifier_name, level);
    // if(!is_found) throw Undeclared(error);

    int num_comp = 0;
    int num_splay = 0;

    if(value.back() != ')'){
        TreeNode* is_found = data.find(identifier_name, level , num_comp , num_splay);
        if(!is_found) throw Undeclared(error);

        if(is_found->key.type == "string" && const_string(value)) is_found->key.ndata = value;
        else if(is_found->key.type == "number" && const_number(value)) is_found->key.ndata = value;
        else throw TypeMismatch(error);
    }
    else{
        functionType(line , level , num_comp, num_splay , data);
    }


    cout << num_comp << " " << num_splay << endl;
}
void SymbolTable::LOOKUP(string& line , SplayTree& data){

}
void SymbolTable::PRINT(string& line , SplayTree& data){

}
void SymbolTable::run(string filename){
    SplayTree Database;
    string line;
    fstream file;
    Database.inpRoot(nullptr); // root = new TreeNode; root->key(abc ,xyz ,gmt);
    string error;
    int level = 0;
    file.open(filename , ios::in);
    while(!file.eof()){
        getline(file, line);
        cSyntaxLine(line);
        error = line;

        string TYPE = cutString(line , " ");

        if(TYPE == "INSERT"){
            INSERT(line, level , error, Database);
        }
        else if(TYPE == "ASSIGN"){
            ASSIGN(line , level, error, Database);
        }
        else if(TYPE == "LOOKUP"){

        }
        else if(TYPE == "BEGIN"){

        }
        else if(TYPE == "END"){

        }
    }
    file.close();
    DestroySplayTree(Database.returnRoot());
}