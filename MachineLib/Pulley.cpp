/**
 * @file Pulley.cpp
 * @author Thomas Toaz
 */


/// lowest beizer curve amount
const double BeltRockMin = 2.0;

/// largest beizer curve amount
const double BeltRockMax = 2.05;

/// Beizer incrementation amount
const double BeltRockIncrement = 0.015;

/// Beizer decrementation amount
const double BeltRockDecrement = 0.02;

#include "pch.h"
#include "Pulley.h"
#include <cmath>

/**
 * Pulley constructor
 * @param radius radius of the pulley
 */
Pulley::Pulley(double radius)
{
    mRadius = radius;

    mPolygon.CenteredSquare(mRadius * 2);
}

/**
 * Update the pulley system
 * @param elapsed time since last update
 */
void Pulley::Update(double elapsed)
{
}

/**
 * Draw our polygons for the pulley
 * @param graphics The graphics context to draw on
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw connection lines to other pulleys connected to this pulley
    for(auto pulley : mConnections)
    {
        // Calculations for line lengths/locations between pulleys
        double magnitude = sqrt(pow(mPulleyPos.x-pulley->GetPosition().x,2) + pow(mPulleyPos.y-pulley->GetPosition().y,2));

        double alphaX1 = mRadius*(mPulleyPos.x-pulley->GetPosition().x)/(magnitude);
        double alphaY1 = mRadius*(mPulleyPos.y-pulley->GetPosition().y)/(magnitude);

        double alphaX2 = pulley->GetRadius()*(mPulleyPos.x-pulley->GetPosition().x)/(magnitude);
        double alphaY2 = pulley->GetRadius()*(mPulleyPos.y-pulley->GetPosition().y)/(magnitude);

        if(mRotation !=0)
        {
            // Create a wxGraphicsPath
            wxGraphicsPath path = graphics->CreatePath();

            // Move to the first starting point
            path.MoveToPoint(mPulleyPos.x - alphaY1, mPulleyPos.y + alphaX1);

            // Add first curve
            path.AddCurveToPoint(
                (mPulleyPos.x - alphaY1 + pulley->GetPosition().x - alphaY2) / mRocking,
                (mPulleyPos.y + alphaX1 + pulley->GetPosition().y + alphaX2) / mRocking,
                (pulley->GetPosition().x - alphaY2 + mPulleyPos.x + alphaY1) / mRocking,
                (pulley->GetPosition().y + alphaX2 + mPulleyPos.y - alphaX1) / mRocking,
                pulley->GetPosition().x - alphaY2, pulley->GetPosition().y + alphaX2
            );

            // Move to the second starting point
            path.MoveToPoint(mPulleyPos.x + alphaY1, mPulleyPos.y - alphaX1);

            // Add second curve
            path.AddCurveToPoint(
                (mPulleyPos.x + alphaY1 + pulley->GetPosition().x + alphaY2) / mRocking,
                (mPulleyPos.y - alphaX1 + pulley->GetPosition().y - alphaX2) / mRocking,
                (pulley->GetPosition().x + alphaY2 + mPulleyPos.x + alphaY1) / mRocking,
                (pulley->GetPosition().y - alphaX2 + mPulleyPos.y - alphaX1) / mRocking,
                pulley->GetPosition().x + alphaY2, pulley->GetPosition().y - alphaX2
            );

            // Set the pen and draw the path
            graphics->SetPen(wxPen(wxColor(0, 0, 0), 2));
            graphics->DrawPath(path);


            if(mRocking <BeltRockMax && mIncrement)
            {
                mRocking += BeltRockIncrement;
            }
            else
            {
                mIncrement = false;
            }


            if(mRocking >BeltRockMin && !mIncrement)
            {
                mRocking -= BeltRockDecrement;
            }
            else
            {
                mIncrement = true;
            }
        }
        else
        {
            graphics->SetPen(wxPen(wxColor(0, 0, 0), 2));
            graphics->StrokeLine(mPulleyPos.x - alphaY1, mPulleyPos.y + alphaX1, pulley->GetPosition().x - alphaY2, pulley->GetPosition().y + alphaX2);
            graphics->StrokeLine(mPulleyPos.x + alphaY1, mPulleyPos.y - alphaX1, pulley->GetPosition().x + alphaY2, pulley->GetPosition().y - alphaX2);
        }

    }

    // Draw the pulley

    mPolygon.DrawPolygon(graphics,mPulleyPos.x,mPulleyPos.y,mRotation);

}

/**
 * Rotate the body for when in contact with a rotational source
 * @param rotation rotation of body
 * @param speed speed of rotation
 */
void Pulley::Rotate(double rotation, double speed)
{
    if(mDriver == nullptr)
    {
        mRotation = rotation;
    }
    else
    {
        double rotationScaled = rotation * mDriver->GetRadius()/mRadius;
        double rotationalIncrement = (rotationScaled)-mPreviousRotion;
        if(abs(rotationScaled)<abs(mPreviousRotion))
        {
            mRotation += (rotationScaled);
        }
        else
        {
            mRotation += (rotationScaled)-mPreviousRotion;
        }

        mPreviousRotion = rotationScaled;


    }

    mSource.SetRotation(rotation, speed);
    mSource.UpdateSinks();
}

/**
 * Connect a pulley to this pulley
 * @param pulley pulley being connect to this pulley
 */
void Pulley::Drive(std::shared_ptr<Pulley> pulley)
{
    mConnections.push_back(pulley);
    pulley->SetDriver(this);
    mSource.AddSink(pulley);
}

/**
 * Sets the initial location of the component in the machine
 * @param x The x-initial position of the component piece
 * @param y The y-initial position of the component piece
 */
void Pulley::SetPosition(double x, double y)
{
    mPulleyPos = wxPoint(x,y);
}

/**
 * Install the body into the physics world
 * @param world
 */
void Pulley::InstallPhysics(std::shared_ptr<b2World> world)
{
    mRotation = 0;
}

/**
 * Set the pulley that is a rotational source for this pulley
 * @param pulley pulley that is driving/moving this pulley
 */
void Pulley::SetDriver(Pulley *pulley)
{
    mDriver = pulley;
}
