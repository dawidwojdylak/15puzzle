#include "piece.h"

Piece::Piece(int id, const QPixmap & img) : m_id{id}, m_image{img}
{
    setPixmap(m_image);
}

Piece::Piece(const Piece &other)
: m_id{other.m_id}, m_image{other.m_image} {}

void Piece::mousePressEvent(QMouseEvent *event)
{
    emit moveSelf(m_id, true);
}
