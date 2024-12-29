/**
 * @file PictureFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineAdapter.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add machine adapter actors
    std::shared_ptr<Actor> machineAdapterActor1= std::make_shared<Actor>(L"Machine");
    auto machineDrawable1 = std::make_shared<MachineAdapter>(L"Machine",resourcesDir);
    machineDrawable1->SetPosition(wxPoint(200, 250));
    machineDrawable1->SetFrameOffset(40);
    picture->SetMachineOne(machineDrawable1);
    machineAdapterActor1->AddDrawable(machineDrawable1);
    machineAdapterActor1->SetPosition(wxPoint(200, 250));
    picture->AddActor(machineAdapterActor1);

    std::shared_ptr<Actor> machineAdapterActor2= std::make_shared<Actor>(L"Machine");
    auto machineDrawable2 = std::make_shared<MachineAdapter>(L"Machine",resourcesDir);
    machineDrawable2->SetMachineNumber(2);
    machineDrawable2->SetPosition(wxPoint(1200, 400));
    machineDrawable2->SetFrameOffset(90);
    picture->SetMachineTwo(machineDrawable2);
    machineAdapterActor2->AddDrawable(machineDrawable2);
    machineAdapterActor2->SetPosition(wxPoint(200, 250));
    picture->AddActor(machineAdapterActor2);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(300, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(550, 620));
    picture->AddActor(sparty);


    return picture;
}

