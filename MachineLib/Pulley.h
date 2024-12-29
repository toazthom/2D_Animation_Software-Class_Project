/**
 * @file Pulley.h
 * @author Thomas Toaz
 *
 * Class for pulley objects within machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

#include "Component.h"
#include "IRotationSink.h"
#include "Polygon.h"
#include "RotationSource.h"

/**
 * Class for pulley objects within machine
 */
class Pulley : public Component, public IRotationSink
{
private:
    /// Wheel polygon for pulley
    cse335::Polygon mPolygon;

    /// Radius of the pulley
    double mRadius;

    /// Rotation source for this component
    RotationSource mSource;

    /// Rotation of the pulley wheel
    double mRotation = 0;

    /// Pulleys this pulley is connected to
    std::vector<std::shared_ptr<Pulley>> mConnections;

    /// Pulley rocking amount for drawing pulley connections
    double mRocking = 2.0;

    /// Boolean to determine if rocking is increasing or decreasing
    bool mIncrement = true;

    /// pointer to pulley driving this pulley
    Pulley * mDriver = nullptr;

    /// previous rotation amount of the pulley
    double mPreviousRotion = 0;

    /// Position of the poly polygon
    wxPoint mPulleyPos;

public:
    Pulley(double radius);

    /// Copy constructor (disabled)
    Pulley(const Pulley &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Pulley &) = delete;

    void Drive(std::shared_ptr<Pulley> pulley);

    void Update(double elapsed) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Rotate(double rotation, double speed) override;
    void SetPosition(double x, double y) override;

    /**
     * Set the image of the body
     * @param fileName file of the image for the body
     */
    void SetImage(std::wstring fileName) {mPolygon.SetImage(fileName);}
    void InstallPhysics(std::shared_ptr<b2World> world) override;

    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }

    /**
     * Get the radius of the pulley
     * @return the radius of the bulley
     */
    double GetRadius() const {return mRadius;}

    void SetDriver(Pulley *pulley);

    /**
     * Get the position of the pulley
     * @return wxPoint of the pulley position
     */
    wxPoint GetPosition() const {return mPulleyPos;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
