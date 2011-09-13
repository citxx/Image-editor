#include "EditorWindow.hpp"
#include "ui_EditorWindow.h"

EditorWindow::EditorWindow(QWidget *parent): QMainWindow(parent) {
    this->ui = new Ui::EditorWindow;
    this->ui->setupUi(this);

    this->imageScene = new ImageScene;
    this->ui->imageView->setScene(this->imageScene);
}

EditorWindow::~EditorWindow() {
    delete this->ui;
    delete this->imageScene;
}
