#pragma once

class [[maybe_unused]] Rectangle {
public:
    [[maybe_unused]] Rectangle(int width, int height);

    [[maybe_unused]] [[nodiscard]] int GetArea() const;

    [[maybe_unused]] [[nodiscard]] int GetPerimeter() const;

    [[maybe_unused]] [[nodiscard]] int GetWidth() const;

    [[maybe_unused]] [[nodiscard]] int GetHeight() const;

private:
    int width_, height_;
};