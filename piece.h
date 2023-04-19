#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QLabel>

#include <QDebug>

class Piece : public QLabel
{
    Q_OBJECT
public:
    explicit Piece(const QPixmap & img, const QPoint & position, int id, QWidget *parent = nullptr);
    explicit Piece(int id);
    Piece(const Piece& other);

    inline int getId() const { return m_id; }
    inline QPoint getPosition() const { return m_position; }
    inline QPixmap getImage() const { return m_image; }
    inline QRect getRect() const { return m_rect; }
signals:

    void idChanged(int newId); // Declare custom signal for id change

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    int m_id;
    QPoint m_position;
    QPixmap m_image;
    QRect m_rect;
};

#endif // PIECE_H
