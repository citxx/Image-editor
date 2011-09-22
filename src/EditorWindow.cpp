#include "EditorWindow.hpp"
#include "Processing.hpp"
#include "FilterDialog.hpp"
#include "RotateDialog.hpp"
#include "ScaleDialog.hpp"
#include "ui_EditorWindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

EditorWindow::EditorWindow(QWidget *parent): QMainWindow(parent) {
    this->ui.setupUi(this);

    this->imageScene = new ImageScene;
    this->ui.imageView->setScene(this->imageScene);

    this->connect(this->ui.actionOpen,   SIGNAL(activated()), this, SLOT(openImage()));
    this->connect(this->ui.actionClose,  SIGNAL(activated()), this, SLOT(closeImage()));
    this->connect(this->ui.actionSave,   SIGNAL(activated()), this, SLOT(saveImage()));
    this->connect(this->ui.actionSaveAs, SIGNAL(activated()), this, SLOT(saveImageAs()));

    this->connect(this->ui.actionContrastLinear, SIGNAL(activated()), this, SLOT(linearContrastCorrection()));
    this->connect(this->ui.actionContrastRGB, SIGNAL(activated()), this, SLOT(rgbContrastCorrection()));
    this->connect(this->ui.actionGrayWorld, SIGNAL(activated()), this, SLOT(grayWorld()));

    this->connect(this->ui.actionCustomFilter, SIGNAL(activated()), this, SLOT(applyFilter()));
    this->connect(this->ui.actionGaussianBlur, SIGNAL(activated()), this, SLOT(gaussianBlur()));
    this->connect(this->ui.actionUnsharp, SIGNAL(activated()), this, SLOT(unsharp()));
    this->connect(this->ui.actionMedianFilter, SIGNAL(activated()), this, SLOT(medianFilter()));

    this->connect(this->ui.actionRotate, SIGNAL(activated()), this, SLOT(rotate()));
    this->connect(this->ui.actionScale, SIGNAL(activated()), this, SLOT(scale()));
}

EditorWindow::~EditorWindow() {
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

void EditorWindow::replaceImage(const QImage &img) {
    this->currentImage = img;
    this->imageScene->setImageMode(QPixmap::fromImage(img));
    this->imageChanged = true;
}

void EditorWindow::openImage() {
    QString fileName = this->chooseImageFile(QFileDialog::ExistingFile);
    if (!fileName.isNull()) {
        if (!this->currentImage.isNull()) {
            this->closeImage();
        }
        this->currentImageFileName = fileName;
        this->currentImage = QImage(fileName);
        this->imageChanged = false;
        this->imageScene->setImageMode(QPixmap::fromImage(this->currentImage));
    }
}

void EditorWindow::closeImage() {
    if (this->imageChanged) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("Closing"));
        msgBox.setText(tr("Do you want to save changes before closing the image?\n\nIf you don't save, your changes will be lost."));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int button = msgBox.exec();

        if (button != QMessageBox::Cancel) {
            if (button == QMessageBox::Save) {
                this->saveImageAs();
            }
            this->currentImageFileName = QString();
            this->currentImage = QImage();
            this->imageScene->setEmptyMode();
        }
    }
    else {
        this->currentImageFileName = QString();
        this->currentImage = QImage();
        this->imageScene->setEmptyMode();
    }
}

void EditorWindow::saveImage() {
    this->currentImage.save(this->currentImageFileName);
    this->imageChanged = false;
}

void EditorWindow::saveImageAs() {
    // TODO: warning of rewriting

    QString fileName = this->chooseImageFile(QFileDialog::AnyFile);

    if (!fileName.isNull()) {
        this->currentImage.save(fileName);
        this->currentImageFileName = fileName;
        this->imageChanged = false;
    }
}

void EditorWindow::linearContrastCorrection() {
    this->replaceImage(Processing::linearContrastCorrection(this->currentImage));
}

void EditorWindow::rgbContrastCorrection() {
    this->replaceImage(Processing::rgbContrastCorrection(this->currentImage));
}

void EditorWindow::grayWorld() {
    this->replaceImage(Processing::grayWorld(this->currentImage));
}

void EditorWindow::applyFilter() {
    FilterDialog dialog(this);

    if (dialog.exec()) {
        this->replaceImage(Processing::applyFilter(this->currentImage, dialog.getFilter()));
    }
}

void EditorWindow::gaussianBlur() {
    bool ok;
    qreal sigma = QInputDialog::getDouble(this, tr("Please, enter sigma"), tr("Sigma: "), 1.0, 0.35, 5.0, 2, &ok);
    if (ok) {
        this->replaceImage(Processing::gaussianBlur(this->currentImage, sigma));
    }
}

void EditorWindow::unsharp() {
    bool ok;
    qreal sigma = QInputDialog::getDouble(this, tr("Please, enter sigma"), tr("Sigma: "), 1.0, 0.35, 5.0, 2, &ok);
    if (ok) {
        qreal alpha = QInputDialog::getDouble(this, tr("Please, enter alpha"), tr("Alpha: "), 1.0, 0.0, 20.0, 2, &ok);
        if (ok) {
            this->replaceImage(Processing::unsharp(this->currentImage, alpha, sigma));
        }
    }
}

void EditorWindow::medianFilter() {
    bool ok;
    int size = QInputDialog::getInt(this, tr("Please, enter the filter size"), tr("Size: "), 3, 2, 50, 1, &ok);
    if (ok) {
        this->replaceImage(Processing::medianFilter(this->currentImage, size));
    }
}

void EditorWindow::rotate() {
    RotateDialog dialog(this);

    if (dialog.exec()) {
        qreal angle = dialog.getAngle();
        QPointF center = dialog.getCenter();
        this->replaceImage(Processing::rotate(this->currentImage, angle, center));
    }
}

void EditorWindow::scale() {
    ScaleDialog dialog(this);

    if (dialog.exec()) {
        qreal factor = dialog.getFactor();
        QPointF center = dialog.getCenter();
        this->replaceImage(Processing::scale(this->currentImage, factor, center));
    }
}
