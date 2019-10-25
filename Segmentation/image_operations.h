#ifndef IMAGE_OPERATIONS_H_
#define IMAGE_OPERATIONS_H_

#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void array_swap( Uint8 array[], size_t i, size_t j);
void array_select_sort(Uint8 array[], size_t len);
void grayscale(SDL_Surface* image_surface);
void binarisation(SDL_Surface* image_surface);
void NoiseReduction(SDL_Surface* image_surface);
int isWhiteHoriz(SDL_Surface* image_surface, int line);
void HorizontalLine(SDL_Surface* image_surface);
void VerticalLine_bis(SDL_Surface* image_surface, int column);
void VerticalLine(SDL_Surface* image_surface);

#endif