#ifndef IMAGE_SHOW_AREA_HPP
#define IMAGE_SHOW_AREA_HPP

#include <QGraphicsView>

class ImageShowArea: public QGraphicsView {
    Q_OBJECT

  public:
    ImageShowArea(QWidget *parent = NULL);
};

#endif  // IMAGE_SHOW_AREA_HPP
