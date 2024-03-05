#pragma once

#include <cstdint>
#include "Point.h"

namespace GraphicPrimitive {
/// Набор возможных стилей кисти
enum class PenType {
    None,  ///< Тип отсутствует
    Solid, ///< Сплошная линия
    Dash,  ///< Пунктирная линия
    Dot    ///< Линия из точек
};

/// Набор возможных стилей заливки
enum class BrushType {
    None,       ///< Тип отсутсвует
    Solid,      ///< Сплошная заливка
    Horizontal, ///< Горизонтальные линии
    Vertical    ///< Вертикальные линии
};

/// Набор возможных типов графических примитивов
enum class FigureType {
    None,       ///< Невалидный тип
    Line,       ///< Отрезок
    Rectangle,  ///< Прямоугольник
    Circle,     ///< Окружность
    Square,     ///< Квадрат
    Ellipse     ///< Эллипс
};

/*!
    \brief Интерфейс графического примитива

    Базовый абстрактный класс графического примитива.

    Содержит:
    - цвет кисти
    - тип кисти
    - ширину кисти
    - цвет заливки
    - тип заливки
*/
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

/*!
    \brief Невалидный графический примитив

    Невалидный графический примитив, доступен только метод <i>type()</i>
*/
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

/*!
    \brief Отрезок

    Графический примитив представляющий отрезок, не использует данные заливки

    Содержит:
    - координату начало отрезка
    - координату конец отрезка
*/
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

    Point p1() const {
        return m_p1;
    }

    void setP1(const Point& point) {
        m_p1 = point;
    }

    Point p2() const {
        return m_p2;
    }

    void setP2(const Point& point) {
        m_p2 = point;
    }

    FigureType type() const override {
        return FigureType::Line;
    }
};

/*!
    \brief Прямоугольник

    Графический примитив представляющий прямоугольник

    Содержит:
    - координату верхнего левого угла
    - ширину
    - высоту
*/
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

    Point corner() const {
        return m_corner;
    }

    void setCorner(const Point& point) {
        m_corner = point;
    }

    float width() const {
        return m_width;
    }

    void setWidth(float width) {
        m_width = width;
    }

    float height() const {
        return m_height;
    }

    void setHeight(float height) {
        m_height = height;
    }

    FigureType type() const override {
        return FigureType::Rectangle;
    }
};

/*!
    \brief Окружность

    Графический примитив представляющий окружность

    Содержит:
    - координату центра
    - радиус
*/
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

    Point center() const {
        return m_center;
    }

    void setCenter(const Point& center) {
        m_center = center;
    }

    float radius() const {
        return m_radius;
    }

    void setRadius(float radius) {
        m_radius = radius;
    }

    FigureType type() const override {
        return FigureType::Circle;
    }
};

/*!
    \brief Квадрат

    Графический примитив представляющий квадрат

    Содержит:
    - координату верхнего левого угла
    - ширину
*/
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

    Point corner() const {
        return m_corner;
    }

    void setCorner(const Point& point) {
        m_corner = point;
    }

    float width() const {
        return m_width;
    }

    void setWidth(float width) {
        m_width = width;
    }

    FigureType type() const override {
        return FigureType::Square;
    }
};

/*!
    \brief Эллипс

    Графический примитив представляющий эллипс

    Содержит:
    - координату центра
    - радиус по оси x
    - радиус по оси y
*/
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

    Point center() const {
        return m_center;
    }

    void setCenter(const Point& center) {
        m_center = center;
    }

    float radiusX() const {
        return m_radiusX;
    }

    void setRadiusX(float radius) {
        m_radiusX = radius;
    }

    float radiusY() const {
        return m_radiusY;
    }

    void setRadiusY(float radius) {
        m_radiusY = radius;
    }

    FigureType type() const override {
        return FigureType::Ellipse;
    }
};

}

