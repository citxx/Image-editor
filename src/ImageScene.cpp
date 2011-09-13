#include "ImageScene.hpp"

ImageScene::ImageScene(QWidget *parent): QGraphicsScene(parent) {
    this->setEmptyMode();
}

void ImageScene::setEmptyMode() {
    this->clear();
    this->addText(tr("Load image"));
}

void ImageScene::setImageMode(const QPixmap &image) {
    this->clear();
    this->addPixmap(image);
}
