#include <QApplication>
#include <QMainWindow>
#include "ui_editor.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Ui::EditorWindow editorWindow;
    QMainWindow *window = new QMainWindow;
    editorWindow.setupUi(window);
    window->show();

    return app.exec();
}
