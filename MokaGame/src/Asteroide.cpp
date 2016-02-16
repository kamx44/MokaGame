#include "Asteroide.h"
#include "Mmath.h"
#include "stdio.h"

Asteroide::Asteroide(Game* game) :game_asteroide(game)
{

    idObject = getRandomId();

    position = getRandomVec2(-100, 100);
    size = getRandomInt(3,8);

    textureID = -1;
    mass = 0;
    velocity = getRandomVec2(-5,5);
    fOrientation = 33;
    vertexCount = (int32)size;
    vertices = new b2Vec2[vertexCount];

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position[0], position[1]);
    fixtureDef.shape = &bodyShape;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 0.3f;

    buildBlob(size, getRandomFloat(0.5,6), getRandomFloat(0.5,6));
    bodyShape.Set(vertices,vertexCount);  //setting shape of polygon
    setToWorld(game_asteroide->world);
    setFixtureToBody();
    mass = body->GetMass();
}

Asteroide::Asteroide(glm::vec2 vposition, float fSize, unsigned int iTexture)
{
    position = vposition;
    size = fSize;
    textureID = iTexture;
    mass = fSize;               // tutaj trzeba polepszyæ
    velocity = getRandomVec2(-2, 2);
}

Asteroide::~Asteroide()
{

}
