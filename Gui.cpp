#include "Gui.h"
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 300
#define BIGGEST_DISK_DIAMETER 150
#define SMALLEST_DISK_DIAMETER 20
#define DISK_HEIGHT 15
#define ROD_WIDTH 10
#define ROD_HEIGHT 135
#define ROD_ALTITUDE 50
#define MAX_DISK_AMOUNT 8

Gui::Gui(Towers *towers_, Solver *solver_) {
    this->towers = towers_;
    this->solver = solver_;
}

void Gui::run() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tower of Hanoi",
                            sf::Style::Titlebar | sf::Style::Close);

    sf::RectangleShape shape(sf::Vector2f(100.0f, 100.0f));

    sf::Font font;
    if (!font.loadFromFile("calibri.ttf"))
        throw;

    sf::Text text, congrats, autosolve;

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    congrats.setFont(font);
    congrats.setCharacterSize(32);
    congrats.setFillColor(sf::Color::Cyan);
    congrats.setString("Puzzle solved!");
    congrats.setPosition((WINDOW_WIDTH - congrats.getLocalBounds().width) / 2.0f, 0);

    autosolve.setFont(font);
    autosolve.setCharacterSize(24);
    autosolve.setFillColor(sf::Color::Red);
    autosolve.setString("Auto solving");
    autosolve.setPosition(WINDOW_WIDTH - autosolve.getLocalBounds().width, 0);

    std::array<std::vector<int>, 3> rods;
    int num, select = -1, tick = 500;
    bool isSolving = false;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Num1:
                    case sf::Keyboard::Num2:
                    case sf::Keyboard::Num3:
                        if (!towers->isComplete() && !isSolving) {
                            num = event.key.code - sf::Keyboard::Num1;
                            if (select == -1) {
                                select = num;
                            } else {
                                if (select != num)
                                    towers->move(select, num);
                                select = -1;
                            }
                        }
                        break;
                    case sf::Keyboard::BackSpace:
                        towers->reset();
                        select = -1;
                        isSolving = false;
                        break;
                    case sf::Keyboard::Hyphen:
                        towers->reset(towers->getDisksAmount() - (towers->getDisksAmount() > 1 ? 1 : 0));
                        select = -1;
                        isSolving = false;
                        break;
                    case sf::Keyboard::Equal:
                        towers->reset(towers->getDisksAmount() + (towers->getDisksAmount() < MAX_DISK_AMOUNT ? 1 : 0));
                        select = -1;
                        isSolving = false;
                        break;
                    case sf::Keyboard::Enter:
                        towers->reset();
                        solver->generate();
                        solver->print(std::cout);
                        select = -1;
                        isSolving = true;
                        clock.restart();
                        break;
                    case sf::Keyboard::Up:
                        tick = std::max(100, tick - 100);
                        break;
                    case sf::Keyboard::Down:
                        tick = std::min(1000, tick + 100);
                        break;
                    default:
                        break;
                }
            }
        }

        if (isSolving && !towers->isComplete() && clock.getElapsedTime() >= sf::milliseconds(tick)) {
            clock.restart();
            solver->next();
        }

        window.clear(sf::Color::White);

        shape.setSize(sf::Vector2f(ROD_WIDTH, ROD_HEIGHT));
        for (int i = 0; i < 3; ++i) {
            shape.setFillColor(i == select ? sf::Color::Blue : sf::Color::Yellow);
            shape.setPosition((i + 1) * WINDOW_WIDTH / 4.0f - ROD_WIDTH / 2.0f,
                              WINDOW_HEIGHT - ROD_HEIGHT - ROD_ALTITUDE);
            window.draw(shape);
        }

        rods = towers->getRods();
        shape.setFillColor(sf::Color::Magenta);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < rods[i].size(); ++j) {
                const float disk_width = SMALLEST_DISK_DIAMETER +
                                         (BIGGEST_DISK_DIAMETER - SMALLEST_DISK_DIAMETER) * (rods[i][j] - 1) /
                                         (MAX_DISK_AMOUNT - 1);
                shape.setSize(sf::Vector2f(disk_width, DISK_HEIGHT));
                shape.setPosition((i + 1) * WINDOW_WIDTH / 4.0f - disk_width / 2.0f,
                                  WINDOW_HEIGHT - ROD_ALTITUDE - (j + 1) * DISK_HEIGHT);
                window.draw(shape);
            }
        }

        text.setString("Moves: " + std::to_string(towers->getMoves()));
        window.draw(text);
        if (towers->isComplete())
            window.draw(congrats);
        if (isSolving)
            window.draw(autosolve);

        window.display();
    }
}
