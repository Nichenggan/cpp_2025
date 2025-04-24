cmake_minimum_required(VERSION 3.27)
project(Gravity_Ninja)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)



include_directories(${CMAKE_SOURCE_DIR})

add_executable(Gravity_Ninja
        main.cpp
        G2D.h
        G2DColor.cpp
        G2Dfull.h
        G2DKey.cpp
        G2DMain.cpp
        G2DMouse.cpp
        G2DPNGreader.cpp
        G2DX.cpp
        glut.h
        GlutImport.h
        V2.cpp
        V2.h
        Button.h
        Button.cpp
        hero.h
        gamedata.h
        hero.cpp
        lodepng.cpp
        lodepng.h
)

target_link_libraries(Gravity_Ninja PRIVATE
        GLUT::GLUT
        OpenGL::GL)

