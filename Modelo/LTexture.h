#ifndef MODEL_LTEXTURE_H_
#define MODEL_LTEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>



//dimension del nivel
#define ANCHO_NIVEL 2048
#define ALTO_NIVEL 1318

class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path,SDL_Renderer * gRenderer);

#ifdef _SDL_TTF_H
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL ,SDL_Renderer *gRenderer=NULL , int anchoProporcion=0, int altoProporcion=0);

    //Gets image dimensions
    int getWidth();
    int getHeight();

    SDL_Texture* getTexture();


private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif
