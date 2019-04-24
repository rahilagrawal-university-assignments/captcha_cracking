//Author : Rahil Agrawal
//Date Created: 9 April 2017
//This is a C program to print a .pbm image as a 2 dimensional array of '*' and '.'

#include<stdio.h>
#include "captcha.h"

void print_image(int height, int width, int pixels[height][width])
{

	//declaring variables to be used in this lab
	int counter_height=height-1,counter_width=0;
	//loop to print '*' for black pixels and '.' for white values to generate an image
	while(counter_height>=0)
	{
		counter_width=0;
		while(counter_width<width)
		{
			if(pixels[counter_height][counter_width]==1)
			{
				printf("*");
			}
			else if (pixels[counter_height][counter_width]==0)
			{
				printf(".");
			}
			counter_width+=1;
		}
		printf("\n");
		counter_height-=1;
	}
	
}
