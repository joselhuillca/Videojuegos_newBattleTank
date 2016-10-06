#include "Animation.h"

Animation::Animation()
{
    //ctor
    CurrentFrame    = 0;
    MaxFrames       = 0;
    FrameInc        = 1;

    FrameRate       = TIME_FOTOGRAMA; //Milliseconds
    OldTime         = 0;

    Oscillate       = false;
}

Animation::~Animation()
{
    //dtor
}

//! Funcion de animar
void Animation::OnAnimate() {
    //Validar la máxima cantidad de frames por segundo posible
    if(OldTime + FrameRate > SDL_GetTicks()) {
        return;
    }

    OldTime = SDL_GetTicks();

    if(Oscillate) {
        if(FrameInc > 0) {
            if(CurrentFrame >= MaxFrames - 1) {
                FrameInc = -FrameInc;
            }
        }else{
            if(CurrentFrame <= 0) {
                FrameInc = -FrameInc;
            }
        }
    }else{
        if(CurrentFrame >= MaxFrames - 1) {
            CurrentFrame = 0;
        }
    }

    CurrentFrame += FrameInc;
}

//! Cambiamos el numero de Frame a mostrar
void Animation::SetCurrentFrame(int Frame) {
    if(Frame < 0 || Frame >= MaxFrames) return;

    CurrentFrame = Frame;
}
