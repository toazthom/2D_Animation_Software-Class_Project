/**
 * @file MachineSystemActual.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "MachineSystemActual.h"
#include "Machine.h"
#include "MachineFactory1.h"
#include "MachineFactory2.h"

/// number of machine 1
const int Machine1Number = 1;

/**
 * Constructor for the machine system
 * @param resourcesDir
 */
MachineSystemActual::MachineSystemActual(std::wstring resourcesDir)
{
    mResourcesDir = resourcesDir;
    SetMachineNumber(Machine1Number);

}

/**
* Set the position for the root of the machine
* @param location The x,y location to place the machine
*/
void MachineSystemActual::SetLocation(wxPoint location)
{
    mLocation = location;
}

/**
 * Get the location of the machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystemActual::GetLocation()
{
    return mLocation;
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineSystemActual::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);

    // Draw your machine assuming an origin of 0,0
    mMachine->DrawMachine(graphics);

    graphics->PopState();


}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystemActual::SetMachineFrame(int frame)
{
    if(frame < mCurrentFrame)
    {
        mCurrentFrame = 0;
        mMachine->Reset();
    }

    for( ; mCurrentFrame < frame;  mCurrentFrame++)
    {
        mMachine->Update(1.0 / mFrameRate);
    }

    // May need more than these, but you'll figure that out...


}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystemActual::SetFrameRate([[maybe_unused]] double rate)
{

}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void MachineSystemActual::SetMachineNumber(int machine)
{
    if(machine == Machine1Number)
    {
        MachineFactory1 machineFactory(mResourcesDir);
        mMachine = machineFactory.Create();
    }
    else
    {
        MachineFactory2 machineFactory(mResourcesDir);
        mMachine = machineFactory.Create();
    }
    mMachine->Reset();
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystemActual::GetMachineNumber()
{
    return mMachine->GetMachine();
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystemActual::GetMachineTime()
{
    return mCurrentFrame/mFrameRate;
}