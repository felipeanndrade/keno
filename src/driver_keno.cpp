/*!
 * @file driver_keno.cpp
 * @author Felipe da Silva Andrade & Marcos A. Cavalcanti Junior
 */

// to compile the project, go to keno root directory and type:
// g++ -std=c++11 -Wall src/*.cpp -I include/ -o build/keno && ./build/keno build/bet_file.dat

#include <iostream>
#include <fstream>
#include <string>
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
	std::cout << std::setw(80) << std::setfill('-') << "" << std::endl;

	// Reading and store the bet in the initialized object
	cash_type IC; // Initial Cash
	size_t NR; // Number of Rounds
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

	}
	bet_file.close();

	// Creating the matrix of payout values

	std::cout << ">>> Bet succesfully read!" << std::endl;
	std::cout << "\tYou are going to wage a total of " << myGame.get_wage() << " dollars.\n";
	std::cout << "\tGoing for a total of " << NR
			  << " rounds, waging $" << IC/NR
			  << " per round.\n\n";

	std::cout << "\tYour bet has " << myGame.get_spots().size() << " numbers. They are: [ ";
	
	for( unsigned int i(0) ; i < myGame.get_spots().size() ; i++ ){
		std::cout << myGame.get_spots()[i] << " ";
	}
	std::cout << "]\n";

	// Generate the random hits
	set_of_numbers_type random_hits = myGame.generate_hits();

	std::cout << "\tThe hits are: [ ";
	for( auto i{0u} ; i < random_hits.size() ; ++i ){
		std::cout << random_hits[i] << " ";
	} 
	std::cout<< "]\n";
	std::cout<< "\n\n";

	set_of_numbers_type my_hits;

	for(unsigned int i{0u}; i < myGame.get_spots().size(); ++i)
	{
		for(auto j{0u}; j < random_hits.size(); ++j)
		{		
			if(myGame.get_spots()[i] == random_hits[j])
			{
				my_hits.push_back(myGame.get_spots()[i]); 	
			}
		}
	}	

	std::cout << "\tYou hit the following number(s) [ ";
	for(auto i{0u}; i < my_hits.size(); ++i)
	{
		std::cout<< my_hits[i] << " ";	
	}
	std::cout << " ], a total of " << my_hits.size() << " hits out of " 
			  << myGame.get_spots().size() << "\n";

	std::cout << "\tPayout rate is " << myGame.get_payout_t()[my_hits.size() - 1][myGame.get_spots().size() - 1] 
			  << " thus you came out with: " << << "\n";
	
	return 0;
}
