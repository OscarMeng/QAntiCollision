#ifndef SHAPEWIDGET_H
#define SHAPEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pan.h"
#include "paintarea.h"
#include "axiswidget.h"

class Pan;
class PaintArea;
class AxisWidget;
class ShapeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShapeWidget(PaintArea *pPaintArea, Pan* pPan);
private:
    virtual ~ShapeWidget();
public:
    PaintArea   *m_pPaintArea;
    Pan         *m_pPan;
    QLabel      *m_pCellLabel;
    QLineEdit   *m_pCellIDEdit;
    QPushButton *m_pCenBtn;
    QPushButton *m_pEccBtn;
    AxisWidget  *m_pAxis;
    QTextEdit   *m_pTextEdit;
    QHBoxLayout *m_pCellLayout;
    QGridLayout *m_pMainLayout;
public:
    bool      m_bCenBtn;//默认中心轴数据
public:

signals:
    void    SendValue(QString sID,bool bCenEcc,QString sData);//单元号，中心轴还是偏心轴，数据发送给坐标轴
public slots:
    void    ReceiveCenShape(QString sID,QString sData);
    void    ReceiveEccShape(QString sID,QString sData);
    void    PressCenBtn();
    void    PressEccBtn();
};

#endif // SHAPEWIDGET_H
