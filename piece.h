#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QLabel>


class Piece : public QLabel
{
    Q_OBJECT
public:
    explicit Piece(int id, const QPixmap & img);
    Piece(const Piece &other);

    inline int getId() const { return m_id; }
    inline QPixmap getImage() const { return m_image.copy(); }
signals:
    void moveSelf(int id, bool checkIfFinished);
protected:
    void mousePressEvent(QMouseEvent* event);

private:
    int m_id;
    QPixmap m_image;
};

#endif // PIECE_H
