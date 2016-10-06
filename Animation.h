#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL/SDL.h>
#include "Defines.h"

class Animation
{
    public:
        Animation();
        virtual ~Animation();

        void OnAnimate();
        inline void SetFrameRate(int Rate){ FrameRate=Rate;}
        void SetCurrentFrame(int Frame);
        inline int GetCurrentFrame(){return CurrentFrame;}

        int	MaxFrames;
		bool Oscillate;
    protected:
    private:
        int	CurrentFrame;
        int FrameInc;

        int FrameRate; //Milliseconds
		long OldTime;
};

#endif // ANIMATION_H
