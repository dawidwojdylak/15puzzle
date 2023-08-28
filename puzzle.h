#ifndef PUZZLE_H
#define PUZZLE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QGridLayout>
#include <QVector>
#include <tuple>
#include <memory>
#include "piece.h"

#define SHUFFLE_STEPS 1


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
    void undo();
    void replaySteps();

    inline unsigned getUserSteps() const { return m_userSteps; }
    inline QVector<std::tuple<int, int>> getHistory() const { return m_history; }
    void setHistory(QVector<std::tuple<int, int>> historyVec);
    inline void setUserSteps(int steps) { m_userSteps = steps; }
    inline void setShuffleSteps(int steps) { m_shuffleSteps = steps; }
    inline void setSideSize(int size) { m_sideSize = size; }
    inline int getSideSize() const { return m_sideSize; }

public slots:
    void movePieceById(int id, bool userMove = true);

signals:
    void updateSteps(int step);
    void puzzleFinished() const;

protected:
    void sliceImage(const QPixmap& image);
    void draw();
    void shuffle();
    void setFirstBlank();
    void checkIfFinished() const;
    void swapPieces(int blankTileIndex, int movingTileIndex, bool userMove = false);

private:
    QVector<Piece*> m_pieces;
    QVector<std::tuple<int, int>> m_history;
    int m_sideSize;
    int m_imageSize;
    QPixmap m_puzzleImage;
    QGridLayout *m_gridLayout;
    unsigned int m_userSteps;
    int m_shuffleSteps;
};

#endif // PUZZLE_H
