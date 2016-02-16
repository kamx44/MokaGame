#ifndef MODULE_H
#define MODULE_H

#include "Game.h"
#include "Object.h"

class Game;

class Module : public Object
{
    public:
        Module(Object* parent_,Game* game_,glm::vec2 position_,b2Vec2* vertices_,int32 size_);
        ~Module();
        Game* game_module;
        Object* parent;
      //  void calcSpeed();
      //  Image *ship_img;
      //  Image *mis_img;
      //  unsigned int myID;
      //  unsigned int misID;
      int32 size;
      int id;
      int getEntityType(){
        return 4;
      }
      void calcSpeed();
      int parentId;
      virtual void setDamage(float damage);

    protected:
    private:
};

#endif // MODULE_H
