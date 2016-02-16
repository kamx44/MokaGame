#include "Ship.h"
#include "Renderer.h"
#include "Events.h"
#include "Mmath.h"
#include <Box2D/Box2D.h>





Ship::Ship(Game* game) :game_ship(game)
{

    idObject = getRandomId();

    ship_img = new Image("data/img/statek.png");
    mis_img = new Image("data/img/rakieta.png");
  //object_type = TEXTURE;
    hp=1000;
    misID = mis_img->imageID;
    myID = ship_img->imageID;

    position[0] = 0;
    position[1] = 0;
    w=6.5;
    h=6.5;

    myID = ship_img->imageID;
    maxSpeed = 50;
    fOrientation = 0;
    mass = 0;

    //shape of ship
    vector<vector<b2Vec2*>> polCon = game->polygonGenerator.getPolygonContainer("statek.plist.xml");
    for(unsigned int i=0;i<polCon.size();i++){
        vector<b2Vec2*> vert2 = polCon[i];
        int32 mSize = vert2.size();
        b2Vec2* mVertices = new b2Vec2[mSize];
        for(int i=0;i<mSize;i++){
            glm::vec2 v = createGlmVec((*vert2[i]));
            v -= glm::vec2(2.9,2.9);
            mVertices[i]=createB2vec2(v);
        }
        module = new Module(this,game_ship,glm::vec2(0,0),mVertices,mSize);
       // b2Filter f = module->body->GetFixtureList()->GetFilterData();
      //  f.categoryBits = 0x0002;
     //   f.maskBits = 0x0004;
    //    f.groupIndex = -1;
        modules.push_back(module);
        mass+=module->body->GetMass();
        if(i==0){
            vertexCount = mSize;
            vertices = new b2Vec2[vertexCount];
            vertices = mVertices;
            body = module->body;
        }
        else
            createJoint(module->body);
    }

//TESTOWA OTOCZKA
  /*      b2Vec2* mVertices = new b2Vec2[4];
        mVertices[0]=b2Vec2(-5.5f, 5.5f);
        mVertices[1]=b2Vec2(5.5f, 5.5f);
        mVertices[2]=b2Vec2(5.5f, -5.5f);
        mVertices[3]=b2Vec2(-5.5f, -5.5f);
        module = new Module(game_ship,glm::vec2(0,0),mVertices,4);
        modules.push_back(module);
        createJoint(module->body);
      //  for(int i=0; i<module->body->GetFixtureList()->size();i++){
      b2Filter f = module->body->GetFixtureList()->GetFilterData();
      f.categoryBits = 0x0001;
      f.maskBits = 0x0002;
      f.groupIndex = 1;
      module->body->GetFixtureList()->SetFilterData(f); //.get(i).setSensor(true);
      module->fixtureDef.isSensor = true;
      module->fixtureDef.density = 0.01;
      module->body->CreateFixture(&module->fixtureDef);*/
      //  }
}


void Ship::createJoint(b2Body* bodyB){

   //jointDef.collideConnected=false;
   jointDef.Initialize(body, bodyB, body->GetWorldCenter());

   jointWeld = (b2WeldJoint*)game_ship->world.CreateJoint( &jointDef );

}



void Ship::strzel_rakieta(KIND type)
{
    Missle* missle = new Missle(this,type,position,position+(orientation2*glm::vec2(20,20)));

    missle->type=type;
    missle->myID=misID;
    missle->setToWorld(game_ship->world);
    missle->setFixtureToBody();
    game_ship->addToCont(missle);

}



void Ship::calcSpeed(){

    static int past=0;  //wtf #morf
    int mouse_x = Events::getInstance().mouseX;
    int mouse_y = Events::getInstance().mouseY;

    float desiredAngle = atan2f( mouse_x, mouse_y)-M_PI;
    float bodyAngle = body->GetAngle();


    ///< calculating rotation

    float totalRotation = desiredAngle - bodyAngle;
    while ( totalRotation < DEGTORAD(-180) ) totalRotation += DEGTORAD(360) ;
    while ( totalRotation > DEGTORAD(180) ) totalRotation -= DEGTORAD(360) ;
    float change = DEGTORAD(1) ;
    float newAngle = bodyAngle + 5*min( change, max(-change, totalRotation));

    body->SetTransform( body->GetPosition(), newAngle );
    setOrientation(body->GetAngle()+M_PI/2);
    if(Events::getInstance().keypadKeys[SDLK_m] ){
        int present = Events::getInstance().keypadKeys[SDLK_m];
        if(past!=present)
            {
                strzel_rakieta(LASER);
            }
        past=1;
      }
      else if(Events::getInstance().keypadKeys[SDLK_n]){
        int present = Events::getInstance().keypadKeys[SDLK_n];
        if(past!=present)
            {
                strzel_rakieta(BULLET);
            }
        past=1;
      }
      else if(Events::getInstance().keypadKeys[SDLK_b]){
        int present = Events::getInstance().keypadKeys[SDLK_b];
        if(past!=present)
            {
                strzel_rakieta(PLASMA);
            }
        past=1;
      }
      else
        past=0;

        glm::vec2 force(0);
        glm::vec2 force2(0);
        glm::vec2 force3(0);
        //force forward and backward
        force += glm::vec2(400) * orientation2 * glm::vec2(Events::getInstance().keypadKeys[SDLK_w]);
        force -= glm::vec2(400) * orientation2 * glm::vec2(Events::getInstance().keypadKeys[SDLK_s]);
        //force left and right
        force2 = glm::vec2(400) * orientation2 * glm::vec2(Events::getInstance().keypadKeys[SDLK_a]);
        force += glm::vec2(-force2.y,force2.x);
        force3 = glm::vec2(400) * orientation2 * glm::vec2(Events::getInstance().keypadKeys[SDLK_d]);
        force += glm::vec2(force3.y,-force3.x);

        body->ApplyForce(createB2vec2(force), body->GetWorldCenter(), 1);

}



Ship::~Ship()
{
    //dtor
}
