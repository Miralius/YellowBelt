#include "rectangle.h"

[[maybe_unused]] Rectangle::Rectangle(int width, int height) : width_(width), height_(height) {
}

[[maybe_unused]] int Rectangle::GetArea() const {
    return width_ * height_;
}

[[maybe_unused]] int Rectangle::GetPerimeter() const {
    return 2 * (width_ + height_);
}

[[maybe_unused]] int Rectangle::GetWidth() const { return width_; }

[[maybe_unused]] int Rectangle::GetHeight() const { return height_; }