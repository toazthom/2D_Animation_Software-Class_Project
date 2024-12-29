/**
 * @file MachineAdapter.h
 * @author Thomas Toaz
 *
 * Adapter class to make machine work with Canadian Experience
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H

#include "Drawable.h"
#include <machine-api.h>

/**
 * Adapter class to make machine work with Canadian Experience
 */
class MachineAdapter : public Drawable
{
private:
    /// Machine system of the adapter
    std::shared_ptr<IMachineSystem> mMachineSystem;

    /// Offset frame value for when you want the machine to start running
    double mFrameOffset = 0;

public:
    MachineAdapter(const std::wstring& name,std::wstring resourceDir);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(wxPoint pos) override;
    void ShowDialogBox(wxWindow* parent) override;
    void GetKeyframe()override;
    void SetMachineNumber(int num);

    /**
     * Get the machine number of the machine in the adapter
     * @return the machine number
     */
    int GetMachineNumber() {return mMachineSystem->GetMachineNumber();}

    /**
     * Set the frame you want the machine to start running on
     * @param offset the offset/machine starting frame
     */
    void SetFrameOffset(double offset) {mFrameOffset = offset;}

    /**
     * Get the frame offset for when the machine will start in the animation
     * @return The frame offset for the machine
     */
    double GetFrameOffset() {return mFrameOffset;}

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H
