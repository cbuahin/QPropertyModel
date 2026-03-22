/*!
 * \file qpropertymodel_global.h
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description
 * Export macro definitions for the QPropertyModel shared library.
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

#ifndef QPROPERTYMODEL_GLOBAL_H
#define QPROPERTYMODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef QPROPERTYMODEL_LIBRARY
# define QPROPERTYMODEL_EXPORT Q_DECL_EXPORT
#else
# define QPROPERTYMODEL_EXPORT Q_DECL_IMPORT
#endif

#endif // QPROPERTYMODEL_GLOBAL_H
