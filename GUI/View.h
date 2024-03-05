#pragma once

#include "Painter.h"
#include "GraphicPrimitivesModel/GraphicPrimitivesModel.h"

namespace GUI {

/*!
\brief Класс графического представления геометрических примитивов

Класс, который позволяют отображать графические примитивы, находящиеся в модели. Синхронизируется осуществляется через callback-и
*/
class View {
    uint32_t m_width;
    uint32_t m_height;
    Painter m_painter;
    std::shared_ptr<Canvas> m_canvas;
    std::list<Area> m_renderFigureAreas;

    std::shared_ptr<Model::GraphicPrimitivesModel> m_model;
    size_t m_addConnectedIndex;
    size_t m_removedConnectedIndex;

public:
    View(uint32_t width, uint32_t height) : m_width(width), m_height(height) {
        m_canvas = std::make_shared<Canvas>(m_width, m_height);
        m_painter.setCanvas(m_canvas);
    }

    ~View() {
        resetModel();
    }

 /*!
Связывает объект с моделью, подключает callback-и
\param model модель
\return <i>void</i>
*/
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

 /*!
Отвязывает объект от установленной модели, отключает callback-и
\return <i>void</i>
*/
    void resetModel() {
        if(!m_model) {
            return;
        }

        m_model->disconnectToAddFigure(m_addConnectedIndex);
        m_model->disconnectToRemoveFigure(m_removedConnectedIndex);
        m_model.reset();
        m_renderFigureAreas.clear();
        m_painter.clearAll();
    }

private:
 /*!
Добавляет отображение графического примитива
\param index индекс графического примитива
\return <i>void</i>
*/
    void addFigure(size_t index) {
        auto figure = m_model->data(index);

        switch (figure->type()) {
        case GraphicPrimitive::FigureType::None:
            break;
        default:
            m_renderFigureAreas.push_back(drawFigure(figure));
        }
    }

 /*!
Удаляет отображение графического примитива
\param index индекс графического примитива
\return <i>void</i>
*/
    void removeFigure(size_t index) {
        auto removedAreaItr = std::next(m_renderFigureAreas.begin(), index);
        auto removedArea = *removedAreaItr;

        m_renderFigureAreas.erase(removedAreaItr);
        m_painter.clearArea(removedArea);

        auto rerenderAreas = calcRerenderAreas(removedArea);
        for(const auto& area : rerenderAreas) {
            m_painter.clearArea(area.second);
        }

        for(const auto& area : rerenderAreas) {
            drawFigure(m_model->data(area.first));
        }
    }

 /*!
Отрисовывает графический примитив
\param figure графический примитив
\return <i>Area</i>
*/
    Area drawFigure(const std::shared_ptr<GraphicPrimitive::Figure>& figure) {
        switch (figure->type()) {
        case GraphicPrimitive::FigureType::None:
            return {};
        case GraphicPrimitive::FigureType::Circle:
            return m_painter.drawFigure(*dynamic_cast<GraphicPrimitive::Circle*>(figure.get()));
        case GraphicPrimitive::FigureType::Ellipse:
            return m_painter.drawFigure(*dynamic_cast<GraphicPrimitive::Ellipse*>(figure.get()));
        case GraphicPrimitive::FigureType::Line:
            return m_painter.drawFigure(*dynamic_cast<GraphicPrimitive::Line*>(figure.get()));
        case GraphicPrimitive::FigureType::Rectangle:
            return m_painter.drawFigure(*dynamic_cast<GraphicPrimitive::Rectangle*>(figure.get()));
        case GraphicPrimitive::FigureType::Square:
            return m_painter.drawFigure(*dynamic_cast<GraphicPrimitive::Square*>(figure.get()));
        default:
            return {};
        }
    }

 /*!
Расчитывает области, которые необходимо отрисовать заново
\param clearArea область, которая была очищена после удаления графического примитива
\return <i>std::map<size_t, Area></i>
*/
    std::map<size_t, Area> calcRerenderAreas(const Area& clearArea) {
        return {};
    }
};

}
