//Author : Rahil Agrawal
//Date Created: 30 April 2017
//This is a C program to crack a captcha digit using various physical attributes
#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) {
    //Declaring variables for storing values such as height , width etc.
	int height=0, width=0, start_row=0, start_column=0, box_width=0, box_height=0,n_black_pixels=0, sum_row=0, sum_column=0;
	//Declaring variables to be used for calculating the physical properties 
    double horizontal_balance=0.0,vertical_balance=0.0,density=0.0;

	//Decalring varioables for the for loop that passes a new file name in each execution
	int counter_digit=0,counter_file=0;

	if (get_pbm_dimensions(argv[1], &height, &width) != 1) 
	{
	    return 1;
	}

	int pixels[height][width];
	if (read_pbm(argv[1], height, width, pixels)) 
	{
		get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

		int box_pixels[box_height][box_width];
		copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);
		//calculating various physical attributes
		horizontal_balance = get_horizontal_balance(box_height, box_width, box_pixels); 		
		vertical_balance = get_vertical_balance(box_height, box_width, box_pixels);
		n_black_pixels = number_black_pixels(box_height,box_width,box_pixels);
		density = n_black_pixels * 1.0 / (box_height*box_width) ;

		int holes=0, hole_location=0;
		number_of_holes(height,width,pixels,&holes,&hole_location);
		
	

		//declaring variables to be used for calculating the ratio of the no of
	    //black pixels in the top half of the image to the total no of black pixels
		int n_bp_top = number_black_pixels(box_height/2,box_width,box_pixels);	
		double bp_fraction_top = n_bp_top*1.0/n_black_pixels;
		//declaring variables to be used for calculating the ratio of the no of
	    //black pixels in the left half of the image to the total no of black pixels
		int n_bp_left = number_black_pixels(box_height, box_width/2,box_pixels);
		double bp_fraction_left = n_bp_left*1.0/n_black_pixels;

		double bp_fraction_left_2 = n_bp_left*1.0/(height*width);

		double ratio_black_total=n_black_pixels*1.0/(height*width);
		get_sums(box_height,box_width,box_pixels,&sum_row,&sum_column);	
		double ratio_rowsum_columnsum = sum_row*1.0/sum_column;
		
		//print_image(box_height,box_width,box_pixels);
		int digit=0;
		
		
		//condition to print the files that have a certain property				
		if (holes==0)
		{										
			if(((bp_fraction_left  >=0.3 && bp_fraction_left<=0.4) && (bp_fraction_top>=0.3 && bp_fraction_top<=0.4) && density<=0.4 && horizontal_balance <=0.5) || (bp_fraction_left>=0.2 && bp_fraction_left<=0.3) || (bp_fraction_top>=0.2 && bp_fraction_top<=0.3 ))
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
		// 1 hole - 0,4,6,9
		if (holes==1)
		{
				//checking location of holes for 6 and 0
				if(hole_location==6)
				{
					digit=6;
				}
				else if(hole_location==0)
				{
					digit=0;
				}
				// if neither 6 nor 0, it is a 9 or a 4
				else if(1-bp_fraction_top>0.5)
				{
					digit = 9;
				}
				else if(1-bp_fraction_top<0.5)
				{
					digit=4;
				}				
		}
		// 2 holes - almost always an 8
		if (holes==2)
		{
			digit=8;
		}


		
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(((bp_fraction_left  >=0.3 && bp_fraction_left<=0.4) && (bp_fraction_top>=0.3 && bp_fraction_top<=0.4) && density<=0.4 && horizontal_balance <=0.5) || (bp_fraction_left>=0.2 && bp_fraction_left<=0.3) || (bp_fraction_top>=0.2 && bp_fraction_top<=0.3 ))
		{
			digit=7;
			
		}
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				
		printf("%d\n",digit);			
	}
			
	
    return 0;
}

