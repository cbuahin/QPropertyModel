/*!
 * \file qvector2dpropertyitem.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Property item for QVector2D type with expandable X/Y children.
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

#ifndef QVECTOR2DPROPERTYITEM_H
#define QVECTOR2DPROPERTYITEM_H

#include "qvariantpropertyItem.h"

/*!
 * \brief Property item for QVector2D with expandable X and Y components.
 *
 * \details The value column displays the vector as \c "(x, y)" with
 * floating-point precision.  Expanding the item reveals two double spin-box
 * children labelled \b X and \b Y.  Changes to either child are aggregated
 * and written back to the underlying QMetaProperty.
 */
class QVector2DPropertyItem : public QVariantPropertyItem
{
	Q_OBJECT

public:
	/*!
	 * \brief Constructs a 2D vector property item.
	 *
	 * \param[in] value        The initial QVector2D value wrapped in a QVariant.
	 * \param[in] metaProperty The meta-property this item represents on the parent QObject.
	 * \param[in] parent       The QObjectClassPropertyItem that owns this item.
	 */
	QVector2DPropertyItem(const QVariant& value, const QMetaProperty& metaProperty, QObjectClassPropertyItem * parent);

	/*!
	 * \brief Destructor.
	 */
	virtual ~QVector2DPropertyItem();

	/*!
	 * \brief Returns display/edit data for the given \a column and \a role.
	 *
	 * \details For column 1, Qt::DisplayRole returns \c "(x, y)".
	 * Qt::EditRole returns the raw QVector2D wrapped in a QVariant.
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
	 * \details Returns Qt::ItemIsEnabled | Qt::ItemIsSelectable.
	 * Individual components are edited through their child items.
	 *
	 * \returns Item flags for this node.
	 */
	Qt::ItemFlags flags() const override;


protected:
	/*!
	 * \brief Populates or refreshes the X and Y child items.
	 *
	 * \details Called automatically on first access and whenever the vector
	 * value changes, keeping children in sync.
	 */
	void setChildValues() override;

	private slots:
	/*!
	 * \brief Slot invoked when an X or Y child value changes.
	 *
	 * \details Re-assembles the QVector2D from the current child values and
	 * writes the updated vector to the underlying QMetaProperty.
	 *
	 * \param[in] name  The child property name (\c "X" or \c "Y").
	 * \param[in] value The new floating-point component value.
	 */
	void onChildItemValueChanged(const QString& name, const QVariant& value);

private:
	bool m_isSettingChildren; /*!< Guard flag to prevent recursive child-update loops. */

};

#endif // QVECTOR2DPROPERTYITEM_H
