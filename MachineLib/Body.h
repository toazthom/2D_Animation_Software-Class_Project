/**
 * @file Body.h
 * @author Thomas Toaz
 *
 * Basic body/object component of a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H

#include <utility>

#include "Component.h"
#include "PhysicsPolygon.h"
#include "IRotationSink.h"

/**
 * Basic body/object component of a machine
 */
class Body : public Component, public IRotationSink
{
private:
    /// The physics polygon object for the body
    cse335::PhysicsPolygon mPolygon;

public:
    ///Destuctor
    virtual ~Body() {}
    ///Constructor
    Body() {};
    /** Copy constructor disabled */
    Body(const Body &) = delete;
    /** Assignment operator disabled */
    void operator=(const Body &) = delete;

    /**
     * Get a pointer to the polygon this body uses
     * @return Pointer to the polygon object
     */
    cse335::PhysicsPolygon* GetPolygon() {return &mPolygon;}

    void AddPoint(int x, int y);

    /**
     * Set the color for the polygonz
     * @param color New color to set
     */
    void SetColor(wxColour color) {mPolygon.SetColor(color);}

    /**
     * Set the body to be dynamic for physics
     */
    void SetDynamic() {mPolygon.SetDynamic();};

    /**
     * Set the body to be kinematic for physics
     */
    void SetKinematic() {mPolygon.SetKinematic();};

    /**
     * Set the image of the body
     * @param fileName file of the image for the body
     */
    void SetImage(std::wstring fileName) {mPolygon.SetImage(fileName);}

    void Update(double elapsed) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetInitialPosition(double x, double y);
    void Rectangle(double x, double y, double width, double height);
    void Circle(int radius);

    void SetPhysics(double density, double friction, double restitution);
    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void Rotate(double rotation, double speed) override;

    void BottomCenteredRectangle(double x, double y);
    void SetInitialRotation(double rotation);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
