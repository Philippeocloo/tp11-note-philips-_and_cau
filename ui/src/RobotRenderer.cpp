#include "RobotRenderer.h"

RobotRenderer::RobotRenderer(const std::vector<Robot>* robots)
{
    m_robots = robots;
    robotModel = LoadModel("res/robot.glb");
    m_currentlySelected = nullptr;
}

void RobotRenderer::render()
{
    for (size_t i = 0; i < m_robots->size(); i++)
    {
        Robot current = (*m_robots)[i];
        Cell* currentCell = current.getCell();
        Vector3 cellPosition = (Vector3){ (float)(-currentCell->getX()) + 7.5f, 0.0f, (float)(currentCell->getY()) - 7.5f};

        DrawModel(robotModel, cellPosition, 1.0f, getColorFromRColor(current.getColor()));
    }
    
}
