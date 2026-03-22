vcpkg_check_linkage(ONLY_DYNAMIC_LIBRARY)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO cbuahin/QPropertyModel
    REF "v${VERSION}"
    SHA512 0  # To be updated after first release tag is made
    HEAD_REF main
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DQPROPERTYMODEL_BUILD_TESTS=OFF
        -DQPROPERTYMODEL_BUILD_DOCS=OFF
        -DQPROPERTYMODEL_BUILD_SHARED=ON
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
    PACKAGE_NAME QPropertyModel
    CONFIG_PATH lib/cmake/QPropertyModel
)

vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

# Install license
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/License.md")

# Install usage
file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
