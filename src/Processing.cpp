#include "Processing.hpp"
#include <QtGlobal>
#include <QPoint>
#include <QRect>
#include <QDebug>

Filter Processing::normalized(Filter filter) {
    qreal sum = 0.0;
    for (int i = 0; i < filter.size(); i++) {
        for (int j = 0; j < filter[i].size(); i++) {
            sum += filter[i][j];
        }
    }

    Filter normalizedFilter(filter);
    for (int i = 0; i < filter.size(); i++) {
        for (int j = 0; j < filter[i].size(); i++) {
            normalizedFilter[i][j] = filter[i][j] / sum;
        }
    }

    return normalizedFilter;
}

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

QRgb applyToPoint(int x, int y, const QImage &img, const Processing::Filter &kernel) {
    int filterWidth = kernel.size();
    int filterHeight = kernel[0].size();

    qreal resultR = 0.0, resultG = 0.0, resultB = 0.0;
    for (int fx = 0; fx < filterWidth; fx++) {
        for (int fy = 0; fy < filterHeight; fy++) {
            int imgX = qBound(0, x + (fx - filterWidth / 2), img.width() - 1);
            int imgY = qBound(0, y + (fy - filterHeight / 2), img.height() - 1);
            QRgb color = img.pixel(imgX, imgY);
            resultR += kernel[fx][fy] * qRed(color);
            resultG += kernel[fx][fy] * qGreen(color);
            resultB += kernel[fx][fy] * qBlue(color);
        }
    }

    int r = qBound(0, (int)resultR, 255);
    int g = qBound(0, (int)resultG, 255);
    int b = qBound(0, (int)resultB, 255);
    return qRgb(r, g, b);
}

QImage Processing::applyFilter(const QImage &img, const Processing::Filter &kernel) {
    QImage answer(img.size(), img.format());

    for (int x = 0; x < img.width(); x++) {
        for (int y = 0; y < img.height(); y++) {
            answer.setPixel(x, y, applyToPoint(x, y, img, kernel));
        }
    }

    return answer;
}

QImage Processing::gaussianBlur(qreal sigma) {

}
