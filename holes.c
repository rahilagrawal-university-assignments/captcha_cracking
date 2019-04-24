//Author : Rahil Agrawal
//Date Created: 9 April 2017
//This is a C program to find the no of holes
#include <stdio.h>
#include "captcha.h"

int number_holes(int height, int width, int pixels[height][width])
{	
	//declaring variables to be used in this function for comparing and storing values.
	int n_holes=0,found=height,flag=0, start_column=0, start_row=0,hole_counted=0,hole_counted_left=0,
		hole_counted_right=0,hole_counted_up=0,hole_counted_down=0;
	int counter_row=0,counter_column=0;
	
	//loop to find the no of black pixels and calculate the sum of the column values of
    //these array values

	for(counter_row=0;counter_row<height;counter_row++)
	{
		for(counter_column=0;counter_column<width;counter_column++)
		{
			if (pixels[counter_row][counter_column]==1)
			{
				start_row=counter_row+1;
				start_column=counter_column+1;
				flag=1;
				break;
			}
		}
		if (flag==1)
		{
			break;
		}
	}


	while(start_row<height-1)
	{
		start_column=counter_column+1;
		while(start_column<width-1)
		{
			if ((pixels[start_row][start_column]==0 && found >= height/2 && start_row < height/2 )||(pixels[start_row][start_column]==0 && found < height/2 && start_row >= height/2)) 
			{
				if (pixels[start_row][start_column+1] == 0 && pixels[start_row][start_column-1] == 0 && pixels[start_row+1][start_column] == 0 && pixels[start_row+1][start_column+1] == 0 && pixels[start_row+1][start_column-1] == 0 && pixels[start_row-1][start_column] == 0 && pixels[start_row-1][start_column+1] == 0 && pixels[start_row-1][start_column-1] == 0 )
				{
					hole_counted=0;hole_counted_left=0;hole_counted_right=0,hole_counted_up=0,hole_counted_down=0;

					for (int i=start_row+1;i<height;i++)
					{
						for(int j=start_column+1;j<width;j++)
						{
							if(pixels[i][j]==1)	
							{
								hole_counted=1;
								break;
							}
						}
						if (hole_counted==1)
						{
							break;
						}
					}
					for(int j=start_column;j>=0;j--)
					{
						if(pixels[start_row][j]==1)
						{	
							hole_counted_left=1;
							break;
						}
						else 
						{
							hole_counted_left=0;
						}
					}	

					for(int j=start_column;j<width;j++)
					{
						if(pixels[start_row][j]==1)
						{	
							hole_counted_right=1;
							break;
						}
						else 
						{
							hole_counted_right=0;
						}
					}

					
					if(start_row>=height/2)
					{
						for(int i=start_row-1;i>=height/2;i--)
						{
							if(pixels[i][start_column]==1)
							{	
								hole_counted_up=1;
								break;
							}
							else 
							{
								hole_counted_up=0;
							}
						}
						
						for(int i=start_row+1;i<height;i++)
						{
							if(pixels[i][start_column]==1)
							{	
								hole_counted_down=1;
								break;
							}
							else 
							{
								hole_counted_down=0;
							}
						}
					}
					
					if(start_row<height/2)
					{
						for(int i=start_row-1;i>=0;i--)
						{
							if(pixels[i][start_column]==1)
							{	
								hole_counted_up=1;
								break;
							}
							else 
							{
								hole_counted_up=0;
							}
						}

						for(int i=start_row+1;i<height/2;i++)
						{
							if(pixels[i][start_column]==1)
							{	
								hole_counted_down=1;
								break;
							}
							else 
							{
								hole_counted_down=0;
							}
						}
					}

					if (hole_counted==1 && hole_counted_right==1 && hole_counted_left ==1 && hole_counted_up==1 && hole_counted_down==1 && start_column>=width/3 && start_column<=2*width/3)
					{
						n_holes +=1;										
						found=start_row;
					}
				}
			}
			start_column+=1;
		}
		start_row+=1;
	}

	//This function returns just one value
	return n_holes;
}
