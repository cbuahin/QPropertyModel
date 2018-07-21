/*!
 * \qflagspropertyitem.h
 * \author Caleb Amoa Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * \license
 * This file and its associated files, and libraries are free software.
 * You can redistribute it and/or modify it under the terms of the
 * Lesser GNU Lesser General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 * This file and its associated files is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.(see <http://www.gnu.org/licenses/> for details)
 * \copyright Copyright 2014-2018, Caleb Buahin, All rights reserved.
 * \date 2014-2018
 * \pre
 * \bug
 * \warning
 * \todo
 */

#ifndef QFLAGSPROPERTYITEM_H
#define QFLAGSPROPERTYITEM_H

#include "qvariantpropertyitem.h"

class QPROPERTYMODEL_EXPORT QFlagsPropertyItem : public QVariantPropertyItem
{
      Q_OBJECT

   public:
      QFlagsPropertyItem(const QVariant& value, const QMetaEnum& metaEnumProperty, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

      virtual ~QFlagsPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      //bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) override;

      bool hasChildren() override;

      Qt::ItemFlags flags() const override;


      QMetaEnum enumerator() const;

   protected:
      void setChildValues() override;

   private slots:
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      QMetaEnum m_metaEnum;
      bool m_isSettingChildren;
};

#endif // QFLAGSPROPERTYITEM_H
