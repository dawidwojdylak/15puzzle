#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QPoint>
#include <QPixmap>

class Piece : public QObject
{
    Q_OBJECT
public:
    explicit Piece(const QPixmap & img, const QPoint & position, int id, QObject *parent = nullptr);

signals:

private:
    int m_id;
    QPoint m_position;
    QPixmap m_image;
};

#endif // PIECE_H
