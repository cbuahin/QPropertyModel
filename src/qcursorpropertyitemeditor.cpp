/*!
 * \file qcursorpropertyitemeditor.cpp
 * \author Caleb Buahin <caleb.buahin@gmail.com>
 * \version 1.0.0
 * \description Implementation of cursor property editor.
 * \license
 * This file is part of QPropertyModel.
 * Copyright (c) 2014-2026 Caleb Buahin. All rights reserved.
 * SPDX-License-Identifier: MIT
 * See License.md for the full license text.
 */

#include "qcustomeditors.h"
#include <QCursor>
#include <QPixmap>
#include <QPainter>
#include <QIcon>
#include <QPainterPath>

namespace {

QPixmap drawCursorIcon(Qt::CursorShape shape)
{
   const int sz = 24;
   QPixmap pixmap(sz, sz);
   pixmap.fill(Qt::transparent);
   QPainter p(&pixmap);
   p.setRenderHint(QPainter::Antialiasing);

   auto drawArrow = [&](const QPolygonF& poly) {
      QPainterPath path;
      path.addPolygon(poly);
      path.closeSubpath();
      p.setPen(QPen(Qt::black, 1));
      p.setBrush(Qt::white);
      p.drawPath(path);
   };

   switch (shape) {
   case Qt::ArrowCursor: {
      // Classic pointer arrow
      QPolygonF arrow;
      arrow << QPointF(4, 2) << QPointF(4, 18) << QPointF(8, 14)
            << QPointF(12, 20) << QPointF(14, 19) << QPointF(10, 13)
            << QPointF(15, 13) << QPointF(4, 2);
      drawArrow(arrow);
      break;
   }
   case Qt::UpArrowCursor: {
      QPolygonF arrow;
      arrow << QPointF(12, 2) << QPointF(6, 12) << QPointF(10, 12)
            << QPointF(10, 22) << QPointF(14, 22) << QPointF(14, 12)
            << QPointF(18, 12) << QPointF(12, 2);
      drawArrow(arrow);
      break;
   }
   case Qt::CrossCursor: {
      p.setPen(QPen(Qt::black, 2));
      p.drawLine(12, 2, 12, 22);
      p.drawLine(2, 12, 22, 12);
      break;
   }
   case Qt::WaitCursor: {
      // Hourglass
      p.setPen(QPen(Qt::black, 1.5));
      p.setBrush(QBrush(QColor(200, 200, 200)));
      QPolygonF top;
      top << QPointF(5, 3) << QPointF(19, 3) << QPointF(12, 12) << QPointF(5, 3);
      QPolygonF bot;
      bot << QPointF(5, 21) << QPointF(19, 21) << QPointF(12, 12) << QPointF(5, 21);
      p.drawPolygon(top);
      p.setBrush(QBrush(QColor(120, 120, 120)));
      p.drawPolygon(bot);
      break;
   }
   case Qt::IBeamCursor: {
      p.setPen(QPen(Qt::black, 1.5));
      p.drawLine(8, 3, 16, 3);
      p.drawLine(12, 3, 12, 21);
      p.drawLine(8, 21, 16, 21);
      break;
   }
   case Qt::SizeVerCursor: {
      // Vertical double arrow
      p.setPen(QPen(Qt::black, 1.5));
      p.setBrush(Qt::white);
      // Up arrowhead
      QPolygonF up;
      up << QPointF(12, 2) << QPointF(7, 8) << QPointF(17, 8);
      p.drawPolygon(up);
      // Down arrowhead
      QPolygonF dn;
      dn << QPointF(12, 22) << QPointF(7, 16) << QPointF(17, 16);
      p.drawPolygon(dn);
      // Shaft
      p.drawLine(12, 8, 12, 16);
      break;
   }
   case Qt::SizeHorCursor: {
      p.setPen(QPen(Qt::black, 1.5));
      p.setBrush(Qt::white);
      QPolygonF lt;
      lt << QPointF(2, 12) << QPointF(8, 7) << QPointF(8, 17);
      p.drawPolygon(lt);
      QPolygonF rt;
      rt << QPointF(22, 12) << QPointF(16, 7) << QPointF(16, 17);
      p.drawPolygon(rt);
      p.drawLine(8, 12, 16, 12);
      break;
   }
   case Qt::SizeBDiagCursor: {
      // Backslash diagonal double arrow (top-right to bottom-left)
      p.setPen(QPen(Qt::black, 1.5));
      p.setBrush(Qt::white);
      QPolygonF tr;
      tr << QPointF(19, 3) << QPointF(13, 3) << QPointF(19, 9);
      p.drawPolygon(tr);
      QPolygonF bl;
      bl << QPointF(5, 21) << QPointF(11, 21) << QPointF(5, 15);
      p.drawPolygon(bl);
      p.drawLine(17, 7, 7, 17);
      break;
   }
   case Qt::SizeFDiagCursor: {
      // Forward diagonal double arrow (top-left to bottom-right)
      p.setPen(QPen(Qt::black, 1.5));
      p.setBrush(Qt::white);
      QPolygonF tl;
      tl << QPointF(5, 3) << QPointF(11, 3) << QPointF(5, 9);
      p.drawPolygon(tl);
      QPolygonF br;
      br << QPointF(19, 21) << QPointF(13, 21) << QPointF(19, 15);
      p.drawPolygon(br);
      p.drawLine(7, 7, 17, 17);
      break;
   }
   case Qt::SizeAllCursor: {
      // Four-way arrow
      p.setPen(QPen(Qt::black, 1.5));
      p.setBrush(Qt::white);
      // Up
      QPolygonF u; u << QPointF(12, 2) << QPointF(8, 7) << QPointF(16, 7);
      p.drawPolygon(u);
      // Down
      QPolygonF d; d << QPointF(12, 22) << QPointF(8, 17) << QPointF(16, 17);
      p.drawPolygon(d);
      // Left
      QPolygonF l; l << QPointF(2, 12) << QPointF(7, 8) << QPointF(7, 16);
      p.drawPolygon(l);
      // Right
      QPolygonF r; r << QPointF(22, 12) << QPointF(17, 8) << QPointF(17, 16);
      p.drawPolygon(r);
      p.drawLine(12, 7, 12, 17);
      p.drawLine(7, 12, 17, 12);
      break;
   }
   case Qt::BlankCursor: {
      // Empty / dashed outline
      p.setPen(QPen(Qt::gray, 1, Qt::DashLine));
      p.setBrush(Qt::NoBrush);
      p.drawRect(4, 4, 16, 16);
      break;
   }
   case Qt::SplitVCursor: {
      p.setPen(QPen(Qt::black, 1.5));
      p.setBrush(Qt::white);
      // Horizontal bar
      p.drawLine(4, 12, 20, 12);
      // Up arrow
      QPolygonF u; u << QPointF(12, 3) << QPointF(8, 8) << QPointF(16, 8);
      p.drawPolygon(u);
      // Down arrow
      QPolygonF d; d << QPointF(12, 21) << QPointF(8, 16) << QPointF(16, 16);
      p.drawPolygon(d);
      break;
   }
   case Qt::SplitHCursor: {
      p.setPen(QPen(Qt::black, 1.5));
      p.setBrush(Qt::white);
      // Vertical bar
      p.drawLine(12, 4, 12, 20);
      // Left arrow
      QPolygonF l; l << QPointF(3, 12) << QPointF(8, 8) << QPointF(8, 16);
      p.drawPolygon(l);
      // Right arrow
      QPolygonF r; r << QPointF(21, 12) << QPointF(16, 8) << QPointF(16, 16);
      p.drawPolygon(r);
      break;
   }
   case Qt::PointingHandCursor: {
      // Simplified hand with pointing finger
      p.setPen(QPen(Qt::black, 1));
      p.setBrush(Qt::white);
      // Finger
      p.drawRoundedRect(10, 2, 5, 12, 2, 2);
      // Palm
      p.drawRoundedRect(5, 12, 15, 10, 3, 3);
      // Other fingers hint
      p.drawRoundedRect(5, 8, 5, 8, 2, 2);
      p.drawRoundedRect(16, 8, 4, 8, 2, 2);
      break;
   }
   case Qt::ForbiddenCursor: {
      // Circle with diagonal line
      p.setPen(QPen(Qt::red, 2));
      p.setBrush(Qt::NoBrush);
      p.drawEllipse(3, 3, 18, 18);
      p.drawLine(6, 6, 18, 18);
      break;
   }
   case Qt::WhatsThisCursor: {
      // Question mark with arrow
      QPolygonF arrow;
      arrow << QPointF(4, 2) << QPointF(4, 12) << QPointF(8, 9) << QPointF(4, 2);
      drawArrow(arrow);
      p.setPen(QPen(Qt::black, 2));
      p.setFont(QFont("Arial", 11, QFont::Bold));
      p.drawText(QRect(11, 6, 14, 18), Qt::AlignLeft | Qt::AlignTop, "?");
      break;
   }
   case Qt::BusyCursor: {
      // Arrow + hourglass
      QPolygonF arrow;
      arrow << QPointF(3, 1) << QPointF(3, 13) << QPointF(6, 10)
            << QPointF(3, 1);
      drawArrow(arrow);
      // Mini hourglass
      p.setPen(QPen(Qt::black, 1));
      p.setBrush(QBrush(QColor(180, 180, 180)));
      QPolygonF ht; ht << QPointF(12, 10) << QPointF(21, 10) << QPointF(16.5, 15);
      p.drawPolygon(ht);
      p.setBrush(QBrush(QColor(100, 100, 100)));
      QPolygonF hb; hb << QPointF(12, 21) << QPointF(21, 21) << QPointF(16.5, 15);
      p.drawPolygon(hb);
      break;
   }
   case Qt::OpenHandCursor: {
      // Open hand - five spread fingers
      p.setPen(QPen(Qt::black, 1));
      p.setBrush(Qt::white);
      p.drawRoundedRect(4, 6, 4, 9, 2, 2);   // pinky
      p.drawRoundedRect(8, 3, 4, 10, 2, 2);   // ring
      p.drawRoundedRect(12, 2, 4, 11, 2, 2);  // middle
      p.drawRoundedRect(16, 4, 4, 9, 2, 2);   // index
      p.drawRoundedRect(5, 13, 16, 9, 4, 4);  // palm
      break;
   }
   case Qt::ClosedHandCursor: {
      // Closed/fist hand
      p.setPen(QPen(Qt::black, 1));
      p.setBrush(Qt::white);
      p.drawRoundedRect(4, 7, 4, 5, 2, 2);
      p.drawRoundedRect(8, 5, 4, 7, 2, 2);
      p.drawRoundedRect(12, 5, 4, 7, 2, 2);
      p.drawRoundedRect(16, 7, 4, 5, 2, 2);
      p.drawRoundedRect(5, 11, 16, 10, 4, 4);
      break;
   }
   case Qt::DragCopyCursor: {
      // Arrow with + sign
      QPolygonF arrow;
      arrow << QPointF(4, 2) << QPointF(4, 14) << QPointF(7, 11)
            << QPointF(4, 2);
      drawArrow(arrow);
      p.setPen(QPen(Qt::darkGreen, 2));
      p.drawLine(16, 12, 16, 22);
      p.drawLine(11, 17, 21, 17);
      break;
   }
   case Qt::DragMoveCursor: {
      // Arrow with box
      QPolygonF arrow;
      arrow << QPointF(4, 2) << QPointF(4, 14) << QPointF(7, 11)
            << QPointF(4, 2);
      drawArrow(arrow);
      p.setPen(QPen(Qt::black, 1.5));
      p.setBrush(QBrush(QColor(200, 200, 255)));
      p.drawRect(12, 12, 10, 10);
      break;
   }
   case Qt::DragLinkCursor: {
      // Arrow with chain-link hint
      QPolygonF arrow;
      arrow << QPointF(4, 2) << QPointF(4, 14) << QPointF(7, 11)
            << QPointF(4, 2);
      drawArrow(arrow);
      p.setPen(QPen(Qt::blue, 1.5));
      p.setBrush(Qt::NoBrush);
      p.drawEllipse(11, 12, 6, 6);
      p.drawEllipse(15, 16, 6, 6);
      break;
   }
   default:
      break;
   }

   p.end();
   return pixmap;
}

} // anonymous namespace

