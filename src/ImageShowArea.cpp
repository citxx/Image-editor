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

void ImageShowArea::updateSelection() {
    int left   = qMin(this->selectionStart.x(), this->selectionEnd.x());
    int right  = qMax(this->selectionStart.x(), this->selectionEnd.x());
    int top    = qMin(this->selectionStart.y(), this->selectionEnd.y());
    int bottom = qMax(this->selectionStart.y(), this->selectionEnd.y());
    this->frame->setGeometry(left, top, right - left + 1, bottom - top + 1);
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
