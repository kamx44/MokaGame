#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include "Object.h"
#include "Game.h"

//class Game;

class Asteroide : public Object
{
    public:
        Asteroide(Game* game);
        Asteroide(glm::vec2 vposition, float fSize, unsigned int iTexture);
        virtual ~Asteroide();
        Game* game_asteroide;
        int32 size;
        unsigned int textureID;
         virtual int getEntityType(){
            return 3;
        }
        virtual void delObject(){
            game_asteroide->delFromCont(this);
        }
    protected:
    private:
};

#endif // ASTEROIDE_H
