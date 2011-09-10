#include "EditorWindow.hpp"
#include "ui_EditorWindow.h"

EditorWindow::EditorWindow(QWidget *parent): QMainWindow(parent) {
    Ui::EditorWindow editorWindowUI;
    editorWindowUI.setupUi(this);
}
