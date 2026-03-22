/*!
 * \file qvariantpropertyItem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item backed by a QMetaProperty for direct QObject introspection.
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

#ifndef QVARIANTPROPERTYITEM_H
#define QVARIANTPROPERTYITEM_H

#include <QMetaProperty>
#include "qpropertymodel_global.h"
#include "qobjectclasspropertyitem.h"

/*!
 * \brief Property item backed by a QMetaProperty for direct QObject read/write.
 *
 * \details QVariantPropertyItem is the workhorse for leaf-level properties.
 * It stores a reference to both the QMetaProperty descriptor and the owning
 * QObjectClassPropertyItem so that values can be read from and written to the
 * underlying QObject at runtime via QMetaProperty::read() and
 * QMetaProperty::write().
 *
 * \details Subclasses (QBoolPropertyItem, QEnumPropertyItem, QFontPropertyItem,
 * etc.) override data() and setData() to provide type-specific rendering,
 * decoration, and editing behaviour while reusing the base read/write logic.
 *
 * \details The resetData() implementation reads the RESET function from the
 * QMetaProperty definition (if present) and invokes it on the QObject, then
 * refreshes the stored value.
 *
 * \sa QObjectClassPropertyItem, QPropertyItem
 */
class QPROPERTYMODEL_EXPORT  QVariantPropertyItem : public QPropertyItem
{
        Q_OBJECT

    public:
        /*!
         * \brief Constructs a QVariantPropertyItem for a specific Q_PROPERTY.
         *
         * \param[in] value        Initial value read from the underlying QObject
         *                         (typically via \a metaProperty.read()).
         * \param[in] metaProperty The QMetaProperty descriptor for this property.
         * \param[in] parent       The class-level property item that owns this leaf.
         */
        QVariantPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem* parent);

        /*!
         * \brief Destroys this item.
         */
        virtual ~QVariantPropertyItem();

        /*!
         * \brief Returns display/decoration data for the given column and role.
         *
         * \details Column 0 returns the property name (and optionally a status
         * icon for read-only properties).  Column 1 returns the current value
         * formatted as a string for Qt::DisplayRole or the raw QVariant for
         * Qt::EditRole.
         *
         * \param[in] column  Target column (0 = Property, 1 = Value).
         * \param[in] role    Qt item-data role.
         * \returns The requested data, or an invalid QVariant.
         */
        QVariant data(int column = 1, Qt::ItemDataRole role = Qt::UserRole) const override;

        /*!
         * \brief Writes a new value to the underlying QObject.
         *
         * \details Calls QMetaProperty::write() on the owning QObject.  If the
         * write fails a qWarning() is emitted and \c false is returned.  On
         * success emits valueChanged().
         *
         * \param[in] value  New value to apply.
         * \param[in] role   Qt item-data role (typically Qt::EditRole).
         * \returns \c true if the write succeeded; \c false otherwise.
         */
        bool setData(const QVariant& value, Qt::ItemDataRole role = Qt::UserRole) override;

        /*!
         * \brief Invokes the Q_PROPERTY RESET function (if declared) to restore
         *        the default value, then synchronises the stored value.
         */
        void resetData() override;

        /*!
         * \brief Returns the QMetaProperty descriptor associated with this item.
         * \returns The QMetaProperty for this property.
         */
        QMetaProperty metaProperty() const;

    protected:
        QMetaProperty             m_metaProperty; /*!< \brief Descriptor of the reflected Q_PROPERTY. */
        QObjectClassPropertyItem* m_parent;        /*!< \brief Owning class-level item; used to resolve the QObject. */

};

Q_DECLARE_METATYPE(QVariantPropertyItem*)

#endif // QVARIANTPROPERTYITEM_H
