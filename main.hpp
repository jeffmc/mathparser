#include <vector>
#include <cstdlib>

namespace Math {

using IntegerNumber = long;
using RealNumber = float;

class Token {
	enum class Type {
		INTEGER_CONSTANT, // -123
		REAL_CONSTANT, // -123.456
		EQUALITY, // = TODO: <= >=
		OPERATION, // single character operations =+-/*%^
		PARENTHESIS_OPEN, // (
		PARENTHESIS_CLOSE, // )
		FUNCTION, // sqrt log
		VARIABLE_SYMBOL // x y z 
	};
	Type type;
	union Data {
		const char* functionString; // sqrt log
		char symbol; // ( ) x y z = + - / * % ^
		IntegerNumber integer_constant; // whole numbers
		RealNumber real_constant; // floating points
	};
	Data data; 
	Token(Token::Type t, Data d) : type(t), data(d) { }
public:
	static Token make_constant(RealNumber num) {
		Data d;
		d.real_constant = num;
		return Token(Token::Type::REAL_CONSTANT, d);
	}
	static Token make_constant(IntegerNumber num) {
		Data d;
		d.integer_constant = num;
		return Token(Token::Type::INTEGER_CONSTANT, d);
	}
	void print() const {
		switch(type) {
		case Type::INTEGER_CONSTANT:
			printf("%li", data.integer_constant);
			break;
		
		case Type::REAL_CONSTANT:
			printf("%g", data.real_constant);
			break;

		case Type::EQUALITY:
		case Type::OPERATION:
		case Type::VARIABLE_SYMBOL:
		case Type::PARENTHESIS_OPEN:
		case Type::PARENTHESIS_CLOSE:
			printf("%c", data.symbol);
			break;
		
		case Type::FUNCTION:
			printf("%s", data.functionString);
			break;
		
		default:
			printf("Error cannot print this type!\n");
			break;
		}
	}

};
using TokenList = std::vector<Token>;

size_t parseNumber(const char* str, TokenList& tokens) {
	
	char* end;
	size_t length = 0;
	
	IntegerNumber int_num = strtol(str,&end,10);
	length = end - str;
	if (*end == '.') {	
		RealNumber real_num = strtof(str,&end);
		length = end - str;
		tokens.push_back(Token::make_constant(real_num));
	} else {
		tokens.push_back(Token::make_constant(int_num));
	}
	
	return length;
} 

TokenList parseString(const char* str) {
	TokenList tokens = {};
	
	while (*str) {
		size_t numLen = parseNumber(str, tokens);
		if (numLen>0) {
			str += numLen;
			continue;
		}
		++str;
		continue;
	}

	return tokens;
}

}
