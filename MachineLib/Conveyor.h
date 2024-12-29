/**
 * @file Conveyor.h
 * @author Thomas Toaz
 *
 * Conveyor belt class for machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H

#include "Component.h"
#include "IRotationSink.h"
#include "PhysicsPolygon.h"
#include <b2_world_callbacks.h>


/**
 * Conveyor belt class for machine
 */
class Conveyor : public Component, public IRotationSink, public b2ContactListener
{
private:
    /// Conveyor Physics Polygon
    cse335::PhysicsPolygon mConveyor;

    /// The speed of the conveyor
    double mSpeed = 0;

    /// Rotation of the conveyor
    double mRotation = 0;

public:
    ///Constructor
    Conveyor(std::wstring imagesDir);

    ///Destuctor
    virtual ~Conveyor() {}

    /** Copy constructor disabled */
    Conveyor(const Conveyor &) = delete;

    /** Assignment operator disabled */
    void operator=(const Conveyor &) = delete;

    void BeginContact(b2Contact *contact) override;
    void Update(double elapsed) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetPosition(double x, double y) override;
    void InstallPhysics(std::shared_ptr<b2World> world) override;
    void AddContact(std::shared_ptr<ContactListener> listener) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    void Rotate(double rotation, double speed) override;
    void SetInitialRotation(double rotation);

    /**
     * Get the position of the conveyor belt
     * @return wxPoint of the location of the conveyor belt
     */
    wxPoint GetPosition() {return wxPoint(mConveyor.GetPosition().m_x,mConveyor.GetPosition().m_y);}



    wxPoint GetShaftPosition();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
