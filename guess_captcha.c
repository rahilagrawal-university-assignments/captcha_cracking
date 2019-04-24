//Author : Rahil Agrawal
//Date Created: 30 April 2017
//This is a C program to guess the captcha image using the logic from crack_digit
#include <stdio.h>
#include "captcha.h"

int guess_captcha(int height, int width, int pixels[height][width] ) {
    //Declaring variables for storing values such as height , width etc.
	int start_row=0, start_column=0, box_width=0, box_height=0,n_black_pixels=0, sum_row=0, sum_column=0;
	//Declaring variables to be used for calculating the physical properties 
    double density=0.0;

	//Decalring varioables for the for loop that passes a new file name in each execution
	int counter_digit=0,counter_file=0;

	get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

	int box_pixels[box_height][box_width];
	copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

	n_black_pixels = number_black_pixels(height,width,pixels);
	// to eliminate the errors during testing
	if (n_black_pixels==0)
	{
		n_black_pixels=1;
	}
	density = n_black_pixels * 1.0 / (height*width) ;

	int holes=0, hole_location=0;
	number_of_holes(height,width,pixels,&holes,&hole_location);
	


	//declaring variables to be used for calculating the ratio of the no of
    //black pixels in the top half of the image to the total no of black pixels
	int n_bp_top = number_black_pixels(height/2,width,pixels);	
	double bp_fraction_top = n_bp_top*1.0/n_black_pixels;
	//declaring variables to be used for calculating the ratio of the no of
    //black pixels in the left half of the image to the total no of black pixels
	int n_bp_left = number_black_pixels(height,width/2,pixels);
	double bp_fraction_left = n_bp_left*1.0/n_black_pixels;

	double bp_fraction_left_2 = n_bp_left*1.0/(height*width);
	
	//print_image(box_height,box_width,box_pixels);
	int digit=0;
	
	
	//conditions to sort the digits according to number of holes and then use other attributes to find the digit			
	//0 holes - 1,2,3,5,7 
	if (holes==0)
	{										
		if((bp_fraction_left>=0.2 && bp_fraction_left<=0.3) || (bp_fraction_top>=0.2 && bp_fraction_top<=0.3 ))
		{
			digit=7;					
		}
		
		else if (bp_fraction_left_2<0.15)
		{
			digit = 7;
		}
		else if (sum_column<8000)
		{
			digit=1;
		}
		else 
		{
			digit=3;
		}
	}
	//1 hole
	if (holes==1)
	{
			if(hole_location==6)
			{
				digit=6;
			}
			else if(hole_location==0)
			{
				digit=0;
			}
			else if(1-bp_fraction_top>0.5)
			{
				digit = 9;
			}
			else if(1-bp_fraction_top<0.5)
			{
				digit=4;
			}				
	}
	//2 holes - always an 8 except 2 or 3 zeroes
	if (holes==2)
	{
		digit=8;
	}


	
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if((bp_fraction_left>=0.2 && bp_fraction_left<=0.3) || (bp_fraction_top>=0.2 && bp_fraction_top<=0.3 ))
	{
		digit=7;
		
	}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				

	return digit;
}

