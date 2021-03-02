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
        ImGui::Begin("Config");
        guiWindow();
        ImGui::End();
    }
}

void Gui::handleEnter()
{
    if (m_isInit && m_isVisible)
    {
        m_console.handle();
    }
}

void Gui::guiWindow()
{
    ImGui::InputTextMultiline("hist", m_console.history(), m_console.size(), ImVec2(0, 0),
                              ImGuiInputTextFlags_ReadOnly |
                              ImGuiInputTextFlags_Multiline |
                              ImGuiInputTextFlags_NoHorizontalScroll);

    ImGui::InputText("cmd", m_console.buffer(), m_console.bufferSize());
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
