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

#ifndef QPROPERTYITEM_H
#define QPROPERTYITEM_H

#include <qpropertymodel_global.h>
#include <QObject>
#include <QModelIndex>
#include <QBrush>
#include <QFont>
#include <QIcon>

class QPropertyModel;

class  QPROPERTYMODEL_EXPORT  QPropertyItem : public QObject
{
      friend class QPropertyModel;

      Q_OBJECT
      Q_PROPERTY(QPropertyModel* Model READ  model)
      Q_PROPERTY(QPropertyItem* Parent READ  parent)
      Q_PROPERTY(QString Name READ  name)
      Q_PROPERTY(QModelIndex Index READ  index)
      Q_PROPERTY(int RowCount READ  rowCount)
      Q_PROPERTY(bool HasChildren READ  hasChildren)
      Q_PROPERTY(Qt::ItemFlags Flags READ  flags)
      Q_PROPERTY(bool IsCheckable READ  isCheckable)
      Q_PROPERTY(bool IsEditable READ  isEditable)
      Q_PROPERTY(bool IsEnabled READ  isEnabled)
      Q_PROPERTY(bool IsSelectable READ  isSelectable)
      Q_PROPERTY(bool IsTristate READ  isTristate)
      Q_PROPERTY(QMetaType::Type Type READ  type)
      Q_PROPERTY(QList<QPropertyItem*> ChildPropertyItems READ  childPropertyItems)

   public:

      enum ColumnType
      {
         Property,
         Value,
      };

      Q_INVOKABLE QPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      virtual ~QPropertyItem();

      QPropertyModel* model() const;

      QPropertyItem* parent() const;

      QString name() const;

      QModelIndex index() const;

      virtual QVariant data(int column , Qt::ItemDataRole  role = Qt::UserRole) const;

      QVariant data() const;

      virtual bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole);

      int rowCount() const;

      virtual bool hasChildren();

      virtual Qt::ItemFlags flags() const;

      void setFlags(Qt::ItemFlags flags);

      bool isCheckable() const;

      bool isEditable() const;

      bool isEnabled() const;

      bool isSelectable() const;

      bool isTristate() const;

      QMetaType::Type type() const;

      QList<QPropertyItem*> childPropertyItems() const;

      QPropertyItem* childPropertyItem(int index) const ;

      bool canReset() const;

      virtual void resetData();

   signals:
      void valueChanged(const QString& propertyName, const QVariant& value);

   protected:
      virtual void setChildValues();

   protected:
      void setCheckable(bool checkable);
      void setEditable(bool editable);
      void setEnabled(bool enabled);
      void setSelectable(bool selectable);
      void setTriState(bool tristate);

   protected:
      QList<QPropertyItem*> m_children;
      QPropertyModel* m_model;
      QPropertyItem* m_parent;
      QModelIndex m_index;
      QVariant m_value;
      QVariant m_resetValue;
      QString m_name;
      bool m_isCheckable, m_isEditable, m_isEnabled, m_isSelectable, m_isTristate, m_childrenSet, m_canReset;
};

Q_DECLARE_METATYPE(QPropertyItem*)

#endif // QPROPERTYITEM_H
