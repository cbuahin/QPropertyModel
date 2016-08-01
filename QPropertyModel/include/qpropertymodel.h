#ifndef QPROPERTYMODEL_H
#define QPROPERTYMODEL_H

#include <qabstractitemmodel.h>
#include "qpropertymodel_global.h"
#include "qvariantpropertyItem.h"
#include "qvariantholderhelper.h"
#include "qpropertyitemdelegate.h"

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
