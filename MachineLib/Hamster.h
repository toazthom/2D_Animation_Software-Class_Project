/**
 * @file Hamster.h
 * @author Thomas Toaz
 * Motor component for motion within the machine
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H

#include "Component.h"
#include "PhysicsPolygon.h"
#include "Polygon.h"
#include <b2_world_callbacks.h>
#include "RotationSource.h"

/**
 * Motor component for motion within the machine
 */
class Hamster : public Component, public b2ContactListener
{
private:
    /// Cage physics polygon of hamster
    cse335::PhysicsPolygon mCage;

    /// Wheel polygon for hamster
    cse335::Polygon mWheel;

    /// Hamster states of animal animation
    std::vector<cse335::Polygon> mHamsters;

    /// Speed of hamster
    double mSpeed = 0.6;

    /// Rotation of hamster wheel
    double mRotation = 0;

    /// The position of the hamster cage
    wxPoint2DDouble mPosition;

    /// Current index of the hamster image being displayed
    int mHamsterIndex = 0;

    /// Rotation source for this component
    RotationSource mSource;

    /// Boolean for whether hamster is running or not
    bool mRunning = false;

    /// Boolean for wheather hamster is running INITIALLY or not
    bool mInitiallyRunning = false;

public:
    Hamster(std::wstring imagesDir);

    ///Destuctor
    virtual ~Hamster() {}

    /** Copy constructor disabled */
    Hamster(const Hamster &) = delete;

    /** Assignment operator disabled */
    void operator=(const Hamster &) = delete;


    void SetSpeed(double speed);
    void BeginContact(b2Contact *contact);

    void Update(double elapsed) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetPosition(double x, double y) override;
    void InstallPhysics(std::shared_ptr<b2World> world)override;
    void AddContact(std::shared_ptr<ContactListener> listener) override;

    void SetInitiallyRunning(bool running);

    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }

    wxPoint GetShaftPosition();

    void TurnDemon(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
