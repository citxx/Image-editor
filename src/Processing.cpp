#include "Processing.hpp"
#include <QtGlobal>
#include <QPoint>
#include <QRect>
#include <QDebug>
#include <QtAlgorithms>
#include <cmath>
#include <QtCore/qmath.h>

QRgb DEFAULT_COLOR = qRgb(0, 0, 0);

qreal brightness(QRgb color) {
    return 0.2125 * qRed(color) + 0.7154 * qGreen(color) + 0.0721 * qBlue(color);
}

int expand(qreal minX, qreal maxX, int x) {
    int result = (x - minX) * 256.0 / (maxX + 1 - minX);
    if (result < 0 || 255 < result) {
        qDebug() << "expand(" << minX << ", " << maxX << ", " << x <<
                           "): invalid return value (" << result << ")";
    }
    return result;
}

QImage Processing::linearContrastCorrection(const QImage &img) {
    qreal minBrightness, maxBrightness;
    minBrightness = maxBrightness = brightness(img.pixel(0,0));
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            qreal br = brightness(img.pixel(x, y));
            minBrightness = qMin(minBrightness, br);
            maxBrightness = qMax(maxBrightness, br);
        }
    }

    qDebug() << "Linear contrast correction: minBrightness(" << minBrightness <<
                ") maxBrightness(" << maxBrightness << ")";

    QImage answer(img.width(), img.height(), img.format());
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            QRgb color = img.pixel(x, y);
            qreal br = brightness(color);
            qreal new_br = expand(minBrightness, maxBrightness, br);
            qreal c = new_br / br;
            answer.setPixel(x, y, qRgb(c * qRed(color), c * qGreen(color), c * qBlue(color)));
        }
    }

    return answer;
}

QImage Processing::rgbContrastCorrection(const QImage &img) {
    int minR, maxR;
    int minG, maxG;
    int minB, maxB;
    QRgb initColor = img.pixel(0,0);
    minR = maxR = qRed(initColor);
    minG = maxG = qGreen(initColor);
    minB = maxB = qBlue(initColor);
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            QRgb color = img.pixel(x, y);

            minR = qMin(minR, qRed(color));
            maxR = qMax(maxR, qRed(color));
            minG = qMin(minG, qGreen(color));
            maxG = qMax(maxG, qGreen(color));
            minB = qMin(minB, qBlue(color));
            maxB = qMax(maxB, qBlue(color));
        }
    }

    qDebug() << "RGB contrast correction: minR(" << minR <<") maxR(" << maxR << ")";
    qDebug() << "RGB contrast correction: minG(" << minG <<") maxG(" << maxG << ")";
    qDebug() << "RGB contrast correction: minB(" << minB <<") maxB(" << maxB << ")";

    QImage answer(img.size(), img.format());
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            QRgb color = img.pixel(x, y);
            int r = expand(minR, maxR, qRed(color));
            int g = expand(minG, maxG, qGreen(color));
            int b = expand(minB, maxB, qBlue(color));
            answer.setPixel(x, y, qRgb(r, g, b));
        }
    }

    return answer;
}

QImage Processing::grayWorld(const QImage &img) {
    qreal sumR = 0.0, sumG = 0.0, sumB = 0.0;
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            QRgb color = img.pixel(x, y);
            sumR += qRed(color);
            sumG += qGreen(color);
            sumB += qBlue(color);
        }
    }
    int count = img.width() * img.height();
    qreal avgR = sumR / count, avgG = sumG / count, avgB = sumB / count;
    qreal avg = (avgR + avgG + avgB) / 3.0;

    QImage result(img.size(), img.format());
    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            QRgb color = img.pixel(x, y);
            int r = qBound(0, (int)(qRed(color) * avg / avgR), 255);
            int g = qBound(0, (int)(qGreen(color) * avg / avgG), 255);
            int b = qBound(0, (int)(qBlue(color) * avg / avgB), 255);
            result.setPixel(x, y, qRgb(r, g, b));
        }
    }

    return result;
}

QRgb applyToPoint(int x, int y, const QImage &img, const Filter &filter) {
    qreal resultR = 0.0, resultG = 0.0, resultB = 0.0;
    for (int fx = 0; fx < filter.width(); fx++) {
        for (int fy = 0; fy < filter.height(); fy++) {
            int imgX = qBound(0, x + (fx - filter.width() / 2), img.width() - 1);
            int imgY = qBound(0, y + (fy - filter.height() / 2), img.height() - 1);
            QRgb color = img.pixel(imgX, imgY);
            resultR += filter.at(fx, fy) * qRed(color);
            resultG += filter.at(fx, fy) * qGreen(color);
            resultB += filter.at(fx, fy) * qBlue(color);
        }
    }

    int r = qBound(0, (int)resultR, 255);
    int g = qBound(0, (int)resultG, 255);
    int b = qBound(0, (int)resultB, 255);
    return qRgb(r, g, b);
}

