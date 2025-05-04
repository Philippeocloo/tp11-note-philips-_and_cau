#include <string>

class Joueur {
private:
    std::string lettre;
    int points;
    bool droit_buzzer;
    int x;
    int y;

public:
    Joueur(const std::string& lettre);

    void essai(int x, int y);

    // Guetteurs
    std::string getLettre() const;
    int getPoints() const;
    bool getDroitBuzzer() const;
    int getX() const;
    int getY() const;

    void setPoints(int points);
    void setDroitBuzzer(bool droit);
    void setPosition(int x, int y);
};
