#ifndef IMAGE_SCENE_HPP
#define IMAGE_SCENE_HPP

#include <QWidget>
#include <QGraphicsScene>

class ImageScene: public QGraphicsScene {
    Q_OBJECT

  public:
    ImageScene(QWidget *parent = NULL);

    void setEmptyMode();
};

#endif  // IMAGE_SCENE_HPP
