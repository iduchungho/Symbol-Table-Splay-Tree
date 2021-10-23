#include "SymbolTable.h"
void DestroySplayTree(TreeNode* root){
    if(!root) return;
    DestroySplayTree(root->left);
    DestroySplayTree(root->right);
    TreeNode* p = root;
    delete p;
}
TreeNode* subtreeMax(TreeNode* root){
    TreeNode* cur = root;
    while(cur->right) cur = cur->right;
    return cur;
}
TreeNode* subtreeMin(TreeNode* root){
    TreeNode* cur = root;
    while(cur->left) cur = cur->left;
    return cur;
}
TreeNode* newTreeNode(TreeNode* root){
    if(!root){
        root = new TreeNode;
    }
    return root;
}
void cSyntaxLine(const string &line , SplayTree &data){
    bool correct = 0;

    if(!correct){
        regex re("INSERT ([a-z]\\w*) ((string|number)|(\\(((string|number)(,(string|number))*)*)\\)->(string|number)) (true|false)");
        if(regex_match(line, re)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re1("ASSIGN [a-z]\\w* ((\\d+)|('\\w*')|([a-z]\\w*)\\(.*\\)|([a-z]\\w*))");
        if(regex_match(line, re1)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re2("BEGIN");
        if(regex_match(line, re2)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re3("END");
        if(regex_match(line, re3)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re4("PRINT");
        if(regex_match(line, re4)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re5("LOOKUP ([a-z]\\w*)");
        if(regex_match(line, re5)) correct = 1;
        else correct = 0;
    }

    if(!correct){
        DestroySplayTree(data.returnRoot());
        throw TypeMismatch(line);
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
void cAphabetSyntax (const string &line , const string& error , SplayTree& data){
    if(line[0] < 65 || (line[0] > 90 && line[0] < 97) || line[0] > 122){
        DestroySplayTree(data.returnRoot());
        throw InvalidInstruction(error);
    }

    int size_ = line.length();

    for(int j = 1; j < size_  ; ++j){
        if(line[j] == 95) continue;
        else if(line[j] < 48 || (line[j] > 57 && line[j] < 65)
                ||(line[j] > 90 && line[j] < 97) || line[j] > 122){
            DestroySplayTree(data.returnRoot());
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
TreeNode* SplayTree::findLocal(const string& element, const int& level , int& num_comp ,int& num_splay){
    TreeNode* cur = this->root;
    TreeNode* ret = nullptr;
    while(cur){
        if(level < cur->key.levelOfBlock){
            cur = cur->left;
        }
        else if(level > cur->key.levelOfBlock){
            cur = cur->right;
        }
        else{
            if(element < cur->key.var){
                cur = cur->left;
            }
            else if(element > cur->key.var){
                cur = cur->right;
            }
            else{
                ret = cur;
                break;
            }
            
        }
    }
    //int num_splay = 0;
    num_comp = numComp(ret, this->root);
    if(ret) splay(ret, num_splay);
    return ret;

}
TreeNode* SplayTree::find(const int& level){
    TreeNode* cur = this->root;
    TreeNode* ret = nullptr;
    while(cur){
        if(level < cur->key.levelOfBlock){
            //++num_comp;
            cur = cur->left;
        }
        else if(level > cur->key.levelOfBlock){
            //++num_comp;
            cur = cur->right;
        }
        else{
            ret = cur;
            break;
        }
    }
    int num_splay = 0;
    if(ret) splay(ret, num_splay);
    return ret;
}
bool SplayTree::_delete(const int& lev){
    
    TreeNode* del = nullptr;
    del = find(lev);
    if(!del) return 0;

    TreeNode* L = del->left;
    TreeNode* R = del->right;

    if(!L && !R){
        this->root = nullptr;
    }
    else if(!L){
        TreeNode* cur = subtreeMin(R);
        int a = 0;
        splay(cur , a);
    }
    else if(!R){
        TreeNode* cur = subtreeMax(L);
        int a = 0;
        splay(cur , a);
    }
    else{
        TreeNode* M = subtreeMax(L);
        int a = 0;
        splay(M , a);
        M->right = R;
        R->parent = M;
    }
    if(del-> parent){
        if(del->parent->left == del) del->parent->left = nullptr;
        else if(del->parent->right == del) del->parent->right = nullptr;
    }
    delete del;
    return 1;


}
void SplayTree::insert(Node* element, int&num_comp ,int& num_splay , const string& error){
    if(!root){
        root = new TreeNode(element);
        return;
    }
    TreeNode* cur = this->root;
    while(cur){
        if(element->levelOfBlock < cur ->key.levelOfBlock){
            if(!cur->left){
                TreeNode* newTNode = new TreeNode(element);
                cur->left = newTNode;
                newTNode->parent = cur;
                num_comp += numComp(newTNode , this->root);
                --num_comp;
                splay(newTNode , num_splay);
                return;
            }
            else cur = cur->left;
        }
        else if (element->levelOfBlock > cur ->key.levelOfBlock){
            if(!cur->right){
                TreeNode* newTNode = new TreeNode(element);
                cur->right = newTNode;
                newTNode->parent = cur;
                num_comp += numComp(newTNode , this->root);
                --num_comp;
                splay(newTNode , num_splay);
                return;
            }
            else cur = cur->right;
        }
        else{

            if(element->var.compare(cur->key.var) < 0){
                if(!cur->left){
                    TreeNode* newTNode = new TreeNode(element);
                    cur->left = newTNode;
                    newTNode->parent = cur;
                    num_comp += numComp(newTNode , this->root);
                    --num_comp;
                    splay(newTNode , num_splay);
                    return;
                }
                else cur = cur->left;
            }
            else if (element->var.compare(cur->key.var) > 0){
                if(!cur->right){
                    TreeNode* newTNode = new TreeNode(element);
                    cur->right = newTNode;
                    newTNode->parent = cur;
                    num_comp += numComp(newTNode , this->root);
                    --num_comp;
                    splay(newTNode , num_splay);
                    return;
                }
                else cur = cur->right;
            }
            else{
                DestroySplayTree(this->root);
                throw Redeclared(error);
                //++num_comp;
                splay(cur , num_splay);
                return;
            }
        }
    }
}
void SplayTree::print(TreeNode* root , bool f = 0){
    if(!root) return;
    if(f == 0){
        f = 1;
        cout << root->key.var << "//" << root->key.levelOfBlock;
    }
    else cout << " " << root->key.var << "//" << root->key.levelOfBlock;
    print(root->left , f);
    print(root->right , f);
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

    cAphabetSyntax(identifier_name , error , data);
    Node* newNode;

    if(type[0] == '('){
        if(!isStatic && level != 0) {
            DestroySplayTree(data.returnRoot());
            throw InvalidDeclaration(error);
        }

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

    data.insert(newNode,num_comp ,num_splay , error);
    delete newNode;

    cout << num_comp << " " << num_splay << endl;
}
bool SymbolTable::functionType(const string& line , const string& error, const int& level , int& num_comp, int& num_splay , SplayTree& data){
    
    string curline = line;
    string identifier_name = cutString(curline ," ");
    string value = cutString(curline ," ");
    string data_ = value;
    string funcName;

    size_t f = value.find("(");
    if(f != string::npos){
        funcName = value.substr(0 , f);
        value.erase(0 , f);
    }

    TreeNode* find = data.findGlobal(funcName , level, num_comp ,num_splay);

    if(!find) {
        DestroySplayTree(data.returnRoot());
        throw Undeclared(error);
    }

    string fVarName = value; //(1,1) (a,b)
    string fTypeName = find->key.type; //(string,string) of function
    string funcTypeRet = find->key.funcTypeReturn; //->string of function

    fVarName.erase(0 , 1);
    fVarName.pop_back();
    fTypeName.erase(0 , 1);
    fTypeName.pop_back();

    while(!fVarName.empty() && !fTypeName.empty()){
        size_t fvar = fVarName.find(",");
        size_t ftype = fTypeName.find(",");
        if(fvar != string::npos && ftype != string::npos){

            string var = fVarName.substr(0, fvar);
            string type = fTypeName.substr(0 , ftype);

            if(const_string(var) && type == "string") {

                fVarName.erase(0 , fvar + 1);
                fTypeName.erase(0 , ftype + 1);

            }
            else if(const_number(var) && type == "number") {

                fVarName.erase(0 , fvar + 1);
                fTypeName.erase(0 , ftype + 1);

            }
            else {
                TreeNode* TNvar1 = data.findGlobal(var , level , num_comp , num_splay);
                if(TNvar1){
                    if(TNvar1->key.type != type){
                        DestroySplayTree(data.returnRoot());
                        throw TypeMismatch(error);
                    }
                    fVarName.erase(0 , fvar + 1);
                    fTypeName.erase(0 , ftype + 1);
                }
                else{
                    DestroySplayTree(data.returnRoot());
                    throw TypeMismatch(error);
                }
            }
        }
        else if(fvar != string::npos && ftype == string::npos){
            DestroySplayTree(data.returnRoot());
            throw TypeMismatch(error);
        }
        else if(fvar == string::npos && ftype != string::npos){
            DestroySplayTree(data.returnRoot());
            throw TypeMismatch(error);
        }
        else{

            if(const_string(fVarName) && fTypeName== "string") {
                fVarName.clear();
                fTypeName.clear();
            }
            else if(const_number(fVarName) && fTypeName == "number") {
                fVarName.clear();
                fTypeName.clear();
            }
            else {
                TreeNode* TNvar1 = data.findGlobal(fVarName , level , num_comp , num_splay);
                if(TNvar1){
                    if(TNvar1->key.type != fTypeName){
                        DestroySplayTree(data.returnRoot());
                        throw TypeMismatch(error);
                    }
                    fVarName.clear();
                    fTypeName.clear();
                }
                else{
                    DestroySplayTree(data.returnRoot());
                    throw TypeMismatch(error);
                }
            }
        }
    }

    TreeNode* findX = data.findGlobal(identifier_name, level ,num_comp , num_splay);
    if(!findX) {
        DestroySplayTree(data.returnRoot());
        throw Undeclared(error);
    }

    if(funcTypeRet == findX->key.type) {
        findX->key.ndata = data_;
    }
    else {
        DestroySplayTree(data.returnRoot());
        throw TypeMismatch(error);
    }

    return 1;
}
TreeNode* SplayTree::findGlobal(const string& ele , const int& level ,int& num_comp , int& num_splay){
    int lev = level;
    TreeNode* ret = nullptr;
    while(lev >= 0){
        TreeNode* cRoot = this->root;
        while(cRoot){
            if(lev < cRoot->key.levelOfBlock) cRoot = cRoot->left;
            else if (lev > cRoot->key.levelOfBlock) cRoot = cRoot->right;
            else{
                if(ele.compare(cRoot->key.var) < 0) cRoot = cRoot->left;
                else if(ele.compare(cRoot->key.var) > 0) cRoot = cRoot->right;
                else {
                    ret = cRoot;
                    break;
                }
            }
        }
        if(ret) break;
        --lev;
    }
    if(ret) num_comp += numComp(ret, this->root);
    if(ret) splay(ret, num_splay);
    return ret;
    
}
int SplayTree::numComp(TreeNode* node , TreeNode* root){
    if(!root) return 0;
    if(node->key.levelOfBlock < root->key.levelOfBlock){
        return 1 + numComp(node , root->left);
    }
    else if(node->key.levelOfBlock > root->key.levelOfBlock){
        return 1 + numComp(node, root->right);
    }
    else{
        if (node->key.var < root->key.var){
            return 1 + numComp(node, root->left);
        }
        else if(node->key.var > root->key.var){
            return 1 + numComp(node, root->right);
        }
        else{
            return 1;
        }
    }
    return 1;
}
void SymbolTable::ASSIGN(string& line, const int& level, const string& error , SplayTree& data){
    string constline =  line;
    string identifier_name = cutString(line ," ");
    string value = cutString(line ," ");

    // TreeNode* is_found = data.find(identifier_name, level);
    // if(!is_found) throw Undeclared(error);

    int num_comp = 0;
    int num_splay = 0;

    if(value.back() != ')'){
        if(!const_string(value) && !const_number(value)){
            TreeNode* findX = data.findGlobal(value , level , num_comp , num_splay);
            if(!findX){
                DestroySplayTree(data.returnRoot());
                throw Undeclared(error);
            }
            TreeNode* var = data.findGlobal(identifier_name , level , num_comp , num_splay);
            if(!var){
                DestroySplayTree(data.returnRoot());
                throw Undeclared(error);
            }
            if(var->key.type == findX->key.type) var->key.ndata = findX->key.ndata;
            else{
                DestroySplayTree(data.returnRoot());
                throw TypeMismatch(error);
            }
        }
        else{
            TreeNode* var = data.findGlobal(identifier_name , level , num_comp , num_splay);
            if(!var){
                DestroySplayTree(data.returnRoot());
                throw Undeclared(error);
            }
            if(var->key.type == "string" && const_string(value)) var->key.ndata = value;
            else if(var->key.type == "number" && const_number(value)) var->key.ndata = value;
            else{
                DestroySplayTree(data.returnRoot());
                throw TypeMismatch(error);
            }
        }
    }
    else{
        functionType(constline , error, level ,num_comp , num_splay , data);
    }


    cout << num_comp << " " << num_splay << endl;
}
void SymbolTable::LOOKUP(string& line , const int& level, const string& error , SplayTree& data){
    TreeNode* varname = nullptr;
    int num_splay = 0;
    int num_comp = 0;
    int is_lev = level;

    varname = data.findGlobal(line, level , num_comp ,num_splay);
    if(!varname) {
        DestroySplayTree(data.returnRoot());
        throw Undeclared(error);
    }

    cout << varname->key.levelOfBlock << endl;
}
void SymbolTable::PRINT(SplayTree& data){
    TreeNode* root = data.returnRoot();
    data.print(root);
    cout << endl;
}
void SymbolTable::searchLevel(const string& varname , const int& level , SplayTree& data){

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
        cSyntaxLine(line ,Database);
        error = line;

        string TYPE = cutString(line , " ");

        if(TYPE == "INSERT"){
            INSERT(line, level , error, Database);
        }
        else if(TYPE == "ASSIGN"){
            ASSIGN(line , level, error, Database);
        }
        else if(TYPE == "LOOKUP"){
            LOOKUP(line , level, error, Database);
        }
        else if(TYPE == "PRINT"){
            PRINT(Database);
        }
        else if(TYPE == "BEGIN"){
            ++level;
        }
        else if(TYPE == "END"){
            if(level > 0){
                bool a = 0;
                while(true){
                    bool a = Database._delete(level);
                    if(!a) break;
                }
            }
            --level;
            if(level < 0) {
                DestroySplayTree(Database.returnRoot());
                throw UnknownBlock();
            }
        }
    }
    file.close();
    if(level > 0) throw UnclosedBlock(level);
    DestroySplayTree(Database.returnRoot());
}