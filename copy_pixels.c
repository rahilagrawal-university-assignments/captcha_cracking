//Author : Rahil Agrawal
//Date Created: 9 April 2017
//This is a C program to copy the image inside the bounding box into a new array.
#include <stdio.h>
#include "captcha.h"

void copy_pixels(int height, int width, int pixels[height][width],int start_row, int start_column, int copy_height, int copy_width,int copy[copy_height][copy_width])

{
	//decalring variables to be used to compare and store values
	int counter_height = start_row;
	int counter_width = start_column;
	int index_row=0,index_column=0;
	
	//loop to take the pixels (array values) from original image and copy into a new array
	while (counter_height<start_row+copy_height)
	{
		counter_width=start_column;
		index_column=0;
		while (counter_width<start_column+copy_width)
		{
			copy[index_row][index_column]=pixels[counter_height][counter_width];
			counter_width+=1;
			index_column+=1;
		}
		counter_height+=1;
		index_row+=1;
	}
}

