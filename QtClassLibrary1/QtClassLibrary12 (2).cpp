#include "QtClassLibrary1.h"


extern "C" __declspec(dllexport) IsModule * loadModule() 
{
	return (new SomeIS2Module()); 
}
MyModuleForm::MyModuleForm(QWidget *parent) :WorkWidget(parent)
{ 
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(oneStep()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(allSteps()));
	widgetName = QStringLiteral("Реструктуризация");
} 

MyModuleForm::~MyModuleForm()
{
}

std::vector<AFElement *> elements;
std::vector<elementMatrix>vEleMatr;
std::vector<AFElement *> vComplicated;
QStandardItemModel *fullTable = new QStandardItemModel();
QStandardItemModel *restTable = new QStandardItemModel();
QStandardItemModel *fullTableAdd1 = new QStandardItemModel();
QStandardItemModel *S1TableModel = new QStandardItemModel();
QStandardItemModel *S2TableModel = new QStandardItemModel();
QStandardItemModel *STableModel = new QStandardItemModel();
QStandardItemModel *S1HeaderModel = new QStandardItemModel();
QStandardItemModel *S2HeaderModel = new QStandardItemModel();


int currElement;


//устаревшая функция построения структур
/*
//???????? ??????? ??? ??????????? (????????)
QWidget* MyModuleForm::createAltTable(QString e,std::vector<QString> code, int k) const 
{
	QWidget* wgt = new QWidget;
	QBoxLayout* l = new QHBoxLayout;
	QTableView* btn = new QTableView;
	QLabel* lbl = new QLabel(e + " =");
	vEleMatr[k].code = e;
	vEleMatr[k].childMatrix = new QStandardItemModel;
	vEleMatr[k].childMatrix->setColumnCount(code.size() + 1);
	vEleMatr[k].childMatrix->setRowCount(code.size() + 1);	
	for (int i = 0; i < code.size()+1; ++i)
		for (int j = 0; j < code.size()+1; ++j)
		{
			QString io = "1";
			vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), 0, Qt::DisplayRole);
			if (j != code.size())
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(j, 0), io, Qt::DisplayRole);
			
			if (j - 1 == i)
			{
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), code[i], Qt::DisplayRole);
			}
			if(i == code.size() && j!=0)
			vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(code.size(), j), io, Qt::DisplayRole);
		}
	btn->setModel(vEleMatr[k].childMatrix);
	btn->verticalHeader()->hide();
	btn->horizontalHeader()->hide();
	btn->setMinimumHeight(0);
	btn->setMinimumWidth(0);
	btn->resizeColumnsToContents();
	btn->resizeRowsToContents();
	btn->setMaximumWidth(400);
	btn->setEditTriggers(QAbstractItemView::NoEditTriggers);
	btn->setSelectionMode(QAbstractItemView::NoSelection);
	btn->setSelectionBehavior(QAbstractItemView::SelectRows);
	l->setMargin(0);
	l->addSpacing(7);
	l->addWidget(lbl);
	l->addWidget(btn);
	wgt->setMinimumHeight(0);
	wgt->setMinimumWidth(0);
	wgt->setLayout(l);
	wgt->setMaximumHeight(71 + 23 * (code.size() - 2));
	wgt->setMaximumWidth(160 + 39 * (code.size() - 2));
	return wgt;
}

//???????? ??????? ??? ??????????????????? (????????)
QWidget* MyModuleForm::createSeqTable(QString e, std::vector<QString> code, int k) const 
{
	QWidget* wgt = new QWidget;
	QBoxLayout* l = new QHBoxLayout;
	QTableView* btn = new QTableView;
	QLabel* lbl = new QLabel(e + " =");
	vEleMatr[k].code = e;
	vEleMatr[k].childMatrix = new QStandardItemModel;
	vEleMatr[k].childMatrix->setColumnCount(code.size() + 1);
	vEleMatr[k].childMatrix->setRowCount(code.size() + 1);
	for (int i = 0; i < code.size()+1; ++i)
	{
		QString io = "1";
		QString zerocu = "0";	
		for (int j = 0; j < code.size() + 1; ++j)
		{			
			vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), 0, Qt::DisplayRole);
			if (i < code.size()+1)
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, 0), io, Qt::DisplayRole);
			if (j - 1 == i)
			{
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), code[i], Qt::DisplayRole);			
			}
			if (i > 0 && vEleMatr[k].childMatrix->index(i-1, j).data().toString() == code[i-1])
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), io, Qt::DisplayRole);
		}
	}
	btn->setModel(vEleMatr[k].childMatrix);
	btn->verticalHeader()->hide();
	btn->horizontalHeader()->hide();
	btn->setMinimumHeight(0);
	btn->setMinimumWidth(0);
	btn->resizeColumnsToContents();
	btn->resizeRowsToContents();
	btn->setMaximumWidth(400);
	btn->setEditTriggers(QAbstractItemView::NoEditTriggers);
	btn->setSelectionMode(QAbstractItemView::NoSelection);
	btn->setSelectionBehavior(QAbstractItemView::SelectRows);
	l->setMargin(0);
	l->addSpacing(7);
	l->addWidget(lbl);
	l->addWidget(btn);
	wgt->setMinimumHeight(0);
	wgt->setMinimumWidth(0);
	wgt->setLayout(l);
	wgt->setMaximumHeight(71 + 23 * (code.size() - 2));
	wgt->setMaximumWidth(160 + 39 * (code.size() - 2));
	return wgt;
}

//???????? ??????? ??? ????????/?????? (????????)
QWidget* MyModuleForm::createCycTable(QString e, std::vector<QString> code,int k) const
{
	QWidget* wgt = new QWidget;
	QBoxLayout* l = new QHBoxLayout;
	QTableView* btn = new QTableView;
	QLabel* lbl = new QLabel(e + " =");
	vEleMatr[k].code = e;
	vEleMatr[k].childMatrix = new QStandardItemModel;
	vEleMatr[k].childMatrix->setColumnCount(2);
	vEleMatr[k].childMatrix->setRowCount(2);
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
		{
			QString io = "1";
			QString oi = "1";
			QString N = "n";
			if (j != code.size())
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(j, 0), 1, Qt::DisplayRole);
			if (j - 1 == i)
			{
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), code[i], Qt::DisplayRole);
			}
			vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(1, 1), 1, Qt::DisplayRole);
			vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(1, 0), N, Qt::DisplayRole);
		}
	btn->setModel(vEleMatr[k].childMatrix);
	btn->verticalHeader()->hide();
	btn->horizontalHeader()->hide();
	btn->setMinimumHeight(0);
	btn->setMinimumWidth(0);
	btn->resizeColumnsToContents();
	btn->resizeRowsToContents();
	btn->setMaximumWidth(400);
	btn->setEditTriggers(QAbstractItemView::NoEditTriggers);
	btn->setSelectionMode(QAbstractItemView::NoSelection);
	btn->setSelectionBehavior(QAbstractItemView::SelectRows);
	l->setMargin(0);
	l->addSpacing(7);
	l->addWidget(lbl);
	l->addWidget(btn);
	wgt->setMinimumHeight(0);
	wgt->setMinimumWidth(0);
	wgt->setLayout(l);
	wgt->setMaximumHeight(71 + 23 * (code.size() - 2));
	wgt->setMaximumWidth(160 + 39 * (code.size() - 2));
	return wgt;
}
*/

