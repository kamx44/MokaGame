#ifndef GAME_H
#define GAME_H

#include <vector>

//#include "Module.h"
//#include "Ship.h"
//#include "Missle.h"
#include "ContactListener.h"
#include "PolygonGenerator.h"


class Asteroide;
class Module;
class Ship;
class Missle;

class Game
{
    public:
        Game();
        virtual ~Game();
        std::vector<Ship*> ships;
        std::vector<Missle*> missles;
        std::vector<Asteroide*> asteroides;
        std::vector<Module*> modules;
        bool playerAlive;

        ContactListener ContactListenerInstance;
        PolygonGenerator polygonGenerator;

        void addToCont(Ship *ship);
        void delFromCont(Ship *ship);


        void addToCont(Missle *missle);
        void delFromCont(Missle *missle);
        void addToCont(Asteroide *ast);
        void delFromCont(Asteroide *ast);
        void addToCont(Module *mod);
        void moveAll();

        int startGame();

        b2Vec2 gravity;
        b2World world;

    protected:
    private:


};

#endif // GAME_H
