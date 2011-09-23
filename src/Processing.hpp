#ifndef PROCESSING_HPP
#define PROCESSING_HPP

#include <QImage>
#include <QVector>

#include "Filter.hpp"

namespace Processing {
    QImage linearContrastCorrection(const QImage &img, QRect area = QRect());
    QImage rgbContrastCorrection(const QImage &img, QRect area = QRect());
    QImage grayWorld(const QImage &img, QRect area = QRect());

    QImage applyFilter(const QImage &img, const Filter &filter, QRect area = QRect());
    QImage applySimpleSeparateFilter(const QImage &img, const Filter &filter, QRect area = QRect());
    QImage gaussianBlur(const QImage &img, qreal sigma, QRect area = QRect());
    QImage unsharp(const QImage &img, qreal alpha, qreal sigma, QRect area = QRect());
    QImage medianFilter(const QImage &img, int size, QRect area = QRect());

    QImage rotate(const QImage &img, qreal angle, QPointF center = QPointF(), QRect area = QRect());
    QImage scale(const QImage &img, qreal factor, QPointF center = QPointF(), QRect area = QRect());
    QImage waves(const QImage &img, QPointF amplitude, qreal length, QRect area = QRect());
}

#endif  // PROCESSING_HPP
