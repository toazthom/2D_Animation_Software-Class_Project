/**
 * @file RotationSource.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "RotationSource.h"
#include "IRotationSink.h"

/**
 * Attached a rotational sink to this source
 * @param sink
 */
void RotationSource::AddSink(std::shared_ptr<IRotationSink> sink)
{
    mSinks.push_back(sink);
//    sink->SetRotationSource(this);
}

/// Update all rotational sinks associated with this source
void RotationSource::UpdateSinks()
{
    for(auto sink : mSinks)
    {
        sink->Rotate(mRotation,mSpeed);
    }
}

/**
 * Set the rotation and speed of the source
 * @param rotation rotation of source
 * @param speed rotation of source
 */
void RotationSource::SetRotation(double rotation, double speed)
{
    mRotation = rotation;
    mSpeed = speed;
}
