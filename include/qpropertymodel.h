/*!
 * \file qpropertymodel.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * QAbstractItemModel subclass implementing the property browser model.
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

#ifndef QPROPERTYMODEL_H
#define QPROPERTYMODEL_H

#include <qabstractitemmodel.h>
#include "qpropertymodel_global.h"
#include "qvariantholderhelper.h"

/*!
 * \brief Qt item model implementing a two-column property browser.
 *
 * \details QPropertyModel is a QAbstractItemModel that exposes the
 * Q_PROPERTY-annotated properties of arbitrary objects as an editable,
 * hierarchical data model.  It is designed to work with QTreeView and
 * QPropertyItemDelegate to produce a property grid similar to the\n * .NET PropertyGrid control or Qt Designer's property panel.
 *
 * \details The model dispatches each incoming value to the appropriate
 * QPropertyItem subclass based on the QMetaType of the QVariant.  The
 * built-in dispatch table covers all common Qt types.  Additional types
 * can be registered at runtime with registerCustomPropertyItemType().
 *
 * \details Supported input types:
 *  - \c QObject*  — All Q_PROPERTY declarations of the object and every
 *    class in its inheritance chain are displayed as collapsible groups.
 *  - \c QVariantHolderHelper*  — Pre-wrapped holder; the single "Value"
 *    property is shown directly.
 *  - Custom registered type — Any QVariant whose metatype ID was passed to
 *    registerCustomPropertyItemType().
 *  - Any other QVariant — Automatically wrapped in QVariantHolderHelper
 *    and displayed as a single "Value" row.
 *
 * \note QList<QObject*> is automatically registered when any model instance
 *       is first constructed.
 *
 * \sa QPropertyItemDelegate, QPropertyItem, QVariantHolderHelper
 */
class QPROPERTYMODEL_EXPORT QPropertyModel : public QAbstractItemModel
{
      Q_OBJECT
      friend class QObjectClassPropertyItem;

   public:
      /*!
       * \brief Constructs an empty model with no data source.
       *
       * \details Call setData() afterwards to populate the model.
       *
       * \param[in] parent  Parent QObject; takes ownership of this model.
       */
      QPropertyModel(QObject* parent);

      /*!
       * \brief Constructs a model pre-populated with the properties of \a item.
       *
       * \details Equivalent to constructing an empty model and calling
       * setData(QVariant::fromValue(item)).
       *
       * \param[in] item    The QObject whose Q_PROPERTY declarations will be shown.
       * \param[in] parent  Parent QObject.
       */
      QPropertyModel(QObject* item, QObject* parent);

      /*!
       * \brief Constructs a model pre-populated from a QVariant.
       *
       * \details The variant can contain any supported type (see class description).
       * Equivalent to constructing an empty model and calling setData(item).
       *
       * \param[in] item    A QVariant containing the data source.
       * \param[in] parent  Parent QObject.
       */
      QPropertyModel(const QVariant& item, QObject* parent);

      /*!
       * \brief Destroys the model and releases all property items.
       */
      ~QPropertyModel();

      /*!
       * \brief Replaces the model's data source and triggers a full view reset.
       *
       * \details Calls beginResetModel() / endResetModel() so any attached
       * QAbstractItemView fully redraws.  Releases ownership of the previous
       * root QPropertyItem.  Passing an invalid (default-constructed) QVariant
       * clears the model completely.
       *
       * \param[in] item  New data source wrapped in a QVariant.
       */
      void setData(const QVariant& item);

      /*!
       * \brief Replaces the model's data source with multiple QObjects.
       *
       * \details When multiple objects are provided, the model shows the
       * properties of the common meta-object chain.  Properties whose values
       * differ across the objects are displayed with a mixed-value indicator
       * ("\xe2\x80\x94").  Editing a property writes the new value to all objects.
       *
       * \param[in] objects  The list of QObject pointers to inspect.
       */
      void setData(const QList<QObject*>& objects);

      /*!
       * \brief Returns the fixed column count (always 2).
       *
       * \details Column 0 is the property name; column 1 is the editable value.
       *
       * \param[in] parent  Unused; present for API conformance.
       * \returns Always 2.
       */
      int columnCount(const QModelIndex& parent = QModelIndex()) const override;

      /*!
       * \brief Returns the number of top-level property rows.
       *
       * \details For a valid parent index the count is delegated to the
       * corresponding QPropertyItem.  For an invalid (root) parent index
       * it returns the number of children of the root property item.
       *
       * \param[in] parent  Parent model index, or an invalid index for root.
       * \returns Row count for the given parent.
       */
      int rowCount(const QModelIndex& parent = QModelIndex()) const override;

      /*!
       * \brief Returns display or decoration data for the given index and role.
       *
       * \details Delegates to the QPropertyItem at the given index.  Supports
       * Qt::DisplayRole, Qt::EditRole, Qt::CheckStateRole, Qt::DecorationRole,
       * Qt::ForegroundRole, and Qt::BackgroundRole.
       *
       * \param[in] index  Model index identifying the row/column/parent.
       * \param[in] role   Qt item-data role.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

      /*!
       * \brief Writes a new value to the property item at \a index.
       *
       * \details Delegates to QPropertyItem::setData() and emits dataChanged()
       * if the write succeeds.
       *
       * \param[in] index  Target model index.
       * \param[in] value  New value to apply.
       * \param[in] role   Qt item-data role (typically Qt::EditRole).
       * \returns \c true if the value was accepted; \c false otherwise.
       */
      bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

