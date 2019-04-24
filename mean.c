//Author : Rahil Agrawal
//Date Created: 22 April 2017
//This is a C program to find the mean and standard deviation of various attributed for all digits
#include <stdio.h>
#include "captcha.h"
#include <math.h>

int main(int argc, char *argv[]) {
    //Declaring variables for storing values such as height , width etc.
	int height=0, width=0, start_row=0, start_column=0, box_width=0, box_height=0,n_black_pixels=0, sum_row=0, sum_column=0;
	//Declaring variables to be used for calculating the physical properties 
    double horizontal_balance=0.0,vertical_balance=0.0,density=0.0,sum_hb=0,mean_hb=0,sum_sq_hb=0,stddev_hb=0,sum_vb=0,mean_vb=0;
	//Decalring varioables for the for loop that passes a new file name in each execution
	int counter_digit=0,counter_file=0;
	char file_name[15];

	for(counter_file=0;counter_file<100;counter_file++)
		{
			if(counter_file<=9)
			sprintf(file_name,"digit/%d_0%d.pbm",0,counter_file);
			else
			sprintf(file_name,"digit/%d_%d.pbm",0,counter_file);
			if (get_pbm_dimensions(file_name, &height, &width) != 1) 
			{
			    return 1;
			}

			int pixels[height][width];
			if (read_pbm(file_name, height, width, pixels)) 
			{
				get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

				int box_pixels[box_height][box_width];
				copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

				horizontal_balance = get_horizontal_balance(box_height, box_width, box_pixels); 		
				vertical_balance = get_vertical_balance(box_height, box_width, box_pixels);
				n_black_pixels = number_black_pixels(box_height,box_width,box_pixels);
				density = n_black_pixels * 1.0 / (box_height*box_width) ;

				//declaring variables to be used for calculating the ratio of the no of
				//black pixels in the top half of the image to the total no of black pixels
				int n_bp_top = number_black_pixels(box_height/2,box_width,box_pixels);	
				double bp_fraction_top = n_bp_top*1.0/n_black_pixels;
				//declaring variables to be used for calculating the ratio of the no of
				//black pixels in the left half of the image to the total no of black pixels
				int n_bp_left = number_black_pixels(box_height, box_width/2,box_pixels);
				double bp_fraction_left = n_bp_left*1.0/n_black_pixels;

				double ratio_black_total=n_black_pixels*1.0/(box_height*box_width);
				get_sums(box_height,box_width,box_pixels,&sum_row,&sum_column);	
				double ratio_rowsum_columnsum = sum_row*1.0/sum_column;

				sum_hb+=horizontal_balance;
				sum_vb+=vertical_balance;
			}
		}

		//calculate mean by using formula
	
		mean_hb=sum_hb/100;
		mean_vb=sum_vb/100;


	
		/*for(counter_file=0;counter_file<100;counter_file++)
		{
			if(counter_file<=9)
			sprintf(file_name,"digit/%d_0%d.pbm",0,counter_file);
			else
			sprintf(file_name,"digit/%d_%d.pbm",0,counter_file);
			if (get_pbm_dimensions(file_name, &height, &width) != 1) 
			{
			    return 1;
			}

			int pixels[height][width];
			if (read_pbm(file_name, height, width, pixels)) 
			{
				get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

				int box_pixels[box_height][box_width];
				copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

				horizontal_balance = get_horizontal_balance(box_height, box_width, box_pixels); 		
				vertical_balance = get_vertical_balance(box_height, box_width, box_pixels);
				density = n_black_pixels * 1.0 / (box_height*box_width) ;
			
				sum_sq_hb += pow((horizontal_balance - mean_hb),2);
			}
		}
	

	stddev_hb= pow(sum_sq_hb,0.5);
	printf("%lf\n", stddev_hb);
	double x = mean_hb/stddev_hb;
	printf("%lf",x);*/
	
	//print the mean of horizontal and vertical balances

	printf("%lf\n",mean_hb);
	printf("%lf\n",mean_vb);
	
    return 0;
}

