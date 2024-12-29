/**
 * @file MachineFactory2.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "MachineFactory2.h"
#include "Machine.h"
#include "Body.h"
#include "Goal.h"
#include "Pulley.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "HamsterAndConveyorFactory.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
MachineFactory2::MachineFactory2(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}



/**
 * Factory method to create machine #1
 * @return
 */
std::shared_ptr<Machine> MachineFactory2::Create()
{
    // The machine itself
    // In this solution the machine number is passed
    // to the working machine constructor, so it knows
    // its number.
    auto machine = std::make_shared<Machine>(2);

    // Notice: All dimensions are in centimeters and assumes
    // the Y axis is positive in the up direction.

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    //
    // The floor
    //
    // The values are chosen so the top of the floor
    // is at Y=0
    //
    auto floor = std::make_shared<Body>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImagesDir + L"/floor.png");
    machine->AddComponent(floor);

    auto platform = std::make_shared<Body>();
    platform->Rectangle(100, 0, 200, 17);
    platform->SetImage(mImagesDir + L"/floor.png");
    platform->SetInitialRotation(.20);
    machine->AddComponent(platform);

    auto platform1 = std::make_shared<Body>();
    platform1->Rectangle(-300, -0, 200, 17);
    platform1->SetImage(mImagesDir + L"/floor.png");
    platform1->SetInitialRotation(-.2);
    machine->AddComponent(platform1);

    auto platform2 = std::make_shared<Body>();
    platform2->Rectangle(-250, 400, 300, 17);
    platform2->SetImage(mImagesDir + L"/floor.png");
    platform2->SetInitialRotation(-0.1);
    machine->AddComponent(platform2);

    // Basketball 1
    auto basketball1 = std::make_shared<Body>();
    basketball1->Circle(12);
    basketball1->SetImage(mImagesDir + L"/deathStar.png");
    basketball1->SetInitialPosition(30, 353);
    basketball1->SetDynamic();
    basketball1->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball1);

    AddBasketball(machine,37,307);
    AddBasketball(machine,77,300);
    AddBasketball(machine,87,200);
    AddBasketball(machine,279,236);
    AddBasketball(machine,150,200);
    AddBasketball(machine,20,220);
    AddBasketball(machine,-200,289);
    AddBasketball(machine,-107,220);
    AddBasketball(machine,-56,100);
    AddBasketball(machine,-129,150);
    AddBasketball(machine,-130,240);


    //
    // The hamster motor for the second-beam
    //
    auto hamster = std::make_shared<Hamster>(mImagesDir);
    hamster->SetPosition(100, 0);
    hamster->SetInitiallyRunning(true);      // Initially running
    hamster->SetSpeed(-1);
    hamster->TurnDemon(mImagesDir);
    machine->AddComponent(hamster);
    auto hamsterShaft = hamster->GetShaftPosition();


    auto conveyor = std::make_shared<Conveyor>(mImagesDir);
    conveyor->SetPosition(30,50);
    machine->AddComponent(conveyor);
    auto conveyorShaft = conveyor->GetShaftPosition();

    // The pulley driven by the hamster
    auto pulley1 = std::make_shared<Pulley>(10);
    pulley1->SetImage(mImagesDir + L"/pulley3.png");
    pulley1->SetPosition(hamsterShaft.x,hamsterShaft.y);
    machine->AddComponent(pulley1);

    hamster->GetSource()->AddSink(pulley1);

    auto pulley2 = std::make_shared<Pulley>(17);
    pulley2->SetImage(mImagesDir + L"/pulley3.png");
    pulley2->SetPosition(conveyorShaft.x,conveyorShaft.y);
    machine->AddComponent(pulley2);

    pulley1->Drive(pulley2);
    pulley2->GetSource()->AddSink(conveyor);


    auto hamster2 = std::make_shared<Hamster>(mImagesDir);
    hamster2->SetPosition(-260, 0);
    hamster2->SetSpeed(-2);
    hamster2->TurnDemon(mImagesDir);
    hamster2->SetInitiallyRunning(true);      // Initially running
    machine->AddComponent(hamster2);
    auto hamsterShaft1 = hamster2->GetShaftPosition();

    auto conveyor1 = std::make_shared<Conveyor>(mImagesDir);
    conveyor1->SetPosition(-100,50);
    machine->AddComponent(conveyor1);
    auto conveyorShaft1 = conveyor1->GetShaftPosition();

    // The pulley driven by the hamster
    auto pulley3 = std::make_shared<Pulley>(10);
    pulley3->SetImage(mImagesDir + L"/pulley3.png");
    pulley3->SetPosition(hamsterShaft1.x,hamsterShaft1.y);
    machine->AddComponent(pulley3);

    hamster2->GetSource()->AddSink(pulley3);

    auto pulley4 = std::make_shared<Pulley>(15);
    pulley4->SetImage(mImagesDir + L"/pulley3.png");
    pulley4->SetPosition(conveyorShaft1.x,conveyorShaft1.y);
    machine->AddComponent(pulley4);

    pulley3->Drive(pulley4);
    pulley4->GetSource()->AddSink(conveyor1);

    auto conveyor2 = std::make_shared<Conveyor>(mImagesDir);
    conveyor2->SetPosition(-230,70);
    conveyor2->SetInitialRotation(-0.05);
    machine->AddComponent(conveyor2);
    auto conveyorShaft2 = conveyor2->GetShaftPosition();

    auto pulley5 = std::make_shared<Pulley>(20);
    pulley5->SetImage(mImagesDir + L"/pulley3.png");
    pulley5->SetPosition(conveyorShaft2.x,conveyorShaft2.y);
    machine->AddComponent(pulley5);

    pulley3->Drive(pulley5);
    pulley5->GetSource()->AddSink(conveyor2);


    auto conveyor3 = std::make_shared<Conveyor>(mImagesDir);
    conveyor3->SetPosition(-310,160);
    conveyor3->SetInitialRotation(-0.2);
    machine->AddComponent(conveyor3);
    auto conveyorShaft3 = conveyor3->GetShaftPosition();

    auto pulley6 = std::make_shared<Pulley>(10);
    pulley6->SetImage(mImagesDir + L"/pulley3.png");
    pulley6->SetPosition(conveyorShaft3.x,conveyorShaft3.y);
    machine->AddComponent(pulley6);

    pulley3->Drive(pulley6);
    pulley6->GetSource()->AddSink(conveyor3);

    // pulley with hand
    auto pulley7 = std::make_shared<Pulley>(5);
    pulley7->SetImage(mImagesDir + L"/pulley3.png");
    pulley7->SetPosition(-345,260);
    machine->AddComponent(pulley7);

    auto arm = std::make_shared<Body>();
    arm->SetInitialPosition(-345,260);
    arm->AddPoint(-7, 10);
    arm->AddPoint(7, 10);
    arm->AddPoint(7, -60);
    arm->AddPoint(-7, -60);
    arm->SetImage(mImagesDir + L"/lightsaber_red.png");
    arm->SetKinematic();
    machine->AddComponent(arm);

    pulley7->GetSource()->AddSink(arm);
    pulley3->Drive(pulley7);

    auto hamster3 = std::make_shared<Hamster>(mImagesDir);
    hamster3->SetPosition(150, 185);
    hamster3->TurnDemon(mImagesDir);
    hamster3->SetSpeed(1);
    machine->AddComponent(hamster3);
    auto hamster1shaft = hamster3->GetShaftPosition();

    auto arm1 = std::make_shared<Body>();
    arm1->SetInitialPosition(hamster1shaft.x,hamster1shaft.y);
    arm1->AddPoint(-7, 10);
    arm1->AddPoint(7, 10);
    arm1->AddPoint(7, -60);
    arm1->AddPoint(-7, -60);
    arm1->SetImage(mImagesDir + L"/lightsaber_red.png");
    arm1->SetKinematic();
    machine->AddComponent(arm1);

    hamster3->GetSource()->AddSink(arm1);


    auto conveyor4 = std::make_shared<Conveyor>(mImagesDir);
    conveyor4->SetPosition(160,50);
    machine->AddComponent(conveyor4);
    auto conveyorShaft4 = conveyor4->GetShaftPosition();

    auto pulley8 = std::make_shared<Pulley>(30);
    pulley8->SetImage(mImagesDir + L"/pulley3.png");
    pulley8->SetPosition(conveyorShaft4.x,conveyorShaft4.y);
    machine->AddComponent(pulley8);

    pulley3->Drive(pulley8);



    //
    // We add the baskedball goal last, so all basketballs
    // will draw behind it.
    //
    BasketballGoal(machine);

    return machine;
}



