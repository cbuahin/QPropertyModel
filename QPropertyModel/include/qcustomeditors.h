#ifndef QCUSTOMEDITORS_H
#define QCUSTOMEDITORS_H

#include <QDebug>
#include <QDoubleSpinBox>
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
}


class QCustomDoubleSpinBox : public QDoubleSpinBox
{
      Q_OBJECT

   public:
      QCustomDoubleSpinBox(QWidget *parent);

      ~QCustomDoubleSpinBox(){}

};

class QCustomDateTimeEdit : public QDateTimeEdit
{
      Q_OBJECT

   public:
      QCustomDateTimeEdit(QWidget *parent);

      ~QCustomDateTimeEdit(){}

};

class QCustomDateEdit : public QDateEdit
{
      Q_OBJECT

   public:
      QCustomDateEdit(QWidget *parent);

      ~QCustomDateEdit(){}
};

class QCustomTimeEdit : public QTimeEdit
{
      Q_OBJECT

   public:
      QCustomTimeEdit(QWidget *parent);

      ~QCustomTimeEdit(){}

};

class QPROPERTYMODEL_EXPORT QBasePropertyItemEditor : public QWidget
{
      Q_OBJECT
      Q_PROPERTY(QVariant Value READ getValue WRITE setValue NOTIFY valueChanged USER true)

   public:
      enum ItemType
      {
         Enum,
         Font,
         Unknown
      };

   public:
      QBasePropertyItemEditor(QWidget *parent);

      QBasePropertyItemEditor(QWidget* childEditor,  QPropertyItem* propertyItem, QWidget *parent);

      virtual ~QBasePropertyItemEditor();

      void setPropertyItem(QPropertyItem* const propertyItem);

      virtual void setValue(const QVariant& value);

      virtual QVariant getValue() const;

   protected:
      void focusOutEvent(QFocusEvent * event) override;

   private:
      virtual void setUpChildWidget();

   private slots:
      void onRefresh();

   signals:
      void valueChanged(QWidget* widget);

   protected:
      QVariant m_value;
      QPropertyItem*  m_propertyItem;
      QPushButton* m_resetPushButton;
      QWidget* m_editorWidget;
      QMetaProperty m_valueProperty;
      ItemType m_itemType;
};

class QPROPERTYMODEL_EXPORT QSelectFromListPropertyItemEditor : public QBasePropertyItemEditor
{
      Q_OBJECT

   public:
      QSelectFromListPropertyItemEditor(QWidget *parent);

      virtual ~QSelectFromListPropertyItemEditor();

      virtual void setValue(const QVariant& value) override;

      virtual QVariant getValue() const override;

   private:
      void setUpChildWidget() override;

   private slots:
      void onCurrentIndexChanged(int index);

   private:
      QComboBox* m_comboBox;
      QStringList m_fontFamily;
      bool isEnum;
      QMetaEnum m_metaEnum;
};

class QPROPERTYMODEL_EXPORT QPopUpPropertyItemEditor : public QBasePropertyItemEditor
{
      Q_OBJECT

   public:
      QPopUpPropertyItemEditor(QWidget *parent);

      virtual ~QPopUpPropertyItemEditor();


      QVariant getValue() const override;

   private slots:
      virtual void onOpenEditorClicked();

   protected:
      QDialog* m_editorDialog;

   private:
      QPushButton* m_openEditorButton;


};




class QPROPERTYMODEL_EXPORT QStringListPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      QStringListPropertyItemEditor(QWidget *parent = 0);

      virtual ~QStringListPropertyItemEditor();

      void setValue(const QVariant& value) override;

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
      Ui::QStringListPropertyItemEditor* ui;
      QStringListModel* m_model;
      QMenu* m_contextMenu;
      bool m_canEdit;
      QStringList m_list;

};




class  QPROPERTYMODEL_EXPORT QObjectListPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:

      QObjectListPropertyItemEditor(QWidget* parent = 0);

      virtual ~QObjectListPropertyItemEditor();

      void setValue(const QVariant& value) override;

      QVariant getValue() const override;

   private:

      void setUpChildWidget() override;


   private slots:

      void onItemClicked(const QModelIndex& index);

      void onAddNewObject();

      void onRemoveObject();

      void close();

   protected:
      Ui::QCustomObjectListPropertyItemEditor* ui;
      QPropertyModel* m_propertyModel;
      QPropertyItemDelegate* m_propertyModelDelegate;
      QStandardItemModel* m_objectListModel;
      QList<QObject*> m_values;
      QModelIndex m_currentlySelected;
};


class QVariantListPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:

      QVariantListPropertyItemEditor(QWidget* parent);

      virtual ~QVariantListPropertyItemEditor();

      void setValue(const QVariant& value) override;

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
      Ui::QCustomObjectListPropertyItemEditor* ui;
      QPropertyModel* m_propertyModel;
      QStandardItemModel* m_variantModel;
      QList<QVariant> m_values;
      QVariantHolderHelper* m_variantHolder;
      QModelIndex m_currentlySelected;
};

class QImagePropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:

      QImagePropertyItemEditor(QWidget *parent);

      virtual ~QImagePropertyItemEditor();

   private slots:

      void onOpenEditorClicked() override;

      void setUpChildWidget() override;

      void setValue(const QVariant& value) override;

      QVariant getValue() const override;

   private:
      QMetaType::Type m_imageType;

};

class QColorPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      QColorPropertyItemEditor(QWidget *parent);

      virtual ~QColorPropertyItemEditor();

      void setValue(const QVariant& value) override;

   private slots:

      void onColorAccepted();


};

class QFontPropertyItemEditor : public QPopUpPropertyItemEditor
{
      Q_OBJECT

   public:
      QFontPropertyItemEditor(QWidget *parent);

      virtual ~QFontPropertyItemEditor();

      void setValue(const QVariant& value) override;

   private slots:
      void onColorAccepted();

};

#endif // QCUSTOMEDITORS_H
