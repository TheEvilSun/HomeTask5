#pragma once

#include <string>

#include "GraphicPrimitivesModel/GraphicPrimitivesModel.h"
#include "GUI/View.h"
#include "Controler/Controler.h"

/*!
\brief Компоненты управления проектом
\author Алексей Волков
\version 1.0
\date Март 2024

Содержит компоненты для работы с проектом
*/
namespace Project {

/*!
\brief Класс проекта

Класс, который содержит модель графических примитивов, графическое представление примитивов и управление примитивами
*/
class Project {
    std::shared_ptr<Model::GraphicPrimitivesModel> m_model;
    std::shared_ptr<GUI::View> m_view;
    std::shared_ptr<Controler::Controler> m_controler;
    std::string m_projectFileName;
public:
    Project(const std::string& projectFileName = {}) :
        m_projectFileName(projectFileName)
    {
        if(m_projectFileName.empty()) {
            m_model = std::make_shared<Model::GraphicPrimitivesModel>();
            m_view = std::make_shared<GUI::View>(800, 600);
            m_controler= std::make_shared<Controler::Controler>();
        }
        else {
            parseProjetcFile();
        }

        m_view->setModel(m_model);
        m_controler->setModel(m_model);
    }
private:
/*!
Парсит файл проекта
\return <i>void</i>
*/
    void parseProjetcFile() {
        uint32_t width;
        uint32_t height;
        std::list<std::shared_ptr<GraphicPrimitive::Figure>> figures;

        /*...........................*/

        m_model = std::make_shared<Model::GraphicPrimitivesModel>(std::move(figures));
        m_view = std::make_shared<GUI::View>(width, height);
        m_controler= std::make_shared<Controler::Controler>();
    }
};

/*!
\brief Классы проекта

Класс, который содержит модель графических примитивов, графическое представление примитивов и управление примитивами
*/
class ProjectManager {
    std::map<size_t, Project> m_projects;

public:
/*!
Создает пустой проект
\return <i>void</i>
*/
    void createProject() {
        m_projects[m_projects.size()] = {};
    }

/*!
Загружает проект из файла
\param projectFileName имя файла проекта
\return <i>void</i>
*/
    void openProject(const std::string& projectFileName) {
        m_projects[m_projects.size()] = { projectFileName };
    }

/*!
Закрывает проект
\param index идентификатор проекта
\return <i>void</i>
*/
    void closeProject(size_t index) {
        saveProject(index);
        m_projects.erase(index);
    }

/*!
Сохраняет проект
\param index идентификатор проекта
\return <i>void</i>
*/
    void saveProject(size_t index) {

    }
};
}
