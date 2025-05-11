#pragma once

#include "Scene.h"

#include <raylib.h>
#include <string>


class MenuScene : public Scene {
private:
    std::string m_playerString;

public:
    virtual void Update(float deltaTime);
    virtual void Render();
};