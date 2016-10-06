#include "Bala.h"

Bala::Bala()
{
    //ctor
    isTank=false;
}

Bala::Bala(int x,int y,int direc, int t)
{
    //ctor
    velocidad = VELOCITY_BALA;
    direccion = direc;

    tipo=t;
    position.x = x;
    position.y = y;

    pos_x = round(x*1.0/CELL_SIZE);
    pos_y = round(y*1.0/CELL_SIZE);

    danio = 1;
    destruido = false;
    isTank=false;
}

Bala::~Bala()
{
    //dtor
}

void Bala::setBala(int x,int y,int direc, int t)
{
    velocidad = VELOCITY_BALA;
    direccion = direc;

    tipo=t;
    position.x = x;
    position.y = y;

    pos_x = round(x*1.0/CELL_SIZE);
    pos_y = round(y*1.0/CELL_SIZE);

    destruido = false;
}

//! Se muede el SDL_Rect segun la direccion
void Bala::Mover()
{
    switch(direccion){
        case 0: //GO_LEFT
            position.x -= VELOCITY_BALA;
            contar_pasos_x-=VELOCITY_BALA;
            break;
        case 1: //GO_DOWN
            position.y += VELOCITY_BALA;
            contar_pasos_y+=VELOCITY_BALA;
            break;
        case 2: //GO_UP
            position.y -= VELOCITY_BALA;
            contar_pasos_y-=VELOCITY_BALA;
            break;
        case 3: //GO_RIGHT
            position.x += VELOCITY_BALA;
            contar_pasos_x+=VELOCITY_BALA;
            break;
        default:
            break;
    }
}

//! Verificamos si la posicion del player tiene algun conflicto con la matriz, si es falso la bala no se explota
bool Bala::verificaEnMatriz(Matriz m,deque<Bala> balas_enemigo,int enemigo_x,int enemigo_y)
{
    int new_contar_pasos_x = abs(contar_pasos_x);
    int new_contar_pasos_y = abs(contar_pasos_y);
    //Verificar si hay colosion con bala
    int tam_list_balas=balas_enemigo.size();
    for(int i=0;i<tam_list_balas;i++){
        if(pos_x==balas_enemigo[i].pos_x && pos_y==balas_enemigo[i].pos_y) return false;
    }
    //Colision con el tanke enemigo
    if(pos_x==enemigo_x && pos_y==enemigo_y){
        isTank=true;
        return false;
    }

    if(direccion==0){//LEFT
        int new_pos_X = pos_x;
        if(new_pos_X<0){return false;}//cout<<m[pos_y][new_pos_X].ID_obj<<"---"<<new_contar_pasos_x<<endl;
        if(m[pos_y][new_pos_X].ID_obj==0 || m[pos_y][new_pos_X].ID_obj==7 ){//cout<<"entro 1"<<"......"<<new_contar_pasos_x<<endl;
            if(new_contar_pasos_x>=60){//cout<<"entro 2"<<endl;
                contar_pasos_x=0;
                pos_x-=1;
            }return true;
        }
        if(m[pos_y][new_pos_X].ID_obj!=0){//hay colicion
            return false;
        }
    }
    if(direccion==1){//DOWN
        int new_pos_Y = pos_y;
        if(new_pos_Y>=MAPA_HEIGHT){return false;}//cout<<m[new_pos_Y][pos_x].ID_obj<<"---"<<new_contar_pasos_y<<endl;
        if(m[new_pos_Y][pos_x].ID_obj==0 || m[new_pos_Y][pos_x].ID_obj==7){//cout<<"entro 1"<<"......"<<new_contar_pasos_x<<endl;
            if(new_contar_pasos_y>=60){//cout<<"entro 2"<<endl;
                contar_pasos_y=0;
                pos_y+=1;
            }return true;
        }
        if(m[new_pos_Y][pos_x].ID_obj!=0){
            return false;
        }
    }
    if(direccion==2){//UP
        int new_pos_Y = pos_y;
        if(new_pos_Y<0){return false;}//cout<<m[new_pos_Y][pos_x].ID_obj<<"---"<<new_contar_pasos_y<<endl;
        if(m[new_pos_Y][pos_x].ID_obj==0 || m[new_pos_Y][pos_x].ID_obj==7){//cout<<"entro 1"<<"......"<<new_contar_pasos_x<<endl;
            if(new_contar_pasos_y>=60){//cout<<"entro 2"<<endl;
                contar_pasos_y=0;
                pos_y-=1;
            }return true;
        }
        if(m[new_pos_Y][pos_x].ID_obj!=0){
            return false;
        }
    }
    if(direccion==3){//RIGTH
        int new_pos_X = pos_x;
        if(new_pos_X>=MAPA_WIDTH){return false;}//cout<<m[pos_y][new_pos_X].ID_obj<<"---"<<new_contar_pasos_x<<endl;
        if(m[pos_y][new_pos_X].ID_obj==0 || m[pos_y][new_pos_X].ID_obj==7){//cout<<"entro 1"<<"......"<<new_contar_pasos_x<<endl;
            if(new_contar_pasos_x>=60){//cout<<"entro 2"<<endl;
                contar_pasos_x=0;
                pos_x+=1;
            }return true;
        }
        if(m[pos_y][new_pos_X].ID_obj!=0){
            return false;
        }
    }
    return true;
}
