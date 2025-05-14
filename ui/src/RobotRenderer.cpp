#include "RobotRenderer.h"

#include "VectorHelper.h"

#include <raymath.h>

RobotRenderer::RobotRenderer()
{
    m_robots = nullptr;
    m_robotModel = LoadModel("res/robot.glb");
    m_arrowModel = LoadModel("res/arrow.obj");
    m_currentlySelected = nullptr;
    m_robotBoundingBox = GetModelBoundingBox(m_robotModel);
}

void RobotRenderer::setCamera(Camera* camera) {
    m_camera = camera;
}

void RobotRenderer::setRobots(std::vector<Robot>* robots) 
{
    m_robots = robots;
}

Direction intToDirection(int i) {
    switch (i)
    {
    case 0:
        return Direction::UP;
        break;
    case 1:
        return Direction::DOWN;
        break;
    case 2:
        return Direction::LEFT;
        break;
    case 3:
        return Direction::RIGHT;
        break;
    
    default:
        return Direction::NONE;
        break;
    }
}

bool checkClickOnArrow(Ray r, BoundingBox bb, Vector3 pos)
{
    bb.min = bb.min + pos;
    bb.max = bb.max + pos;

    RayCollision col = GetRayCollisionBox(r, bb);

    return col.hit;
}

SelectionInformation RobotRenderer::checkSelection()
{
    if(m_robots == nullptr) return {nullptr, Direction::NONE};

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        m_ray = GetScreenToWorldRay(GetMousePosition(), *m_camera);

        // Check collision between ray and box
        for (size_t i = 0; i < m_robots->size(); i++)
        {
            Robot* current = &((*m_robots)[i]);
            Cell* currentCell = current->getCell();
            Vector3 cellPosition = (Vector3){ (float)(-currentCell->getX()) + 7.5f, 0.0f, (float)(currentCell->getY()) - 7.5f};

            BoundingBox bb = m_robotBoundingBox;
            bb.min = bb.min + cellPosition;
            bb.max = bb.max + cellPosition;

            m_collision = GetRayCollisionBox(m_ray, bb);
            
            if(m_collision.hit) {
                m_currentlySelected = current;
                return (SelectionInformation){m_currentlySelected, Direction::NONE};
            }

            //If selected check for collisions with arrows
            if(current != m_currentlySelected) {
                continue;
            }

            BoundingBox arrowBB = GetMeshBoundingBox(m_arrowModel.meshes[0]);

            for (size_t direction = 0; direction < 4; direction++)
            {
                Vector3 arrowPosition = cellPosition;
                Model arrow = m_arrowModel;
                BoundingBox rotatedBB;
                switch (direction)
                {
                case 0: //North
                    arrowPosition.z += 1;
                    arrow.transform = MatrixRotateXYZ({0, 180.0f*DEG2RAD, 0});
                    rotatedBB.min = Vector3Transform(arrowBB.min, arrow.transform);
                    rotatedBB.max = Vector3Transform(arrowBB.max, arrow.transform);
                    
                    break;
                case 1: //South
                    arrowPosition.z -= 1;
                    break;
                case 2: //West
                    arrowPosition.x += 1;
                    arrow.transform = MatrixRotateXYZ({0, -90.0f*DEG2RAD, 0});
                    break;
                case 3: //East
                    arrowPosition.x -= 1;
                    arrow.transform = MatrixRotateXYZ({0, 90.0f*DEG2RAD, 0});
                    break;
                default:
                    break;
                }

                if(checkClickOnArrow(m_ray, rotatedBB, arrowPosition)) {
                    return {m_currentlySelected, intToDirection(direction)};
                }
            }
        }
        return {m_currentlySelected, Direction::NONE};
    }
    return {nullptr, Direction::NONE};
}

void RobotRenderer::render()
{
    if(m_robots == nullptr) return;
    for (size_t i = 0; i < m_robots->size(); i++)
    {
        const Robot* current = &(*m_robots)[i];
        Cell* currentCell = current->getCell();
        Vector3 cellPosition = (Vector3){ (float)(-currentCell->getX()) + 7.5f, 0.0f, (float)(currentCell->getY()) - 7.5f};

        DrawModel(m_robotModel, cellPosition, 1.0f, getColorFromRColor(current->getColor()));

        if(m_currentlySelected == current) {
            //Draw arrows
            for (size_t direction = 0; direction < 4; direction++)
            {
                Vector3 arrowPosition = cellPosition;
                Model arrow = m_arrowModel;
                switch (direction)
                {
                case 0: //North
                    arrowPosition.z += 1;
                    arrow.transform = MatrixRotateXYZ({0, 180.0f*DEG2RAD, 0});
                    DrawModel(arrow, arrowPosition, 1.0f, GRAY);
                    break;
                case 1: //South
                    arrowPosition.z -= 1;
                    DrawModel(m_arrowModel, arrowPosition, 1.0f, GRAY);
                    break;
                case 2: //West
                    arrowPosition.x += 1;
                    arrow.transform = MatrixRotateXYZ({0, -90.0f*DEG2RAD, 0});
                    DrawModel(arrow, arrowPosition, 1.0f, GRAY);
                    break;
                case 3: //East
                    arrowPosition.x -= 1;
                    arrow.transform = MatrixRotateXYZ({0, 90.0f*DEG2RAD, 0});
                    DrawModel(arrow, arrowPosition, 1.0f, GRAY);
                    break;
                default:
                    break;
                }
            }
            

        }
    }
    
}
