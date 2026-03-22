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
       * \brief Destroys this item and all lazily created child property items.
       */
      virtual ~QObjectClassPropertyItem();

      /*!
       * \brief Returns data for the given column and role.
       *
       * \details Column 0 returns the class name styled with the background
       * colour (Qt::BackgroundRole) and foreground colour (Qt::ForegroundRole)
       * defined by s_backgroundColor / s_foregroundColor.  Column 1 is empty.
       *
       * \param[in] column  Target column (0 = Property, 1 = Value).
       * \param[in] role    Qt item-data role.
       * \returns The requested data, or an invalid QVariant.
       */
      QVariant data(int column = 1, Qt::ItemDataRole role = Qt::UserRole) const override;

      /*!
       * \brief Sets data on the class-level item.
       *
       * \details Class-level header rows are not directly editable; this
       * method is a no-op and always returns \c false.
       *
       * \param[in] value  Ignored.
       * \param[in] role   Ignored.
       * \returns Always \c false.
       */
      bool setData(const QVariant& value, Qt::ItemDataRole role = Qt::UserRole) override;

      /*!
       * \brief Returns \c true if the reflected class declares any own properties.
       *
       * \details On the first call, lazily populates the children list by
       * iterating over the QMetaObject's own (non-inherited) Q_PROPERTYs and
       * creating the appropriate QPropertyItem subclass for each.
       *
       * \returns \c true if any child property items were created.
       */
      bool hasChildren() override;

      /*!\n       * \brief Returns the number of child property items.
       *
       * \details Triggers lazy child construction (via hasChildren()) on the
       * first call so that rowCount() always reflects the actual property count.
       *
       * \returns The number of own-property child items.
       */
      int rowCount() const override;

      /*!
       * \brief Returns the QObject instance this class-level item reflects.
       * \returns The QObject pointer passed at construction time.
       */
      QObject* qObject() const;

   private:
      const QMetaObject* m_metaObject;       /*!< \brief Class-level descriptor enumerated by this item. */
      QObject*           m_objectvalue;      /*!< \brief The QObject whose properties are reflected. */
      static QColor      s_backgroundColor; /*!< \brief Background colour for class-level header rows. */
      static QColor      s_foregroundColor; /*!< \brief Foreground colour for class-level header rows. */
};

#endif // QOBJECTCLASSPROPERTYITEM_H
