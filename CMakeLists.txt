cmake_minimum_required(VERSION 3.29)
project(Project4_Search_Engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(supersearch main.cpp
        AVLTree.h
        indexHandler.cpp
        indexHandler.h
        porter2_stemmer.cpp
        porter2_stemmer.h
        DocParser.cpp
        DocParser.h
        queryEngine.cpp
        queryEngine.h
        userInterface.cpp
        userInterface.h)
