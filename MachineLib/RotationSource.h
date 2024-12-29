/**
 * @file RotationSource.h
 * @author Thomas Toaz
 *
 * Rotational source class for machine objects that can transfer rotation to other objects
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H

class IRotationSink;

/**
 * Rotational source class for machine objects that can transfer rotation to other objects
 */
class RotationSource
{
private:
    /// Rotation of the source
    double mRotation;

    /// Speed of rotation
    double mSpeed;

    /// Rotational Sinks attached to this source
    std::vector<std::shared_ptr<IRotationSink>> mSinks;


public:
    ///Constructor
    RotationSource() {};

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    void AddSink(std::shared_ptr<IRotationSink>  sink);
    void UpdateSinks();

    void SetRotation(double rotation, double speed);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
