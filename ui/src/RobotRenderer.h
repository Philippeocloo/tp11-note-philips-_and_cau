#pragma once
#include "Robot.h"
#include "Cell.h"

#include <enums/Direction.h>

#include <vector>

#include <raylib.h>
#include "ColorConverter.h"


struct SelectionInformation {
    const Robot* selectedRobot;
    Direction dir;
};


class RobotRenderer{
private:
    const Robot* m_currentlySelected;
    const std::vector<Robot>* m_robots;
    Model m_robotModel;
    Model m_arrowModel;
    BoundingBox m_robotBoundingBox;

    Camera* m_camera;

    Ray m_ray = { 0 };                    // Picking line ray
    RayCollision m_collision = { 0 };     // Ray collision hit info
public:
    RobotRenderer();
    void setCamera(Camera* camera);
    void setRobots(const std::vector<Robot>* robots);
    SelectionInformation checkSelection();
    void render();
};