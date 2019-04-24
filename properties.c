//Author : Rahil Agrawal
//Date Created: 10 April 2017
//This is a C program to find the physical properties of a .pbm file given as terminal input
#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) {
    int height, width, start_row, start_column, box_width, box_height,n_black_pixels;
    double horizontal_balance,vertical_balance,density;

    //if condition that displays an error message if no file name is provided
	if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

	//if condition that checks if the valid height and width are acquired
	if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
return 1;
	}

	int pixels[height][width];
	//Reading the .pbm image and storing it as a 2D Array of 1s and 0s
	if (read_pbm(argv[1], height, width, pixels)) {
	
	//Limiting the image to boundaries within which the black pixels occur
	get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

	int box_pixels[box_height][box_width];

	//Copying the bounding image into a smaller array
	copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

	
	//calculating physical attributes of images to determine the digit
    horizontal_balance = get_horizontal_balance(box_height, box_width, box_pixels); 		vertical_balance = get_vertical_balance(box_height, box_width, box_pixels);
	n_black_pixels = number_black_pixels(box_height,box_width,box_pixels);
	density = n_black_pixels * 1.0 / (box_height*box_width) ;

    printf("Vertical balance %.3lf\n", vertical_balance);
    printf("Horizontal balance %.3lf\n", horizontal_balance);
	//printf("The height of image is: %d\n",box_height);
	//printf("The width of image is: %d\n",box_width);
	//printf("The number of black pixels are: %d\n", n_black_pixels);
	printf("The density of black pixels is: %lf\n", density);
	print_image(height, width, pixels);
	
	}
	

    return 0;
}

