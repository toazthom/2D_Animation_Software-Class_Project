/**
 * @file Machine.h
 * @author Thomas Toaz
 *
 * Actual machine made of components
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

class Component;
class b2World;
class ContactListener;

/**
 * Actual machine made of components
 */
class Machine
{
private:
    /// Machine number/which machine this is
    int mNumber;

    /// Component pieces the machine is made of
    std::vector<std::shared_ptr<Component>> mComponents;

    /// The box2d world
    std::shared_ptr<b2World> mWorld;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;

public:
    /// Constructor
    Machine(int number);

    /// Copy constructor (disabled)
    Machine(const Machine &) = delete;

    /// Assignment operator
    void operator=(const Machine &) = delete;

    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics);
    void Update(double elapsed);
    void AddComponent(const std::shared_ptr<Component>& component);

    /**
     * Get Which machine this machine is (its number)
     * @return The number of the machine
     */
    int GetMachine() const {return mNumber;}

    void Reset();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
