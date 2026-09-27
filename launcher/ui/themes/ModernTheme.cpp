// SPDX-License-Identifier: GPL-3.0-only
#include "ModernTheme.h"

#include <QObject>

QString ModernTheme::id()
{
    return "modern-dark";
}

QString ModernTheme::name()
{
    return QObject::tr("Modern Dark");
}

QString ModernTheme::tooltip()
{
    return QObject::tr("A modern dark theme for the Prism Launcher UI redesign.");
}

QPalette ModernTheme::colorScheme()
{
    QPalette palette;

    const QColor window("#0b111b");
    const QColor base("#101925");
    const QColor alternate("#152131");
    const QColor surface("#172334");
    const QColor text("#e8eef7");
    const QColor muted("#8998ad");
    const QColor accent("#35bdf5");
    const QColor accentStrong("#269dd0");

    palette.setColor(QPalette::Window, window);
    palette.setColor(QPalette::WindowText, text);
    palette.setColor(QPalette::Base, base);
    palette.setColor(QPalette::AlternateBase, alternate);
    palette.setColor(QPalette::ToolTipBase, surface);
    palette.setColor(QPalette::ToolTipText, text);
    palette.setColor(QPalette::Text, text);
    palette.setColor(QPalette::Button, surface);
    palette.setColor(QPalette::ButtonText, text);
    palette.setColor(QPalette::BrightText, QColor("#ff667a"));
    palette.setColor(QPalette::Link, accent);
    palette.setColor(QPalette::Highlight, accentStrong);
    palette.setColor(QPalette::HighlightedText, Qt::white);
    palette.setColor(QPalette::PlaceholderText, muted);

    return fadeInactive(palette, fadeAmount(), fadeColor());
}

double ModernTheme::fadeAmount()
{
    return 0.35;
}

QColor ModernTheme::fadeColor()
{
    return QColor("#0b111b");
}

bool ModernTheme::hasStyleSheet()
{
    return true;
}

QString ModernTheme::appStyleSheet()
{
    return R"(
QMainWindow, QDialog {
    background: #0b111b;
}

QToolBar {
    background: #0f1824;
    border: none;
    spacing: 6px;
    padding: 7px;
}

QToolBar::separator {
    background: #253246;
    width: 1px;
    margin: 6px 4px;
}

QToolButton, QPushButton {
    background: #172334;
    color: #e8eef7;
    border: 1px solid #26364c;
    border-radius: 7px;
    padding: 7px 11px;
}

QToolButton:hover, QPushButton:hover {
    background: #1d2d42;
    border-color: #35516f;
}

QToolButton:pressed, QPushButton:pressed,
QToolButton:checked, QPushButton:checked {
    background: #173a52;
    border-color: #35bdf5;
}

QToolButton:disabled, QPushButton:disabled {
    color: #637186;
    background: #111a27;
    border-color: #202c3d;
}

QLineEdit, QTextEdit, QPlainTextEdit, QComboBox, QSpinBox, QDoubleSpinBox {
    background: #101925;
    color: #e8eef7;
    border: 1px solid #26364c;
    border-radius: 7px;
    padding: 6px 8px;
    selection-background-color: #269dd0;
}

QLineEdit:focus, QTextEdit:focus, QPlainTextEdit:focus, QComboBox:focus,
QSpinBox:focus, QDoubleSpinBox:focus {
    border-color: #35bdf5;
}

QMenuBar {
    background: #0f1824;
    color: #dbe6f4;
}

QMenuBar::item {
    padding: 6px 10px;
    border-radius: 5px;
}

QMenuBar::item:selected {
    background: #1d2d42;
}

QMenu {
    background: #111b29;
    color: #e8eef7;
    border: 1px solid #26364c;
    padding: 5px;
}

QMenu::item {
    padding: 7px 24px 7px 10px;
    border-radius: 5px;
}

QMenu::item:selected {
    background: #1b3951;
}

QStatusBar {
    background: #0f1824;
    color: #8998ad;
    border-top: 1px solid #1e2b3c;
}

QTreeView, QListView, QTableView {
    background: #0d1621;
    alternate-background-color: #111d2a;
    border: none;
    outline: none;
}

QHeaderView::section {
    background: #142030;
    color: #dbe6f4;
    border: none;
    border-right: 1px solid #26364c;
    padding: 7px;
}

QTabWidget::pane {
    border: 1px solid #26364c;
    border-radius: 7px;
    background: #0f1824;
}

QTabBar::tab {
    background: transparent;
    color: #8998ad;
    padding: 8px 12px;
    border-bottom: 2px solid transparent;
}

QTabBar::tab:selected {
    color: #e8eef7;
    border-bottom-color: #35bdf5;
}

QScrollBar:vertical {
    background: transparent;
    width: 11px;
    margin: 2px;
}

QScrollBar::handle:vertical {
    background: #314158;
    border-radius: 4px;
    min-height: 28px;
}

QScrollBar::handle:vertical:hover {
    background: #405570;
}

QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
    background: transparent;
    height: 0px;
}

QFrame#modernSidebar {
    background: #0c1420;
    border-right: 1px solid #1d2a3b;
}

QLabel#modernBrand {
    color: #f4f8fd;
    font-size: 18px;
    font-weight: 700;
    padding: 4px 2px;
}

QToolButton#modernNavButton {
    background: transparent;
    border: 1px solid transparent;
    border-radius: 8px;
    text-align: left;
    padding: 9px 11px;
}

QToolButton#modernNavButton:hover {
    background: #152235;
    border-color: #22344a;
}

QToolButton#modernNavButton[active="true"] {
    background: #17334a;
    border-color: #2d6f99;
    color: #eef9ff;
}

QLabel#modernSidebarFooter {
    color: #607086;
    font-size: 11px;
    padding: 8px 4px 2px 4px;
}

QWidget#modernContent {
    background: #0b111b;
}

QWidget#modernHeader {
    background: transparent;
}

QLabel#modernPageTitle {
    color: #f1f5fb;
    font-size: 22px;
    font-weight: 700;
    padding-right: 8px;
}

QLineEdit#modernSearchBox {
    min-height: 24px;
    background: #101a27;
    border: 1px solid #26374d;
    border-radius: 8px;
    padding: 7px 10px;
}

QToolButton#modernPrimaryButton {
    background: #208cc2;
    color: white;
    border: 1px solid #35bdf5;
    border-radius: 8px;
    padding: 8px 13px;
    font-weight: 600;
}

QToolButton#modernPrimaryButton:hover {
    background: #269dd0;
}

QToolTip {
    color: #f5f8fc;
    background: #172334;
    border: 1px solid #35516f;
    border-radius: 5px;
    padding: 5px;
}
)";
}
