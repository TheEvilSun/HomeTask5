cmake_minimum_required(VERSION 3.14)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(HomeTask5 VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

configure_file(version.h.in version.h)

add_subdirectory(GraphicPrimitives)
add_subdirectory(GUI)
add_subdirectory(GraphicPrimitivesModel)
add_subdirectory(Controler)
add_subdirectory(ProjectManager)
add_executable(HomeTask5 main.cpp)

target_link_libraries(GUI PUBLIC
    GraphicPrimitives
    GraphicPrimitivesModel
)

target_link_libraries(Controler PUBLIC
    GraphicPrimitives
    GraphicPrimitivesModel
)

target_link_libraries(GraphicPrimitivesModel PUBLIC
    GraphicPrimitives
)

target_link_libraries(ProjectManager PUBLIC
    GraphicPrimitivesModel
    GUI
    Controler
)


target_link_libraries(HomeTask5 PUBLIC
    ProjectManager
)

target_include_directories(HomeTask5 PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_BINARY_DIR/ProjectManager}"
)

target_include_directories(GUI PUBLIC
    "${PROJECT_BINARY_DIR/GraphicPrimitives}"
     "${PROJECT_BINARY_DIR/GraphicPrimitivesModel}"
)

target_include_directories(GraphicPrimitivesModel PUBLIC
    "${PROJECT_BINARY_DIR/GraphicPrimitives}"
)

target_include_directories(Controler PUBLIC
    "${PROJECT_BINARY_DIR/GraphicPrimitives}"
     "${PROJECT_BINARY_DIR/GraphicPrimitivesModel}"
)

target_include_directories(ProjectManager PUBLIC
    "${PROJECT_BINARY_DIR/GraphicPrimitivesModel}"
    "${PROJECT_BINARY_DIR/GUI}"
    "${PROJECT_BINARY_DIR/Controler}"
)

install(TARGETS HomeTask5 RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alservol@gmail.com)

include(CPack)
