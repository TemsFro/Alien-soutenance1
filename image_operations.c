#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "image_operations.h"
#include "pixel_operations.h"

void array_swap( Uint8 array[], size_t i, size_t j)
{
    int swap=array[i];
    array[i]=array[j];
    array[j]=swap;
}

void array_select_sort(Uint8 array[], size_t len)
{
    size_t pos;
    for (size_t i = 0; i < len; i++)
    {
        pos=i;
        for (size_t j = i+1; j < len; j++)
        {
            if (array[j]<array[pos])
            {
                pos=j;
            }
        }
        array_swap(array,i,pos);
    }
}

//Make the image with shades of grey
void grayscale(SDL_Surface* image_surface)
{
	Uint32 pixel;
    Uint8 r, g, b;
    Uint8 a;
    for (int i=0;i<image_surface->w;i++)
    {
        for (int j=0; j<image_surface->h;j++)
        {
            pixel = get_pixel(image_surface, i, j);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            a = 0.3*r + 0.59*g + 0.11*b;
            pixel = SDL_MapRGB(image_surface->format, a, a, a);
            put_pixel(image_surface, i, j, pixel);
        }
    }
}

//Put black or white pixels depending on the shades of grey
void binarisation(SDL_Surface* image_surface)
{
	Uint32 pixel;
    Uint8 r, g, b;
    for (int i=0;i<image_surface->w;i++)
    {
        for (int j=0; j<image_surface->h;j++)
        {
            pixel = get_pixel(image_surface, i, j);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            if(r >= 200 && g >= 200 && b >= 200)
      		{
        		r = 255;
        		g = 255;
        		b = 255;
      		}		
      		else
      		{
        		r = 0;
        		g = 0;
        		b = 0;
      		}
            pixel = SDL_MapRGB(image_surface->format, r, g, b);
            put_pixel(image_surface, i, j, pixel);
        }
    }
}

//Median filter algorithm
void NoiseReduction(SDL_Surface* image_surface)
{
	Uint32 pixel1, pixel2, pixel3, pixel4, pixel5, pixel6, pixel7, pixel8, pixel9;
    Uint8 r1, r2, r3, r4, r5, r6, r7, r8, r9;
    Uint8 g1, g2, g3, g4, g5, g6, g7, g8, g9;
    Uint8 b1, b2, b3, b4, b5, b6, b7, b8, b9;
    Uint8 a1, a2, a3, a4, a5, a6, a7, a8, a9;
    Uint8 res;

    for (int i = 1; i < image_surface->w-1; ++i)
    {
        for (int j = 1; j < image_surface->h-1; ++j)
        {
            
            pixel1= get_pixel(image_surface, i-1, j-1);
            pixel2= get_pixel(image_surface, i-1, j);
            pixel3= get_pixel(image_surface, i-1, j+1);
            pixel4= get_pixel(image_surface, i, j-1);
            pixel5= get_pixel(image_surface, i, j);
            pixel6= get_pixel(image_surface, i, j+1);
            pixel7= get_pixel(image_surface, i+1, j-1);
            pixel8= get_pixel(image_surface, i+1, j);
            pixel9= get_pixel(image_surface, i+1, j+1);

            SDL_GetRGB(pixel1, image_surface->format, &r1, &g1, &b1);
            SDL_GetRGB(pixel2, image_surface->format, &r2, &g2, &b2);
            SDL_GetRGB(pixel3, image_surface->format, &r3, &g3, &b3);
            SDL_GetRGB(pixel4, image_surface->format, &r4, &g4, &b4);
            SDL_GetRGB(pixel5, image_surface->format, &r5, &g5, &b5);
            SDL_GetRGB(pixel6, image_surface->format, &r6, &g6, &b6);
            SDL_GetRGB(pixel7, image_surface->format, &r7, &g7, &b7);
            SDL_GetRGB(pixel8, image_surface->format, &r8, &g8, &b8);
            SDL_GetRGB(pixel9, image_surface->format, &r9, &g9, &b9);
            a1=0.3*r1+0.59*g1+0.11*b1;
            a2=0.3*r2+0.59*g2+0.11*b2;
            a3=0.3*r3+0.59*g3+0.11*b3;
            a4=0.3*r4+0.59*g4+0.11*b4;
            a5=0.3*r5+0.59*g5+0.11*b5;
            a6=0.3*r6+0.59*g6+0.11*b6;
            a7=0.3*r7+0.59*g7+0.11*b7;
            a8=0.3*r8+0.59*g8+0.11*b8;
            a9=0.3*r9+0.59*g9+0.11*b9;

            Uint8 voisins[9]={a1,a2,a3,a4,a5,a6,a7,a8,a9};
            array_select_sort(voisins,9);
            res=voisins[4];

            pixel5 = SDL_MapRGB(image_surface->format, res, res, res);
            put_pixel(image_surface, i, j, pixel5);
        }
    }
}
//Check if a horizontal line if full of white pixels
int isWhiteHoriz(SDL_Surface* image_surface, int line)
{
	int res=1;
	Uint32 pixel;
	Uint8 r, g, b;
	int i=0;
	while((i<(image_surface -> w)) && res)
	{
		pixel= get_pixel(image_surface, i, line);
        SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
		res= (0.3*r+0.59*g+0.11*b)==255;
		i+=1;
	}
	return res;
}

//Convert all horizontal lines which are full of white pixels, 
//into red pixels
void HorizontalLine(SDL_Surface* image_surface)
{
	Uint32 pixel;
	for (int i = 0; i < image_surface -> h; ++i)
	{
		if (isWhiteHoriz(image_surface,i))
		{
			for (int j = 0; j < image_surface -> w; ++j)
			{
				pixel = SDL_MapRGB(image_surface->format, 255, 0, 0);
            	put_pixel(image_surface, j, i, pixel);
			}
		}
	}
}

//Main body of "VerticalLine" function
void VerticalLine_bis(SDL_Surface* image_surface, int column)
{
	Uint32 pixel;
	Uint8 r, g, b;
	int j=0;
	while(j<image_surface -> h)
	{
		pixel= get_pixel(image_surface, column, j);
		SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);	

		if (r==255 && g==0 && b==0)
			j+=1;
		else if(r==0)
		{
			int nextRed2=j;			
			int isRed2=0;			
			while(!isRed2)
			{
				pixel= get_pixel(image_surface, column, nextRed2);
				SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
				if (r==255 && g==0 && b==0)
					isRed2=1;		
				else
					nextRed2+=1;	
			}
			j=nextRed2;

		}
		else
		{
			int nextRed=j;			
			int isRed=0;			
			while(!isRed)
			{
				pixel= get_pixel(image_surface, column, nextRed);
				SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
				if (r==255 && g==0 && b==0)
					isRed=1;		
				else
					nextRed+=1;	
			}

			int k=j;
			int isWhite=1;
			while(k < nextRed && isWhite)
			{
				pixel= get_pixel(image_surface, column, k);
				SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
				if (r==0 && g==0 && b==0)
					isWhite=0;
				k+=1;
			}


			if (isWhite)
			{
				int m=j;
				while(m<nextRed)
				{
					pixel = SDL_MapRGB(image_surface->format, 255, 0, 0);
            		put_pixel(image_surface, column, m, pixel);
            		m+=1;
				}
			}
			j=nextRed;
		}
	}
}
//Separate all letters with a red line
void VerticalLine(SDL_Surface* image_surface)
{
	for (int i = 0; i < image_surface -> w; ++i)
		VerticalLine_bis(image_surface, i);
}