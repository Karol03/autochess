/**
 * Created by Karol Dudzic @ 2021
 */
#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "console.hpp"
#include "movestream.hpp"


namespace dsp::gui
{

class Gui
{
public:
    explicit Gui() = default;
    ~Gui();

    void deinit();
    void display(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void init(sf::RenderWindow& window);
    void processEvent(sf::Event& event);

    inline void setVisible(bool isVisible) { m_isVisible = isVisible; }
    inline void tie(MoveStreamPtr stream) { std::swap(m_stream, stream); }

private:
    void guiWindow();

private:
    bool m_isInit{false};
    bool m_isVisible{false};
    sf::Clock m_deltaClock;
    Console m_console;
    MoveStreamPtr m_stream;
};

}  // namespace dsp::gui
