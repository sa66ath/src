#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "table.h"


namespace Driver {
	extern int no_of_errors;
	extern std::istream* input;
	void skip();
}

#include <sstream>
#include <iostream>

int Driver::no_of_errors = 0;
std::istream* Driver::input = 0;

namespace Parser_interface {
	double expr(bool);
}

double Parser_interface::expr(bool get)
{
	return Parser::expr(get);
}



void Driver::skip()
{
	no_of_errors++;

	while(*input) {
		char ch;
		input->get(ch);
		switch(ch) {
		case '\n':
		case ';':
			return;
		}
	}
}



int main(int argc, char* argv[])
{
	using namespace Parser_interface;
	using namespace Lexer;
	using namespace Error;

	switch(argc) {
	case 1:
		Driver::input = &std::cin;
		break;
	case 2:
		Driver::input = new std::istringstream(argv[1]);
		break;
	default:
		std::cerr << "too many arguments\n";
		return 1;
	}
			
	table["pi"] = 3.1415926535897932384626433832795;
	table["e"] = 2.71828182845904;

	while(*Driver::input) {
		try {
			get_token();
			if(curr_tok == END)	break;
			if(curr_tok == PRINT)	continue;
			std::cout << expr(false) << '\n';
		}
		catch(Error::Zero_divide) {
			std::cerr << "attempt to divide by zero\n";	
			Driver::skip();
		}
		catch(Error::Syntax_error e) {
			std::cerr << "syntax error: " << e.p << std::endl;
			Driver::skip();
		}
	}

	if(Driver::input != &std::cin)	delete Driver::input;

	return Driver::no_of_errors;
}

