#include "Target.h"

/**
 * @file Target.cpp
 * @brief Implémentation des méthodes de la classe Target, représentant une cible du jeu.
 */

 /**
 * @brief Constructeur par défaut de Target
 * Initialise une cible de forme CROSS et de couleur RED.
 */
Target::Target() : m_shape(Shape::CROSS), m_color(RColor::R_RED) {} // valeurs par défaut


/**
 * @brief Constructeur paramétré de Target
 * @param i_shape Forme de la cible
 * @param i_color Couleur de la cible
 */
Target::Target(Shape i_shape, RColor i_color): m_shape(i_shape), m_color(i_color) {}

// Getters 
/**
 * @brief Retourne la forme de la cible
 * @return Shape Forme de la cible (CROSS, CIRCLE, etc.)
 */
Shape Target::getShape() const {
    return m_shape;
}

/**
 * @brief Retourne la couleur de la cible
 * @return RColor Couleur associée à la cible
 */
RColor Target::getColor() const {
    return m_color;
}


// Setters
/**
 * @brief Modifie la forme de la cible
 * @param i_shape Nouvelle forme à attribuer à la cible
 */
void Target::setShape(Shape i_shape) {
    m_shape = i_shape;
}

/**
 * @brief Modifie la couleur de la cible
 * @param i_color Nouvelle couleur à attribuer à la cible
 */
void Target::setColor(RColor i_color) {
    m_color = i_color;
}

//Surchage
/**
 * @brief Opérateur d'égalité
 * @param other Cible à comparer
 * @return true si la forme et la couleur sont identiques, false sinon
 */
bool Target::operator==(const Target& other) const {
    return m_shape == other.m_shape && m_color == other.m_color;
}
