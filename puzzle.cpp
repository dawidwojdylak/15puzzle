#include "puzzle.h"


Puzzle::Puzzle(int sideSize, int imageSize, QWidget *parent)
    : QWidget{parent}, m_sideSize(sideSize), m_imageSize(imageSize)
{
//    m_pieceSize = m_imageSize / m_sideSize;
    setMinimumSize(m_imageSize, m_imageSize);
    setMaximumSize(m_imageSize, m_imageSize);
    m_gridLayout = new QGridLayout(parent);
}

void Puzzle::setup(QPixmap img)
{
    if (img.isNull())
        return;


    sliceImage(img);
//    int row = 0;
//    int col = 0;
//    for (const QPixmap &slice : slices) {
//        QLabel *label = new QLabel();
//        label->setPixmap(slice);
//        m_gridLayout->addWidget(label, row, col); // Add label to layout with row and column
//        col++; // Move to next column
//        if (col == 3) {
//            col = 0; // Reset column and move to next row
//            row++;
//        }
//    }


}

//void Puzzle::paintEvent(QPaintEvent *event)
//{
////    QPainter painter(this);
////    painter.fillRect(event->rect(), Qt::white);
////    for (const Piece & p : m_pieces)
//    //        painter.drawPixmap(p.getRect(), p.getImage());
//}

void Puzzle::sliceImage(const QPixmap &image)
{
    int n = m_sideSize;
    int imageWidth = image.width();
    int imageHeight = image.height();
    int sliceWidth = imageWidth / n;
    int sliceHeight = imageHeight / n;
    int sliceSize = qMin(sliceWidth, sliceHeight); // Use minimum of sliceWidth and sliceHeight as side length for square slices
    int id = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = j * sliceWidth;
            int y = i * sliceHeight;
            QPixmap slice = image.copy(x, y, sliceSize, sliceSize); // Use sliceSize for width and height to create square slices
//            auto piece = std::make_shared<Piece>(id++);
            Piece * piece = new Piece(id++);
            piece->setPixmap(slice);
            m_pieces.append(piece);
        }
    }

    int row = 0;
    int col = 0;

    for (auto &piece : m_pieces) {
        m_gridLayout->addWidget(piece, row, col); // Add label to layout with row and column
        col++; // Move to next column
        if (col == 3) {
            col = 0; // Reset column and move to next row
            row++;
        }
    }

//    return slices;
}

//int imageWidth = image.width();
//int imageHeight = image.height();
//int sliceWidth = imageWidth / m_sideSize;
//int sliceHeight = imageHeight / m_sideSize;
//int sliceSize = qMin(sliceWidth, sliceHeight);
//int id = 0;
//for (int i = 0; i < m_sideSize; i++) {
//    for (int j = 0; j < m_sideSize; j++) {
//        int x = j * sliceWidth;
//        int y = i * sliceHeight;
//        QPixmap slice = image.copy(x, y, sliceSize, sliceSize);
//        Piece * piece = new Piece(id++);
//        piece->setPixmap(slice);
//        m_pieces.append(*piece);
//    }
//}

//int row = 0;
//int col = 0;

//for (const Piece &piece : m_pieces) {

//    m_gridLayout->addWidget(piece, row, col); // Add label to layout with row and column
//    col++; // Move to next column
//    if (col == 3) {
//        col = 0; // Reset column and move to next row
//        row++;
//    }
//}
