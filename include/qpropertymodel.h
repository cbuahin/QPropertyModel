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
 * \date 2014-2025
 * \pre
 * \bug
 * \warning
 * \todo
 */

#ifndef QPROPERTYMODEL_H
#define QPROPERTYMODEL_H

#include <qabstractitemmodel.h>
#include "qpropertymodel_global.h"
#include "qvariantholderhelper.h"

/*!
 * \brief The QPropertyModel class
 */
class QPROPERTYMODEL_EXPORT QPropertyModel : public QAbstractItemModel
{
      friend class QObjectClassPropertyItem;

   public:
      QPropertyModel(QObject* parent);

      QPropertyModel(QObject* item, QObject* parent);

      QPropertyModel(const QVariant& item, QObject* parent);

      ~QPropertyModel();

      void setData(const QVariant& item);

      int columnCount(const QModelIndex & parent = QModelIndex()) const override;

      int rowCount(const QModelIndex & parent = QModelIndex()) const override;

      QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

      bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;

      QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;

      QModelIndex parent(const QModelIndex & index) const override;

      Qt::ItemFlags flags(const QModelIndex & index) const override;

      QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

      bool hasChildren(const QModelIndex & parent = QModelIndex()) const override;

      void clear();

      QPropertyItem* rootPropertyItem() const;

      QVariant rootQVariantItem() const;

      bool registerCustomPropertyItemType(int userType, const QMetaObject* metaObject);


   public slots:

      void onDataChanged(const QModelIndex & index);

   private:

      bool checkIfSuperClassIsPropertyItem(const QMetaObject* metaObject);

      bool createRootPropertyItemByType(int userType, const QVariant& item);

      QPropertyItem* createPropertyItemByType(int userType, const QVariant& item, const QMetaProperty& property, QPropertyItem * parent);

   private:
      QPropertyItem* m_rootPropertyItem;
      QVariantHolderHelper* m_variantHolder;
      static QMap<int, const QMetaObject*> m_registeredPropertyItems;
      bool m_wrapperUsed;
};

Q_DECLARE_METATYPE(QList<QObject*>)

#endif // QPROPERTYMODEL_H
