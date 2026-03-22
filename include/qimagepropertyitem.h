/*!
 * \file qimagepropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QImage/QPixmap/QBitmap types.
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

#ifndef QIMAGEPROPERTYITEM_H
#define QIMAGEPROPERTYITEM_H

#include "qvariantpropertyItem.h"


/*!
 * \brief Property item for QImage, QPixmap, and QBitmap types.
 *
 * \details Displays a scaled thumbnail preview of the image in the value
 * column via Qt::DecorationRole.  Activating the editor opens a modal
 * image-browser popup where a new image file can be selected and loaded.
 * Supports QImage, QPixmap, and QBitmap interchangeably.
 */
class QImagePropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs an image property item.
       *
       * \param[in] value        The initial image value (QImage, QPixmap, or QBitmap)
       *                         wrapped in a QVariant.
       * \param[in] metaProperty The meta-property this item represents on the parent QObject.
       * \param[in] parent       The QObjectClassPropertyItem that owns this item.
       */
      QImagePropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QImagePropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1:
       * - Qt::DecorationRole returns a scaled QPixmap thumbnail.
       * - Qt::DisplayRole returns an empty string (decoration acts as display).
       * - Qt::EditRole returns the raw image wrapped in a QVariant.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

};

#endif // QIMAGEPROPERTYITEM_H
