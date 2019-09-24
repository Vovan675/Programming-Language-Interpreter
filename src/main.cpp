#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


#include "Constants.h"
#include "Token.h"

#include "Expressions/Expression.h"


#include "Tokenizer.h"
#include "Parser.h"


using namespace std;


int main() {



	ifstream file;
	while (true) {
	
	file.open("test.lang");
	std::ostringstream out;
	out << file.rdbuf();
	file.close();


	string programText = out.str();



		Tokenizer tokenizer;
		vector<Token> tokens = tokenizer.tokenize(programText);
		//vector<Token> tokens = tokenizer.tokenize("PI + 2");

		
		for (int i = 0; i < tokens.size(); i++) {
			cout << tokens.at(i).m_type << " " << tokens.at(i).m_value << endl;
		}


		Parser parser;
		Statement* statement = parser.parse(tokens);
		statement->execute();

		for (auto it = variables.begin(); it != variables.end(); it++) {
			//cout << it->first << "= " << it->second << endl;
		}

		system("pause");
	}
	return 0;
}