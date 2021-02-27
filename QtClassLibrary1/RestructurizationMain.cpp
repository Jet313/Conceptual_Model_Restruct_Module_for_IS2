#include "RestructurizationClasses.h"
#include <QTextCodec>
#include <clocale>
#include <unordered_map>
#include <qprogressdialog.h>
#include <QMessageBox>
#include <QSizePolicy>

extern "C" __declspec(dllexport) IsModule * loadModule() 
{
	return (new SomeIS2Module()); 
}

MyModuleForm::MyModuleForm(QWidget *parent) :WorkWidget(parent)
{ 
	ui.setupUi(this);
	QTextCodec* codec = QTextCodec::codecForName("cp1251");
	QTextCodec::codecForUtfText("cp1251");
	QTextCodec::setCodecForLocale(codec);
	setlocale(0, "");
	connect(ui.oneIterButt, SIGNAL(clicked()), this, SLOT(oneStep()));
	connect(ui.allIterButt, SIGNAL(clicked()), this, SLOT(allSteps()));
	connect(ui.createTablesButt, SIGNAL(clicked()), this, SLOT(createItemTables()));
	connect(ui.deleteTablesButt, SIGNAL(clicked()), this, SLOT(deleteCreatedTables()));

	QString restr = "Реструктуризация";
	widgetName = restr;	
} 

MyModuleForm::~MyModuleForm()
{
}

/*глобальные модели*/
	//std::vector<AFElement *> elements;

QStandardItemModel* fullTable = new QStandardItemModel();
QStandardItemModel* restTable = new QStandardItemModel();
QStandardItemModel* fullTableAdd1 = new QStandardItemModel();
QStandardItemModel* S1TableModel = new QStandardItemModel();
QStandardItemModel* S2TableModel = new QStandardItemModel();
QStandardItemModel* STableModel = new QStandardItemModel();
QStandardItemModel* SHeaderModel = new QStandardItemModel();
QStandardItemModel* S1HeaderModel = new QStandardItemModel();
QStandardItemModel* S2HeaderModel = new QStandardItemModel();
auto ElementsVector = std::vector<SubjectRelation*>();
std::vector<ALElementList> elementsIterations;
std::vector<std::vector<QString>> codesfull;
std::vector<iterationColoring>  iterationsVector;
std::vector<elementMatrix>vEleMatr;
std::vector<AFElement*> vComplicated;
std::vector<hLayout> tableLayouts;
std::vector<elementRelations> systemRelations;
int currElement;
QString openedProject = "";
bool firstTimeInitialized;

