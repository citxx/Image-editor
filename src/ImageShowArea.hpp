#ifndef IMAGE_SHOW_AREA_HPP
#define IMAGE_SHOW_AREA_HPP

#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QRubberBand>
#include <QRect>

class ImageShowArea: public QGraphicsView {
    Q_OBJECT

    QRubberBand *frame;
    QPoint selectionStart;
    QPoint selectionEnd;
    bool selectionActive;

    void updateSelection();

  protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

  public:
    ImageShowArea(QWidget *parent = NULL);
    ~ImageShowArea();

    QRect getSelection();
    void resetSelection();
};

#endif  // IMAGE_SHOW_AREA_HPP
