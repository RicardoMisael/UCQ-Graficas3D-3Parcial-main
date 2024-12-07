#include "Actor.h"

Actor::Actor(std::string actorName) {
    // Setup Actor Name 
    m_name = actorName;

    // Setup Shape 
    auto shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);

    // Setup Transform
    auto transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);
}

/**
 * @brief Actualiza los componentes del actor.
 * Sincroniza la posición, rotación y escala del objeto `ShapeFactory`
 * con los valores de transformación definidos en `Transform`.
 */
void Actor::update(float deltaTime) {
    auto transform = getComponent<Transform>();
    auto shape = getComponent<ShapeFactory>();

    if (transform && shape) {
        // Actualizar posición
        shape->setPosition(Vector2(transform->getPosition().x, transform->getPosition().y));

        // Actualizar rotación
        shape->setRotation(transform->getRotation().x);

        // Actualizar escala
        shape->setScale(Vector2(transform->getScale().x, transform->getScale().y));
    }
}

/**
 * @brief Renderiza el actor en la ventana proporcionada.
 * Recorre los componentes y dibuja el `ShapeFactory` asociado si está presente.
 */
void Actor::render(Window& window) {
    for (const auto& component : components) {
        if (auto shape = std::dynamic_pointer_cast<ShapeFactory>(component)) {
            window.draw(*shape->getShape());
        }
    }
}

/**
 * @brief Destruye el actor.
 * Método vacío para potencial limpieza de recursos asociados al actor.
 */
void Actor::destroy() {
    // Limpieza de recursos si es necesario
}

// Obtiene el nombre del actor.
std::string Actor::getName() const {
    return m_name;
}

// Agrega el nombre del actor.
void Actor::setName(const std::string& newName) {
    m_name = newName;
}
