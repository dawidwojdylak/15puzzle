#include "piece.h"

Piece::Piece(const QPixmap & img, const QPoint & position, int id, QObject *parent)
    : QObject{parent}, m_id{id}
{
    m_image = img;
    m_position = position;
}
