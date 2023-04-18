#ifndef PUZZLE_H
#define PUZZLE_H

#include <QWidget>
#include "piece.h"

class Puzzle : public QWidget
{
    Q_OBJECT
public:
    explicit Puzzle(QWidget *parent = nullptr);

signals:

private:
    std::vector<std::pair<Piece, int>> m_pieces;
    int m_side_size;
};

#endif // PUZZLE_H
