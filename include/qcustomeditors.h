/*!
 * \file qcustomeditors.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Custom QWidget editor classes used by QPropertyItemDelegate.
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

#ifndef QCUSTOMEDITORS_H
#define QCUSTOMEDITORS_H

#include <QDebug>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMetaProperty>
#include <QDialog>
#include <QComboBox>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QRect>
#include <QByteArray>
#include "qpropertyitem.h"
#include "qpropertyitemdelegate.h"
#include "qpropertymodel_global.h"
#include "qvariantholderhelper.h"



extern int m_windowState;
extern QByteArray m_state;
extern QRect m_geometry;

class QPropertyModel;

namespace Ui {
   class QStringListPropertyItemEditor;
   class QCustomObjectListPropertyItemEditor;
   class QPalettePropertyItemEditor;
}


/*!
 * \brief A QDoubleSpinBox that accepts all keyboard input without event filtering.
 *
 * \details Overrides the default step/key behaviour to be more suitable for
 * property-browser delegate editors embedded in a QTreeView.
 */
class QCustomDoubleSpinBox : public QDoubleSpinBox
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the spin-box with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QCustomDoubleSpinBox(QWidget *parent);

      ~QCustomDoubleSpinBox(){}

};

/*!
 * \brief A QSpinBox configured for in-delegate use in a property browser.
 *
 * \details Provides a full-range integer spin-box suitable for
 * property-browser delegate editors, matching Qt Creator behaviour.
 */
class QCustomSpinBox : public QSpinBox
{
      Q_OBJECT

   public:
      QCustomSpinBox(QWidget *parent);

      ~QCustomSpinBox(){}

};

/*!
 * \brief A QDateTimeEdit configured for in-delegate use in a property browser.
 */
class QCustomDateTimeEdit : public QDateTimeEdit
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QCustomDateTimeEdit(QWidget *parent);

      ~QCustomDateTimeEdit(){}

};

/*!
 * \brief A QDateEdit configured for in-delegate use in a property browser.
 */
class QCustomDateEdit : public QDateEdit
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QCustomDateEdit(QWidget *parent);

      ~QCustomDateEdit(){}
};

/*!
 * \brief A QTimeEdit configured for in-delegate use in a property browser.
 */
class QCustomTimeEdit : public QTimeEdit
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QCustomTimeEdit(QWidget *parent);

      ~QCustomTimeEdit(){}

};

/*!
 * \brief Base class for all property item editors used by QPropertyItemDelegate.
 *
 * \details Provides a uniform interface for in-place editors inside a QTreeView.
 * Each editor wraps a child widget (e.g. QComboBox, QPushButton) and exposes
 * a \c Value Q_PROPERTY that the delegate reads and writes via QAbstractItemDelegate
 * callbacks.  Optionally includes a reset button that restores the property to
 * its default value.
 *
 * Subclasses override setValue()/getValue() and setUpChildWidget() to provide
 * type-specific behaviour.  The valueChanged() signal is connected to the
 * delegate's commitData()/closeEditor() logic.
 */
class QPROPERTYMODEL_EXPORT QBasePropertyItemEditor : public QWidget
{
      Q_OBJECT
      Q_PROPERTY(QVariant Value READ getValue WRITE setValue NOTIFY valueChanged USER true)

   public:
      /*!
       * \brief Enumerates the special editor sub-types.
       *
       * \details Controls minor behavioural variations in QSelectFromListPropertyItemEditor
       * for enum vs. font-family selection.
       */
      enum ItemType
      {
         Enum,    /*!< \brief Editor is presenting a QMetaEnum-backed combo-box. */
         Font,    /*!< \brief Editor is presenting a font-family combo-box. */
         Unknown  /*!< \brief Editor type is unspecified or does not require special handling. */
      };

   public:
      /*!
       * \brief Constructs a bare editor shell without a child widget.
       *
       * \param[in] parent The parent widget (typically the viewport of the QTreeView).
       */
      QBasePropertyItemEditor(QWidget *parent);

