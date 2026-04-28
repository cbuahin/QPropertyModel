#
# CMakeLists.txt - CMake configuration for QPropertyModel
#
# Author: Caleb Buahin <caleb.buahin@gmail.com>
#
# Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
# SPDX-License-Identifier: MIT
#

cmake_minimum_required(VERSION 3.16)

project(
    QPropertyModel
    VERSION 1.1.0
    LANGUAGES C CXX
    HOMEPAGE_URL "https://github.com/cbuahin/QPropertyModel"
    DESCRIPTION "A Qt-based property browser model designed after .NET PropertyGrid"
)

# ──────────────────────────────────────────────────────────────────────────────
# Options
# ──────────────────────────────────────────────────────────────────────────────
option(QPROPERTYMODEL_BUILD_TESTS       "Build unit tests"                    OFF)
option(QPROPERTYMODEL_BUILD_DOCS        "Build Doxygen documentation"         OFF)
option(QPROPERTYMODEL_BUILD_SHARED      "Build as shared library"             ON)
option(QPROPERTYMODEL_BUILD_MANUAL_TEST "Build the manual UI test application" ON)

# ──────────────────────────────────────────────────────────────────────────────
# C++ standard
# ──────────────────────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ──────────────────────────────────────────────────────────────────────────────
# Qt auto-tools
# ──────────────────────────────────────────────────────────────────────────────
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

# ──────────────────────────────────────────────────────────────────────────────
# Qt dependency (supports Qt5 and Qt6)
# ──────────────────────────────────────────────────────────────────────────────
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# Qt OpenGLWidgets no longer required (OpenGL not used in the library)

# ──────────────────────────────────────────────────────────────────────────────
# Translation files
# ──────────────────────────────────────────────────────────────────────────────
set(TS_FILES translation/QPropertyModel_en_US.ts)

# ──────────────────────────────────────────────────────────────────────────────
# Library sources
# ──────────────────────────────────────────────────────────────────────────────
set(QPROPERTYMODEL_SOURCES
    src/qbasepropertyitemeditor.cpp
    src/qboolpropertyitem.cpp
    src/qbrushpropertyitem.cpp
    src/qchildboolpropertyitem.cpp
    src/qchildbrushpropertyitem.cpp
    src/qchildenumpropertyitem.cpp
    src/qchildiconpropertyitem.cpp
    src/qchildimagepropertyitem.cpp
    src/qchildpointfpropertyitem.cpp
    src/qchildpointpropertyitem.cpp
    src/qcolorpropertyitemeditor.cpp
    src/qcursorpropertyitemeditor.cpp
    src/qcustomeditors.cpp
    src/qenumpropertyitem.cpp
    src/qflagspropertyitem.cpp
    src/qfontfamilypropertyitem.cpp
    src/qfontpropertyitem.cpp
    src/qfontpropertyitemeditor.cpp
    src/qiconpropertyitem.cpp
    src/qimagepropertyitem.cpp
    src/qimagepropertyitemeditor.cpp
    src/qlinefpropertyitem.cpp
    src/qlinepropertyitem.cpp
    src/qmatrix4x4propertyitem.cpp
    src/qobjectclasspropertyitem.cpp
    src/qobjectlistpropertyitem.cpp
    src/qobjectlistpropertyitemeditor.cpp
    src/qobjectpropertyitem.cpp
    src/qpalettepropertyitemeditor.cpp
    src/qpenpropertyitem.cpp
    src/qpointfpropertyitem.cpp
    src/qpointpropertyitem.cpp
    src/qpolygonpropertyitem.cpp
    src/qpopuppropertyitemeditor.cpp
    src/qpropertyitem.cpp
    src/qpropertyitemdelegate.cpp
    src/qpropertymodel.cpp
    src/qrectfpropertyitem.cpp
    src/qrectpropertyitem.cpp
    src/qselectfromlistpropertyitemeditor.cpp
    src/qsizefpropertyitem.cpp
    src/qsizepolicypropertyitem.cpp
    src/qsizepropertyitem.cpp
    src/qstringlistpropertyitem.cpp
    src/qstringlistpropertyitemeditor.cpp
    src/qtransformpropertyitem.cpp
    src/qvariantholderhelper.cpp
    src/qvariantlistpropertyItem.cpp
    src/qvariantlistpropertyitemeditor.cpp
    src/qvariantpropertyitem.cpp
    src/qvector2dpropertyitem.cpp
    src/qvector3dpropertyitem.cpp
    src/qvector4dpropertyitem.cpp
)

