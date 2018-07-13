/*!
 * \file *.h
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

#ifndef QOBJECTPROPERTYITEM_H
#define QOBJECTPROPERTYITEM_H

#include "qpropertyitem.h"
#include <QMetaProperty>

class QPROPERTYMODEL_EXPORT QObjectPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      Q_INVOKABLE QObjectPropertyItem(QObject* value, const QMetaProperty& prop, QPropertyItem * parent);

      virtual ~QObjectPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) override;

      bool hasChildren() override;

      QObject* qObject() const;

   protected:
      QObject* m_objectvalue;

   private:
      QMetaProperty m_property;
      bool m_hasMetaProperty ;

};

#endif // QOBJECTPROPERTYITEM_H
