#include "puzzle.h"
#include <QtMath>
#include <QMessageBox>


Puzzle::Puzzle(int sideSize, int imageSize, QWidget *parent)
    : QWidget{parent}, m_sideSize(sideSize), m_imageSize(imageSize)
{
    setMinimumSize(m_imageSize, m_imageSize);
    setMaximumSize(m_imageSize, m_imageSize);
    m_gridLayout = new QGridLayout(parent);
}

void Puzzle::setup(QPixmap img)
{
    if (img.isNull())
        return;


    sliceImage(img);
    setFirstBlank();
    shuffle();
    draw();
}

void Puzzle::movePiece(int id)
{
    int blankTileIndex = -1;
    int movingTileIndex = -1;
    int blankTileId = 0;

    for (int i = 0; i < m_pieces.size(); ++i)
    {
        if (m_pieces[i]->getId() == blankTileId)
            blankTileIndex = i;
        else if (m_pieces[i]->getId() == id)
            movingTileIndex = i;

        // If both elements are found, break out of the loop
        if (blankTileIndex != -1 && movingTileIndex != -1)
            break;
    }

    // if ( (qFabs(blankTileIndex - movingTileIndex) != 1) and (qFabs(blankTileIndex - movingTileIndex) != m_sideSize) )

    // Check, if selected tiles are neighbors
    if ( (qFabs(blankTileIndex - movingTileIndex) == 1) or (qFabs(blankTileIndex - movingTileIndex) == m_sideSize) )
    {
        // Swap the tiles
        if (blankTileIndex != -1 && movingTileIndex != -1)
        {
            Piece * temp = m_pieces[blankTileIndex];
            m_pieces[blankTileIndex] = m_pieces[movingTileIndex];
            m_pieces[movingTileIndex] = temp;

        }
    }

    draw();
    checkIfFinished();
}



void Puzzle::sliceImage(const QPixmap &image)
{
    int n = m_sideSize;
    int imageWidth = image.width();
    int imageHeight = image.height();
    int sliceWidth = imageWidth / n;
    int sliceHeight = imageHeight / n;
    int sliceSize = qMin(sliceWidth, sliceHeight);
    int id = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x = j * sliceWidth;
            int y = i * sliceHeight;
            QPixmap slice = image.copy(x, y, sliceSize, sliceSize);

            /* debug */
            QPainter tempPainter(&slice);
            tempPainter.setFont( QFont("Arial") );
            tempPainter.drawText(QPoint(100, 100), QString::number(id));

            Piece * piece = new Piece(id++, slice);
            connect(piece, &Piece::moveSelf, this, &Puzzle::movePiece);
            m_pieces.append(piece);
        }
    }
}

void Puzzle::draw()
{
    int row = 0;
    int col = 0;
    for (auto &piece : m_pieces)
    {
        m_gridLayout->addWidget(piece, row, col);
        if (++col >= m_sideSize)
        {
            col = 0;
            row++;
        }
    }
}

void Puzzle::clearPuzzle()
{
    QLayoutItem *oldPieceItem;
    while ((oldPieceItem = m_gridLayout->takeAt(0)) != nullptr) 
    {
        delete oldPieceItem->widget(); 
        delete oldPieceItem;
    }
    m_pieces.clear();
}

void Puzzle::shuffle()
{

}

void Puzzle::setFirstBlank()
{
    QPixmap blank(m_pieces[0]->getImage().width(), m_pieces[0]->getImage().height());
    blank.fill(Qt::transparent);
    m_pieces[0]->setPixmap(blank);
}

void Puzzle::checkIfFinished() const
{
    bool finished = true;
    int i = 0;
    for (const Piece * p : m_pieces)
    {
        if (p->getId() != i)
        {
            finished = false;
            break;
        }
        i++;
    }

    if (finished)
    {
        QMessageBox msgBox;
        msgBox.setText("Congratulations!");
        msgBox.exec();
    }
}