      /*!
       * \brief Constructs an editor wrapping an existing \a childEditor widget.
       *
       * \param[in] childEditor   The widget to embed as the editing control.
       * \param[in] propertyItem  The property item being edited; used to wire the reset button.
       * \param[in] parent        The parent widget.
       */
      QBasePropertyItemEditor(QWidget* childEditor,  QPropertyItem* propertyItem, QWidget *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QBasePropertyItemEditor();

      /*!
       * \brief Associates \a propertyItem with this editor.
       *
       * \details Sets up the reset button's enable state based on
       * QPropertyItem::canReset() and stores the item pointer for getValue()/setValue().
       *
       * \param[in] propertyItem The property item this editor represents.  Must not be null.
       */
      void setPropertyItem(QPropertyItem* const propertyItem);

      /*!
       * \brief Sets the editor's current \a value.
       *
       * \details Called by QPropertyItemDelegate::setEditorData() to initialise the
       * editor before it becomes visible.  The default implementation stores the
       * value in m_value; subclasses should override to push it into the child widget.
       *
       * \param[in] value The value to display in the editor.
       */
      virtual void setValue(const QVariant& value);

      /*!
       * \brief Returns the editor's current value.
       *
       * \details Called by QPropertyItemDelegate::setModelData().  The default
       * implementation returns m_value; subclasses should override to read back
       * the current state of the child widget.
       *
       * \returns The current value as a QVariant.
       */
      virtual QVariant getValue() const;

   protected:
      /*!
       * \brief Handles focus-out events to commit the current value.
       *
       * \details Emits valueChanged() when the editor loses focus so the delegate
       * knows to commit and close the editor.
       *
       * \param[in] event The focus event.
       */
      void focusOutEvent(QFocusEvent * event) override;
      bool event(QEvent * event) override;

   private:
      /*!
       * \brief Creates and configures the child editor widget.
       *
       * \details Called from the constructor.  Subclasses must override to
       * instantiate and lay out their specific child widget.
       */
      virtual void setUpChildWidget();

   private slots:
      /*!
       * \brief Slot connected to the reset push-button's clicked() signal.
       *
       * \details Restores the property to its reset value via
       * QPropertyItem::resetData() and emits valueChanged() to notify the delegate.
       */
      void onRefresh();

   signals:
      /*!
       * \brief Emitted when the editor's value changes.
       *
       * \details QPropertyItemDelegate connects this signal to commitData() so the
       * model is updated immediately on each edit.
       *
       * \param[out] widget This editor widget (\c this), forwarded to the delegate.
       */
      void valueChanged(QWidget* widget);

   protected:
      QVariant        m_value;           /*!< The current editor value, synced with the child widget. */
      QPropertyItem*  m_propertyItem;    /*!< The property item this editor is bound to. */
      QPushButton*    m_resetPushButton; /*!< Optional reset-to-default button (may be null). */
      QWidget*        m_editorWidget;    /*!< The type-specific child editing widget. */
      QMetaProperty   m_valueProperty;   /*!< Meta-property descriptor for the Value Q_PROPERTY. */
      ItemType        m_itemType;        /*!< Sub-type hint for specialised editor behaviour. */
      bool            m_dialogOpen;      /*!< Guard flag to suppress focusOut while a modal dialog is open. */
};

/*!
 * \brief Editor that presents a QComboBox populated with a list of enumeration
 * keys or font family names.
 *
 * \details Used by QPropertyItemDelegate for QEnumPropertyItem and
 * QFontFamilyPropertyItem.  When ItemType is Enum the combo-box is populated
 * from a QMetaEnum; when ItemType is Font it is populated from QFontDatabase.
 */
class QPROPERTYMODEL_EXPORT QSelectFromListPropertyItemEditor : public QBasePropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the combo-box editor with the given \a parent.
       *
       * \param[in] parent The parent widget (typically the QTreeView viewport).
       */
      QSelectFromListPropertyItemEditor(QWidget *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QSelectFromListPropertyItemEditor();

      /*!
       * \brief Sets the current selection to \a value.
       *
       * \details Looks up the combo-box row that matches the integer enum value
       * or the font family string and selects it.
       *
       * \param[in] value The enum integer or font-family string as a QVariant.
       */
      virtual void setValue(const QVariant& value) override;

      /*!
       * \brief Returns the currently selected value.
       *
       * \details Returns the integer enum value or the selected font-family string
       * corresponding to the current combo-box selection.
       *
       * \returns The selected value as a QVariant.
       */
      virtual QVariant getValue() const override;

   private:
      /*!
       * \brief Creates the internal QComboBox and populates it appropriately.
       */
      void setUpChildWidget() override;

   private slots:
      /*!
       * \brief Slot invoked when the combo-box selection changes.
       *
       * \details Stores the new selection and emits valueChanged() to trigger
       * immediate model commit.
       *
       * \param[in] index The new zero-based combo-box index.
       */
      void onCurrentIndexChanged(int index);

   private:
      QComboBox*  m_comboBox;   /*!< The embedded QComboBox selection widget. */
      QStringList m_fontFamily; /*!< Font family names (valid when ItemType == Font). */
      bool        isEnum;       /*!< \c true when this editor represents a QMetaEnum. */
      QMetaEnum   m_metaEnum;   /*!< The QMetaEnum used to populate the combo-box (valid when isEnum). */
};

/*!
 * \brief Base editor that opens a separate dialog window for complex type editing.
 *
 * \details When the user activates this editor a push-button is shown.  Clicking
 * it calls onOpenEditorClicked() which opens a modal QDialog subclass tailored
 * to the specific property type (colour picker, string-list editor, etc.).
 * Subclasses override onOpenEditorClicked() to display their specific dialog.
 */
class QPROPERTYMODEL_EXPORT QPopUpPropertyItemEditor : public QBasePropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the popup editor with the given \a parent.
       *
       * \param[in] parent The parent widget (typically the QTreeView viewport).
       */
      QPopUpPropertyItemEditor(QWidget *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QPopUpPropertyItemEditor();

      /*!
       * \brief Returns the current value retrieved from the popup dialog.
       *
       * \details Subclasses read the dialog result here and return it as a QVariant.
       *
       * \returns The current value as a QVariant.
       */
      QVariant getValue() const override;

   private slots:
      /*!
       * \brief Slot invoked when the open-editor push-button is clicked.
       *
       * \details The default implementation does nothing; subclasses override this
       * to show their type-specific dialog and update m_value with the result.
       */
      virtual void onOpenEditorClicked();

   protected:
      QDialog* m_editorDialog; /*!< The modal dialog displayed when the button is clicked. */

   private:
      QPushButton* m_openEditorButton; /*!< The push-button that triggers the popup dialog. */

};

/*!
 * \brief Popup editor for QStringList properties.
 *
 * \details Opens a dialog with an editable list widget allowing strings to be
 * added, removed, reordered, and copied.  A right-click context menu provides
 * convenient access to the same operations.
 */
class QPROPERTYMODEL_EXPORT QStringListPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the string-list editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QStringListPropertyItemEditor(QWidget *parent = 0);

