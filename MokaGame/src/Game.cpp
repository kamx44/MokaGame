#include "Game.h"
#include "Object.h"
#include "Renderer.h"
#include "Camera.h"
#include "Events.h"
#include "PolygonGenerator.h"
#include <Box2D/Box2D.h>

Game::Game() :gravity(0.0f, 0.0f), world(gravity)
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::addToCont(Ship *ship)
{
    ships.push_back(ship);
}

void Game::addToCont(Missle *missle)
{
    missles.push_back(missle);
}

void Game::addToCont(Asteroide *ast)
{
    asteroides.push_back(ast);
}

void Game::addToCont(Module *mod)
{
    modules.push_back(mod);
}



void Game::delFromCont(Ship *ship)
{
    for(unsigned int i=0; i<ships.size(); i++)
    {
        if(ship==ships[i])
        {
            if(ships.size()==1)
            {
                ship->destroyBody(world);
                ships.clear();
                delete ship;
                playerAlive=false;
                throw "KONIEC";
            }
            else
            {
                // prev=--it;
                //  next=++it;
                ship->destroyBody(world);
                ships.erase(ships.begin()+i);
                delete ship;
                playerAlive=false;
                throw "KONIEC";
            }
        }
    }
}

void Game::delFromCont(Asteroide *ast)
{
    //zaimplementowac try i catch przy braku elementu w kontenerze!!!!

      for(unsigned int i=0; i<asteroides.size(); i++)
    {
        if(ast==asteroides[i])
        {
            if(asteroides.size()==1)
            {
                ast->destroyBody(world);
                asteroides.clear();
                delete ast;
            }
            else
            {
                // prev=--it;
                //  next=++it;
                ast->destroyBody(world);
                asteroides.erase(asteroides.begin()+i);
                delete ast;
            }
        }
    }
}

void Game::delFromCont(Missle *missle)
{
    //zaimplementowac try i catch przy braku elementu w kontenerze!!!!

    //  std::deque<Missle*>::iterator prev;
    //  std::deque<Missle*>::iterator next;

    //  for ( auto it = missles.begin(); it != missles.end(); ++it )
    for(unsigned int i=0; i<missles.size(); i++)
    {
        if(missle==missles[i])
        {
            if(missles.size()==1)
            {
                missle->destroyBody(world);
                missles.clear();
                delete missle;
            }
            else
            {
                // prev=--it;
                //  next=++it;
                missle->destroyBody(world);
                missles.erase(missles.begin()+i);
                delete missle;
            }
        }
    }
}


int Game::startGame()
{

    //PolygonGenerator pol;

    playerAlive=true;
    Renderer::getInstance();
    Events::getInstance();
    Renderer::getInstance().game=this;
    world.SetContactListener(&ContactListenerInstance);

//adding objects
    Ship* statek = new Ship(this);
    addToCont(statek);
    for(int i=0; i<100; i++)
    {
        Asteroide* ast = new Asteroide(this);
        addToCont(ast);
    }

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    try{
    while(playerAlive)
    {
        world.Step(Renderer::getInstance().ratio, velocityIterations, positionIterations);
        moveAll();
        Renderer::getInstance().drawAll();
        if(!Events::getInstance().checkEvents()) return 0;
        Camera::getInstance().calculateCameraMovement();
        Camera::getInstance().moveCamera();
    }
    }
    catch(string& e)
    {
        std::cout<<e<<std::endl;
    }

}

void Game::moveAll()
{

    for(unsigned int i = 0; i < asteroides.size(); i ++)
    {
        if(asteroides[i]->isAlive)
            asteroides[i]->update(Renderer::getInstance().ratio);
        else
            delFromCont(asteroides[i]);
    }

    if(ships[0]->isAlive){
        for(unsigned int i=0; i<ships[0]->modules.size(); i++)
        {

                ships[0]->modules[i]->calcSpeed();
                ships[0]->modules[i]->update(Renderer::getInstance().ratio);


        }

        ships[0]->update(Renderer::getInstance().ratio);//move();
        ships[0]->calcSpeed();
     }
     else
        delFromCont(ships[0]);



    for(unsigned int i=0; i<missles.size(); i++)
    {

        missles[i]->move();
        if(missles[i]->state==0)
            break;
        else if(missles[i]->state==2 )
        {
//temp            cout<<"usuwanie: "<<endl;
            delFromCont(missles[i]);
        }
        else if(missles[i]->state==3)
        {
            missles[i]->ttl2 -= Renderer::getInstance().ratio;
            if(missles[i]->ttl2<-0.051)
            {
                delFromCont(missles[i]);
//temp                cout<<"TTL2"<<missles[i]->ttl2<<endl;
            }

        }

    }
}

