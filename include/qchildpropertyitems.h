/*!
 * \qchildpropertyitems.h
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

#ifndef QCHILDPROPERTYITEMS_H
#define QCHILDPROPERTYITEMS_H

#include <QMetaEnum>
#include "qpropertyitem.h"

class QPROPERTYMODEL_EXPORT QChildBoolPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      QChildBoolPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      virtual ~QChildBoolPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) override;

};

class QChildBrushPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      QChildBrushPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      virtual ~QChildBrushPropertyItem();

      bool hasChildren() override;

      Qt::ItemFlags flags() const override;


   protected:
      void setChildValues() override;

   private slots:
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren;

};



class QChildEnumPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      QChildEnumPropertyItem(const QVariant& value, const QString& name, const QMetaEnum& metaEnum, QPropertyItem * parent);

      virtual ~QChildEnumPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      QMetaEnum enumerator() const;

   private:
      QMetaEnum m_metaEnumProperty;
};



class QChildIconPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      QChildIconPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      virtual ~QChildIconPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;


};


class QChildImagePropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      QChildImagePropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      virtual ~QChildImagePropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

};

class QChildPointFPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      QChildPointFPropertyItem(const QVariant& value, const QString& name, QPropertyItem *parent);

      virtual ~QChildPointFPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool hasChildren() override;

      Qt::ItemFlags flags() const override;


   protected:
      void setChildValues() override;

   private slots:
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren;

};

class QChildPointPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      QChildPointPropertyItem(const QVariant& value, const QString& name, QPropertyItem *parent);

      virtual ~QChildPointPropertyItem();

      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool hasChildren() override;

      Qt::ItemFlags flags() const override;


   protected:
      void setChildValues() override;

   private slots:
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren;

};

#endif // QCHILDPROPERTYITEMS_H

