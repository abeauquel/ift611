#include <QtWidgets>
#include "labelclic.h"
LabelClic::LabelClic(QWidget *parent) : QLabel(parent)
{
 this->setText("Fenêtre Qt");
}
void LabelClic::mousePressEvent(QMouseEvent *event)
{
 if (event->button() == Qt::LeftButton)
 {
 QMessageBox::information(this, "Bouton gauche enfoncé",
 "Hello World!", QMessageBox::Ok);
 }
}

