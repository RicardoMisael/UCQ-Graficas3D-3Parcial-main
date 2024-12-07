#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Texture : public Component {
public:
    /**
     * @brief Constructor por defecto.
     * Inicializa la textura sin cargar ningún archivo.
     */
    Texture()
        : m_textureName(""),
        m_extension(""),
        Component(ComponentType::TEXTURE) {}

    /**
     * @brief Constructor que inicializa y carga una textura desde un archivo.
     * Intenta cargar la textura especificada con el nombre y extensión proporcionados.
     * Si la carga falla, intenta cargar una textura por defecto ("Default.png").
     */
    Texture(const std::string& textureName, const std::string& extension)
        : m_textureName(textureName),
        m_extension(extension),
        Component(ComponentType::TEXTURE) {
        if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
            std::cerr << "Error al cargar textura: " << m_textureName + "." + m_extension << std::endl;
            if (!m_texture.loadFromFile("Default.png")) {
                std::cerr << "Error al cargar textura por defecto: Default.png" << std::endl;
            }
        }
    }

    /**
     * @brief Destructor por defecto.
     * Libera recursos asociados con la textura.
     */
    virtual ~Texture() = default;

    /**
     * @brief Obtiene la referencia a la textura SFML cargada.
     * @return Referencia a la textura.
     */
    sf::Texture& getTexture() {
        return m_texture;
    }

    /**
     * @brief Actualiza el componente de textura (actualmente vacío).
     * @param deltaTime Tiempo transcurrido desde la última actualización.
     */
    void update(float deltaTime) override {}

    /**
     * @brief Renderiza la textura en la ventana (actualmente no implementado).
     * @param window Ventana donde se renderizará la textura.
     */
    void render(Window& window) override {}

private:
    std::string m_textureName; ///< Nombre del archivo de la textura (sin extensión).
    std::string m_extension;   ///< Extensión del archivo de la textura.
    sf::Texture m_texture;     ///< Instancia de la textura SFML.
};
