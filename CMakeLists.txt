cmake_minimum_required(VERSION 3.28)
project(untitled_bullshit)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled_bullshit main.cpp
        Engine/definitions/Entity.h
        Engine/definitions/Ability.h
        Engine/definitions/Ability.cpp
        Engine/definitions/Effect.h
        Engine/managers/TurnManager.h
        Engine/definitions/Action.h)
