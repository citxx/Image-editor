#ifndef PROCESSING_HPP
#define PROCESSING_HPP

#include <QImage>
#include <QVector>

#include "Filter.hpp"

namespace Processing {
    QImage linearContrastCorrection(const QImage &img);
    QImage rgbContrastCorrection(const QImage &img);

    QImage applyFilter(const QImage &img, const Filter &filter);
    QImage applySimpleSeparateFilter(const QImage &img, const Filter &filter);
    QImage gaussianBlur(const QImage &img, qreal sigma);
    QImage unsharp(const QImage &img, qreal alpha, qreal sigma);

    QImage rotate(const QImage &img, QPointF center, qreal angle, QRect area = QRect());
}

#endif  // PROCESSING_HPP
