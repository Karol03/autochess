/**
 * Created by Karol Dudzic @ 2021
 */

#include "gui.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>


namespace dsp::gui
{

Gui::~Gui()
{
    deinit();
}

void Gui::init(sf::RenderWindow& window)
{
    if (!m_isInit)
    {
        window.resetGLStates();
        ImGui::SFML::Init(window);
    }
    m_isInit = true;
}

void Gui::deinit()
{
    if (m_isInit)
    {
        ImGui::SFML::Shutdown();
    }
    m_isInit = false;
}

void Gui::draw(sf::RenderWindow& window)
{
    if (m_isInit && m_isVisible)
    {
        ImGui::SFML::Update(window, m_deltaClock.restart());
        ImGui::Begin("Config", NULL, ImGuiWindowFlags_NoScrollbar);
        ImGui::SetWindowSize(ImVec2(400, 160), ImGuiCond_FirstUseEver);
        guiWindow();
        ImGui::End();
    }
}

void Gui::guiWindow()
{
    ImGui::BeginChild("##history", ImVec2(0, -3*ImGui::GetTextLineHeight()), false,
                      ImGuiInputTextFlags_ReadOnly |
                      ImGuiInputTextFlags_Multiline |
                      ImGuiInputTextFlags_NoHorizontalScroll);
    ImGui::TextUnformatted(m_console.history());
    ImGui::SetScrollHereY(0.999f);
    ImGui::EndChild();

    ImGui::Separator();

    ImGui::PushItemWidth(-1);
    if (m_console.isBusy())
    {
        ImGui::InputText("##command", m_console.buffer(),
                         m_console.bufferSize(),
                         ImGuiInputTextFlags_ReadOnly);
        ImGui::Text("Working...");
    }
    else if (ImGui::InputText("##command", m_console.buffer(),
                              m_console.bufferSize(),
                              ImGuiInputTextFlags_EnterReturnsTrue))
    {
        m_console.handle();
    }

    if (ImGui::IsItemHovered() || (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
    {
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
    }
    ImGui::PopItemWidth();
}

void Gui::display(sf::RenderWindow& window)
{
    if (m_isInit && m_isVisible)
    {
        ImGui::SFML::Render(window);
    }
}

void Gui::processEvent(sf::Event& event)
{
    if (m_isInit && m_isVisible)
    {
        ImGui::SFML::ProcessEvent(event);
    }
}

}  // namespace dsp::gui
