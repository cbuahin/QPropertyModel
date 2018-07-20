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

#ifndef QVARIANTHOLDERHELPER_H
#define QVARIANTHOLDERHELPER_H

#include "qpropertymodel_global.h"
#include <QVariant>
#include <QModelIndex>
#include "qobjectpropertyitem.h"

class QPROPERTYMODEL_EXPORT QVariantHolderHelper : public QObject
{
      Q_OBJECT
      Q_PROPERTY(QVariant Value READ value WRITE setValue NOTIFY valueChanged)

   public:
      QVariantHolderHelper(const QVariant& value, QObject* parent);

      virtual ~QVariantHolderHelper();

      QVariant value() const;

      void setValue(const QVariant& value);

      QModelIndex modelIndex() const;

      void setModelIndex(const QModelIndex& index);

   private:
      QString objectName() const;

   signals:
      void valueChanged();

   private:
      QVariant m_value;
      QModelIndex m_index;
};





#endif // QVARIANTHOLDERHELPER_H
