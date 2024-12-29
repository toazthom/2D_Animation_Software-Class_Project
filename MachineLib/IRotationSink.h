/**
 * @file IRotationSink.h
 * @author Thomas Toaz
 *
 * Rotational sink interface class for linking to rotational sources
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H

/**
 * Rotational sink interface class for linking to rotational sources
 */
class IRotationSink
{
private:

public:
    /**
     * Transfer the rotation/speed of something else into this sink
     * @param rotation
     * @param speed
     */
    virtual void Rotate(double rotation, double speed) = 0;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
