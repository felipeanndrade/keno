/*!
* @file keno.cpp
 * @author Felipe da Silva Andrade & Marcos A. Cavalcanti Junior
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator> // std::swap
 #include <ctime> // std::time

#include "keno.h"

bool KenoBet::add_number( number_type spot_ ){

	// verify if the current number is in the valid interval
	if( (spot_ < 1) or (spot_ > 80) ){
		return false;
	}

	// verify if the current number already exists in the spots vector
	for ( int i(0) ; i < std::distance( std::begin(m_spots), std::end(m_spots) ) ; i++ ){
		if( m_spots[i] == spot_ ){
			return false;
		}
	}

	// add the current number to spots vector
	m_spots.push_back( spot_ );

	// apply QuickSort to spots vector
	spots_qsort( m_spots , 0, m_spots.size() );

	return true;
}

int KenoBet::spots_partition( set_of_numbers_type & spots_vector, int left , int right ){

	// pivot index -- is always the last element
	int pivot ( right - 1 );

	// partition element's index
	int pti( left );

	// note that add_number ensures there is no repeated number in spots vector

	// swap for less-than elements
	for ( int i(0) ; i < (right - left) ; i++ ){

		// index of current element of comparison
		int current( left + i );

		if( spots_vector[current] < spots_vector[pivot] ){
			std::swap( spots_vector[pti] , spots_vector[current] );
			pti++;
		}

	}

	// swap the own pivot and increments pti
	std::swap( spots_vector[pti], spots_vector[pivot] );

	return ++pti;

}

void KenoBet::spots_qsort( set_of_numbers_type & spots_vector, int left , int right ){

	// prevents receive an empty segment of the vector
	if( left == right ){
		return;
	}

	int pti( spots_partition( spots_vector, left, right ) );

	// recursive calls
	spots_qsort( spots_vector, left , pti - 1 );
	spots_qsort( spots_vector, pti  , right    );

}

bool KenoBet::set_wage( cash_type wage_ )
{
	if(wage_ > 0){return (m_wage = wage_);}
	
	else
		return false;
}

cash_type KenoBet::get_wage( void ) const
{
	return m_wage;
}

set_of_numbers_type KenoBet::get_spots( void ) const {

	return m_spots;

}

set_of_numbers_type KenoBet::generate_hits( void ) {

	// https://en.cppreference.com/w/cpp/algorithm/random_shuffle

	// vector of hits to be generated
	set_of_numbers_type random_hits;

	// populate hits vector from 1 to 80
	for ( int i(0) ; i < 80 ; i++ ){
		random_hits.push_back(i+1);
	}

	// seed random number generation
	std::srand ( unsigned ( std::time(0) ) );

	// apply shuffle to the vector
	std::random_shuffle ( std::begin(random_hits) , std::end(random_hits) );

	// remove other elements than not the 20 firsts
	for ( int i(0) ; i < 60 ; i++ ){
		random_hits.pop_back();
	}

	// apply QuickSort to the vector
	spots_qsort( random_hits, 0, random_hits.size() );

	return random_hits;

}

matrix_type KenoBet::get_payout_t(void) const
{
	return m_payout_table;
}

bool KenoBet::set_rounds( number_type rounds_)
{
	if(rounds_ > 0) {return (m_rounds = rounds_);}

	else
		return false;
}

number_type KenoBet::get_rounds(void) const
{
	return m_rounds;
}
