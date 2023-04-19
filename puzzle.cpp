#include "puzzle.h"


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
    shuffle();
    draw();
}

void Puzzle::movePiece(int id)
{
//    if (id == 0) // the blank tile
//    {
//        return;
//    }

    qDebug() << "movePiece: " << id;
    int blankTileIndex = -1;
    int index2 = -1;
    int blankTileId = 0;



    for (int i = 0; i < m_pieces.size(); ++i)
    {
        if (m_pieces[i]->getId() == blankTileId)
            blankTileIndex = i;
        else if (m_pieces[i]->getId() == id)
            index2 = i;

        // If both elements are found, break out of the loop
        if (blankTileIndex != -1 && index2 != -1)
            break;
    }

        qDebug() << "blankTileIndex: " << blankTileIndex << "\nindex2: " << index2;

    if (blankTileIndex != -1 && index2 != -1)
    {
        QPixmap blank = m_pieces[blankTileIndex]->getImage().copy();
        blank.fill(Qt::transparent);
//        m_pieces[blankTileIndex]->setPixmap(blank);

        Piece * newBlankPiece = new Piece(blankTileId, blank);
        Piece * newPiece = new Piece(id, m_pieces[index2]->getImage());

        connect(newBlankPiece, &Piece::moveSelf, this, &Puzzle::movePiece);
        connect(newPiece, &Piece::moveSelf, this, &Puzzle::movePiece);

//        delete m_pieces[blankTileIndex];
//        delete m_pieces[index2];

//        m_pieces.replace(blankTileIndex, newPiece);
//        m_pieces.replace(index2, newBlankPiece);

        m_pieces[blankTileIndex] = newPiece;
        m_pieces[index2] = newBlankPiece;

    }

//    if (id != 0) // the blank tile
//    {
//        // find index of
//        for (int i = 0; i < m_pieces.size(); ++i)
//        {
//            qDebug() << m_pieces[i]->getId();
//            if (m_pieces[i]->getId() == id)
//            {
//                m_pieces.replace(0, m_pieces[i]);
//                break;
//            }
//        }
//    }


    // debug vec printing
    for (const auto & i : m_pieces)
        qDebug() << "id: " << i->getId();

//    m_pieces.clear();
//    clearPuzzle();

    draw();
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
//    QLayoutItem* item;
//    while ((item = m_gridLayout->takeAt(0)) != nullptr)
//    {
//        m_gridLayout->removeItem(item);
//        delete item->widget(); // Delete the widget associated with the item
//        delete item; // Delete the item
//    }
//    update();
//    repaint();
//    m_gridLayout->update();

//    while (QLayoutItem* item = m_gridLayout->takeAt(0)) {
//        QWidget* widget = item->widget();
//        if (widget) {
//            m_gridLayout->removeWidget(widget);
//            delete widget;
//        }
//        delete item;
//    }

//    QLayoutItem* item;
//    while ((item = m_gridLayout->takeAt(0)) != nullptr)
//    {
//        QWidget* widget = item->widget();
//        m_gridLayout->removeItem(item);
////        delete widget;
//    }
//        update();
//        repaint();

}

void Puzzle::shuffle()
{
    QPixmap blank(m_pieces[0]->getImage().width(), m_pieces[0]->getImage().height());
    blank.fill(Qt::transparent);
    m_pieces[0]->setPixmap(blank);
}


