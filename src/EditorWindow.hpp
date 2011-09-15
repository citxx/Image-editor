#ifndef EDITOR_WINDOW_HPP
#define EDITOR_WINDOW_HPP

#include <QMainWindow>
#include <QImage>
#include "ImageScene.hpp"
#include "ui_EditorWindow.h"

class EditorWindow: public QMainWindow {
    Q_OBJECT

    Ui::EditorWindow *ui;

    QImage currentImage;
    ImageScene *imageScene;

  public slots:
    void openImage();
    void closeImage();

  public:
    EditorWindow(QWidget *parent = NULL);
    ~EditorWindow();
};

#endif  // EDITOR_WINDOW_HPP
