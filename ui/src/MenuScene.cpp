#include "MenuScene.h"
#include "GameScene.h"

#include "main.h"

#include "Consts.h"

void MenuScene::Update(float deltaTime)
{
    //Check button presses
    int key = GetCharPressed();

    //Key pressed is A -> Z (https://en.wikipedia.org/wiki/List_of_Unicode_characters)
    if(key >= 97 && key <= 122 ) {
        int foundIndex = -1;
        for (unsigned int i = 0; i < m_playerString.length(); i++)
        {
            char currentChar = m_playerString[i];

            if(currentChar == key) {
                foundIndex = i;
                break;
            }
        }
        
        if(foundIndex == -1) {
            m_playerString += key;
        } else {
            m_playerString.erase(foundIndex, 1);
        }
        
    }

    //If space, start the game
    if(key == 32) {
        //if no player registered, don't start the game
        if(m_playerString.length() == 0) {
            return;
        }

        //Create the GameScene
        Scene* gameScene = new GameScene(m_playerString);

        //Change to it
        setCurrentScene(gameScene);
    }
}

void MenuScene::Render()
{
    DrawText("Ricochet Robots", 100, 200, 20, BLACK);
    DrawText("Appuyez sur chaque touche associée à un joueur: ", 100, 230, 20, BLACK);
    DrawText(m_playerString.c_str(), 100, 260, 20, BLACK);

    DrawText("Appuyez sur ESPACE pour démarrer", 100, 300, 20, BLACK);
}