//функция построения структурных описаний каждого сложного элемента
QWidget* MyModuleForm::createTable(AFElement *element, std::vector<QString> code, int k) const
{
	QWidget* wgt = new QWidget;
	QBoxLayout* l = new QHBoxLayout;
	QTableView* btn = new QTableView;
	QLabel* lbl = new QLabel(QString::fromWCharArray(element->getCode().data()) + " =");
	vEleMatr[k].code = QString::fromWCharArray(element->getCode().data());
	vEleMatr[k].childMatrix = new QStandardItemModel;
	vEleMatr[k].childMatrix->clear();
	if (element->getType() == FEType::Iteration)
	{
		vEleMatr[k].childMatrix->setColumnCount(2);
		vEleMatr[k].childMatrix->setRowCount(2);
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
			{
				if (j != code.size())
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(j, 0), 1, Qt::DisplayRole);
				if (j - 1 == i)
				{
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), code[i], Qt::DisplayRole);
				}
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(1, 1), 1, Qt::DisplayRole);
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(1, 0), "n", Qt::DisplayRole);
			}
	}
	if (element->getType() == FEType::Alternate)
	{
		vEleMatr[k].childMatrix->setColumnCount(code.size() + 1);
		vEleMatr[k].childMatrix->setRowCount(code.size() + 1);
		for (int i = 0; i < code.size() + 1; ++i)
			for (int j = 0; j < code.size() + 1; ++j)
			{
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), 0, Qt::DisplayRole);
				if (j != code.size())
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(j, 0), 1, Qt::DisplayRole);

				if (j - 1 == i)
				{
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), code[i], Qt::DisplayRole);
				}
				if (i == code.size() && j != 0)
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(code.size(), j), 1, Qt::DisplayRole);
			}
	}
	if (element->getType() == FEType::Sequanse)
	{
		vEleMatr[k].childMatrix->setColumnCount(code.size() + 1);
		vEleMatr[k].childMatrix->setRowCount(code.size() + 1);
		for (int i = 0; i < code.size() + 1; ++i)
		{
			for (int j = 0; j < code.size() + 1; ++j)
			{
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), 0, Qt::DisplayRole);
				if (i < code.size() + 1)
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, 0), "1", Qt::DisplayRole);
				if (j - 1 == i)
				{
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), code[i], Qt::DisplayRole);
				}
				if (i > 0 && vEleMatr[k].childMatrix->index(i - 1, j).data().toString() == code[i - 1])
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), "1", Qt::DisplayRole);
			}
		}
	}
	btn->setModel(vEleMatr[k].childMatrix);
	btn->verticalHeader()->hide();
	btn->horizontalHeader()->hide();
	btn->setMinimumHeight(0);
	btn->setMinimumWidth(0);
	btn->resizeColumnsToContents();
	btn->resizeRowsToContents();
	btn->setMaximumWidth(400);
	btn->setEditTriggers(QAbstractItemView::NoEditTriggers);
	btn->setSelectionMode(QAbstractItemView::NoSelection);
	btn->setSelectionBehavior(QAbstractItemView::SelectRows);
	l->setMargin(0);
	l->addSpacing(7);
	l->addWidget(lbl);
	l->addWidget(btn);
	wgt->setMinimumHeight(0);
	wgt->setMinimumWidth(0);
	wgt->setLayout(l);
	wgt->setMaximumHeight(71 + 23 * (code.size() - 2));
	wgt->setMaximumWidth(160 + 39 * (code.size() - 2));
	return wgt;
}

