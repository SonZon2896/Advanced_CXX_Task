cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME Advanced_CXX_Task_8)

project (${PROJECT_NAME})

set(SOURCES "ExpressionFactory.cpp")
set(HEADERS "Addition.h" "Constant.h" "Expression.h" "ExpressionFactory.h"
			"Operator.h" "Variable.h")

add_executable (${PROJECT_NAME} "main.cpp" ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()