      /*!
       * \brief Returns the model index for the item at the given row/column.
       *
       * \param[in] row     Zero-based row number under \a parent.
       * \param[in] column  0 for Property, 1 for Value.
       * \param[in] parent  Parent model index; invalid for top-level items.
       * \returns A QModelIndex encoding the position, or an invalid index if
       *          \a row or \a column is out of range.
       */
      QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

      /*!
       * \brief Returns the parent index of the given model index.
       *
       * \param[in] index  A valid model index.
       * \returns The parent model index, or an invalid index if \a index refers
       *          to a top-level item.
       */
      QModelIndex parent(const QModelIndex& index) const override;

      /*!
       * \brief Returns the item flags for the given index.
       *
       * \details Delegates to QPropertyItem::flags().  Read-only properties
       * (no WRITE accessor) will not include Qt::ItemIsEditable.
       *
       * \param[in] index  Model index to query.
       * \returns The combined Qt::ItemFlags for the item at \a index.
       */
      Qt::ItemFlags flags(const QModelIndex& index) const override;

      /*!
       * \brief Returns the header label for the given section.
       *
       * \details Section 0 returns "Property"; section 1 returns "Value".
       *
       * \param[in] section      Column index (0 or 1).
       * \param[in] orientation  Only Qt::Horizontal is meaningful.
       * \param[in] role         Qt item-data role; only Qt::DisplayRole is handled.
       * \returns The column header string, or an invalid QVariant for other roles.
       */
      QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

      /*!
       * \brief Returns \c true if the item at \a parent has child rows.
       *
       * \param[in] parent  Parent model index.
       * \returns \c true if the corresponding QPropertyItem reports children.
       */
      bool hasChildren(const QModelIndex& parent = QModelIndex()) const override;

      /*!
       * \brief Clears the model and releases the root property item.
       *
       * \details After this call rowCount() returns 0 and rootPropertyItem()
       * returns \c nullptr.  The operation is wrapped in beginResetModel() /
       * endResetModel() so attached views are notified.
       */
      void clear();

      /*!
       * \brief Returns the root QPropertyItem.
       * \returns Pointer to the root item, or \c nullptr if the model is empty.
       */
      QPropertyItem* rootPropertyItem() const;

      /*!
       * \brief Returns the wrapped QVariant when the model was given a plain
       *        QVariant data source.
       *
       * \details This method only returns a valid value when the currently
       * displayed data is backed by a QVariantHolderHelper.  In all other cases
       * it returns an invalid QVariant.
       *
       * \returns The current root QVariant, or an invalid QVariant.
       */
      QVariant rootQVariantItem() const;

      /*!
       * \brief Registers a custom QPropertyItem subclass for a user-defined type.
       *
       * \details After registration, whenever QPropertyModel encounters a
       * QVariant whose metatype ID equals \a userType, it instantiates
       * \a metaObject via QMetaObject::newInstance() to create the property
       * item for that value.  The meta-object must belong to a concrete
       * QPropertyItem subclass whose constructor matches the expected signature.
       *
       * \details Example:
       * \code
       * int myType = qMetaTypeId<MyStruct>();
       * model->registerCustomPropertyItemType(myType,
       *     &MyStructPropertyItem::staticMetaObject);
       * \endcode
       *
       * \param[in] userType    QMetaType identifier (e.g. qMetaTypeId<T>()).
       * \param[in] metaObject  Static meta-object of a QPropertyItem subclass.
       *                        Must not be \c nullptr.
       * \returns \c true if registered successfully; \c false if \a metaObject
       *          is \c nullptr or does not inherit QPropertyItem.
       * \warning This method is not thread-safe.  Call it before any model
       *          instance begins processing data of that type.
       */
      bool registerCustomPropertyItemType(int userType, const QMetaObject* metaObject);

   public slots:
      /*!
       * \brief Internal slot connected to QPropertyItem::valueChanged() to
       *        propagate data-change notifications to attached views.
       *
       * \param[in] index  The model index whose data has changed.
       */
      void onDataChanged(const QModelIndex& index);

   private:
      /*! \brief Checks whether \a metaObject ultimately inherits QPropertyItem. */
      bool checkIfSuperClassIsPropertyItem(const QMetaObject* metaObject);

      /*!
       * \brief Creates the root property item from a QVariant of the given type.
       * \param[in] userType  The QMetaType ID of the value.
       * \param[in] item      The value to wrap.
       * \returns \c true if a matching creator was found and the root was created.
       */
      bool createRootPropertyItemByType(int userType, const QVariant& item);

      /*!
       * \brief Creates a child property item for a specific QMetaProperty.
       * \param[in] userType  The QMetaType ID of the property value.
       * \param[in] item      Current value of the property.
       * \param[in] property  The meta-property descriptor.
       * \param[in] parent    The owning class-level property item.
       * \returns A new QPropertyItem subclass instance, or \c nullptr if the
       *          type is not recognised.
       */
      QPropertyItem* createPropertyItemByType(int userType, const QVariant& item,
                                               const QMetaProperty& property, QPropertyItem* parent);

   private:
      QPropertyItem*           m_rootPropertyItem;          /*!< \brief Root of the property tree; nullptr when empty. */
      QVariantHolderHelper*    m_variantHolder;             /*!< \brief Wrapper used when a plain QVariant is shown. */
      static QMap<int, const QMetaObject*> m_registeredPropertyItems; /*!< \brief Type-to-creator registry shared across all instances. */
      bool m_wrapperUsed; /*!< \brief True when m_variantHolder owns the current data. */
      QList<QObject*>          m_objects;                   /*!< \brief All objects in multi-object mode; empty otherwise. */
};

Q_DECLARE_METATYPE(QList<QObject*>)

#endif // QPROPERTYMODEL_H
