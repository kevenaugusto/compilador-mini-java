#include "scanner.h"

string* vet;

void print(Token*);
void allocVetor();
void freeVetor();

int main(int argc, char* argv[]) 
{
    string input;
    
    getline(cin, input);

    Scanner* scanner = new Scanner(input);

    allocVetor();
    
    Token* t;
    
    do
    {
        t = scanner->nextToken();
        
        print(t);
    }while (t->name != END_OF_FILE);

    delete scanner;

    return 0;
}

void allocVetor()
{
    vet = new string[51];

    vet[0] = "UNDEF";
    vet[1] = "ID";
    vet[2] = "BOOLEAN";
    vet[3] = "CLASS";
    vet[4] = "ELSE";
    vet[5] = "EXTENDS"; 
    vet[6] = "FALSE";
    vet[7] = "IF";
    vet[8] = "INT";
    vet[9] = "LENGTH";
    vet[10] = "MAIN";
    vet[11] = "NEW";
    vet[12] = "PUBLIC";
    vet[13] = "RETURN";
    vet[14] = "STATIC";
    vet[15] = "STRING";
    vet[16] = "SOUT";
    vet[17] = "THIS";
    vet[18] = "TRUE";
    vet[19] = "VOID";
    vet[20] = "WHILE";
    vet[21] = "RELOP";
    vet[22] = "EQ"; 
    vet[23] = "NE";
    vet[24] = "GT";
    vet[25] = "GE";
    vet[26] = "LT";
    vet[27] = "LE";
    vet[28] = "AND";
    vet[29] = "DEQ";
    vet[30] = "MORE";
    vet[31] = "MINUS";
    vet[32] = "MULT";
    vet[33] = "DIV";
    vet[34] = "DIF";
    vet[35] = "NOT";
    vet[36] = "NUMBER";
    vet[37] = "DOUBLE_LITERAL";
    vet[38] = "FLOAT_LITERAL";
    vet[39] = "INTEGER_LITERAL"; 
    vet[40] = "SEPARATOR";
    vet[41] = "L_PARENTHESES";
    vet[42] = "R_PARENTHESES";
    vet[43] = "L_BRACKET";
    vet[44] = "R_BRACKET";
    vet[45] = "L_BRACES";
    vet[46] = "R_BRACES";
    vet[47] = "SEMICOLON";
    vet[48] = "DOT";
    vet[49] = "COMMA";
    vet[50] = "END_OF_FILE";
}

void freeVetor()
{
    delete[] vet;
}

void print(Token* t)
{
    cout << vet[t->name];

    if (t->attribute != UNDEF)
        cout << "(" << vet[t->attribute] << ")";

    cout << " ";
}