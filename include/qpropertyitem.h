/*!
 * \file qpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Abstract base class for all property tree items.
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

#ifndef QPROPERTYITEM_H
#define QPROPERTYITEM_H

#include <qpropertymodel_global.h>
#include <QObject>
#include <QModelIndex>
#include <QBrush>
#include <QFont>
#include <QIcon>

class QPropertyModel;
Q_DECLARE_OPAQUE_POINTER(QPropertyModel*)

/*!
 * \brief Abstract base class for all nodes in a QPropertyModel property tree.
 *
 * \details QPropertyItem represents a single row in the two-column property
 * browser.  Column 0 holds the human-readable property name; column 1 holds
 * the editable value.
 *
 * \details The class uses a lazy-construction pattern: child items are only
 * built the first time hasChildren() is called, and are cached in m_children.
 * Subclasses override setChildValues() to populate those children.  For
 * example, QBrushPropertyItem creates Color, Style, and Texture children that,
 * when modified, reconstruct the parent QBrush bottom-up via the
 * valueChanged() signal chain connected from child to parent.
 *
 * \details Ownership of child QPropertyItem instances is managed by Qt's
 * parent-child mechanism — each child's QObject parent is the containing
 * QPropertyItem so Qt destroys the subtree automatically.
 *
 * \sa QPropertyModel, QPropertyItemDelegate, QVariantPropertyItem
 */
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

      /*!
       * \brief Identifies which column a data() or setData() request targets.
       */
      enum ColumnType
      {
         Property, /*!< \brief Column 0 — the property name label. */
         Value,    /*!< \brief Column 1 — the editable property value. */
      };

      /*!
       * \brief Constructs a QPropertyItem with the given initial value and display name.
       *
       * \details This constructor is declared Q_INVOKABLE so that custom
       * subclasses can be instantiated dynamically via
       * QMetaObject::newInstance() through the type registry in QPropertyModel.
       *
       * \param[in] value  Initial value to store in this item.
       * \param[in] name   Human-readable label displayed in the Property column.
       * \param[in] parent Parent QPropertyItem; pass \c nullptr for root items.
       */
      Q_INVOKABLE QPropertyItem(const QVariant& value, const QString& name, QPropertyItem* parent);

      /*!
       * \brief Destroys the item and recursively destroys all child items.
       */
      virtual ~QPropertyItem();

      /*!
       * \brief Returns the QPropertyModel that owns this item.
       * \returns Pointer to the owning model, or \c nullptr if not yet attached.
       */
      QPropertyModel* model() const;

      /*!
       * \brief Returns the parent QPropertyItem of this item.
       * \returns Pointer to the parent, or \c nullptr for root items.
       */
      QPropertyItem* parent() const;

      /*!
       * \brief Returns the display name of this property (shown in column 0).
       * \returns The name string set at construction time.
       */
      QString name() const;

      /*!
       * \brief Returns the persistent model index of this item.
       * \returns The QModelIndex assigned by the owning QPropertyModel.
       */
      QModelIndex index() const;

      /*!
       * \brief Returns data for the given column and role.
       *
       * \details Column 0 (\c QPropertyItem::Property) returns the property
       * name for Qt::DisplayRole.  Column 1 (\c QPropertyItem::Value) returns
       * the stored value for Qt::DisplayRole and Qt::EditRole.
       *
       * \param[in] column  Target column index (0 = Property, 1 = Value).
       * \param[in] role    Qt item-data role.
       * \returns The requested data as a QVariant, or an invalid QVariant if
       *          the role/column combination is not handled.
       */
      virtual QVariant data(int column, Qt::ItemDataRole role = Qt::UserRole) const;

      /*!
       * \brief Convenience overload that returns the stored value (column 1, UserRole).
       * \returns The current property value as a QVariant.
       */
      QVariant data() const;

      /*!
       * \brief Sets the property value for the given role.
       *
       * \details The base implementation accepts Qt::EditRole and Qt::UserRole
       * and emits valueChanged() on success.  Type-specific subclasses may
       * additionally handle Qt::CheckStateRole (e.g. QBoolPropertyItem).
       *
       * \param[in] value  New value to store.
       * \param[in] role   Qt item-data role (typically Qt::EditRole).
       * \returns \c true if the value was accepted and stored; \c false if
       *          the role is not handled or the value type is incompatible.
       */
      virtual bool setData(const QVariant& value, Qt::ItemDataRole role = Qt::UserRole);

      /*!
       * \brief Returns the number of direct child property items.
       * \returns The count of children currently populated; 0 if none.
       */
      virtual int rowCount() const;

      /*!
       * \brief Returns \c true if this item has or can potentially have children.
       *
       * \details The first call to this method triggers lazy child construction
       * via setChildValues().  Subsequent calls return the cached result without
       * rebuilding children.
       *
       * \returns \c true if children exist or were lazily created.
       */
      virtual bool hasChildren();

      /*!
       * \brief Returns the Qt item flags for this item.
       *
       * \details Default combination is Qt::ItemIsEnabled |
       * Qt::ItemIsEditable | Qt::ItemIsSelectable.  Override in subclasses
       * to change editability or checkability.
       *
       * \returns The combined Qt::ItemFlags for this item.
       */
      virtual Qt::ItemFlags flags() const;

      /*!
       * \brief Replaces the item's flags with the supplied flags.
       *
       * \details Normally used by QPropertyModel to suppress editing for
       * read-only Q_PROPERTYs (i.e. those without a WRITE accessor).
       *
       * \param[in] flags  New flags to apply to this item.
       */
      void setFlags(Qt::ItemFlags flags);

      /*!
       * \brief Returns \c true if the item renders a checkbox.
       * \returns Boolean indicating checkbox visibility.
       */
      bool isCheckable()  const;

      /*!
       * \brief Returns \c true if the value column is editable.
       * \returns Boolean indicating editability state.
       */
      bool isEditable()   const;

      /*!
       * \brief Returns \c true if the item is enabled in the view.
       * \returns Boolean indicating enabled state.
       */
      bool isEnabled()    const;

      /*!
       * \brief Returns \c true if the item can be selected in the view.
       * \returns Boolean indicating selection state.
       */
      bool isSelectable() const;

      /*!
       * \brief Returns \c true if the checkbox operates in three-state mode.
       * \returns Boolean indicating tristate mode.
       */
      bool isTristate()   const;

      /*!
       * \brief Returns the QMetaType::Type of the stored value.
       * \returns The metatype identifier of the underlying QVariant.
       */
      QMetaType::Type type() const;

      /*!
       * \brief Returns the ordered list of all direct child property items.
       * \returns A QList of child QPropertyItem pointers; empty if the item
       *          has no children or children have not been built yet.
       */
      QList<QPropertyItem*> childPropertyItems() const;

      /*!
       * \brief Returns the child item at zero-based position \a index.
       *
       * \param[in] index  Zero-based position in the children list.
       * \returns The child item, or \c nullptr if \a index is out of bounds.
       */
      QPropertyItem* childPropertyItem(int index) const;

      /*!
       * \brief Returns \c true if this item supports resetting to a default value.
       * \returns \c true when a reset value has been recorded; \c false otherwise.
       */
      bool canReset() const;

      /*!
       * \brief Resets the item to its default value recorded at construction.
       *
       * \details The base implementation restores m_value to m_resetValue and
       * emits valueChanged().  Subclasses such as QVariantPropertyItem also
       * write the reset value back through the QMetaProperty.
       */
      virtual void resetData();

   signals:
      /*!
       * \brief Emitted whenever the stored value changes.
       *
       * \details Connected internally from child items to their parent so
       * that composite types (QPen, QBrush, QFont, etc.) can reconstruct
       * their aggregate value when a sub-component changes.
       *
       * \param[out] propertyName  Name of the property whose value changed.
       * \param[out] value         The new value.
       */
      void valueChanged(const QString& propertyName, const QVariant& value);

   protected:
      /*!
       * \brief Lazily constructs child property items for composite types.
       *
       * \details Called exactly once, on the first invocation of hasChildren().
       * Subclasses override this method to enumerate sub-components and append
       * QPropertyItem instances to m_children.  The base implementation is a
       * no-op.
       */
      virtual void setChildValues();

      /*!
       * \brief Sets whether the item renders a checkbox.
       * \param[in] checkable  \c true to show a checkbox.
       */
      void setCheckable(bool checkable);

      /*!
       * \brief Sets whether the value column is editable.
       * \param[in] editable  \c true to allow editing.
       */
      void setEditable(bool editable);

      /*!
       * \brief Sets whether the item is enabled in the view.
       * \param[in] enabled  \c true to enable the item.
       */
      void setEnabled(bool enabled);

      /*!
       * \brief Sets whether the item can be selected.
       * \param[in] selectable  \c true to allow selection.
       */
      void setSelectable(bool selectable);

      /*!
       * \brief Sets whether the checkbox operates in tristate mode.
       * \param[in] tristate  \c true to enable tristate behaviour.
       */
      void setTriState(bool tristate);

   protected:
      QList<QPropertyItem*> m_children;   /*!< \brief Ordered list of lazily constructed child items. */
      QPropertyModel*       m_model;      /*!< \brief Owning model; set by QPropertyModel::setData(). */
      QPropertyItem*        m_parent;     /*!< \brief Parent item; \c nullptr for the root item. */
      QModelIndex           m_index;      /*!< \brief Persistent model index assigned by QPropertyModel. */
      QVariant              m_value;      /*!< \brief Current value displayed in column 1. */
      QVariant              m_resetValue; /*!< \brief Saved default value used by resetData(). */
      QString               m_name;       /*!< \brief Display name shown in column 0. */
      bool m_isCheckable;  /*!< \brief Whether the item shows a checkbox. */
      bool m_isEditable;   /*!< \brief Whether the value column accepts edits. */
      bool m_isEnabled;    /*!< \brief Whether the item is enabled in the view. */
      bool m_isSelectable; /*!< \brief Whether the item is selectable. */
      bool m_isTristate;   /*!< \brief Whether the checkbox uses three states. */
      bool m_childrenSet;  /*!< \brief Guard flag preventing re-entrant child construction. */
      bool m_canReset;     /*!< \brief Whether a default reset value has been recorded. */
};

Q_DECLARE_METATYPE(QPropertyItem*)

#endif // QPROPERTYITEM_H
