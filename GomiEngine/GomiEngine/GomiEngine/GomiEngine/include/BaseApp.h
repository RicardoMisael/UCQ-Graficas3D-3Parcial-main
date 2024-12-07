#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "ShapeFactory.h"
#include "Actor.h"
#include "GUI.h"
#include "Services/NotificationSystem.h"
#include "Services/ResourceManager.h"

/**
 * @class Application
 * @brief Clase base que maneja el ciclo de vida de la aplicación.
 */
class Application {
public:
    Application() = default; ///< Constructor por defecto.
    ~Application(); ///< Destructor para limpieza de recursos.

    /**
     * @brief Ejecuta la aplicación.
     * Este método inicia el bucle principal de la aplicación.
     * @return Código de retorno para el sistema operativo.
     */
    int execute();

    /**
     * @brief Inicializa los recursos y sistemas de la aplicación.
     * @return Verdadero si la inicialización fue exitosa.
     */
    bool setup();

    /**
     * @brief Realiza actualizaciones por fotograma.
     * Este método gestiona la lógica del programa que debe ejecutarse
     * en cada iteración del bucle principal.
     */
    void processUpdates();

    /**
     * @brief Renderiza todos los elementos en pantalla.
     * Este método dibuja los objetos en la ventana gráfica.
     */
    void draw();

    /**
     * @brief Libera los recursos asignados durante la ejecución.
     */
    void releaseResources();

    /**
     * @brief Gestiona el movimiento de un actor en función del tiempo.
     * @param elapsedTime Tiempo transcurrido desde el último fotograma.
     * @param actor Puntero compartido al actor que se desea mover.
     */
    void manageActorMovement(float elapsedTime, EngineUtilities::TSharedPointer<Actor> actor);

private:
    sf::Clock m_timer; ///< Reloj para medir el tiempo entre fotogramas.
    sf::Time m_elapsedTime; ///< Tiempo transcurrido entre fotogramas.

    Window* m_mainWindow = nullptr; ///< Puntero a la ventana principal.

    // Actores en la escena
    EngineUtilities::TSharedPointer<Actor> m_triangleActor;
    EngineUtilities::TSharedPointer<Actor> m_circleActor;
    EngineUtilities::TSharedPointer<Actor> m_pathActor;

    std::vector<EngineUtilities::TSharedPointer<Actor>> m_sceneActors; ///< Lista de actores en escena.

    // Puntos para definir trayectorias
    Vector2 m_pathPoints[9];
    int m_activePoint = 0; ///< Punto actual en la trayectoria.
    int m_activeActor = 0; ///< Actor seleccionado actualmente.

    // Texturas utilizadas en la aplicación
    sf::Texture m_backgroundTexture;
    sf::Texture m_characterTexture;

    GUI m_userInterface; ///< Interfaz gráfica de usuario.
};
