#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <vector>
#include <deque>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "Defines.h"
#include "Objeto.h"
#include "Bala.h"
#include "Animation.h"

using namespace std;

typedef vector< vector<Objeto> > Matriz;

class Player
{
    public:
        Player();
        ~Player();


        void setPlayer(int x,int y,int direc, int tipo);

        int pos_x;//pocicion en matriz
        int pos_y;//pocicion en matriz
        bool disparar;
        bool isDead;

        SDL_Rect position;
        deque<Bala> list_balas;

        void Mover();
        bool verificaEnMatriz(Matriz m);
        bool DrawSurface(SDL_Surface* source, SDL_Surface* destination, int X, int Y, int X2, int Y2, int W, int H);
        void DrawBalas(SDL_Surface* source, SDL_Surface* destination, Matriz &m,Animation &ani,vector<SDL_Surface*> BALAS,deque<Bala> balas_enemigo,int enemigo_x,int enemigo_y);

        inline void setVelocidad(int v){velocidad=v;}
        inline void setDireccion(int d){direccion=d;}
        inline void setVida(int vd){vida=vd;}
        inline void setModelo(int m){modelo_Tank=m;}

        inline int getVelocidad(){return velocidad;}
        inline int getDireccion(){return direccion;}
        inline int getVida(){return vida;}
        inline int getModelo(){return modelo_Tank;}

        //inline
    protected:
    private:
        int velocidad;
        int direccion;
        int vida;

        int modelo_Tank;

        bool verificar_matriz;
};

#endif // PLAYER_H
