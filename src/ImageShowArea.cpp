#include "ImageShowArea.hpp"

#include <QDebug>

ImageShowArea::ImageShowArea(QWidget *parent):
    QGraphicsView(parent),
    frame(NULL),
    selectionActive(false) {
    this->setMouseTracking(false);
    this->frame = new QRubberBand(QRubberBand::Rectangle, this);
}

ImageShowArea::~ImageShowArea() {
    delete this->frame;
}

QRect bound(const QPoint &start, const QPoint &end) {
    int left   = qMin(start.x(), end.x());
    int right  = qMax(start.x(), end.x());
    int top    = qMin(start.y(), end.y());
    int bottom = qMax(start.y(), end.y());
    return QRect(QPoint(left, top), QPoint(right, bottom));
}

QRectF bound(const QPointF &start, const QPointF &end) {
    int left   = qMin(start.x(), end.x());
    int right  = qMax(start.x(), end.x());
    int top    = qMin(start.y(), end.y());
    int bottom = qMax(start.y(), end.y());
    return QRectF(QPointF(left, top), QPointF(right, bottom));
}

void ImageShowArea::updateSelection() {
    this->frame->setGeometry(bound(this->selectionStart, this->selectionEnd));
    this->frame->show();
}

void ImageShowArea::mousePressEvent(QMouseEvent *event) {
    this->selectionActive = true;
    this->selectionStart = event->pos();
    this->selectionEnd = this->selectionStart;
    this->updateSelection();
}

void ImageShowArea::mouseMoveEvent(QMouseEvent *event) {
    if (this->selectionActive) {
        this->selectionEnd = event->pos();
        this->updateSelection();
    }
}

void ImageShowArea::mouseReleaseEvent(QMouseEvent *event) {
    this->selectionActive = false;
    this->selectionEnd = event->pos();
    this->updateSelection();
}

QRect ImageShowArea::getSelection() {
    QPointF start = this->mapToScene(this->selectionStart);
    QPointF end = this->mapToScene(this->selectionEnd);

    QRectF selectionRect = bound(start, end);
    QRectF imageRect = this->scene()->itemsBoundingRect().adjusted(0.0, 0.0, -1.0, -1.0);
    QRectF resultF = selectionRect & imageRect;
    if (resultF.isEmpty()) {
        resultF = imageRect;
    }
    return resultF.toAlignedRect();
}

void ImageShowArea::resetSelection() {
    this->selectionStart = QPoint();
    this->selectionEnd = QPoint();

    delete this->frame;
    this->frame = new QRubberBand(QRubberBand::Rectangle, this);
}
