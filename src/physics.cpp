#include "physics.h"
#include <math.h>
#include <iostream>

// Thing constructor
Thing::Thing(float x, float y, float radius)
: x{x}, y{y}, radius{radius}, dX{0}, dY{0}
{
}
// end of Thing constructor

void Thing::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Thing::getX()
{
return this->x;
}

float Thing::getY()
{
return this->y;
}

float Thing::getRadius()
{
return this->radius;
}

void Thing::applyForce(float xForce, float yForce)
{
    dX += xForce;
    dY += yForce;
}


bool Thing::didCollide(Thing& otherThing)
{
    float distX = this->x - otherThing.x;
    float distY = this->y - otherThing.y;
    float distance = sqrt( (distX*distX)+ (distY*distY) );

//     // if the distance is less than the circle's
//     // radius the point is inside!
    if (distance < this->radius + otherThing.radius) 

    {
        return true;   
    }
        return false;
}

void Thing::update()
{
    x += dX;
    y += dY;
}

//World Constructor
World::World(float width, float height, float gravity)
: width{width}, height{height}, gravity{gravity}, things{}
{
}
//End of World Constructor

float World::getWidth()
{
    return this->width;
}

float World::getHeight()
{
    return this->height;
}

void World::addThing(Thing* thing)
{   
    things.push_back(thing);
}

void World::removeThing(Thing* thing)
{ 
    things.erase(things.begin());
}

bool World::didThingsCollide(Thing* thing1, Thing* thing2)
{
    float distX = thing1->getX() - thing2->getX();
    float distY = thing1->getY() - thing2->getY();
    float distance = sqrt( (distX*distX)+ (distY*distY) );

     if(distance < thing1->getRadius() + thing2->getRadius())
     {
         applyRepulsion(1.0f,1.0f);
         return true;
     }
     return false;
}

bool World::isThingOutOfBounds(Thing* thing)
{
    if (thing->getX() > this->width 
        || thing->getX() < this->width - this-> width
        || thing->getY() > this->height 
        || thing->getY() < this->height - this->height)
    {
        removeThing(thing);
        return true;
    }
    return false;
}


int World::countThings()
{
    return this->things.size();
}

void World::applyGravity(float gravity, Thing* thing)
{
    float thingHeight = thing->getY();

    for (int i = 0; i < this->height; i++)
    {
        thingHeight += gravity;
        thing->setPosition(thing->getX(), thingHeight);

        if (thingHeight == this->height)
        {
            break;
        }
    }
}

void World::applyRepulsion(float xForce, float yForce)
{
    for (int  i = 0; i < things.size(); i++)
    {
        float xPos = things[i]->getX();
        float yPos = things[i]->getY();

        xPos -= xForce;
        yPos -= yForce;

        things[i]->setPosition(xPos, yPos);
        things[i]->setPosition(xPos, yPos);
    }
    
}