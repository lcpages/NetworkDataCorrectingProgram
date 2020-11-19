/**
 * @file decoding.c
 * @author Arash Habibi
 * @author Julien Montavont
 * @version 2.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Functions to decipher the code words
 */

#include <stdio.h>
#include "codingdecoding.h"

void copyDataBitsDecoding(CodeWord_t *cw, char *message, int data_size)
{
  int i = 0;

  for(i=0; i<data_size; i++)
    {
      setNthBitW(&(message[i]), 1, getNthBit(cw[i], 1));
      setNthBitW(&(message[i]), 2, getNthBit(cw[i], 2));
      setNthBitW(&(message[i]), 3, getNthBit(cw[i], 3));
      setNthBitW(&(message[i]), 4, getNthBit(cw[i], 4));
      setNthBitW(&(message[i]), 5, getNthBit(cw[i], 5));
      setNthBitW(&(message[i]), 6, getNthBit(cw[i], 6));
      setNthBitW(&(message[i]), 7, getNthBit(cw[i], 7));
      setNthBitW(&(message[i]), 8, getNthBit(cw[i], 8));
    }
}

/**
 * Up to you

void errorCorrection(CodeWord_t *cw, int data_size)
{
  return;
}
*/

// Up to you

int thereIsError(CodeWord_t *cw, int data_size)
{
	int nbOf1 = 0; 
	int error = 0; 
	for(int k=0; k < data_size; k++)
	{
		//printBits(cw[k], "Word"); 

		for(int i= 1; i < 9; i++) 
		{	
			if(getNthBit(cw[k], i)) nbOf1++;
				
		}
		if((nbOf1 %2) == 0)
		{
			if(!getNthBit(cw[k],9))
			{
				 printBits(cw[k], "error detected"); 
				 error = 1;
			} 
		}
		else if(getNthBit(cw[k],9))
		{
			 error = 1; 
			 printBits(cw[k], "error detected"); 

		}
		nbOf1=0; 
	}
	if(error) return 1; 
  return 0;
}


void decoding(char *cw, int cw_size, char *message, int *data_size)
{
  *data_size = cw_size / sizeof(CodeWord_t);

  //-- For error correction
  //-- to uncomment when complete and needed
  //errorCorrection((CodeWord_t*)cw, *data_size);

  //-- For decoding
  copyDataBitsDecoding((CodeWord_t*)cw, message, *data_size);

  //-- For error detection
  //-- to uncomment when complete and needed
   if(thereIsError((CodeWord_t*)cw, *data_size))
   {
      printf("PARITY ERROR: \"%s\"\n", message);
   }

  return;
}
