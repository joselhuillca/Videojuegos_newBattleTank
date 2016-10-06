#ifndef DEFINES_H
#define DEFINES_H

#include <string>
using namespace std;

static const unsigned WINDOW_WIDTH = 1080;
static const unsigned WINDOW_HEIGHT = 900;
static const unsigned SPACE_POINTS = 180;

static const unsigned TRANSPARENT_R = 255;
static const unsigned TRANSPARENT_G = 255;
static const unsigned TRANSPARENT_B = 255;

static const unsigned NUM_TANKS = 4;
static const unsigned NUM_BLOQUES = 9;
static const unsigned NUM_BALAS = 3;
static const unsigned VELOCITY_TANK = 5;

static const unsigned VELOCITY_BALA = 10;
static const unsigned TIME_GAME = 90;//90

static const unsigned FOTOGRAMAS = 30;
static const unsigned TIME_FOTOGRAMA = 10*FOTOGRAMAS/9;

static const unsigned GO_UP = 2;
static const unsigned GO_DOWN = 1;
static const unsigned GO_LEFT = 0;
static const unsigned GO_RIGHT = 3;
static const unsigned CELL_SIZE = 60;
static const unsigned MAPA_WIDTH = 18;
static const unsigned MAPA_HEIGHT = 12;

static const string TITLE_GAME = "NEW! - BATTLE TANK";
static const string MESSAGE_SDL_INIT = "No se pudo iniciar SDL:";
static const string MESSAGE_SDL_VIDEO = "No se pudo iniciar video";
static const string MESSAGE_UPDATE_SCREEN_ERROR = "Error al actualizar la pantalla!";


#endif // DEFINES_H
