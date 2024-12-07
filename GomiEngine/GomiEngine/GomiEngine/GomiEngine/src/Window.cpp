#include "GraphicsWindow.h"

GraphicsWindow::GraphicsWindow(int width, int height, const std::string& title) {
    m_graphicsWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);

    if (!m_graphicsWindow) {
        ERROR("GraphicsWindow", "GraphicsWindow", "CHECK CONSTRUCTOR");
    }
    else {
        MESSAGE("GraphicsWindow", "GraphicsWindow", "OK");
    }

    // Inicialización del recurso de ImGui
    ImGui::SFML::Init(*m_graphicsWindow);

    // Crear RenderTexture con las mismas dimensiones que la ventana
    if (!m_renderTexture.create(width, height)) {
        ERROR("GraphicsWindow", "RenderTexture", "CHECK CREATION");
    }
}

// Destructor que libera recursos de ImGui y de la ventana.
GraphicsWindow::~GraphicsWindow() {
    delete m_graphicsWindow;
    m_graphicsWindow = nullptr;
}

// Maneja los eventos de la ventana, como cierre y redimensionamiento.
void
GraphicsWindow::handleEvents() {
    sf::Event event;
    while (m_graphicsWindow->pollEvent(event)) {
        // Procesa los eventos de ImGui
        ImGui::SFML::ProcessEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            m_graphicsWindow->close();
            break;
        case sf::Event::Resized:
            unsigned int width = event.size.width;
            unsigned int height = event.size.height;

            m_view = m_graphicsWindow->getView();
            m_view.setSize(static_cast<float>(width), static_cast<float>(height));
            m_graphicsWindow->setView(m_view);

            // Actualizar RenderTexture si la ventana cambia de tamaño
            m_renderTexture.create(width, height);
            break;
        }
    }
}

// Limpia la ventana y la RenderTexture.
void
GraphicsWindow::clear() {
    if (m_graphicsWindow != nullptr) {
        m_graphicsWindow->clear();
    }
    else {
        ERROR("GraphicsWindow", "clear", "CHECK FOR GRAPHICS WINDOW POINTER DATA");
    }
    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.clear();
    }
}

// Muestra el contenido de la ventana.
void
GraphicsWindow::display() {
    if (m_graphicsWindow != nullptr) {
        m_graphicsWindow->display();
    }
    else {
        ERROR("GraphicsWindow", "display", "CHECK FOR GRAPHICS WINDOW POINTER DATA");
    }
}

// Verifica si la ventana está abierta.
bool
GraphicsWindow::isOpen() const {
    if (m_graphicsWindow != nullptr) {
        return m_graphicsWindow->isOpen();
    }
    else {
        ERROR("GraphicsWindow", "isOpen", "CHECK FOR GRAPHICS WINDOW POINTER DATA");
        return false;
    }
}

// Dibuja un objeto en la RenderTexture.
void
GraphicsWindow::draw(const sf::Drawable& drawable) {
    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.draw(drawable);
    }
}

// Obtiene el puntero a la ventana.
sf::RenderWindow*
GraphicsWindow::getWindow() {
    if (m_graphicsWindow != nullptr) {
        return m_graphicsWindow;
    }
    else {
        ERROR("GraphicsWindow", "getWindow", "CHECK FOR GRAPHICS WINDOW POINTER DATA");
        return nullptr;
    }
}

// Finaliza el proceso de renderizado en la RenderTexture.
void
GraphicsWindow::renderToTexture() {
    m_renderTexture.display();
}

// Muestra la RenderTexture en una ventana de ImGui.
void
GraphicsWindow::showInImGui() {
    const sf::Texture& texture = m_renderTexture.getTexture();

    // Obtener el tamaño de la textura
    ImVec2 size(texture.getSize().x, texture.getSize().y);

    // Renderizar la textura en ImGui con las coordenadas UV invertidas en el eje Y
    ImGui::Begin("Scene");
    ImGui::Image((void*)(intptr_t)texture.getNativeHandle(), size, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

// Actualiza ImGui con el deltaTime de la ventana.
void
GraphicsWindow::update() {
    // Almacena el deltaTime una sola vez
    deltaTime = clock.restart();

    // Usa el deltaTime para actualizar ImGui
    ImGui::SFML::Update(*m_graphicsWindow, deltaTime);
}

// Renderiza ImGui en la ventana.
void
GraphicsWindow::render() {
    ImGui::SFML::Render(*m_graphicsWindow);
}

// Libera recursos de ImGui y elimina el puntero de la ventana.
void
GraphicsWindow::destroy() {
    ImGui::SFML::Shutdown();
    SAFE_PTR_RELEASE(m_graphicsWindow);
}
