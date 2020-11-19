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


//  Up to you

void errorCorrection(CodeWord_t *cw, int data_size)
{
	//on implémente la matrice de contrôle correspondant au code(12,8) 
	short int Mcrt[4][12] = {{1,0,0,0,0,0,1,1,0,0,1,1},
													{0,1,1,0,1,0,1,0,1,0,1,1},
													{0,0,0,1,1,0,0,1,1,1,1,0},
													{0,0,1,0,0,1,0,1,1,1,1,1}};

		CodeWord_t res_t = 0000; 
		CodeWord_t xor_res = 0; 

		short int index = 0; 
		int j=0;
		
		for(int k = 0; k < data_size; k++)
		{	
				//	printBits(cw[k], "WR");  

			 //On effectue la multiplication des matrice H*c 							
			for(int i=0; i < 4; i++)
			{
					for(j=0; j < 12 ; j++)
					{
						
						if( Mcrt[i][j] && getNthBit(cw[k],12-j)) index++; 
						
						
					}

					if(index % 2 !=0) setNthBitCW(&res_t,4-i,1); 
					index =0;
			}

			if(res_t !=0) //si la résultat de la multiplication n'est null
			{							//on cherche l'erreur 
				
				printBits(cw[k], "\nWR"); 
				printBits(res_t, "ERROR !"); 
				//On cherche le ieme bit faux et on le corrige:
				short int min = 0; 
				switch(res_t){
					 case 1: min =6;//0001
					 break;
					 case 2: min =4;//0010
					 break;
					 case 8: min =1;
					 break;
					 case 4: min =2;
					 break;
					 case 5: min =3;
					 break;
					 case 6: min =5;
					 break;
					 case 3: min =10;  //on établit la correspondance entre le vecteur
					 break;						//du résultat Mcrt*cw avec la colonne de la matrice
					 case 13: min =12;	//de contrôle
					 break;
					 case 7: min =9;
					 break;
					 case 12: min =7;
					 break;
					 case 15: min =11;
					 break;
					 case 11: min =8;
					 break;
					  
					 default: min=1;
					 break;   
				}
				min--; 
				printf("min %d\n", min); 
				if(getNthBit(cw[k],12-min))
							setNthBitCW(&(cw[k]),12-min,0); 
						else 
							setNthBitCW(&(cw[k]),12-min,1); 
				printBits(cw[k], "correction"); 
			}
			//Si il n'y a pas d'erreur, on calcule le message original
			
			//les bits de contrôles sont situés aux colonnes C
			//3, C5, C7, C8 ,C9, C10, C11, C12
			
			setNthBitCW(&xor_res, 8, getNthBit(cw[k],12-2));
			setNthBitCW(&xor_res, 7, getNthBit(cw[k],12-4));
			setNthBitCW(&xor_res, 6, getNthBit(cw[k],12-6));
			setNthBitCW(&xor_res, 5, getNthBit(cw[k],12-7));
			setNthBitCW(&xor_res, 4, getNthBit(cw[k],12-8));
			setNthBitCW(&xor_res, 3, getNthBit(cw[k],12-9));
			setNthBitCW(&xor_res, 2, getNthBit(cw[k],12-10));
			setNthBitCW(&xor_res, 1, getNthBit(cw[k],12-11));

			
		//	printBits(xor_res, "Result"); 
			cw[k] = xor_res;
			res_t =0;
			xor_res =0; 
		}
		
  return;
}


// Up to you

//int thereIsError(CodeWord_t *cw, int data_size)
//{
//  return 0;
//}


void decoding(char *cw, int cw_size, char *message, int *data_size)
{
  *data_size = cw_size / sizeof(CodeWord_t);

  //-- For error correction
  //-- to uncomment when complete and needed
  errorCorrection((CodeWord_t*)cw, *data_size);

  //-- For decoding
  copyDataBitsDecoding((CodeWord_t*)cw, message, *data_size);

  //-- For error detection
  //-- to uncomment when complete and needed
   //if(thereIsError((CodeWord_t*)cw, *data_size))
    //{
     printf("PARITY ERROR: \"%s\"\n", message);
  // }

  return;
}