QImage Processing::applyFilter(const QImage &img, const Filter &filter) {
    QImage answer(img.size(), img.format());

    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            answer.setPixel(x, y, applyToPoint(x, y, img, filter));
        }
    }

    return answer;
}

QImage Processing::applySimpleSeparateFilter(const QImage &img, const Filter &filter) {
    return applyFilter(applyFilter(img, filter), filter.transposed());
}

Filter getGaussianFilter(qreal sigma) {
    int filterSize = (int)(6 * sigma);
    if (filterSize % 2 == 0) {
        filterSize += 1;
    }

    Filter gaussian(1, filterSize);
    int center = filterSize / 2;
    for (int i = 0; i < filterSize; i++) {
        int x = i - center;
        gaussian.at(0, i) = qExp(-(x * x) / (2 * sigma * sigma)) / (qSqrt(2 * M_PI) * sigma);
    }

    return gaussian.normalized();
}

QImage Processing::gaussianBlur(const QImage &img, qreal sigma) {
    qDebug() << "Gaussian blur: sigma(" << sigma << ")";

    return Processing::applySimpleSeparateFilter(img, getGaussianFilter(sigma));
}

QImage Processing::unsharp(const QImage &img, qreal alpha, qreal sigma) {
    Filter gaussian = getGaussianFilter(sigma);
    Filter unsharpFilter = (1 + alpha) * Filter::single(gaussian) - alpha * gaussian;

    return Processing::applyFilter(img, unsharpFilter);
}

qreal linearInterpolation(
    qreal left,
    qreal right,
    qreal leftValue,
    qreal rightValue,
    qreal x) {

    return ((x - left) * rightValue + (right - x) * leftValue) / (right - left);
}

qreal belinearInterpolation(
    QRect r,
    qreal ltValue,
    qreal lbValue,
    qreal rbValue,
    qreal rtValue,
    qreal x, qreal y) {

    qreal p1 = linearInterpolation(r.left(), r.left() + r.width(), ltValue, rtValue, x);
    qreal p2 = linearInterpolation(r.left(), r.left() + r.width(), lbValue, rbValue, x);
    qreal result = linearInterpolation(r.top(), r.top() + r.height(), p1, p2, y);
    return result;
}

QRgb belinearColorInterpolation(
    QRect rt,
    QRgb ltValue,
    QRgb lbValue,
    QRgb rbValue,
    QRgb rtValue,
    qreal x, qreal y) {

    int r = (int)belinearInterpolation(rt, qRed(ltValue),
                                           qRed(lbValue),
                                           qRed(rbValue),
                                           qRed(rtValue), x, y);
    int g = (int)belinearInterpolation(rt, qGreen(ltValue),
                                           qGreen(lbValue),
                                           qGreen(rbValue),
                                           qGreen(rtValue), x, y);
    int b = (int)belinearInterpolation(rt, qBlue(ltValue),
                                           qBlue(lbValue),
                                           qBlue(rbValue),
                                           qBlue(rtValue), x, y);
    return qRgb(r, g, b);
}

bool rgbLess(const QRgb &a, const QRgb &b) {
    return brightness(a) < brightness(b);
}

QRgb medianPoint(int x, int y, const QImage &img, int size) {
    QList <QRgb> vicinity;
    for (int fx = 0; fx < size; fx++) {
        for (int fy = 0; fy < size; fy++) {
            int imgX = x + (fx - size / 2);
            int imgY = y + (fy - size / 2);
            if (qBound(0, imgX, img.width() - 1) == imgX &&
                qBound(0, imgY, img.height() - 1) == imgY) {
                vicinity.append(img.pixel(imgX, imgY));
            }
        }
    }

    qSort(vicinity.begin(), vicinity.end());

    return vicinity[vicinity.size() / 2];
}

QImage Processing::medianFilter(const QImage &img, int size) {
    QImage answer(img.size(), img.format());

    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            answer.setPixel(x, y, medianPoint(x, y, img, size));
        }
    }

    return answer;
}

