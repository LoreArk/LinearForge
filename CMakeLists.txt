cmake_minimum_required(VERSION 3.10)
project(LinearForge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Trova i pacchetti (Definiscono le variabili/macro internamente)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# 2. Definisci l'eseguibile con i percorsi corretti dell'Explorer
add_executable(${PROJECT_NAME} 
    main.cpp 
    glad.c 
    src/Shader.cpp 
    src/Engine.cpp
    src/Mesh.cpp
)

# 3. GESTIONE INCLUDE (Qui è dove risolviamo l'errore)
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/systems 
    ${GLFW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
)

# 4. Link delle librerie
target_link_libraries(${PROJECT_NAME} 
    ${GLFW_LIBRARIES} 
    OpenGL::GL
    glm::glm
)

add_custom_command(TARGET LinearForge POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/shaders
)