set(QPROPERTYMODEL_HEADERS
    include/qboolpropertyitem.h
    include/qbrushpropertyitem.h
    include/qchildpropertyitems.h
    include/qcustomeditors.h
    include/qenumpropertyitem.h
    include/qflagspropertyitem.h
    include/qfontfamilypropertyitem.h
    include/qfontpropertyitem.h
    include/qiconpropertyitem.h
    include/qimagepropertyitem.h
    include/qlinefpropertyitem.h
    include/qlinepropertyitem.h
    include/qmatrix4x4propertyitem.h
    include/qobjectclasspropertyitem.h
    include/qobjectlistpropertyitem.h
    include/qobjectpropertyitem.h
    include/qpenpropertyitem.h
    include/qpointfpropertyitem.h
    include/qpointpropertyitem.h
    include/qpolygonpropertyitem.h
    include/qpropertyitem.h
    include/qpropertyitemdelegate.h
    include/qpropertymodel.h
    include/qpropertymodel_global.h
    include/qrectfpropertyitem.h
    include/qrectpropertyitem.h
    include/qsizefpropertyitem.h
    include/qsizepolicypropertyitem.h
    include/qsizepropertyitem.h
    include/qstringlistpropertyitem.h
    include/qtransformpropertyitem.h
    include/qvariantholderhelper.h
    include/qvariantlistpropertyitem.h
    include/qvariantpropertyItem.h
    include/qvector2dpropertyitem.h
    include/qvector3dpropertyitem.h
    include/qvector4dpropertyitem.h
)

set(QPROPERTYMODEL_FORMS
    forms/qcustomobjectlistpropertyitemeditor.ui
    forms/qstringlistpropertyitemeditor.ui
)

# ──────────────────────────────────────────────────────────────────────────────
# Library target
# ──────────────────────────────────────────────────────────────────────────────
if(QT_VERSION_MAJOR EQUAL 6)
    if(QPROPERTYMODEL_BUILD_SHARED)
        qt_add_library(QPropertyModel SHARED MANUAL_FINALIZATION)
    else()
        qt_add_library(QPropertyModel STATIC MANUAL_FINALIZATION)
    endif()
    qt_add_resources(QPropertyModel "qpropertymodel_resources"
        PREFIX "/"
        FILES resources/qpropertymodel.qrc
    )
    qt_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})
else()
    if(QPROPERTYMODEL_BUILD_SHARED)
        add_library(QPropertyModel SHARED)
    else()
        add_library(QPropertyModel STATIC)
    endif()
    qt5_add_resources(QPropertyModel "qpropertymodel_resources"
        PREFIX "/"
        FILES resources/qpropertymodel.qrc
    )
    qt5_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})
endif()

target_sources(QPropertyModel
    PRIVATE
        ${QPROPERTYMODEL_SOURCES}
        ${QPROPERTYMODEL_FORMS}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES ${QPROPERTYMODEL_HEADERS}
)

target_compile_definitions(QPropertyModel
    PRIVATE
        QPROPERTYMODEL_LIBRARY
        QT_DEPRECATED_WARNINGS
)

target_include_directories(QPropertyModel
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/forms
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(QPropertyModel
        PUBLIC
            Qt6::Widgets
    )
else()
    target_link_libraries(QPropertyModel
        PUBLIC
            Qt5::Widgets
    )
endif()

set_target_properties(QPropertyModel PROPERTIES
    VERSION   ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME QPropertyModel
)

# ──────────────────────────────────────────────────────────────────────────────
# Unit tests
# ──────────────────────────────────────────────────────────────────────────────
if(QPROPERTYMODEL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ──────────────────────────────────────────────────────────────────────────────
# Manual UI test application
# ──────────────────────────────────────────────────────────────────────────────
if(QPROPERTYMODEL_BUILD_MANUAL_TEST)
    add_subdirectory(src/test)
endif()


# ──────────────────────────────────────────────────────────────────────────────
# Installation
# ──────────────────────────────────────────────────────────────────────────────
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS QPropertyModel
    EXPORT QPropertyModelTargets
    RUNTIME       DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE       DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT QPropertyModelTargets
    FILE        QPropertyModelTargets.cmake
    NAMESPACE   QPropertyModel::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QPropertyModel
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/QPropertyModelConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/QPropertyModelConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QPropertyModel
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/QPropertyModelConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/QPropertyModelConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/QPropertyModelConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QPropertyModel
)

# ──────────────────────────────────────────────────────────────────────────────
# CPack packaging
# ──────────────────────────────────────────────────────────────────────────────
set(CPACK_PACKAGE_NAME              "QPropertyModel")
set(CPACK_PACKAGE_VENDOR            "Caleb Buahin")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VERSION           ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT           "caleb.buahin@gmail.com")
set(CPACK_RESOURCE_FILE_LICENSE     "${CMAKE_CURRENT_SOURCE_DIR}/License.md")
set(CPACK_RESOURCE_FILE_README      "${CMAKE_CURRENT_SOURCE_DIR}/Readme.md")
set(CPACK_GENERATOR                 "ZIP;TGZ")
set(CPACK_ARCHIVE_FILE_NAME         "QPropertyModel-${PROJECT_VERSION}")
include(CPack)

# ──────────────────────────────────────────────────────────────────────────────
# Qt6 finalization
# ──────────────────────────────────────────────────────────────────────────────
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_target(QPropertyModel)
endif()
