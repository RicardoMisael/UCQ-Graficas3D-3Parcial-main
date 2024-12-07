#include "BaseApp.h"
#include <cmath>

BaseApp::~BaseApp()
{
    NotificationService::getInstance().saveMessagesToFile("LogData.txt");
}

/**
 * @brief Ejecuta el ciclo principal de la aplicación.
 */
int BaseApp::run() {
    NotificationService& notifier = NotificationService::getInstance();

    if (!initialize()) {
        notifier.addMessage(ConsolErrorType::ERROR, "Initialization failed, check method validations");
        notifier.saveMessagesToFile("LogData.txt");
        ERROR("BaseApp", "run", "Initialization failed");
    }
    else {
        notifier.addMessage(ConsolErrorType::NORMAL, "All components initialized successfully");
    }

    m_GUI.init();

    while (m_window->isOpen()) {
        m_window->handleEvents();
        deltaTime = clock.restart();
        update();
        render();
    }

    cleanup();
    return 0;
}

bool BaseApp::initialize() {
    NotificationService& notifier = NotificationService::getInstance();
    ResourceManager& resourceManager = ResourceManager::getInstance();

    m_window = std::make_unique<Window>(1920, 1080, "Patas Engine");
    if (!m_window) {
        notifier.addMessage(ConsolErrorType::ERROR, "Error creating window");
        return false;
    }

    // Setup waypoints for actors (example: Circle)
    points[0] = Vector2(720.0f, 350.0f);
    points[1] = Vector2(720.0f, 260.0f);
    points[2] = Vector2(125.0f, 50.0f);
    points[3] = Vector2(70.0f, 120.0f);
    points[4] = Vector2(70.0f, 450.0f);
    points[5] = Vector2(400.0f, 350.0f);
    points[6] = Vector2(550.0f, 500.0f);
    points[7] = Vector2(650.0f, 550.0f);
    points[8] = Vector2(720.0f, 450.0f);

    // Initialize Track Actor
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (!Track.isNull()) {
        Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
        Track->getComponent<Transform>()->setTransform(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Vector2(11.0f, 12.0f));
        if (!resourceManager.loadTexture("Circuit", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Failed to load texture: Circuit");
        }

        auto trackTexture = resourceManager.getTexture("Circuit");
        if (trackTexture) {
            Track->getComponent<ShapeFactory>()->getShape()->setTexture(&trackTexture->getTexture());
        }

        m_actors.push_back(Track);
    }

    // Initialize Circle Actor (Player)
    Circle = EngineUtilities::MakeShared<Actor>("Player");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        Circle->getComponent<Transform>()->setTransform(Vector2(200.0f, 200.0f), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
        if (!resourceManager.loadTexture("Characters/tile000", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Failed to load texture: Mario");
        }

        auto trackTexture = resourceManager.getTexture("Characters/tile000");
        if (trackTexture) {
            Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&trackTexture->getTexture());
        }

        m_actors.push_back(Circle);
    }

    // Initialize Triangle Actor
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
        Triangle->getComponent<Transform>()->setPosition(Vector2(200.0f, 200.0f));
        Triangle->getComponent<Transform>()->setRotation(Vector2(0.0f, 0.0f));
        Triangle->getComponent<Transform>()->setScale(Vector2(1.0f, 1.0f));
    }

    m_actors.push_back(Triangle);

    return true;
}

void BaseApp::update() {
    m_window->update();

    for (auto& actor : m_actors) {
        if (actor && actor->isNull()) continue;
        actor->update(m_window->deltaTime.asSeconds());
        if (actor->getName() == "Player") {
            updateMovement(m_window->deltaTime.asSeconds(), actor);
        }
    }
}

void BaseApp::render() {
    NotificationService& notifier = NotificationService::getInstance();
    m_window->clear();

    for (auto& actor : m_actors) {
        if (actor && !actor->isNull()) {
            actor->render(*m_window);
        }
    }

    // ImGui rendering
    m_window->renderToTexture();
    m_window->showInImGui();
    m_GUI.console(notifier.getNotifications());
    m_GUI.inspector();
    m_GUI.hierarchy(m_actors);

    m_window->render();
    m_window->display();
}

void BaseApp::cleanup() {
    m_window->destroy();
    m_window.reset(); // Automatically frees memory
}

void BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
    if (!circle || circle.isNull()) return;

    auto transform = circle->getComponent<Transform>();
    if (transform.isNull()) return;

    Vector2 targetPos = points[m_currentPoint];
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    Vector2 currentPos = transform->getPosition();
    float distanceToTarget = (targetPos - currentPos).lengthSquared(); // Avoid sqrt

    if (distanceToTarget < 10.0f) {
        m_currentPoint = (m_currentPoint + 1) % 9;
    }
}
