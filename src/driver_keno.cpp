/*!
 * @file driver_keno.cpp
 * @author Felipe da Silva Andrade & Marcos A. Cavalcanti Junior
 */

// to compile the project, go to keno root directory and type:
// g++ -std=c++11 -Wall src/*.cpp -I include/ -o build/keno && ./build/keno build/bet_file.dat

#include <iostream>
#include <fstream>
#include <iomanip>

#include "keno.h"

int main(int argc, char **argv)
{

	// Verifies if a bet file was given by command line
	if(argv[1] == nullptr)
	{
		std::cout << "No bet file was given; Try: ./keno <bet_file.dat>\n";
		return EXIT_FAILURE;
	}

	// Creating a stream file to read the bet file.	
	std::ifstream bet_file;
	bet_file.open(argv[1]);

	// Initialize a object
	KenoBet myGame;

	std::cout << ">>> Preparing to read the bet file [" << argv[1] << "], please wait...\n";
	std::cout << std::setw(40) << std::setfill('-') << "" << std::endl;

	// Reading and store the bet in the initialized object
	cash_type IC; // Initial Cash
	number_type NR; // Number of Rounds
	number_type spot; // Spot number

	// if the file was successfull opened
	if( bet_file.is_open() ){
		
		bet_file >> IC; // The first line: The money
		bet_file >> NR; // The second line: The number of rounds

		myGame.set_wage( IC ); // The first line: The money

		// add all spot numbers to the bet object
		while( not bet_file.eof() ){
			bet_file >> spot;
			myGame.add_number( spot );
		}

	} else {

		// implement fail flags

	}

	bet_file.close();

	std::cout << ">>> Bet succesfully read!" << std::endl;
	std::cout << "    You are going to wage a total of " << myGame.get_wage() << " dollars.\n";
	std::cout << "    Going for a total of " << NR
			  << " rounds, waging $" << IC/NR
			  << " per round.\n\n";

	// std::cout << "\t Your bet has 3 numbers. They are: [" << gameSpots << "]\n";
	std::cout << "    Your bet has " << myGame.get_spots().size() << " numbers. They are: [ ";
	// std::cout << myGame.get_spots();
	for( unsigned int i(0) ; i < myGame.get_spots().size() ; i++ ){
		std::cout << myGame.get_spots()[i] << " ";
	}
	std::cout << "]\n";

	return 0;
}
