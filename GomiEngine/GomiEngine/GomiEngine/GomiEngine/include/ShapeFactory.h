#pragma once

#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

class ShapeFactory : public Component {
public:
    /**
     * @brief Constructor por defecto.
     * Inicializa el ShapeFactory sin una forma específica.
     */
    ShapeFactory()
        : m_shape(nullptr),
        m_ShapeType(ShapeType::EMPTY),
        Component(ComponentType::SHAPE) {}

    /**
     * @brief Destructor por defecto.
     * Libera recursos asociados con la forma gráfica si corresponde.
     */
    virtual ~ShapeFactory() {
        delete m_shape;
    }

    /**
     * @brief Crea una nueva forma basada en el tipo especificado.
     * @param shapeType Tipo de forma a crear.
     * @return Puntero a la forma gráfica creada.
     */
    sf::Shape* createShape(ShapeType shapeType);

    /**
     * @brief Actualiza el componente de malla.
     * @param deltaTime Tiempo transcurrido desde la última actualización.
     */
    void update(float deltaTime) override {}

    /**
     * @brief Renderiza el componente de malla.
     * @param window Ventana donde se renderiza la forma.
     */
    void render(Window& window) override;

    /**
     * @brief Establece la posición de la forma.
     * @param x Coordenada X de la posición.
     * @param y Coordenada Y de la posición.
     */
    void setPosition(float x, float y);

    /**
     * @brief Establece la posición de la forma.
     * @param position Posición como un vector 2D.
     */
    void setPosition(const Vector2& position);

    /**
     * @brief Establece el color de relleno de la forma.
     * @param color Color a aplicar como relleno.
     */
    void setFillColor(const sf::Color& color);

    /**
     * @brief Establece la rotación de la forma.
     * @param angle Ángulo de rotación en grados.
     */
    void setRotation(float angle);

    /**
     * @brief Establece la escala de la forma.
     * @param scale Escala como un vector 2D.
     */
    void setScale(const Vector2& scale);

    /**
     * @brief Obtiene un puntero a la forma actual.
     * @return Puntero a la forma gráfica creada.
     */
    sf::Shape* getShape() {
        return m_shape;
    }

private:
    sf::Shape* m_shape;       // Puntero a la forma gráfica actual.
    ShapeType m_ShapeType;    // Tipo de forma que se está gestionando.
};
