# QPropertyModel

[![CI](https://github.com/cbuahin/QPropertyModel/actions/workflows/ci.yml/badge.svg)](https://github.com/cbuahin/QPropertyModel/actions/workflows/ci.yml)
[![Docs](https://github.com/cbuahin/QPropertyModel/actions/workflows/docs.yml/badge.svg)](https://github.com/cbuahin/QPropertyModel/actions/workflows/docs.yml)
[![Release](https://github.com/cbuahin/QPropertyModel/actions/workflows/package.yml/badge.svg)](https://github.com/cbuahin/QPropertyModel/actions/workflows/package.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](License.md)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Qt](https://img.shields.io/badge/Qt-5%20%7C%206-brightgreen.svg)](https://www.qt.io/)

A Qt-based property browser model and delegate, designed after the **.NET PropertyGrid** control. Reflect any `QObject`'s Q_PROPERTY declarations into a tree view with automatic type-specific editors — no boilerplate required.

<img src="https://github.com/cbuahin/QPropertyModel/blob/master/resources/Images/pic4.png" alt="QPropertyModel screenshot" width="500"/>

---

## Features

- **Zero-boilerplate reflection** — point `QPropertyModel` at any `QObject` and it automatically enumerates all `Q_PROPERTY` declarations.
- **Rich built-in editors** — spin boxes, color pickers, font choosers, combo boxes, image selectors, and more are wired in automatically.
- **Hierarchical properties** — composite types (e.g. `QRect`, `QBrush`, `QPen`, `QFont`) expand into child rows for per-component editing.
- **Enum and flags support** — `Q_ENUM` / `Q_FLAG` properties render as labeled combo boxes populated at runtime from the meta-object.
- **`QList<QObject*>` support** — nested object lists open a pop-up property editor for the selected item.
- **Custom type registration** — register a factory for any type not built in via `QPropertyModel::registerCustomPropertyItemType()`.
- **Qt 5 & Qt 6 compatible** — single code path; the build system auto-detects the installed Qt major version.
- **Standard Qt model/view** — `QPropertyModel` is a `QAbstractItemModel`; pair it with any `QTreeView` and `QPropertyItemDelegate`.

---

## Supported Property Types

| Type | Editor | Child rows |
|------|--------|------------|
| `QString` | Line edit | — |
| `int` | Spin box | — |
| `double` | Double spin box | — |
| `bool` | Check box | — |
| `QColor` | Color picker dialog | — |
| `QFont` | Font chooser dialog | Family, Size, Bold, Italic, … |
| `QBrush` | Inline combo (style) + color picker | Style, Color |
| `QPen` | Inline combo (style) + color picker | Style, Color, Width |
| `QPoint` | Inline display | X, Y |
| `QPointF` | Inline display | X, Y |
| `QSize` | Inline display | Width, Height |
| `QSizeF` | Inline display | Width, Height |
| `QRect` | Inline display | X, Y, Width, Height |
| `QRectF` | Inline display | X, Y, Width, Height |
| `QLine` | Inline display | P1, P2 |
| `QLineF` | Inline display | P1, P2 |
| `QVector2D` | Inline display | X, Y |
| `QVector3D` | Inline display | X, Y, Z |
| `QVector4D` | Inline display | X, Y, Z, W |
| `QIcon` | Image file picker | Normal/Off pixmap |
| `QImage` | Image file picker | — |
| `QStringList` | Pop-up list editor | — |
| `QVariantList` | Pop-up list editor | — |
| `QDate` | Date picker | — |
| `QTime` | Time picker | — |
| `QDateTime` | Date-time picker | — |
| `QUrl` | Line edit | — |
| `Q_ENUM` types | Combo box (label) | — |
| `Q_FLAG` types | Combo box (flags) | Individual flag children |
| `QList<QObject*>` | Pop-up property editor | Per-item properties |
| Custom types | User-supplied factory | User-defined |

---

## Prerequisites

| Dependency | Version | Notes |
|------------|---------|-------|
| CMake | ≥ 3.16 | Build system |
| Qt | 5.15 or 6.x | Widgets, OpenGL, LinguistTools |
| C++ compiler | C++17 | GCC 9+, Clang 10+, MSVC 2019+ |

Qt OpenGLWidgets is required automatically when building against Qt 6.

---

## Building from Source

```bash
# 1. Clone
git clone https://github.com/cbuahin/QPropertyModel.git
cd QPropertyModel

# 2. Configure
cmake -B build \
      -DCMAKE_BUILD_TYPE=Release \
      -DQPROPERTYMODEL_BUILD_SHARED=ON \
      -DQPROPERTYMODEL_BUILD_TESTS=ON

# 3. Build
cmake --build build --parallel

# 4. (Optional) Install
cmake --install build --prefix /usr/local
```

### CMake Options

| Option | Default | Description |
|--------|---------|-------------|
| `QPROPERTYMODEL_BUILD_SHARED` | `OFF` | Build as a shared library instead of static |
| `QPROPERTYMODEL_BUILD_TESTS` | `OFF` | Build the unit-test suite |
| `QPROPERTYMODEL_BUILD_DOCS` | `OFF` | Build Doxygen HTML documentation |

---

## vcpkg Integration

QPropertyModel ships a vcpkg port in the `ports/` directory.

```bash
# Install from the overlay port
vcpkg install qpropertymodel --overlay-ports=ports
```

Then add to your CMake project:

```cmake
find_package(QPropertyModel CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE QPropertyModel::QPropertyModel)
```

---

## Integrating via CMake FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
    QPropertyModel
    GIT_REPOSITORY https://github.com/cbuahin/QPropertyModel.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(QPropertyModel)

target_link_libraries(my_app PRIVATE QPropertyModel::QPropertyModel)
```

---

## Quick Start

```cpp
#include <QTreeView>
#include <QPropertyModel>
#include <QPropertyItemDelegate>

// 1. Create the model and delegate
auto *model    = new QPropertyModel(this);
auto *delegate = new QPropertyItemDelegate(this);

// 2. Wire up the view
auto *view = new QTreeView(this);
view->setModel(model);
view->setItemDelegate(delegate);
view->setAlternatingRowColors(true);

// 3. Display any QObject's properties
QObject *target = /* your QObject subclass */;
model->setObject(target);
```

Properties are displayed immediately. Edits made in the view are written back to
`target` via `QObject::setProperty()`.

### Registering a Custom Type

```cpp
// Register a factory for MyCustomType (must be declared via Q_DECLARE_METATYPE)
QPropertyModel::registerCustomPropertyItemType(
    QMetaType::fromType<MyCustomType>().id(),
    [](const QString &name, const QVariant &value, QPropertyItem *parent) {
        return new MyCustomPropertyItem(name, value, parent);
    }
);
```

---

## Running Tests

Tests use the Qt Test framework and `QAbstractItemModelTester`.

```bash
cmake -B build -DQPROPERTYMODEL_BUILD_TESTS=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

---

## Generating Documentation

```bash
cmake -B build -DQPROPERTYMODEL_BUILD_DOCS=ON
cmake --build build --target QPropertyModel_docs
# Open docs/html/index.html
```

Alternatively, run Doxygen directly from the `docs/` directory:

```bash
cd docs
doxygen Doxyfile
# Open ./html/index.html
```

---

## Contributing

1. Fork the repository and create a feature branch.
2. Follow existing code style (Qt naming conventions, C++17, `Q_PROPERTY`).
3. Add or update unit tests in `tests/` for any new behaviour.
4. Run the full test suite before opening a pull request.
5. Include a short entry in [CHANGELOG.md](CHANGELOG.md).

Bug reports and feature requests are welcome via [GitHub Issues](https://github.com/cbuahin/QPropertyModel/issues).

---

## License

QPropertyModel is released under the [MIT License](License.md).

Copyright (c) 2014–2026 Caleb Buahin &lt;caleb.buahin@gmail.com&gt;

This software links against the Qt framework, which is available under LGPL v3
and commercial licenses. See [License.md](License.md) for full third-party
attribution.

