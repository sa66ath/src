#include "paser_impl.h"
#include "table.h"

double Parser::prim(bool get)
{
	if(get)	get_token();

	switch(curr_tok) {
	case NUMBER:
	{	
		double v = number_value;
		get_token();
		return v;
	}
	case NAME:
	{
		double& v = table[string_value];
		if(get_token() == ASSIGN)	v=expr(true);
		return v;
	}
	case MINUS:
		return -prim(true);
	case LP:
	{
		double e = expr(true);
		if(curr_tok != RP)	throw Error::Syntax_error("')' expected");
		get_token();
		return e;
	}
	default:
		throw Error::Syntax_error("primary expected");
	}
}



double Parser::term(bool get)
{
	double left = prim(get);

	for(;;) {
		switch(curr_tok) {
		case MUL:	
			left *= prim(true);
			break;
		case DIV:	
			if(double d = prim(true)) {
				left /= d;
				break;
			}
			throw Error::Zero_divide();
		default:
			return left;
		}
	}
}


double Parser::expr(bool get)
{
	double left = term(get);

	for(;;) {
		switch(curr_tok) {
		case PLUS:	
			left += term(true);
			break;
		case MINUS:	
			left -= term(true);
			break;
		default:
			return left;
		}
	}
}