/**
 * Generate the top beam and its basketball
 *
 * The top beam and ramp and basketball that
 * rolls right and goes through the hoop.
 * @param machine Beam to generate
 */
void MachineFactory2::TopBeamAndRamp(std::shared_ptr<Machine> machine)
{
    const double BeamX = -25;
    auto beam1 = std::make_shared<Body>();
    beam1->BottomCenteredRectangle(400, 20);
    beam1->SetImage(mImagesDir + L"/beam.png");
    beam1->SetInitialPosition(BeamX, 300);
    machine->AddComponent(beam1);

    auto wedge1 = std::make_shared<Body>();
    wedge1->AddPoint(-25, 0);
    wedge1->AddPoint(25, 0);
    wedge1->AddPoint(25, 4.5);
    wedge1->AddPoint(-25, 25);
    wedge1->SetImage(mImagesDir + L"/wedge.png");
    wedge1->SetInitialPosition(BeamX-175, 320);
    machine->AddComponent(wedge1);

    // Basketball 1
    auto basketball1 = std::make_shared<Body>();
    basketball1->Circle(12);
    basketball1->SetImage(mImagesDir + L"/basketball1.png");
    basketball1->SetInitialPosition(BeamX-186, 353);
    basketball1->SetDynamic();
    basketball1->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball1);
}

