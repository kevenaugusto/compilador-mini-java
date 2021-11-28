#include "scanner.h"    

// ISSO AQUI VAI EMBORA DEPOIS, OK?!

Token** table;

void initTable()
{
    table = new Token*[19];

    table[0] = new Token(BOOLEAN, "boolean");
    table[1] = new Token(CLASS, "class");
    table[2] = new Token(ELSE, "else");
    table[3] = new Token(EXTENDS, "extends");
    table[4] = new Token(FALSE, "false");
    table[5] = new Token(IF, "if");
    table[6] = new Token(INT, "int");
    table[7] = new Token(LENGTH, "length");
    table[8] = new Token(MAIN, "main");
    table[9] = new Token(NEW, "new");
    table[10] = new Token(PUBLIC, "public");
    table[11] = new Token(RETURN, "return");
    table[12] = new Token(STATIC, "static");
    table[13] = new Token(STRING, "String");
    table[14] = new Token(SOUT, "System.out.println");
    table[15] = new Token(THIS, "this");
    table[16] = new Token(TRUE, "true");
    table[17] = new Token(VOID, "void");
    table[18] = new Token(WHILE, "while");
}

void freeTable()
{
    for (int i = 0; i < 19; i++)
        delete table[i];

    delete[] table;
}

Token* searchTable(string lexeme)
{
    for (int i = 0; i < 19; i++)
        if (lexeme == table[i]->lexeme)
            return table[i];

    return 0;
}

// LEMBRA DE DELETAR ESSA MERDA AÍ, ZERO MEIA!

//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input/*, SymbolTable* table*/)
{
    // VAI EMBORA TAMBÉM!!
    initTable();
    // LEMBRA DE DELETAR!!

    /*this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;*/
    pos = 0;
    line = 1;

    //st = table;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile,line) )
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 

    //A próxima linha deve ser comentada posteriormente.
    //Ela é utilizada apenas para verificar se o 
    //preenchimento de input foi feito corretamente.
    cout << this->input;

}

