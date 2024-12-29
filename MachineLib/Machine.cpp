/**
 * @file Machine.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"
#include "b2_world.h"
#include "ContactListener.h"

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;


/**
 * Machine constructor
 * @param number Which machine we are creating
 */
Machine::Machine(int number)
{
    {
        mNumber = number;
        mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));
    }
}

/**
* Draw the machine looping through all of its component pieces
* @param graphics Graphics object to render to
*/
void Machine::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    for(auto component : mComponents)
    {
        component->Draw(graphics);
    }
}

/**
 * Update the machine/all its components
 * @param elapsed The time between the last update and this current update
 */
void Machine::Update(double elapsed)
{
    for(auto component : mComponents)
    {
        component->Update(elapsed);
    }

    // Advance the physics system one frame in time
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}

/**
 * Reset the machine system
 */
void Machine::Reset()
{
    // Create new b2world
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

    // Create and install the contact filter
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());

    // Install components into physics world
    for(auto component : mComponents)
    {
        component->InstallPhysics(mWorld);
        component->AddContact(mContactListener);
    }
}

/**
 * Add a component to the machine
 * @param component component being added
 */
void Machine::AddComponent(const std::shared_ptr<Component> &component)
{
    mComponents.push_back(component);
    component->SetMachine(this);
}

