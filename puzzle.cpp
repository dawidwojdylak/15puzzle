#include "puzzle.h"


Puzzle::Puzzle(int sideSize, int imageSize, QWidget *parent)
    : QWidget{parent}, m_sideSize(sideSize), m_imageSize(imageSize)
{
    m_pieceSize = m_imageSize / m_sideSize;
    setMinimumSize(m_imageSize, m_imageSize);
    setMaximumSize(m_imageSize, m_imageSize);
}

void Puzzle::setup(QPixmap img)
{
    if (img.isNull())
        return;

    int size = qMin(img.width(), img.height());
    m_puzzleImage = img.copy((img.width() - size) / 2,
        (img.height() - size) / 2, size, size).scaled(width(),
            height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    for (int y = 0; y < m_sideSize - 1; y++)
    {
        for (int x = 0; x < m_sideSize; x++)
        {
            QPixmap piecePixmap = m_puzzleImage.copy(x * m_pieceSize, y * m_pieceSize, m_pieceSize, m_pieceSize);
            Piece piece(piecePixmap, QPoint(x, y), x + y);
            m_pieces.push_back(piece);
        }
    }

//    QPainter painter(this);
//    for (const Piece & p : m_pieces)
//        painter.drawPixmap(p.getRect(), p.getImage());
}

void Puzzle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::white);
    for (const Piece & p : m_pieces)
        painter.drawPixmap(p.getRect(), p.getImage());
}   
