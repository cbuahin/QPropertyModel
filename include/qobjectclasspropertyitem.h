/*!
 * \file qobjectclasspropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item representing one class level of a QObject hierarchy.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 * \copyright
 * Copyright 2026, Caleb Buahin, All rights reserved.
 * \date 2014-2026
 * \pre
 * \bug
 * \warning
 * \todo
 */

#ifndef QOBJECTCLASSPROPERTYITEM_H
#define QOBJECTCLASSPROPERTYITEM_H

#include "qpropertyitem.h"
#include <QMetaObject>

/*!
 * \brief Property item representing a single class level in a QObject hierarchy.
 *
 * \details When a QObject is displayed in the property browser,
 * QObjectPropertyItem creates one QObjectClassPropertyItem per class (and
 * super-class) in the object's meta-object chain.  Each
 * QObjectClassPropertyItem reflects only the Q_PROPERTY declarations defined
 * directly at its class level, avoiding duplicates across the hierarchy.
 *
 * \details hasChildren() drives lazy construction.  On the first call it
 * enumerates the own properties of the corresponding QMetaObject and creates
 * the appropriate QPropertyItem subclass for each type (bool, enum, QBrush,
 * QPen, QFont, QVector2D–QVector4D, QList<QObject*>, etc.).
 *
 * \details This class also holds static colour resources used by all
 * class-level header rows in the view (s_backgroundColor / s_foregroundColor).
 *
 * \sa QObjectPropertyItem, QVariantPropertyItem
 */
class QPROPERTYMODEL_EXPORT QObjectClassPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a class-level property item for a single class in a QObject hierarchy.
       *
       * \param[in] value       The QObject instance whose properties are reflected.
       * \param[in] metaObject  The class-level QMetaObject to enumerate properties from.
       * \param[in] parent      Parent property item.
       */
      Q_INVOKABLE QObjectClassPropertyItem(QObject* value, const QMetaObject* metaObject, QPropertyItem* parent);

      /*!
       * \brief Constructs a class-level property item for multiple QObjects.
       *
       * \details Used in multi-object selection mode.  All objects in
       * \a values must share the same (or compatible) meta-object hierarchy.
       * The first object in the list is treated as the "primary" object used
       * for reading property values and constructing child items.
       *
       * \param[in] values      The list of QObject instances to reflect.
       * \param[in] metaObject  The class-level QMetaObject to enumerate properties from.
       * \param[in] parent      Parent property item.
       */
      QObjectClassPropertyItem(const QList<QObject*>& values, const QMetaObject* metaObject, QPropertyItem* parent);

      /*!
       * \brief Destroys this item and all lazily created child property items.
       */
      virtual ~QObjectClassPropertyItem();

      /*!
       * \brief Returns data for the given column and role.
       */
      QVariant data(int column = 1, Qt::ItemDataRole role = Qt::UserRole) const override;

      /*!
       * \brief Sets data on the class-level item (no-op).
       */
      bool setData(const QVariant& value, Qt::ItemDataRole role = Qt::UserRole) override;

      /*!
       * \brief Returns \c true if the reflected class declares any own properties.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns the number of child property items.
       */
      int rowCount() const override;

      /*!
       * \brief Returns the primary QObject instance this class-level item reflects.
       * \returns The first QObject pointer in the managed list.
       */
      QObject* qObject() const;

      /*!
       * \brief Returns all QObject instances managed by this class-level item.
       * \returns The full list; single-element for single-object mode.
       */
      QList<QObject*> qObjects() const;

      /*!
       * \brief Returns \c true if this item manages more than one QObject.
       */
      bool isMultiObject() const;

      /*!
       * \brief Returns \c true if all managed objects have the same value for \a prop.
       */
      bool hasUniformValue(const QMetaProperty& prop) const;

      /*!
       * \brief Writes \a value to all managed objects via the given property.
       * \returns \c true if at least the primary write succeeded.
       */
      bool writePropertyToAll(const QMetaProperty& prop, const QVariant& value);

   public slots:
      /*!
       * \brief Re-queries the display labels for every child property item
       *        and updates them via QPropertyItem::setName.
       *
       * \details Connected to the reflected QObject's
       * \c displayLabelsChanged() signal when present.  Lets adapters whose
       * labels depend on runtime context (unit system, locale) refresh
       * the property tree without rebuilding it.
       */
      void refreshDisplayLabels();

   private:
      /*!
       * \brief Resolves the display label for \a property on the primary object.
       *
       * \details Lookup order:
       *   1. \c Q_INVOKABLE \c displayLabelFor(QString) on the object — if it
       *      returns a non-empty string, use it.
       *   2. \c Q_CLASSINFO with the property name as key.
       *   3. The raw Q_PROPERTY name.
       */
      QString resolveDisplayLabel(QObject* primary, const QMetaProperty& property) const;

      const QMetaObject*   m_metaObject;       /*!< \brief Class-level descriptor enumerated by this item. */
      QList<QObject*>      m_objectvalues;     /*!< \brief The QObject instances whose properties are reflected. */
      static QColor        s_backgroundColor;  /*!< \brief Background colour for class-level header rows. */
      static QColor        s_foregroundColor;  /*!< \brief Foreground colour for class-level header rows. */
};

#endif // QOBJECTCLASSPROPERTYITEM_H
