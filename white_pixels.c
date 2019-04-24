//Author : Rahil Agrawal
//Date Created: 30 April 2017
//This is a C program to find the no of white pixels
#include <stdio.h>
#include "captcha.h"

int number_white_pixels(int height, int width, int pixels[height][width])
{	
	//declaring variables to be used in this function for comparing and storing values.
	int n_white_pixels=0;
	int counter_row=0,counter_column=0;
	
	//loop to find the no of white pixels
	while(counter_row<height)
	{
		counter_column=0;
		while(counter_column<width)
		{
			if (pixels[counter_row][counter_column]==0)
			{
				n_white_pixels+=1;
			}
			counter_column+=1;
		}
		counter_row+=1;
	}

	//This function returns just one value
	return n_white_pixels;
}
