/**
 * @file Component.cpp
 * @author Thomas Toaz
 */

#include "pch.h"
#include "Component.h"
#include "Machine.h"

/**
 * Set the machine using this component
 * @param machine Machine using this component
 */
void Component::SetMachine(Machine *machine)
{
    mMachine = machine;
}
