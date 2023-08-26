#ifndef PUZZLE_H
#define PUZZLE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QGridLayout>
#include <QVector>
#include <memory>
#include "piece.h"

#define SHUFFLE_STEPS 30


class Puzzle : public QWidget
{
    Q_OBJECT
public:
    enum Key {
        KEY_DOWN,
        KEY_UP,
        KEY_LEFT,
        KEY_RIGHT
    };

    explicit Puzzle(int sideSize = 3, int imageSize = 400, QWidget *parent = nullptr);

    void setup(QPixmap img);
    void clearPuzzle();
    void movePieceByKey(Key k);

public slots:
    void movePieceById(int id, bool userMove = true);

signals:
    void updateSteps(int step);

protected:
    void sliceImage(const QPixmap& image);
    void draw();
    void shuffle();
    void setFirstBlank();
    void checkIfFinished() const;
    void swapPieces(int blankTileIndex, int movingTileIndex, bool userMove = false);

private:
    QVector<Piece*> m_pieces;
    int m_sideSize;
    int m_imageSize;
    QPixmap m_puzzleImage;
    QGridLayout *m_gridLayout;
    unsigned int m_userSteps;
};

#endif // PUZZLE_H
