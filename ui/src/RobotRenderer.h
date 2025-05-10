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
    RobotRenderer(const std::vector<Robot>* robot);
    bool checkSelection();
    void render();
};