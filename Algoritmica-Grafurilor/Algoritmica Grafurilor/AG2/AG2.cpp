#include "AG2.h"

AG2::AG2(QWidget* parent)
    : QWidget{ parent }
{

    m_button = new QPushButton("Solve!", this);
	m_layout = new QGridLayout(this);
	m_layout->addWidget(m_button, 0, 0, Qt::AlignRight | Qt::AlignTop);
    this->resize(1000, 1000);

    connect(m_button, &QPushButton::clicked, this, &AG2::pushButton);
}
AG2::~AG2()
{
	delete m_button;
    delete m_layout;
}

void AG2::pushButton()
{
    m_button->setText("Solving...");
    m_graf.BFS();
    m_graf.MakeVectorForNodesPaints();
    paintPathNodes();
    m_button->setText("Solved!");
}
void AG2::paintPathNodes()
{
    for (auto stack : m_graf.GetVectorForNodesToPaint())
        while (!stack.empty())
        {
            if(m_graf.GetMatrix()[stack.top().x()][stack.top().y()]->getValue() != '2')
            m_graf.GetMatrix()[stack.top().x()][stack.top().y()]->setSelected(true);
            stack.pop();
        }
}
void AG2::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setPen(Qt::darkCyan);

    if (m_graf.GetSizeLines() == 0)
    {
        std::ifstream fin("text.txt");
        fin >> m_graf;
        fin.close();
    }
    for (int line = 0; line < m_graf.GetSizeLines(); line++)
    for (int column = 0; column < m_graf.GetSizeColumns(); column++)
        {
            if (m_graf.NodeIsNull(line, column))
            {p.setBrush(Qt::black);}
            else
                if (m_graf.NodeIsForPath(line, column))
                { p.setBrush(Qt::green);}
                else
                    if (m_graf.ValueNode(line, column) == '1')
                    {p.setBrush(Qt::white);}
                    else
                        if (m_graf.ValueNode(line, column) == '2')
                        {p.setBrush(Qt::red);}
                        else
                            if (m_graf.ValueNode(line, column) == '3')
                            {p.setBrush(Qt::blue);}
            int x = column * width() / m_graf.GetSizeColumns();
            int y = 40 + line * (height() - 40) / m_graf.GetSizeLines();
            p.drawRect(x, y, width() / m_graf.GetSizeColumns(), (height() - 40) / m_graf.GetSizeLines());
        }
    update();
}