//местный MAIN
void MyModuleForm::IS_WidgetActived() {

	std::vector<ALElementList> elements3;
	std::vector<QString> codes;
	std::vector<QString> functions;
	
	//std::vector<AFElement *> elements;
	//std::vector<AFElement *> vComplicated;
	//ui.pushButton->setEnabled(false);
	//ui.pushButton_2->setEnabled(false);
	//ui.tableView->setVisible(false);
	//ui.tableView_3->setVisible(false);
	//ui.expandedTableTab->setEnabled(false);
	//ui.optimizedTableTab->setEnabled(false);
	//ui.fullTableTab->setEnabled(false);
	//ui.fullTableTab->setVisible(false);
	//ui.specTab->setTabEnabled(1, false);
	//ui.specTab->setTabEnabled(2, false);
	//ui.specTab->setTabEnabled(3, false);
	//ui.expandedLable->setVisible(false);
	//ui.iterationLable->setVisible(false);
	//ui.comboBox->setVisible(false);
	//ui.plainTextEdit->setVisible(false);
	//ui.optiTableView->setVisible(false);
	//ui.restLable->setVisible(false);
	//ui.tabWidget->setTabEnabled(2, false);
	//ui.tabWidget->setTabEnabled(3, false);	

	auto IS_type = IS::getModelType();
	AFStructure* DynamicModel = NULL;

	switch (IS_type)
	{
	case (IS_Model_Type::IS_CM):
	{
		ConceptModel* modelToRestructC = (ConceptModel*)IS::getConceptModel();
		DynamicModel = modelToRestructC->getDynamicStructure(0);
		ui.notificationLabel->setText("Концептуальная модель");
		break;
	}
	case (IS_Model_Type::IS_ILM):
	{
		InfologyModel* modelToRestructI = (InfologyModel*)IS::getInfologyModel();
		DynamicModel = modelToRestructI->getDynamicStructure(0);
		ui.notificationLabel->setText("Инфологическая модель");
		break;
	}
	case (IS_Model_Type::IS_PM):
	{
		PrimaryModel* modelToRestructP = (PrimaryModel*)IS::getPrimaryModel();
		DynamicModel = modelToRestructP->getDynamicStructure(0);
		ui.notificationLabel->setText("Начальная модель");
		break;
	}
	case (IS_Model_Type::IS_Comon):
		ui.notificationLabel->setText("Какая модель??");
		break;
	}
	ui.notificationLabel->setVisible(true);


	if (IS::currentProject()->projectName != openedProject)
	{
		iterationsVector.clear();
		vEleMatr.clear();
		ElementsVector.clear();
		systemRelations.clear();
		vComplicated.clear();
		codesfull.clear();
		elements3.clear();
		elementsIterations.clear();
	//	ui.textBrowser->clear();

		ui.expandedTableTab->setEnabled(false);
		ui.optimizedTableTab->setEnabled(false);
		ui.fullTableTab->setEnabled(false);
		deleteCreatedTables();
		tableLayouts.clear();
		ui.specTab->setTabEnabled(1, false);
		ui.specTab->setTabEnabled(2, false);
		ui.specTab->setTabEnabled(3, false);
		firstTimeInitialized = true;
		//ui.notificationLabel->setVisible(false);
	}
	else
	{
		ui.notificationLabel->setVisible(true);
		firstTimeInitialized = false;
	}

	//createTableLayouts();		
	//ConceptModel* modelToRestruct = (ConceptModel*)IS::getInfologyModel();
	//auto ModelStructure = modelToRestruct->getDynamicStructure(0);


	auto ModelStructure = DynamicModel;
	if (firstTimeInitialized)
	{
		for (auto i = 0; i < ModelStructure->getElementsCount(); ++i)
		{
			ElementsVector.push_back((SubjectRelation*)ModelStructure->getAFElement(i));
		}
		std::sort(ElementsVector.begin(), ElementsVector.end(), AFElement::AFEcompOrder);

		//проверка последовательности элементов
		/*std::vector<QString> codesfull2;
		codesfull2.clear();
		for (auto i = 0; i < ElementsVector.size(); ++i)
		{
			codesfull2.push_back(QString::fromWCharArray(ElementsVector[i]->getCode().data()));
		}*/

		//вектор всех неэлементарных действий
		for (int i = 0; i < ModelStructure->getElementsCount(); ++i)
		{
			elementMatrix buffElem;
			if (ModelStructure->getAFElement(i)->getType() != FEType::None)
			{
				vComplicated.push_back(ModelStructure->getAFElement(i));
				vEleMatr.push_back(buffElem);
			}

		}
		std::sort(vComplicated.begin(), vComplicated.end(), AFElement::AFEcodeOrder);

		//создание вектора кодов всех элементов
		for (int i = 0; i < vComplicated.size(); ++i)
		{
			elements3.push_back(vComplicated[i]->getChildren()); //получение всех "детей" всех сложных предметных действий
			for (int j = 0; j < elements3[i].count(); ++j)
			{
				codes.push_back(QString::fromWCharArray(elements3[i].element<AFElement*>(j)->getCode().data())); //запись кодов всех детей в вектор				
			}
			codesfull.push_back(codes); //получается вектор векторов, содержащий код сложного действия и коды всех его детей соответственно
			codes.clear(); //очистна буферного вектора
			if (vComplicated[i]->getType() == FEType::Iteration)
			{
				iterationColoring test;
				test.iterColor = test.colorPicker();
				test.code = QString::fromWCharArray(vComplicated[i]->getCode().data());
				elementsIterations.push_back(vComplicated[i]->getFullChildren());
				iterationsVector.push_back(test);
			}
		}
		//вектор всех детей итераций
		for (int m = 0; m < elementsIterations.size(); ++m)
		{
			for (int l = 1; l < elementsIterations[m].count(); ++l)
			{
				if (elementsIterations[m].element<AFElement*>(l)->getType() == FEType::None)
				{
					iterationsVector[m].children.push_back(QString::fromWCharArray(elementsIterations[m].element<AFElement*>(l)->getCode().data()));
					ui.textBrowser->append(QString::fromWCharArray(elementsIterations[m].element<AFElement*>(l)->getCode().data()));
				}
			}
		}


		//всякие утилитарные переменные, которые неплохо было бы раскидать по функциям
		int tableS2Size = 0, tableSSize = 0, S2Span = 0, SSpan = 0;


		createSpecTables(); //функция создания форм спецификаций

		//заполнение спецификации S1
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
				S1TableModel->setData(S1TableModel->index(i, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
				S1TableModel->setData(S1TableModel->index(i, 1), Qt::AlignCenter, Qt::TextAlignmentRole);
				S1TableModel->setData(S1TableModel->index(i, 0), vComplicated[i]->getLevel(), Qt::DisplayRole);
				S1TableModel->setData(S1TableModel->index(i, 1), vComplicated[i]->getNumber(), Qt::DisplayRole);
			}
			S1TableModel->setData(S1TableModel->index(0, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
			S1TableModel->setData(S1TableModel->index(0, 2), vComplicated.size(), Qt::DisplayRole);

			//расчет ранжирования
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
							S1TableModel->setData(S1TableModel->index(i - j, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
							S1TableModel->setData(S1TableModel->index(i - j, 2), vComplicated.size() - i - j + sameNumberCount.size() + 1, Qt::DisplayRole);
						}
						sameNumberCount.clear();
					}
					else
					{
						for (int j = 0; j < sameNumberCount.size() + 1; j++)
						{
							S1TableModel->setData(S1TableModel->index(i - j, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
							S1TableModel->setData(S1TableModel->index(i - j, 2), vComplicated.size() - i - j + sameNumberCount.size(), Qt::DisplayRole);
						}
						sameNumberCount.clear();
					}
				}

			}
			S1TableModel->setData(S1TableModel->index(vComplicated.size() - 1, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
			S1TableModel->setData(S1TableModel->index(vComplicated.size() - 1, 2), 1, Qt::DisplayRole);

			ui.S1Table->verticalHeader()->hide();
			ui.S1Table->horizontalHeader()->hide();
			ui.S1Table->setMinimumHeight(0);
			ui.S1Table->setMinimumWidth(0);
			ui.S1Table->resizeRowsToContents();
			ui.S1Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
			ui.S1Table->setSelectionMode(QAbstractItemView::NoSelection);
			ui.S1Table->setSelectionBehavior(QAbstractItemView::SelectRows);
			ui.S1Table->setColumnWidth(0, 100);
			ui.S1Table->setColumnWidth(1, 100);
			ui.S1Table->setColumnWidth(2, 100);
			ui.S1Table->setFixedWidth(302);
			ui.S1Table->setFixedHeight(vComplicated.size() * 23);

		}

		//заполнение спецификации S2
		if (vComplicated.size() > 0)
		{
			ui.S2Table->setVisible(true);
			//расчет размера S2
			std::vector<ALElementList> buff;
			buff.clear();
			std::vector<AFElement*> buffChild;
			buffChild.clear();
			for (int i = 0; i < vComplicated.size(); ++i)
			{
				tableS2Size = tableS2Size + vComplicated[i]->childsCount();
				buff.push_back(vComplicated[i]->getChildren());
			}
			//заполнение S2
			S2TableModel->setRowCount(tableS2Size);
			S2TableModel->setColumnCount(4);
			ui.S2Table->setModel(S2TableModel);
			for (int i = 0; i < codesfull.size(); ++i)
			{

				S2TableModel->setData(S2TableModel->index(i + S2Span, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
				S2TableModel->setData(S2TableModel->index(i + S2Span, 1), Qt::AlignCenter, Qt::TextAlignmentRole);
				S2TableModel->setData(S2TableModel->index(i + S2Span, 0), vComplicated[i]->getLevel(), Qt::DisplayRole);
				S2TableModel->setData(S2TableModel->index(i + S2Span, 1), vComplicated[i]->getNumber(), Qt::DisplayRole);

				for (int j = 0; j < buff[i].count(); ++j)
				{
					S2TableModel->setData(S2TableModel->index(i + j + S2Span, 3), Qt::AlignCenter, Qt::TextAlignmentRole);
					S2TableModel->setData(S2TableModel->index(i + j + S2Span, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
					//S2TableModel->setData(S2TableModel->index(i + j + S2Span, 2), elements3[i].element<AFElement *>(j)->getLevel(), Qt::DisplayRole);
					//S2TableModel->setData(S2TableModel->index(i + j + S2Span, 3), elements3[i].element<AFElement *>(j)->getNumber(), Qt::DisplayRole);
					S2TableModel->setData(S2TableModel->index(i + j + S2Span, 2), buff[i].element<AFElement*>(j)->getLevel(), Qt::DisplayRole);
					S2TableModel->setData(S2TableModel->index(i + j + S2Span, 3), buff[i].element<AFElement*>(j)->getNumber(), Qt::DisplayRole);
				}
				ui.S2Table->setSpan(i + S2Span, 0, buff[i].count(), 1);
				ui.S2Table->setSpan(i + S2Span, 1, buff[i].count(), 1);
				S2Span = S2Span + buff[i].count() - 1;

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
			//ui.S2Table->setMaximumWidth(400);
			//ui.S2Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
			//ui.S2Table->setSelectionMode(QAbstractItemView::NoSelection);
			//ui.S2Table->setSelectionBehavior(QAbstractItemView::SelectRows);
			ui.S2Table->setColumnWidth(0, 100);
			ui.S2Table->setColumnWidth(1, 100);
			ui.S2Table->setColumnWidth(2, 100);
			ui.S2Table->setColumnWidth(3, 100);
			ui.S2Table->setFixedWidth(402);
		}

		//спецификация S (hp)
		if (vComplicated.size() > 0)
		{
			ui.STable->setVisible(true);

			STableModel->setRowCount(22);
			STableModel->setColumnCount(6);
			ui.STable->setModel(STableModel);
			/*		for (int i = 0; i < codesfull.size(); ++i)
			{

				STableModel->setData(STableModel->index(i + SSpan, 0), vComplicated[i]->getLevel(), Qt::DisplayRole);
				STableModel->setData(STableModel->index(i + SSpan, 1), vComplicated[i]->getNumber(), Qt::DisplayRole);
		/*		for (int j = 0; j < vComplicated[i]->childsCount(); ++j)
				{
		//			STableModel->setData(STableModel->index(i + j + SSpan, 2), elements3[i].element<AFElement *>(j)->getLevel(), Qt::DisplayRole);
		//			STableModel->setData(STableModel->index(i + j + SSpan, 3), elements3[i].element<AFElement *>(j)->getNumber(), Qt::DisplayRole);
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

			}*/
			for (int i = 0; i < STableModel->rowCount(); ++i)
				for (int j = 0; j < STableModel->columnCount(); ++j)
				{
					STableModel->setData(STableModel->index(i, j), Qt::AlignCenter, Qt::TextAlignmentRole);
				}
			STableModel->setData(STableModel->index(0, 0), "2", Qt::DisplayRole);
			STableModel->setData(STableModel->index(0, 1), "1", Qt::DisplayRole);
			ui.STable->setSpan(0, 0, 8, 1);
			ui.STable->setSpan(0, 1, 8, 1);
			STableModel->setData(STableModel->index(8, 0), "3", Qt::DisplayRole);
			STableModel->setData(STableModel->index(8, 1), "3", Qt::DisplayRole);
			ui.STable->setSpan(8, 0, 8, 1);
			ui.STable->setSpan(8, 1, 8, 1);
			STableModel->setData(STableModel->index(16, 0), "3", Qt::DisplayRole);
			STableModel->setData(STableModel->index(16, 1), "5", Qt::DisplayRole);
			STableModel->setData(STableModel->index(17, 0), "4", Qt::DisplayRole);
			STableModel->setData(STableModel->index(17, 1), "4", Qt::DisplayRole);
			ui.STable->setSpan(17, 0, 2, 1);
			ui.STable->setSpan(17, 1, 2, 1);
			STableModel->setData(STableModel->index(19, 0), "4", Qt::DisplayRole);
			STableModel->setData(STableModel->index(19, 1), "5", Qt::DisplayRole);
			ui.STable->setSpan(19, 0, 3, 1);
			ui.STable->setSpan(19, 1, 3, 1);
			ui.STable->verticalHeader()->hide();
			ui.STable->horizontalHeader()->hide();
			ui.STable->setMinimumHeight(0);
			ui.STable->setMinimumWidth(0);
			ui.STable->resizeColumnsToContents();
			ui.STable->resizeRowsToContents();
			//ui.STable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		//	ui.STable->setSelectionMode(QAbstractItemView::NoSelection);
			//ui.STable->setSelectionBehavior(QAbstractItemView::SelectRows);
			ui.STable->setColumnWidth(0, 100);
			ui.STable->setColumnWidth(1, 100);
			ui.STable->setColumnWidth(2, 100);
			ui.STable->setColumnWidth(3, 100);
			ui.STable->setColumnWidth(4, 100);
			ui.STable->setColumnWidth(5, 100);
			ui.STable->setFixedWidth(602);
		}

		openedProject = IS::currentProject()->projectName;
		firstTimeInitialized = false;
	}

}

//проверка входной инф связности на уровне структурного описания сложного элемента
std::vector<QString> MyModuleForm::InInfromationLinkCheck(QString code) const
{
	//auto ModelStructure = IS::getConceptModel()->getDynamicStructure(0);
	//auto ElementsVector = std::vector<SubjectRelation*>();
	std::vector<QString> ArgumentsVector;
	ArgumentsVector.clear();	

	for (auto SubjectRelationElement : ElementsVector)
	{
		if (SubjectRelationElement->getType() != FEType::None) continue;		
			
			ui.textBrowser->append(QString::fromWCharArray(SubjectRelationElement->getCode().data()) + "-{ \n");
			if (QString::fromWCharArray(SubjectRelationElement->getCode().data()) == code)
			{
				ALElementList args1 = SubjectRelationElement->getContentArgs('+');
				std::vector<AIElement *> pvec;
				ui.textBrowser->append(QString::fromWCharArray(SubjectRelationElement->getCode().data()) + "-{ \n");
				for (int i = 0; i < args1.count(); ++i)
				{
					pvec.push_back(args1.element<AIElement*>(i));

					for (auto it = ElementsVector.begin(); *it != SubjectRelationElement; ++it)
					{
						if ((*it)->getType() != FEType::None)
						{
							continue;
						}

						if ((*it)->getFunction() == args1.element<AIElement*>(i))
						{

							//нашли
							STableModel->setData(STableModel->index(16, 0), "3", Qt::DisplayRole);
							ArgumentsVector.push_back(QString::fromWCharArray((*it)->getCode().data()));
							ui.textBrowser->append(QString::fromWCharArray((*it)->getCode().data()) + " \n");

						}

					}
					
				}
			}
			ui.textBrowser->append("}- \n");
		
	}
	return ArgumentsVector;
}

// проверка аргументов по-умолчанию
bool MyModuleForm::DefaultArgument(QString code) const
{
	//auto ModelStructure = IS::getConceptModel()->getDynamicStructure(0);
	//auto ElementsVector = std::vector<SubjectRelation*>();
	bool DefaultArguments = false;
	std::vector<QString> ArgumentsVector;
	ArgumentsVector.clear();

	/*
	for (auto i = 0; i < ModelStructure->getElementsCount(); ++i)
	{
		ElementsVector.push_back((SubjectRelation*)ModelStructure->getAFElement(i));
	}
	std::sort(ElementsVector.begin(), ElementsVector.end(), AFElement::AFEcompOrder);
	*/

	for (auto SubjectRelationElement : ElementsVector)
	{
		if (SubjectRelationElement->getType() != FEType::None) continue;
		if (QString::fromWCharArray(SubjectRelationElement->getCode().data()) == code)
		{
			ALElementList args2 = SubjectRelationElement->getContentArgs('.');
			if (args2.count() > 0)
			{
				DefaultArguments = true;
			}
			/*for (int i = 0; i < args2.count(); ++i)
			{
				pvec.push_back(args2.element<AIElement*>(i));
			}*/

			ALElementList args3 = SubjectRelationElement->getAutoArgs('.');
			if (args3.count() > 0)
			{
				DefaultArguments = true;
			}
			/*for (int i = 0; i < args3.count(); ++i)
			{
				pvec.push_back(args3.element<AIElement*>(i));
			}*/
		}
	}
	return DefaultArguments;
}

//проверка выходной инф связности на уровне структурного описания сложного элемента
std::vector<QString> MyModuleForm::OutInfromationLinkCheck(QString code) const
{		
	std::vector<QString> ArgumentsVector;
	ArgumentsVector.clear();
	
	
	for (auto SubjectRelationElement : ElementsVector)
	{
		if (SubjectRelationElement->getType() == FEType::None)
			{
			auto ElementFunction = SubjectRelationElement->getFunction();
			if (ElementFunction)
				{
				ui.textBrowser->append(QString::fromWCharArray(SubjectRelationElement->getCode().data()) + "{ \n");
				auto BinaryLinkList = ElementFunction->getBinaryLinksList();
				for (int i = 0; i < BinaryLinkList.count(); ++i)
					{
					if (((AEBinaryLink*)BinaryLinkList.element(i))->getType() == LT_CONTENT)
						{
						auto contentLink = BinaryLinkList.element<AEContentLink*>(i);
						if (contentLink->getAIelement() == ElementFunction && contentLink->getChar() == '+')
							{
							QString s = QString::fromWCharArray(contentLink->getAFelement()->getCode().data());							
							s += "->" + QString::fromWCharArray(contentLink->getAFelement()->getFunction()->getCode().data());
							if (QString::fromWCharArray(SubjectRelationElement->getCode().data()) == code)
							{
								ArgumentsVector.push_back(QString::fromWCharArray(contentLink->getAFelement()->getCode().data()));
							}
							ui.textBrowser->append(s);
							}

						}
					}
				ui.textBrowser->append("} \n");
					}
			}
	}
	return ArgumentsVector;
}

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
		vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(code.size(), 0), QColor(162, 224, 229), Qt::BackgroundColorRole);
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
				if (j - 1 == i)
				{
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), code[i], Qt::DisplayRole);
				}
				if (i == (code.size()) && j == 0)
				{
					vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(i, j), 1, Qt::DisplayRole);
				}				
			}
		}

		//проверка инф. связности
		bool ArgumentCheck = false;		
		for (int j = 0; j < code.size(); ++j)
		{	
			elementRelations newElement;
			newElement.code = code[j];
			auto OArgumentsVector = OutInfromationLinkCheck(code[j]);
			newElement.relatedElementsOut = OArgumentsVector;
			auto IArgumentsVector = InInfromationLinkCheck(code[j]);
			newElement.relatedElementsIn = IArgumentsVector;

			if (DefaultArgument(code[j]))
			{
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(j, 0), 1, Qt::DisplayRole);
			}
			if (OArgumentsVector.size() !=0 || IArgumentsVector.size() != 0)
			{
				ArgumentCheck = true;
				std::vector<int> OArgumentCheck;
				std::vector<int> IArgumentCheck;
				OArgumentCheck.clear();
				IArgumentCheck.clear();

				for (auto Argument : OArgumentsVector)
				{
					OArgumentCheck.push_back(0);
				}

				for (auto Argument : IArgumentsVector)
				{
					IArgumentCheck.push_back(0);
				}

				for (int i = 0; i < OArgumentsVector.size(); ++i)
				{
					for (int c = 0; c < code.size() + 1; ++c)
					{
						int m = c + 1;							
								if (vEleMatr[k].childMatrix->index(c, m).data() == OArgumentsVector[i])
								{
									vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(c, j+1), "1", Qt::DisplayRole);
									OArgumentCheck[i] = 1;
									break;
								}										
							if (OArgumentCheck[i] == 1) break;
					}
					
					if (i == OArgumentsVector.size() - 1)
					{
						for (int c = 0; c < OArgumentsVector.size(); c++)
						{
							if (OArgumentCheck[c] == 0)
							{
								vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(code.size(), j), "1", Qt::DisplayRole);
							}
						}
					}
				}

				//входные
				for (int i = 0; i < IArgumentsVector.size(); ++i)
				{
					for (int c = 0; c < code.size() + 1; ++c)
					{						
							int m = c + 1;							
								if (vEleMatr[k].childMatrix->index(c, m).data() == IArgumentsVector[i])
								{
									vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(j, m), "1", Qt::DisplayRole);
									IArgumentCheck[i] = 1;
									break;								
							}
							if (IArgumentCheck[i] == 1) break;						
					}
					if (i == IArgumentsVector.size() - 1)
					{
						for (int c = 0; c < IArgumentsVector.size(); c++)
						{
							if (IArgumentCheck[c] == 0)
							{
								vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(j, 0), "1", Qt::DisplayRole);
							}
						}
					}
				}
			}
		}
		if (!ArgumentCheck)
		{
			for (int o = 0; o < code.size() + 1; ++o)
			{
				vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(o, o), "1", Qt::DisplayRole);
			}
		}		
		vEleMatr[k].childMatrix->setData(vEleMatr[k].childMatrix->index(code.size(), 0), QColor(240, 100, 10, 40), Qt::BackgroundColorRole);
	}

	//отрисовка элементов графического интерфейса
	btn->setModel(vEleMatr[k].childMatrix);	
	btn->verticalHeader()->hide();
	btn->horizontalHeader()->hide();
	btn->setMinimumHeight(0);
	btn->setMinimumWidth(0);
	btn->resizeColumnsToContents();
	btn->resizeRowsToContents();
	btn->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	btn->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	int w = 0, h = 0;
	for (int i = 0; i < vEleMatr[k].childMatrix->columnCount(); ++i)
		w += btn->columnWidth(i);
	for (int i = 0; i < vEleMatr[k].childMatrix->rowCount(); ++i)
		h += btn->rowHeight(i);	
	//btn->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	
	
	btn->setFixedHeight(h);
	btn->setFixedWidth(w);
	btn->adjustSize();
	// btn->setFixedHeight(71 + 23 * (code.size() - 2));
	//btn->setFixedWidth(41 + 39 * code.size());	
	l->setMargin(0);
	l->addSpacing(7);	
	l->addWidget(lbl);
	l->addWidget(btn);	
	l->addStretch();
	//l->addSpacerItem(new QSpacerItem(7, 0, QSizePolicy::Maximum, QSizePolicy::Maximum));
	//l->minimumSize();
	l->setDirection(QBoxLayout::LeftToRight);	
	l->setAlignment(Qt::AlignCenter);
	wgt->setMinimumHeight(0);
	wgt->setMinimumWidth(0);
	wgt->setLayout(l);			
	wgt->setFixedWidth(350);
	//wgt->setFixedWidth(41 + 41 * code.size() + 7 + 40);	
	//wgt->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//ui.textBrowser->clear();
	return wgt;
}

