/**
 * @file Goal.h
 * @author Thomas Toaz
 *
 * Basketball Goal.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_GOAL_H

#include "Component.h"
#include <b2_world_callbacks.h>
#include "PhysicsPolygon.h"
#include "Polygon.h"

/**
 * Basketball Goal.
 */
class Goal : public Component, public b2ContactListener
{
private:
    /// The polygon object for the goal image
    cse335::Polygon mPolygon;

    /// Physics polygon for the backboard/post
    cse335::PhysicsPolygon mPost;

    /// Polygon that we are going to hit to
    /// determine the basket has been scored
    cse335::PhysicsPolygon mGoal;

    /// Goal score
    int mScore = 0;

    /// Position of the goal polygon
    wxPoint mGoalPos;


public:
    Goal(std::wstring imagesDir);

    ///Destuctor
    virtual ~Goal() {}
    /** Copy constructor disabled */
    Goal(const Goal &) = delete;
    /** Assignment operator disabled */
    void operator=(const Goal &) = delete;


    void Update(double elapsed) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetPosition(double x, double y) override;

    void InstallPhysics(std::shared_ptr<b2World> world) override;

    void BeginContact(b2Contact *contact) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;


    void AddContact(std::shared_ptr<ContactListener> listener) override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_GOAL_H
