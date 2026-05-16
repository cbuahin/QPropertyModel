#
# tests/CMakeLists.txt — QPropertyModel unit test suite
#
# SPDX-License-Identifier: MIT
# Copyright (c) 2014-2026 Caleb Buahin
#

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Widgets LinguistTools)

# Helper macro to create a test executable
macro(qpm_add_test TEST_NAME)
    set(_SOURCES ${ARGN})
    add_executable(${TEST_NAME} ${_SOURCES})

    target_link_libraries(${TEST_NAME}
        PRIVATE
            QPropertyModel
            Qt${QT_VERSION_MAJOR}::Test
            Qt${QT_VERSION_MAJOR}::Widgets
    )

    target_compile_definitions(${TEST_NAME} PRIVATE QT_DEPRECATED_WARNINGS)

    add_test(
        NAME    ${TEST_NAME}
        COMMAND ${TEST_NAME}
    )

    set_tests_properties(${TEST_NAME} PROPERTIES
        TIMEOUT 60
        ENVIRONMENT "QT_QPA_PLATFORM=offscreen"
    )
endmacro()

# ── Test suites ────────────────────────────────────────────────────────────────
qpm_add_test(tst_qpropertymodel
    tst_qpropertymodel.cpp
    testobject.cpp
    testobject.h
)

qpm_add_test(tst_qpropertyitem
    tst_qpropertyitem.cpp
)

qpm_add_test(tst_customtypes
    tst_customtypes.cpp
    testobject.cpp
    testobject.h
)

qpm_add_test(tst_bugs
    tst_bugs.cpp
    testobject.cpp
    testobject.h
)

qpm_add_test(tst_qobjectclasspropertyitem
    tst_qobjectclasspropertyitem.cpp
    testobject.cpp
    testobject.h
)

qpm_add_test(tst_qobjectpropertyitem
    tst_qobjectpropertyitem.cpp
    testobject.cpp
    testobject.h
)

qpm_add_test(tst_typed_properties
    tst_typed_properties.cpp
    testobject.cpp
    testobject.h
)

qpm_add_test(tst_composite_properties
    tst_composite_properties.cpp
    testobject.cpp
    testobject.h
)

qpm_add_test(tst_enum_properties
    tst_enum_properties.cpp
    testobject.cpp
    testobject.h
)

qpm_add_test(tst_edge_cases
    tst_edge_cases.cpp
    testobject.cpp
    testobject.h
)

