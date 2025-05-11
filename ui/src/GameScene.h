#pragma once

#include <raylib.h>

#include <GameSupervisor.h>

#include "Scene.h"
#include "RobotRenderer.h"

class GameScene : public Scene {
private:
    Camera m_camera;
    RobotRenderer m_robotRenderer;

    Model m_crossModel;
    Model m_triModel;

    GameSupervisor m_supervisor;

    void RenderCell(Cell& currentCell);

public:
    GameScene(std::string players);
    ~GameScene();

    virtual void Update(float deltaTime);
    virtual void Render();

    

};