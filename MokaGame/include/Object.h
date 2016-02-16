#ifndef OBJECT_H
#define OBJECT_H

#include <math.h>
#include <set>
#include <glm/glm.hpp>
#include <glm/detail/type_mat2x2.hpp>
#include <Box2D/Box2D.h>






enum TYP{
        TEXTURE,
        FIGURE
    };

class Object
{
    public:
        Object();
        virtual ~Object();

        static std::set<int> idContainer;
        TYP object_type;  //typ obiektu
        glm::vec2 position;             // position of the object
        glm::vec2 velocity;             // linear velocity
        float acceleration;             // acceleration
        float maxSpeed;                 // max speed of the object

        b2CircleShape circle;           // circle shape
        b2BodyDef bodyDef;              // box2d body definition
        b2Body* body;                   // pointer to body in the world object
        b2PolygonShape bodyShape;       // shape of body
        b2FixtureDef fixtureDef;        // fixture definition
     // b2Fixture fixture;              // fixture of the body
        bool m_contacting;              // cheking if thers any contact
        float angularVelocity;          // predkosc katowa
        float torque;                   // moment obrotowy
        glm::vec2 force;                // force which moves object
        glm::mat2 orientation;          // orientacja w przestrzeni - wektory OBB
        glm::vec2 orientation2;
        float fOrientation;             // moze sie przydac  KAT
        int32 vertexCount;
        b2Vec2 *vertices;
        glm::vec2 normals[32];


        // Set by shape?
        float inertia;                  // moment bezwladnosci
        float inverseInertia;           // inverse inertia
        float mass;                     // mass
        float inverseMass;              // inverse masee
        float hp;                       // health
        int   idObject;                 // id of the object
        bool  isAlive;

        float staticFriction;           // tarcie statyczne
        float dynamicFriction;          // dynamiczne ...
        float restitution;              // opor powietrza?




        virtual void startContact(){
            m_contacting = true;
        }
        virtual void endContact(){
            m_contacting = false;
        }
        virtual int getEntityType() = 0;
        int getRandomId();
        void setOrientation(float angle);                             // z kata do wektora 2x2 ...
        glm::vec2 getSupport(glm::vec2 dir);
        int buildBlob(int numVertices, float radiusX, float radiusY);
        void update(float dt);
        void setToWorld(b2World &world);
        void setFixtureToBody();
        void destroyBody(b2World &world);
        void ApplyImpulse(  glm::vec2& impulse,  glm::vec2& contactVector );  //dostanie impulsa
        virtual void setDamage(float damage);
        virtual void delObject();
        int move();

    protected:
    private:
};



#endif // OBJECT_H
