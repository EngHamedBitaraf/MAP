#ifndef MYMARBLEWIDGET_H
#define MYMARBLEWIDGET_H

#include <marble/MarbleWidget.h>
using namespace Marble;

class MyMarbleWidget: public MarbleWidget
{
public:
    MyMarbleWidget();
    virtual void customPaint(GeoPainter* painter);
    

};

#endif // MYMARBLEWIDGET_H
