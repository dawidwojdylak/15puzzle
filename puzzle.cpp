#include "puzzle.h"
#include <QtMath>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <QDebug>

Puzzle::Puzzle(int sideSize, int imageSize, QWidget *parent)
    : QWidget{parent}, m_sideSize(sideSize), m_imageSize(imageSize),
    m_userSteps(0), m_shuffleSteps(SHUFFLE_STEPS), m_tileText(true)
{
    setMinimumSize(m_imageSize, m_imageSize);
    setMaximumSize(m_imageSize, m_imageSize);
    m_gridLayout = new QGridLayout(parent);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Puzzle::setup(QPixmap img)
{
    if (img.isNull())
        return;

    m_image = img;

    sliceImage(img);
    setFirstBlank();
        shuffle();
    draw();
}

void Puzzle::setup()
{
    setup(m_image);
}

void Puzzle::movePieceByKey(Key k)
{
    int blankIdx = -1;
    // find the blank piece
    for (int i = 0; i < m_pieces.size(); ++i)
        if (m_pieces[i]->getId() == 0)
        {
            blankIdx = i;
            break;
        }


    int pieceToBeMovedIdx = -1;
    switch (k)
    {
    case KEY_DOWN:
        pieceToBeMovedIdx = blankIdx - m_sideSize;
        break;
    case KEY_UP:
        pieceToBeMovedIdx = blankIdx + m_sideSize;
        break;
    case KEY_LEFT:
        pieceToBeMovedIdx = blankIdx + 1;
        break;
    case KEY_RIGHT:
        pieceToBeMovedIdx = blankIdx - 1;
        break;
    
    default:
        break;
    }

    if (blankIdx <= m_pieces.size() and pieceToBeMovedIdx <= m_pieces.size() and blankIdx >= 0 and pieceToBeMovedIdx >= 0) 
    {
        swapPieces(blankIdx, pieceToBeMovedIdx, true);
        checkIfFinished();
    }
}

void Puzzle::undo()
{
    if (m_history.isEmpty()) return;
    std::tuple<int, int> lastMove = m_history.last();
    m_history.removeLast();

    swapPieces(std::get<1>(lastMove), std::get<0>(lastMove));

    emit updateSteps(--m_userSteps);
}

void Puzzle::replaySteps()
{
    for (auto step : m_history)
    {
        swapPieces(std::get<0>(step), std::get<1>(step));
    }
}

void Puzzle::restoreTilesPositions(const QVector<std::tuple<int, int>> &positions)
{
    QVector<Piece*> temp = m_pieces;
 
    for (const auto &pos : positions)
    {
        // qDebug() << "restore: " << std::get<0>(pos) << " : " << std::get<1>(pos);
        int index = std::get<0>(pos);
        int id = std::get<1>(pos);


        for (int i = 0; i < temp.size(); i++)
        {
            if (temp[i]->getId() == id)
            {
                QPixmap img = temp[i]->getImage();
                if (id == 0)
                    img.fill(Qt::transparent);
                Piece * piece = new Piece(id, img);
                connect(piece, &Piece::moveSelf, this, &Puzzle::movePieceById);
                if (index >= m_pieces.size())
                    m_pieces.resize(index + 1);
                
                m_pieces[index] = piece;
                break;
            }
        }
    }


    QLayoutItem *oldPieceItem;
    while ((oldPieceItem = m_gridLayout->takeAt(0)) != nullptr)
    {
        delete oldPieceItem->widget();
        delete oldPieceItem;
    }
    draw();
}

void Puzzle::setHistory(QVector<std::tuple<int, int>> historyVec)
{
    m_history.clear();
    for (auto i : historyVec)
        m_history.append(std::make_tuple(std::get<1>(i), std::get<0>(i)));
}

void Puzzle::movePieceById(int id, bool userMove)
{
    int blankTileIndex = -1;
    int movingTileIndex = -1;
    const int blankTileId = 0;

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

    swapPieces(blankTileIndex, movingTileIndex, userMove);


    if (userMove)
        checkIfFinished();
}

void Puzzle::onNumbersCheckBoxChecked(bool checked)
{
    m_tileText = checked;
    clearPuzzle();
    setup();
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

            if (m_tileText)
            {
                QPainter tempPainter(&slice);
                QRect textRect = tempPainter.boundingRect(slice.rect(), Qt::AlignCenter, QString::number(id + 1));
                QFont font("Arial");
                font.setPointSize(14);
                tempPainter.setFont(font);
                tempPainter.setPen(Qt::red);
                tempPainter.drawText(textRect, QString::number(id + 1));
            }

            Piece * piece = new Piece(id++, slice);
            connect(piece, &Piece::moveSelf, this, &Puzzle::movePieceById);
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
    m_userSteps = 0;
}

void Puzzle::shuffle()
{
    for (int i = 0; i < m_shuffleSteps * m_sideSize * m_sideSize; ++i)
    {
        int j = 0;
        for (const Piece * piece : m_pieces)
        {
            // find the blank piece
            if (piece->getId() == 0)
            {
                // get random tile to swap
                int possibleIndices[4] = {j+1, j-1, j+m_sideSize, j-m_sideSize};
                int randomIndex = std::rand() % 4;
                movePieceById(possibleIndices[randomIndex], false);
                break;
            }
            j++;
        }
    }
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
        emit puzzleFinished();
}

void Puzzle::swapPieces(int blankTileIndex, int movingTileIndex, bool userMove)
{
    if (m_pieces.size() - blankTileIndex <= 0 or m_pieces.size() - movingTileIndex <= 0)
        return;

    // Check, if selected tiles are neighbors
    if ( (qFabs(blankTileIndex - movingTileIndex) == 1) or (qFabs(blankTileIndex - movingTileIndex) == m_sideSize) )
    {
        // check if the blank tile is on the border
        if (
            ((blankTileIndex % m_sideSize == 0) and (blankTileIndex - movingTileIndex == 1))
            or 
            ((blankTileIndex % m_sideSize == m_sideSize - 1) and (blankTileIndex - movingTileIndex == -1))
        )
            return;

        // Swap the tiles
        if (blankTileIndex != -1 && movingTileIndex != -1)
        {
            Piece * temp = m_pieces[blankTileIndex];
            m_pieces[blankTileIndex] = m_pieces[movingTileIndex];
            m_pieces[movingTileIndex] = temp;
            if (userMove)
            {
                m_history.append(std::make_tuple(blankTileIndex, movingTileIndex));
                emit updateSteps(++m_userSteps);
            }
        }
    }

    draw();
}
