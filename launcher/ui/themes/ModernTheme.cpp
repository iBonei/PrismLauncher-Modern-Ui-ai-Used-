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

QFrame#modernWelcome {
    background: #142638;
    border: 1px solid #29445b;
    border-radius: 16px;
}

QLabel#modernWelcomeEyebrow, QLabel#modernSectionEyebrow {
    color: #69c8dd;
    font-size: 10px;
    font-weight: 700;
    letter-spacing: 1px;
}

QLabel#modernWelcomeTitle {
    color: #f5f9fd;
    font-size: 27px;
    font-weight: 750;
}

QLabel#modernWelcomeSubtitle {
    color: #9fb3c7;
    font-size: 12px;
}

QLabel#modernLibraryHint {
    color: #8396ab;
    font-size: 12px;
    padding-bottom: 4px;
}

QToolButton#modernSecondaryButton {
    color: #dbeaf6;
    background: #1b3348;
    border: 1px solid #365269;
    border-radius: 9px;
    padding: 8px 14px;
    font-weight: 600;
}

QToolButton#modernSecondaryButton:hover {
    background: #28465e;
    border-color: #5a7e98;
}

QFrame#modernSidebar {
    background: #0d1724;
    border-right: 1px solid #233549;
}

QWidget#modernBrandRow {
    background: transparent;
}

QLabel#modernBrandIcon {
    background: #111b29;
    border: 1px solid #26364c;
    border-radius: 9px;
}

QLabel#modernBrand {
    color: #f4f8fd;
    font-size: 16px;
    font-weight: 700;
}

QLabel#modernBrandSubtitle {
    color: #6f8198;
    font-size: 9px;
    font-weight: 500;
}

QToolButton#modernNavButton {
    background: transparent;
    border: 1px solid transparent;
    border-radius: 9px;
    text-align: left;
    padding: 10px 11px;
    font-size: 12px;
}

QToolButton#modernNavButton:hover {
    background: #152235;
    border-color: #2a4059;
}

QToolButton#modernNavButton:pressed {
    background: #1a2a3e;
    border-color: #3c5d7d;
}

QToolButton#modernNavButton[active="true"] {
    background: #17334a;
    border-color: #2d6f99;
    color: #eef9ff;
}

QToolButton#modernUtilityButton,
QToolButton#modernAccountButton {
    background: #111b29;
    color: #dce6f3;
    border: 1px solid #223248;
    border-radius: 8px;
    padding: 8px 10px;
    text-align: left;
}

QToolButton#modernUtilityButton:hover,
QToolButton#modernAccountButton:hover {
    background: #17263a;
    border-color: #35516f;
}

QToolButton#modernUtilityButton:pressed,
QToolButton#modernAccountButton:pressed {
    background: #101c2b;
    border-color: #466684;
}

QToolButton#modernAccountButton {
    font-weight: 600;
}

QLabel#modernSidebarFooter {
    color: #607086;
    font-size: 11px;
    padding: 6px 4px 2px 4px;
}

QWidget#modernContent {
    background: #0b111b;
}

QWidget#modernHeader {
    background: transparent;
}

QLabel#modernPageTitle {
    color: #f1f5fb;
    font-size: 21px;
    font-weight: 700;
    padding-right: 10px;
}

QLineEdit#modernSearchBox {
    min-height: 24px;
    background: #101a27;
    border: 1px solid #26374d;
    border-radius: 9px;
    padding: 7px 10px;
}

QLineEdit#modernSearchBox:hover {
    border-color: #35516f;
}

QLineEdit#modernSearchBox:focus {
    border-color: #35bdf5;
    background: #111d2b;
}

QToolButton#modernPrimaryButton {
    background: #208cc2;
    color: white;
    border: 1px solid #35bdf5;
    border-radius: 9px;
    padding: 8px 14px;
    font-weight: 600;
}

QToolButton#modernPrimaryButton:hover {
    background: #269dd0;
    border-color: #64d2ff;
}

QToolButton#modernPrimaryButton:pressed {
    background: #177aa8;
    border-color: #35bdf5;
}

QFrame#modernDetails {
    background: #111e2d;
    border-left: 1px solid #1d2a3b;
}

QLabel#modernDetailsTitle {
    color: #8ea0b8;
    font-size: 11px;
    font-weight: 600;
    text-transform: uppercase;
}

