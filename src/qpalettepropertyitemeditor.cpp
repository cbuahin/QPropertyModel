/*!
 * \file qpalettepropertyitemeditor.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of palette property editor with comprehensive UI.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include "qcustomeditors.h"
#include "ui_qpalettepropertyitemeditor.h"
#include <QColorDialog>
#include <QPalette>
#include <QApplication>

QPalettePropertyItemEditor::QPalettePropertyItemEditor(QWidget *parent)
   : QPopUpPropertyItemEditor(parent)
{

}

QPalettePropertyItemEditor::~QPalettePropertyItemEditor()
{

}

void QPalettePropertyItemEditor::setValue(const QVariant& value)
{
   m_value = value;
}

void QPalettePropertyItemEditor::setUpChildWidget()
{
   m_value = m_propertyItem->data(1, Qt::EditRole);
}

void QPalettePropertyItemEditor::onOpenEditorClicked()
{
   m_dialogOpen = true;
   
   // Create dialog with UI form
   QDialog dialog(this);
   Ui::QPalettePropertyItemEditor ui;
   ui.setupUi(&dialog);
   
   QPalette palette = qvariant_cast<QPalette>(m_value);
   QPalette newPalette = palette;
   QPalette defaultPalette = QApplication::palette();
   
   m_colorButtons.clear();
   
   // Define all color roles with their display names
   struct ColorRoleInfo {
      QPalette::ColorRole role;
      const char* name;
   };
   
   static const ColorRoleInfo roles[] = {
      {QPalette::WindowText, "Window Text"},
      {QPalette::Button, "Button"},
      {QPalette::Light, "Light"},
      {QPalette::Midlight, "Midlight"},
      {QPalette::Dark, "Dark"},
      {QPalette::Mid, "Mid"},
      {QPalette::Text, "Text"},
      {QPalette::BrightText, "Bright Text"},
      {QPalette::ButtonText, "Button Text"},
      {QPalette::Base, "Base"},
      {QPalette::Window, "Window"},
      {QPalette::Shadow, "Shadow"},
      {QPalette::Highlight, "Highlight"},
      {QPalette::HighlightedText, "Highlighted Text"},
      {QPalette::Link, "Link"},
      {QPalette::LinkVisited, "Link Visited"},
      {QPalette::AlternateBase, "Alternate Base"},
      {QPalette::ToolTipBase, "Tooltip Base"},
      {QPalette::ToolTipText, "Tooltip Text"},
      {QPalette::PlaceholderText, "Placeholder Text"}
   };
   
   // Populate all three tabs
   int row = 0;
   for (const auto& roleInfo : roles) {
      populateColorRole(QPalette::Active, roleInfo.role, roleInfo.name, 
                       ui.gridLayoutActive, row);
      populateColorRole(QPalette::Inactive, roleInfo.role, roleInfo.name, 
                       ui.gridLayoutInactive, row);
      populateColorRole(QPalette::Disabled, roleInfo.role, roleInfo.name, 
                       ui.gridLayoutDisabled, row);
      row++;
   }
   
   // Setup all color buttons with the current palette
   setupColorButtons(&dialog, newPalette);
   
   // Connect sync checkbox
   connect(ui.checkBoxSyncInactive, &QCheckBox::toggled, [&](bool checked) {
      ui.tabWidget->setTabEnabled(1, !checked);
   });
   
   // Connect reset button
   connect(ui.buttonResetToDefault, &QPushButton::clicked, [&]() {
      newPalette = defaultPalette;
      setupColorButtons(&dialog, newPalette);
   });
   
   // Connect color buttons
   for (auto& btnInfo : m_colorButtons) {
      connect(btnInfo.button, &QPushButton::clicked, [&, btnInfo]() {
         QColor currentColor = newPalette.color(btnInfo.group, btnInfo.role);
         QColor newColor = QColorDialog::getColor(currentColor, &dialog, tr("Select Color"));
         if (newColor.isValid()) {
            newPalette.setColor(btnInfo.group, btnInfo.role, newColor);
            
            // Sync inactive with active if checkbox is checked
            if (ui.checkBoxSyncInactive->isChecked() && btnInfo.group == QPalette::Active) {
               newPalette.setColor(QPalette::Inactive, btnInfo.role, newColor);
            }
            
            setupColorButtons(&dialog, newPalette);
         }
      });
   }
   
   m_dialogOpen = false;
   
   if (dialog.exec() == QDialog::Accepted) {
      m_value = QVariant::fromValue(newPalette);
      emit valueChanged(this);
   }
   
   m_colorButtons.clear();
}

void QPalettePropertyItemEditor::populateColorRole(QPalette::ColorGroup group, 
                                                    QPalette::ColorRole role,
                                                    const QString& name, 
                                                    QGridLayout* layout, 
                                                    int row)
{
   QLabel* label = new QLabel(name + ":");
   layout->addWidget(label, row, 0);
   
   QPushButton* colorButton = new QPushButton();
   colorButton->setFixedHeight(28);
   colorButton->setMinimumWidth(100);
   layout->addWidget(colorButton, row, 1);
   
   ColorButton btnInfo;
   btnInfo.button = colorButton;
   btnInfo.group = group;
   btnInfo.role = role;
   m_colorButtons.append(btnInfo);
}

void QPalettePropertyItemEditor::setupColorButtons(QDialog* dialog, QPalette& palette)
{
   for (const auto& btnInfo : m_colorButtons) {
      QColor color = palette.color(btnInfo.group, btnInfo.role);
      QString colorName = color.name();
      
      // Create a style with both background color and text color
      QString style = QString(
         "QPushButton { "
         "  background-color: %1; "
         "  color: %2; "
         "  border: 1px solid #888; "
         "  padding: 4px; "
         "}"
         "QPushButton:hover { "
         "  border: 2px solid #000; "
         "}"
      ).arg(colorName, 
            color.lightness() > 128 ? "#000000" : "#FFFFFF");
      
      btnInfo.button->setStyleSheet(style);
      btnInfo.button->setText(colorName);
   }
}
