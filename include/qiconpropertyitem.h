/*!
 * \file qiconpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QIcon type with image/file chooser.
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

#ifndef QICONPROPERTYITEM_H
#define QICONPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QIcon, displaying an icon preview in the value column.
 *
 * \details Renders a small icon thumbnail via Qt::DecorationRole so the
 * selected icon is immediately visible.  Activating the editor opens a modal
 * image-browser popup where a new icon source file can be selected.  The item
 * also exposes a child QImage item for direct pixel-level inspection.
 */
class QIconPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs an icon property item.
       *
       * \param[in] value        The initial QIcon value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QIconPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QIconPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1:
       * - Qt::DecorationRole returns a QIcon for thumbnail display.
       * - Qt::DisplayRole returns an empty string (decoration acts as display).
       * - Qt::EditRole returns the raw QIcon wrapped in a QVariant.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true if the icon has child items (e.g. an image child).
       *
       * \details Triggers lazy creation of child items via setChildValues() on
       * the first call.
       *
       * \returns \c true when the icon is non-null; \c false otherwise.
       */
      bool hasChildren() override;

   protected:
      /*!
       * \brief Populates or refreshes child items for the icon.
       *
       * \details Called automatically by hasChildren() on first access and
       * whenever the icon value changes.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when a child item's value changes.
       *
       * \details Updates the parent QIcon from the changed child and writes the
       * result to the underlying QMetaProperty.
       *
       * \param[in] name  The child property name.
       * \param[in] value The new child value.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */
};

#endif // QICONPROPERTYITEM_H
