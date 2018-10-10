/*!
 * @file keno.cpp
 * @author Felipe da Silva Andrade & Marcos A. Cavalcanti Junior
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator> // std::swap

#include "keno.h"

bool KenoBet::add_number( number_type spot_ ){

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

	m_wage = wage_;

	return true;
}

void KenoBet::reset( void )
{

}

cash_type KenoBet::get_wage( void ) const
{
	return m_wage;
}

size_t KenoBet::size( void ) const
{
}

set_of_numbers_type
KenoBet::get_hits( const set_of_numbers_type & hits_ ) const
{

}

set_of_numbers_type KenoBet::get_spots( void ) const {

	return m_spots;

}