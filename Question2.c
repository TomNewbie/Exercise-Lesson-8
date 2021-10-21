#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// global parameters
const int HEIGHT = 699;
const int WIDTH  = 964;
const int CHANNEL = 3;



//==================================== begin meta-code ==============================

void read_color_image(unsigned char *color_image, char* file_name)
{
    // ...
    int height, width, channel;
    unsigned char* temp = stbi_load(file_name, &width , &height , &channel, 0);
    if(temp == NULL)
    {
    	printf("Unable to load image.\n");
    	exit(1);
    }
    for(int i=0; i<HEIGHT;i++)
    {
    	for(int j=0; j<WIDTH;j++)
    	{
    		for(int k=0; k <CHANNEL;k++)
    		{
    			color_image[i*WIDTH*CHANNEL + j*CHANNEL + k] = temp[i*WIDTH*CHANNEL + j*CHANNEL + k];
    		}
    	}
	}
	stbi_image_free(temp);
}

void save_color_image(unsigned char *color_image, char* file_name)
{
    // ...
    unsigned char* temp = (unsigned char*) malloc(HEIGHT*WIDTH*CHANNEL);
    for(int i=0; i< HEIGHT;i++)
    {
    	for(int j=0; j< WIDTH; j++)
    	{
    		for(int k = 0; k<CHANNEL;k++)
    		{
    			temp[i*WIDTH*CHANNEL + j*CHANNEL + k] = color_image[i*WIDTH*CHANNEL + j*CHANNEL + k];
    		}
    	}
    }
    stbi_write_png(file_name, WIDTH, HEIGHT, CHANNEL, temp, WIDTH*CHANNEL);
    free(temp);
}

void save_gray_image(unsigned char *gray_image, char* file_name)
{
    // ...
    unsigned char* temp = (unsigned char*) malloc(HEIGHT*WIDTH);
    for(int i=0; i<HEIGHT;i++)
    {
    	for(int j=0;j<WIDTH;j++)
    	{
    		temp[i*WIDTH + j] = gray_image[i*WIDTH + j];
    	}
    }
    stbi_write_png(file_name, WIDTH, HEIGHT, 1, temp, WIDTH);
    free(temp);
}

//==================================== end meta-code ==============================


//==================================================================================
//==================================== your code here ==============================
//==================================================================================

void create_mask(unsigned char *image, unsigned char *background,
						unsigned char *mask, int threshold){
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
				unsigned char result_r = abs(*(image + i*WIDTH*CHANNEL + j*CHANNEL) - *(background + i*WIDTH*CHANNEL + j*CHANNEL));
				unsigned char result_g = abs(*(image + i*WIDTH*CHANNEL + j*CHANNEL + 1) - *(background + i*WIDTH*CHANNEL + j*CHANNEL + 1));
				unsigned char result_b = abs(*(image + i*WIDTH*CHANNEL + j*CHANNEL + 2) - *(background + i*WIDTH*CHANNEL + j*CHANNEL + 2));

				if((result_r + result_g + result_b)/3 > threshold){
					*(mask + i*WIDTH + j) = 255;				
				}
				else{
					*(mask + i*WIDTH + j) = 0;	
				}
			
		}
	}

}

void new_image(unsigned char *image, unsigned char *background, 
	unsigned char *mask , unsigned char *result)
{
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			for(int k = 0; k < CHANNEL; k++ ){
				if(mask[i*WIDTH + j]){
					result[i*WIDTH*CHANNEL + j*CHANNEL + k] = image[i*WIDTH*CHANNEL + j*CHANNEL + k];
				}
				else{
					result[i*WIDTH*CHANNEL + j*CHANNEL + k] = background[i*WIDTH*CHANNEL + j*CHANNEL + k];
				}
			}
		}
	}
}
				

int main(void) {
    // create images
	unsigned char *color_image  = (unsigned char*) malloc(HEIGHT*WIDTH*CHANNEL);
	unsigned char *color_background = (unsigned char*) malloc(HEIGHT*WIDTH*CHANNEL);

	unsigned char *mask = (unsigned char*) malloc(HEIGHT*WIDTH);
	unsigned char *result_image = (unsigned char*) malloc(HEIGHT*WIDTH*CHANNEL);
	unsigned char *new_background = (unsigned char*) malloc(HEIGHT*WIDTH*CHANNEL);

	printf("Running... "); // Test if the program is working
	// load color image
	read_color_image(color_image, "pg4.jpg");
	read_color_image(color_background, "background4.jpg");
	read_color_image(new_background, "weather_forecast.jpg");

	// threshold is 50 
	create_mask(color_image, color_background, mask, 50);

	
	// save gray image
    save_gray_image(mask, "hello13.jpg");

	// create new image
	new_image(color_image, new_background, mask, result_image);

	// save new image
	save_color_image(result_image, "result10.jpg");


	free(color_image);
	free(color_background);
	free(mask);
	free(result_image);
    return 0;
}

