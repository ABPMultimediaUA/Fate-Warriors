///
/// MATRIX MULTIPLICATION EXERCISE
///
/// LICENSE
///
///  Copyright(C) 2017 ronaldo / Cheesetea / ByteRealms / Fremos.
///  Contact: ronaldo@cheesetea.com, @FranGallegoBR
///
///  This program is free software: you can redistribute it and/or modify
///  it under the terms of the GNU General Public License as published by
///  the Free Software Foundation, either version 3 of the License, or
///  (at your option) any later version.
///
///  This program is distributed in the hope that it will be useful,
///  but WITHOUT ANY WARRANTY; without even the implied warranty of
///  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///  GNU General Public License for more details.
///
///  You should have received a copy of the GNU General Public License
///  along with this program.  If not, see <http://www.gnu.org/licenses/>.
///
#include <iostream>
#include <ctime>
#include <cstdlib>

// Constants
//
const uint32_t size        = 500;      // Size of square matrices
const uint32_t randfactor  = 10000000; // rand() will be divided by this

///
/// r = a*b (Matrices)
///
void
multiplyMatrices(uint32_t **r, uint32_t **a, uint32_t **b) {
   uint16_t i, j, k;
   uint32_t s;
   for(i=0; i < size; ++i) {
      for(j=0; j < size; ++j) {
         s = 0;
         for(k=0; k < size; ++k) {
            s += a[i][k] * b[k][j];
         }
         r[i][j] = s;
      }
   }
}

///
/// Populates matrix m in-place randomly
///
void
populateRandMatrix(uint32_t** m) {
   for(uint16_t i=0; i < size; ++i) {
      for(uint16_t j=0; j < size; ++j) {
         m[i][j] = std::rand() / randfactor;
      }
   }
}

///
/// Reserve memory for a matrix
///
uint32_t**
reserveMatrix(uint32_t size) {
   uint32_t** m = new uint32_t*[size];
   for (uint32_t i=0; i < size; i++)
      m[i] = new uint32_t[size];

   return m;
}

///
/// Release a previously reserved memory for a matrix
///
void
releaseMatrix(uint32_t** m, uint32_t size) {
   if (m) {
      for(uint32_t i=0; i < size; i++)
         if (m[i]) delete [] m[i];
      delete [] m;
   }
}

///
/// PROGRAM
///
int 
main(void) {
   uint32_t **a, **b, **c;

   // Reserve Matrices
   a = reserveMatrix(size);
   b = reserveMatrix(size);
   c = reserveMatrix(size);

   // Populate Matrices a and b randomly
   std::srand(std::time(0));
   populateRandMatrix(a);
   populateRandMatrix(b);

   // Calculate c=a*b
   multiplyMatrices(c, a, b);

   releaseMatrix(a, size);
   releaseMatrix(b, size);
   releaseMatrix(c, size);

   return 0;
}