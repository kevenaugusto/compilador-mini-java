#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,
    ID,
    BOOLEAN,
    CLASS,
    ELSE,
    EXTENDS,
    FALSE,
    IF,
    INT,
    LENGTH,
    MAIN,
    NEW,
    PUBLIC,
    RETURN,
    STATIC,
    STRING,
    SOUT,
    THIS,
    TRUE,
    VOID,
    WHILE,
    RELOP,
    EQ,
    NE,
    GT,
    GE,
    LT,
    LE,
    AND,
    DEQ,
    MORE,
    MINUS,
    MULT,
    DIV,
    DIF,
    NOT,
    NUMBER,
    DOUBLE_LITERAL,
    FLOAT_LITERAL,
    INTEGER_LITERAL,
    SEPARATOR,
    L_PARENTHESES,
    R_PARENTHESES,
    L_BRACKET,
    R_BRACKET,
    L_BRACES,
    R_BRACES,
    SEMICOLON,
    DOT,
    COMMA,
    END_OF_FILE
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name, string lexeme)
        {
            this->name = name;
            this->lexeme = lexeme;
            attribute = UNDEF;
        }

        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};