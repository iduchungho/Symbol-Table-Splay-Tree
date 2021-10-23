#include<iostream>
#include<regex>
#include<string>
#include<fstream>

using namespace std;

bool syntaxLine(string value){
    bool correct = 0;

    if(!correct){
        regex re("INSERT ([a-z]\\w*) ((string|number)|(\\(((string|number)(,(string|number))*)*)\\)->(string|number)) (true|false)");
        if(regex_match(value, re)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re1("ASSIGN [a-z]\\w* ((\\d+)|('\\w*')|([a-z]\\w*)\\(.*\\)|([a-z]\\w*))");
        if(regex_match(value, re1)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re2("BEGIN");
        if(regex_match(value, re2)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re3("END");
        if(regex_match(value, re3)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re4("PRINT");
        if(regex_match(value, re4)) correct = 1;
        else correct = 0;
    }
    if(!correct){
        regex re5("LOOKUP ([a-z]\\w*)");
        if(regex_match(value, re5)) correct = 1;
        else correct = 0;
    }

    return correct;
}

int main(){
    fstream file;
    string line;
    file.open("testcase/test1.txt" , ios::in);
    while(!file.eof()){
        getline(file, line);
        if(syntaxLine(line)) cout << "correct\n";
        else cout << "error: " << line << endl;
    }
    file.close();
    return 0;
}