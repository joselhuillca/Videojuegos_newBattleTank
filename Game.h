#ifndef GAME_H
#define GAME_H

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include "Defines.h"
#include "Animation.h"
#include "Objeto.h"
#include "Player.h"
#include "Bala.h"
#include "Texto.h"

using namespace std;

typedef vector< vector<Objeto> > Matriz;

class Game
{
    public:
        Game();
        virtual ~Game();

        void ExecuteGame();
        bool Update();
        void KeyWords();
        void KeyWordStates();

        SDL_Surface *LoadSurfaceFromFile(string filename);
        void DrawSurface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
        bool DrawSurface(SDL_Surface* source, SDL_Surface* destination, int X, int Y, int X2, int Y2, int W, int H);
        bool Transparent(SDL_Surface* destination, int R, int G, int B);
        void SurfacesTransparents();
        void LoadFiles();
        void UnloadFiles();

        void Create_mapa();
        void DibujarMapa();

        void Reset_Players();
        void Info_Game();
        void Cronometro();
    protected:
    private:
        Animation Anim_Explocion;
        Matriz Mapa;
        int CROOM;
        bool done;
        long frametime;
        Uint8 *keystates;


        SDL_Event event;

        SDL_Surface* SCREEN;
        SDL_Surface* LINEA;
        SDL_Surface* PANTALLA_INI;
        SDL_Surface* VIDA;
        SDL_Surface* MARKERP2;
        SDL_Surface* MARKERP1;

        SDL_Surface* EXPLOCION;

        vector< SDL_Surface* > BLOQUES;
        vector< SDL_Surface* > Tanks;
        vector< SDL_Surface* > BALAS;

        Player player_1;
        Player player_2;
        int tank_modelo_p1;
        int tank_modelo_p2;

        Texto player1_name;
        Texto player2_name;
        Texto player1_vida;
        Texto player2_vida;
        Texto Mensaje_Fin;
        Texto TextCrono;

        //TIME
        time_t time_ini, time_fin;
        double diferencia;
        double tiempo_juego;;//solo tienes ese tiempo para acabar el juego
        int minutos;
        int segundos;
        int temp;

};

#endif // GAME_H
