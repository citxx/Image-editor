#include <QApplication>
#include "EditorWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EditorWindow *window = new EditorWindow;
    window->show();

    return app.exec();
}
