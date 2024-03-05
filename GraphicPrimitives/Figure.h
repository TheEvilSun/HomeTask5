#pragma once

#include <cstdint>
#include "Point.h"

namespace GraphicPrimitive {

enum class PenType {
    None,
    Solid,
    Dash,
    Dot
};

enum class BrushType {
    None,
    Solid,
    Horizontal,
    Vertical
};

enum class FigureType {
    None,
    Line,
    Rectangle,
    Circle,
    Square,
    Ellipse
};

class Figure {
    uint32_t m_penColor;
    PenType m_penType;
    float m_penWidth;

    uint32_t m_brushColor;
    BrushType m_brushType;

public:
    Figure(uint32_t penColor, PenType penType, float penWidth, uint32_t brushColor, BrushType brushType) :
        m_penColor(penColor),
        m_penType(penType),
        m_penWidth(penWidth),
        m_brushColor(brushColor),
        m_brushType(brushType)
    {

    }

    Figure(const Figure& other) :
        m_penColor(other.m_penColor),
        m_penType(other.m_penType),
        m_penWidth(other.m_penWidth),
        m_brushColor(other.m_brushColor),
        m_brushType(other.m_brushType)
    {

    }

    uint32_t penColor() const {
        return m_penColor;
    }

    void setPenColor(uint32_t color) {
        m_penColor = color;
    }

    PenType penType() const {
        return m_penType;
    }

    void setPenType(PenType type) {
        m_penType = type;
    }

    float penWidth() const {
        return m_penWidth;
    }

    void setPenWidth(float width) {
        m_penWidth = width;
    }

    uint32_t brushColor() const {
        return m_brushColor;
    }

    void setBrushColor(uint32_t color) {
        m_brushColor = color;
    }

    BrushType brushType() const {
        return m_brushType;
    }

    void setBrushType(BrushType type) {
        m_brushType = type;
    }

    virtual FigureType type() const = 0;
};

class InvalidFigure : public Figure {

public:
    InvalidFigure() : Figure(0, PenType::None, 0, 0, BrushType::None) {

    }

    InvalidFigure(const InvalidFigure& other) :
        Figure(other)
    {

    }

    uint32_t penColor() const = delete;
    void setPenColor(uint32_t color) = delete;

    PenType penType() const = delete;
    void setPenType(PenType type) = delete;

    float penWidth() const = delete;
    void setPenWidth(float width) = delete;

    uint32_t brushColor() const = delete;
    void setBrushColor(uint32_t color) = delete;

    PenType brushType() const = delete;
    void setBrushType(BrushType type) = delete;

    FigureType type() const override {
        return FigureType::None;
    }
};

class Line : public Figure {
    Point m_p1;
    Point m_p2;

public:
    Line(Point p1, Point p2, uint32_t penColor, PenType penType, float penWidth) :
        Figure(penColor, penType, penWidth, 0, BrushType::None),
        m_p1(p1),
        m_p2(p2)
    {

    }

    Line(const Line& other) :
        Figure(other),
        m_p1(other.m_p1),
        m_p2(other.m_p2)
    {

    }

    uint32_t brushColor() const = delete;
    void setBrushColor(uint32_t color) = delete;

    PenType brushType() const = delete;
    void setBrushType(BrushType type) = delete;

    FigureType type() const override {
        return FigureType::Line;
    }
};

class Rectangle : public Figure {
    Point m_corner;
    float m_width;
    float m_height;

public:
    Rectangle(Point corner, float width, float height, uint32_t penColor, PenType penType, float penWidth, uint32_t brushColor, BrushType brushType) :
        Figure(penColor, penType, penWidth, brushColor, brushType),
        m_corner(corner),
        m_width(width),
        m_height(height)
    {

    }

    Rectangle(const Rectangle& other) :
        Figure(other),
        m_corner(other.m_corner),
        m_width(other.m_width),
        m_height(other.m_height)
    {

    }

    FigureType type() const override {
        return FigureType::Rectangle;
    }
};

class Circle : public Figure {
    Point m_center;
    float m_radius;

public:
    Circle(Point center, float radius, uint32_t penColor, PenType penType, float penWidth, uint32_t brushColor, BrushType brushType) :
        Figure(penColor, penType, penWidth, brushColor, brushType),
        m_center(center),
        m_radius(radius)
    {

    }

    Circle(const Circle& other) :
        Figure(other),
        m_center(other.m_center),
        m_radius(other.m_radius)
    {

    }

    FigureType type() const override {
        return FigureType::Circle;
    }
};

class Square : public Figure{
    Point m_corner;
    float m_width;

public:
    Square(Point corner, float width, uint32_t penColor, PenType penType, float penWidth, uint32_t brushColor, BrushType brushType) :
        Figure(penColor, penType, penWidth, brushColor, brushType),
        m_corner(corner),
        m_width(width)
    {

    }

    Square(const Square& other) :
        Figure(other),
        m_corner(other.m_corner),
        m_width(other.m_width)
    {

    }

    FigureType type() const override {
        return FigureType::Square;
    }
};

class Ellipse : public Figure {
    Point m_center;
    float m_radiusX;
    float m_radiusY;

public:
    Ellipse(Point center, float radiusX, float radiusY, uint32_t penColor, PenType penType, float penWidth, uint32_t brushColor, BrushType brushType) :
        Figure(penColor, penType, penWidth, brushColor, brushType),
        m_center(center),
        m_radiusX(radiusX),
        m_radiusY(radiusY)
    {

    }

    Ellipse(const Ellipse& other) :
        Figure(other),
        m_center(other.m_center),
        m_radiusX(other.m_radiusX),
        m_radiusY(other.m_radiusY)
    {

    }

    FigureType type() const override {
        return FigureType::Ellipse;
    }
};

}

