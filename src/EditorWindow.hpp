#ifndef EDITOR_WINDOW_HPP
#define EDITOR_WINDOW_HPP

#include <QMainWindow>
#include "ui_EditorWindow.h"

class EditorWindow: public QMainWindow {
    Q_OBJECT

    Ui::EditorWindow *ui;

  public:
    EditorWindow(QWidget *parent = NULL);
    ~EditorWindow();
};

#endif  // EDITOR_WINDOW_HPP
