#include "shapewidget.h"

ShapeWidget::ShapeWidget(PaintArea *pPaintArea,Pan *pPan) : m_pPaintArea(pPaintArea),m_pPan(pPan)
{
    setPalette(QPalette(Qt:: white));
    setAutoFillBackground(true);
    setMinimumSize(400,300);

    m_bCenBtn=true;

    m_pCellLabel=new QLabel(tr("单元号:"));
    m_pCellIDEdit=new QLineEdit;
    m_pCenBtn=new QPushButton(tr("中心轴"));
    m_pEccBtn=new QPushButton(tr("偏心轴"));
    m_pAxis=new AxisWidget(this);
    m_pTextEdit=new QTextEdit;

    m_pCellLayout=new QHBoxLayout();
    m_pCellLayout->addWidget(m_pCellLabel);
    m_pCellLayout->addWidget(m_pCellIDEdit);
    m_pCellLayout->addWidget(m_pCenBtn);
    m_pCellLayout->addWidget(m_pEccBtn);

    m_pMainLayout=new QGridLayout(this);
    m_pMainLayout->addLayout(m_pCellLayout,0,0);
    m_pMainLayout->addWidget(m_pAxis);
    m_pMainLayout->addWidget(m_pTextEdit);
    m_pMainLayout->setRowStretch(0,1);
    m_pMainLayout->setRowStretch(1,4);
    m_pMainLayout->setRowStretch(2,3);

    connect(m_pCenBtn,SIGNAL(clicked(bool)),this,SLOT(PressCenBtn()));
    connect(m_pEccBtn,SIGNAL(clicked(bool)),this,SLOT(PressEccBtn()));
    connect(m_pPan,SIGNAL(SendCenValue(QString,QString)),
            this,SLOT(ReceiveCenShape(QString,QString)));
    connect(m_pPan,SIGNAL(SendEccValue(QString,QString)),
            this,SLOT(ReceiveEccShape(QString,QString)));
    connect(this,SIGNAL(SendValue(QString,bool,QString)),m_pAxis,SLOT(ReceiveValue(QString,bool,QString)));
    m_pCellIDEdit->setText("1");
}

ShapeWidget::~ShapeWidget()
{
    delete m_pAxis;
}

void ShapeWidget::ReceiveCenShape(QString sID, QString sData)
{
    if(m_bCenBtn)
    {
        m_pCellIDEdit->setText(sID);
        m_pTextEdit->setText(sData);
        emit SendValue(sID,m_bCenBtn,sData);
        m_pAxis->update();
    }
}

void ShapeWidget::ReceiveEccShape( QString sID,QString sData)
{
    if(!m_bCenBtn)
    {
        m_pCellIDEdit->setText(sID);
        m_pTextEdit->setText(sData);
        emit SendValue(sID,m_bCenBtn,sData);
        m_pAxis->update();
    }
}

void ShapeWidget::PressCenBtn()
{
    m_bCenBtn=true;
    QString sID=m_pCellIDEdit->text().trimmed();
    bool b;
    int nID=sID.toInt(&b);
    if(nID>0&&nID<CELL_NUM)
    {
        QString sc="";
        for(int i=1;i<=WAVE_NUM;i++)
        {
            if(m_pPan->CellCenPosValue(nID,i)!=BYTE_NULL)
            {
                sc+=QString::number(m_pPan->CellCenPosValue(nID,i));
            }
        }
        m_pTextEdit->setText(sc);
        emit SendValue(sID,m_bCenBtn,sc);
        m_pAxis->update();
    }
}

void ShapeWidget::PressEccBtn()
{
    m_bCenBtn=false;
    QString sID=m_pCellIDEdit->text().trimmed();
    bool b;
    int nID=sID.toInt(&b);
    if(nID>0&&nID<CELL_NUM)
    {
        QString se="";
        for(int i=1;i<=WAVE_NUM;i++)
        {
            if(m_pPan->CellEccPosValue(nID,i)!=BYTE_NULL)
            {
                se+=QString::number(m_pPan->CellEccPosValue(nID,i));
            }
        }
        m_pTextEdit->setText(se);
        emit SendValue(sID,m_bCenBtn,se);
        m_pAxis->update();
    }
}

