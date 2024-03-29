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
	cash_type net_balance; // Net balance for each round.	
	
	// if the file was successfull opened
	if( bet_file.is_open() ){
		
		bet_file >> IC; // The first line: The money
		bet_file >> NR; // The second line: The number of rounds

		myGame.set_wage( IC ); // The first line: The money
		myGame.set_rounds( NR ); // The second line: The number of rounds
	
		// add all spot numbers to the bet object
		// This loop catches only the firs 15 numbers!!!
		for(auto i{0u}; i < 15; ++i)
		{
			bet_file >> spot;
			myGame.add_number( spot );
		}

	}
	else
	{
		bet_file.close();
		return -1;
	}

	// For each round we have a wage	
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
	std::cout << "] ";	


	net_balance = myGame.get_wage();	

	// The loop for rounds starts here! 
	for(auto rounds{1}; rounds <= myGame.get_rounds(); ++rounds )
	{	
		// Generating random hits	
		set_of_numbers_type random_hits = myGame.generate_hits();

		std::cout << "\n\t\tThis is round #" << rounds << " of " << myGame.get_rounds() 
			  << " and your wage is $" << myGame.get_wage() / myGame.get_rounds() <<" Good luck!\n";	
		std::cout << "\t\tThe hits are: [ ";
		for( auto i{0u} ; i < random_hits.size() ; ++i ){
			std::cout << random_hits[i] << " ";
		} 
		std::cout<< "]\n";

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
		
		net_balance -= myGame.get_wage()/myGame.get_rounds();	
		
		std::cout << "\t\tYou hit the following number(s) [ ";
		for(auto i{0u}; i < my_hits.size(); ++i)
		{
			std::cout<< my_hits[i] << " ";	
		}
		std::cout << " ], a total of " << my_hits.size() << " hits out of " 
			  << myGame.get_spots().size() << "\n";
		
		// The index of the matrix is sub by one, because the sizes doesn't begins in 0, as the matrix index
		std::cout << "\t\tPayout rate is " << myGame.get_payout_t()[myGame.get_spots().size() - 1][my_hits.size()  - 1] 
				  << " thus you came out with: "  
				  << myGame.get_wage()/myGame.get_rounds() *myGame.get_payout_t()[myGame.get_spots().size() - 1][my_hits.size()  - 1]
				  << "\n";
	
		// Add to the net balance the value owned in this round
		net_balance += (myGame.get_wage()/myGame.get_rounds()) * (myGame.get_payout_t()[myGame.get_spots().size() - 1][my_hits.size()  - 1]); 
		
		std::cout << "\t\tYour net balance so far is: $" << net_balance <<" dolars.\n";
		
		std::cout << "\t\t" << std::setw(80) << std::setfill('-') << "" << std::endl;

	}
	std::cout << ">>> End of rounds!\n";	
	std::cout << std::setw(80) << std::setfill('-') << "" << std::endl;
	

	// Sumary!
	std::cout << ">>> You spent in this game a total of $1500 dollars.\n";
	std::cout << ">>> Hooray, you won $" << net_balance - myGame.get_wage() << " dollars. See you next time! ;-)\n";	
	std::cout << ">>> You are leaving the Keno table with $" << net_balance << " dollars.\n";
	return 0;
}
