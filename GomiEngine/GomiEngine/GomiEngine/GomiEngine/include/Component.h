#pragma once
class Window;

/**
 * @enum ComponentCategory
 * @brief Define los tipos de componentes disponibles en el sistema.
 */
enum ComponentCategory {
    UNDEFINED = 0,
    TRANSFORM = 1,
    SPRITE = 2,
    RENDERER = 3,
    PHYSICS = 4,
    AUDIO_SOURCE = 5,
    SHAPE = 6,
    TEXTURE = 7
};

/**
 * @class GameComponent
 * @brief Clase abstracta base para todos los componentes de un juego.
 * Proporciona una interfaz para actualizar y renderizar componentes,
 * y permite identificar su categoría.
 */
class GameComponent {
public:
    GameComponent() = default; ///< Constructor por defecto.

    /**
     * @brief Constructor que inicializa el componente con una categoría específica.
     * @param category Tipo del componente.
     */
    explicit GameComponent(ComponentCategory category) : m_category(category) {}

    virtual ~GameComponent() = default; ///< Destructor virtual para limpieza segura.

    /**
     * @brief Método abstracto para actualizar el estado del componente.
     * @param deltaTime Tiempo transcurrido desde la última actualización.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Método abstracto para renderizar el componente en la pantalla.
     * @param window Ventana o contexto gráfico donde se dibujará el componente.
     */
    virtual void render(Window& window) = 0;

    /**
     * @brief Devuelve la categoría del componente.
     * @return Categoría del componente.
     */
    ComponentCategory getCategory() const { return m_category; }

protected:
    ComponentCategory m_category = UNDEFINED; ///< Categoría del componente.
};
