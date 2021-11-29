#include "scanner.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;

		void advance();
		void match(int);
		
	public:
		Parser(string);
		void run();
        void program();
		void mainClass();
		void classDeclaration();
		void varDeclaration();
		void methodDeclaration();
		bool isType(int&);
		void type();
		void statement();
		bool isStatement(int&, int&);
		void expression();
		bool isExpression();
		void exp();
		void op();
        void error(string);
};