#ifndef TEXTO_H
#define TEXTO_H

#include <SDL/SDL.h>
#include <iostream>
#include "Defines.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;

enum textquality {solid, shaded, blended};

class Texto
{
    public:
        Texto();
        virtual ~Texto();

        TTF_Font*    loadfont(char* file, int ptsize);
        SDL_Surface *drawtext(TTF_Font* fonttodraw, char fgR, char fgG, char fgB, char fgA,	char bgR, char bgG, char bgB, char bgA, char text[], textquality quality);

        SDL_Surface *Text;

        TTF_Font* font;
        int size_text;
    protected:
    private:
};

#endif // TEXTO_H