QCursorPropertyItemEditor::QCursorPropertyItemEditor(QWidget *parent)
   : QBasePropertyItemEditor(parent)
{
   m_comboBox = new QComboBox(this);
   
   // Populate with all standard cursor shapes
   struct CursorInfo {
      Qt::CursorShape shape;
      const char* name;
   };
   
   static const CursorInfo cursors[] = {
      {Qt::ArrowCursor, "Arrow"},
      {Qt::UpArrowCursor, "Up Arrow"},
      {Qt::CrossCursor, "Cross"},
      {Qt::WaitCursor, "Wait"},
      {Qt::IBeamCursor, "I-Beam"},
      {Qt::SizeVerCursor, "Size Vertical"},
      {Qt::SizeHorCursor, "Size Horizontal"},
      {Qt::SizeBDiagCursor, "Size Backward Diagonal"},
      {Qt::SizeFDiagCursor, "Size Forward Diagonal"},
      {Qt::SizeAllCursor, "Size All"},
      {Qt::BlankCursor, "Blank"},
      {Qt::SplitVCursor, "Split Vertical"},
      {Qt::SplitHCursor, "Split Horizontal"},
      {Qt::PointingHandCursor, "Pointing Hand"},
      {Qt::ForbiddenCursor, "Forbidden"},
      {Qt::WhatsThisCursor, "What's This"},
      {Qt::BusyCursor, "Busy"},
      {Qt::OpenHandCursor, "Open Hand"},
      {Qt::ClosedHandCursor, "Closed Hand"},
      {Qt::DragCopyCursor, "Drag Copy"},
      {Qt::DragMoveCursor, "Drag Move"},
      {Qt::DragLinkCursor, "Drag Link"}
   };
   
   for (const auto& info : cursors) {
      QPixmap pixmap = drawCursorIcon(info.shape);
      QIcon icon(pixmap);
      m_comboBox->addItem(icon, info.name, (int)info.shape);
   }
   
   static_cast<QHBoxLayout*>(layout())->insertWidget(0, m_comboBox, 1);
   
   connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
}

QCursorPropertyItemEditor::~QCursorPropertyItemEditor()
{

}

void QCursorPropertyItemEditor::setValue(const QVariant& value)
{
   QCursor cursor = qvariant_cast<QCursor>(value);
   int shape = (int)cursor.shape();
   
   // Find the index matching this shape
   for (int i = 0; i < m_comboBox->count(); ++i) {
      if (m_comboBox->itemData(i).toInt() == shape) {
         m_comboBox->blockSignals(true);
         m_comboBox->setCurrentIndex(i);
         m_comboBox->blockSignals(false);
         break;
      }
   }
}

QVariant QCursorPropertyItemEditor::getValue() const
{
   int shape = m_comboBox->currentData().toInt();
   return QVariant::fromValue(QCursor((Qt::CursorShape)shape));
}

void QCursorPropertyItemEditor::onCurrentIndexChanged(int index)
{
   Q_UNUSED(index);
   emit valueChanged(this);
}

void QCursorPropertyItemEditor::setUpChildWidget()
{
   if (m_propertyItem) {
      QVariant value = m_propertyItem->data(1, Qt::EditRole);
      setValue(value);
   }
}
