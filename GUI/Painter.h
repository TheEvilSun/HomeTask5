#pragma once

#include <memory>

#include "GraphicPrimitives/GraphicPrimitives.h"

namespace GUI {

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

class Canvas {
    uint32_t m_width;
    uint32_t m_height;

public:
    Canvas(uint32_t width, uint32_t height) : m_width(width), m_height(height) {

    }
};

class Painter {
    std::shared_ptr<Canvas> m_canvas;

public:
    void clearAll() {

    }

    void clearArea(const Area& area) {

    }

    std::shared_ptr<Canvas> canvas() const {
        return m_canvas;
    }

    void setCanvas(const std::shared_ptr<Canvas>& canvas) {
        m_canvas = canvas;
    }

    Area drawFigure(const GraphicPrimitive::Line& line) {
        return {};
    }

    Area drawFigure(const GraphicPrimitive::Rectangle& rectangle) {
        return {};
    }

    Area drawFigure(const GraphicPrimitive::Square& square) {
        return {};
    }

    Area drawFigure(const GraphicPrimitive::Circle& circle) {
        return {};
    }

    Area drawFigure(const GraphicPrimitive::Ellipse &ellipse) {
        return {};
    }
};

}
