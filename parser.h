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
		void type();
		void methodDeclaration();
		void isType();
		void statement();
		void expression();
        void error(string);
};