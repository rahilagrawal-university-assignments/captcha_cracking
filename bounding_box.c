//Author : Rahil Agrawal
//Date Created: 9 April 2017
//This is a C program to find the boundary of a single digit .pbm image
#include<stdio.h>
#include "captcha.h"

void get_bounding_box(int height, int width, int pixels[height][width],int *start_row, int *start_column, int *box_height, int *box_width)
{

	//decalring counter variables for while loop
	int counter_height=0,counter_width=0;
	//declaring dynamic variables for finding the boundary values
	int min_row=0,min_column=0,flag=0,max_row=0,max_column=0;
/////////////////////////////////////////////////////////////////////////////////////////
	//Loop to find the first row where black pixel occurs
	while(counter_height<height)
	{
		counter_width=0;
		while(counter_width<width)
		{
			if(pixels[counter_height][counter_width]==1)
			{
				min_row=counter_height;
				//min_column=counter_width;
				flag=1;
				break;
			}
			counter_width+=1;
		}
		if (flag==1)
		{
			break;
		}
		//printf("\n");
		counter_height+=1;
	}

	*start_row=min_row;
	

//////////////////////////////////////////////////////////////////////////////////////////

	counter_width=0;
	flag=0;
	//loop to find the first column where black pixel occurs
	while(counter_width<width)
		{
			counter_height=0;
			while(counter_height<height)
			{
				if(pixels[counter_height][counter_width]==1)
				{
					//min_row=counter_height;
					min_column=counter_width;
					flag=1;
					break;
				}
				counter_height+=1;
			}
			if (flag==1)
			{
				break;
			}
			//printf("\n");
			counter_width+=1;
			
		}
	
	*start_column=min_column;
//////////////////////////////////////////////////////////////////////////////////////////
	//loop to find the last row where a black pixel occurs
	counter_height = 0;	
	while(counter_height<height)
	{
		counter_width=0;
		while(counter_width<width)
		{
			if(pixels[counter_height][counter_width]==1)
			{
				max_row=counter_height;
				//min_column=counter_width;
			}
			counter_width+=1;
		}
		//printf("\n");
		counter_height+=1;
	}
	

//////////////////////////////////////////////////////////////////////////////////////////
	//Loop to find the last column where a black pixel occurs
	counter_width=0;
	while(counter_width<width)
		{
			counter_height=0;
			while(counter_height<height)
			{
				if(pixels[counter_height][counter_width]==1)
				{
					//min_row=counter_height;
					max_column=counter_width;
				}
				counter_height+=1;
			}
			//printf("\n");
			counter_width+=1;
			
		}
	

//////////////////////////////////////////////////////////////////////////////////////////	
	//calculating the dimensions of the bounding box
	*box_height=max_row-*start_row+1;
	*box_width=max_column-*start_column+1;
	
}
