#include <iostream>

#include "main.hpp"

int main(int argc, const char** argv) {
	if (argc != 2) {
		printf("Needs one argument!\n");
		return 1;
	}
	printf("%s\n", argv[1]);
	
	Math::TokenList tokens = Math::parseString(argv[1]);
	
	printf("Tokens[%u]: \n", tokens.size());
	for (auto it=tokens.cbegin();it!=tokens.cend();++it) {
		it->print();
		printf(" ");
	}
	printf("\n");

	return 0;
}
