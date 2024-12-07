#pragma once
#include "Prerequisites.h"

class Window {
public:
    // Constructor parametrizado.
    Window(int width, int height, const std::string& title);

    // Destructor
    ~Window();

    // Procesa los eventos de la ventana y actualiza el estado de esta.
    void handleEvents();

    // Limpia el contenido de la ventana con el color predeterminado.
    void clear();

    // Muestra el contenido de la ventana en la pantalla.
    void display();

    // Verifica si la ventana sigue abierta.
    bool isOpen() const;

    /**
     * @brief Dibuja un objeto que puede ser dibujado en la ventana.
     * @param drawable Referencia a un objeto SFML que puede ser dibujado.
     */
    void draw(const sf::Drawable& drawable);

    /**
     * @brief Obtiene el objeto interno SFML RenderWindow.
     * @return Un puntero al objeto interno SFML RenderWindow.
     */
    sf::RenderWindow* getWindow();

    // Función de inicialización.
    void init(int width, int height, const std::string& title);

    // Función que se actualiza por frame.
    void update();

    // Función de renderizado.
    void render();

    // Libera los recursos utilizados por la ventana.
    void destroy();

    // Permite renderizar los objetos gráficos a una textura.
    void renderToTexture();

    // Muestra el contenido de la ventana en ImGui.
    void showInImGui();

    // Ajusta la vista de la ventana.
    void setView(const sf::View& view);

    // Devuelve el tiempo transcurrido entre frames.
    sf::Time getDeltaTime() const;

private:
    sf::RenderWindow* m_window; // Puntero al objeto `RenderWindow` de SFML.
    sf::View m_view; // Vista de la ventana para manejar la perspectiva de visualización.

public:
    sf::RenderTexture m_renderTexture; // Textura para renderizar el contenido.
    sf::Time deltaTime; // Tiempo transcurrido entre frames.
    sf::Clock clock; // Reloj para calcular el tiempo transcurrido entre frames.
};

// Constructor parametrizado
Window::Window(int width, int height, const std::string& title) {
    init(width, height, title);
}

// Destructor
Window::~Window() {
    destroy();
}

void Window::init(int width, int height, const std::string& title) {
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

void Window::handleEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }
    }
}

void Window::clear() {
    m_window->clear();
}

void Window::display() {
    m_window->display();
}

bool Window::isOpen() const {
    return m_window->isOpen();
}

void Window::draw(const sf::Drawable& drawable) {
    m_window->draw(drawable);
}

sf::RenderWindow* Window::getWindow() {
    return m_window;
}

void Window::update() {
    deltaTime = clock.restart();
}

void Window::render() {
    // Aquí puedes hacer el renderizado específico que desees.
}

void Window::destroy() {
    if (m_window) {
        delete m_window;
        m_window = nullptr;
    }
}

void Window::renderToTexture() {
    // Implementar renderizado a textura
}

void Window::showInImGui() {
    // Implementar muestra en ImGui
}

void Window::setView(const sf::View& view) {
    m_window->setView(view);
}

sf::Time Window::getDeltaTime() const {
    return deltaTime;
}
