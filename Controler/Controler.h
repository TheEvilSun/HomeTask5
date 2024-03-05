#pragma once

#include "GraphicPrimitivesModel/GraphicPrimitivesModel.h"

namespace Controler {
class Controler {
    std::list<GraphicPrimitive::FigureType> m_createdFigures;
    std::shared_ptr<Model::GraphicPrimitivesModel> m_model;
    size_t m_addConnectedIndex;
    size_t m_removedConnectedIndex;

public:
    Controler() {

    }

    void setModel(const std::shared_ptr<Model::GraphicPrimitivesModel>& model) {
        if(!model) {
            return;
        }

        m_model = model;
        m_addConnectedIndex = m_model->connectToAddFigure([this](size_t index){ addFigure(index); });
        m_removedConnectedIndex = m_model->connectToRemoveFigure([this](size_t index){ removeFigure(index); });

        for(size_t i = 0; i < m_model->count(); i++) {
            addFigure(i);
        }
    }

    void resetModel() {
        if(!m_model) {
            return;
        }

        m_model->disconnectToAddFigure(m_addConnectedIndex);
        m_model->disconnectToRemoveFigure(m_removedConnectedIndex);
        m_model.reset();
        m_createdFigures.clear();
    }

    void createLine(GraphicPrimitive::Point p1, GraphicPrimitive::Point p2, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Line(p1, p2, penColor, penType, penWidth));
        }
    }

    void createRectnagle(GraphicPrimitive::Point corner, float width, float height, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth, uint32_t brushColor, GraphicPrimitive::BrushType brushType) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Rectangle(corner, width, height, penColor, penType, penWidth, brushColor, brushType));
        }
    }

    void createSquare(GraphicPrimitive::Point corner, float width, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth, uint32_t brushColor, GraphicPrimitive::BrushType brushType) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Square(corner, width, penColor, penType, penWidth, brushColor, brushType));
        }
    }

    void createCircle(GraphicPrimitive::Point center, float radius, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth, uint32_t brushColor, GraphicPrimitive::BrushType brushType) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Circle(center, radius, penColor, penType, penWidth, brushColor, brushType));
        }
    }

    void createEllipse(GraphicPrimitive::Point center, float radiusX, float radiusY, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth, uint32_t brushColor, GraphicPrimitive::BrushType brushType) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Ellipse(center, radiusX, radiusY, penColor, penType, penWidth, brushColor, brushType));
        }
    }

private:
    void addFigure(size_t index) {
        auto figure = m_model->data(index);

        switch (figure->type()) {
        case GraphicPrimitive::FigureType::None:
            break;
        default:
            m_createdFigures.push_back(figure->type());
        }
    }

    void removeFigure(size_t index) {
        auto removedFigureItr = std::next(m_createdFigures.begin(), index);
        m_createdFigures.erase(removedFigureItr);
    }
};

}
