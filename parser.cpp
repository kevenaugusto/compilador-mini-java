#include "parser.h"

Parser::Parser(string input)
{
	//currentST = globalST = new SymbolTable();
	//initSimbolTable();

	scanner = new Scanner(input/*, globalST*/);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
		
	else
		error("Erro inesperado");
}

void
Parser::run()
{
	advance();

	program();

	cout << "Compilacao encerrada com sucesso!\n";
}

void
Parser::program()
{
	mainClass();

	while (lToken->name == CLASS)
		classDeclaration();
	
	match(END_OF_FILE);
}

void
Parser::mainClass()
{
	match(CLASS);
	match(ID);
	match(L_BRACES);
	match(PUBLIC);
	match(STATIC);
	match(VOID);
	match(MAIN);
	match(L_PARENTHESES);
	match(STRING);
	match(L_BRACKET);
	match(R_BRACKET);
	match(ID);
	match(R_PARENTHESES);
	match(L_BRACES);
	statement();
	match(R_BRACES);
	match(R_BRACES);
}

void
Parser::classDeclaration()
{
	match(CLASS);
	match(ID);

	if (lToken->name == EXTENDS)
	{
		advance();
		match(ID);
	}

	match(L_BRACES);

	while (isType(lToken->name))
		varDeclaration();

	while (lToken->name == PUBLIC)
		methodDeclaration();

	match(R_BRACES);
}

void
Parser::varDeclaration()
{
	type();
	match(ID);
	match(SEMICOLON);
}

void
Parser::methodDeclaration()
{
	match(PUBLIC);
	type();
	match(ID);
	match(L_PARENTHESES);

	if (isType(lToken->name))
	{
		type();
		match(ID);

		while (lToken->attribute == COMMA)
		{
			advance();

			if (isType(lToken->name))
			{
				type();
				match(ID);
			}
		}
	}

	match(R_PARENTHESES);
	match(L_BRACES);

	while (isType(lToken->name))
		varDeclaration();

	while (isStatement(lToken->name, lToken->attribute))
		statement();
	
	match(RETURN);
	expression();
	match(SEMICOLON);
	match(R_BRACES);
}



bool
Parser::isStatement(int& name, int& attribute)
{
	if (attribute == L_BRACES)
		return true;
	else if (name == IF || name == WHILE || name == SOUT || name == ID)
		return true;
	else
		return false;
}

bool
Parser::isType(int& name)
{
	if (name == INT || name == BOOLEAN || name == ID)
		return true;
	
	return false;
}

void
Parser::type()
{
	if (lToken->name == INT)
	{
		advance();
		
		if (lToken->attribute == L_BRACKET)
		{
			match(L_BRACKET);
			match(R_BRACKET);
		}
	}
	else if (lToken->name == BOOLEAN)
		match(BOOLEAN);
	else if (lToken->name == ID)
		match(ID);
}

void
Parser::statement()
{
	if (lToken->attribute == L_BRACES)
	{
		advance();
		statement();
		match(R_BRACES);
	}
	else if (lToken->name == IF)
	{
		advance();
		match(L_PARENTHESES);
		expression();
		match(R_PARENTHESES);
		statement();
		match(ELSE);
		statement();
	}
	else if (lToken->name == WHILE)
	{
		advance();
		match(L_PARENTHESES);
		expression();
		match(R_PARENTHESES);
		statement();
	}
	else if (lToken->name == SOUT)
	{
		advance();
		match(L_PARENTHESES);
		expression();
		match(R_PARENTHESES);
		match(SEMICOLON);
	}
	else if (lToken->name == ID)
	{
		advance();

		if (lToken->attribute == EQ)
		{ 	
			advance();
			expression();
			match(SEMICOLON);
		}
		else
		{
			match(L_BRACKET);
			expression();
			match(R_BRACKET);
			match(EQ);
			expression();
			match(SEMICOLON);
		}
	}
}

void
Parser::expression()
{
	if (lToken->attribute == INTEGER_LITERAL || lToken->name == TRUE || lToken->name == FALSE || lToken->name == ID || lToken->name == THIS)
	{
		advance();
		exp();
	}
	else if (lToken->name == NEW)
	{
		advance();
		
		if (lToken->name == INT)
		{
			advance();
			match(L_BRACKET);
			expression();
			match(R_BRACKET);
		}
		else
		{
			match(ID);
			match(L_PARENTHESES);
			match(R_PARENTHESES);
		}

		exp();
	}
	else if (lToken->attribute == NOT)
	{
		advance();
		expression();
		exp();
	}
	else if (lToken->attribute == L_PARENTHESES)
	{
		match(L_PARENTHESES);
		expression();
		match(R_PARENTHESES);
		exp();
	}
}

void
Parser::exp()
{
	if (lToken->attribute == L_BRACKET)
	{	
		advance();
		expression();
		match(R_BRACKET);
		exp();
	}
	else if (lToken->attribute == DOT)
	{	
		advance();
		
		if (lToken->name == LENGTH)
		{
			advance();
			exp();
		}
		else if (lToken->name == ID)
		{
			match(ID);
			match(L_PARENTHESES);
			if (isExpression())
			{
				expression();

				while (lToken->attribute == COMMA)
				{
					advance();
					expression();
				}
			}			
			match(R_PARENTHESES);
			exp();
		}
	}
	else if (lToken->name == RELOP)
	{	
		op();
		expression();
		exp();
	}
}

bool
Parser::isExpression()
{
	if (lToken->attribute == INTEGER_LITERAL || lToken->name == TRUE || lToken->name == FALSE || lToken->name == ID || lToken->name == THIS || lToken->name == NEW || lToken->attribute == NOT || lToken->attribute == L_PARENTHESES)
		return true;
	else
		return false;
}

void
Parser::op()
{
	if (lToken->attribute == AND || lToken->attribute == LT || lToken->attribute == GT || lToken->attribute == DEQ || lToken->attribute == DIF || lToken->attribute == MORE || lToken->attribute == MINUS || lToken->attribute == MULT || lToken->attribute == DIV)
		advance();
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
