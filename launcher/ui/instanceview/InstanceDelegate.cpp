// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Prism Launcher - Minecraft Launcher
 *  Copyright (C) 2022 Sefa Eyeoglu <contact@scrumplex.net>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *      Copyright 2013-2021 MultiMC Contributors
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include "InstanceDelegate.h"
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QtMath>

#include <QIcon>
#include <QTextEdit>
#include "BaseInstance.h"
#include "InstanceList.h"

ListViewDelegate::ListViewDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

void drawSelectionRect(QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect)
{
    if ((option.state & QStyle::State_Selected))
        painter->fillRect(rect, option.palette.brush(QPalette::Highlight));
    else {
        QColor backgroundColor = option.palette.color(QPalette::Window);
        backgroundColor.setAlpha(160);
        painter->fillRect(rect, QBrush(backgroundColor));
    }
}

void drawBadges(QPainter* painter, const QStyleOptionViewItem& option, BaseInstance* instance, QIcon::Mode mode, QIcon::State state)
{
    QList<QString> pixmaps;
    if (instance->isRunning()) {
        pixmaps.append("status-running");
    } else if (instance->hasCrashed() || instance->hasVersionBroken()) {
        pixmaps.append("status-bad");
    }

    static const int itemSide = 24;
    static const int spacing = 1;
    const int itemsPerRow = qMax(1, qFloor(double(option.rect.width() + spacing) / double(itemSide + spacing)));
    const int rows = qCeil((double)pixmaps.size() / (double)itemsPerRow);
    QListIterator<QString> it(pixmaps);
    painter->translate(option.rect.topLeft());
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < itemsPerRow; ++x) {
            if (!it.hasNext()) {
                return;
            }
            // FIXME: inject this.
            auto icon = QIcon::fromTheme(it.next());
            // opt.icon.paint(painter, iconbox, Qt::AlignCenter, mode, state);
            const QPixmap pixmap;
            // itemSide
            QRect badgeRect(option.rect.width() - x * itemSide + qMax(x - 1, 0) * spacing - itemSide,
                            y * itemSide + qMax(y - 1, 0) * spacing, itemSide, itemSide);
            icon.paint(painter, badgeRect, Qt::AlignCenter, mode, state);
        }
    }
    painter->translate(-option.rect.topLeft());
}

void ListViewDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setClipRect(opt.rect);

    const bool selected = opt.state & QStyle::State_Selected;
    const bool enabled = opt.state & QStyle::State_Enabled;
    const bool hovered = opt.state & QStyle::State_MouseOver;
    const QRect card = opt.rect.adjusted(4, 4, -4, -4);
    const QColor background = selected ? QColor("#1d3a4d") : hovered ? QColor("#192b3d") : QColor("#142333");
    const QColor border = selected ? QColor("#48c8e9") : hovered ? QColor("#47627d") : QColor("#284055");
    painter->setPen(QPen(border, selected ? 2.0 : 1.0));
    painter->setBrush(background);
    painter->drawRoundedRect(card, 14, 14);

    const QRect artBox(card.left() + 15, card.top() + 17, 76, 76);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#0d1927"));
    painter->drawRoundedRect(artBox, 11, 11);
    opt.icon.paint(painter, artBox.adjusted(7, 7, -7, -7), Qt::AlignCenter,
                   enabled ? (selected ? QIcon::Selected : QIcon::Normal) : QIcon::Disabled);

    const auto* instance = (BaseInstance*)index.data(InstanceList::InstancePointerRole).value<void*>();
    const int textLeft = artBox.right() + 16;
    const int textWidth = qMax(10, card.right() - textLeft - 12);
    const QRect nameRect(textLeft, card.top() + 18, textWidth, 23);
    QFont titleFont = opt.font;
    titleFont.setBold(true);
    titleFont.setPointSizeF(titleFont.pointSizeF() + 1.0);
    painter->setFont(titleFont);
    painter->setPen(enabled ? QColor("#f3f7fc") : QColor("#68788c"));
    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter,
                      painter->fontMetrics().elidedText(index.data().toString(), Qt::ElideRight, textWidth));

    QString detail = instance ? instance->getStatusbarDescription() : QString();
    const qsizetype comma = detail.indexOf(',');
    if (comma >= 0)
        detail = detail.left(comma);
    QFont detailFont = opt.font;
    detailFont.setPointSizeF(qMax(8.0, detailFont.pointSizeF() - 0.5));
    painter->setFont(detailFont);
    painter->setPen(QColor("#9caec0"));
    painter->drawText(QRect(textLeft, card.top() + 44, textWidth, 19),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      painter->fontMetrics().elidedText(detail, Qt::ElideRight, textWidth));

    QString stateText = QObject::tr("Ready to launch");
    QColor stateColor("#66d3a0");
    if (instance && instance->isRunning()) {
        stateText = QObject::tr("Running");
        stateColor = QColor("#6fd0f5");
    } else if (instance && (instance->hasCrashed() || instance->hasVersionBroken())) {
        stateText = QObject::tr("Needs attention");
        stateColor = QColor("#f0a2a6");
    }
    painter->setPen(stateColor);
    painter->drawEllipse(QRect(textLeft, card.top() + 78, 7, 7));
    painter->setPen(QColor("#a5b7c8"));
    painter->drawText(QRect(textLeft + 13, card.top() + 70, textWidth - 13, 23),
                      Qt::AlignLeft | Qt::AlignVCenter, stateText);
    painter->restore();
}

