#include "ImageScene.hpp"

ImageScene::ImageScene(QWidget *parent): QGraphicsScene(parent) {
    this->setEmptyMode();
}

void ImageScene::centralize() {
    this->setSceneRect(this->itemsBoundingRect());
}

void ImageScene::setEmptyMode() {
    this->clear();
    this->addText(tr("Load an image"));
    this->centralize();
}

void ImageScene::setImageMode(const QPixmap &image) {
    this->clear();
    this->addPixmap(image);
    this->centralize();
}
