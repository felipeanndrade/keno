/*!
 * @file driver_keno.cpp
 * @author Felipe da Silva Andrade & Marcos Antonio Junior
 */

#include <iostream>
#include <fstream>
#include <string>

#include "keno.h"

int main(int argc, char **argv)
{

	std::fstream file;
	file.open(argv[1]);

	KenoBet	myGame;	
	std::string receiver;
	
	while(std::getline(file, receiver))
	{
		cash_type receiver_wage = std::stoi(receiver);

		if(myGame.set_wage(receiver_wage))
		{
			std::cout << "The wage has been set\n";
		}
		else
		std::cout << "ERROR\n";	
	}

	return 0;
}
