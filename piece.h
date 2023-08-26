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
    explicit Piece(int id, const QPixmap & img);

    inline int getId() const { return m_id; }
    inline QPoint getPosition() const { return m_position; }
    inline QPixmap getImage() const { return m_image.copy(); }
    inline QRect getRect() const { return m_rect; }
signals:
    void moveSelf(int id, bool checkIfFinished);
protected:
    void mousePressEvent(QMouseEvent* event);

private:
    int m_id;
    QPoint m_position;
    QPixmap m_image;
    QRect m_rect;
};

#endif // PIECE_H
