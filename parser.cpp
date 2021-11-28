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

}

void
Parser::classDeclaration()
{

}

void
Parser::classDeclaration()
{

}

void
Parser::varDeclaration()
{

}

void
Parser::methodDeclaration()
{

}

void
Parser::isType()
{

}

void
Parser::isStatement()
{

}

void
Parser::isExpression()
{

}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
