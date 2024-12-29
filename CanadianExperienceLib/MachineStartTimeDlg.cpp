/**
 * @file MachineStartTimeDlg.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>

#include "MachineStartTimeDlg.h"
#include "MachineAdapter.h"

/**
 * Constructor
 * @param parent The parent window we will center in
 * @param adapter the machine adapter we are altering
 */
MachineStartTimeDlg::MachineStartTimeDlg(wxWindow* parent, MachineAdapter* adapter) : mMachineAdapter(adapter)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"MachineStartTimeDlg");

    mFrameOffsetAmount = adapter->GetFrameOffset();

    Bind(wxEVT_BUTTON, &MachineStartTimeDlg::OnOK, this, wxID_OK);

    auto numFramesCtrl = XRCCTRL(*this, "AdapterFrameOffset", wxTextCtrl);
    wxIntegerValidator<int> numFramesValidator(&mFrameOffsetAmount);
    numFramesValidator.SetRange(1, 10000);
    numFramesCtrl->SetValidator(numFramesValidator);
}

/**
 * Handle an OK button press
 * @param event Button event
 */
void MachineStartTimeDlg::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        mMachineAdapter->SetFrameOffset(mFrameOffsetAmount);

        EndModal(wxID_OK);
    }
}