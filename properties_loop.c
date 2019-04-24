//Author : Rahil Agrawal
//Date Created: 11 April 2017
//This is a C program to find the physical properties of all the example .pbm files
#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) {
    //Declaring variables for storing values such as height , width etc.
	int height=0, width=0, start_row=0, start_column=0, box_width=0, box_height=0,n_black_pixels=0, sum_row=0, sum_column=0,x=0;
	//Declaring variables to be used for calculating the physical properties 
    double horizontal_balance=0.0,vertical_balance=0.0,density=0.0;

	//Decalring varioables for the for loop that passes a new file name in each execution
	int counter_digit=0,counter_file=0;
	char file_name[15];

	//Loop that finds the physical properties of each image with one image at a time
	for(counter_digit=0;counter_digit<10;counter_digit++)
	{
			counter_file=0;
			for(counter_file=0;counter_file<100;counter_file++)
			{
				if(counter_file<=9)
				sprintf(file_name,"digit/%d_0%d.pbm",counter_digit,counter_file);
				else
				sprintf(file_name,"digit/%d_%d.pbm",counter_digit,counter_file);
				if (get_pbm_dimensions(file_name, &height, &width) != 1) {
		    return 1;
		}

			int pixels[height][width];
			if (read_pbm(file_name, height, width, pixels)) 
			{
				get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

				int box_pixels[box_height][box_width];
				copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);
				//calculating various attributes to be used for determining digits
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

				double bp_fraction_left_2 = n_bp_left*1.0/(box_height*box_width);
				get_sums(box_height,box_width,box_pixels,&sum_row,&sum_column);	
				double ratio_rowsum_columnsum = sum_row*1.0/sum_column;
				
				//print_image(box_height,box_width,box_pixels);
				int digit=0;
				
				
				//conditions to determine the digit
				//initially checking number of holes			
				if (holes==0)
				{										
					//checking the next set of properties					
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
					else if(sum_column>8000 && sum_column<11000)
					{
						digit=2;
					}
					else
					{
						digit=3;
					}
					printf("%s ",file_name);
					printf("%d ",sum_column);
					printf("%d\n",digit);
						
				}
				//1 hole
				if (holes==1)
				{
						//using conditions acquired from the holes program - hole location
						if(hole_location==6)
						{
							digit=6;
						}
						else if(hole_location==0)
						{
							digit=0;
						}
						// if not a 6 or a 0, using other properties to determine if a 4 or a 9
						else if(1-bp_fraction_top>0.5)
						{
							digit = 9;
						}
						else if(1-bp_fraction_top<0.5)
						{
							digit=4;
						}				
				}
				//2 holes
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
				if (digit==counter_digit)
				{
					x++;
				}
							
			}
		}
	}
	printf("%d",x);

    return 0;
}

