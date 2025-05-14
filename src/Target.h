#pragma once

/**
 * @file Target.h
 * @brief Déclaration de la classe Target représentant une cible du plateau de jeu.
 */


#include "enums/Shape.h"
#include "enums/Color.h"

/**
 * @class Target
 * @brief Classe représentant une cible sur le plateau, définie par une forme et une couleur.
 */
class Target {
    
private:
    Shape m_shape;
    RColor m_color;

public:
/**
     * @brief Constructeur par défaut de Target
     * Initialise une cible avec des valeurs par défaut.
     */
    Target();

    /**
     * @brief Constructeur paramétré de Target
     * @param i_shape Forme de la cible
     * @param i_color Couleur de la cible
     */
    Target(Shape i_shape, RColor i_color);

    /**
     * @brief Destructeur par défaut
     */
    ~Target() = default;

    /**
     * @brief Récupère la forme de la cible
     * @return Shape La forme actuelle de la cible
     */
    Shape getShape() const;

    /**
     * @brief Récupère la couleur de la cible
     * @return RColor La couleur actuelle de la cible
     */
    RColor getColor() const;

    /**
     * @brief Définit la forme de la cible
     * @param i_shape Nouvelle forme à assigner
     */
    void setShape(Shape i_shape);

    /**
     * @brief Définit la couleur de la cible
     * @param i_color Nouvelle couleur à assigner
     */
    void setColor(RColor i_color);

    /**
     * @brief Opérateur d'égalité
     * @param other Cible à comparer
     * @return true si les deux cibles ont la même forme et la même couleur, false sinon
     */
    bool operator==(const Target& other) const;
};
