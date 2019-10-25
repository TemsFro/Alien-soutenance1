#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "image_operations.h"


//main function uses the filename of your image
//You will see a screen with the different changes 
//Press any button to pass to an other change
//The final change is your image with all letters separated
int main(int argc, char* argv[])
{

	if (argc > 2)
		errx(1,"Usage: write image filename");

    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    //Initialize the SDL
    init_sdl();

    image_surface = load_image(argv[1]);
    //Display the image.
    screen_surface=display_image(image_surface);
    //Wait for a key to be pressed.
    wait_for_keypressed();
    
    //Grayscale part
    grayscale(image_surface);   
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    
    //Binarisation part
    binarisation(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();

    //NoiseReduction part
    NoiseReduction(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();

    //Horizontal separation of lines
    HorizontalLine(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();
    
    //Vertical separation of letters
    VerticalLine(image_surface);
    update_surface(screen_surface, image_surface);
    wait_for_keypressed();

    //Free the image surface.
    SDL_FreeSurface(image_surface);
    //Free the screen surface.
    SDL_FreeSurface(screen_surface);

    return 0;
}
