#include <string>

class Player {
private:
    std::string m_lettre;
    int m_points;
    bool m_buzzer;
    int m_x;
    int m_y;

public:
    Player(const std::string& lettre);

    void tryPlayer(int x, int y);

    // Guetteurs
    std::string getLettre() const;
    int getPoints() const;
    bool getBuzzer() const;
    int getX() const;
    int getY() const;

    void setPoints(int points);
    void setBuzzer(bool droit);
    void setPosition(int x, int y);
};

