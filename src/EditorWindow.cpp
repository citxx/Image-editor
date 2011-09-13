#include "EditorWindow.hpp"
#include "ui_EditorWindow.h"

EditorWindow::EditorWindow(QWidget *parent): QMainWindow(parent) {
    this->ui = new UI::EditorWindow;
    this->ui->setupUi(this);
}

EditorWindow::~EditorWindow() {
    delete this->ui;
}
