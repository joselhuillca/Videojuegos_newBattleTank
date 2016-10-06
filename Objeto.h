#ifndef OBJETO_H
#define OBJETO_H


class Objeto
{
    public:
        Objeto(int id=0){ID_obj=id;}
        Objeto(int x, int y,int id=0);
        virtual ~Objeto();

        int ID_obj;
        unsigned Direction;
        int Tipo_obj;

        inline void setVida(int v){vida=v;}
        inline int getVida(){return vida;}

    protected:
    private:
        unsigned pos_x;
        unsigned pos_y;
        int vida;
};

#endif // OBJETO_H
