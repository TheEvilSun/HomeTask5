#pragma once

#include <list>
#include <vector>
#include <map>
#include <functional>
#include <memory>

#include "GraphicPrimitives/GraphicPrimitives.h"

namespace Model {
class GraphicPrimitivesModel {
    using CallbackType = std::function<void(size_t)>;

    std::list<std::shared_ptr<GraphicPrimitive::Figure>> m_figures;
    std::map<size_t, CallbackType> m_figureAddedCallbacks;
    std::map<size_t, CallbackType> m_figureRemovedCallbacks;

public:
    GraphicPrimitivesModel() {
    }

    GraphicPrimitivesModel(std::list<std::shared_ptr<GraphicPrimitive::Figure>>&& figures) : m_figures(figures){
    }


    std::shared_ptr<GraphicPrimitive::Figure> data(size_t index) {
        if(index >= m_figures.size()) {
            return std::make_shared<GraphicPrimitive::InvalidFigure>();
        }

        return *std::next(m_figures.begin(), index);
    }

    template<typename Figure>
    void addFigure(const Figure& figure) {
        m_figures.push_back(std::make_shared<Figure>(figure));
        figureAdded(m_figures.size() - 1);
    }

    void removeFigure(size_t index) {
        if(index >= m_figures.size()) {
            return;
        }

        m_figures.erase(std::next(m_figures.begin(), index));
        figureRemoved(index);
    }

    size_t count() const {
        return m_figures.size();
    }

    size_t connectToAddFigure(CallbackType callback) {
        auto index = m_figureAddedCallbacks.size();
        m_figureAddedCallbacks[index] = callback;
        return index;
    }

    bool disconnectToAddFigure(size_t index) {
        return m_figureAddedCallbacks.erase(index);
    }

    size_t connectToRemoveFigure(CallbackType callback) {
        auto index = m_figureRemovedCallbacks.size();
        m_figureRemovedCallbacks[index] = callback;
        return index;
    }

    bool disconnectToRemoveFigure(size_t index) {
        return m_figureRemovedCallbacks.erase(index);
    }

private:
    void figureAdded(size_t index) {
        for(auto& callback : m_figureAddedCallbacks) {
            callback.second(index);
        }
    }

    void figureRemoved(size_t index) {
        for(auto& callback : m_figureRemovedCallbacks) {
            callback.second(index);
        }
    }
};

}
