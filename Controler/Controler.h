#pragma once

#include "GraphicPrimitivesModel/GraphicPrimitivesModel.h"

/*!
\brief Классы контролеры для работы с моделью <i>GraphicPrimitivesModel</i>
\author Алексей Волков
\version 1.0
\date Март 2024

Классы, которые позволяют добавлять, удалять объекты модели, актуальность данных модели осуществляют через callback-и
*/

namespace Controler {
/*!
\brief Класс контролер для работы с моделью <i>GraphicPrimitivesModel</i>

Класс, который позволяют добавлять, удалять объекты модели, актуальность данных модели осуществляют через callback-и
*/
class Controler {
    std::list<GraphicPrimitive::FigureType> m_createdFigures;
    std::shared_ptr<Model::GraphicPrimitivesModel> m_model;
    size_t m_addConnectedIndex;
    size_t m_removedConnectedIndex;

public:
    Controler() {

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
        m_createdFigures.clear();
    }

 /*!
Создает графический примитив "Отрезок"
\param p1 первый конец отрезка
\param p2 второй конец отрезка
\param penColor цвет кисти
\param penType тип кисти
\param penWidth ширина кисти
\return <i>void</i>
*/
    void createLine(GraphicPrimitive::Point p1, GraphicPrimitive::Point p2, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Line(p1, p2, penColor, penType, penWidth));
        }
    }

/*!
Создает графический примитив "Прямоугольник"
\param corner левый верхний угол прямоугольника
\param width ширина прямоугольника
\param height высота прямоугольника
\param penColor цвет кисти рамки прямоугольника
\param penType тип кисти рамки прямоугольника
\param penWidth ширина кисти рамки прямоугольника
\param brushColor цвет заливки
\param brushType тип заливки
\return <i>void</i>
*/
    void createRectnagle(GraphicPrimitive::Point corner, float width, float height, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth, uint32_t brushColor, GraphicPrimitive::BrushType brushType) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Rectangle(corner, width, height, penColor, penType, penWidth, brushColor, brushType));
        }
    }

 /*!
Создает графический примитив "Квадрат"
\param corner левый верхний угол квадрата
\param width ширина квадрата
\param penColor цвет кисти рамки квадрата
\param penType тип кисти рамки квадрата
\param penWidth ширина кисти рамки квадрата
\param brushColor цвет заливки
\param brushType тип заливки
\return <i>void</i>
*/
    void createSquare(GraphicPrimitive::Point corner, float width, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth, uint32_t brushColor, GraphicPrimitive::BrushType brushType) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Square(corner, width, penColor, penType, penWidth, brushColor, brushType));
        }
    }

 /*!
Создает графический примитив "Окружность"
\param center центр окружности
\param radius радиус окружности
\param penColor цвет кисти контура окружности
\param penType тип кисти контура окружности
\param penWidth ширина кисти контура окружности
\param brushColor цвет заливки
\param brushType тип заливки
\return <i>void</i>
*/
    void createCircle(GraphicPrimitive::Point center, float radius, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth, uint32_t brushColor, GraphicPrimitive::BrushType brushType) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Circle(center, radius, penColor, penType, penWidth, brushColor, brushType));
        }
    }

 /*!
Создает графический примитив "Эллипс"
\param center центр эллипса
\param radiusX радиус по оси x эллипса
\param radiusY радиус по оси y эллипса
\param penColor цвет кисти контура эллипса
\param penType тип кисти контура эллипса
\param penWidth ширина кисти контура эллипса
\param brushColor цвет заливки
\param brushType тип заливки
\return <i>void</i>
*/
    void createEllipse(GraphicPrimitive::Point center, float radiusX, float radiusY, uint32_t penColor, GraphicPrimitive::PenType penType, float penWidth, uint32_t brushColor, GraphicPrimitive::BrushType brushType) {
        if(m_model) {
            m_model->addFigure(GraphicPrimitive::Ellipse(center, radiusX, radiusY, penColor, penType, penWidth, brushColor, brushType));
        }
    }

private:
 /*!
Callback на добавление графического примитива в модель
\param index индекс добавленного графичекого примитива
\return <i>void</i>
*/
    void addFigure(size_t index) {
        auto figure = m_model->data(index);

        switch (figure->type()) {
        case GraphicPrimitive::FigureType::None:
            break;
        default:
            m_createdFigures.push_back(figure->type());
        }
    }

 /*!
Callback на удаление графического примитива из модели
\param index индекс удаляемого графичекого примитива из модели
\return <i>void</i>
*/
    void removeFigure(size_t index) {
        auto removedFigureItr = std::next(m_createdFigures.begin(), index);
        m_createdFigures.erase(removedFigureItr);
    }
};

}
