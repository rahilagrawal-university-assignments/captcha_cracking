//Author : Rahil Agrawal
//Date Created: 9 April 2017
//This is a C program to find the verticalal balance of a captcha image digit.
#include <stdio.h>
#include "captcha.h"

double get_vertical_balance(int height, int width, int pixels[height][width])
{	
	//declaring variables to be used in this function for comparing and storing values.
	double vertical_balance=0.0;
	int row_sum=0;
	int n_black_pixels=0;
	int counter_row=0,counter_column=0;
	
	//loop to find the no of black pixels and calculate the sum of the column values of
    //these array values
	while(counter_row<height)
	{
		counter_column=0;
		while(counter_column<width)
		{
			if (pixels[counter_row][counter_column]==1)
			{
				row_sum+=counter_column;
				n_black_pixels+=1;
			}
			counter_column+=1;
		}
		counter_row+=1;
	}
	//using the formula for calculating the vertical balance of a digit
	//Formula given by lecturer in the lab exercises section
	vertical_balance=(row_sum*1.0/n_black_pixels + 0.5)/height;

	//This function returns just one value
	return vertical_balance;
}
