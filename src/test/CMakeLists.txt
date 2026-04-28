#
# src/test/CMakeLists.txt — QPropertyModel manual UI test application
#
# This target is optional. Enable it with:
#   cmake -DQPROPERTYMODEL_BUILD_MANUAL_TEST=ON ...
#
# SPDX-License-Identifier: MIT
# Copyright (c) 2014-2026 Caleb Buahin
#

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(QPropertyModelDemo
    main.cpp
    qpropertymodeltesting.cpp
    qpropertymodeltesting.h
    qpropertymodeltesting.ui
    tempobject.cpp
    tempobject.h
)

# Make the .ui file in src/test/ discoverable by AUTOUIC
set_target_properties(QPropertyModelDemo PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_include_directories(QPropertyModelDemo
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(QPropertyModelDemo
    PRIVATE
        QPropertyModel
        Qt${QT_VERSION_MAJOR}::Widgets
)

target_compile_definitions(QPropertyModelDemo PRIVATE QT_DEPRECATED_WARNINGS)

if(APPLE)
    set_target_properties(QPropertyModelDemo PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "QPropertyModelDemo"
    )
endif()
