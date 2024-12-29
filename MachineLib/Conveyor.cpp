/**
 * @file Conveyor.cpp
 * @author Thomas Toaz
 */

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

#include "pch.h"
#include "Conveyor.h"
#include "ContactListener.h"
#include "b2_contact.h"

/**
 * Constructor for Converyor
 * @param imagesDir image directory
 */
Conveyor::Conveyor(std::wstring imagesDir)
{
    mConveyor.BottomCenteredRectangle(ConveyorSize);
    mConveyor.SetImage(imagesDir + ConveyorImageName);
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Conveyor::BeginContact(b2Contact *contact)
{
    // Transfter Energy to the other stuff

}

/**
 * Update the conveyir
 * @param elapsed time since last update
 */
void Conveyor::Update(double elapsed)
{

}

/**
 * Draw our polygons for the conveyor.
 * @param graphics The graphics context to draw on
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mConveyor.Draw(graphics);
}

/**
 * Sets the initial location of the component in the machine
 * @param x The x-initial position of the component piece
 * @param y The y-initial position of the component piece
 */
void Conveyor::SetPosition(double x, double y)
{
    mConveyor.SetInitialPosition(x,y);
    Component::SetPosition(x,y);
}

/**
 * Install the body into the physics world
 * @param world
 */
void Conveyor::InstallPhysics(std::shared_ptr<b2World> world)
{
    mConveyor.InstallPhysics(world);
}

/**
 * Rotate the body for when in contact with a rotational source
 * @param rotation rotation of body
 * @param speed speed of rotation
 */
void Conveyor::Rotate(double rotation, double speed)
{
    //Add stuff here, set speed?
    mSpeed = speed;

    auto contact = mConveyor.GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(-speed, 0));
        }

        contact = contact->next;
    }
}

/**
 * Get the location of the conveyor shaft
 * @return
 */
wxPoint Conveyor::GetShaftPosition()
{
    double rotationX = 0;
    double rotationY = 0;
    if(mRotation!=0)
    {
        rotationX = (ConveyorShaftOffset.m_x)*cos(mRotation);
        rotationY = (ConveyorShaftOffset.m_y)*sin(mRotation);
    }

    return wxPoint(mConveyor.GetPosition().m_x + ConveyorShaftOffset.m_x - rotationX,mConveyor.GetPosition().m_y + ConveyorShaftOffset.m_y - rotationY);
}

/**
 * Add a contact listener to the componenet
 * @param listener contact listener of the world
 */
void Conveyor::AddContact(std::shared_ptr<ContactListener> listener)
{
    listener->Add(mConveyor.GetBody(), this);
}

/**
 * Transfer the tangent speed to contact objects
 * @param contact
 * @param oldManifold
 */
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetTangentSpeed(mSpeed);
}

/**
 * Set the initial rotation of the body component
 * @param rotation
 */
void Conveyor::SetInitialRotation(double rotation)
{
    mConveyor.SetRotation(rotation);
    mRotation = rotation;
}
