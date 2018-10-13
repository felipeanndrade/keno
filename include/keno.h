/*!
 * @file keno.h
 * @author Felipe da Silva Andrade & Marcos A. Cavalcanti Junior
 */

#ifndef _KENO_H_
#define _KENO_H_

#include <vector>

using number_type = unsigned short int; //<! data type for a keno hit
using cash_type = float; //<! Defines the wage type in this application.
using set_of_numbers_type = std::vector< number_type >;
using matrix_type = std::vector< std::vector< float >>;

class KenoBet
{
	private:
		set_of_numbers_type m_spots; //<! The player's bet.
		cash_type m_wage; 			 //<! The player's wage.
		size_t m_rounds;		
		matrix_type m_payout_table;	
		
		/*! 
		 * @brief Apply a partition to the slice [left, right) of spots vector. Used in qsort_spots() function.
		 * @param spots_vector The spots vector member itself.
		 * @param left Left index of the partition interval.
		 * @param right Right index of the partition interval.
		 * @return Index of the element just past to the pivot element of partition.
		 */
		int spots_partition( set_of_numbers_type & spots_vector, int left , int right );

		/*! 
		 * @brief Apply the QuickSort algorithm to the m_spots vector.
		 * @param spots_vector The spots vector member itself.
		 * @param left Left index of the partition interval.
		 * @param right Right index of the partition interval.
		 */
		void spots_qsort( set_of_numbers_type & spots_vector, int left , int right );

	public:
		
		//! Creates an empty Keno bet.
		KenoBet() : m_wage(0), m_rounds(1)
		{
			m_payout_table =
			{
			{ 0,   3 }, // 1 spot
			{ 0,   1,   9 }, // 2 spots
			{ 0,   1,   2,  16 }, // 3 spots
			{ 0, 0.5,   2,   6,  12 }, // 4 spots
			{ 0, 0.5,   1,   3,  15, 50 }, // 5 spots
			{ 0, 0.5,   1,   2,   3, 30, 75 }, // 6 spots
			{ 0, 0.5, 0.5,   1,   6, 12, 36, 100 }, // 7 spots
			{ 0, 0.5, 0.5,   1,   3,  6, 19,  90, 720 }, // 8 spots
			{ 0, 0.5, 0.5,   1,   2,  4,  8,  20,  80, 1200 }, // 9 spots
			{ 0,   0, 0.5,   1,   2,  3,  5,  10,  30,  600, 1800 }, // 10 spots
			{ 0,   0, 0.5,   1,   1,  2,  6,  15,  25,  180, 1000, 3000 }, // 11 spots
			{ 0,   0,   0, 0.5,   1,  2,  4,  24,  72,  250,  500, 2000, 4000 }, // 12 spots
			{ 0,   0,   0, 0.5, 0.5,  3,  4,   5,  20,   80,  240,  500, 3000, 6000 }, // 13 spots
			{ 0,   0,   0, 0.5, 0.5,  2,  3,   5,  12,   50,  150,  500, 1000, 2000,  7500 }, // 14 spots
			{ 0,   0,   0, 0.5, 0.5,  1,  2,   5,  15,   50,  150,  300,  600, 1200,  2500, 10000 } // 15 spots
			};


		};

		/*! 
		 * @brief Adds a number to the spots only if the number is not already there.
		 * @param spot_ The number we wish to include in the bet.
		 * @return True if number chosen is successfully inserted; False otherwise. 
		 */
		bool add_number( number_type spot_ );

		/*! 
		 * @brief Sets the amount of money the player is betting.
		 * @param wage_ The wage.
		 */
		bool set_wage( cash_type wage_ );

		//!
		// @brief Resets a bet to an empty state.
		void reset( void );

		/*!
		 * @brief Retrieves the player's wage on this bet.
		 * @return The wage value.
		 */
		cash_type get_wage( void ) const;

		/*!
		 * @brief Return a vector < spot_type > with the spots the player has picked so far.
		 * @return The vector< spot_type > with the player's spots picked so far.
		 */
		set_of_numbers_type get_spots( void ) const;

		/*!
		 * @brief 
		 * @return 
		 */
		set_of_numbers_type generate_hits( void );

		matrix_type get_payout_t(void) const;	
};

#endif
