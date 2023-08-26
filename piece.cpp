#include "piece.h"

Piece::Piece(int id, const QPixmap & img) : m_id{id}, m_image{img}
{
    setPixmap(m_image);
}

void Piece::mousePressEvent(QMouseEvent *event)
{
    emit moveSelf(m_id, true);
    QLabel::mousePressEvent(event);
}