/**
 * Create a stack of 9 dominos.
 * @param machine Machine to add to
 * @param position The position to draw the domino stack at
 */
void MachineFactory2::DominoStack(std::shared_ptr<Machine> machine, wxPoint2DDouble position)
{
    Domino(machine, position + wxPoint2DDouble(30, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(10, DominoHeight/2), 0, DominoColor::Blue);
    Domino(machine, position + wxPoint2DDouble(20, DominoHeight + DominoWidth/2), 0.25, DominoColor::Green);

    Domino(machine, position + wxPoint2DDouble(-10, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-30, DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(-20, DominoHeight + DominoWidth/2), 0.25, DominoColor::Black);

    const int DominoLevel2 = DominoHeight + DominoWidth;

    Domino(machine, position + wxPoint2DDouble(10, DominoLevel2 + DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-10, DominoLevel2 + DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(0, DominoLevel2 + DominoHeight + DominoWidth/2), 0.25, DominoColor::Black);
}

/**
 * This is the second beam from the top and the spinning arm that hits the ball
 * @param machine Machine to add to
 */
void MachineFactory2::BeamAndSpinningArm(std::shared_ptr<Machine> machine)
{
    const double Beam2X = -25;
    auto beam2 = std::make_shared<Body>();
    beam2->BottomCenteredRectangle(400, 20);
    beam2->SetImage(mImagesDir + L"/beam.png");
    beam2->SetInitialPosition(Beam2X, 240);
    machine->AddComponent(beam2);

    // Basketball 2
    auto basketball2 = std::make_shared<Body>();
    basketball2->Circle(12);
    basketball2->SetImage(mImagesDir + L"/basketball2.png");
    basketball2->SetInitialPosition(Beam2X - 170, 240 + 12 + 20);
    basketball2->SetDynamic();
    basketball2->SetPhysics(1, 0.5, 0.75);
    machine->AddComponent(basketball2);

    //
    // The hamster motor for the second-beam
    //
    auto hamster = std::make_shared<Hamster>(mImagesDir);
    hamster->SetPosition(-220, 185);
    hamster->SetInitiallyRunning(true);      // Initially running
    hamster->SetSpeed(0.60);
    machine->AddComponent(hamster);
    auto hamster1shaft = hamster->GetShaftPosition();

    auto arm = std::make_shared<Body>();
    arm->SetInitialPosition(hamster1shaft.x,hamster1shaft.y);
    arm->AddPoint(-7, 10);
    arm->AddPoint(7, 10);
    arm->AddPoint(7, -60);
    arm->AddPoint(-7, -60);
    arm->SetImage(mImagesDir + L"/arm.png");
    arm->SetKinematic();
    machine->AddComponent(arm);

    hamster->GetSource()->AddSink(arm);
}

/**
 * Add the basketball goal to the machine
 * @param machine Machine to add to
 */
void MachineFactory2::BasketballGoal(std::shared_ptr<Machine> machine)
{
    auto goal = std::make_shared<Goal>(mImagesDir);
    goal->SetPosition(270, 0);
    machine->AddComponent(goal);
}

/**
 * Create the beam that has 10 dominoes on it.
 * @param machine Machine to add bem to
 * @param position Location to place the beam.
 */
void MachineFactory2::DominoesOnBeam(std::shared_ptr<Machine> machine, wxPoint2DDouble position)
{
    // The beam the dominoes sit on
    auto beam = std::make_shared<Body>();
    beam->BottomCenteredRectangle(150, 15);
    beam->SetImage(mImagesDir + L"/beam.png");
    beam->SetInitialPosition(position.m_x,position.m_y);
    machine->AddComponent(beam);

    for(int d=0; d<10; d++)
    {
        // Where to put this domino
        auto dominos = position + wxPoint2DDouble(-70 + d * 15, 27);

        Domino(machine, dominos, 0, DominoColor::Green);
    }
}


/**
 * Create a Domino and add it to the machine.
 *
 * This has been created to make it easier to create
 * a lot of dominos
 *
 * @param machine Machine to add the domino to
 * @param position Position to place the center of the domino
 * @param rotation Rotation in turns
 * @param color Color code
 * @return Returns the created domino body
 */
std::shared_ptr<Body>  MachineFactory2::Domino(std::shared_ptr<Machine> machine, wxPoint2DDouble position, double rotation, DominoColor color)
{
    auto x = position.m_x;
    auto y = position.m_y;

    auto domino = std::make_shared<Body>();
    domino->Rectangle(-DominoWidth/2, -DominoHeight/2, DominoWidth, DominoHeight);
    switch(color)
    {
        case DominoColor::Black:
            domino->SetImage(mImagesDir + L"/domino-black.png");
            break;

        case DominoColor::Red:
            domino->SetImage(mImagesDir + L"/domino-red.png");
            break;

        case DominoColor::Green:
            domino->SetImage(mImagesDir + L"/domino-green.png");
            break;

        case DominoColor::Blue:
            domino->SetImage(mImagesDir + L"/domino-blue.png");
            break;
    }

    domino->SetInitialPosition(x, y);
    domino->SetInitialRotation(rotation);
    domino->SetDynamic();
    machine->AddComponent(domino);

    return domino;
}

/**
 * Add a basketball to the machine
 * @param machine machine we are adding to
 * @param x x-coordinate of ball
 * @param y y-coordinate of balls
 */
void MachineFactory2::AddBasketball(std::shared_ptr<Machine> machine, double x, double y)
{
    auto basketball = std::make_shared<Body>();
    basketball->Circle(12);
    basketball->SetImage(mImagesDir + L"/deathStar.png");
    basketball->SetInitialPosition(x, y);
    basketball->SetDynamic();
    basketball->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball);
}
