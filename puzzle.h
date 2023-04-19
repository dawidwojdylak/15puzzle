#ifndef PUZZLE_H
#define PUZZLE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "piece.h"

class Puzzle : public QWidget
{
    Q_OBJECT
public:
    explicit Puzzle(int sideSize = 3, int imageSize = 400, QWidget *parent = nullptr);

    void setup(QPixmap img);


signals:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<Piece> m_pieces;
    int m_sideSize;
    int m_imageSize;
    int m_pieceSize;
    QPixmap m_puzzleImage;
};

#endif // PUZZLE_H
