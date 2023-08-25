#include "piece.h"

// Piece::Piece(const QPixmap & img, const QPoint & position, int id, QWidget *parent)
//     : QLabel{parent}, m_id{id}
// {
//     m_image = img;
//     m_position = position;
// }

Piece::Piece(int id, const QPixmap & img) : m_id{id}, m_image{img}
{
    setPixmap(m_image);
}

//Piece::Piece(const Piece &other)
//    : m_id(other.m_id), m_position(other.m_position), m_image(other.getImage())
//{
//    m_rect = other.m_rect;
//}

void Piece::mousePressEvent(QMouseEvent *event)
{
    emit moveSelf(m_id);
    QLabel::mousePressEvent(event);
}
