
#include "ContactListener.h"
#include "Module.h"
#include "Missle.h"
#include "Asteroide.h"
#include "Object.h"



ContactListener::ContactListener()
{
    bContact = false;
}

ContactListener::~ContactListener()
{
    //dtor
}


void ContactListener::BeginContact(b2Contact* contact) {

      //check if fixture A was a Object
      bContact = true;
      std::cout<<"KONTAKT"<<std::endl;
      Object* bodyUserDataA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
      Object* bodyUserDataB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();
     // std::cout<<bodyUserData->getEntityType()<<std::endl;
      if ( (bodyUserDataA->getEntityType()==3 && bodyUserDataB->getEntityType()==1)){
        dynamic_cast<Missle*>( bodyUserDataB )->startContact();
        dynamic_cast<Asteroide*>( bodyUserDataA )->startContact();
      }
      else if ( (bodyUserDataA->getEntityType()==4 && bodyUserDataB->getEntityType()==3)){
        dynamic_cast<Module*>( bodyUserDataA )->startContact();
        dynamic_cast<Asteroide*>( bodyUserDataB )->startContact();
     //   bodyUserDataB.body->
        b2Vec2 vel = dynamic_cast<Module*>( bodyUserDataA )->body->GetLinearVelocity();
        std::cout<<"Velocity: "<<vel.x<<" "<<vel.y<<std::endl;
        float mas = dynamic_cast<Module*>( bodyUserDataA )->parent->mass;
        std::cout.setf( std::ios::fixed );
        std::cout.precision(5);
        std::cout<<"Mass"<<mas<<std::endl;

        b2Vec2 vel2 = dynamic_cast<Asteroide*>( bodyUserDataB )->body->GetLinearVelocity();
        std::cout<<"Velocity2: "<<vel2.x<<" "<<vel2.y<<std::endl;
        float mas2 = dynamic_cast<Asteroide*>( bodyUserDataB )->mass;
        std::cout.setf( std::ios::fixed );
        std::cout.precision(5);
        std::cout<<"Mass2"<<mas2<<std::endl;

        std::cout<<"ENERGIA KINETYCZNA 1";

	//
      }
      else if ( (bodyUserDataA->getEntityType()==4 && bodyUserDataB->getEntityType()==4)){
          std::cout<<"KUIRWAAA"<<std::endl;
      }
}

void ContactListener::EndContact(b2Contact* contact) {

      //check if fixture A was a Object
      Object* bodyUserDataA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
      Object* bodyUserDataB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();
     // std::cout<<bodyUserData->getEntityType()<<std::endl;
      if ( (bodyUserDataA->getEntityType()==3 && bodyUserDataB->getEntityType()==1)){
        static_cast<Missle*>( bodyUserDataB )->endContact();
        static_cast<Asteroide*>( bodyUserDataA )->endContact();
      }
      else if ( (bodyUserDataA->getEntityType()==4 && bodyUserDataB->getEntityType()==3)){
        dynamic_cast<Module*>( bodyUserDataA )->endContact();
        dynamic_cast<Asteroide*>( bodyUserDataB )->endContact();
      }
      bContact = false;
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
     Object* bodyUserDataA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
     Object* bodyUserDataB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();
     if ( (bodyUserDataA->getEntityType()==4 && bodyUserDataB->getEntityType()==4)){
        if(dynamic_cast<Module*>( bodyUserDataA )->parentId==dynamic_cast<Module*>( bodyUserDataB )->parentId)
            contact->SetEnabled(false);
     }
}


void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
    //if(bContact){
      Object* bodyUserDataA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData();
     Object* bodyUserDataB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData();
     // if ( (bodyUserDataA && bodyUserDataB)){
       //   std::cout<<"impulse->count: "<<impulse->count<<std::endl;
      for(int i=0;i<impulse->count;i++){
          std::cout<<"impulse->normalImpulses "<<i<<" :"<<impulse->normalImpulses[i]<<std::endl;
          bodyUserDataA->setDamage(impulse->normalImpulses[i]);
          bodyUserDataB->setDamage(impulse->normalImpulses[i]);
      }

      //}
   // }
 }

