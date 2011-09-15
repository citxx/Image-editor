#include "EditorWindow.hpp"
#include "Processing.hpp"
#include "ui_EditorWindow.h"

#include <QFileDialog>

EditorWindow::EditorWindow(QWidget *parent): QMainWindow(parent) {
    this->ui = new Ui::EditorWindow;
    this->ui->setupUi(this);

    this->imageScene = new ImageScene;
    this->ui->imageView->setScene(this->imageScene);

    this->connect(this->ui->actionOpen,   SIGNAL(activated()), this, SLOT(openImage()));
    this->connect(this->ui->actionClose,  SIGNAL(activated()), this, SLOT(closeImage()));
    this->connect(this->ui->actionSave,   SIGNAL(activated()), this, SLOT(saveImage()));
    this->connect(this->ui->actionSaveAs, SIGNAL(activated()), this, SLOT(saveImageAs()));

    this->connect(this->ui->actionContrastLinear, SIGNAL(activated()), this, SLOT(linearContrastCorrection()));
}

EditorWindow::~EditorWindow() {
    delete this->ui;
    delete this->imageScene;
}

QString EditorWindow::chooseImageFile(QFileDialog::FileMode mode) {
    QFileDialog imageChooser(this);
    imageChooser.setFileMode(mode);
    imageChooser.setNameFilter(tr("Images (*.png *.jpg *.jpeg *.bmp *.xpm)"));
    imageChooser.setViewMode(QFileDialog::Detail);

    if (imageChooser.exec()) {
        return imageChooser.selectedFiles().at(0);
    }
    else {
        return QString();
    }
}

void EditorWindow::openImage() {
    QString fileName = this->chooseImageFile(QFileDialog::ExistingFile);
    if (!fileName.isNull()) {
        if (!this->currentImage.isNull()) {
            this->closeImage();
        }
        this->currentImageFileName = fileName;
        this->currentImage = QImage(fileName);
        this->imageScene->setImageMode(QPixmap::fromImage(this->currentImage));
    }
}

void EditorWindow::closeImage() {
    // TODO: The dialog asking if the user want to save the image

    this->currentImageFileName = QString();
    this->currentImage = QImage();
    this->imageScene->setEmptyMode();
}

void EditorWindow::saveImage() {
    // TODO: warning of rewriting

    this->currentImage.save(this->currentImageFileName);
}

void EditorWindow::saveImageAs() {
    QString fileName = this->chooseImageFile(QFileDialog::AnyFile);

    if (!fileName.isNull()) {
        this->currentImage.save(fileName);
        this->currentImageFileName = fileName;
    }
}

void EditorWindow::linearContrastCorrection() {
    this->currentImage = Processing::linearContrastCorrection(this->currentImage);
    this->imageScene->setImageMode(QPixmap::fromImage(this->currentImage));
}
