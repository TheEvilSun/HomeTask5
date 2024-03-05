#pragma once

#include <memory>

#include "GraphicPrimitives/GraphicPrimitives.h"
/*!
\brief Компоненты графического интерфейса
\author Алексей Волков
\version 1.0
\date Март 2024

Содержит компоненты для работы с пользовательским интерфейсом
*/
namespace GUI {

/*!
\brief Класс прямоугольной области

Класс прямоугольной области на плоскости, содержит координату верхнего левого угла, ширину и высоту
*/
struct Area {
    GraphicPrimitive::Point corner = {0, 0};
    double width = 0;
    double height = 0;

    Area(){

    }

    Area(const GraphicPrimitive::Point corner_val, double width_val, double height_val) :
        corner(corner_val),
        width(width_val),
        height(height_val)
    {

    }
};

/*!
\brief Класс холста

Класс холста, необходим для отрисовки графических примитивов, содержит ширину и высоту
*/
class Canvas {
    uint32_t m_width;
    uint32_t m_height;

public:
    Canvas(uint32_t width, uint32_t height) : m_width(width), m_height(height) {

    }
};

/*!
\brief Класс художника

Класс художника, отрисовывает графические примитивы на холсте
*/
class Painter {
    std::shared_ptr<Canvas> m_canvas;

public:
/*!
Очищает весь холст
\return <i>void</i>
*/
    void clearAll() {

    }

 /*!
Очищает указанную область холста
\param area область очистки
\return <i>void</i>
*/
    void clearArea(const Area& area) {

    }

 /*!
Возвращает указатель на холст, который используется для рисования
\return <i>std::shared_ptr<Canvas></i>
*/
    std::shared_ptr<Canvas> canvas() const {
        return m_canvas;
    }

 /*!
Устанавливает холс, на котором будет происходить отрисовка
\param canvas указатель на холст
\return <i>void</i>
*/
    void setCanvas(const std::shared_ptr<Canvas>& canvas) {
        m_canvas = canvas;
    }

 /*!
Отрисовка отрезка, возвращает прямоугольную область, в которую вписан отрезок
\param line отрезок
\return <i>Area</i>
*/
    Area drawFigure(const GraphicPrimitive::Line& line) {
        return {};
    }

 /*!
Отрисовка прямоугольника, возвращает прямоугольную область, в которую вписан прямоугольник
\param rectangle прямоугольник
\return <i>Area</i>
*/
    Area drawFigure(const GraphicPrimitive::Rectangle& rectangle) {
        return {};
    }

 /*!
Отрисовка квадрата, возвращает прямоугольную область, в которую вписан квадрат
\param square квадрат
\return <i>Area</i>
*/
    Area drawFigure(const GraphicPrimitive::Square& square) {
        return {};
    }

 /*!
Отрисовка окружности, возвращает прямоугольную область, в которую вписана окружность
\param circle окружность
\return <i>Area</i>
*/
    Area drawFigure(const GraphicPrimitive::Circle& circle) {
        return {};
    }

 /*!
Отрисовка эллипса, возвращает прямоугольную область, в которую вписан эллипс
\param ellipse эллипс
\return <i>Area</i>
*/
    Area drawFigure(const GraphicPrimitive::Ellipse &ellipse) {
        return {};
    }
};

}
