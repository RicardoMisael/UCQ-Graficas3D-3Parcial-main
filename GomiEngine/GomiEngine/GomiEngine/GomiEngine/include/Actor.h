#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"
#include "Transform.h"

/**
 * @class Actor
 * @brief Representa una entidad de juego que puede actualizarse, renderizarse y contener componentes.
 */
class Actor : public Entity {
public:
    Actor() = default; ///< Constructor por defecto.

    /**
     * @brief Constructor que inicializa el actor con un nombre.
     * @param actorName Nombre del actor.
     */
    explicit Actor(const std::string& actorName);

    virtual ~Actor() = default; ///< Destructor virtual para limpieza segura.

    /**
     * @brief Realiza la lógica de actualización del actor.
     * @param deltaTime Tiempo transcurrido desde la última actualización.
     */
    void update(float deltaTime) override;

    /**
     * @brief Renderiza el actor en el contexto gráfico.
     * @param window Ventana o contexto gráfico para renderizado.
     */
    void render(Window& window) override;

    /**
     * @brief Libera los recursos asociados al actor.
     */
    void destroy();

    /**
     * @brief Obtiene el nombre del actor.
     * @return Cadena de texto con el nombre del actor.
     */
    std::string getName() const;

    /**
     * @brief Modifica el nombre del actor.
     * @param newName Nuevo nombre para el actor.
     */
    void setName(const std::string& newName);

    /**
     * @brief Busca un componente específico asociado al actor.
     * @tparam T Tipo del componente que se desea obtener.
     * @return Puntero compartido al componente solicitado o nullptr si no existe.
     */
    template <typename T>
    EngineUtilities::TSharedPointer<T> findComponent();

private:
    std::string m_actorName = "Unnamed Actor"; ///< Nombre del actor.
};

/**
 * @brief Busca un componente específico del actor utilizando su tipo.
 * @tparam T Tipo del componente a buscar.
 * @return Puntero compartido al componente encontrado, o nullptr si no se encuentra.
 */
template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::findComponent() {
    for (const auto& component : components) {
        if (auto specificComponent = component.template dynamic_pointer_cast<T>()) {
            return specificComponent;
        }
    }
    // Devuelve un puntero vacío si el componente no existe.
    return nullptr;
}
