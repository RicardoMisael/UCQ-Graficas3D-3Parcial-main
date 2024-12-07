#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

class Transform : public Component {
public:
    /**
     * @brief Constructor por defecto.
     * Inicializa la posición, rotación y escala a valores predeterminados.
     */
    Transform()
        : position(0.0f, 0.0f),
        rotation(0.0f, 0.0f),
        scale(1.0f, 1.0f),
        Component(ComponentType::TRANSFORM) {}

    virtual ~Transform() = default;

    /**
     * @brief Actualiza el componente de transformación.
     * @param deltaTime El tiempo transcurrido desde la última actualización.
     */
    void update(float deltaTime) override {}

    /**
     * @brief Renderiza el componente de transformación (actualmente no implementado).
     * @param window La ventana en la que se renderizará el componente.
     */
    void render(Window& window) override {}

    // Métodos para establecer las propiedades de la transformación.
    void setPosition(const Vector2& _position) { position = _position; }
    void setRotation(const Vector2& _rotation) { rotation = _rotation; }
    void setScale(const Vector2& _scale) { scale = _scale; }

    // Métodos para obtener las propiedades de la transformación.
    Vector2 getPosition() const { return position; }
    Vector2 getRotation() const { return rotation; }
    Vector2 getScale() const { return scale; }

    // Métodos para acceder directamente a los datos de la transformación.
    float* getPosData() { return &position.x; }
    float* getRotData() { return &rotation.x; }
    float* getSclData() { return &scale.x; }

    /**
     * @brief Establece posición, rotación y escala de un solo golpe.
     * @param pos Nueva posición.
     * @param rot Nueva rotación.
     * @param scl Nueva escala.
     */
    void setTransform(const Vector2& pos, const Vector2& rot, const Vector2& scl) {
        position = pos;
        rotation = rot;
        scale = scl;
    }

    /**
     * @brief Mueve el objeto hacia una posición objetivo con una velocidad específica.
     * @param targetPosition La posición objetivo hacia la cual se mueve el objeto.
     * @param speed La velocidad de movimiento.
     * @param deltaTime El tiempo transcurrido desde la última actualización.
     * @param range La distancia mínima antes de que el movimiento hacia el objetivo se detenga.
     */
    void Seek(const Vector2& targetPosition, float speed, float deltaTime, float range) {
        Vector2 direction = targetPosition - position;
        float length = direction.length();  // Suponiendo que `Vector2` tenga un método `length()`

        if (length > range) {
            direction.normalize();  // Normaliza el vector
            position += direction * speed * deltaTime;
        }
    }

    // Libera los recursos asociados al componente (no implementado).
    void destroy() {}

private:
    Vector2 position; // Posición del objeto
    Vector2 rotation; // Rotación del objeto
    Vector2 scale;    // Escala del objeto
};
