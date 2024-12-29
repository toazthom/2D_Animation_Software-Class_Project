/**
 * @file MachineStartTimeDlg.h
 * @author Thomas Toaz
 *
 * Machine start time/offset setter dialog box
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTTIMEDLG_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTTIMEDLG_H

class MachineAdapter;

/**
 * Machine start time/offset setter dialog box
 */
class MachineStartTimeDlg final : public wxDialog{
private:
    void OnOK(wxCommandEvent& event);

    /// The pointer to the machine adapter
    MachineAdapter *mMachineAdapter;

    /// Start frame of the machine
    int mFrameOffsetAmount = 0;

public:
    MachineStartTimeDlg(wxWindow* parent, MachineAdapter *adapter);
};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTTIMEDLG_H
