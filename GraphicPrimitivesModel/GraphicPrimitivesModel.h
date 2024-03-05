#pragma once

#include <list>
#include <vector>
#include <map>
#include <functional>
#include <memory>

#include "GraphicPrimitives/GraphicPrimitives.h"
/*!
\brief Классы моделей для хранения графических примитивов
\author Алексей Волков
\version 1.0
\date Март 2024

Классы, которые позволяют хранить, добавлять, удалять объекты графических примитивов: GraphicPrimitive::Point, GraphicPrimitive::Line, GraphicPrimitive::Rectangle, GraphicPrimitive::Circle, GraphicPrimitive::Square, GraphicPrimitive::Ellipse
*/
namespace Model {

using CallbackType = std::function<void(size_t)>; ///< тип callback-а

/*!
\brief Классы модели для работы с графическими притивами

Класс, который позволяют хранить, добавлять, удалять графические примитивы, синхронизируется осуществляется через callback-и
*/
class GraphicPrimitivesModel {    
    std::list<std::shared_ptr<GraphicPrimitive::Figure>> m_figures;
    std::map<size_t, CallbackType> m_figureAddedCallbacks;
    std::map<size_t, CallbackType> m_figureRemovedCallbacks;

public:
    GraphicPrimitivesModel() {
    }

    GraphicPrimitivesModel(std::list<std::shared_ptr<GraphicPrimitive::Figure>>&& figures) : m_figures(figures){
    }

/*!
Возвращает указатель на графический примитив
\param index индекс графического примитива
\return <i>std::shared_ptr<GraphicPrimitive::Figure></i>
*/
    std::shared_ptr<GraphicPrimitive::Figure> data(size_t index) {
        if(index >= m_figures.size()) {
            return std::make_shared<GraphicPrimitive::InvalidFigure>();
        }

        return *std::next(m_figures.begin(), index);
    }

/*!
Добавляет графический примитив в модель, вызывает callback-и
\param figure графический примитив
\return <i>void</i>
*/
    template<typename Figure>
    void addFigure(const Figure& figure) {
        m_figures.push_back(std::make_shared<Figure>(figure));
        figureAdded(m_figures.size() - 1);
    }

/*!
Удаляет графический примитив из модели, вызывает callback-и
\param index индекс графического примитива
\return <i>void</i>
*/
    void removeFigure(size_t index) {
        if(index >= m_figures.size()) {
            return;
        }

        m_figures.erase(std::next(m_figures.begin(), index));
        figureRemoved(index);
    }

/*!
Возвращает количество графических примитивов в модели
\return <i>size_t</i>
*/
    size_t count() const {
        return m_figures.size();
    }

/*!
Подключает callback на добавление графического примитива в модель, возвращает идентификатор подключения
\param callback вызываемый объект
\return <i>size_t</i>
*/
    size_t connectToAddFigure(CallbackType callback) {
        auto index = m_figureAddedCallbacks.size();
        m_figureAddedCallbacks[index] = callback;
        return index;
    }

/*!
Отключает callback на добавление графического примитива в модель, возвращает <i>true</i> если удалось отключить, в противном случае <i>false</i>
\param index идентификатор подключения
\return <i>bool</i>
*/
    bool disconnectToAddFigure(size_t index) {
        return m_figureAddedCallbacks.erase(index);
    }

/*!
Подключает callback на удаление графического примитива из модели, возвращает идентификатор подключения
\param callback вызываемый объект
\return <i>size_t</i>
*/
    size_t connectToRemoveFigure(CallbackType callback) {
        auto index = m_figureRemovedCallbacks.size();
        m_figureRemovedCallbacks[index] = callback;
        return index;
    }

/*!
Отключает callback на удаление графического примитива из модели, возвращает <i>true</i> если удалось отключить, в противном случае <i>false</i>
\param index идентификатор подключения
\return <i>bool</i>
*/
    bool disconnectToRemoveFigure(size_t index) {
        return m_figureRemovedCallbacks.erase(index);
    }

private:
/*!
Вызывает callback-и на добавление графического примитива
\param index индекс графического примитива
\return <i>void</i>
*/
    void figureAdded(size_t index) {
        for(auto& callback : m_figureAddedCallbacks) {
            callback.second(index);
        }
    }

/*!
Вызывает callback-и на удаление графического примитива
\param index индекс графического примитива
\return <i>void</i>
*/
    void figureRemoved(size_t index) {
        for(auto& callback : m_figureRemovedCallbacks) {
            callback.second(index);
        }
    }
};

}