QLabel#modernInstanceName {
    color: #f4f8fd;
    font-size: 19px;
    font-weight: 700;
    padding-top: 2px;
}

QLabel#modernInstanceIcon {
    background: #111b29;
    border: 1px solid #26364c;
    border-radius: 14px;
    margin: 8px 0 4px 0;
}

QLabel#modernInstanceStatus {
    color: #8798ae;
    font-size: 12px;
    padding-bottom: 4px;
}

QLabel#modernInstanceMeta {
    color: #a7b5c8;
    background: #111b29;
    border: 1px solid #223248;
    border-radius: 8px;
    padding: 9px 10px;
    font-size: 11px;
}

QToolButton#modernLaunchButton {
    background: #2abf6f;
    color: #07150d;
    border: 1px solid #52dd8d;
    border-radius: 8px;
    padding: 9px 12px;
    font-weight: 700;
    text-align: left;
}

QToolButton#modernLaunchButton:hover {
    background: #39cf7d;
    border-color: #74e7a6;
}

QToolButton#modernLaunchButton:pressed {
    background: #20a75e;
    border-color: #52dd8d;
}

QToolButton#modernLaunchButton:disabled {
    background: #14231c;
    color: #607267;
    border-color: #243b30;
}

QToolButton#modernDetailsButton {
    background: #172334;
    color: #e8eef7;
    border: 1px solid #26364c;
    border-radius: 8px;
    padding: 8px 11px;
    text-align: left;
}

QToolButton#modernDetailsButton:hover {
    background: #1d2d42;
    border-color: #35516f;
}

QToolButton#modernDetailsButton:pressed {
    background: #142235;
    border-color: #466684;
}

/* Reimagined v3: integrated launch pad, not a fixed side inspector. */
QFrame#modernDetails {
    background: #16283a;
    border: 1px solid #2a455b;
    border-radius: 16px;
}

QLabel#modernInstanceIcon {
    background: #0f1d2b;
    border: 1px solid #35536b;
    border-radius: 15px;
    margin: 0;
}

QLabel#modernInstanceName {
    color: #f3f8ff;
    font-size: 25px;
    font-weight: 750;
    padding: 0;
}

QLabel#modernInstanceStatus {
    color: #afc1d1;
    font-size: 12px;
}

QLabel#modernInstanceMeta {
    background: transparent;
    border: none;
    color: #7f9eb6;
    padding: 3px 0;
    font-size: 11px;
}

QWidget#modernActionPanel {
    background: transparent;
}

QToolButton#modernLaunchButton {
    background: #29c77e;
    color: #071b15;
    border: 1px solid #62e4a5;
    border-radius: 10px;
    padding: 11px 16px;
    font-size: 13px;
    font-weight: 750;
    text-align: left;
    min-height: 25px;
}

QToolButton#modernLaunchButton:hover {
    background: #4cdb9a;
    border-color: #8ef2be;
}

QToolButton#modernDetailsButton {
    background: #21384c;
    color: #e0edf8;
    border: 1px solid #375269;
    border-radius: 9px;
    padding: 8px 10px;
    text-align: left;
}

QToolButton#modernDetailsButton:hover {
    background: #304e65;
    border-color: #6e91ac;
}

QWidget#modernContent {
    background: #0b1421;
}
QLineEdit#modernSearchBox {
    min-height: 28px;
    background: #121f2d;
    border-radius: 10px;
}
QLabel#modernPageTitle {
    font-size: 23px;
}

/* Unified application shell: instance editing, settings and creation. */
QListView#modernPageNavigation {
    background: #0c1929;
    border: 1px solid #24394f;
    border-radius: 13px;
    padding: 9px 6px;
    outline: none;
    font-size: 12px;
}

QListView#modernPageNavigation::item {
    color: #a9bfd2;
    min-height: 40px;
    padding: 4px 10px;
    margin: 3px 5px;
    border-radius: 9px;
    border: 1px solid transparent;
}

QListView#modernPageNavigation::item:hover {
    color: #f0f8ff;
    background: #1b3147;
    border-color: #36556e;
}

QListView#modernPageNavigation::item:selected {
    color: #f5fbff;
    background: #234763;
    border-color: #3a91bd;
    font-weight: 700;
}

QFrame#modernPageSurface {
    background: #101e2e;
    border: 1px solid #263d53;
    border-radius: 14px;
}