QImage Processing::rotate(const QImage &img, qreal angleG, QPointF center, QRect area) {
    if (center.isNull()) {
        center = QPointF(0.0, 0.0);
    }
    if (area.isNull()) {
        area = QRect(0, 0, img.width() - 1, img.height() - 1);
    }
    qreal angle = angleG * M_PI / 180.0;

    center += QPointF(area.left() + area.width() / 2.0, area.top() + area.height() / 2.0);

    qDebug() << "Rotate: center(" << center << "), area(" << area << ")";

    QImage result(img);

    for (int x = area.left(); x <= area.right(); x++) {
        for (int y = area.top(); y <= area.bottom(); y++) {
            result.setPixel(x, y, DEFAULT_COLOR);
        }
    }

    for (int x = 0; x < result.width(); x++) {
        for (int y = 0; y < result.height(); y++) {
            QPointF relative = QPointF(x, y) - center;
            qreal sourceX = center.x() + relative.x() * qCos(-angle) + relative.y() * qSin(-angle);
            qreal sourceY = center.y() - relative.x() * qSin(-angle) + relative.y() * qCos(-angle);

            if (QRectF(area).contains(sourceX, sourceY)) {
                int left, top;
                int sx = (int)sourceX;
                int sy = (int)sourceY;

                if (sx + 1 >= area.right()) {
                    left = sx - 1;
                }
                else {
                    left = sx;
                }

                if (sy + 1 >= area.bottom()) {
                    top = sy - 1;
                }
                else {
                    top = sy;
                }

                result.setPixel(x, y, belinearColorInterpolation(
                    QRect(left, top, 1, 1),
                    img.pixel(left, top),
                    img.pixel(left, top + 1),
                    img.pixel(left + 1, top + 1),
                    img.pixel(left + 1, top),
                    sourceX, sourceY
                ));
            }
        }
    }

    return result;
}

QImage Processing::scale(const QImage &img, qreal factor, QPointF center, QRect area) {
    if (center.isNull()) {
        center = QPointF(0.0, 0.0);
    }
    if (area.isNull()) {
        area = QRect(0, 0, img.width() - 1, img.height() - 1);
    }

    center += QPointF(area.left() + area.width() / 2.0, area.top() + area.height() / 2.0);

    qDebug() << "Rotate: center(" << center << "), area(" << area << ")";

    QImage result(img);

    for (int x = area.left(); x <= area.right(); x++) {
        for (int y = area.top(); y <= area.bottom(); y++) {
            result.setPixel(x, y, DEFAULT_COLOR);
        }
    }

    for (int x = 0; x < result.width(); x++) {
        for (int y = 0; y < result.height(); y++) {
            QPointF relative = QPointF(x, y) - center;
            qreal sourceX = center.x() + relative.x() / factor;
            qreal sourceY = center.y() + relative.y() / factor;

            if (QRectF(area).contains(sourceX, sourceY)) {
                int left, top;
                int sx = (int)sourceX;
                int sy = (int)sourceY;

                if (sx + 1 >= area.right()) {
                    left = sx - 1;
                }
                else {
                    left = sx;
                }

                if (sy + 1 >= area.bottom()) {
                    top = sy - 1;
                }
                else {
                    top = sy;
                }

                result.setPixel(x, y, belinearColorInterpolation(
                    QRect(left, top, 1, 1),
                    img.pixel(left, top),
                    img.pixel(left, top + 1),
                    img.pixel(left + 1, top + 1),
                    img.pixel(left + 1, top),
                    sourceX, sourceY
                ));
            }
        }
    }

    return result;
}

QImage Processing::waves(const QImage &img, QPointF amplitude, QPointF length, QRect area) {
    if (area.isNull()) {
        area = QRect(0, 0, img.width() - 1, img.height() - 1);
    }

    QImage result(img);

    for (int x = 0; x < result.width(); x++) {
        for (int y = 0; y < result.height(); y++) {
            qreal sourceX = x + amplitude.x() * qSin(2 * M_PI * y / length.x());
            qreal sourceY = y + amplitude.y() * qSin(2 * M_PI * x / length.y());

            if (QRectF(area).contains(sourceX, sourceY)) {
                int left, top;
                int sx = (int)sourceX;
                int sy = (int)sourceY;

                if (sx + 1 >= area.right()) {
                    left = sx - 1;
                }
                else {
                    left = sx;
                }

                if (sy + 1 >= area.bottom()) {
                    top = sy - 1;
                }
                else {
                    top = sy;
                }

                result.setPixel(x, y, belinearColorInterpolation(
                    QRect(left, top, 1, 1),
                    img.pixel(left, top),
                    img.pixel(left, top + 1),
                    img.pixel(left + 1, top + 1),
                    img.pixel(left + 1, top),
                    sourceX, sourceY
                ));
            }
        }
    }

    return result;
}
