/*!
 * \file qvariantholderhelper.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Helper QObject wrapping a plain QVariant as a reflectable property.
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

#ifndef QVARIANTHOLDERHELPER_H
#define QVARIANTHOLDERHELPER_H

#include "qpropertymodel_global.h"
#include <QVariant>
#include <QModelIndex>
#include "qobjectpropertyitem.h"

/*!
 * \brief QObject wrapper that exposes a plain QVariant as a reflectable property.
 *
 * \details QPropertyModel uses this helper when setData() receives a plain QVariant
 * (i.e. not a QObject pointer or a custom-registered type).  It wraps the
 * value in a synthesised QObject with a single Q_PROPERTY so the model can
 * display it using the standard QObjectClassPropertyItem mechanism.
 *
 * The modelIndex() / setModelIndex() pair allows the model to map this helper
 * back to the original item index for update propagation.
 *
 * \note This class is an implementation detail of QPropertyModel.
 * It is exported only to support unit testing and should not be used directly
 * by application code.
 *
 * \warning This class uses a Q_PROPERTY named \c Value; do not register
 * QVariantHolderHelper as a custom property type with QPropertyModel.
 */
class QPROPERTYMODEL_EXPORT QVariantHolderHelper : public QObject
{
      Q_OBJECT
      Q_PROPERTY(QVariant Value READ value WRITE setValue NOTIFY valueChanged)

   public:
      /*!
       * \brief Constructs the helper with an initial \a value.
       *
       * \param[in] value  The initial QVariant value to wrap.
       * \param[in] parent Optional QObject parent for memory management.
       */
      QVariantHolderHelper(const QVariant& value, QObject* parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QVariantHolderHelper();

      /*!
       * \brief Returns the currently stored value.
       *
       * \returns The current QVariant value.
       */
      QVariant value() const;

      /*!
       * \brief Sets a new value and emits valueChanged() if the value has changed.
       *
       * \details This is the write accessor for the \c Value Q_PROPERTY.  It is
       * called by QPropertyModel whenever the user edits the value in the view.
       *
       * \param[in] value The new QVariant value to store.
       */
      void setValue(const QVariant& value);

      /*!
       * \brief Returns the model index associated with this helper.
       *
       * \details The model stores the index of the item that owns this helper
       * so it can locate and update the correct row when the value changes.
       *
       * \returns The QModelIndex pointing to the owning item in QPropertyModel.
       */
      QModelIndex modelIndex() const;

      /*!
       * \brief Associates this helper with a model \a index.
       *
       * \details Called by QPropertyModel when this helper is installed as the
       * data source for a specific item.
       *
       * \param[in] index The QModelIndex of the owning item.
       */
      void setModelIndex(const QModelIndex& index);

   private:
      /*!
       * \brief Returns an empty string.
       *
       * \details Overrides QObject::objectName() to prevent the object name
       * from appearing as an extra property in the model.
       *
       * \returns An empty QString.
       */
      QString objectName() const;

   signals:
      /*! \brief Emitted whenever the stored value is changed via setValue(). */
      void valueChanged();

   private:
      QVariant    m_value; /*!< The wrapped QVariant value. */
      QModelIndex m_index; /*!< The model index of the owning QPropertyItem. */
};





#endif // QVARIANTHOLDERHELPER_H
