#pragma once
#include <string>

using namespace std;

struct VARIABLETYPE{
      const char* VINT      = "int";
      const char* VCHAR     = "char";
      const char* VFLOAT    = "float";
      const char* VLONG     = "long";
      const char* VSHORT    = "short";
      const char* VUINT8T   = "uint8_t";
      const char* VUINT16T  = "uint16_t";
      const char* VUINT32T  = "uint32_t";
      const char* VUINT64T  = "uint64_t";
      const char* VINT8T    = "int8_t";
      const char* VINT16T   = "int16_t";
      const char* VINT32T   = "int32_t";
      const char* VINT64T   = "int64_t";
      const char* VBOOL     = "bool";
      // flags for var
      const char* FCONST    = "const";
      const char* FUNSIGNED = "unsigned";
      const char* FSIGNED   = "signed";
};

struct SYNTAXCOMAND{
      const char* PRINTLN   = "println";
      const char* PRINT     = "print";
      const char* INCLUDE   = "include";
      const char* EXTERN    = "extern";
      const char* DEFINE    = "define";
      const char* INPUT     = "input";
      const char* FN        = "fn";
      const char* CL        = "cl";
      const char* FOPEN     = "fopen";
      const char* FCLOSE    = "fclose";
      const char* FWRITE    = "fwrite";
      const char* FREAD     = "fread";
      const char* FCREATE   = "fcreate";
      const char* SYSCOM    = "syscom";
      const char* LEVEL     = "level";
      const char* WHILE     = "while";
      const char* FOR       = "for";
      const char* IF        = "if";
      const char* ELSE      = "else";
};

struct SEPSING{
      const char SH     = '(';
      const char EH     = ')';
      const char SA     = '[';
      const char EA     = ']';
      const char SP     = '&';
      const char PE     = '%';
      const char DO     = '$';
      const char SO     = '@';
      const char VO     = ' ';
      const char END    = ';';
      const char* NL    = "//";
};

void lexer();
int tokenize();
string ReadLineFile(string filename);