#include "EditorWindow.hpp"
#include "ui_EditorWindow.h"

#include <QFileDialog>

EditorWindow::EditorWindow(QWidget *parent): QMainWindow(parent) {
    this->ui = new Ui::EditorWindow;
    this->ui->setupUi(this);

    this->imageScene = new ImageScene;
    this->ui->imageView->setScene(this->imageScene);

    this->connect(this->ui->actionOpen,  SIGNAL(activated()), this, SLOT(openImage()));
    this->connect(this->ui->actionClose, SIGNAL(activated()), this, SLOT(closeImage()));
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

        if (!this->currentImage.isNull()) {
            this->closeImage();
        }
        this->currentImage = QImage(fileName);
        this->imageScene->setImageMode(QPixmap::fromImage(this->currentImage));
    }
}

void EditorWindow::closeImage() {
    // TODO: The dialog asking if the user want to save the image

    this->currentImage = QImage();
    this->imageScene->setEmptyMode();
}
