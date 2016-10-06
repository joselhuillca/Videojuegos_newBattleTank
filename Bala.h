#ifndef BALA_H
#define BALA_H

#include <SDL.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <deque>
#include "Defines.h"
#include "Objeto.h"

using namespace std;

typedef vector< vector<Objeto> > Matriz;

class Bala
{
    public:
        Bala();
        Bala(int x,int y,int direc, int tipo);
        ~Bala();

        void setBala(int x,int y,int direc, int tipo);
        void Mover();
        bool verificaEnMatriz(Matriz m,deque<Bala> balas_enemigo,int enemigo_x,int enemigo_y);

        int pos_x;//pocicion en matriz
        int pos_y;//pocicion en matriz
        bool destruido;
        bool isTank;

        SDL_Rect position;

        inline void setVelocidad(int v){velocidad=v;}
        inline void setDireccion(int d){direccion=d;}
        inline void setDanio(int vd){danio=vd;}
        inline void setTipo(int m){tipo=m;}

        inline int getVelocidad(){return velocidad;}
        inline int getDireccion(){return direccion;}
        inline int getDanio(){return danio;}
        inline int getTipo(){return tipo;}
    protected:
    private:
        int tipo;
        int danio;
        int velocidad;
        int direccion;

        int contar_pasos_x;
        int contar_pasos_y;
};

#endif // BALA_H
