#ifndef EDITOR_WINDOW_HPP
#define EDITOR_WINDOW_HPP

#include <QMainWindow>

class EditorWindow: public QMainWindow {
    Q_OBJECT

  public:
    EditorWindow(QWidget *parent = NULL);
};

#endif  // EDITOR_WINDOW_HPP
