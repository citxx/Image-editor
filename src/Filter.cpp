#include "Filter.hpp"

Filter::Filter(int width, int height):
    body(height, QVector <qreal>(width, 0.0)) {
}

const qreal & Filter::at(int x, int y) const {
    return this->body[x][y];
}

qreal & Filter::at(int x, int y) {
    return this->body[x][y];
}

int Filter::width() const {
    return this->body[0].size();
}

int Filter::height() const {
    return this->body.size();
}
