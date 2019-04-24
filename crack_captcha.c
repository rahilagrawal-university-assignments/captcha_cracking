//Author : Rahil Agrawal
//Date Created: 30 April 2017
//This is a C program to find the boundary of a single digit .pbm image
#include<stdio.h>
#include "captcha.h"

void split_captcha(int height, int width, int pixels[height][width])
{

	//decalring counter variables for while loop
	int counter_height=0,counter_width=0;
	//declaring dynamic variables for finding the boundary values
	int flag=1;
/////////////////////////////////////////////////////////////////////////////////////////
//loop to find a column of zeroes that runs from top to bottom and convert it to 3s to make it easy to separate the 4 digits	
	while(counter_height<height)
	{
		counter_width=0;
		flag=1;
		while(counter_width<width)
		{
			if(pixels[counter_height][counter_width]==0)
			{
				//if 0 is found, check if it is inside a column of zeroes
				flag=0;
				for(int i=0;i<height;i++)
				{
					if(pixels[i][counter_width]==1 || counter_width==width-1 || counter_width==0 || pixels[i][counter_width+1]==1 || 							pixels[i][counter_width-1]==1)
					{
						// if thezero is not in a column of zeroes, break out of the loop
						flag=1;
						break;
					}
					
				}
			}
			// if the zeroes is a part of the white space separating the two digits, make the white space an array of 3s
			if (flag==0)
			{
				for(int i=0;i<height;i++)
				{
					pixels[i][counter_width]=3;
				}				
			}
			counter_width+=1;
		}
		counter_height+=1;
	}
//now use the separating 3s to store each digit in an array
	counter_height=0;
	counter_width=0;
	int j=0;
	int k=0;
	
	
	counter_width=0;
	while(counter_width<width-2)
	{
		if(pixels[0][counter_width]==3)
		{
			// loop to calculate the width of the array for storing the digit - runs from 3 to 3 that have a series of 0s in between
			j = counter_width+1;
			k=0;
			while(pixels[0][j]==0)
			{
				k++;
				j++;
			}
			if(k>1)
			{
				break;
			}

		}
		counter_width++;
	}
	// declaring and storing the digit in an array
	int array_digit1[height][k];
	for(int i=0;i<height;i++)
	{
		for(j=0;j<k;j++)
		{
			array_digit1[i][j]=pixels[i][j+counter_width+1];
			
		}
		
	}
	printf("%d",guess_captcha(height,k,array_digit1)); // the guess_captcha function is similar to crack_digit and returns a single digit
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//after first digit is stored, the next digit starts from the next 3 to 0 transition
	counter_width+=k;
	while(counter_width<width-2)
	{
		if(pixels[0][counter_width]==3)
		{
			j = counter_width+1;
			k=0;
			
			while(pixels[0][j]==0)
			{
				k++;
				j++;
			}
			if(k>1)
			{
				break;
			}

		}
		counter_width++;
	}
	
	int array_digit2[height][k];
	for(int i=0;i<height;i++)
	{
		for(j=0;j<k;j++)
		{
			array_digit2[i][j]=pixels[i][j+counter_width+1];
			
		}
		
	}
	printf("%d",guess_captcha(height,k,array_digit2));
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//similarly for the third digit
	counter_width+=k;
	while(counter_width<width-2)
	{
		if(pixels[0][counter_width]==3)
		{
			j = counter_width+1;
			k=0;
			while(j<width && pixels[0][j]==0)
			{
				k++;
				j++;
			}
			if(k>1)
			{
				break;
			}

		}
		counter_width++;
	}

	int array_digit3[height][k];
	for(int i=0;i<height;i++)
	{
		for(j=0;j<k;j++)
		{
			array_digit3[i][j]=pixels[i][j+counter_width+1];
		
		}
		
	}
	printf("%d",guess_captcha(height,k,array_digit3));
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// the last element of the captcha may or may not be a 3 so there are two cases
	int lastdigit_start=counter_width;
	counter_width+=k;
	
	while(counter_width<width-2)
	{
		if(pixels[0][counter_width]==3)
		{
			j = counter_width+1;
			k=0;
			while(j<width && pixels[0][j]==0)
			{
				k++;
				j++;
			}
			if(k>1)
			{
				break;
			}

		}
		counter_width++;
	}

	// case 1 - last digit is not a 3 in which case, the width of array is form 3 to the end of array
	if(counter_width==width-2 || counter_width==width-1)
	{
		int array_digit4[height][counter_width-lastdigit_start];		
		for(int i=0;i<height;i++)
		{
			for(j=lastdigit_start;j<counter_width;j++)
			{
				array_digit4[i][j-lastdigit_start]=pixels[i][j];
			}
			
		}
		printf("%d\n",guess_captcha(height,counter_width-lastdigit_start,array_digit4));

	}
	//case 2 - array still has 3s at the end - similar to the first three digits
	else
	{	
		int array_digit4[height][k];
		for(int i=0;i<height;i++)
		{
			for(j=0;j<k;j++)
			{
				array_digit4[i][j]=pixels[i][j+counter_width+1];
			}
			
		}
		printf("%d\n",guess_captcha(height,k,array_digit4));

	}
	
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{

	int height=0, width=0;
	
	//getting dimensions of the image
	if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
		    return 1;
		}
	int pixels[height][width];
			
	// reading the image and calling the split function
	if (read_pbm(argv[1], height, width, pixels)) 
	{
		split_captcha(height, width, pixels);
	}

	return 0;
}
