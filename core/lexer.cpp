/*/   lexer.cpp
 creator:programost /*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <inc/lexer.hpp>

const unordered_map<string, TokenKind> KEYWORDS = {
        {"int", TOK_KW_INT}, {"char", TOK_KW_CHAR}, {"float", TOK_KW_FLOAT},
        {"long", TOK_KW_LONG}, {"short", TOK_KW_SHORT},
        {"uint8_t", TOK_KW_UINT8}, {"uint16_t", TOK_KW_UINT16},
        {"uint32_t", TOK_KW_UINT32}, {"uint64_t", TOK_KW_UINT64},
        {"int8_t", TOK_KW_INT8}, {"int16_t", TOK_KW_INT16},
        {"int32_t", TOK_KW_INT32}, {"int64_t", TOK_KW_INT64},
        {"bool", TOK_KW_BOOL},
        {"const", TOK_KW_CONST}, {"unsigned", TOK_KW_UNSIGNED},
        {"signed", TOK_KW_SIGNED},
        {"bin", TOK_KW_BIN}, {"void", TOK_KW_VOID},
        {"println", TOK_KW_PRINTLN}, {"print", TOK_KW_PRINT},
        {"include", TOK_KW_INCLUDE}, {"extern", TOK_KW_EXTERN},
        {"define", TOK_KW_DEFINE},
        {"input", TOK_KW_INPUT},
        {"fn", TOK_KW_FN}, {"cl", TOK_KW_CL},
        {"fopen", TOK_KW_FOPEN}, {"fclose", TOK_KW_FCLOSE},
        {"fwrite", TOK_KW_FWRITE}, {"fread", TOK_KW_FREAD},
        {"fcreate", TOK_KW_FCREATE},
        {"syscom", TOK_KW_SYSCOM}, {"level", TOK_KW_LEVEL},
        {"while", TOK_KW_WHILE}, {"for", TOK_KW_FOR},
        {"if", TOK_KW_IF}, {"else", TOK_KW_ELSE},
        {"return", TOK_KW_RETURN}, {"var", TOK_KW_VAR},
        {"export", TOK_KW_EXPORT},
        {"in", TOK_KW_IN}, {"range", TOK_KW_RANGE}, {"len", TOK_KW_LEN},
};

vector<Token> lexer(string filename) {
        ifstream file(filename);
        if (!file) {
                cerr << "Err: cannot open file: " << filename << endl;
                return vector<Token>();
        }

        stringstream buffer;
        buffer << file.rdbuf();
        string content = buffer.str();

        vector<Token> tokens;
        int line = 1;
        int col = 1;
        size_t pos = 0;

        auto push = [&](TokenKind kind, string value, int l, int c) {
                tokens.push_back({kind, value, l, c});
        };

        while (pos < content.size()) {
                char c = content[pos];

                if (c == ' ' || c == '\t' || c == '\r') {
                        pos++; col++;
                        continue;
                }
                if (c == '\n') {
                        pos++; line++; col = 1;
                        continue;
                }

                if (c == '/' && pos + 1 < content.size() && content[pos + 1] == '/') {
                        while (pos < content.size() && content[pos] != '\n') {
                                pos++; col++;
                        }
                        continue;
                }

                if (isalpha((unsigned char)c) || c == '_') {
                        int startCol = col;
                        string ident;
                        while (pos < content.size() && (isalnum((unsigned char)content[pos]) || content[pos] == '_')) {
                                ident += content[pos];
                                pos++; col++;
                        }
                        auto it = KEYWORDS.find(ident);
                        push(it != KEYWORDS.end() ? it->second : TOK_IDENT, ident, line, startCol);
                        continue;
                }

                if (isdigit((unsigned char)c)) {
                        int startCol = col;
                        string num;
                        char n = pos + 1 < content.size() ? content[pos + 1] : '\0';
                        if (c == '0' && (n == 'x' || n == 'X')) {
                                num = "0x";
                                pos += 2; col += 2;
                                while (pos < content.size() && isxdigit((unsigned char)content[pos])) {
                                        num += content[pos]; pos++; col++;
                                }
                        } else if (c == '0' && (n == 'b' || n == 'B')) {
                                num = "0b";
                                pos += 2; col += 2;
                                while (pos < content.size() && (content[pos] == '0' || content[pos] == '1')) {
                                        num += content[pos]; pos++; col++;
                                }
                        } else {
                                while (pos < content.size() && (isdigit((unsigned char)content[pos]) || content[pos] == '.')) {
                                        num += content[pos]; pos++; col++;
                                }
                        }
                        push(TOK_NUMBER, num, line, startCol);
                        continue;
                }

                if (c == '"') {
                        int startCol = col;
                        string str;
                        pos++; col++;
                        while (pos < content.size() && content[pos] != '"' && content[pos] != '\n') {
                                str += content[pos];
                                pos++; col++;
                        }
                        if (pos >= content.size() || content[pos] != '"') {
                                cerr << "Err: unterminated string at line " << line << endl;
                                push(TOK_UNKNOWN, str, line, startCol);
                        } else {
                                pos++; col++;
                                push(TOK_STRING, str, line, startCol);
                        }
                        continue;
                }

                int startCol = col;
                string val(1, c);
                TokenKind kind;

                char n = pos + 1 < content.size() ? content[pos + 1] : '\0';
                auto two = [&](TokenKind k, const char* v) {
                        kind = k; val = v; pos += 2; col += 2;
                };

                if (c == '-' && n == '>')      { two(TOK_ARROW, "->"); }
                else if (c == '+' && n == '+') { two(TOK_INC, "++"); }
                else if (c == '-' && n == '-') { two(TOK_DEC, "--"); }
                else if (c == '=' && n == '=') { two(TOK_EQ, "=="); }
                else if (c == '!' && n == '=') { two(TOK_NE, "!="); }
                else if (c == '<' && n == '=') { two(TOK_LE, "<="); }
                else if (c == '>' && n == '=') { two(TOK_GE, ">="); }
                else if (c == '&' && n == '&') { two(TOK_ANDAND, "&&"); }
                else if (c == '|' && n == '|') { two(TOK_OROR, "||"); }
                else {
                        switch (c) {
                                case '(': kind = TOK_LPAREN; break;
                                case ')': kind = TOK_RPAREN; break;
                                case '{': kind = TOK_LBRACE; break;
                                case '}': kind = TOK_RBRACE; break;
                                case '[': kind = TOK_LBRACKET; break;
                                case ']': kind = TOK_RBRACKET; break;
                                case '<': kind = TOK_LANGLE; break;
                                case '>': kind = TOK_RANGLE; break;
                                case ',': kind = TOK_COMMA; break;
                                case '#': kind = TOK_HASH; break;
                                case '.': kind = TOK_DOT; break;
                                case '&': kind = TOK_AMP; break;
                                case '%': kind = TOK_PERCENT; break;
                                case '$': kind = TOK_DOLLAR; break;
                                case '@': kind = TOK_AT; break;
                                case ';': kind = TOK_SEMICOLON; break;
                                case '=': kind = TOK_ASSIGN; break;
                                case '+': kind = TOK_PLUS; break;
                                case '-': kind = TOK_MINUS; break;
                                case '*': kind = TOK_STAR; break;
                                case '/': kind = TOK_SLASH; break;
                                case '!': kind = TOK_NOT; break;
                                default:
                                        kind = TOK_UNKNOWN;
                                        cerr << "Err: unexpected character '" << c
                                             << "' at line " << line << ", col " << col << endl;
                                        break;
                        }
                        pos++; col++;
                }
                push(kind, val, line, startCol);
        }

        push(TOK_EOF, "", line, col);
        return tokens;
}
