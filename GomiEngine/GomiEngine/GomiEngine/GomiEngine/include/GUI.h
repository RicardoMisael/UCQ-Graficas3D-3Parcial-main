#pragma once
#include "Prerequisites.h"
#include "Actor.h"
#include "Services/NotificationSystem.h"

class Window;

/**
 * @class InterfaceManager
 * @brief Clase responsable de gestionar la interfaz gráfica de usuario (GUI) del sistema.
 * Permite la interacción con elementos visuales y herramientas de depuración.
 */
class InterfaceManager {
public:
    InterfaceManager() = default; ///< Constructor por defecto.
    ~InterfaceManager() = default; ///< Destructor por defecto.

    /**
     * @brief Inicializa los recursos necesarios para la GUI.
     */
    void initialize();

    /**
     * @brief Actualiza los elementos interactivos de la GUI en cada fotograma.
     */
    void refresh();

    /**
     * @brief Dibuja la GUI en pantalla.
     */
    void draw();

    /**
     * @brief Libera los recursos asociados a la GUI.
     */
    void release();

    /**
     * @brief Configura el estilo visual y temático de la interfaz.
     */
    void configureStyle();

    /**
     * @brief Muestra una consola de mensajes categorizados (errores, advertencias, información).
     * @param logMessages Mapa de mensajes clasificados por tipo.
     */
    void displayConsole(const std::map<ConsolErrorType, std::string>& logMessages);

    /**
     * @brief Presenta un menú jerárquico para gestionar los actores de la escena.
     * @param actorList Lista de actores disponibles en la aplicación.
     */
    void displayHierarchy(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actorList);

    /**
     * @brief Proporciona un panel para visualizar y modificar las propiedades del actor seleccionado.
     */
    void displayInspector();

    /**
     * @brief Crea un control de interfaz para manipular valores de tipo `vec2`.
     * @param label Etiqueta del control.
     * @param values Puntero a los valores flotantes a modificar.
     * @param defaultValue Valor inicial al que se puede restablecer.
     * @param columnWidth Ancho de la columna para la etiqueta.
     */
    void vector2Control(const std::string& label,
        float* values,
        float defaultValue = 0.0f,
        float columnWidth = 100.0f);

private:
    EngineUtilities::TSharedPointer<Actor> m_selectedActor; ///< Actor actualmente seleccionado.
};