int
Scanner::getLine()
{
    return line;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* tok;
    string lexeme;

    //Verifica se chegou ao final do arquivo
    if (input[pos] == '\0')
    {
        tok = new Token(END_OF_FILE);

        return tok;
    }

    //Consome espaços em branco
    while (isspace(input[pos]))
        pos++;

    if (input[pos] == '\n')
        pos++;
    else if (input[pos] == '\t')
        pos++;
    else if (input[pos] == '\r')
        pos++;
    else if (input[pos] == '\f')
        pos++;

    //Consome compentários
    if (input[pos] == '/')
    {
        pos++;
        if (input[pos] == '/')
        {
            pos++;
            while (input[pos] != '\n')
                pos++;
            pos++;
        }
        else if (input[pos] == '*')
        {
            pos++;
            while (input[pos] == '\0')
            {
                if (input[pos] == '*')
                {
                    pos++;
                    if (input[pos] == '/')
                    {
                        pos++;
                        break;
                    }
                }
                else
                    pos++;
            }
        }
        else
        {
            tok = new Token(RELOP, DIV);
            return tok;
        }
    }

    // Separadores
    if (input[pos] == '(')
    {
        pos++;
        tok = new Token(SEPARATOR, L_PARENTHESES);
        return tok;
    }
    else if (input[pos] == ')')
    {
        pos++;
        tok = new Token(SEPARATOR, R_PARENTHESES);
        return tok;
    }
    else if (input[pos] == '[')
    {
        pos++;
        tok = new Token(SEPARATOR, L_BRACKET);
        return tok;
    }
    else if (input[pos] == ']')
    {
        pos++;
        tok = new Token(SEPARATOR, R_BRACKET);
        return tok;
    }
    else if (input[pos] == '{')
    {
        pos++;
        tok = new Token(SEPARATOR, L_BRACES);
        return tok;
    }
    else if (input[pos] == '}')
    {
        pos++;
        tok = new Token(SEPARATOR, R_BRACES);
        return tok;
    }
    else if (input[pos] == ';')
    {
        pos++;
        tok = new Token(SEPARATOR, SEMICOLON);
        return tok;
    }
    else if (input[pos] == '.')
    {
        pos++;
        tok = new Token(SEPARATOR, DOT);
        return tok;
    }
    else if (input[pos] == ',')
    {
        pos++;
        tok = new Token(SEPARATOR, COMMA);
        return tok;
    }

    //Operadores relacionais
    if (input[pos] == '<')
    {
        pos++;
        tok = new Token(RELOP, LT);
        return tok;
    }
    else if (input[pos] == '=')//=
    {   
        pos++;
        if (input[pos] == '=')
        {
            pos++;
            tok = new Token(RELOP, DEQ);
            return tok;
        }
        else
        {
            tok = new Token(RELOP, EQ);
            return tok;
        }
    }
    else if (input[pos] == '>')
    {
        pos++;
        tok = new Token(RELOP, GT);
        return tok;
    }
    else if (input[pos] == '&')
    {
        pos++;
        if (input[pos] == '&')
        {
            pos++;
            tok = new Token(RELOP, AND);
            return tok;
        }
    }
    else if (input[pos] == '+')
    {
        pos++;
        tok = new Token(RELOP, MORE);
        return tok;
    }
    else if (input[pos] == '-')
    {
        pos++;
        tok = new Token(RELOP, MINUS);
        return tok;
    }
    else if (input[pos] == '*')
    {
        pos++;
        tok = new Token(RELOP, MULT);
        return tok;
    }
    else if (input[pos] == '!')
    {
        pos++;
        if (input[pos] == '=')
        {
            pos++;
            tok = new Token(RELOP, DIF);
            return tok;
        }
        else
        {
            tok = new Token(RELOP, NOT);
            return tok;
        }
    }

    //Identificadores
    if (isalpha(input[pos]))
    {
        lexeme.push_back(input[pos]);
        pos++;

        while (isalnum(input[pos]))
        {
            lexeme.push_back(input[pos]);
            pos++;
        }

        //Busco na tabela para ver se é palavra reservada
        tok = searchTable(lexeme);

        if (lexeme == "System" and input[pos] == '.')
        {
            pos++;
            string palavra;

            if (isalpha(input[pos]))
            {
                palavra.push_back(input[pos]);
                pos++;

                while (isalnum(input[pos]))
                {
                    palavra.push_back(input[pos]);
                    pos++;
                }
            }

            if (palavra == "out" and input[pos] == '.')
            {
                pos++;
                palavra = "";

                if (isalpha(input[pos]))
                {
                    palavra.push_back(input[pos]);
                    pos++;

                    while (isalnum(input[pos]))
                    {
                        palavra.push_back(input[pos]);
                        pos++;
                    }
                }

                if (palavra == "println")
                    return new Token(SOUT, "System.out.println");
            }
        }

        if (!tok)
            tok = new Token(ID);
    
        return tok;
    }

    //Números
    if (isdigit(input[pos]))
    {
        pos++;

        while (isdigit(input[pos]))
            pos++;

        bool isFloat = false;

        if (input[pos] == '.')
        {
            pos++;

            if (isdigit(input[pos]))
            {
                pos++;

                while (isdigit(input[pos]))
                    pos++;
            }
            else
                lexicalError();

            isFloat = true;
        }
                       
        if (input[pos] == 'E')
        {
            pos++;

            if (input[pos] == '+' || input[pos] == '-')
                pos++;
            
            if (isdigit(input[pos]))
            {
                pos++;
                while (isdigit(input[pos]))
                    pos++;
            }
            else
                lexicalError();

            tok = new Token(NUMBER, DOUBLE_LITERAL);           
        }
        else if (isFloat)
            tok = new Token(NUMBER, FLOAT_LITERAL);
        else
            tok = new Token(NUMBER, INTEGER_LITERAL);
        
        return tok;
    }

    lexicalError();
    
    tok = new Token(UNDEF);

    return tok;
 
}

void 
Scanner::lexicalError(string msg)
{
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}
