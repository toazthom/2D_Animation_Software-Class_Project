/**
 * @file Component.h
 * @author Thomas Toaz
 *
 *
 * Base class for component parts that make up machines
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

#include "Machine.h"

class b2World;


/**
 * Base class for component parts that make up machines
 */
class Component
{
private:
    /// The machine using this component
    Machine *mMachine = nullptr;

public:
    /**
     * Sets the initial location of the component in the machine
     * @param x The x-initial position of the component piece
     * @param y The y-initial position of the component piece
     */
    virtual void SetPosition(double x, double y) {};

    ///Destuctor
    virtual ~Component() {}
    ///Constructor
    Component() {};
    /** Copy constructor disabled */
    Component(const Component &) = delete;
    /** Assignment operator disabled */
    void operator=(const Component &) = delete;


    /**
     * Draw the component
     * @param graphics
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
     * Update the component
     * @param elapsed time since last update
     */
    virtual void Update(double elapsed) {};

    /**
     * Install the object into the physics world of the system
     * @param world physics world you are installing the object into
     */
    virtual void InstallPhysics(std::shared_ptr<b2World> world) = 0;

    void SetMachine(Machine *machine);
    /**
     * Get the machine this component is a part of
     * @return The machine of the component
     */
    Machine * GetMachine() {return mMachine;}

    /**
     * Add a contact listener to the component
     * @param listener contact listener to be conected to component
     */
    virtual void AddContact(std::shared_ptr<ContactListener> listener){}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
