/*!
 * \file qfontfamilypropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for font-family strings rendered via a combo-box.
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

#ifndef QFONTFAMILYPROPERTYITEM_H
#define QFONTFAMILYPROPERTYITEM_H

#include "qpropertyitem.h"


/*!
 * \brief Property item for font family selection.
 *
 * \details Displays the font family name in the name column and provides a
 * QComboBox editor populated with all font families available on the system
 * (via QFontDatabase).  This item is used as a child of QFontPropertyItem
 * to expose the \b Family attribute of a QFont for individual editing.
 */
class QFontFamilyPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a font family property item.
       *
       * \param[in] value  The initial font family name wrapped in a QVariant.
       * \param[in] name   The display name shown in the name column (typically \c "Family").
       * \param[in] parent The QPropertyItem that owns this child item.
       */
      QFontFamilyPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QFontFamilyPropertyItem();

   private:

};

#endif // QFONTFAMILYPROPERTYITEM_H
