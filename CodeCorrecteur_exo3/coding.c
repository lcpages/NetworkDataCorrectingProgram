/**
 * @file coding.c
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
 * Generate code words from the initial data flow
 */

#include "codingdecoding.h"
#include "stdio.h"

void copyDataBitsCoding(char *message, CodeWord_t *cw, int size)
{
  int i = 0;

  for(i=0; i<size; i++)
    {
      setNthBitCW(&(cw[i]), 1, getNthBit(message[i], 1));
      setNthBitCW(&(cw[i]), 2, getNthBit(message[i], 2));
      setNthBitCW(&(cw[i]), 3, getNthBit(message[i], 3));
      setNthBitCW(&(cw[i]), 4, getNthBit(message[i], 4));
      setNthBitCW(&(cw[i]), 5, getNthBit(message[i], 5));
      setNthBitCW(&(cw[i]), 6, getNthBit(message[i], 6));
      setNthBitCW(&(cw[i]), 7, getNthBit(message[i], 7));
      setNthBitCW(&(cw[i]), 8, getNthBit(message[i], 8));
    }

  return;
}


//  Up to you

void computeCtrlBits(CodeWord_t *message, int size)
{

  //on implémente la matrice génératrice du code (12,8)
  short int Mgn[8][12] = {{0,1,1,0,0,1,0,0,0,0,0,0},
													{0,1,0,1,1,0,0,0,0,0,0,0},
													{1,1,0,0,0,0,1,0,0,0,0,0},
													{1,0,0,1,0,1,0,1,0,0,0,0},
													{0,1,0,1,0,1,0,0,1,0,0,0},
													{0,0,0,1,0,1,0,0,0,1,0,0},
													{1,1,0,1,0,1,0,0,0,0,1,0},
													{1,1,0,0,0,1,0,0,0,0,0,1}};



	CodeWord_t res_t = 0;
	short int index = 0;
	int j = 0;

	for(int k=0; k<size; k++)
	{


		for(int i=0; i < 12; i++)
		{
				for(j=0; j < 8 ; j++)
				{
          //opération AND avec la matrice
					if( Mgn[j][i] && getNthBit(message[k],8-j)) index++;


				}
        //permute tous les valeurs vers la gauche
				res_t = res_t << 1;
        // si l'opération de multiplication vaut 1 :
				if(index % 2 !=0) setNthBitCW(&res_t,1,1);

			//	printf("index value %d \n", index );
				index = 0;
		}
		//	printBits(res_t, "send  ");

		message[k] = res_t;
		res_t =0;
	}

  return;
}


void coding(char *message, int data_size, char *cw, int *cw_size)
{
  *cw_size = data_size * sizeof(CodeWord_t);

  copyDataBitsCoding(message, (CodeWord_t*)cw, data_size);
  //-- to uncomment when complete and needed
  computeCtrlBits((CodeWord_t*)cw, data_size);

  return;
}
