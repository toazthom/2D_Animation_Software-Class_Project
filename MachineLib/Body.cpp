/**
 * @file Body.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "Body.h"

/**
 * Adds a point to create the body
 * @param x x-position of point being added
 * @param y x-position of point being added
 */
void Body::AddPoint(int x, int y)
{
    mPolygon.AddPoint(x,y);
}

/**
 * Draw our polygon.
 * @param graphics The graphics context to draw on
 */
void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}

/**
 * Update body component of machine
 * @param elapsed time elasped since last update
 */
void Body::Update(double elapsed)
{

}

/**
 * Sets the initial location of the body in the machine
 * @param x x location of body
 * @param y y location of body
 */
void Body::SetInitialPosition(double x, double y)
{
    mPolygon.SetInitialPosition(x,y);
}

/**
 * Create a rectangle body
 * @param x x-location of rectangle
 * @param y y-location of rectangle
 * @param width width of rectangle
 * @param height height of rectangle
 */
void Body::Rectangle(double x, double y, double width, double height)
{
    mPolygon.Rectangle(x,y,width,height);
}

/**
 * Create a circle body
 * @param radius The radius of the circle
 */
void Body::Circle(int radius)
{
    mPolygon.Circle(radius);
}

/**
 * Set the physics qualities of the body
 * @param density density of the body
 * @param friction friction of the body
 * @param restitution restitution of the body
 */
void Body::SetPhysics(double density, double friction, double restitution)
{
    mPolygon.SetPhysics(density,friction,restitution);
}

/**
 * Install the body into the physics world
 * @param world
 */
void Body::InstallPhysics(std::shared_ptr<b2World> world)
{
    mPolygon.InstallPhysics(world);
}

/**
 * Rotate the body for when in contact with a rotational source
 * @param rotation rotation of body
 * @param speed speed of rotation
 */
void Body::Rotate(double rotation, double speed)
{
    mPolygon.SetAngularVelocity(speed);
}

/**
 * Call bottomCenteredRectangle on body's physics polygon
 * @param x
 * @param y
 */
void Body::BottomCenteredRectangle(double x, double y)
{
    mPolygon.BottomCenteredRectangle(wxSize(x,y));
}

/**
 * Set the initial rotation of the body component
 * @param rotation
 */
void Body::SetInitialRotation(double rotation)
{
    mPolygon.SetRotation(rotation);
}