      /*!
       * \brief Destructor.
       */
      virtual ~QStringListPropertyItemEditor();

      /*!
       * \brief Populates the list widget with the strings from \a value.
       *
       * \param[in] value A QStringList wrapped in a QVariant.
       */
      void setValue(const QVariant& value) override;

      /*!
       * \brief Returns the current list of strings as a QVariant.
       *
       * \returns The edited QStringList wrapped in a QVariant.
       */
      QVariant getValue() const override;

   private:
      void setUpChildWidget() override;

   private slots:
      void customContextMenuRequested(const QPoint & pos);
      void add();
      void remove();
      void close();
      void onCopy();

   private:
      Ui::QStringListPropertyItemEditor* ui;          /*!< Generated UI layout for the editor dialog. */
      QStringListModel*                  m_model;     /*!< Backing model for the list view. */
      QMenu*                             m_contextMenu; /*!< Right-click menu for add/remove/copy. */
      bool                               m_canEdit;   /*!< Whether the list is editable. */
      QStringList                        m_list;      /*!< The current list of strings. */

};


/*!
 * \brief Popup editor for QList<QObject*> properties.
 *
 * \details Opens a two-panel dialog: the left panel lists the objects by name;
 * the right panel shows a nested QPropertyModel for the currently selected
 * object, allowing each object's properties to be edited in place.
 * New objects can be added via the factory mechanism registered with
 * QObjectListPropertyItem, and existing objects can be removed.
 */
