/*!
 * @file driver_keno.cpp
 * @author Felipe da Silva Andrade & Marcos Antonio Junior
 */

#include <iostream>
#include <fstream>

#include "keno.h"

int main(int argc, char **argv)
{

	// Verifies if a bet file was given by command line
	if(argv[1] == nullptr)
	{
		std::cout << "No bet file was given; Try: ./keno <bet_file.dat>\n ";	
		return EXIT_FAILURE;
	}

	// Creating a stream file to read the bet file.	
	std::ofstream bet_file;
	bet_file.open(argv[1], "r");

	// Initialize a object
	KenoBet myGame;

	// std::stoi in this case must need a variable to be 'stremmed'
	std::cout << ">>> Preparing to read the bet file [" << std::stoi(argv[1]) << "], please wait...\n";
	std::cout << setw(40) << setfill('-') << "" << std::endl;

	// Reading and store the bet in the initialized object	
	myGame.set_wage(); // The first line: The money
	myGame.set_rounds(); // The second line: The number of rounds
	myGame.add_number(); // The third line: storing all the numbers 

	std::cout << ">>> Bet succesfully read!" << std::endl;
	std::cout << "\t You are going to wage a total of " << myGame.get_wage() << " dollars.\n";
	std::cout << "\t Going for a total of " << myGame.size 
			  << " rounds, waging $" << /* Usar alguma funcao de probabilidade?? myGame.get_wage()/myGame.size */ 
			  << " per round.\n";
	std::cout << "\n\n\n";
	std::cout << "\t Your bet has 3 numbers. They are: [" <<  myGame.get_spots() << "]\n";		

	// Run the game how many times the player expecifies in bet file
	for( auto i{0u}; i < myGame.size; ++i) // Check the sintax to access 'myGame.size'
	{
		std::cout << "\t\t" << setw(40) << setfill('-') << "" << std::endl;
		std::cout << "\t\t This is round #" << i+1 << " of " << myGame.size 
				  << " and your wage is $" << myGame.get_wage() <<  ". Good luck!\n";

		// Generate the random hits
		set_of_numbers_type random_hits = myGame.generate_hits();

		std::cout << "\t\t The hits are: [";
	    for(auto i{0u}; i < random_hits.size(); ++i)
		{
			std::cout << random_hits[i] << " ";
		} 
		std::cout<< "]\n";
		
		// ============== After this point, nothing 'works' properly =============== //	
		std::cout << "\t\t Payout rate is " << /* print payout rate */ 
				  << ", thus your came out with: " << /* set new wage */ << "\n";
		std::cout << "\t\t Your net balance so far is: $" << /* print wage */ 
				  << " dollars.\n";

		// Comparing the hits with the numbers of bet
		for(auto i{0u}; i < random_hits.size() - 1; ++i) // This may not work, because vectors returns iterators insted off references. 
		{
		}	
	}
	

	bet_file.close();

	return 0;
}
