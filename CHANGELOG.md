# Changelog

All notable changes to QPropertyModel are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [1.0.0] — 2024-01-01

### Added
- **MIT License** — re-licensed from LGPL v3 to MIT; Qt LGPL dependency acknowledged in `License.md`.
- **Modern CMake build system** — minimum CMake 3.16; `FILE_SET HEADERS`, `GNUInstallDirs`, `CMakePackageConfigHelpers`, Qt5/Qt6 dual support.
- **CMake install targets** — `find_package(QPropertyModel CONFIG REQUIRED)` support via generated `QPropertyModelConfig.cmake`.
- **CPack packaging** — ZIP + TGZ source/binary packages (version 1.0.0).
- **Doxygen documentation** — `QPROPERTYMODEL_BUILD_DOCS=ON` option; `Doxyfile.in` with Graphviz/dot, SVG call graphs, HTML + XML output.
- **vcpkg port** — `ports/qpropertymodel/` with `vcpkg.json`, `portfile.cmake`, and `usage` file.
- **GitHub Actions workflows**:
  - `ci.yml` — builds and tests on Ubuntu, macOS, Windows with Qt 6.5.3.
  - `docs.yml` — generates Doxygen docs and deploys to GitHub Pages on `main`.
  - `package.yml` — creates ZIP/TGZ release artifacts on version tags.
- **Unit test suite** — `QPROPERTYMODEL_BUILD_TESTS=ON` option; three test binaries:
  - `tst_qpropertymodel` — construction, model conformance (QAbstractItemModelTester), setData, clear, headers, data read/write.
  - `tst_qpropertyitem` — flags round-trip, bounds-safe `childPropertyItem()`, signal emission, data-by-column, type inspection.
  - `tst_customtypes` — `registerCustomPropertyItemType()` error paths, success path, `QVariantHolderHelper` value/signal, `QList<QObject*>` auto-registration.
- **Doxygen class and method documentation** added to all 34 public headers.

### Fixed
- `QPropertyItem` constructor: `m_model` and `m_canReset` were uninitialized (undefined behaviour).
- `QPropertyItem::flags()` / `setFlags()`: duplicate `m_isEnabled` check (should have been `m_isSelectable`).
- `QPropertyItem::childPropertyItem(int)`: no bounds check → crash on invalid index; now returns `nullptr`.
- `QPropertyModel::clear()`: called `setData(QVariant())` which recursively triggered `beginResetModel/endResetModel` a second time.
- `QPropertyModel::rootQVariantItem()`: null dereference when no root item was set.
- `QPropertyModel::registerCustomPropertyItemType()`: accepted a null `metaObject` without error; now validates and emits `qWarning()`.
- `QObjectClassPropertyItem`: removed orphaned `qDebug()` statement keyed on property name `"Publications"`.
- `QObjectClassPropertyItem`: added null guard for `m_objectvalue` before iterating properties.
- `QVariantPropertyItem::setData()`: silent failure when `QMetaProperty::write()` returned `false`; now logs `qWarning()`.

### Changed
- `QObjectClassPropertyItem`: added `m_children.reserve()` before the property population loop (performance).
- All source and header files: replaced LGPL v3 license header blocks with MIT SPDX headers.
- `Readme.md`: will be updated with build badges, vcpkg install instructions, and workflow status.

---

[1.0.0]: https://github.com/cbuahin/QPropertyModel/releases/tag/v1.0.0
