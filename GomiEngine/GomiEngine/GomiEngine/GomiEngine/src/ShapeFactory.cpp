#include "ShapeBuilder.h"

/**
 * @brief Genera una figura según el tipo solicitado
 * ShapeType se refiere al tipo de figura a crear:
 * (CIRCLE, RECTANGLE, TRIANGLE)
 */
sf::Shape*
ShapeBuilder::createFigure(ShapeType figureType) {
    m_FigureType = figureType;
    switch (figureType) {
    case NONE: {
        return nullptr;
    }
             // Crea un círculo con radio de 10 unidades.
    case CIRCLE: {
        sf::CircleShape* circle = new sf::CircleShape(10.0f);
        m_figure = circle;
        return circle;
    }
               // Crea un rectángulo con dimensiones 100x50.
    case RECTANGLE: {
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(100.0f, 50.0f));
        m_figure = rectangle;
        return rectangle;
    }
                  // Crea un triángulo representado por un círculo con 3 lados y radio de 50.
    case TRIANGLE: {
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);
        m_figure = triangle;
        return triangle;
    }
    default:
        return nullptr;
    }
}

// Establece la posición de la figura usando coordenadas (x, y).
void
ShapeBuilder::setPosition(float x, float y) {
    if (m_figure) {
        m_figure->setPosition(x, y);
    }
}

// Establece la posición de la figura utilizando un objeto de tipo Vector2 (de la librería matemática).
void
ShapeBuilder::setPosition(const Vector2& position) {
    if (m_figure) {
        m_figure->setPosition(position.x, position.y);
    }
}

// Ajusta la rotación de la figura en grados.
void
ShapeBuilder::setRotation(float angle) {
    if (m_figure) {
        m_figure->setRotation(angle);
    }
}

// Ajusta la escala de la figura utilizando un objeto Vector2 (de la librería matemática).
void
ShapeBuilder::setScale(const Vector2& scale) {
    if (m_figure) {
        m_figure->setScale(scale.x, scale.y);
    }
}

// Modifica el color de relleno de la figura.
void
ShapeBuilder::setFillColor(const sf::Color& color) {
    if (m_figure) {
        m_figure->setFillColor(color);
    }
}
