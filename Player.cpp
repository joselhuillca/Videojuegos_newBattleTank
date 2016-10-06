#include "Player.h"

Player::Player()
{
}

void Player::setPlayer(int x,int y,int direc, int tipo)
{
    //ctor
    velocidad = VELOCITY_TANK;
    direccion = direc;

    modelo_Tank=tipo;
    pos_x = x;
    pos_y = y;

    position.x = pos_x*CELL_SIZE;
    position.y = pos_y*CELL_SIZE;

    verificar_matriz = false;
    vida = 15;
    isDead = false;
}

Player::~Player()
{
    //dtor
}

//! Se muede el SDL_Rect segun la direccion
void Player::Mover()
{
    switch(direccion){
        case 0: //GO_LEFT
            position.x -= VELOCITY_TANK;
            break;
        case 1: //GO_DOWN
            position.y += VELOCITY_TANK;
            break;
        case 2: //GO_UP
            position.y -= VELOCITY_TANK;
            break;
        case 3: //GO_RIGHT
            position.x += VELOCITY_TANK;
            break;
        default:
            break;
    }
}

//! Verificamos si la posicion del player tiene algun conflicto con la matriz, si es falso el jugador no se movera
bool Player::verificaEnMatriz(Matriz m)
{
    if(direccion==0){//LEFT
        int new_pos_X = pos_x-1;
        double pos = position.x*1.0/CELL_SIZE;
        if(new_pos_X<0 || m[pos_y][new_pos_X].ID_obj!=0){
            if(pos-pos_x*1.0>=0){//Para que el tanque avance hasta el final del bloque,XD
                return true;
            }
            return false;
        }
        if(m[pos_y][new_pos_X].ID_obj==0){
            pos_x = round(pos);
            return true;
        }
    }
    if(direccion==1){//DOWN
        double pos = position.y*1.0/CELL_SIZE;
        int new_pos_Y = pos_y+1;
        if(new_pos_Y>=MAPA_HEIGHT || m[new_pos_Y][pos_x].ID_obj!=0){
            if(pos-pos_y*1.0<=0){//Para que el tanque avance hasta el final del bloque,XD
                return true;
            }
            return false;
        }
        if(m[new_pos_Y][pos_x].ID_obj==0){
            pos_y = round(pos);
            return true;
        }
    }
    if(direccion==2){//UP
        double pos = position.y*1.0/CELL_SIZE;
        int new_pos_Y = pos_y-1;
        if(new_pos_Y<0 || m[new_pos_Y][pos_x].ID_obj!=0){
            if(pos-pos_y*1.0>=0){//Para que el tanque avance hasta el final del bloque,XD
                return true;
            }
            return false;
        }
        if(m[new_pos_Y][pos_x].ID_obj==0){
            pos_y = round(pos);
            return true;
        }
    }
    if(direccion==3){//RIGTH
        double pos = position.x*1.0/CELL_SIZE;
        int new_pos_X = pos_x+1;
        if(new_pos_X>=MAPA_WIDTH || m[pos_y][new_pos_X].ID_obj!=0){
            if(pos-pos_x*1.0<=0){//Para que el tanque avance hasta el final del bloque,XD
                return true;
            }
            return false;
        }
        if(m[pos_y][new_pos_X].ID_obj==0){
            pos_x = round(pos);
            return true;
        }
    }
    return true;
}

//! Dibuja superficie/imagen=destination en la posicion x,y sobre source, pero destination es una animacion=(imagen mas larga), solo dibuja una parte de destination W,H
bool Player::DrawSurface(SDL_Surface* source, SDL_Surface* destination, int X, int Y, int X2, int Y2, int W, int H)
{
    if(destination == NULL || source == NULL) {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(source, &SrcR, destination, &DestR);//cout<<X2<<" - "<<Y2<<endl;

	return true;
}

//! Dibujar las balas de los jugadores
void Player::DrawBalas(SDL_Surface* sourceAni, SDL_Surface* destination,Matriz &m,Animation &ani,vector<SDL_Surface*> BALAS,deque<Bala> balas_enemigo,int enemigo_x,int enemigo_y)
{
    int tam_p1= list_balas.size();
    for(int i=0;i<tam_p1;i++){
        int x = list_balas[i].position.x;
        int y = list_balas[i].position.y;
        int px=list_balas[i].pos_x;
        int py=list_balas[i].pos_y;


        if(list_balas[0].destruido){
            list_balas.pop_front();
            tam_p1= list_balas.size();
        }
        else{
            list_balas[i].Mover();
            list_balas[i].destruido=!list_balas[i].verificaEnMatriz(m,balas_enemigo,enemigo_x,enemigo_y);
            if(list_balas[i].destruido && py>=0 && py<MAPA_HEIGHT && px>=0 && px<MAPA_WIDTH){//!animacion de explocion
                // Para que la animacion se vea sobre el onjeto
                int x_=0,y_=0,dir=list_balas[i].getDireccion();
                if(dir==0) x_=-CELL_SIZE;//LEFT
                if(dir==1) y_=CELL_SIZE;//DOWN
                if(dir==2) y_=-CELL_SIZE;//UP
                if(dir==3) x_=CELL_SIZE;//RIGHT
                //for(int i=0;i<1000;i++){
                    ani.OnAnimate();
                    DrawSurface(sourceAni, destination, x+x_, y+SPACE_POINTS+y_, ani.GetCurrentFrame() * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);
                //}
                //!Disminuye la vida del bloque
                //cout<<Mapa[py][px].ID_obj<<endl;
                int id =m[py][px].ID_obj;
                if(id!=0 && id!=8){
                    m[py][px].ID_obj-=list_balas[i].getDanio();
                    m[py][px].setVida(m[py][px].getVida()-list_balas[i].getDanio());
                    if(m[py][px].getVida()<=0){
                        m[py][px].ID_obj=0;
                        m[py][px].setVida(0);
                    }
                }
                //!Disminuye la vida del Player
                if(list_balas[i].isTank){
                    vida-=list_balas[i].getDanio();
                }

            }
            DrawSurface(BALAS[list_balas[i].getTipo()], destination, x, y+SPACE_POINTS, list_balas[i].getDireccion() * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);
        }

    }
}



