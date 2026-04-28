/*!
 * \file qpropertymodeltesting.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Main window for the QPropertyModel manual UI test application.
 * Constructs a QPropertyModel loaded with a TempObject instance and
 * displays it in a QTreeView using QPropertyItemDelegate.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#ifndef QPROPERTYMODELTESTING_H
#define QPROPERTYMODELTESTING_H

#include <QMainWindow>
#include "ui_qpropertymodeltesting.h"

class QPropertyModel;

/*!
 * \brief Main window for the QPropertyModel manual UI test.
 *
 * On construction it creates a QPropertyModel loaded with a TempObject,
 * registers TempObjectPropertyItem and TempObjectListPropertyItem as custom
 * item types, and wires a QPropertyItemDelegate to the embedded QTreeView.
 * A toggle button switches between single-object and multi-object mode.
 */
class QPropertyModelTesting : public QMainWindow
{
   Q_OBJECT

public:
   explicit QPropertyModelTesting(QWidget* parent = nullptr);
   ~QPropertyModelTesting();

private slots:
   void onToggleMultiObject();

private:
   Ui::QPropertyModelTesting ui;
   QPropertyModel* m_model;
   QObject* m_tempObj1;
   QObject* m_tempObj2;
   bool m_multiMode;
};

#endif // QPROPERTYMODELTESTING_H
