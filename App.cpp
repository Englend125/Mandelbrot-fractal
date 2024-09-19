#include "App.h"

App::App() {
    window = new sf::RenderWindow(sf::VideoMode(900, 900), "Mondelbrot");
    conditions = new std::stack<std::pair<cint, cint>>;

    cur_left = new cint(-2, 2);
    cur_right = new cint(2, -2);
    c_ = cint(-0.3, -1);

    texture.create(window->getSize().x, window->getSize().y);

    mode = 1;

    draw();
}

int App::mondelbrot_check(cint c) {
    cint z(0, 0);

    for (int i = 1; i <= 150; ++i) {
        z = z.step(2) + c;
        if (z.abs() > 1e3) return 2 * i;
    }

    return -1;
}

int App::zhulia_check(cint z) {

    for (int i = 1; i <= 150; ++i) {
        z = z.step(2) + c_;
        if (z.abs() > 1e3) return 2 * i;
    }

    return -1;
}

void App::draw() {
    window->clear();

    sf::VertexArray screen(sf::Points);
    std::vector<sf::Vertex> points;

    for (double i = 1; i <= window->getSize().x; ++i) {
        for (double j = 1; j <= window->getSize().y; ++j) {
            sf::Vertex vertex(sf::Vector2f(i, j));

            double a = cur_left->get_a() + (i / window->getSize().x) * (cur_right->get_a() - cur_left->get_a());
            double b = cur_left->get_b() - (j / window->getSize().y) * (cur_left->get_b() - cur_right->get_b());

            cint c(a, b);

            int k;

            if (mode == 1) k = mondelbrot_check(c);
            else k = zhulia_check(c);

            if (k == -1) {
                vertex.color = sf::Color::Black;
            } else {
                vertex.color = sf::Color(17 * k % 256, 3 * k % 256, 13 * k %256);
            }
            points.push_back(vertex);
        }
    }

    window->draw(&points[0], points.size(), sf::Points);
    texture.update(*window);
    window->display();
}

void App::returning() {
    if (conditions->empty()) return;
    *cur_left = conditions->top().first;
    *cur_right = conditions->top().second;
    conditions->pop();
    draw();
}

void App::update() {
    conditions->push({*cur_left, *cur_right});
    sf::Vector2i mouse = sf::Mouse::getPosition(*window);

    double i = mouse.x;
    double j = mouse.y;

    double a = cur_left->get_a() + (i / window->getSize().x) * (cur_right->get_a() - cur_left->get_a());
    double b = cur_left->get_b() - (j / window->getSize().y) * (cur_left->get_b() - cur_right->get_b());

    double scaleX = cur_right->get_a() - cur_left->get_a();
    double scaleY = cur_left->get_b() - cur_right->get_b();
    scaleX /= scale;
    scaleY /= scale;

    cur_left->set_a(a - scaleX);
    cur_left->set_b(b + scaleY);

    cur_right->set_a(a + scaleX);
    cur_right->set_b(b - scaleY);

    draw();
}

void App::window_update(sf::RectangleShape &rect) {

    if (rect.getSize().x < 5) return;

    conditions->push({*cur_left, *cur_right});

    auto pos = rect.getPosition();

    double i = pos.x;
    double j = pos.y;

    double a = cur_left->get_a() + (i / window->getSize().x) * (cur_right->get_a() - cur_left->get_a());
    double b = cur_left->get_b() - (j / window->getSize().y) * (cur_left->get_b() - cur_right->get_b());

    cint old_left = *cur_left;

    *cur_left = cint(a, b);

    i += rect.getSize().x;
    j += rect.getSize().x;

    a = old_left.get_a() + (i / window->getSize().x) * (cur_right->get_a() - old_left.get_a());
    b = old_left.get_b() - (j / window->getSize().y) * (old_left.get_b() - cur_right->get_b());

    *cur_right = cint(a, b);
    draw();
}

void App::show() {
    sf::Event event;

    bool flag = 1;

    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        returning();
                        continue;
                    case sf::Keyboard::Space:
                        update();
                        continue;
                    case sf::Keyboard::Up:
                        scale *= 2;
                        std::cout << "Scale is: " << scale / 2 << std::endl;
                        continue;
                    case sf::Keyboard::Down:
                        if (scale > 4) {
                            scale /= 2;
                            std::cout << "Scale is: " << scale / 2 << std::endl;
                        }
                        continue;
                    case sf::Keyboard::M:
                        std::cout << "M\n";
                        *cur_left = cint(-2, 2);
                        *cur_right = cint(2, -2);
                        while (conditions->size()) conditions->pop();
                        mode = !mode;
                        draw();
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed && flag) {
                sf::RectangleShape rect;

                rect.setPosition(event.mouseButton.x, event.mouseButton.y);

                sf::Sprite sprite(texture);
                sprite.setPosition(0, 0);

                rect.setFillColor(sf::Color(100, 150, 100, 100));

                while (event.type != sf::Event::MouseButtonReleased) {
                    rect.setSize(sf::Vector2f(abs(rect.getPosition().x - sf::Mouse::getPosition(*window).x),
                                          abs(rect.getPosition().x - sf::Mouse::getPosition(*window).x)));
                    window->clear();
                    window->draw(sprite);
                    window->draw(rect);
                    window->display();
                    window->pollEvent(event);
                }
                window->clear();
                window_update(rect);
            }
        }
    }
}

