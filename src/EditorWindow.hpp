#ifndef EDITOR_WINDOW_HPP
#define EDITOR_WINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include "ImageScene.hpp"
#include "ImageShowArea.hpp"
#include "ui_EditorWindow.h"

class EditorWindow: public QMainWindow {
    Q_OBJECT

    Ui::EditorWindow ui;
    ImageShowArea *imageView;

    QImage currentImage;
    QString currentImageFileName;
    ImageScene *imageScene;
    bool imageChanged;

    QString chooseImageFile(QFileDialog::FileMode);  // TODO: make static
    void replaceImage(const QImage &img);
    void processing();
    void ready();

  private slots:
    void openImage();
    void closeImage();
    void saveImage();
    void saveImageAs();

    void linearContrastCorrection();
    void rgbContrastCorrection();
    void grayWorld();

    void applyFilter();
    void gaussianBlur();
    void unsharp();
    void medianFilter();

    void rotate();
    void scale();
    void waves();

  public:
    EditorWindow(QWidget *parent = NULL);
    ~EditorWindow();
};

#endif  // EDITOR_WINDOW_HPP
