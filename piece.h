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
    Piece(const Piece& other);

    inline int getId() const { return m_id; }
    inline QPoint getPosition() const { return m_position; }
    inline QPixmap getImage() const { return m_image; }
    inline QRect getRect() const { return m_rect; }
signals:

protected:
    


private:
    int m_id;
    QPoint m_position;
    QPixmap m_image;
    QRect m_rect;
};

#endif // PIECE_H