//функция реструктуризации
void MyModuleForm::restructFunc(QStandardItemModel *restTable)
{
	int zeroC = 0, zeroRowCount = 0, flag = 0;
	while (flag < 2)
	{
		for (int k = 0; k < vEleMatr.size(); ++k)
		{
			for (int i = 0; i < restTable->rowCount(); ++i)
			{				
				for (int j = 1; j < i+2; ++j)
				{
					if (restTable->index(i, j).data(Qt::DisplayRole).toString().startsWith("c") && restTable->index(i, j - 1).data(Qt::DisplayRole).toString().indexOf("1") == -1 && (j-1!=0))
					{
						zeroRowCount = 1; //начальное смещение
						for (int zerorow = 1; zerorow < restTable->columnCount(); zerorow++) //расчет доп. смещения
						{
							if (restTable->index(i, j - 1 - zerorow).data(Qt::DisplayRole).toString().indexOf("1") == -1 && (j - 1 - zerorow!=0))
							{
								zeroRowCount++;
								
							}
							else break;
						}
						for (int v = 0; v < restTable->rowCount(); ++v)
						{
							if (!(restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString().startsWith("c")))
							{
								
								if (restTable->index(v, j).data(Qt::DisplayRole).toString().startsWith("c") && restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString().indexOf("1") == -1)
								{
									restTable->setData(restTable->index(v, j - zeroRowCount), restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);									
									restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									
								}
								else if (restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString().startsWith("1") /*&& !restTable->index(v, j).data(Qt::DisplayRole).toString().startsWith("c")*/)
								{
									restTable->setData(restTable->index(v, j - zeroRowCount), restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString() + "/" + restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
									restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									
								}
								else if ((restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString().startsWith("0")) && (restTable->index(v, j).data(Qt::DisplayRole).toString() != "0"))
								{	
									bool flag = 0;
									for (int counter = 0; counter < v; counter++)
									{
										if (restTable->index(counter, j - zeroRowCount).data(Qt::DisplayRole).toString().indexOf("/") != -1)
										{
											flag = 1;
											break;
										}
											
									}
									if (flag)
									{
										restTable->setData(restTable->index(v, j - zeroRowCount), restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString() + "/" +  restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
										restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									}
									else
									{
										restTable->setData(restTable->index(v, j - zeroRowCount), restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
										restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);
									}
									
								}
								else if ((restTable->index(v, j).data(Qt::DisplayRole).toString() == "0") && (restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString().indexOf("/") != -1))
								{
									restTable->setData(restTable->index(v, j - zeroRowCount), restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString() + "/" + restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
									restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);

								}
								
								else if ((restTable->index(v, j).data(Qt::DisplayRole).toString() == "0") && (restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString() == "0"))
								{

									restTable->setData(restTable->index(v, j - zeroRowCount), restTable->index(v, j - zeroRowCount).data(Qt::DisplayRole).toString() + "/" + restTable->index(v, j).data(Qt::DisplayRole).toString(), Qt::DisplayRole);
									restTable->setData(restTable->index(v, j), 0, Qt::DisplayRole);

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
	for (int i = 0; i < restTable->rowCount(); ++i)
	{
		for (int j = 0; j < restTable->columnCount(); ++j)
		{
			if (restTable->index(i, j).data(Qt::DisplayRole).toString().startsWith("c"))
			{
				restTable->setData(restTable->index(i, j), QColor(162, 224, 229, 40), Qt::BackgroundColorRole);
			}			
			if (restTable->index(i, j).data(Qt::DisplayRole).toString().indexOf("/") != -1 && restTable->index(i, j).data(Qt::DisplayRole).toString().indexOf("1") == -1)
			{
				restTable->setData(restTable->index(i, j), 0, Qt::DisplayRole);
			}
		}
	}
	ui.optiTableView->resizeColumnsToContents();
	ui.optiTableView->resizeRowsToContents();
	int TableHeight = 0, TableWidth = 0;
	for (int j = 0; j < restTable->columnCount(); ++j)
	{
		TableWidth += ui.optiTableView->columnWidth(j);
	}
	for (int i = 0; i < restTable->rowCount(); ++i)
	{
		TableHeight += ui.optiTableView->rowHeight(i);
	}
	ui.optiTableView->setFixedHeight(TableHeight + 2);
	ui.optiTableView->setFixedWidth(TableWidth + 2);

	int elementCount = 0;
	for (int i = 0; i < restTable->columnCount(); ++i)
	{
		for (int j = 0; j < restTable->rowCount(); ++j)
		{
			if (restTable->index(j, i).data(Qt::DisplayRole).toString().startsWith("c"))
			{
				elementCount = elementCount++;
			}
		}
		if (elementCount == 1)
		{
			for (int j = 0; j < restTable->rowCount(); ++j)
			{
				if (restTable->index(j, i).data(Qt::DisplayRole).toString() == "0/1")
				{
					restTable->setData(restTable->index(j, i), "1", Qt::DisplayRole);
				}
			}
		}
		elementCount = 0;
	}
	
}


	
	//функция итерационного расширения общей таблицы (одна итерация)
	void MyModuleForm::oneStep()
	{
		for (int i = 0; i < fullTable->rowCount(); ++i)
			for (int j = 0; j < fullTable->columnCount(); ++j)
				fullTable->setData(fullTable->index(i, j), QColor(255,255, 255), Qt::BackgroundColorRole);

		if ((vEleMatr.size() > 1) && (currElement < vEleMatr.size()))
		{
				for (int i = 0; i < fullTable->rowCount(); ++i)
					//for (int j = 0; j < fullTable->columnCount(); ++j)
				//	{
						if (vEleMatr[currElement].code == fullTable->index(i, i+1).data(Qt::DisplayRole).toString())
						{  
							//встраивание таблицы детей (наследников) сложной предметной зависимоти в общую таблину
							int itemI = i;
							int itemJ = i+1;
							fullTable->insertRows(itemI+1, vEleMatr[currElement].childMatrix->rowCount() - 2);
							fullTable->insertColumns(itemJ+1, vEleMatr[currElement].childMatrix->columnCount() - 2);
							//ui.fullTableView->setFixedHeight(fullTable->rowCount() * 24 - fullTable->rowCount() + 2);
							//ui.fullTableView->setFixedWidth(fullTable->columnCount() * 40 - fullTable->columnCount() + 2);
							for (int r = 0; r < vEleMatr[currElement].childMatrix->rowCount(); ++r)
								for (int c = 0; c < vEleMatr[currElement].childMatrix->columnCount(); ++c)
								{
									if (c == 0 && r == vEleMatr[currElement].childMatrix->rowCount() - 1)
									{
										fullTable->setData(fullTable->index(itemI + r, itemJ + c - 1), 0, Qt::DisplayRole);
										fullTable->setData(fullTable->index(itemI + r, itemJ + c - 1), QColor(237, 228, 133, 90), Qt::BackgroundColorRole);
									}
									else
									{
										fullTable->setData(fullTable->index(itemI + r, itemJ + c - 1), vEleMatr[currElement].childMatrix->index(r, c).data(), Qt::DisplayRole);
										fullTable->setData(fullTable->index(itemI + r, itemJ + c - 1), QColor(237, 228, 133, 90), Qt::BackgroundColorRole);
									}
								}
							i += vEleMatr[currElement].childMatrix->rowCount() - 2;
						//	j += vEleMatr[currElement].childMatrix->columnCount() - 2;
						//}
					}

				//перерасчет таблицы

				//очистка
				for (int i = 0; i < fullTable->rowCount(); ++i)
					for (int j = 0; j < fullTable->columnCount(); ++j)
						if ((j-1 != i))
							fullTable->setData(fullTable->index(i, j), "0", Qt::DisplayRole);

				//перерасчет информационной связности
				for (int i = 0; i < fullTable->rowCount() - 1; ++i)
				{
					for (int j = i+1; j < i+2; ++j)
					{
						QString ele = fullTable->index(i, j).data(Qt::DisplayRole).toString();
						if (j - 1 == i)
						{
							if (DefaultArgument(fullTable->index(i, j).data(Qt::DisplayRole).toString()))
							{
								fullTable->setData(fullTable->index(j - 1, 0), "1", Qt::DisplayRole);
							}
							auto OutArgumentsVector = OutInfromationLinkCheck(fullTable->index(i, j).data(Qt::DisplayRole).toString());
							auto InArgumentsVector = InInfromationLinkCheck(fullTable->index(i, j).data(Qt::DisplayRole).toString());
							if (OutArgumentsVector.size() > 0)
							{
								std::vector<int> ArgumentCheck;
								ArgumentCheck.clear();
								for (auto Argument : OutArgumentsVector)
								{
									ArgumentCheck.push_back(0);
								}


								for (int k = 0; k < OutArgumentsVector.size(); ++k)
								{
									for (int c = 0; c < fullTable->rowCount(); ++c)
									{
										if (fullTable->index(c, c + 1).data() == OutArgumentsVector[k])
										{
											fullTable->setData(fullTable->index(c, j), "1", Qt::DisplayRole);
											ArgumentCheck[k] = 1;
											if (c + 1 == 7 && i == 2)
											{
												int a = 14;
											}
											break;
										}

									}
									if (k == OutArgumentsVector.size() - 1)
									{
										for (int c = 0; c < OutArgumentsVector.size(); c++)
										{
											if (ArgumentCheck[c] == 0)
											{
												fullTable->setData(fullTable->index(fullTable->rowCount() - 1, j), "1", Qt::DisplayRole);
											}
										}
									}
								}
							}
							if (InArgumentsVector.size() > 0)
							{
								std::vector<int> SecondaryArgumentCheck;
								SecondaryArgumentCheck.clear();
								for (auto Argument : InArgumentsVector)
								{
									SecondaryArgumentCheck.push_back(0);
								}

								for (int k = 0; k < InArgumentsVector.size(); ++k)
								{
									for (int c = 0; c < fullTable->rowCount(); ++c)
									{
										for (int m = 1; m < c + 2; ++m)
										{
											if (m - 1 == c)
											{
												if (fullTable->index(c, m).data() == InArgumentsVector[k])
												{
													fullTable->setData(fullTable->index(i, m), "1", Qt::DisplayRole);
													SecondaryArgumentCheck[k] = 1;
													if (j == 2 && m == 7)
													{
														int a = 14;
													}
												}
											}
										}
									}
									if (k == InArgumentsVector.size() - 1)
									{
										for (int c = 0; c < InArgumentsVector.size(); c++)
										{
											if (SecondaryArgumentCheck[c] == 0)
											{
												fullTable->setData(fullTable->index(0, j), "1", Qt::DisplayRole);
											}
										}
									}
								}


							}
						}
					}
				}
				
				currElement++; //переход на следующий элемент

			//графическое отображение
			ui.fullTableView->resizeColumnsToContents();
			ui.fullTableView->resizeRowsToContents();
			QString IterationCount = QString::number(vEleMatr.size() - currElement);
			ui.iterationLable->setText("Оставшееся количество итераций: " + IterationCount);
		}

		if (currElement == vEleMatr.size()) //если таблица полностью заполнена
		{	
			//обесцвечивание таблицы
			for (int i = 0; i < fullTable->rowCount(); ++i)
				for (int j = 0; j < fullTable->columnCount(); ++j)
					fullTable->setData(fullTable->index(i, j), QColor(255, 255, 255), Qt::BackgroundColorRole);
			//отрисовка итераций
			for (int m = 0; m < iterationsVector.size(); m++)
			{
				for (int l = 0; l < iterationsVector[m].children.size(); l++)
				{
					//if (elementsIterations[m].element<AFElement *>(l)->getType() == FEType::None)
					for (int i = 0; i < fullTable->rowCount(); i++)
						for (int j = 1; j < i + 2; j++)
						{
							if (iterationsVector[m].children[l] == fullTable->index(i, j).data(Qt::DisplayRole).toString())
							{
								fullTable->setData(fullTable->index(i, j), iterationsVector[m].iterColor, Qt::BackgroundColorRole);
								fullTableAdd1->setData(fullTableAdd1->index(i, j), iterationsVector[m].iterColor, Qt::BackgroundColorRole);
								if (l == 0)
								{
									iterationsVector[m].startI = i;
									iterationsVector[m].startJ = j;
								}
								if (l == iterationsVector[m].children.size() - 1)
								{
									iterationsVector[m].finishI = i;
									iterationsVector[m].finishJ = j;
								}
							}
						}
				}
			}
			for (int m = 0; m < iterationsVector.size(); m++)
			{
				//if (iterationsV[m].startI == iterationsV[m].finishI == iterationsV[m].startJ == iterationsV[m].finishJ) continue;
				//else
				{
					for (int i = iterationsVector[m].startI; i <= iterationsVector[m].finishI; i++)
					{
						for (int j = iterationsVector[m].startJ; j <= iterationsVector[m].finishJ; j++)
						{
							fullTable->setData(fullTable->index(i, j), iterationsVector[m].iterColor, Qt::BackgroundColorRole);
							fullTableAdd1->setData(fullTableAdd1->index(i, j), iterationsVector[m].iterColor, Qt::BackgroundColorRole);
						}
					}
				}
			}

			//поиск обратных (некорректных связей)
			bool incompetenceFound = false;
			for (int i = 0; i < fullTable->rowCount(); ++i)
				for (int j = i+1; j < fullTable->columnCount(); ++j)
					if (fullTable->index(i, j).data(Qt::DisplayRole).toString() == "1")
					{
						fullTable->setData(fullTable->index(i, j), QColor(255, 0, 0, 120), Qt::BackgroundColorRole);
						incompetenceFound = true;
					}
								
			ui.oneIterButt->setEnabled(false);
			ui.allIterButt->setEnabled(false);
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
			ui.expandedTableView->resizeColumnsToContents();
			ui.expandedTableView->resizeRowsToContents();
			//ui.expandedTableView->setFixedHeight(fullTable->rowCount() * 24 - fullTable->rowCount() + 2);
			//ui.expandedTableView->setFixedWidth(fullTable->columnCount() * 40 - fullTable->columnCount() + 2);
			restTable->clear();
			restTable->setColumnCount(fullTable->columnCount());
			restTable->setRowCount(fullTable->rowCount());
			for (int i = 0; i < fullTable->rowCount(); ++i)
				for (int j = 0; j < fullTable->columnCount(); ++j)
				{
					restTable->setData(restTable->index(i, j), fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString());
				}

			ui.optiTableView->setModel(restTable);
			ui.optiTableView->setVisible(true);
			ui.optiLable->setText(vEleMatr[0].code + " = ");
			restructFunc(restTable);
			ui.specTab->setTabEnabled(3, true);
			if (incompetenceFound)
			{
				QMessageBox msgBox;
				msgBox.setWindowIcon(QIcon(":/restruct_resource/IS2Icon"));
				msgBox.setWindowTitle("Модуль реструктуризации");
				msgBox.setText("Внимание!");
				msgBox.setInformativeText("Обнаружены обратные связи между элементами: функция рассчитывается раньше, чем ее аргумент. Проверьте правильность свойств элементов!");
				msgBox.setStandardButtons(QMessageBox::Ok);
				msgBox.setDefaultButton(QMessageBox::Ok);	
				int ret = msgBox.exec();
			}
		}
		
	}

	//функция итерационного расширения общей таблицы (все итерации)
	void MyModuleForm::allSteps()
	{
		//обесцвечивание таблицы
		for (int i = 0; i < fullTable->rowCount(); ++i)
			for (int j = 0; j < fullTable->columnCount(); ++j)
				fullTable->setData(fullTable->index(i, j), QColor(255, 255, 255), Qt::BackgroundColorRole);

		if ((vEleMatr.size()) > 1 && (currElement < vEleMatr.size()))
		{

			//полоса статуса построения
			ui.fullTableView->setVisible(false);
			ui.fullLable->setVisible(false);
			QProgressDialog dlg("Создание полной таблицы...", QString(), 0, (ElementsVector.size() + fullTable->rowCount() + 4));			
			dlg.setWindowTitle("Реструктуризация");
			dlg.setAutoClose(false);
			dlg.setMinimumDuration(1);
			dlg.setWindowModality(Qt::WindowModal);
			dlg.setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
			dlg.setWindowIcon(QIcon(":/restruct_resource/IS2Icon"));
			QString statusBar = "";
			//

			for (currElement; currElement < vEleMatr.size(); ++currElement)
			{
				statusBar = "Встраивание таблиц " + QVariant(currElement).toString() + " из " + QVariant(vEleMatr.size()).toString();
				dlg.setLabelText(statusBar);
				for (int i = 0; i < fullTable->rowCount(); ++i)
					//for (int j = 0; j < fullTable->columnCount(); ++j)
					//{
						if (vEleMatr[currElement].code == fullTable->index(i, i+1).data(Qt::DisplayRole).toString())
						{
							int itemI = i;
							int itemJ = i+1;
							fullTable->insertRows(itemI+1, vEleMatr[currElement].childMatrix->rowCount() - 2);
							fullTable->insertColumns(itemJ+1, vEleMatr[currElement].childMatrix->columnCount() - 2);
							//ui.fullTableView->setFixedHeight(fullTable->rowCount() * 24 - fullTable->rowCount() + 2);
							//ui.fullTableView->setFixedWidth(fullTable->columnCount() * 40 - fullTable->columnCount() + 2);
							for (int r = 0; r < vEleMatr[currElement].childMatrix->rowCount(); ++r)
								for (int c = 0; c < vEleMatr[currElement].childMatrix->columnCount(); ++c)
									fullTable->setData(fullTable->index(itemI + r, itemJ + c - 1), vEleMatr[currElement].childMatrix->index(r, c).data(), Qt::DisplayRole);
							i += vEleMatr[currElement].childMatrix->rowCount() - 2;
							//j += vEleMatr[currElement].childMatrix->columnCount() - 2;
						//}
					}
				for (int i = 0; i < fullTable->rowCount(); ++i)
					for (int j = 0; j < fullTable->columnCount(); ++j)
						if (fullTable->item(i, j) == 0)
							fullTable->setData(fullTable->index(i, j), "0", Qt::DisplayRole);
				
				dlg.setValue(currElement + 1);				
			}
			
			//перерасчет таблицы

			//очистка
			statusBar = "Начало перерасчета связей";
			dlg.setLabelText(statusBar);
			for (int i = 0; i < fullTable->rowCount(); ++i)
			{
				for (int j = 0; j < fullTable->columnCount(); ++j)
					if ((fullTable->item(i, j) == 0) || (j - 1 != i))
						fullTable->setData(fullTable->index(i, j), "0", Qt::DisplayRole);
			}
			dlg.setValue(dlg.value() + 1);
			//

			//перерасчет информационной связности
			
			for (int i = 0; i < fullTable->rowCount(); ++i)
			{
				statusBar = "Перерасчет связей элемента № " + QVariant(i).toString() + " из " + QVariant(fullTable->rowCount()).toString();;
				dlg.setLabelText(statusBar);
				for (int j = 1; j < fullTable->columnCount(); ++j)
				{
					QString ele = fullTable->index(i, j).data(Qt::DisplayRole).toString();
					if (j - 1 == i)
					{
						if (DefaultArgument(fullTable->index(i, j).data(Qt::DisplayRole).toString()))
						{
							fullTable->setData(fullTable->index(j - 1, 0), "1", Qt::DisplayRole);
						}
						auto OutArgumentsVector = OutInfromationLinkCheck(fullTable->index(i, j).data(Qt::DisplayRole).toString());
						auto InArgumentsVector = InInfromationLinkCheck(fullTable->index(i, j).data(Qt::DisplayRole).toString());
						if (OutArgumentsVector.size() > 0)
						{
							std::vector<int> ArgumentCheck;
							ArgumentCheck.clear();
							for (auto Argument : OutArgumentsVector)
							{
								ArgumentCheck.push_back(0);
							}


							for (int k = 0; k < OutArgumentsVector.size(); ++k)
							{
								for (int c = 0; c < fullTable->rowCount(); ++c)
								{
									if (fullTable->index(c, c + 1).data() == OutArgumentsVector[k])
									{
										fullTable->setData(fullTable->index(c, j), "1", Qt::DisplayRole);
										ArgumentCheck[k] = 1;
										if (c + 1 == 7 && i == 2)
										{
											int a = 14;
										}
										break;
									}

								}
								if (k == OutArgumentsVector.size() - 1)
								{
									for (int c = 0; c < OutArgumentsVector.size(); c++)
									{
										if (ArgumentCheck[c] == 0)
										{
											fullTable->setData(fullTable->index(fullTable->rowCount() - 1, j), "1", Qt::DisplayRole);
										}
									}
								}
							}
						}
						if (InArgumentsVector.size() > 0)
						{
							std::vector<int> SecondaryArgumentCheck;
							SecondaryArgumentCheck.clear();
							for (auto Argument : InArgumentsVector)
							{
								SecondaryArgumentCheck.push_back(0);
							}

							for (int k = 0; k < InArgumentsVector.size(); ++k)
							{
								for (int c = 0; c < fullTable->rowCount(); ++c)
								{
									for (int m = 1; m < c + 2; ++m)
									{
										if (m - 1 == c)
										{
											if (fullTable->index(c, m).data() == InArgumentsVector[k])
											{
												fullTable->setData(fullTable->index(i, m), "1", Qt::DisplayRole);
												SecondaryArgumentCheck[k] = 1;
												if (j == 2 && m == 7)
												{
													int a = 14;
												}
											}
										}
									}
								}
								if (k == InArgumentsVector.size() - 1)
								{
									for (int c = 0; c < InArgumentsVector.size(); c++)
									{
										if (SecondaryArgumentCheck[c] == 0)
										{
											fullTable->setData(fullTable->index(0, j), "1", Qt::DisplayRole);
										}
									}
								}
							}


						}
					}
				}
				dlg.setValue(dlg.value() + 1);
				}
			
			
			
//			ui.pushButton->setEnabled(false);
//			ui.pushButton_2->setEnabled(false);

			statusBar = "Завершение расчетов";
			dlg.setLabelText(statusBar);
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
			dlg.setValue(dlg.value() + 2);
			//ui.expandedTableView->setFixedHeight(fullTable->rowCount() * 24 - fullTable->rowCount() + 2);
			//ui.expandedTableView->setFixedWidth(fullTable->columnCount() * 40 - fullTable->columnCount() + 2);
			ui.expandedTableView->resizeColumnsToContents();
			ui.expandedTableView->resizeRowsToContents();

			restTable->clear();
			restTable->setColumnCount(fullTable->columnCount());
			restTable->setRowCount(fullTable->rowCount());
			ui.iterationLable->setText("Оставшееся количество итераций: 0");
			
			for (int i = 0; i < fullTable->rowCount(); ++i)
				for (int j = 0; j < fullTable->columnCount(); ++j)
				{
					restTable->setData(restTable->index(i, j), fullTableAdd1->index(i, j).data(Qt::DisplayRole).toString());
				}
			dlg.setValue(dlg.value() + 1);
			ui.optiTableView->setModel(restTable);
			ui.optiTableView->setVisible(true);
//			ui.tabWidget->setTabEnabled(2, true);
//			ui.tabWidget->setTabEnabled(3, true);
			restructFunc(restTable);
		//	dlg.setValue(dlg.value() + 2);
			dlg.setValue(dlg.value() + 1);
			ui.fullTableView->setVisible(true);
			ui.fullLable->setVisible(true);

		}
		
		ui.fullTableView->resizeColumnsToContents();
		ui.fullTableView->resizeRowsToContents();
		int w = 0, h = 0;
		for (int i = 0; i < fullTable->columnCount(); ++i)
			w += ui.fullTableView->columnWidth(i);
		for (int i = 0; i < fullTable->rowCount(); ++i)
			h += ui.fullTableView->rowHeight(i);

		ui.fullTableView->setFixedHeight(h);
		ui.fullTableView->setFixedWidth(w);
		ui.expandedTableView->setFixedWidth(w);
		ui.expandedTableView->setFixedHeight(h);
		//отображение циклов (переработать??)
		for (int m = 0; m < iterationsVector.size(); m++)
		{
			for (int l = 0; l < iterationsVector[m].children.size(); l++)
			{
				//if (elementsIterations[m].element<AFElement *>(l)->getType() == FEType::None)
					for (int i = 0; i < fullTable->rowCount(); i++)
						for (int j = 1; j < i+2; j++)
						{
							if (iterationsVector[m].children[l] == fullTable->index(i, j).data(Qt::DisplayRole).toString())
							{
								fullTable->setData(fullTable->index(i, j), iterationsVector[m].iterColor, Qt::BackgroundColorRole);
								fullTableAdd1->setData(fullTableAdd1->index(i, j), iterationsVector[m].iterColor, Qt::BackgroundColorRole);
								if (l == 0)
								{
									iterationsVector[m].startI = i;
									iterationsVector[m].startJ = j;
								}
								if (l == iterationsVector[m].children.size()-1)
								{
									iterationsVector[m].finishI = i;
									iterationsVector[m].finishJ = j;
								}
							}
						}
			}
		}
		for (int m = 0; m < iterationsVector.size(); m++)
		{
			//if (iterationsV[m].startI == iterationsV[m].finishI == iterationsV[m].startJ == iterationsV[m].finishJ) continue;
			//else
			{
				for (int i = iterationsVector[m].startI; i <= iterationsVector[m].finishI; i++)
				{
					for (int j = iterationsVector[m].startJ; j <= iterationsVector[m].finishJ; j++)
					{
						fullTable->setData(fullTable->index(i, j), iterationsVector[m].iterColor, Qt::BackgroundColorRole);
						fullTableAdd1->setData(fullTableAdd1->index(i, j), iterationsVector[m].iterColor, Qt::BackgroundColorRole);
					}
				}
			}
		}
		ui.specTab->setTabEnabled(3, true);
		ui.oneIterButt->setEnabled(false);
		ui.allIterButt->setEnabled(false);
	}

	//функция создания таблиц спецификаций
	void MyModuleForm::createSpecTables()
	{
		ui.S1Table->setVisible(false);
		ui.S2Table->setVisible(false);
		ui.STable->setVisible(false);
		
		SHeaderModel->setColumnCount(6);
		SHeaderModel->setRowCount(2);
		SHeaderModel->setData(SHeaderModel->index(0, 0), "Код сложной зависимости", Qt::DisplayRole);
		SHeaderModel->setData(SHeaderModel->index(0, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
		SHeaderModel->setData(SHeaderModel->index(0, 2), "Код параметра", Qt::DisplayRole);
		SHeaderModel->setData(SHeaderModel->index(0, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
		SHeaderModel->setData(SHeaderModel->index(1, 0), "Уровень", Qt::DisplayRole);
		SHeaderModel->setData(SHeaderModel->index(1, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
		SHeaderModel->setData(SHeaderModel->index(1, 1), "Позиция", Qt::DisplayRole);
		SHeaderModel->setData(SHeaderModel->index(1, 1), Qt::AlignCenter, Qt::TextAlignmentRole);
		SHeaderModel->setData(SHeaderModel->index(1, 2), "Группа", Qt::DisplayRole);
		SHeaderModel->setData(SHeaderModel->index(1, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
		SHeaderModel->setData(SHeaderModel->index(1, 3), "Номер", Qt::DisplayRole);
		SHeaderModel->setData(SHeaderModel->index(1, 3), Qt::AlignCenter, Qt::TextAlignmentRole);
		SHeaderModel->setData(SHeaderModel->index(0, 4), "Роль", Qt::DisplayRole);
		SHeaderModel->setData(SHeaderModel->index(0, 4), Qt::AlignCenter, Qt::TextAlignmentRole);
		SHeaderModel->setData(SHeaderModel->index(0, 5), "Вид информации", Qt::DisplayRole);
		SHeaderModel->setData(SHeaderModel->index(0, 5), Qt::AlignCenter, Qt::TextAlignmentRole);


		S1HeaderModel->setColumnCount(3);
		S1HeaderModel->setRowCount(2);
		S1HeaderModel->setData(S1HeaderModel->index(0, 0), "Код сложной зависимости", Qt::DisplayRole);
		S1HeaderModel->setData(S1HeaderModel->index(0, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
		S1HeaderModel->setData(S1HeaderModel->index(0, 2), "Ранг", Qt::DisplayRole);
		S1HeaderModel->setData(S1HeaderModel->index(0, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
		S1HeaderModel->setData(S1HeaderModel->index(1, 0), "Уровень", Qt::DisplayRole);
		S1HeaderModel->setData(S1HeaderModel->index(1, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
		S1HeaderModel->setData(S1HeaderModel->index(1, 1), "Позиция", Qt::DisplayRole);
		S1HeaderModel->setData(S1HeaderModel->index(1, 1), Qt::AlignCenter, Qt::TextAlignmentRole);

		S2HeaderModel->setColumnCount(4);
		S2HeaderModel->setRowCount(2);
		S2HeaderModel->setData(S2HeaderModel->index(0, 0), "Код сложной зависимости", Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(0, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
		S2HeaderModel->setData(S2HeaderModel->index(0, 2),"Код зависимости", Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(0, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 0), "Уровень", Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 1), "Позиция", Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 1), Qt::AlignCenter, Qt::TextAlignmentRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 2), "Уровень", Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 2), Qt::AlignCenter, Qt::TextAlignmentRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 3), "Позиция", Qt::DisplayRole);
		S2HeaderModel->setData(S2HeaderModel->index(1, 3), Qt::AlignCenter, Qt::TextAlignmentRole);

		ui.S2Header->setModel(S2HeaderModel);
		ui.S2Header->verticalHeader()->hide();
		ui.S2Header->horizontalHeader()->hide();
		ui.S2Header->setSpan(0, 0, 1, 2);
		ui.S2Header->setSpan(0, 2, 1, 2);
		//ui.S2Header->resizeColumnsToContents();
		ui.S2Header->resizeRowsToContents();
		//ui.S2Header->setFixedWidth(402);
		//ui.S2Header->setFixedHeight(58);
		ui.S2Header->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.S2Header->setSelectionMode(QAbstractItemView::NoSelection);
		ui.S2Header->setSelectionBehavior(QAbstractItemView::SelectRows);

		ui.SHeader->setModel(SHeaderModel);
		ui.SHeader->verticalHeader()->hide();
		ui.SHeader->horizontalHeader()->hide();
		ui.SHeader->setSpan(0, 0, 1, 2);
		ui.SHeader->setSpan(0, 2, 1, 2);
		ui.SHeader->setSpan(0, 4, 2, 1);
		ui.SHeader->setSpan(0, 5, 2, 1);
		//ui.S2Header->resizeColumnsToContents();
		//ui.SHeader->resizeRowsToContents();
		//ui.SHeader->setFixedWidth(602);
		//ui.SHeader->setFixedHeight(58);
		ui.SHeader->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.SHeader->setSelectionMode(QAbstractItemView::NoSelection);
		ui.SHeader->setSelectionBehavior(QAbstractItemView::SelectRows);
		


		ui.S1Header->setModel(S1HeaderModel);
		ui.S1Header->verticalHeader()->hide();
		ui.S1Header->horizontalHeader()->hide();
		//ui.S1Header->setFixedWidth(302);
		//ui.S1Header->setFixedHeight(58);
		ui.S1Header->setSpan(0, 0, 1, 2);
		ui.S1Header->setSpan(0, 2, 2, 1);
		//ui.S1Header->resizeColumnsToContents();
		//ui.S1Header->resizeRowsToContents();
		ui.S1Header->setEditTriggers(QAbstractItemView::NoEditTriggers);
		ui.S1Header->setSelectionMode(QAbstractItemView::NoSelection);
		ui.S1Header->setSelectionBehavior(QAbstractItemView::SelectRows);
	}

	//очистка созданных таблиц
	void MyModuleForm::deleteCreatedTables()
	{
		QLayoutItem* child;
		//qDeleteAll(ui.tableVLayout->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
		while (!ui.tableVLayout->isEmpty()) {
				child = ui.tableVLayout->takeAt(0);
				if (child->layout() != 0) {
					QLayout *hb = child->layout();
					while (!hb->isEmpty()) {
						QWidget *w = hb->takeAt(0)->widget();
						delete w;
					}
				}
				else if (child->widget() != 0) {
					delete child->widget();
				}

				delete child;
			}
		/*
			if (ui.tableVLayout->takeAt(0)->widget())
			{
				QWidget *w = ui.tableVLayout->takeAt(0)->widget();
				delete w;
			}
			if (ui.tableVLayout->takeAt(0)->layout())
			{
				QLayout *hb = ui.tableVLayout->takeAt(0)->layout();
				while (!hb->isEmpty()) {
					QWidget *w = hb->takeAt(0)->widget();
					delete w;
				}
				delete hb;
			}
		}		*/
		/*
		for (int i = ui.tableVLayout->count(); i >= 0; --i)
		{
			QLayoutItem* item = ui.tableVLayout->takeAt(i);
			if (item)
			{

				QWidget* widget = item->widget();
				if (widget)
				{
					ui.tableVLayout->removeWidget(widget);
					delete widget;
				}
				ui.tableVLayout->removeItem(item);
				delete item;
				//--i;
			}
			//qDeleteAll(ui.tableVLayout->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
			*/			
	}

	//создание таблиц
	void MyModuleForm::createItemTables()
	{
		ui.notificationLabel->setVisible(false);
		ui.createTablesButt->setEnabled(false);
		ui.deleteTablesButt->setEnabled(false);
		//iterationsV.clear();
		deleteCreatedTables();
		tableLayouts.clear();
		currElement = 1;
		int p = 0, l = 0;		

		QProgressDialog dlg("Создание таблиц...", QString(), 0, vComplicated.size()+2);		
		dlg.setWindowTitle("Реструктуризация");
		dlg.setAutoClose(false);
		dlg.setMinimumDuration(1);
		dlg.setWindowModality(Qt::WindowModal);
		dlg.setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
		dlg.setWindowIcon(QIcon(":/restruct_resource/IS2Icon"));
		QString statusBar = "";
		

		for (int i = 1; i < 9; ++i)
		{
			hLayout tableLayout;
			tableLayout.tableSize = i;
			tableLayout.setSize(i);
			tableLayout.currSize = 0;
			tableLayout.last = true;
			tableLayouts.push_back(tableLayout);
		}
		
		for (int k = 0; k < vComplicated.size(); ++k)
		{
			statusBar = "Создание таблиц " + QVariant(k).toString() + " из " + QVariant(vComplicated.size()).toString();
			dlg.setLabelText(statusBar);
			QWidget * TableWidget = createTable(vComplicated[k], codesfull[k], k);
			for (int i = 0; i < tableLayouts.size(); ++i)
			{
				
				if (codesfull[k].size() == tableLayouts[i].tableSize)
				{
					if (tableLayouts[i].currSize <= tableLayouts[i].maxSize)
					{
						tableLayouts[i].layout->addWidget(TableWidget, 0);
						tableLayouts[i].layout->setAlignment(Qt::AlignLeft);						
						//tableLayouts[i].layout->addStretch();
						tableLayouts[i].currSize++;						
						break;
					}
					else
					{
						tableLayouts[i].layout->addStretch();
						if (tableLayouts[i].last == false)
						{							
							continue;
						}
						else
						{
							hLayout tableLayout;
							tableLayout.tableSize = codesfull[k].size();
							tableLayout.setSize(codesfull[k].size());
							tableLayouts.insert(tableLayouts.begin() + (i + 1), tableLayout);
							tableLayouts[i + 1].layout->addWidget(TableWidget, p);
							//QSpacerItem* item = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
							//tableLayouts[i + 1].layout->addSpacerItem(item);
							//tableLayouts[i+1].layout->addStretch();
							tableLayouts[i + 1].layout->setAlignment(Qt::AlignLeft);
							tableLayouts[i + 1].currSize = 1;
							tableLayouts[i + 1].last = true;
							QSpacerItem* item = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
							tableLayouts[i].layout->addSpacerItem(item);
							tableLayouts[i].layout->addStretch();
							//tableLayouts[i+1].layout->addStretch();
							tableLayouts[i].last = false;
							break;
						}
					}
				}		
				
			}	
		
			
			dlg.setValue(k + 1);
		}

		for (int i = 0; i < tableLayouts.size(); ++i)
		{
			if (tableLayouts[i].currSize == 0)
				tableLayouts.erase(tableLayouts.begin() + i);
		}
		dlg.setValue(dlg.value() + 1);
		

		for (int i = 0; i < tableLayouts.size(); ++i)
		{				
				ui.tableVLayout->addLayout(tableLayouts[i].layout);				
			
			if ((i < tableLayouts.size() -2 ) && (tableLayouts[i].tableSize != tableLayouts[i + 1].tableSize))
			{
				auto lineA = new QFrame;
				lineA->setFrameShape(QFrame::HLine);
				lineA->setFrameShadow(QFrame::Sunken);
				ui.tableVLayout->addWidget(lineA);
			}
		}
		dlg.setValue(dlg.value() + 1);

		if (vComplicated.size() > 0)
		{
			fullTable->clear();
			fullTable->setColumnCount(vEleMatr[0].childMatrix->columnCount());
			fullTable->setRowCount(vEleMatr[0].childMatrix->rowCount());
			for (int i = 0; i < vEleMatr[0].childMatrix->rowCount(); ++i)
				for (int j = 0; j < vEleMatr[0].childMatrix->columnCount(); ++j)
				{
					if ((i == vEleMatr[0].childMatrix->rowCount() - 1) && (j == 0))
					{
						fullTable->setData(fullTable->index(i, j), "0", Qt::DisplayRole);
						continue;
					}
					fullTable->setData(fullTable->index(i, j), vEleMatr[0].childMatrix->index(i, j).data(Qt::DisplayRole).toString());
				}
			ui.createTablesButt->setEnabled(true);
			ui.deleteTablesButt->setEnabled(true);
			ui.iterationLable->setVisible(true);			
			QString IterationCount = QString::number(vComplicated.size() - 1);
			ui.iterationLable->setText("Оставшееся количество итераций: " + IterationCount);
			ui.fullLable->setText(vEleMatr[0].code + " = ");
			ui.fullLable->setVisible(true);
			ui.fullTableView->setVisible(true);
			ui.fullTableView->verticalHeader()->hide();
			ui.fullTableView->horizontalHeader()->hide();
			//ui.fullTableView->setFixedHeight(vEleMatr[0].childMatrix->rowCount() * 24 - vEleMatr[0].childMatrix->rowCount() + 2);
			//ui.fullTableView->setFixedWidth(vEleMatr[0].childMatrix->columnCount() * 40 - vEleMatr[0].childMatrix->columnCount() + 2);
			ui.fullTableView->setModel(fullTable);
			ui.fullTableView->resizeColumnsToContents();
			ui.fullTableView->resizeRowsToContents();			
		}

		if (vComplicated.size() > 1)
		{
			ui.allIterButt->setEnabled(true);
			ui.oneIterButt->setEnabled(true);
		}

		//инициализация расширенной общей таблицы
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
			ui.expandedLable->setText(vEleMatr[0].code + " = ");
			ui.expandedLable->setVisible(true);
			ui.expandedTableView->setVisible(true);
			ui.expandedTableView->verticalHeader()->hide();
			ui.expandedTableView->horizontalHeader()->hide();
			//ui.expandedTableView->setFixedHeight(vEleMatr[0].childMatrix->rowCount() * 24 - vEleMatr[0].childMatrix->rowCount() + 2);
			//ui.expandedTableView->setFixedWidth(vEleMatr[0].childMatrix->columnCount() * 40 - vEleMatr[0].childMatrix->columnCount() + 2);
			ui.expandedTableView->setModel(fullTableAdd1);
			ui.expandedTableView->resizeColumnsToContents();
			ui.expandedTableView->resizeRowsToContents();

		}

		//инициализация таблицы реструктуризации
		if (vComplicated.size() > 0)
		{
			restTable->clear();
			restTable->setColumnCount(fullTable->columnCount());
			restTable->setRowCount(fullTable->rowCount());

			for (int i = 0; i < fullTable->rowCount(); ++i)
				for (int j = 0; j < fullTable->columnCount(); ++j)
				{
					restTable->setData(restTable->index(i, j), fullTable->index(i, j).data(Qt::DisplayRole).toString());
				}
			ui.optiTableView->verticalHeader()->hide();
			ui.optiTableView->horizontalHeader()->hide();
			ui.optiTableView->setModel(restTable);
			ui.optiLable->setText(vEleMatr[0].code + " = ");
		}
		ui.specTab->setTabEnabled(1, true);
		ui.specTab->setTabEnabled(2, true);
	}
	

