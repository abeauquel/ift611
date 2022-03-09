#ifndef LABELCLIC_H
#define LABELCLIC_H
#include <QtWidgets/QLabel>
class LabelClic : public QLabel
{
 Q_OBJECT
 
public:
 LabelClic(QWidget *parent = 0);
 
protected:
 void mousePressEvent(QMouseEvent *event);
};
#endif

