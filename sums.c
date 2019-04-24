//Author : Rahil Agrawal
//Date Created: 11 April 2017
//This is a C program to find the sum of rows and columns of black pixels
#include <stdio.h>
#include "captcha.h"

void get_sums(int height, int width, int pixels[height][width], int *sum_row, int *sum_column)
{	
	//declaring variables to be used in this function for comparing and storing values.
	int n_black_pixels=0;
	int counter_row=0,counter_column=0;
	*sum_row=0;
	*sum_column=0;
	
	//loop to find the no of black pixels and calculate the sum of the column values of
    //these array values
	while(counter_row<height)
	{
		counter_column=0;
		while(counter_column<width)
		{
			if (pixels[counter_row][counter_column]==1)
			{
				n_black_pixels+=1;
				*sum_row+=counter_row;
				*sum_column+=counter_column;
			}
			counter_column+=1;
		}
		counter_row+=1;
	}
	
}
