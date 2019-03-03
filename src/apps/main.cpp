/*
 *   Copyright (c) 2007 John Weaver
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/*
 * Some example code.
 *
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "hungarian/munkres.h"
#include "hungarian/adapters/boostmatrixadapter.h"

int
main(int argc, char *argv[]) {
	time_t timer;
	time_t start = time(&timer);

	int nrows = 80000;
	int ncols = 80000;
	
	if ( argc == 3 ) {
		nrows = atoi(argv[1]);
		ncols = atoi(argv[2]);
	}

	std::cout << "ready to start" << std::endl;
	hun::Matrix<double> matrix(nrows, ncols);
	std::cout << "initialized matrix after" << start - time(&timer)  << std::endl;
	
	srandom(time(nullptr)); // Seed random number generator.

	// Initialize matrix with random values.
	for ( int row = 0 ; row < nrows ; row++ ) {
		for ( int col = 0 ; col < ncols ; col++ ) {
			matrix(row,col) = (double)random();
		}
	}

	std::cout << "randomized finished after" << start - time(&timer) << std::endl;
	// Display begin matrix state.
	for ( int row = 0 ; row < nrows ; row++ ) {
		for ( int col = 0 ; col < ncols ; col++ ) {
			std::cout.width(2);
			std::cout << matrix(row,col) << ",";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Apply Munkres algorithm to matrix.
	Munkres<double> m;
	m.solve(matrix);

	std::cout << "hungarian finished after " << start - time(&timer) << std::endl;
	// Display solved matrix.

	std::cout << "the result is:" << std::endl;
	for ( int row = 0 ; row < nrows ; row++ ) {
		for ( int col = 0 ; col < ncols ; col++ ) {
			std::cout.width(2);
			std::cout << matrix(row,col) << ",";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	
	for ( int row = 0 ; row < nrows ; row++ ) {
		int rowcount = 0;
		for ( int col = 0 ; col < ncols ; col++  ) {
			if ( matrix(row,col) == 0 )
				rowcount++;
		}
		if ( rowcount != 1 )
			std::cerr << "Row " << row << " has " << rowcount << " columns that have been matched." << std::endl;
	}

	for ( int col = 0 ; col < ncols ; col++ ) {
		int colcount = 0;
		for ( int row = 0 ; row < nrows ; row++ ) {
			if ( matrix(row,col) == 0 )
				colcount++;
		}
		if ( colcount != 1 )
			std::cerr << "Column " << col << " has " << colcount << " rows that have been matched." << std::endl;
	}

	return 0;
}
