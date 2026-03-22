/*!
 * \file qbrushpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QBrush type with expandable colour/style/texture children.
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

#ifndef QBRUSHPROPERTYITEM_H
#define QBRUSHPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QBrush with expandable Color, Style, and Texture children.
 *
 * \details Displays a filled-rectangle preview of the brush colour and style in
 * the value column.  Expanding the item reveals three child items:
 * - **Color** — the brush foreground colour (QColor).
 * - **Style** — a Qt::BrushStyle enum selector.
 * - **Texture** — an optional QImage texture (non-null for textured brushes).
 *
 * Changes to any child are aggregated and written back to the underlying
 * QMetaProperty via onChildItemValueChanged().
 */
class QBrushPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a brush property item.
       *
       * \param[in] value        The initial QBrush value wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QBrushPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QBrushPropertyItem();

      /*!
       * \brief Returns \c true to indicate that Color, Style, and Texture children exist.
       *
       * \details Triggers lazy creation of child items via setChildValues() on the
       * first call.
       *
       * \returns Always \c true.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns item flags.
       *
       * \details Returns Qt::ItemIsEnabled | Qt::ItemIsSelectable (the brush is
       * not directly editable at the top level; editing is done through children).
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;


   protected:
      /*!
       * \brief Populates or refreshes the Color, Style, and Texture child items.
       *
       * \details Called automatically by hasChildren() the first time it is
       * invoked, and again whenever the brush value changes so child items
       * stay in sync with the parent.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when a child item's value changes.
       *
       * \details Re-assembles the QBrush from all child values and writes the
       * updated brush back to the underlying QMetaProperty.
       *
       * \param[in] name  The property name of the child that changed.
       * \param[in] value The new value of the changed child.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};

#endif // QBRUSHPROPERTYITEM_H
