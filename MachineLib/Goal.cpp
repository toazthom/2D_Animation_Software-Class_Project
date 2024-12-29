/**
 * @file Goal.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "Goal.h"
#include "ContactListener.h"
#include "b2_contact.h"
#include <sstream>

/// Image to draw for the goal
const std::wstring GoalImage = L"/goal.png";

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 15;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 278, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 299);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble PostPosition = wxPoint2DDouble(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble GoalPosition = wxPoint2DDouble(-12, 165);

/**
 * Goal object constructor
 * @param imagesDir directory for the images goal need to access
 */
Goal::Goal(std::wstring imagesDir)
{
    mPolygon.BottomCenteredRectangle(GoalSize);
    mPolygon.SetImage(imagesDir + GoalImage);

    mPost.BottomCenteredRectangle(PostSize);
    mPost.SetColor(*wxBLUE);

    mGoal.BottomCenteredRectangle(TargetSize);
    mGoal.SetColor(*wxBLUE);
}


/**
 * Draw our polygons.
 * @param graphics The graphics context to draw on
 */
void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.DrawPolygon(graphics,mGoalPos.x,mGoalPos.y,0);

    // Draw the scoreboard background
    graphics->SetBrush(wxBrush(ScoreboardBackgroundColor));
    graphics->SetPen(wxPen(wxColor(0, 0, 0), ScoreboarderLineWidth));
    graphics->DrawRectangle(mGoalPos.x+ScoreboardRectangle.m_x, mGoalPos.y+ScoreboardRectangle.m_y, ScoreboardRectangle.m_width, ScoreboardRectangle.m_height);

    graphics->PushState();
    graphics->Translate(mGoalPos.x + ScoreboardTextLocation.m_x,mGoalPos.y + ScoreboardTextLocation.m_y);
    graphics->Scale(1, -1);

    std::stringstream score;
    if(mScore<10)
    {
        score << 0;
    }
    score << mScore;

    // Set text color and font size
    wxFont font(ScoreboardFontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, wxColor(255, 255, 255));  // White text color
    graphics->DrawText(score.str(), 0, 0);
    graphics->PopState();
}

/**
 * Update body component of machine
 * @param elapsed time elasped since last update
 */
void Goal::Update(double elapsed)
{

}

/**
 * Install the body into the physics world
 * @param world
 */
void Goal::InstallPhysics(std::shared_ptr<b2World> world)
{
    mGoal.InstallPhysics(world);
    mPost.InstallPhysics(world);

    // Set score to 0 for whem we are rewinding/resetting the machine
    mScore = 0;
}

/**
 * Sets the initial location of the component in the machine
 * @param x The x-initial position of the component piece
 * @param y The y-initial position of the component piece
 */
void Goal::SetPosition(double x, double y)
{
    mPost.SetInitialPosition(x+PostPosition.m_x,y +PostPosition.m_y);
    mGoal.SetInitialPosition(x+GoalPosition.m_x,y+GoalPosition.m_y);

    // Store goal polygon position for drawing the regular polygon
    mGoalPos = wxPoint(x,y);
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Goal::BeginContact(b2Contact *contact)
{
    mScore += 2;
}

/**
 * Handle before the solution of a contact with the
 * scoreboard target object. We take this time to
 * turn off the contact, so the ball will pass through.
 * @param contact Contqct object
 * @param oldManifold Manifold object
 */
void Goal::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetEnabled(false);
}

/**
 * Add a contact listener to the componenet
 * @param listener contact listener of the world
 */
void Goal::AddContact(std::shared_ptr<ContactListener> listener)
{
    listener->Add(mGoal.GetBody(), this);
}