class  QPROPERTYMODEL_EXPORT QObjectListPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the object-list editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QObjectListPropertyItemEditor(QWidget* parent = 0);

      /*!
       * \brief Destructor.
       */
      virtual ~QObjectListPropertyItemEditor();

      /*!
       * \brief Populates the editor with the list of objects from \a value.
       *
       * \param[in] value A QList<QObject*> wrapped in a QVariant.
       */
      void setValue(const QVariant& value) override;

      /*!
       * \brief Returns the current list of objects as a QVariant.
       *
       * \returns The edited QList<QObject*> wrapped in a QVariant.
       */
      QVariant getValue() const override;

   private:

      void setUpChildWidget() override;


   private slots:

      /*!
       * \brief Slot invoked when the user clicks an object in the left panel.
       *
       * \details Loads the selected object into the right-panel QPropertyModel.
       *
       * \param[in] index The model index of the clicked item.
       */
      void onItemClicked(const QModelIndex& index);

      /*!
       * \brief Slot invoked when the "Add" button is clicked.
       *
       * \details Creates a new object via the registered factory and appends it
       * to the list.  The new object is immediately selected in the left panel.
       */
      void onAddNewObject();

      /*!
       * \brief Slot invoked when the "Remove" button is clicked.
       *
       * \details Removes the currently selected object from the list.  The
       * removed object is deleted if this editor owns it.
       */
      void onRemoveObject();

      /*!
       * \brief Slot invoked when the dialog is closed.
       *
       * \details Emits valueChanged() so the model is updated with the
       * final list of objects before the editor is destroyed.
       */
      void close();

   protected:
      Ui::QCustomObjectListPropertyItemEditor* ui;      /*!< Generated UI for the two-panel dialog. */
      QPropertyModel*           m_propertyModel;        /*!< Model for the right-panel property editor. */
      QPropertyItemDelegate*    m_propertyModelDelegate;/*!< Delegate for the right-panel tree view. */
      QStandardItemModel*       m_objectListModel;      /*!< Backing model for the left-panel object list. */
      QList<QObject*>           m_values;               /*!< Current list of QObject pointers. */
      QModelIndex               m_currentlySelected;    /*!< Index of the currently selected object. */
};


/*!
 * \brief Popup editor for QVariantList properties.
 *
 * \details Opens a two-panel dialog similar to QObjectListPropertyItemEditor.
 * The left panel lists variants; the right panel shows a nested QPropertyModel
 * for the currently selected variant.  Variants can be added or removed.
 */
class QVariantListPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the variant-list editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QVariantListPropertyItemEditor(QWidget* parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QVariantListPropertyItemEditor();

      /*!
       * \brief Populates the editor with the variants from \a value.
       *
       * \param[in] value A QVariantList wrapped in a QVariant.
       */
      void setValue(const QVariant& value) override;

      /*!
       * \brief Returns the current list of variants as a QVariant.
       *
       * \returns The edited QVariantList wrapped in a QVariant.
       */
      QVariant getValue() const override;

   private:

      void setUpChildWidget() override;


   private slots:

      void onItemClicked(const QModelIndex& index);

      void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int> ());

      void onAddQVariant();

      void onRemoveQVariant();

      void close();

   private:
      Ui::QCustomObjectListPropertyItemEditor* ui;    /*!< Generated UI for the dialog. */
      QPropertyModel*      m_propertyModel;           /*!< Model for the right-panel property editor. */
      QStandardItemModel*  m_variantModel;            /*!< Backing model for the left-panel list. */
      QList<QVariant>      m_values;                  /*!< Current list of variant values. */
      QVariantHolderHelper* m_variantHolder;          /*!< Helper wrapping the selected variant as a QObject. */
      QModelIndex          m_currentlySelected;       /*!< Index of the currently selected variant. */
};

/*!
 * \brief Popup editor for QImage, QPixmap, and QBitmap properties.
 *
 * \details Opens a file-browser dialog so the user can select an image file.
 * The loaded image is converted to the appropriate type (QImage, QPixmap, or
 * QBitmap) and stored as the editor value.
 */
class QImagePropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the image browser editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QImagePropertyItemEditor(QWidget *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QImagePropertyItemEditor();

      /*!
       * \brief Sets the initial image \a value displayed in the editor.
       *
       * \param[in] value The current image wrapped in a QVariant.  Also records
       *                   the QMetaType used so the result is returned as the
       *                   same image type.
       */
      void setValue(const QVariant& value) override;

      /*!
       * \brief Returns the edited image value.
       *
       * \returns The loaded image (QImage, QPixmap, or QBitmap) wrapped in a QVariant.
       */
      QVariant getValue() const override;

   private slots:
      /*!
       * \brief Opens a file dialog and loads the selected image.
       *
       * \details Detects the image type (QImage / QPixmap / QBitmap) from
       * m_imageType and stores the loaded image as m_value.
       */
      void onOpenEditorClicked() override;

   private:
      void setUpChildWidget() override;

      QMetaType::Type m_imageType; /*!< The concrete image sub-type (QImage, QPixmap, or QBitmap). */

};

