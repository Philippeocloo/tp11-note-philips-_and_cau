#include "Target.h"

Target::Target() : m_shape(Shape::CROSS), m_color(RColor::RED) {} // valeurs par défaut

Target::Target(Shape i_shape, RColor i_color): m_shape(i_shape), m_color(i_color) {}

// Getters 
Shape Target::getShape() const {
    return m_shape;
}

RColor Target::getColor() const {
    return m_color;
}


// Setters
void Target::setShape(Shape i_shape) {
    m_shape = i_shape;
}

void Target::setColor(RColor i_color) {
    m_color = i_color;
}

//Surchage
bool Target::operator==(const Target& other) const {
    return m_shape == other.m_shape && m_color == other.m_color;
}
