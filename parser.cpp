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
	type();
	match(ID);
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

void
Parser::type()
{
	
}

void
Parser::isType()
{

}

void
Parser::statement()
{

}

void
Parser::expression()
{

}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