QLabel#modernPageHeading {
    color: #f3f9ff;
    font-size: 24px;
    font-weight: 750;
    padding: 7px 4px 8px 4px;
}

QDialog#NewInstanceDialog {
    background: #0a1522;
}

QFrame#modernIdentityCard {
    background: #152a3e;
    border: 1px solid #31536c;
    border-radius: 14px;
    padding: 14px;
}

QLabel#modernCreateEyebrow,
QLabel#modernDiscoverEyebrow {
    color: #69cee8;
    font-size: 10px;
    font-weight: 700;
}

QLabel#modernCreateTitle,
QLabel#modernDiscoverTitle {
    color: #f6faff;
    font-size: 23px;
    font-weight: 750;
}

QLabel#modernCreateSubtitle {
    color: #9eafc3;
    font-size: 12px;
    padding-bottom: 6px;
}

QToolButton#iconButton {
    background: #0f1d2d;
    border: 1px solid #38556e;
    border-radius: 12px;
    padding: 12px;
}

QToolButton#iconButton:hover {
    background: #223e54;
    border-color: #61bdda;
}

QListView#packView {
    background: #101f30;
    border: 1px solid #2b425a;
    border-radius: 11px;
    padding: 5px;
    outline: none;
}

QListView#packView::item {
    border: 1px solid transparent;
    border-radius: 9px;
    padding: 8px 10px;
    margin: 3px;
    min-height: 55px;
}

QListView#packView::item:selected {
    color: #f1fbff;
    background: #23445c;
    border-color: #3aa9d0;
}

QListView#packView::item:hover {
    background: #1c344a;
    border-color: #42637c;
}

QTextBrowser#packDescription {
    background: #111e2d;
    border: 1px solid #2b4157;
    border-radius: 11px;
    padding: 14px;
}

QWidget#filterWidget {
    background: #111f30;
    border: 1px solid #2a4158;
    border-radius: 11px;
}

QSplitter::handle {
    background: #1c3044;
}

QDialogButtonBox QPushButton {
    min-height: 23px;
    min-width: 92px;
    border-radius: 8px;
    padding: 9px 16px;
}

QDialogButtonBox QPushButton:default {
    background: #229fcf;
    border: 1px solid #5ed0ef;
    color: #ffffff;
    font-weight: 700;
}

QDialogButtonBox QPushButton:default:hover {
    background: #31b4e3;
}

QGroupBox {
    color: #e5f0fa;
    font-weight: 650;
    background: #142538;
    border: 1px solid #2b435c;
    border-radius: 10px;
    margin-top: 16px;
    padding: 13px 12px 10px 12px;
}

QGroupBox::title {
    subcontrol-origin: margin;
    subcontrol-position: top left;
    left: 14px;
    padding: 0 6px;
    color: #afc8dc;
}

QCheckBox, QRadioButton {
    color: #d4e2ef;
    spacing: 9px;
    padding: 4px;
}

QCheckBox::indicator, QRadioButton::indicator {
    width: 16px;
    height: 16px;
}

QTabWidget::pane {
    border: 1px solid #2a435b;
    border-radius: 10px;
    background: #122236;
}

QTabBar::tab {
    color: #9fb3c8;
    background: #14283b;
    border: 1px solid #2b4359;
    border-bottom: none;
    border-top-left-radius: 8px;
    border-top-right-radius: 8px;
    padding: 10px 18px;
    margin-right: 4px;
}

QTabBar::tab:selected {
    color: #f5faff;
    background: #234663;
    border-color: #3b87b3;
}

QTableView, QTreeView {
    background: #101f30;
    alternate-background-color: #15283a;
    border: 1px solid #294057;
    border-radius: 9px;
    gridline-color: #273d52;
    selection-background-color: #265775;
    selection-color: #f3faff;
}

QHeaderView::section {
    background: #1b3248;
    color: #cfe4f5;
    border: none;
    border-bottom: 1px solid #38536c;
    padding: 10px 12px;
    font-weight: 650;
}

QComboBox::drop-down {
    border: none;
    width: 25px;
}

QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox {
    min-height: 24px;
    background: #102034;
    border: 1px solid #304a63;
    border-radius: 8px;
    padding: 7px 10px;
}

QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus {
    border-color: #54bfe7;
    background: #15293e;
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
