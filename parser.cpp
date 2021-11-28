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

	cout << "Compilação encerrada com sucesso!\n";
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
	isType();
	match(ID);
}

void
Parser::methodDeclaration()
{
	match(PUBLIC);
	isType();
	match(ID);
	match(L_PARENTHESES);

	if (isType(lToken->name))
	{
		match(ID);

		while (lToken->name == COMMA)
		{
			if (isType(lToken->name))
				match(ID);
		}
	}

	match(R_PARENTHESES);
	match(L_BRACES);

	while (isType(lToken->name))
		varDeclaration();

	while (lToken->name == L_BRACES)
		statement();

	match(RETURN);
	expression();
	match(SEMICOLON);
	match(R_BRACES);
}

bool
Parser::isType()
{
	if (lToken->name == INT)
	{
		advance();
		
		if (lToken->name == L_BRACKET)
		{
			match(L_BRACKET);
			match(R_BRACKET);
		}

		return true;
	}
	else if (lToken->name == BOOLEAN)
	{
		match(BOOLEAN);
		return true;
	}
	else
	{
		match(ID);
		return true;
	}

	return false;
}

void
Parser::statement()
{
	if (lToken->name == L_BRACES)
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

		if (lToken->name == EQ)
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
	if (lToken->name == INTEGER_LITERAL || lToken->name == TRUE || lToken->name == FALSE || lToken->name == ID || lToken->name == THIS)
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
	else if (lToken->name == NOT)
	{
		advance();
		expression();
	}
	else
	{
		match(L_PARENTHESES);
		expression();
		match(R_PARENTHESES);
	}
}

void
Parser::exp()
{
	if (lToken->name == L_BRACKET)
	{
		advance();
		expression();
		match(R_BRACKET);
		exp();
	}
	else if (lToken->name == DOT)
	{
		advance();
		
		if (lToken->name == LENGTH)
		{
			advance();
			exp();
		}
		else
		{
			match(ID);
			match(L_PARENTHESES);
			// SÓ DEUS E O EDU SABEM			
			match(R_PARENTHESES);
		}
	}
	else
	{
		op();
		expression();
		exp();
	}
}

void
Parser::op()
{
	if (lToken->name == AND || lToken->name == LT || lToken->name == GT || lToken->name == DEQ || lToken->name == DIF || lToken->name == MORE || lToken->name == MINUS || lToken->name == MULT || lToken->name == DIV)
		advance();
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
