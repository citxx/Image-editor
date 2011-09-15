#ifndef EDITOR_WINDOW_HPP
#define EDITOR_WINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include "ImageScene.hpp"
#include "ui_EditorWindow.h"

class EditorWindow: public QMainWindow {
    Q_OBJECT

    Ui::EditorWindow *ui;

    QImage currentImage;
    QString currentImageFileName;
    ImageScene *imageScene;

    QString chooseImageFile(QFileDialog::FileMode);  // TODO: make static

  public slots:
    void openImage();
    void closeImage();
    void saveImage();
    void saveImageAs();

  public:
    EditorWindow(QWidget *parent = NULL);
    ~EditorWindow();
};

#endif  // EDITOR_WINDOW_HPP
