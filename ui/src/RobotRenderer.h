#pragma once
#include "Robot.h"
#include "Cell.h"
#include <vector>

#include <raylib.h>
#include "ColorConverter.h"


class RobotRenderer{
private:
    Robot* m_currentlySelected;
    const std::vector<Robot>* m_robots;
    Model robotModel;
public:
    RobotRenderer();
    void setRobots(const std::vector<Robot>* robots);
    bool checkSelection();
    void render();
};