QSize ListViewDelegate::sizeHint([[maybe_unused]] const QStyleOptionViewItem& option,
                                 [[maybe_unused]] const QModelIndex& index) const
{
    return QSize(310, 116);
}

class NoReturnTextEdit : public QTextEdit {
    Q_OBJECT
   public:
    explicit NoReturnTextEdit(QWidget* parent) : QTextEdit(parent)
    {
        setTextInteractionFlags(Qt::TextEditorInteraction);
        setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    }
    bool event(QEvent* event) override
    {
        auto eventType = event->type();
        if (eventType == QEvent::KeyPress || eventType == QEvent::KeyRelease) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            auto key = keyEvent->key();
            if ((key == Qt::Key_Return || key == Qt::Key_Enter) && eventType == QEvent::KeyPress) {
                emit editingDone();
                return true;
            }
            if (key == Qt::Key_Tab) {
                return true;
            }
        }
        return QTextEdit::event(event);
    }
   signals:
    void editingDone();
};

void ListViewDelegate::updateEditorGeometry(QWidget* editor,
                                            const QStyleOptionViewItem& option,
                                            [[maybe_unused]] const QModelIndex& index) const
{
    QRect textRect = option.rect.adjusted(108, 17, -16, -65);
    editor->setGeometry(textRect);
}

void ListViewDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    auto text = index.data(Qt::EditRole).toString();
    QTextEdit* realEditor = qobject_cast<NoReturnTextEdit*>(editor);
    realEditor->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    realEditor->append(text);
    realEditor->selectAll();
    realEditor->document()->clearUndoRedoStacks();
}

void ListViewDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QTextEdit* realEditor = qobject_cast<NoReturnTextEdit*>(editor);
    QString text = realEditor->toPlainText();
    text.replace(QChar('\n'), QChar(' '));
    text = text.trimmed();
    // Prevent instance names longer than 128 chars
    text.truncate(128);
    if (text.size() != 0) {
        const auto before = model->data(index).toString();
        model->setData(index, text);
        emit textChanged(before, text);
    }
}

QWidget* ListViewDelegate::createEditor(QWidget* parent,
                                        [[maybe_unused]] const QStyleOptionViewItem& option,
                                        [[maybe_unused]] const QModelIndex& index) const
{
    auto editor = new NoReturnTextEdit(parent);
    connect(editor, &NoReturnTextEdit::editingDone, this, &ListViewDelegate::editingDone);
    return editor;
}

void ListViewDelegate::editingDone()
{
    NoReturnTextEdit* editor = qobject_cast<NoReturnTextEdit*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

#include "InstanceDelegate.moc"
