#ifndef PUZZLE_H
#define PUZZLE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QGridLayout>
#include <QVector>
#include <memory>
#include "piece.h"

class Puzzle : public QWidget
{
    Q_OBJECT
public:
    explicit Puzzle(int sideSize = 3, int imageSize = 400, QWidget *parent = nullptr);

    void setup(QPixmap img);


signals:

protected:
//    void paintEvent(QPaintEvent *event) override;

    void sliceImage(const QPixmap& image);

private:
//    QVector<std::shared_ptr<Piece>> m_pieces;
    QVector<Piece*> m_pieces;
    int m_sideSize;
    int m_imageSize;
    QPixmap m_puzzleImage;
    QGridLayout *m_gridLayout;
};

#endif // PUZZLE_H
