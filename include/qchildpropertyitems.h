/*!
 * \file qchildpropertyitems.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Lightweight child property items for composite types (bool, enum, brush, point, etc.).
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

#ifndef QCHILDPROPERTYITEMS_H
#define QCHILDPROPERTYITEMS_H

#include <QMetaEnum>
#include "qpropertyitem.h"

/*!
 * \brief Child property item displaying a bool value as a checkbox.
 *
 * \details Used as a child of flag-type and composite property items to
 * represent individual boolean components.  Returns Qt::CheckStateRole data
 * so the view renders a checkbox, and accepts both Qt::CheckStateRole and
 * Qt::EditRole to toggle the underlying bool.
 */
class QChildBoolPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a boolean child property item.
       *
       * \param[in] value  The initial bool value wrapped in a QVariant.
       * \param[in] name   The display name shown in the name column.
       * \param[in] parent The QPropertyItem that owns this child.
       */
      QChildBoolPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QChildBoolPropertyItem();

      /*!
       * \brief Returns display/check-state data for the given \a column and \a role.
       *
       * \details For column 1, Qt::CheckStateRole returns Qt::Checked or
       * Qt::Unchecked based on the current bool value.  Qt::DisplayRole returns
       * an empty string so only the checkbox is shown.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Sets the bool value from \a value under the given \a role.
       *
       * \details Accepts Qt::CheckStateRole (Qt::Checked / Qt::Unchecked) and
       * Qt::EditRole (raw bool).  Emits valueChanged() on success.
       *
       * \param[in] value The new value; may be a Qt::CheckState or a bool variant.
       * \param[in] role  The role under which to set data.
       * \returns \c true if the value was accepted and written successfully.
       */
      bool setData(const QVariant & value, Qt::ItemDataRole role = Qt::UserRole) override;

};

/*!
 * \brief Child property item representing a nested QBrush value.
 *
 * \details Expandable: creates Color, Style, and Texture sub-children so the
 * individual brush components can be edited directly.  Used as the \b Brush
 * child of QPenPropertyItem.
 */
class QChildBrushPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a brush child property item.
       *
       * \param[in] value  The initial QBrush value wrapped in a QVariant.
       * \param[in] name   The display name shown in the name column (e.g. \c "Brush").
       * \param[in] parent The QPropertyItem that owns this child.
       */
      QChildBrushPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QChildBrushPropertyItem();

      /*!
       * \brief Returns \c true to indicate that Color, Style, and Texture children exist.
       *
       * \details Triggers lazy creation of child items via setChildValues() on
       * the first call.
       *
       * \returns Always \c true.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns item flags.
       *
       * \details Returns Qt::ItemIsEnabled | Qt::ItemIsSelectable.  The brush is
       * edited through its child items.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;


   protected:
      /*!
       * \brief Populates or refreshes the Color, Style, and Texture child items.
       *
       * \details Called automatically on first access and whenever the brush
       * value changes, keeping children in sync.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when a child item's value changes.
       *
       * \details Re-assembles the QBrush from updated child values and emits
       * valueChanged() so the parent QPenPropertyItem can rebuild the QPen.
       *
       * \param[in] name  The child property name.
       * \param[in] value The new child value.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};


/*!
 * \brief Child property item displaying a Qt enum value by its enumerator key name.
 *
 * \details Wraps a QMetaEnum to convert the stored integer enum value to its
 * human-readable key string (e.g. \c "SolidLine") for display.  A QComboBox
 * editor populated with all keys lets the user choose the desired enumerator.
 */
class QChildEnumPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs an enum child property item.
       *
       * \param[in] value     The initial enum value wrapped in a QVariant.
       * \param[in] name      The display name shown in the name column.
       * \param[in] metaEnum  The QMetaEnum describing the enum type.
       * \param[in] parent    The QPropertyItem that owns this child.
       */
      QChildEnumPropertyItem(const QVariant& value, const QString& name, const QMetaEnum& metaEnum, QPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QChildEnumPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns the enumerator key string
       * corresponding to the current integer value.  Qt::EditRole returns the
       * raw integer so the QComboBox delegate can match by index.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns the QMetaEnum associated with this child item.
       *
       * \details Exposes the enumerator so the delegate can populate its QComboBox
       * with the full list of valid keys.
       *
       * \returns The QMetaEnum describing the enum type.
       */
      QMetaEnum enumerator() const;

   private:
      QMetaEnum m_metaEnumProperty; /*!< Metadata for the enum type represented by this item. */
};



/*!
 * \brief Child property item displaying a QIcon preview.
 *
 * \details Used as a child of icon-type property items to show a thumbnail
 * of the current icon.  Qt::DecorationRole provides the icon for display;
 * no in-line editing is supported at this level.
 */
class QChildIconPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs an icon child property item.
       *
       * \param[in] value  The initial QIcon value wrapped in a QVariant.
       * \param[in] name   The display name shown in the name column.
       * \param[in] parent The QPropertyItem that owns this child.
       */
      QChildIconPropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QChildIconPropertyItem();

      /*!
       * \brief Returns display/decoration data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DecorationRole returns the QIcon so the view
       * renders the icon thumbnail.  Qt::DisplayRole returns an empty string.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;


};


/*!
 * \brief Child property item displaying a QImage/QPixmap/QBitmap thumbnail.
 *
 * \details Used as a child of image-type property items to show a scaled
 * thumbnail of the current image.  Qt::DecorationRole provides the pixmap.
 */
class QChildImagePropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs an image child property item.
       *
       * \param[in] value  The initial image value (QImage, QPixmap, or QBitmap)
       *                   wrapped in a QVariant.
       * \param[in] name   The display name shown in the name column.
       * \param[in] parent The QPropertyItem that owns this child.
       */
      QChildImagePropertyItem(const QVariant& value, const QString& name, QPropertyItem * parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QChildImagePropertyItem();

      /*!
       * \brief Returns display/decoration data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DecorationRole returns a scaled QPixmap
       * thumbnail.  Qt::DisplayRole returns an empty string.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

};

/*!
 * \brief Child property item for a QPointF value, expandable into X and Y components.
 *
 * \details Used as a child of QLineFPropertyItem (for P1/P2 endpoints)
 * and other composite items requiring floating-point point children.
 */
class QChildPointFPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs a floating-point point child property item.
       *
       * \param[in] value  The initial QPointF value wrapped in a QVariant.
       * \param[in] name   The display name shown in the name column.
       * \param[in] parent The QPropertyItem that owns this child.
       */
      QChildPointFPropertyItem(const QVariant& value, const QString& name, QPropertyItem *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QChildPointFPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns \c "(x, y)" with
       * floating-point values.  Qt::EditRole returns the raw QPointF.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      bool hasChildren() override;

      /*!
       * \brief Returns item flags.
       *
       * \details Returns Qt::ItemIsEnabled | Qt::ItemIsSelectable.  Component
       * values are edited through the X and Y children.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;


   protected:
      /*!
       * \brief Populates or refreshes the X and Y child items.
       *
       * \details Called automatically on first access and whenever the point
       * value changes.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when an X or Y child value changes.
       *
       * \details Re-assembles the QPointF from child values and emits
       * valueChanged() so the parent item can update its own value.
       *
       * \param[in] name  The child property name (\c "X" or \c "Y").
       * \param[in] value The new floating-point coordinate value.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};

/*!
 * \brief Child property item for a QPoint value, expandable into X and Y components.
 *
 * \details Used as a child of QLinePropertyItem (for P1/P2 endpoints) and
 * other composite items requiring integer point children.
 */
class QChildPointPropertyItem : public QPropertyItem
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs an integer point child property item.
       *
       * \param[in] value  The initial QPoint value wrapped in a QVariant.
       * \param[in] name   The display name shown in the name column.
       * \param[in] parent The QPropertyItem that owns this child.
       */
      QChildPointPropertyItem(const QVariant& value, const QString& name, QPropertyItem *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QChildPointPropertyItem();

      /*!
       * \brief Returns display/edit data for the given \a column and \a role.
       *
       * \details For column 1, Qt::DisplayRole returns \c "(x, y)" with integer
       * values.  Qt::EditRole returns the raw QPoint.
       *
       * \param[in] column The view column (0 = name, 1 = value).
       * \param[in] role   The data role requested.
       * \returns The requested data, or an invalid QVariant if not applicable.
       */
      QVariant data(int column = 1, Qt::ItemDataRole  role = Qt::UserRole) const override;

      /*!
       * \brief Returns \c true to indicate that X and Y child items exist.
       *
       * \details Triggers lazy creation of child items via setChildValues() on
       * the first call.
       *
       * \returns Always \c true.
       */
      bool hasChildren() override;

      /*!
       * \brief Returns item flags.
       *
       * \details Returns Qt::ItemIsEnabled | Qt::ItemIsSelectable.  Component
       * values are edited through the X and Y children.
       *
       * \returns Item flags for this node.
       */
      Qt::ItemFlags flags() const override;


   protected:
      /*!
       * \brief Populates or refreshes the X and Y child items.
       *
       * \details Called automatically on first access and whenever the point
       * value changes.
       */
      void setChildValues() override;

   private slots:
      /*!
       * \brief Slot invoked when an X or Y child value changes.
       *
       * \details Re-assembles the QPoint from child values and emits
       * valueChanged() so the parent item can update its own value.
       *
       * \param[in] name  The child property name (\c "X" or \c "Y").
       * \param[in] value The new integer coordinate value.
       */
      void onChildItemValueChanged(const QString& name, const QVariant& value);

   private:
      bool m_isSettingChildren;

};

#endif // QCHILDPROPERTYITEMS_H