//??????? ????????????????
void MyModuleForm::restructFunc(QStandardItemModel *restTable)
{
	int zeroC = 0, zeroRowCount = 0, flag = 0;
	while (flag < 2)
	{
		for (int k = 0; k < vEleMatr.size(); ++k)
		{
			for (int i = 1; i < restTable->rowCount(); ++i)
			{
				for (int j = 1; j < restTable->columnCount(); ++j)
				{
					if (restTable->index(i, j).data(Qt::DisplayRole).toString().startsWith("c") && restTable->index(i, j - 1).data(Qt::DisplayRole).toString() == "0")
					{
						zeroRowCount = 1; //?????? ?????????? ????? ??? ??????? ???? ?? ???? ????????
						for (int zerorow = 1; zerorow < restTable->columnCount(); ++zerorow) //????????? ?????????? ????? ?? ??????, ???? ?????????? ???????? ?? ?? ???? ??????
						{
							if (restTable->index(i, j - 1 - zerorow).data(Qt::DisplayRole).toString() == "0")
							{
								zeroRowCount++;
							}
							else
								break;
						}
						for (int v = 0; v < restTable->rowCount(); ++v)
						{
							if (!(restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString().startsWith("c")))
							{
								if (restTable->index(v, j).data(Qt::DisplayRole).toString().startsWith("c") && restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString() != "1")
								{
									restTable->setData(restTable->index(v, j - zeroRowCount), restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
									restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									continue;
								}
								if (restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString().startsWith("1") /*&& !restTable->index(v, j).data(Qt::DisplayRole).toString().startsWith("c")*/)
								{
									restTable->setData(restTable->index(v, j - zeroRowCount), restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString() + "/" + restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
									restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									continue;
								}
								if ((restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString() == "0") && (restTable->index(v, j).data(Qt::DisplayRole).toString() != "0"))
								{
									restTable->setData(restTable->index(v, j - zeroRowCount), restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString() + "/" + restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
									restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									continue;
								}
								
							}
						}
						if (restTable->index(i, i+1).data(Qt::DisplayRole).toString() == "0")
						restTable->removeColumn(j);
					}				

				}
			}
			for (int i = restTable->columnCount(); i > 0; --i)
			{
				for (int j = restTable->rowCount(); j > 0; --j)
				{
					if (restTable->index(j, i).data(Qt::DisplayRole).toString() == "0")
						zeroC++;
					if (zeroC == restTable->rowCount() - 1)
					{
						restTable->removeColumn(i);
					}

				}
				zeroC = 0;
			}
		}
		flag++;
	}
	ui.tableView_2->resizeColumnsToContents();
	ui.tableView_2->resizeRowsToContents();
}

void MyModuleForm::IS_WidgetActived() //??????? main
{
	currElement = 1;
	ConceptModel *cm = (ConceptModel *)IS::getConceptModel();
	std::vector<ALElementList> elements3;
	std::vector<AFElement *> elements;
	std::vector<AFElement *> vComplicated;
	std::vector<QString> codes;
	std::vector<std::vector<QString>> codesfull;
	ui.pushButton->setEnabled(true);
	ui.pushButton_2->setEnabled(true);
	vEleMatr.clear();	

	//????? ???????????? (????????)
/*	for (int i = 0; i < cm->getDynamicStructure(0)->getElementsCount(); ++i)

	{

		if (cm->getDynamicStructure(0)->getAFElement(i)->getType() == FEType::None)
			elements.push_back(cm->getDynamicStructure(0)->getAFElement(i));

	} */

//????? ? tableWidget (????????)
	/*	for (int k = 0; k < vComplicated.size(); ++k)
	{
	QString code = QString::fromWCharArray(vComplicated[k]->getCode().data());
	w = createAltTable(code, codesfull[k])->width();
	wsum += w;
	if (wsum < ui.m_3->width())
	{
	if (p == 0)
	ui.m_3->insertColumn(l);
	ui.m_3->setCellWidget(p, l, createAltTable(code, codesfull[k]));
	h = createAltTable(code, codesfull[k])->height();
	ui.m_3->resizeColumnsToContents();
	if (h >= maxh)
	maxh = h;
	//ui.m_3->model()->index(0, k)
	ui.m_3->setRowHeight(p, maxh + 1);
	l++;
	}
	else
	{
	maxh = 0;
	l = 0;
	wsum = w;
	p++;
	ui.m_3->insertRow(p);
	ui.m_3->setCellWidget(p, l, createAltTable(code, codesfull[k]));
	h = createAltTable(code, codesfull[k])->height();
	ui.m_3->resizeColumnsToContents();
	if (h >= maxh)
	maxh = h;
	//ui.m_3->model()->index(0, k)
	ui.m_3->setRowHeight(p, maxh + 1);
	l++;

	}
	}*/

	//??????? ?????? ?? ?? ???????????? ????????
	for (int i = 0; i < cm->getDynamicStructure(0)->getElementsCount(); ++i)
	{
		elementMatrix buffElem;
		if (cm->getDynamicStructure(0)->getAFElement(i)->getType() != FEType::None)
		{   
			vComplicated.push_back(cm->getDynamicStructure(0)->getAFElement(i));
			vEleMatr.push_back(buffElem);
		}
	}


	//???????? ?????? ?????
	for (int i = 0; i < vComplicated.size(); ++i)
	{
		elements3.push_back(vComplicated[i]->getChildren()); //??????? "????" ???? ?????????????? ? ???????????? ? ??????
		for (int j = 0; j < elements3[i].count(); ++j)
		{
			codes.push_back(QString::fromWCharArray(elements3[i].element<AFElement *>(j)->getCode().data())); //??? ??????? "???????" ???????????? ? ?????? ???????????????? ????
		}
		codesfull.push_back(codes); //?????? ????? ???? ????? ???? ??????????????
		codes.clear(); //??????? ??????? ????? ?????? ???????????????
	}

	//?????? ??????????? ??????????
	int w, h, maxw = 0, maxh = 0, wsum = 0, p = 0, l = 0, zeroC = 0, flag = 0, ccount = 0, tableS2Size = 0, tableSSize = 0, S2Span = 0, SSpan = 0;
	
	std::vector<int> maxwidth; //?????????????? ?????? 3 ?????????? (???????? ?? ?????? ???????)
	for (int i = 0; i < 3; ++i)
		maxwidth.push_back(0);

	//???????? ??????? ?????
	for (int i = 0; i < ui.gridLayout_4->count(); ++i)
	{
		QLayoutItem* item = ui.gridLayout_4->itemAt(i);
		if (item)
		{
			ui.gridLayout_4->removeItem(item);
			QWidget* widget = item->widget();
			if (widget)
			{
				ui.gridLayout_4->removeWidget(widget);
				delete widget;
			}
			delete item;
			--i;
		}
	}

	//????? ? grid
	for (int k = 0; k < vComplicated.size(); ++k)
	{
		ui.gridLayout_4->addWidget(createTable(vComplicated[k], codesfull[k], k), p, l, 1, 1);		
		if (maxwidth[l] < createTable(vComplicated[k], codesfull[k], k)->width())
		{ 		
				ui.gridLayout_4->setColumnMinimumWidth(l, createTable(vComplicated[k], codesfull[k], k)->width());
				maxwidth[l] = createTable(vComplicated[k], codesfull[k], k)->width();
		}
		l++;
		if (l == 3)
		{
			p++;
			l = 0;
		}
	}

	//????????????? ????? ???????
	if (vComplicated.size() > 0)
	{
		fullTable->clear();
		fullTable->setColumnCount(vEleMatr[0].childMatrix->columnCount());
		fullTable->setRowCount(vEleMatr[0].childMatrix->rowCount());
		for (int i = 0; i < vEleMatr[0].childMatrix->rowCount(); ++i)
			for (int j = 0; j < vEleMatr[0].childMatrix->columnCount(); ++j)
			{
				fullTable->setData(fullTable->index(i, j), vEleMatr[0].childMatrix->index(i, j).data(Qt::DisplayRole).toString());
			}
		ui.tableView->setModel(fullTable);
		ui.tableView->resizeColumnsToContents();
		ui.tableView->resizeRowsToContents();
	}
	
	
	//????????????? ??????????? ???????
	if (vComplicated.size() > 0)
	{
		fullTableAdd1->clear();
		fullTableAdd1->setColumnCount(fullTable->columnCount());
		fullTableAdd1->setRowCount(fullTable->rowCount());
		for (int i = 0; i < fullTableAdd1->rowCount(); ++i)
			for (int j = 0; j < fullTableAdd1->columnCount(); ++j)
			{
				fullTableAdd1->setData(fullTableAdd1->index(i, j), fullTable->index(i, j).data(Qt::DisplayRole).toString());
			}

		for (int i = 0; i < fullTableAdd1->rowCount() - 1; ++i)
			for (int j = 1; j < fullTableAdd1->columnCount(); ++j)
			{
				if (fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString() == "1")
					fullTableAdd1->setData(fullTableAdd1->index(j - 1, i + 1), fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString());
			}
		ui.tableView_3->setModel(fullTableAdd1);
		ui.tableView_3->resizeColumnsToContents();
		ui.tableView_3->resizeRowsToContents();

	}
	
//????????????? ??????? ????????????????
	if (vComplicated.size() > 0)
	{
		restTable->clear();
		restTable->setColumnCount(fullTable->columnCount());
		restTable->setRowCount(fullTable->rowCount());

		for (int i = 0; i < fullTable->rowCount(); ++i)
			for (int j = 0; j < fullTable->columnCount(); ++j)
		{
			restTable->setData(restTable->index(i,j),fullTable->index(i,j).data(Qt::DisplayRole).toString());			
		}
		ui.tableView_2->setModel(restTable);
	}

//???????????????? ??? ??????? (????????)
	/*if (vComplicated.size() > 1)
	{
		for (int k = 0; k < vComplicated.size(); ++k)
		{   if (flag != 2)
			for (int i = restTable->rowCount(); i > 1; --i)
			{
				for (int j = restTable->columnCount(); j > 1; --j)
				{
					if (restTable->index(i, j).data(Qt::DisplayRole).toString().startsWith("c"))
						if (restTable->index(i, j - 1).data(Qt::DisplayRole).toString() == "0")
						{
							flag = 1;
							for (int v = 0; v < restTable->rowCount(); ++v)
							{
								if (!(restTable->index(v, j - 1).data(Qt::DisplayRole).toString().startsWith("c")))
								{
									if (restTable->index(v, j).data(Qt::DisplayRole).toString().startsWith("c") && restTable->index(v, j - 1).data(Qt::DisplayRole).toString() == "0")
									{
										restTable->setData(restTable->index(v, j - 1), restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
										restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									}
									if (restTable->index(v, j - 1).data(Qt::DisplayRole).toString() == "1" && !restTable->index(v, j).data(Qt::DisplayRole).toString().startsWith("c"))
									{
										restTable->setData(restTable->index(v, j - 1), restTable->index(v, j - 1).data(Qt::DisplayRole).toString() + "/" + restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
										restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									}
									if (restTable->index(v, j - 1).data(Qt::DisplayRole).toString() == "0" && restTable->index(v, j).data(Qt::DisplayRole).toString() != "0")
									{
									restTable->setData(restTable->index(v, j - 1), restTable->index(v, j - 1).data(Qt::DisplayRole).toString() + "/" + restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
									restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									}
								}
							}
						}
						else
						{
							ccount++;
						}
					if (ccount == restTable->rowCount() - 1)
						flag = 2;
				}				
		}
			for (int i = restTable->columnCount(); i > 0; --i)
			{
				for (int j = restTable->rowCount(); j > 0; --j)
				{
					if (restTable->index(j, i).data(Qt::DisplayRole).toString() == "0")
						zeroC++;
					if (zeroC == restTable->rowCount()-1)
					{
						restTable->removeColumn(i);
					}
					
				}
				zeroC = 0;
			}
		}
		ui.tableView_2->resizeColumnsToContents();
		ui.tableView_2->resizeRowsToContents();
	}
*/
	
	createSpecTables(); //???????? ??????? ??????
	

//???????? ? ?????????? ??????? S1
	if (vComplicated.size() > 0)
	{
		ui.S1Table->setVisible(true);
		sort(vComplicated.begin(), vComplicated.end(), AFElement::AFEcodeOrder);
		std::vector<int> sameNumberCount;
		S1TableModel->setRowCount(vComplicated.size());
		S1TableModel->setColumnCount(3);
		ui.S1Table->setModel(S1TableModel);

		for (int i = 0; i < vComplicated.size(); ++i)
		{
			S1TableModel->setData(S1TableModel->index(i, 0), vComplicated[i]->getLevel(), Qt::DisplayRole);
			S1TableModel->setData(S1TableModel->index(i, 1), vComplicated[i]->getNumber(), Qt::DisplayRole);
		}

		S1TableModel->setData(S1TableModel->index(0, 2), vComplicated.size(), Qt::DisplayRole);
		
		//???????? ?????????? ??????
		for (int i = 1; i < vComplicated.size(); ++i)
		{
			if (S1TableModel->index(i, 0).data(Qt::DisplayRole).toString() == S1TableModel->index(i + 1, 0).data(Qt::DisplayRole).toString())
			{
			sameNumberCount.push_back(0);
			}
			else
			{
				if (S1TableModel->item(i + 1, 0) == 0)
				{
					for (int j = 0; j < sameNumberCount.size() + 1; j++)
					{
						S1TableModel->setData(S1TableModel->index(i - j, 2), vComplicated.size() - i - j + sameNumberCount.size()+1, Qt::DisplayRole);
					}
					sameNumberCount.clear();
				}
				else
				{
					for (int j = 0; j < sameNumberCount.size() + 1; j++)
					{
						S1TableModel->setData(S1TableModel->index(i - j, 2), vComplicated.size() - i - j + sameNumberCount.size(), Qt::DisplayRole);
					}
					sameNumberCount.clear();
				}
			}
		
		}
		S1TableModel->setData(S1TableModel->index(vComplicated.size() - 1, 2), 1, Qt::DisplayRole);

		ui.S1Table->verticalHeader()->hide();
		ui.S1Table->horizontalHeader()->hide();
		ui.S1Table->setMinimumHeight(0);
		ui.S1Table->setMinimumWidth(0);
		ui.S1Table->resizeRowsToContents();		
		ui.S1Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.S1Table->setSelectionMode(QAbstractItemView::NoSelection);
		ui.S1Table->setSelectionBehavior(QAbstractItemView::SelectRows);
		ui.S1Table->setColumnWidth(0, 137);
		ui.S1Table->setColumnWidth(1, 55);
		ui.S1Table->setColumnWidth(2, 39);
		ui.S1Table->setFixedWidth(233);

	}

	//???????? ? ?????????? S2
	if (vComplicated.size() > 0)
	{
		ui.S2Table->setVisible(true);
		//?????? ???-?? ????? ? ??????? S2
		for (int i = 0; i < vComplicated.size(); ++i)
		{
			tableS2Size = tableS2Size + vComplicated[i]->childsCount();
		}
		//???????? ? ?????????? ??????? S2
		S2TableModel->setRowCount(tableS2Size);
		S2TableModel->setColumnCount(4);
		ui.S2Table->setModel(S2TableModel);
		for (int i = 0; i < codesfull.size(); ++i)
		{
			S2TableModel->setData(S2TableModel->index(i + S2Span, 0), vComplicated[i]->getLevel(), Qt::DisplayRole);
			S2TableModel->setData(S2TableModel->index(i + S2Span, 1), vComplicated[i]->getNumber(), Qt::DisplayRole);
			for (int j = 0; j < vComplicated[i]->childsCount(); ++j)
			{
				S2TableModel->setData(S2TableModel->index(i + j + S2Span, 2), elements3[i].element<AFElement *>(j)->getLevel(), Qt::DisplayRole);
				S2TableModel->setData(S2TableModel->index(i + j + S2Span, 3), elements3[i].element<AFElement *>(j)->getNumber(), Qt::DisplayRole);
			}
			ui.S2Table->setSpan(i + S2Span, 0, vComplicated[i]->childsCount(), 1);
			ui.S2Table->setSpan(i + S2Span, 1, vComplicated[i]->childsCount(), 1);
			S2Span = S2Span + vComplicated[i]->childsCount() - 1;

		}

		int spanOffset = 0;
		for (int i = 0; i < S2TableModel->rowCount(); ++i)
		{
			if ((S2TableModel->index(i, 0).data() == S2TableModel->index(i + 1, 0).data()) && (S2TableModel->index(i, 1).data() == S2TableModel->index(i + 1, 1).data()))
			{


				ui.S2Table->setSpan(i, 1, spanOffset + 1, 1);
				spanOffset++;
			}
			else
				spanOffset = 0;

		}
		ui.S2Table->verticalHeader()->hide();
		ui.S2Table->horizontalHeader()->hide();
		ui.S2Table->setMinimumHeight(0);
		ui.S2Table->setMinimumWidth(0);
		ui.S2Table->resizeColumnsToContents();
		ui.S2Table->resizeRowsToContents();
		ui.S2Table->setMaximumWidth(400);
		ui.S2Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.S2Table->setSelectionMode(QAbstractItemView::NoSelection);
		ui.S2Table->setSelectionBehavior(QAbstractItemView::SelectRows);
		ui.S2Table->setColumnWidth(0, 137);
		ui.S2Table->setColumnWidth(1, 55);
		ui.S2Table->setColumnWidth(2, 79);
		ui.S2Table->setColumnWidth(3, 55);
		ui.S2Table->setFixedWidth(328);
	}

	//?????????? S
	if (vComplicated.size() > 0)
	{
		ui.STable->setVisible(true);
		//?????? ???-?? ????? ? ??????? S2
		for (int i = 0; i < vComplicated.size(); ++i)
		{
			tableSSize = tableSSize + vComplicated[i]->childsCount();
		}
		//???????? ? ?????????? ??????? S2
		STableModel->setRowCount(tableSSize);
		STableModel->setColumnCount(7);
		ui.STable->setModel(STableModel);
		for (int i = 0; i < codesfull.size(); ++i)
		{
			STableModel->setData(STableModel->index(i + SSpan, 0), vComplicated[i]->getLevel(), Qt::DisplayRole);
			STableModel->setData(STableModel->index(i + SSpan, 1), vComplicated[i]->getNumber(), Qt::DisplayRole);
			for (int j = 0; j < vComplicated[i]->childsCount(); ++j)
			{
				STableModel->setData(STableModel->index(i + j + SSpan, 2), elements3[i].element<AFElement *>(j)->getLevel(), Qt::DisplayRole);
				STableModel->setData(STableModel->index(i + j + SSpan, 3), elements3[i].element<AFElement *>(j)->getNumber(), Qt::DisplayRole);
			}
			ui.STable->setSpan(i + SSpan, 0, vComplicated[i]->childsCount(), 1);
			ui.STable->setSpan(i + SSpan, 1, vComplicated[i]->childsCount(), 1);
			SSpan = SSpan + vComplicated[i]->childsCount() - 1;

		}

		int spanOffset = 0;
		for (int i = 0; i < STableModel->rowCount(); ++i)
		{
			if ((STableModel->index(i, 0).data() == STableModel->index(i + 1, 0).data()) && (STableModel->index(i, 1).data() == S2TableModel->index(i + 1, 1).data()))
			{


				ui.STable->setSpan(i, 1, spanOffset + 1, 1);
				spanOffset++;
			}
			else
				spanOffset = 0;

		}
		ui.STable->verticalHeader()->hide();
		ui.STable->horizontalHeader()->hide();
		ui.STable->setMinimumHeight(0);
		ui.STable->setMinimumWidth(0);
		ui.STable->resizeColumnsToContents();
		ui.STable->resizeRowsToContents();
		//ui.STable->setMaximumWidth(400);
		ui.STable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.STable->setSelectionMode(QAbstractItemView::NoSelection);
		ui.STable->setSelectionBehavior(QAbstractItemView::SelectRows);
		ui.STable->setColumnWidth(0, 137);
		ui.STable->setColumnWidth(1, 55);
		ui.STable->setColumnWidth(2, 79);
		ui.STable->setColumnWidth(3, 55);
	//	ui.STable->setFixedWidth(328);
	}

//???????? ?????????, ? ??????? ??? ?????? ?? ???????
	QStandardItemModel *m_cb;
	m_cb = new QStandardItemModel(this);
	m_cb->setColumnCount(1);
	ui.comboBox->setModel(m_cb);

	sort(elements.begin(), elements.end(), AFElement::AFEcompOrder);


	int a = -1;
	for (auto it = vComplicated.begin(); it != vComplicated.end(); ++it)
	{
		AFElement *el = *it;
		QString code = QString::fromWCharArray(el->getCode().data());
		a++;
		m_cb->setData(m_cb->index(a, 0), code, Qt::DisplayRole);
		m_cb->setData(m_cb->index(a, 0), (uint)el, Qt::UserRole + 1);
	}
}

	void MyModuleForm::on_comboBox_currentIndexChanged(int index)
	{

		ui.plainTextEdit->clear();
		uint data = ui.comboBox->currentData(Qt::UserRole + 1).toUInt();
		if (!data)
			return;

		QString text;
		AFElement *el = reinterpret_cast<AFElement*>(data);
		text += QString::fromWCharArray(el->getCode().data()) + '\n';

		ALElementList args = el->getContentArgs('+');

		for (auto it = elements.begin(); it != elements.end(); ++it)
		{
			AFElement *e = *it;
			if (e != el)
			{
				AIElement *f = e->getFunction();
				for (int i = 0; i < args.count(); i++)
				{
					if (f == args.element<AIElement*>(i))
					{
						text += QString::fromWCharArray(e->getCode().data()) + ", ";
						break;
					}
				}
			}

		}

		ui.plainTextEdit->insertPlainText(text);
	}

	//???????, ??????????? ????? ??????????? ???????? ????? ??????? (1 ???)
	void MyModuleForm::oneStep()
	{
		if ((vEleMatr.size() > 1) && (currElement < vEleMatr.size()))
		{
				for (int i = 0; i < fullTable->rowCount(); ++i)
					for (int j = 0; j < fullTable->columnCount(); ++j)
					{
						if (vEleMatr[currElement].code == fullTable->index(i, j).data(Qt::DisplayRole).toString())
						{
							int itemI = i;
							int itemJ = j;
							fullTable->insertRows(itemI+1, vEleMatr[currElement].childMatrix->rowCount() - 2);
							fullTable->insertColumns(itemJ+1, vEleMatr[currElement].childMatrix->columnCount() - 2);
							for (int r = 0; r < vEleMatr[currElement].childMatrix->rowCount(); ++r)
								for (int c = 0; c < vEleMatr[currElement].childMatrix->columnCount(); ++c)
									fullTable->setData(fullTable->index(itemI + r, itemJ + c - 1), vEleMatr[currElement].childMatrix->index(r, c).data(), Qt::DisplayRole);
							i += vEleMatr[currElement].childMatrix->rowCount() - 2;
							j += vEleMatr[currElement].childMatrix->columnCount() - 2;
						}
					}
				for (int i = 0; i < fullTable->rowCount(); ++i)
					for (int j = 0; j < fullTable->columnCount(); ++j)
						if (fullTable->item(i, j) == 0)
							fullTable->setData(fullTable->index(i, j), "0", Qt::DisplayRole);
				currElement++;
			ui.tableView->resizeColumnsToContents();
			ui.tableView->resizeRowsToContents();
		}
		if (currElement == vEleMatr.size())
		{
			ui.pushButton->setEnabled(false);
			ui.pushButton_2->setEnabled(false);
			fullTableAdd1->clear();
			fullTableAdd1->setColumnCount(fullTable->columnCount());
			fullTableAdd1->setRowCount(fullTable->rowCount());
			for (int i = 0; i < fullTableAdd1->rowCount(); ++i)
				for (int j = 0; j < fullTableAdd1->columnCount(); ++j)
				{
					fullTableAdd1->setData(fullTableAdd1->index(i, j), fullTable->index(i, j).data(Qt::DisplayRole).toString());
				}

			for (int i = 0; i < fullTableAdd1->rowCount()-1; ++i)
				for (int j = 1; j < fullTableAdd1->columnCount(); ++j)
				{
					if(fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString()=="1")
					fullTableAdd1->setData(fullTableAdd1->index(j-1, i+1), fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString());
				}
			ui.tableView_3->resizeColumnsToContents();
			ui.tableView_3->resizeRowsToContents();
			restTable->clear();
			restTable->setColumnCount(fullTable->columnCount());
			restTable->setRowCount(fullTable->rowCount());
			for (int i = 0; i < fullTable->rowCount(); ++i)
				for (int j = 0; j < fullTable->columnCount(); ++j)
				{
					restTable->setData(restTable->index(i, j), fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString());
				}

			ui.tableView_2->setModel(restTable);
			restructFunc(restTable);

		}
	}

	//???????, ??????????? ????? ??????????? ???????? ????? ???????? (??? ????)
	void MyModuleForm::allSteps()
	{
		if ((vEleMatr.size()) > 1 && (currElement < vEleMatr.size()))
		{
			for (currElement; currElement < vEleMatr.size(); ++currElement)
			{
				for (int i = 0; i < fullTable->rowCount(); ++i)
					for (int j = 0; j < fullTable->columnCount(); ++j)
					{
						if (vEleMatr[currElement].code == fullTable->index(i, j).data(Qt::DisplayRole).toString())
						{
							int itemI = i;
							int itemJ = j;
							fullTable->insertRows(itemI+1, vEleMatr[currElement].childMatrix->rowCount() - 2);
							fullTable->insertColumns(itemJ+1, vEleMatr[currElement].childMatrix->columnCount() - 2);
							for (int r = 0; r < vEleMatr[currElement].childMatrix->rowCount(); ++r)
								for (int c = 0; c < vEleMatr[currElement].childMatrix->columnCount(); ++c)
									fullTable->setData(fullTable->index(itemI + r, itemJ + c - 1), vEleMatr[currElement].childMatrix->index(r, c).data(), Qt::DisplayRole);
							i += vEleMatr[currElement].childMatrix->rowCount() - 2;
							j += vEleMatr[currElement].childMatrix->columnCount() - 2;
						}
					}
				for (int i = 0; i < fullTable->rowCount(); ++i)
					for (int j = 0; j < fullTable->columnCount(); ++j)
						if (fullTable->item(i, j) == 0)
							fullTable->setData(fullTable->index(i, j), "0", Qt::DisplayRole);
			}
			ui.tableView->resizeColumnsToContents();
			ui.tableView->resizeRowsToContents();
			ui.pushButton->setEnabled(false);
			ui.pushButton_2->setEnabled(false);

			fullTableAdd1->clear();
			fullTableAdd1->setColumnCount(fullTable->columnCount());
			fullTableAdd1->setRowCount(fullTable->rowCount());

			for (int i = 0; i < fullTableAdd1->rowCount(); ++i)
				for (int j = 0; j < fullTableAdd1->columnCount(); ++j)
				{
					fullTableAdd1->setData(fullTableAdd1->index(i, j), fullTable->index(i, j).data(Qt::DisplayRole).toString());
				}

			for (int i = 0; i < fullTableAdd1->rowCount() - 1; ++i)
				for (int j = 1; j < fullTableAdd1->columnCount(); ++j)
				{
					if (fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString() == "1")
					fullTableAdd1->setData(fullTableAdd1->index(j-1, i+1), fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString());
				}
			ui.tableView_3->resizeColumnsToContents();
			ui.tableView_3->resizeRowsToContents();
			restTable->clear();
			restTable->setColumnCount(fullTable->columnCount());
			restTable->setRowCount(fullTable->rowCount());

			for (int i = 0; i < fullTable->rowCount(); ++i)
				for (int j = 0; j < fullTable->columnCount(); ++j)
				{
					restTable->setData(restTable->index(i, j), fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString());
				}
			ui.tableView_2->setModel(restTable);
			restructFunc(restTable);

		}
	}

	//???????? ?????? ??? ???????????? ????????? ???????
	void MyModuleForm::createSpecTables()
	{
		ui.S1Table->setVisible(false);
		ui.S2Table->setVisible(false);
		ui.STable->setVisible(false);
		S1HeaderModel->setColumnCount(3);
		S1HeaderModel->setRowCount(2);
		S1HeaderModel->setData(S1HeaderModel->index(0, 0), QString::fromLocal8Bit("??? ???????? ????????"), Qt::DisplayRole);
		S1HeaderModel->setData(S1HeaderModel->index(0, 2), QString::fromLocal8Bit("????"), Qt::DisplayRole);
		S1HeaderModel->setData(S1HeaderModel->index(1, 0), QString::fromLocal8Bit("???????"), Qt::DisplayRole);
		S1HeaderModel->setData(S1HeaderModel->index(1, 1), QString::fromLocal8Bit("???????"), Qt::DisplayRole);

		S2HeaderModel->setColumnCount(4);
		S2HeaderModel->setRowCount(2);
		S2HeaderModel->setData(S2HeaderModel->index(0, 0), QString::fromLocal8Bit("??? ???????? ????????"), Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(0, 2), QString::fromLocal8Bit("??? ????????"), Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 0), QString::fromLocal8Bit("???????"), Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 1), QString::fromLocal8Bit("???????"), Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 2), QString::fromLocal8Bit("???????"), Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 3), QString::fromLocal8Bit("???????"), Qt::DisplayRole);

		ui.S2Header->setModel(S2HeaderModel);
		ui.S2Header->verticalHeader()->hide();
		ui.S2Header->horizontalHeader()->hide();
		ui.S2Header->setSpan(0, 0, 1, 2);
		ui.S2Header->setSpan(0, 2, 1, 2);
		ui.S2Header->resizeColumnsToContents();
		ui.S2Header->resizeRowsToContents();
		ui.S2Header->setFixedWidth(328);
		ui.S2Header->setFixedHeight(48);


		ui.S1Header->setModel(S1HeaderModel);
		ui.S1Header->verticalHeader()->hide();
		ui.S1Header->horizontalHeader()->hide();
		ui.S1Header->setFixedWidth(233);
		ui.S1Header->setFixedHeight(48);

		ui.S1Header->setSpan(0, 0, 1, 2);
		ui.S1Header->setSpan(0, 2, 2, 1);
		ui.S1Header->resizeColumnsToContents();
		ui.S1Header->resizeRowsToContents();
		ui.S1Header->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.S1Header->setSelectionMode(QAbstractItemView::NoSelection);
		ui.S1Header->setSelectionBehavior(QAbstractItemView::SelectRows);
	}