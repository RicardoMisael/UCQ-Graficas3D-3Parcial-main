#pragma once
#include "Prerequisites.h"
#include "Component.h"

class Window;

/**
 * @class GameEntity
 * @brief Clase base abstracta que representa una entidad dentro del juego.
 * Las entidades pueden contener múltiples componentes para definir su comportamiento.
 */
class GameEntity {
public:
    virtual ~GameEntity() = default; ///< Destructor virtual para limpieza segura.

    /**
     * @brief Método abstracto para actualizar la entidad.
     * @param deltaTime Tiempo transcurrido desde la última actualización.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Método abstracto para renderizar la entidad en pantalla.
     * @param window Contexto gráfico para las operaciones de dibujo.
     */
    virtual void render(Window& window) = 0;

    /**
     * @brief Añade un componente a la entidad.
     * @tparam T Tipo del componente que se desea añadir. Debe derivar de `Component`.
     * @param component Puntero compartido al componente a añadir.
     */
    template <typename T>
    void attachComponent(EngineUtilities::TSharedPointer<T> component) {
        static_assert(std::is_base_of<Component, T>::value, "El tipo T debe derivar de Component");
        m_components.push_back(component.template dynamic_pointer_cast<Component>());
    }

    /**
     * @brief Busca un componente específico en la entidad.
     * @tparam T Tipo del componente a buscar.
     * @return Puntero compartido al componente encontrado, o nullptr si no existe.
     */
    template <typename T>
    EngineUtilities::TSharedPointer<T> fetchComponent() const {
        for (const auto& component : m_components) {
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
            if (specificComponent) {
                return specificComponent;
            }
        }
        return EngineUtilities::TSharedPointer<T>(); // Devuelve nullptr si no se encuentra.
    }

protected:
    bool m_isActive = true; ///< Indica si la entidad está activa.
    int m_id = 0; ///< Identificador único de la entidad.

    std::vector<EngineUtilities::TSharedPointer<Component>> m_components; ///< Lista de componentes adjuntos a la entidad.
};
