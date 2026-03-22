/*!
 * \file qpropertyitemdelegate.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * QStyledItemDelegate providing rich editors for the property model.
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

#ifndef QPROPERTYITEMDELEGATE_H
#define QPROPERTYITEMDELEGATE_H

#include "qpropertymodel_global.h"
#include <QStyledItemDelegate>
#include <QItemEditorFactory>

/*!
 * \brief QStyledItemDelegate providing rich inline and popup editors for QPropertyModel.
 *
 * \details QPropertyItemDelegate should always be used in conjunction with
 * QPropertyModel.  It creates a custom QItemEditorFactory on construction
 * that maps Qt metatypes to purpose-built editor widgets (colour chooser,
 * font picker, image browser, pen/brush editor, string-list editor, etc.).
 *
 * \details Usage pattern:
 * \code
 *   auto *model    = new QPropertyModel(myObject, this);
 *   auto *delegate = new QPropertyItemDelegate(this);
 *   treeView->setModel(model);
 *   treeView->setItemDelegate(delegate);
 * \endcode
 *
 * \details Extending with custom editors:
 * \code
 *   delegate->registerCustomTypeEditorCreator(
 *       QMetaType::Type(qMetaTypeId<MyType>()),
 *       new QStandardItemEditorCreator<MyTypeEditor>());
 * \endcode
 *
 * \sa QPropertyModel, QItemEditorFactory
 */
class QPROPERTYMODEL_EXPORT QPropertyItemDelegate : public QStyledItemDelegate
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the delegate and registers all built-in editor creators.
       *
       * \details Creates an internal QItemEditorFactory and registers editors
       * for QColor, QFont, QIcon, QImage, QPixmap, QPen, QBrush, QStringList,
       * QObjectList, and all other built-in property types.
       *
       * \param[in] parent  Parent QObject.
       */
      QPropertyItemDelegate(QObject* parent);

      /*!
       * \brief Destroys the delegate and its internal editor factory.
       */
      ~QPropertyItemDelegate();

      /*!
       * \brief Registers a custom editor creator for the given metatype.
       *
       * \details Allows third-party code to inject completely custom editor
       * widgets into the delegate's editor factory without subclassing the
       * delegate itself.  Ownership of \a creator is transferred to the
       * internal factory.
       *
       * \param[in] type     QMetaType identifier of the property type to
       *                     associate the editor with.
       * \param[in] creator  Creator instance; ownership is transferred.
       */
      void registerCustomTypeEditorCreator(QMetaType::Type type, QItemEditorCreatorBase* creator);

      /*!
       * \brief Creates the editor widget for the property at \a index.
       *
       * \details Looks up the metatype of the property item at \a index in the
       * internal factory and instantiates the corresponding editor widget.
       * Falls back to QStyledItemDelegate::createEditor() for unregistered types.
       *
       * \param[in] parent  Parent widget for the editor.
       * \param[in] option  Style options for the editor's visual context.
       * \param[in] index   Model index identifying the property being edited.
       * \returns A newly created editor widget, or \c nullptr.
       */
      QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                            const QModelIndex& index) const override;

      /*!
       * \brief Paints custom previews for QPen, QBrush, and QColor value cells.
       *
       * \details For supported types, renders a filled colour swatch or pen
       * stroke preview inline in the value column.  All other cells are
       * forwarded to QStyledItemDelegate::paint().
       *
       * \param[in] painter  Painter to draw with.
       * \param[in] option   Style options including the cell rectangle.
       * \param[in] index    Model index identifying the cell to paint.
       */
      void paint(QPainter* painter, const QStyleOptionViewItem& option,
                 const QModelIndex& index) const override;

      /*!
       * \brief Populates \a editor with the current value from \a index.
       *
       * \param[in] editor  The editor widget returned by createEditor().
       * \param[in] index   Model index from which to read the value.
       */
      void setEditorData(QWidget* editor, const QModelIndex& index) const override;

      /*!
       * \brief Writes the editor's current value back to the model.
       *
       * \param[in] editor  The editor widget whose value should be committed.
       * \param[in] model   The model to write to.
       * \param[in] index   Model index identifying the property to update.
       */
      void setModelData(QWidget* editor, QAbstractItemModel* model,
                        const QModelIndex& index) const override;

      /*!
       * \brief Returns the preferred size for the cell at \a index.
       *
       * \param[in] option  Style options for the cell.
       * \param[in] index   Model index of the cell.
       * \returns The recommended QSize for the cell.
       */
      QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

      /*!
       * \brief Positions and sizes the editor within the cell rectangle.
       *
       * \param[in] editor  The editor widget to reposition.
       * \param[in] option  Style options that include the cell geometry.
       * \param[in] index   Model index of the cell being edited.
       */
      void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                                const QModelIndex& index) const override;

   private slots:
      /*!
       * \brief Immediately commits editor data to the model on every value change.
       *
       * \details Connected to editor widgets that emit a valueChanged-style
       * signal, enabling live (non-commit-on-close) editing behaviour.
       *
       * \param[in] widget  The editor widget whose value changed.
       */
      void onEditorValueChanged(QWidget* widget);

};

#endif // QPROPERTYITEMDELEGATE_H
