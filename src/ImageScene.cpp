#include "ImageScene.hpp"

ImageScene::ImageScene(QWidget *parent): QGraphicsScene(parent) {
    this->setEmptyMode();
}

void ImageScene::setEmptyMode() {
    this->clear();
    this->addText(tr("Load image"));
}
