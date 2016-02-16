#include "Module.h"
#include "Mmath.h"


Module::Module(Object* parent_,Game* game_,glm::vec2 position_,b2Vec2* vertices_,int32 size_ )
  : game_module(game_),
    size(size_),
    parent(parent_)
{


    position=position_;
    vertices=vertices_;
    vertexCount = size;
    parentId = parent->idObject;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);

    bodyShape.Set(vertices,vertexCount);

    fixtureDef.shape = &bodyShape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;
    fOrientation = 0;

    mass = size;

    setToWorld(game_module->world);
    setFixtureToBody();
  //  body->Set
}


void Module::calcSpeed(){
  //  fOrientation = body->GetAngle()-90;
   // body->SetTransform(b2Vec2(0,0),fOrientation);

}

void Module::setDamage(float damage){
    parent->hp -= (int)damage;
    std::cout<<"Dosta³ hita : "<<(int)damage<<" zostalo: "<<parent->hp<<std::endl;
    if(parent->hp<=0){
        parent->isAlive=false;
    }
}

Module::~Module()
{
    //dtor
}
