#include "parser.h"
#include "error.h"
#include "lexer.h"

namespace Parser {
	double prim(bool get);
	double term(bool get);
	double expr(bool);

	using namespace Lexer;
	using namespace Error;
}

