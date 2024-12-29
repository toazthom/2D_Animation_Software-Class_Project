/**
 * @file MachineAdapter.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "MachineAdapter.h"
#include "Drawable.h"
#include "Timeline.h"
#include "MachineStartTimeDlg.h"

/**
 * Constructor for machine adapter object
 * @param name name of the adapter
 * @param resourceDir
 */
MachineAdapter::MachineAdapter(const std::wstring& name,std::wstring resourceDir):
    Drawable(name)
{
    MachineSystemFactory systemFactory(resourceDir);
    mMachineSystem = systemFactory.CreateMachineSystem();
    mMachineSystem->SetLocation(wxPoint(300,300));
}

/**
 * Draw the machine adapter object
 * @param graphics
 */
void MachineAdapter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double scale = 0.60f;

    graphics->PushState();
    graphics->Scale(scale, scale);
    graphics->Translate(GetPosition().x,GetPosition().y);
    mMachineSystem->DrawMachine(graphics);
    graphics->PopState();
}

/**
 * Return whether machine adapter is at current location
 * @param pos
 * @return
 */
bool MachineAdapter::HitTest(wxPoint pos)
{
    // Always true because only called within actor, and the machine in
    // Actor is spread over a wide area with no one/particular position
    return true;
}

/**
 * Show the dialog box for the machine system
 * @param parent parent window to display the dialog box at
 */
void MachineAdapter::ShowDialogBox(wxWindow* parent)
{
    MachineDialog dlg(parent, mMachineSystem);
    if (dlg.ShowModal() == wxID_OK)
    {
        // A machine has been selected
        parent->Refresh();
    }

    MachineStartTimeDlg dlg1(parent, this);
    if (dlg1.ShowModal() == wxID_OK)
    {
        // A machine has been selected
        parent->Refresh();
    }
}

/**
 * Set the machine system properties to match those fo the timeline
 */
void MachineAdapter::GetKeyframe()
{
    auto timeline = GetAngleChannel()->GetTimeline();
    mMachineSystem->SetFrameRate(timeline->GetFrameRate());

    // Calculate what the current frame of the machine should be base on it's starting frame offset
    double machineFrame = timeline->GetCurrentFrame()-mFrameOffset;

    if(machineFrame >= 0)
    {
        mMachineSystem->SetMachineFrame(machineFrame);
    }
    else
    {
        mMachineSystem->SetMachineFrame(-1);
    }
}

/**
 * Set the machine number for the machine you want to use
 * @param num the machine number
 */
void MachineAdapter::SetMachineNumber(int num)
{
    mMachineSystem->SetMachineNumber(num);
}
