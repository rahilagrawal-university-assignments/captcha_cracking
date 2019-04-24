//Author: Rahil Agrawal
//Date Created: 28 April 2017
//This program returns the number of holes and the probable digit by estimating the location of the hole

#include<stdio.h>
#include "captcha.h"


void floodfill(int counter_row, int counter_column, int oldpix, int newpix, int height, int width,int pixels[height][width],int *lastfound_row,int *firstfound_row);

//Function to count and return the number of holes and probable digit
void number_of_holes(int height, int width, int pixels[height][width], int *holes, int *hole_location)
{
	int array_height = height;
	int array_width = width;
	*holes=0;
	int lastfound_row=0,firstfound_row=0;
	int flag=0;

	int counter_column=0,counter_row=0;

	while(counter_row<height)
	{
		counter_column=0;
		while(counter_column<width)
		{
			if(pixels[counter_row][counter_column]==0)
			{
				firstfound_row=counter_row;
				lastfound_row=counter_row;
				//condition for 6 - hole starting point
				if (*holes==1 && counter_row<height/3)
				{
					flag=1;
					//condition for 0 - area of hole
					if(number_white_pixels(height,width,pixels)*1.0/(height*width)>0.06)
					{
						flag=2;
					}
				}
				floodfill(counter_row,counter_column,0,2,array_height,array_width,pixels,&lastfound_row,&firstfound_row);
				*holes+=1;
				
			}
			counter_column+=1;
		}
		counter_row+=1;
	}
	//Once the number of holes is acquired, 1 is reduced as the first flood fill happens on the outer region of the image
	if (*holes==1)
	{
		*holes=0;
	}
	else if (*holes==3)
	{
		*holes=2;
	}
	else if (*holes==2)
	{
		//using conditions for 6 and 0
		if (flag==1)
		{
			*hole_location=6;
		}
		else if (flag==2)
		{
			*hole_location=0;
		}
		//if not 6 or 0, it is either a 9 or a 4
		else
		{
			*hole_location=1;
		}
		
		*holes=1;
	}
}

//Recursive function for flood fill - renames all the 0s to 2s and keeps doing this until a 1 is encountered
void floodfill(int counter_row, int counter_column, int oldpix, int newpix, int height, int width, int pixels[height][width], int *lastfound_row, int *firstfound_row)
{
	//if not a 0, stop recursive calling	
	if (pixels[counter_row][counter_column]!=oldpix)
	{
		return;
	}
	//if a 0, make it a 2
	pixels[counter_row][counter_column] = newpix;

	//call the recursive function for left, top, bottom and right elements of the array and check if they are zeroes
	if (counter_row>0)
	{
		floodfill(counter_row-1,counter_column,oldpix,newpix,height,width,pixels,lastfound_row,firstfound_row);
		(*firstfound_row)--;
	}
	if (counter_column>0)
	{
		floodfill(counter_row,counter_column-1,oldpix,newpix,height,width,pixels,lastfound_row,firstfound_row);
	}
	if (counter_row<height-1)
	{
		floodfill(counter_row+1,counter_column,oldpix,newpix,height,width,pixels,lastfound_row,firstfound_row);
		(*lastfound_row)++;
	}
	if (counter_column<width-1)
	{
		floodfill(counter_row,counter_column+1,oldpix,newpix,height,width,pixels,lastfound_row,firstfound_row);
	}


}