/*!
 * \brief Popup editor that opens a QColorDialog for QColor properties.
 *
 * \details When the push-button is clicked a native QColorDialog opens.
 * On acceptance the chosen colour is stored as the editor value and
 * valueChanged() is emitted so the model is updated immediately.
 */
class QColorPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the colour picker editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QColorPropertyItemEditor(QWidget *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QColorPropertyItemEditor();

      /*!
       * \brief Sets the initial colour \a value displayed in the editor button.
       *
       * \param[in] value The current QColor wrapped in a QVariant.
       */
      void setValue(const QVariant& value) override;

   private slots:
      /*!
       * \brief Slot invoked when the QColorDialog is accepted.
       *
       * \details Stores the accepted QColor as m_value and emits valueChanged().
       */
      void onColorAccepted();


};

/*!
 * \brief Popup editor that opens a QFontDialog for QFont properties.
 *
 * \details When the push-button is clicked a native QFontDialog opens.
 * On acceptance the chosen font is stored as the editor value and
 * valueChanged() is emitted so the model is updated immediately.
 */
class QFontPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the font picker editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QFontPropertyItemEditor(QWidget *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QFontPropertyItemEditor();

      /*!
       * \brief Sets the initial font \a value displayed in the editor button.
       *
       * \param[in] value The current QFont wrapped in a QVariant.
       */
      void setValue(const QVariant& value) override;

   private slots:
      /*!
       * \brief Slot invoked when the QFontDialog is accepted.
       *
       * \details Stores the accepted QFont as m_value and emits valueChanged().
       */
      void onColorAccepted();

};

/*!
 * \brief Dropdown editor for QCursor properties with visual cursor display.
 *
 * \details Displays a QComboBox with all standard Qt cursor shapes.
 * Shows both the cursor icon and name in the dropdown.
 */
class QPROPERTYMODEL_EXPORT QCursorPropertyItemEditor : public QBasePropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the cursor editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QCursorPropertyItemEditor(QWidget *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QCursorPropertyItemEditor();

      /*!
       * \brief Sets the initial cursor \a value displayed in the editor.
       *
       * \param[in] value The current QCursor wrapped in a QVariant.
       */
      void setValue(const QVariant& value) override;

      /*!
       * \brief Returns the currently selected cursor value.
       *
       * \returns The selected QCursor wrapped in a QVariant.
       */
      QVariant getValue() const override;

   private slots:
      void onCurrentIndexChanged(int index);

   private:
      void setUpChildWidget() override;

      QComboBox* m_comboBox;

};

/*!
 * \brief Popup editor that opens a palette editor dialog for QPalette properties.
 *
 * \details When the push-button is clicked a comprehensive dialog opens showing
 * all palette color roles organized by color group (Active, Inactive, Disabled).
 * Supports editing all standard color roles with visual color preview buttons.
 */
class QPROPERTYMODEL_EXPORT QPalettePropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      /*!
       * \brief Constructs the palette editor with the given \a parent.
       *
       * \param[in] parent The parent widget.
       */
      QPalettePropertyItemEditor(QWidget *parent);

      /*!
       * \brief Destructor.
       */
      virtual ~QPalettePropertyItemEditor();

      /*!
       * \brief Sets the initial palette \a value displayed in the editor.
       *
       * \param[in] value The current QPalette wrapped in a QVariant.
       */
      void setValue(const QVariant& value) override;

   private slots:
      void onOpenEditorClicked() override;

   private:
      void setUpChildWidget() override;
      void populateColorRole(QPalette::ColorGroup group, QPalette::ColorRole role, 
                            const QString& name, QGridLayout* layout, int row);
      void setupColorButtons(QDialog* dialog, QPalette& palette);

      struct ColorButton {
         QPushButton* button;
         QPalette::ColorGroup group;
         QPalette::ColorRole role;
      };
      
      QList<ColorButton> m_colorButtons;

};

#endif // QCUSTOMEDITORS_H
