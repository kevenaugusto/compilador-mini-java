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
        //Continuar....
        void error(string);
};