/*/   lexer.cpp
 creator:programost /*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <inc/lexer.hpp>
#include <inc/parser.hpp>

struct VARIABLETYPE var;
struct SYNTAXCOMAND synx;
struct SEPSING sep;

string ReadLineFile(string filename) {
        static ifstream file;
        static bool opened = false;
        string line;

        if (!opened) {
                file.open(filename);
                if (!file.is_open()) {
                return string(); 
                }
                opened = true;
        }

        if (getline(file, line)) {
                return line;  
        } else {
                file.close();
                opened = false;
                return string(); 
        }
}

int tokenize(){
        string line;
        while ((line = ReadLineFile("test.yl")) != "") { // Пока значение фиксированное, так что передача имени файла не работает пока что
                
        }
        return 0;
}

void lexer(){
        while (1){
             
        }
}