#include "EditorWindow.hpp"
#include "Processing.hpp"
#include "FilterDialog.hpp"
#include "RotateDialog.hpp"
#include "ScaleDialog.hpp"
#include "WavesDialog.hpp"
#include "UnsharpDialog.hpp"
#include "ui_EditorWindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

EditorWindow::EditorWindow(QWidget *parent): QMainWindow(parent) {
    this->ui.setupUi(this);
    this->imageView = new ImageShowArea(this);
    this->ui.centralwidget->layout()->addWidget(this->imageView);

    this->imageScene = new ImageScene;
    this->imageView->setScene(this->imageScene);

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
    this->connect(this->ui.actionWaves, SIGNAL(activated()), this, SLOT(waves()));

    this->ui.statusbar->showMessage(tr("Ready"));
    this->setEmptyMode();
}

EditorWindow::~EditorWindow() {
    delete this->imageView;
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
    this->imageView->resetSelection();
}

void EditorWindow::processing() {
    this->ui.statusbar->showMessage(tr("Processing..."));
}

void EditorWindow::ready() {
    this->ui.statusbar->showMessage(tr("Ready"));
}

void EditorWindow::setEmptyMode() {
    qDebug() << "Empty mode";
    this->ui.actionOpen->setEnabled(true);
    this->ui.actionClose->setEnabled(false);
    this->ui.actionSave->setEnabled(false);
    this->ui.actionSaveAs->setEnabled(false);
    this->ui.actionQuit->setEnabled(true);

    this->ui.actionContrastLinear->setEnabled(false);
    this->ui.actionContrastRGB->setEnabled(false);
    this->ui.actionGrayWorld->setEnabled(false);

    this->ui.actionCustomFilter->setEnabled(false);
    this->ui.actionGaussianBlur->setEnabled(false);
    this->ui.actionUnsharp->setEnabled(false);
    this->ui.actionMedianFilter->setEnabled(false);

    this->ui.actionRotate->setEnabled(false);
    this->ui.actionScale->setEnabled(false);
    this->ui.actionWaves->setEnabled(false);
    qDebug() << "Empty mode: done";
}

void EditorWindow::setImageMode() {
    qDebug() << "Image mode";
    this->ui.actionOpen->setEnabled(true);
    this->ui.actionClose->setEnabled(true);
    this->ui.actionSave->setEnabled(true);
    this->ui.actionSaveAs->setEnabled(true);
    this->ui.actionQuit->setEnabled(true);

    this->ui.actionContrastLinear->setEnabled(true);
    this->ui.actionContrastRGB->setEnabled(true);
    this->ui.actionGrayWorld->setEnabled(true);

    this->ui.actionCustomFilter->setEnabled(true);
    this->ui.actionGaussianBlur->setEnabled(true);
    this->ui.actionUnsharp->setEnabled(true);
    this->ui.actionMedianFilter->setEnabled(true);

    this->ui.actionRotate->setEnabled(true);
    this->ui.actionScale->setEnabled(true);
    this->ui.actionWaves->setEnabled(true);
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
        this->setImageMode();
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
            this->setEmptyMode();
        }
    }
    else {
        this->currentImageFileName = QString();
        this->currentImage = QImage();
        this->imageScene->setEmptyMode();
        this->setEmptyMode();
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
    this->processing();
    this->replaceImage(Processing::linearContrastCorrection(this->currentImage, this->imageView->getSelection()));
    this->ready();
}

void EditorWindow::rgbContrastCorrection() {
    this->processing();
    this->replaceImage(Processing::rgbContrastCorrection(this->currentImage, this->imageView->getSelection()));
    this->ready();
}

void EditorWindow::grayWorld() {
    this->processing();
    this->replaceImage(Processing::grayWorld(this->currentImage, this->imageView->getSelection()));
    this->ready();
}

void EditorWindow::applyFilter() {
    FilterDialog dialog(this);

    if (dialog.exec()) {
        this->processing();

        this->replaceImage(Processing::applyFilter(this->currentImage, dialog.getFilter(), this->imageView->getSelection()));
    }

    this->ready();
}

void EditorWindow::gaussianBlur() {
    bool ok;
    qreal sigma = QInputDialog::getDouble(this, tr("Please, enter sigma"), tr("Sigma: "), 1.0, 0.35, 5.0, 2, &ok);
    if (ok) {
        this->processing();

        this->replaceImage(Processing::gaussianBlur(this->currentImage, sigma, this->imageView->getSelection()));
    }

    this->ready();
}

void EditorWindow::unsharp() {
    UnsharpDialog dialog(this);

    if (dialog.exec()) {
        this->processing();

        qreal sigma = dialog.getSigma();
        qreal alpha = dialog.getAlpha();
        this->replaceImage(Processing::unsharp(this->currentImage, alpha, sigma, this->imageView->getSelection()));
    }

    this->ready();
}

void EditorWindow::medianFilter() {
    bool ok;
    int size = QInputDialog::getInt(this, tr("Please, enter the filter size"), tr("Size: "), 3, 2, 50, 1, &ok);
    if (ok) {
        this->processing();

        this->replaceImage(Processing::medianFilter(this->currentImage, size, this->imageView->getSelection()));
    }

    this->ready();
}

void EditorWindow::rotate() {
    RotateDialog dialog(this);

    if (dialog.exec()) {
        this->processing();

        qreal angle = dialog.getAngle();
        QPointF center = dialog.getCenter();
        this->replaceImage(Processing::rotate(this->currentImage, angle, center, this->imageView->getSelection()));
    }

    this->ready();
}

void EditorWindow::scale() {
    ScaleDialog dialog(this);

    if (dialog.exec()) {
        this->processing();

        qreal factor = dialog.getFactor();
        QPointF center = dialog.getCenter();
        this->replaceImage(Processing::scale(this->currentImage, factor, center, this->imageView->getSelection()));
    }

    this->ready();
}

void EditorWindow::waves() {
    WavesDialog dialog(this);

    if (dialog.exec()) {
        this->processing();

        QPointF amplitude = dialog.getAmplitude();
        qreal length = dialog.getLength();
        this->replaceImage(Processing::waves(this->currentImage, amplitude, length, this->imageView->getSelection()));
    }

    this->ready();
}
