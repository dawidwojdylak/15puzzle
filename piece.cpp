#include "piece.h"

Piece::Piece(const QPixmap & img, const QPoint & position, int id, QObject *parent)
    : QObject{parent}, m_id{id}
{
    m_image = img;
    m_position = position;
}

Piece::Piece(const Piece &other)
    : m_id(other.m_id), m_position(other.m_position), m_image(other.getImage())
{
    m_rect = other.m_rect;
}
