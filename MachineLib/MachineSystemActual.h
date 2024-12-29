/**
 * @file MachineSystemActual.h
 * @author Thomas Toaz
 *
 * A Machine System class that displays a machine.
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H

#include "IMachineSystem.h"

class Machine;

/**
 * A Machine System class that displays a machine.
 */
class MachineSystemActual : public IMachineSystem
{
private:
    /**
     * A pointer to the machine class being displayed.
     */
    std::shared_ptr<Machine> mMachine;

    /**
     * Location of the machine system
     */
    wxPoint mLocation;

    /**
     * Display view flag
     */
     int mFlag;

    /**
     * Frame rate of the animation system
     */
    double mFrameRate = 30;

    /**
     * Current time of the machine system
     */
    double mCurrentTime = 0;

    /**
     * Current frame of the machine system
     */
    int mCurrentFrame = 0;

    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;

    /// Resource Directory of the project
    std::wstring mResourcesDir;

public:
    /// Constructor
    MachineSystemActual(std::wstring resourcesDir);

    /// Copy constructor (disabled)
    MachineSystemActual(const MachineSystemActual &) = delete;

    /// Assignment operator
    void operator=(const MachineSystemActual &) = delete;

    void SetLocation(wxPoint location) override;
    wxPoint GetLocation() override;

    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetMachineFrame(int frame) override;
    void SetFrameRate(double rate) override;
    void SetMachineNumber(int machine) override;
    int GetMachineNumber() override;
    double GetMachineTime() override;

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    void SetFlag(int flag) override {}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H
