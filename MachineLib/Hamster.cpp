/**
 * @file Hamster.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "Hamster.h"
#include "ContactListener.h"
#include "b2_contact.h"
#include "RotationSource.h"

/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is now many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint2DDouble(25, 40);

/// multiplier for the rotation amount to convert it into ints to index hamster image by
const int RotationMultiplier = 16;

/// Maximum rotational index of hamster when subdividing rotations
const int MaxRotationIndex = 12;

/// Maximum rotational index of hamster when subdividing rotations
const int MidRotationIndex = 8;

/// Maximum rotational index of hamster when subdividing rotations
const int MinRotationIndex = 4;

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the DEMON HAMSTER cage
const std::wstring DemonHamsterCageImage = L"/demonHamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};


/// The DEMON HAMSTER running hamster animation images.
const std::wstring DemonHamsterImages[4] =
    {L"/demonHamster-sleep.png", L"/demonHamster-run-1.png",
        L"/demonHamster-run-2.png", L"/demonHamster-run-3.png"};


/**
 * hamster object constructor
 * @param imagesDir directory for the images hamster need to access
 */
Hamster::Hamster(std::wstring imagesDir)
{
    mCage.BottomCenteredRectangle(HamsterCageSize);
    mWheel.CenteredSquare(HamsterWheelSize);

    mCage.SetImage(imagesDir + HamsterCageImage);
    mWheel.SetImage(imagesDir + HamsterWheelImage);

    mHamsters = std::vector<cse335::Polygon>(4);

    for(auto i = 0; i<4;i++)
    {
        mHamsters[i].SetImage(imagesDir + HamsterImages[i]);
        mHamsters[i].CenteredSquare(HamsterWheelSize);
    }

}

/**
 * Set the speed of the hamster
 * @param speed The new speed of the hamster
 */
void Hamster::SetSpeed(double speed)
{
    mSpeed = speed;
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Hamster::BeginContact(b2Contact *contact)
{
    // Turn the hamster on
    mRunning = true;
    mHamsterIndex = 1;
}

/**
 * Update the hamster
 * @param elapsed time since last update
 */
void Hamster::Update(double elapsed)
{
    // This is incomplete...
    if(mRunning)
    {
        mRotation += -mSpeed * elapsed;
    }

    if(abs(mRotation) > 1)
    {
        mRotation = 0;
    }


    if (mHamsterIndex != 0)
    {
        mSource.SetRotation(mRotation, -mSpeed);
        mSource.UpdateSinks();
        // Increment hamster indexes to animate running, casting to int.
        mHamsterIndex = abs(mRotation)*RotationMultiplier + 1;

        // 4 hamster images, so adjust the int cast so that it does not go beyond 4 in a given rotation.
        // A rotation is 0-1 for a full rotation.
        if(mHamsterIndex>MaxRotationIndex)
        {
            mHamsterIndex = mHamsterIndex - MaxRotationIndex;
        }
        else if(mHamsterIndex>MidRotationIndex)
        {
            mHamsterIndex = mHamsterIndex - MidRotationIndex;
        }
        else if(mHamsterIndex>MinRotationIndex)
        {
            mHamsterIndex = mHamsterIndex - MinRotationIndex;
        }

        if(mHamsterIndex==4 || mHamsterIndex==5)
        {
            mHamsterIndex =2;
        }
    }
    else
    {
        // Stop all sinks this source is attached to.
        mSource.SetRotation(0, 0);
        mSource.UpdateSinks();
    }
}

/**
 * Draw our polygons for the hamster.
 * @param graphics The graphics context to draw on
 */
void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mCage.Draw(graphics);
    mWheel.DrawPolygon(graphics,mPosition.m_x + WheelCenter.m_x,mPosition.m_y + WheelCenter.m_y,mRotation);

    graphics->PushState();
    graphics->Translate(mPosition.m_x + WheelCenter.m_x, mPosition.m_y + WheelCenter.m_y);

    if(mSpeed < 0)
    {
        graphics->Scale(-1, 1);
    }


    // Draw the running image
    mHamsters[mHamsterIndex].DrawPolygon(graphics, 0, 0, 0);

    graphics->PopState();

}

/**
 * Sets the initial location of the component in the machine
 * @param x The x-initial position of the component piece
 * @param y The y-initial position of the component piece
 */
void Hamster::SetPosition(double x, double y)
{
    mCage.SetInitialPosition(x,y);
    mPosition = wxPoint2DDouble(x,y);
}

/**
 * Install the body into the physics world
 * @param world
 */
void Hamster::InstallPhysics(std::shared_ptr<b2World> world)
{
    mCage.InstallPhysics(world);

    // Reset hamster for cases where hamster is not initially running
    // And restarting the machine should make them asleep again.
    if(!mInitiallyRunning)
    {
        mRunning = false;
        mHamsterIndex = 0;
    }

}

/**
     * Set the hamster to intitially running by making it's speed non-zero
     * @param running boolean value of whether the hamster shoudl be running at start
     */
void Hamster::SetInitiallyRunning(bool running)
{
    mRunning = true;
    mInitiallyRunning = true;
    mHamsterIndex = 1;
}

/**
 * Get the location of the hamster shaft
 * @return
 */
wxPoint Hamster::GetShaftPosition()
{
    return wxPoint(mPosition.m_x + HamsterShaftOffset.m_x,mPosition.m_y + HamsterShaftOffset.m_y);
}

/**
 * Add a contact listener to the componenet
 * @param listener contact listener of the world
 */
void Hamster::AddContact(std::shared_ptr<ContactListener> listener)
{
    listener->Add(mCage.GetBody(), this);
}

/**
 * Turns hamster into DEMON HAMSTER!
 * @param imagesDir images directory
 */
void Hamster::TurnDemon(std::wstring imagesDir)
{
    mHamsters = std::vector<cse335::Polygon>(4);
    for(auto i = 0; i<4;i++)
    {
        mHamsters[i].SetImage(imagesDir + DemonHamsterImages[i]);
        mHamsters[i].CenteredSquare(HamsterWheelSize);
    }
    mCage.SetImage(imagesDir + DemonHamsterCageImage);
}
