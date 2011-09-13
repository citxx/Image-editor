#include "EditorWindow.hpp"
#include "ui_EditorWindow.h"

#include <QFileDialog>

EditorWindow::EditorWindow(QWidget *parent): QMainWindow(parent) {
    this->ui = new Ui::EditorWindow;
    this->ui->setupUi(this);

    this->imageScene = new ImageScene;
    this->ui->imageView->setScene(this->imageScene);

    this->connect(this->ui->actionOpen, SIGNAL(activated()), this, SLOT(openImage()));
}

EditorWindow::~EditorWindow() {
    delete this->ui;
    delete this->imageScene;
}

void EditorWindow::openImage() {
    QFileDialog imageChooser(this);
    imageChooser.setFileMode(QFileDialog::ExistingFile);
    imageChooser.setNameFilter(tr("Images (*.png *.jpg *.jpeg *.bmp *.xpm)"));
    imageChooser.setViewMode(QFileDialog::Detail);

    QString fileName;
    if (imageChooser.exec()) {
        fileName = imageChooser.selectedFiles().at(0);

        QPixmap image(fileName);
        this->imageScene->setImageMode(image);
    }
}
