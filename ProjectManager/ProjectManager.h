#pragma once

#include <string>

#include "GraphicPrimitivesModel/GraphicPrimitivesModel.h"
#include "GUI/View.h"
#include "Controler/Controler.h"

namespace Project {
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

class ProjectManager {
    std::map<size_t, Project> m_projects;

public:
    void createProject() {
        m_projects[m_projects.size()] = {};
    }

    void openProject(const std::string& projectFileName) {
        m_projects[m_projects.size()] = { projectFileName };
    }

    void closeProject(size_t index) {
        saveProject(index);
        m_projects.erase(index);
    }

    void saveProject(size_t index) {

    }
};
}
