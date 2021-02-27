#include <ui_module_form.h> 
#include <IS> 
#include <cm>
#include <ilm>
#include <pm>
#include <QStandardItemModel>
#include <QBoxLayout>
#include <QLabel>


class MyModuleForm : public WorkWidget 
{
	Q_OBJECT 
public: 
	MyModuleForm(QWidget *parent = 0); 
	~MyModuleForm();
	void IS_WidgetActived();
	//void on_comboBox_currentIndexChanged(int index);
	void createSpecTables();
	//void deleteCreatedTables();
	//void createItemTables();
	bool DefaultArgument(QString code) const;
	//QWidget* createAltTable(QString e, std::vector<QString>, int k) const;
	//QWidget * createSeqTable(QString e, std::vector<QString> code, int k) const;
	//QWidget * createCycTable(QString e, std::vector<QString> code, int k) const;
	std::vector<QString> OutInfromationLinkCheck(QString code) const;
	std::vector<QString> InInfromationLinkCheck(QString code) const;
	QWidget * createTable(AFElement * element, std::vector<QString> code, int k) const;
	//void createFormS1();

	void restructFunc(QStandardItemModel * restTable);

protected: 
		Ui_Form ui;
private slots:
		void oneStep();
		void allSteps();
		void deleteCreatedTables();
		void createItemTables();
		
};

class SomeIS2Module : public IsModule 
{ 
public: 
	SomeIS2Module() {
	
	}; 
	
		~SomeIS2Module() {}; 
		void loadModule() {} 
		void showModuleWidget() 
		{			
				RegisterModuleWidget(new MyModuleForm());
		}

		ModuleInfo* setModuleInfo() 
		{
			ModuleInfo *mi = new ModuleInfo; 
			mi->description = "Restructurization module for MAIL"; 
			mi->version = 1.1; 
			mi->name = "Restructurization"; 
			return mi;
		}
		
};

class iterationColoring {
	
public:
	QString code;
	std::vector<QString> children;
	int startI = 0, startJ = 0, finishI = 0, finishJ = 0;
	QColor iterColor;

	QColor colorPicker() {
		QColor randomColor;
		int rgb[3];
		int i;
		for (i = 0; i<3; i++)
		{
			rgb[i] = rand() % 256;
		}
		return QColor(rgb[0],rgb[1],rgb[2], 40);
	}
};

class elementMatrix
{
public:
		QString	code;
		QStandardItemModel *childMatrix;
};

class elementRelations
{
public:
	QString code;
	std::vector<QString> relationsCodes;
	std::vector<QString> relatedElementsIn;
	std::vector<QString> relatedElementsOut;
	std::vector<QString> relatedElementsDefault;
	QString iterationCode;
};

class hLayout
{
public:
	QHBoxLayout *layout = new QHBoxLayout();
	int tableSize;
	int maxSize;
	int currSize;
	bool last;

	void setSize(int tableSize)
	{
		switch (tableSize)
		{
		case 2:	{ maxSize = 7; }
		case 3:{ maxSize = 5; }
		case 4:{ maxSize = 4; }
		case 5:{ maxSize = 3; }
		case 6:{ maxSize = 3; }
		case 7: { maxSize = 3; }
		case 8: { maxSize = 2; }
		case 9: { maxSize = 1; }
		default: { maxSize = 3; }
		}
	}
	void addItem()
	{
		currSize = currSize + 1;
	}
	
};

class IOArguments
{
public:
	bool defaultArgument = 0;
	std::vector<QString> Arguments;
};

class MyHeaderModel : public QAbstractItemModel
{
public:
	MyHeaderModel(QObject *parent = 0) : QAbstractItemModel(parent) {}
	int columnCount(const QModelIndex &parent = QModelIndex()) const { return 2; }
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const { return QVariant(); }
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const { return QModelIndex(); }
	QModelIndex parent(const QModelIndex &index) const { return QModelIndex(); }
	int rowCount(const QModelIndex &parent = QModelIndex()) const { return 0; }
};

class MyHeader : public QHeaderView
{
	Q_OBJECT
public:
	MyHeader(QHeaderView *header, QWidget *parent = 0) : QHeaderView(Qt::Horizontal, header), mainHeader(header)
	{
		setModel(new MyHeaderModel(this));
		// This example uses hardcoded groups, you can extend
		// this yourself to save the groups
		// Group 1 is 0-2 and Group 2 is 3-4
		resizeSection(0, getSectionSizes(0, 2));
		resizeSection(1, getSectionSizes(3, 4));
		connect(this, SIGNAL(sectionResized(int, int, int)), this, SLOT(updateSizes()));
		//connect(((QTableWidget *)(mainHeader->parentWidget()))->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateOffset()));
		setGeometry(0, 0, header->width(), header->height());
		updateOffset();
		mainHeader->installEventFilter(this);
	}
	public slots:
	void updateSizes()
	{
		setOffset(mainHeader->offset());
		mainHeader->resizeSection(2, mainHeader->sectionSize(2) + (sectionSize(0) - getSectionSizes(0, 2)));
		mainHeader->resizeSection(4, mainHeader->sectionSize(4) + (sectionSize(1) - getSectionSizes(3, 4)));
	}
	void updateOffset()
	{
		setOffset(mainHeader->offset());
	}
protected:
	bool eventFilter(QObject *o, QEvent *e)
	{
		if (o == mainHeader) {
			if (e->type() == QEvent::Resize) {
				setOffset(mainHeader->offset());
				setGeometry(0, 0, mainHeader->width(), mainHeader->height());
			}
			return false;
		}
		return QHeaderView::eventFilter(o, e);
	}
private:
	int getSectionSizes(int first, int second)
	{
		int size = 0;
		for (int a = first; a <= second; ++a)
			size += mainHeader->sectionSize(a);
		return size;
	}
	QHeaderView *mainHeader;

};

