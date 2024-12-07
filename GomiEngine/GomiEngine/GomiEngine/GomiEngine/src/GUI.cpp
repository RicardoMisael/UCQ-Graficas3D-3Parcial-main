#include "GUIHandler.h"
#include "WindowHandler.h"
#include "imgui_internal.h"

// Inicializa la interfaz gráfica.
void GUIHandler::initialize() {
    configureStyle();
}

// Actualiza los elementos de la interfaz.
void GUIHandler::updateInterface() {
}

// Dibuja los elementos de la interfaz.
void GUIHandler::draw() {
}

// Libera recursos y destruye la interfaz gráfica.
void GUIHandler::releaseResources() {
}

// Establece el estilo y colores para los elementos gráficos.
void GUIHandler::configureStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    // Personalización del estilo gráfico
    style.WindowRounding = 8.0f;
    style.FrameRounding = 5.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 5.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.WindowPadding = ImVec2(10, 10);

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.1f, 1.0f);        // Fondo ventana, tono azul oscuro
    colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.4f, 1.0f);         // Fondo título, morado
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.6f, 1.0f);   // Fondo título activo
    colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.2f, 1.0f);         // Fondo cuadro, azul oscuro
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4f, 0.4f, 0.9f, 0.6f);  // Fondo cuadro hover
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.6f, 0.6f, 1.0f, 0.6f);   // Fondo cuadro activo
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.5f, 1.0f);          // Botón
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.7f, 1.0f);   // Botón hover
    colors[ImGuiCol_ButtonActive] = ImVec4(0.4f, 0.4f, 0.8f, 1.0f);    // Botón activo
    colors[ImGuiCol_Text] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);            // Texto blanco
    colors[ImGuiCol_Border] = ImVec4(0.6f, 0.6f, 0.9f, 0.7f);          // Color de borde
    colors[ImGuiCol_CheckMark] = ImVec4(0.8f, 0.8f, 1.0f, 1.0f);       // Marca de verificación
    colors[ImGuiCol_SliderGrab] = ImVec4(0.6f, 0.6f, 1.0f, 1.0f);      // Agarre del deslizador
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8f, 0.8f, 1.0f, 1.0f); // Deslizador activo
}

// Muestra la consola de mensajes con errores del programa.
void GUIHandler::showConsole(std::map<ConsolErrorType, std::string> messages) {
    ImGui::Begin("Console");
    for (const auto& pair : messages) {
        ImGui::Text("Code: %d - Message: %s", pair.first, pair.second.c_str());
    }
    ImGui::End();
}

// Muestra la jerarquía de actores y permite la selección de uno.
void GUIHandler::showHierarchy(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
    NotificationService& notifier = NotificationService::getInstance();

    ImGui::Begin("Actor Hierarchy");

    for (int i = 0; i < actors.size(); ++i) {
        auto& actor = actors[i];
        if (actor.isNull()) continue;

        ImGui::PushID(i);
        std::string displayName = std::to_string(i) + " - " + actor->getName();
        if (ImGui::Selectable(displayName.c_str(), selectedActor == actor)) {
            selectedActor = actor;
        }
        ImGui::PopID();
    }

    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button("Add Circle")) {
        auto circle = EngineUtilities::MakeShared<Actor>("Circle");
        if (!circle.isNull()) {
            circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
            circle->getComponent<Transform>()->setTransform(Vector2(100.0f, 100.0f), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
            actors.push_back(circle);
            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + circle->getName() + "' created.");
        }
    }

    if (ImGui::Button("Add Rectangle")) {
        auto rectangle = EngineUtilities::MakeShared<Actor>("Rectangle");
        if (!rectangle.isNull()) {
            rectangle->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
            rectangle->getComponent<Transform>()->setTransform(Vector2(200.0f, 150.0f), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
            actors.push_back(rectangle);
            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + rectangle->getName() + "' created.");
        }
    }

    if (ImGui::Button("Add Triangle")) {
        auto triangle = EngineUtilities::MakeShared<Actor>("Triangle");
        if (!triangle.isNull()) {
            triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
            triangle->getComponent<Transform>()->setTransform(Vector2(150.0f, 200.0f), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
            actors.push_back(triangle);
            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + triangle->getName() + "' created.");
        }
    }

    ImGui::End();
}

// Muestra el inspector para editar atributos del actor seleccionado.
void GUIHandler::showInspector() {
    if (selectedActor.isNull()) {
        return;
    }

    ImGui::Begin("Inspector");

    char actorName[128];
    std::string name = selectedActor->getName();
    if (name.size() < sizeof(actorName)) {
        std::copy(name.begin(), name.end(), actorName);
        actorName[name.size()] = '\0';
    }

    if (ImGui::InputText("Name", actorName, sizeof(actorName))) {
        selectedActor->setName(std::string(actorName));
    }

    auto transform = selectedActor->getComponent<Transform>();
    if (!transform.isNull()) {
        float* position = new float[2];
        float* rotation = new float[2];
        float* scale = new float[2];
        displayVec2Control("Position", selectedActor->getComponent<Transform>()->getPosData());
        displayVec2Control("Rotation", selectedActor->getComponent<Transform>()->getRotData());
        displayVec2Control("Scale", selectedActor->getComponent<Transform>()->getSclData());
    }

    ImGui::End();
}

// Muestra controles para editar valores de vectores 2D.
void GUIHandler::displayVec2Control(const std::string& label, float* values, float resetValue, float columnWidth) {
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    if (ImGui::DragFloat("##Position", values, 0.1f, resetValue, FLT_MAX, "%.3f")) {
    }
    ImGui::PopStyleVar();
    ImGui::Columns(1);
    ImGui::PopID();
}
