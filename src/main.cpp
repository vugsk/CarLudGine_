
#include <iostream>
#include <ParserJsonFiles.hpp>

using namespace clg_parserfilescpp;
using namespace std;


int main()
{

	const string file = "Setting_game.json";
	const string key = "kd";


	ParserJsonFiles pif;
	cout << pif.read<string>( file.c_str(), key.c_str() );

	// cout << "⬛" << endl;

    return 0;
}


