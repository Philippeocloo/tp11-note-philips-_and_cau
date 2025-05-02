#include "Target.h"

Target::Target() : m_shape(Shape::Cross), m_color(Color::Red) {} // valeurs par défaut

Target::Target(Shape i_shape, Color i_color)
    : m_shape(i_shape), m_color(i_color) {}


// Getters 
Shape Target::getShape() const {
    return m_shape;
}

Color Target::getColor() const {
    return m_color;
}


// Setters
void Target::setShape(Shape i_shape) {
    m_shape = i_shape;
}

void Target::setColor(Color i_color) {
    m_color = i_color;
}
