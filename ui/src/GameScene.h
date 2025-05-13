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
    Board* m_currentBoard = nullptr;

    int m_playerBuzzing = -1;
    std::string m_currentGuess;

    float m_timer = 5.0f;

    void RenderCell(Cell& currentCell);

    //Guessing related stuff
    int getPlayerBuzzing();
    bool PollGuess();

    void RenderCurrentTarget();

public:
    GameScene(std::string players);
    ~GameScene();

    virtual void Update(float deltaTime);
    virtual void Render();

    

};