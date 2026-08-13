#pragma once
#include <string>
#include <vector>

using namespace std;

enum TokenKind {
    TOK_IDENT,           
    TOK_NUMBER,          
    TOK_STRING,          

    TOK_KW_INT, TOK_KW_CHAR, TOK_KW_FLOAT, TOK_KW_LONG, TOK_KW_SHORT, TOK_KW_BOOL,
    TOK_KW_CONST, TOK_KW_UNSIGNED, TOK_KW_SIGNED,
    TOK_KW_BIN, TOK_KW_VOID,

    TOK_KW_PRINTLN, TOK_KW_PRINT,
    TOK_KW_INCLUDE, TOK_KW_EXTERN, TOK_KW_DEFINE,
    TOK_KW_INPUT,
    TOK_KW_FN, TOK_KW_CL,
    TOK_KW_FOPEN, TOK_KW_FCLOSE, TOK_KW_FWRITE, TOK_KW_FREAD, TOK_KW_FCREATE,
    TOK_KW_SYSCOM, TOK_KW_LEVEL,
    TOK_KW_WHILE, TOK_KW_FOR, TOK_KW_IF, TOK_KW_ELSE,
    TOK_KW_RETURN, TOK_KW_VAR, TOK_KW_EXPORT,
    TOK_KW_IN, TOK_KW_RANGE, TOK_KW_LEN,

    TOK_LPAREN, TOK_RPAREN,      
    TOK_LBRACE, TOK_RBRACE,      
    TOK_LBRACKET, TOK_RBRACKET,  
    TOK_LANGLE, TOK_RANGLE,      
    TOK_COMMA, TOK_HASH, TOK_DOT,
    TOK_AMP, TOK_PERCENT,        
    TOK_DOLLAR, TOK_AT,         

    // --- операторы ---
    TOK_ARROW,           // ->
    TOK_ASSIGN,          // =
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_INC, TOK_DEC,    // ++ --
    TOK_EQ, TOK_NE,      // == !=
    TOK_LE, TOK_GE,      // <= >=
    TOK_NOT,             // !
    TOK_ANDAND, TOK_OROR,// && ||

    TOK_SEMICOLON,       
    TOK_EOF,             
    TOK_UNKNOWN          
};

struct Token {
    TokenKind kind;
    string    value;   
    int       line;    
    int       col;
};

vector<Token> lexer(string filename);
