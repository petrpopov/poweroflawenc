#include <QtGui>
#include <QPixmap>
#include <QCursor>

#include "mainform.h"
#include "imagebutton.h"
#include "imagelabel.h"
#include "texteditlist.h"
#include "textedit.h"
#include "iconlist.h"



MainForm::MainForm(QWidget *parent,Qt::WindowFlags fl) : QMainWindow(parent,fl)
{	
  	setMouseTracking(true);
	mLeftPressed = false;
	
	path += ".//images//";
	
	QPixmap mainPixmap(":/images/mainpix.png");
  	setMask(mainPixmap.mask());
   	resize(mainPixmap.width()+4, mainPixmap.height()+4);
	
	
	QLabel *central = new QLabel(this);
 	central->setMask(mainPixmap.mask());
 	central->setPixmap(mainPixmap);
	setCentralWidget(central);
	central->show();
	
	
	powerButton = new ImageButton(QString::fromAscii(":/images/power"), 10, 466, this);
	powerButton->setObjectName("powerButton");
	dataButton = new ImageButton(QString::fromAscii(":/images/database"),545, 504,this);
	dataButton->setObjectName("dataButton");
	dataButton->setStickBlink(true);
	journalButton = new ImageButton(QString::fromAscii(":/images/journal"),608,477,this);
	journalButton->setObjectName("journalButton");
	journalButton->setStickBlink(true);
	navButton = new ImageButton(QString::fromAscii(":/images/navigation"),639,468,this);
	navButton->setObjectName("navButton");
	navButton->setStickBlink(true);
	
	leftButton = new ImageButton(QString::fromAscii(":/images/left"),433,106,this);
	leftButton->setObjectName("leftButton");
	topleftButton = new ImageButton(QString::fromAscii(":/images/topleft"),433,81,this);
	topleftButton->setObjectName("topleftButton");
	rightButton = new ImageButton(QString::fromAscii(":/images/right"),651,109,this);
 	rightButton->setObjectName("rightButton");
	toprightButton = new ImageButton(QString::fromAscii(":/images/topright"),652,85,this);
 	toprightButton->setObjectName("toprightButton");
	
	panelsLabel = new QLabel(this);
	panelsLabel->setPixmap( QPixmap(":/images/panels.png") );
	panelsLabel->resize( panelsLabel->pixmap()->size() );
	panelsLabel->setMask( panelsLabel->pixmap()->mask() );
	panelsLabel->move(449, 75);
	
	glassLabel = new QLabel(this);
	glassLabel->setPixmap( QPixmap(":/images/hourglass.png") );
	glassLabel->resize( glassLabel->pixmap()->size() );
	glassLabel->move(510, 100);
	
 	loadNewsPage();
	hideNewsPage();
	
	loadNavigationPage();
	hideNavigationPage();
	
	loadDataPage();
	hideDataPage();
	
	loadJournalPage();
	hideJournalPage();
	
	loadMainPage();
// 	hideMainPage();
	
	statusTextEdit = new TextEdit(this);
	statusTextEdit->setGeometry(170,460,350,25);
	
	QFile file(".//data//status.txt");
	if(file.exists())
	{
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QString text = file.readAll();
			if( !text.isEmpty() )
			{
				statusList = text.split("\n");
			}
			file.close();
		}
	}
	
	connect( powerButton, SIGNAL( clicked() ), this, SLOT( close() ) );
	connect( powerButton, SIGNAL( clicked() ), this, SLOT( playButtonSoundPress() ) );
	connect( powerButton, SIGNAL( playSoundMove() ), this, SLOT( playButtonSoundMove() ) );
	
	connect( navButton, SIGNAL( clicked() ), this, SLOT(changePage()) );
	connect( dataButton, SIGNAL( clicked() ), this, SLOT(changePage()) );
	connect( journalButton, SIGNAL( clicked() ), this, SLOT(changePage()) );
	
	connect( topleftButton, SIGNAL( clicked() ), this, SLOT( arrowSlot() ) );
	connect( topleftButton, SIGNAL( clicked() ), this, SLOT( playButtonSoundPress() ) );
	connect( topleftButton, SIGNAL( playSoundMove() ), this, SLOT( playButtonSoundMove() ) );
	
	connect( toprightButton, SIGNAL( clicked() ), this, SLOT( arrowSlot() ) );
	connect( toprightButton, SIGNAL( clicked() ), this, SLOT( playButtonSoundPress() ) );
	connect( toprightButton, SIGNAL( playSoundMove() ), this, SLOT( playButtonSoundMove() ) );
	
	connect( leftButton, SIGNAL( clicked() ), this, SLOT( arrowSlot() ) );
	connect( leftButton, SIGNAL( clicked() ), this, SLOT( playButtonSoundPress() ) );
	connect( leftButton, SIGNAL( playSoundMove() ), this, SLOT( playButtonSoundMove() ) );
	
	connect( rightButton, SIGNAL( clicked() ), this, SLOT( arrowSlot() ) );
	connect( rightButton, SIGNAL( clicked() ), this, SLOT( playButtonSoundPress() ) );
	connect( rightButton, SIGNAL( playSoundMove() ), this, SLOT( playButtonSoundMove() ) );
	
	connect( rnavButton, SIGNAL( clicked() ), this, SLOT( changeMap() ));
	connect( lnavButton, SIGNAL( clicked() ), this, SLOT( changeMap() ));
	
	connect( rdButton, SIGNAL( clicked() ), this, SLOT( changeDataItem() ) );
	connect( rdButton, SIGNAL( clicked() ), this, SLOT( playButtonSoundPress() ) );
	connect( rdButton, SIGNAL( playSoundMove() ), this, SLOT( playButtonSoundMove() ) );
	
	connect( ldButton, SIGNAL( clicked() ), this, SLOT( changeDataItem() ) );
	connect( ldButton, SIGNAL( clicked() ), this, SLOT( playButtonSoundPress() ) );
	connect( ldButton, SIGNAL( playSoundMove() ), this, SLOT( playButtonSoundMove() ) );
	
	connect( rdtopButton, SIGNAL( clicked() ), this, SLOT( changeDataItem() ) );
	connect( rdtopButton, SIGNAL( playSoundMove() ), this, SLOT( playButtonSoundMove() ) );
	connect( rdtopButton, SIGNAL( clicked() ), this, SLOT( playButtonSoundPress() ) );
	
	connect( ldtopButton, SIGNAL( clicked() ), this, SLOT( changeDataItem() ) );
	connect( ldtopButton, SIGNAL( clicked() ), this, SLOT( playButtonSoundPress() ) );
	connect( ldtopButton, SIGNAL( playSoundMove() ), this, SLOT( playButtonSoundMove() ) );
	
	connect( forcesButton, SIGNAL( clicked() ), this, SLOT( showDataForces() ) );
	connect( peopleButton, SIGNAL( clicked() ), this, SLOT( showDataPeople() ) );
	connect( techButton, SIGNAL( clicked() ), this, SLOT( showDataTech() ) );
	connect( outfitButton, SIGNAL( clicked() ), this, SLOT( showDataOutfit() ) );
	
	QList<QPushButton *> allPButtons = this->findChildren<QPushButton *>();
	for(int i = 0; i < allPButtons.size(); i++)
	{
		connect(allPButtons[i],SIGNAL(statusTextBegin()), this, SLOT(showStatusText()));
		connect(allPButtons[i],SIGNAL(statusTextEnd()), this, SLOT(clearStatusText()));
	}
	
	//Context menu-----------------------------------------
	aboutAction = new QAction(tr("About Encyclopedia"),this);
	aboutAction->setIcon( QPixmap(":/images/about.png") );
	aboutQtAction = new QAction(tr("About Qt"), this);
	soundAction = new QAction(tr("Sound is: ON"),this);
	soundAction->setIcon( QPixmap(":/images/sound.png") );
	soundAction->setCheckable(true);
	
	this->addAction(soundAction);
	this->addAction(aboutAction);
	this->addAction(aboutQtAction);
	
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutSlot()));
	connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(soundAction, SIGNAL(triggered()), this, SLOT(switchSound()));
	setContextMenuPolicy(Qt::ActionsContextMenu);
	//-----------------------------------------------
	
	
	
	//Cursor and icon---------------------------------
	move(150, 150);
	setWindowTitle("Power of Law Encyclopedia");
	setWindowIcon( QPixmap(":/images/htpd.ico") );
	
	cursorPixmap = QPixmap(":/images/cursor.png");
	myCursor = QCursor(cursorPixmap, 0, 0);
	setCursor( myCursor );
	//----------------------------------------------------
	
	
	//Sound settings------------------------------------
	settings = new QSettings("ezheg", "Power of law Encyclopedia");

	int ss = settings->value("sound").toInt();
	if(ss == 1)
	{
		sound = true;
		soundAction->setText( tr("Sound is: ON") );
	}
	else
	{
		sound = false;
		soundAction->setText( tr("Sound is: OFF") );
	}
	soundAction->setChecked(sound);
	//====================================================================
	
	version = "0.9";
}



void MainForm::switchSound()
{
	if( soundAction->isChecked() )
	{
		sound = true;
		
		settings->setValue("sound", 1);
		soundAction->setText( tr("Sound is: ON") );
	}
	else
	{
		sound = false;
		
		settings->setValue("sound", 0);
		soundAction->setText( tr("Sound is: OFF") );
	}
}

void MainForm::arrowSlot()
{
	//Попробовать сделать один вариант навигационных кнопок
	//И использовать их во всех режимах - новости, бд, карты
	
	if(page == "news")
		changeNews();
}


//Pages slots-----------------------------------

void MainForm::changePage()
{
	//Показываем ту страницу, к которой привязана кнопка
	//Если страница уже показывается - грузим новости	
	
	QPushButton *button = (QPushButton *)sender();
	
	if(button->objectName() == "navButton")
	{
		if(page == "database")
		{
			dataButton->incPIndex();
			dataButton->changePixmap(0);
			showNavigationPage();
		}
		else if(page == "journal")
		{
			journalButton->incPIndex();
			journalButton->changePixmap(0);
			showNavigationPage();
		}
		else if(page == "main" || page == "news")
			showNavigationPage();
		else
			showNewsPage();
	}
	else if(button->objectName() == "dataButton")
	{
		if(page == "navigation")
		{
			navButton->incPIndex();
			navButton->changePixmap(0);
			showDataPage();
		}
		else if(page == "journal")
		{
			journalButton->incPIndex();
			journalButton->changePixmap(0);
			showDataPage();
		}
		else if(page == "main" || page == "news")
			showDataPage();
		else
			showNewsPage();
	}
	else if(button->objectName() == "journalButton")
	{
		if(page == "database")
		{
			dataButton->incPIndex();
			dataButton->changePixmap(0);
			showJournalPage();
		}
		else if(page == "navigation")
		{
			navButton->incPIndex();
			navButton->changePixmap(0);
			showJournalPage();
		}
		else if(page == "main" || page == "news")
			showJournalPage();
		else
			showNewsPage();
	}
}

void MainForm::hidePage()
{
	//Скрыть текущую страницу
	//Используется при показах страниц
	
	if(page == "main")
		hideMainPage();
	else if(page == "news")
		hideNewsPage();
	else if(page == "navigation")
		hideNavigationPage();
	else if(page == "database")
		hideDataPage();
	else if(page == "journal")
		hideJournalPage();
}

void MainForm::hideDataPage()
{
	dataLabel->hide();
	outfitButton->hide();
	techButton->hide();
	forcesButton->hide();
	peopleButton->hide();
	dbLabel->hide();
	dbPeopleLabel->hide();
	dbTechLabel->hide();
	dbArmorLabel->hide(); 
	dbTextEdit->hide(); 
	charTextLeft->hide();
	charTextRight->hide(); 
	dbHeader->hide(); 
	dbHeader->hide();
	dbType->hide(); 
	ldButton->hide(); 
	ldtopButton->hide(); 
	rdButton->hide(); 
	rdtopButton->hide();
	
	dataButton->changePixmap(0);
	
	page = "";
}

void MainForm::hideNavigationPage()
{
	//Скрытие страницы с картами уровней
	
	navLabel->hide();
	pLabel->hide();
	mapLabel->hide();
	rnavButton->hide();
	lnavButton->hide();
	mapHeader->hide();
	
	navButton->changePixmap(0);
	
	page = "";
}

void MainForm::hideNewsPage()
{
	//Скрытие сттаницы с нововостями
	
	newsLabel->hide();
	newsHeaderLabel->hide();
	newsText->hide();
	newsHeader->hide();
	
	leftButton->hide();
	topleftButton->hide();
	rightButton->hide();
	toprightButton->hide();
	
	page = "";
}

void MainForm::hideMainPage()
{
	//Скрытие страницы, которая показывается при запуске
	mLabel->hide();
	mTextList->hide();
	
	panelsLabel->show();
	glassLabel->hide();
	
	page = "";
}

void MainForm::showDataPage()
{
	hidePage();
	
	dataLabel->show();
	outfitButton->show();
	techButton->show();
	forcesButton->show();
	peopleButton->show();
	dbLabel->show();
	dbPeopleLabel->show();
	dbTechLabel->show();
	dbArmorLabel->show();
	dbTextEdit->show();
	charTextLeft->show();
	charTextRight->show();
	dbHeader->show();
	dbHeader->show();
	dbType->show();
	ldButton->show();
	ldtopButton->show();
	rdButton->show();
	rdtopButton->show();
	
	switch(outfitDepartIndex)
	{
		case 0:
			armorsShow();
			break;
		case 1:
			grenadesShow();
			break;
		case 2:
			ammunitionShow();
			break;
		case 3:
			weaponsShow();
			break;
		case 4:
			equipmentShow();
			break;
	}
	
	dataButton->changePixmap(2);
	
	page = "database";
	
	if(dataPage == "outfit")
		showDataOutfit();
	else if(dataPage == "people")
		showDataPeople();
	else if(dataPage == "tech")
		showDataTech();
	else if(dataPage == "forces")
		showDataForces();
}

void MainForm::showNewsPage()
{
	//Показаь новости
	hidePage();
	
	newsLabel->show();
	newsHeaderLabel->show();
	newsText->show();
	newsHeader->show();
	
	leftButton->show();
	topleftButton->show();
	rightButton->show();
	toprightButton->show();
	
	page = "news";
}

void MainForm::showMainPage()
{
	//Пусть будет на всякий случай
	hidePage();
	
	mLabel->show();
	mTextList->show();
	
	panelsLabel->hide();
	glassLabel->show();
	
	page = "main";
}

void MainForm::showNavigationPage()
{
	//Показать страницу с картами
	hidePage();
	
	navLabel->show();
	pLabel->show();
	mapLabel->show();
	rnavButton->show();
	lnavButton->show();
	mapHeader->show();
	
	navButton->changePixmap(2);
	
	page = "navigation";
}


void MainForm::changeDataItem()
{
	if(dataPage == "people")
		changePeople();
	else if(dataPage == "forces")
		changeForces();
	else if(dataPage == "tech")
		changeTech();
	else if(dataPage == "outfit")
		changeOutfit();
}

void MainForm::changeOutfit()
{
	QPushButton *button = (QPushButton *)sender();
 	QStringList t;
	
	if(button->objectName() == "ldtopButton")
	{
		if( outfitDepartIndex == 0 )
			outfitDepartIndex = outfitList.size() - 1;
		else
			--outfitDepartIndex;
		outfitIndex = 0;
	}
	else if(button->objectName() == "rdtopButton")
	{
		if(outfitDepartIndex == outfitList.size() - 1)
			outfitDepartIndex = 0;
		else
			++outfitDepartIndex;
		outfitIndex = 0;
	}
	else if(button->objectName() == "ldButton")
	{
		t = outfitList[outfitDepartIndex];
		if(outfitIndex == 0)
			outfitIndex = t.size() - 1;
		else
			--outfitIndex;	
	}
	else if(button->objectName() == "rdButton")
	{	
		t = outfitList[outfitDepartIndex];
		if(outfitIndex == t.size() - 1)
			outfitIndex = 0;
		else
			++outfitIndex;
	}
	
	switch(outfitDepartIndex)
	{
		case 0:
			armorsShow();
			break;
		case 1:
			grenadesShow();
			break;
		case 2:
			ammunitionShow();
			break;
		case 3:
			weaponsShow();
			break;
		case 4:
			equipmentShow();
			break;
	}
}

void MainForm::loadJournalPage()
{
	iconList = new IconList(path+"wallpapers//", this);
	
	QFile file(".//data//journal.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QString text = file.readAll();
	if( text.isEmpty() )
		return;
	file.close();
	
	iconText = new TextEdit(this);
	iconText->setGeometry(100, 110, 400, 50);
	iconText->setText( QString::fromLocal8Bit(text.toAscii().constData()) );
	
	page = "journal";
}

void MainForm::showJournalPage()
{
	hidePage();
	
	journalButton->changePixmap(2);
	iconList->show();
	iconList->setFocus(Qt::MouseFocusReason);
	iconText->show();
	
	panelsLabel->hide();
	glassLabel->show();
	
	page = "journal";
}

void MainForm::hideJournalPage()
{
	iconList->hide();
	iconText->hide();
	
	journalButton->changePixmap(0);
	
	panelsLabel->show();
	glassLabel->hide();
	
	page = "";
}

void MainForm::loadDataPage()
{
	dataLabel = new ImageLabel(path+"database//", 82, 41, this);
	outfitButton = new ImageButton(path+"database//buttons//"+
			QString::fromAscii("outfit"), 165, 50, this);
	outfitButton->setStickPress( true );
	outfitButton->setObjectName("outfitButton");
	
	techButton = new ImageButton(path+"database//buttons//"+
			QString::fromAscii("tech"), 287, 50, this);
	techButton->setStickPress( true );
	techButton->setObjectName("techButton");
	
	forcesButton = new ImageButton(path+"database//buttons//"+
			QString::fromAscii("forces"), 409, 50, this);
	forcesButton->setStickPress( true );
	forcesButton->setObjectName("forcesButton");
	
 	peopleButton = new ImageButton(path+"database//buttons//"+
 			QString::fromAscii("people"), 531, 50, this);
	peopleButton->setStickPress( true );
	peopleButton->setObjectName("peopleButton");
	
	
	dbLabel = new ImageLabel(path+"database//forces//", 159, 138, this);
	dbPeopleLabel = new ImageLabel(path+"database//people//", 159, 138, this);
	dbTechLabel = new ImageLabel(path+"database//tech//", 159, 138, this);
	dbArmorLabel = new ImageLabel(path+"database//armors//", 159, 138, this);
	
	dbTextEdit = new TextEditList(this);
	dbTextEdit->setGeometry(90, 320, 535, 120);
	
	charTextLeft = new TextEditList( this );
	charTextLeft->setGeometry(400,130,140,190);
#ifdef Q_OS_UNIX
 	charTextLeft->setCurrentFont(QFont("Sans Serif", 6));
#endif
	
#ifdef Q_OS_WIN
	charTextLeft->setCurrentFont(QFont("Sans Serif", 8));
#endif
	
	charTextRight = new TextEditList( this );
	charTextRight->setGeometry(550,130,100,190);
#ifdef Q_OS_UNIX
	charTextRight->setCurrentFont(QFont("Sans Serif", 6));
#endif
	
#ifdef Q_OS_WIN
	charTextRight->setCurrentFont(QFont("Sans Serif", 8));
#endif
	
	dbHeader = new TextEdit(this);
	dbHeader->setGeometry(450,80,190,21);
	
	dbType = new TextEdit(this);
	dbType->setGeometry(80,260,320,21);
	
	ldButton = new ImageButton(QString::fromAscii(":/images/left"),433,106,this);
	ldButton->setObjectName("ldButton");
	ldtopButton = new ImageButton(QString::fromAscii(":/images/topleft"),433,81,this);
	ldtopButton->setObjectName("ldtopButton");
	rdButton = new ImageButton(QString::fromAscii(":/images/right"),651,109,this);
	rdButton->setObjectName("rdButton");
	rdtopButton = new ImageButton(QString::fromAscii(":/images/topright"),652,85,this);
	rdtopButton->setObjectName("rdtopButton");
	
	loadDbForces();
	loadDbPeople();
	loadDbTech();
	loadDbOutfit();

 	showDataOutfit();
	
	page = "database";
}

void MainForm::loadDbOutfit()
{
	QFile file(".//data//db//armors.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QString text = file.readAll();
	if( text.isEmpty() )
		return;
	file.close();
	outfitList.append( text.split("\n") );
	
	
	file.setFileName(".//data//db//grenades.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	text = file.readAll();
	if( text.isEmpty() )
		return;
	file.close();
	outfitList.append( text.split("\n") );
	
	file.setFileName(".//data//db//ammunition.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	text = file.readAll();
	if( text.isEmpty() )
		return;
	file.close();
	outfitList.append( text.split("\n") );
	
	file.setFileName(".//data//db//weapons.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	text = file.readAll();
	if( text.isEmpty() )
		return;
	file.close();
	outfitList.append( text.split("\n") );
	
	file.setFileName(".//data//db//equipment.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	text = file.readAll();
	if( text.isEmpty() )
		return;
	file.close();
	outfitList.append( text.split("\n") );
	
	
	
	file.setFileName(".//data//db//armors_descr.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	armorsTextLeft = file.readAll();
	if( armorsTextLeft.isEmpty() )
		return;
	file.close();
	
	file.setFileName(".//data//db//grenades_descr.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	grenadesTextLeft = file.readAll();
	if( grenadesTextLeft.isEmpty() )
		return;
	file.close();
	
	file.setFileName(".//data//db//ammunition_descr.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	ammunitionTextLeft = file.readAll();
	if( ammunitionTextLeft.isEmpty() )
		return;
	file.close();
	
	file.setFileName(".//data//db//weapons_descr.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	weaponsTextLeft = file.readAll();
	if( weaponsTextLeft.isEmpty() )
		return;
	file.close();
	
	file.setFileName(".//data//db//equipment_descr.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	equipmentText = file.readAll();
	if( equipmentText.isEmpty() )
		return;
	file.close();
	
	equipmentTextList = equipmentText.split("*");
	
	outfitDepartIndex = 4;
	outfitIndex = 0;
}

void MainForm::showDataOutfit()
{
	if(dataPage == "outfit")
		return;
	else if(dataPage == "people")
	{
		peopleButton->changePixmap(0);
		peopleButton->incPressIndex();
	}
	else if(dataPage == "forces")
	{
		forcesButton->changePixmap(0);
		forcesButton->incPressIndex();
	}
	else if(dataPage == "tech")
	{
		techButton->changePixmap(0);
		techButton->incPressIndex();
	}
	
	QStringList t = outfitList[outfitDepartIndex];
	QStringList n = t[outfitIndex].split("\t");
	
	
	switch(outfitDepartIndex)
	{
		case 0:
			armorsShow();
			break;
		case 1:
			grenadesShow();
			break;
		case 2:
			ammunitionShow();
			break;
		case 3:
			weaponsShow();
			break;
		case 4:
			equipmentShow();
			break;
	}
	
// 	dbArmorLabel->show();
// 	dbArmorLabel->changePixmap( n[0].trimmed() );
		
	dbTechLabel->hide();
	dbPeopleLabel->hide();
	dbLabel->hide();
		
	
	outfitButton->changePixmap(1);
	dataPage = "outfit";
}

void MainForm::equipmentShow()
{
	QStringList t = outfitList[outfitDepartIndex];
	QStringList n = t[outfitIndex].split("\t");
	
	dbArmorLabel->show();
	dbArmorLabel->changePixmap( n[0].trimmed() );
	
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	
	dbHeader->append( QString::fromLocal8Bit( n[ n.size()-1 ].toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[10].toAscii().constData() ) );
	
	QString type = n[2];
	int t1 = n[2].toInt();
	
	charTextLeft->clear();
	charTextLeft->setAlignment( Qt::AlignRight );
	
	charTextLeft->append( QString::fromLocal8Bit( equipmentTextList[t1].trimmed().toAscii().constData() ) );
	
	QString textRight;
	textRight = n[3] + "\n";
	
	switch(t1)
	{
		case 0:
			textRight += n[4] + "\n";
			textRight += n[7] + "\n";
			textRight += n[6] + "\n";
			textRight += n[5] + "\n";
			break;
		case 1:
			textRight += n[4] + "\n";
			textRight += n[8] + "\n";
			textRight += n[5] + "\n";
			break;
		case 2:
			textRight += n[4] + "\n";
			textRight += n[8] + "\n";
			textRight += n[5] + "\n";
			break;
		case 3:
			textRight += n[4] + "\n";
			textRight += n[8] + "\n";
			textRight += n[5] + "\n";
			break;
		case 4:
			textRight += n[6] + "\n";
			textRight += n[5] + "\n";
			textRight += n[9] + "\n";
			break;
	}
	
	charTextRight->clear();
	charTextRight->setAlignment( Qt::AlignLeft );
 	charTextRight->append( QString::fromLocal8Bit( textRight.toAscii().constData() ));
}

void MainForm::weaponsShow()
{
	QStringList t = outfitList[outfitDepartIndex];
	QStringList n = t[outfitIndex].split("\t");
	
	dbArmorLabel->show();
	dbArmorLabel->changePixmap( n[0].trimmed() );
	
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	
	dbHeader->clear();
	QStringList a = t[0].split("\t");
	dbHeader->append( QString::fromLocal8Bit( a[ a.size()-1 ].toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[31].toAscii().constData() ) );
	
	QString textRight;
	textRight = n[5] + "\n";
 	textRight += n[6] + "\n";
 	textRight += n[7] + "\n";
 	textRight += n[8] + "\n";
 	textRight += n[18] + "\n";
 	textRight += n[19] + "\n";
 	textRight += n[13] + " " + n[15] + "\n";
 	textRight += n[14] + " " + n[16] + "\n";
 	textRight += n[9] + "/" + n[9] + "/";
 	QString s = n[10];
 	if(s.toInt() == 1)
 		s = "-";
 	textRight += s + "\n";
 	textRight += n[11] + "/" + n[34] + "/" + n[35] + "\n";
 	textRight += n[12] + "\n";
	textRight += n[36];
	
	
	charTextLeft->clear();
	charTextLeft->setAlignment( Qt::AlignRight );
	charTextLeft->append( QString::fromLocal8Bit( weaponsTextLeft.toAscii().constData() ));
	
	charTextRight->clear();
	charTextRight->setAlignment( Qt::AlignLeft );
	charTextRight->append( QString::fromLocal8Bit( textRight.toAscii().constData() ));
}

void MainForm::ammunitionShow()
{
	QStringList t = outfitList[outfitDepartIndex];
	QStringList n = t[outfitIndex].split("\t");
	
	dbArmorLabel->show();
	dbArmorLabel->changePixmap( n[0].trimmed() );
	
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	
	dbHeader->clear();
 	QStringList a = t[0].split("\t");
 	dbHeader->append( QString::fromLocal8Bit( a[ a.size()-1 ].toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[22].toAscii().constData() ) );
	
	QString textRight;
	textRight += n[3] + "\n";
	textRight += n[10] + "\n";
	textRight += n[12] + "\n";
	textRight += n[5] + " " + n[7] + "\n";
	textRight += n[6] + " " + n[8] + "\n";
	textRight += n[11];
	
	charTextLeft->clear();
	charTextLeft->setAlignment( Qt::AlignRight );
	charTextLeft->append( QString::fromLocal8Bit( ammunitionTextLeft.toAscii().constData() ));
	
	charTextRight->clear();
	charTextRight->setAlignment( Qt::AlignLeft );
	charTextRight->append( QString::fromLocal8Bit( textRight.toAscii().constData() ));
}

void MainForm::grenadesShow()
{
	QStringList t = outfitList[outfitDepartIndex];
	QStringList n = t[outfitIndex].split("\t");
	
	dbArmorLabel->show();
	dbArmorLabel->changePixmap( n[0].trimmed() );
	
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	

	dbHeader->clear();
  	dbHeader->append( QString::fromLocal8Bit( n[10].toAscii().constData() ) );
 	dbHeader->setAlignment( Qt::AlignCenter );

 	dbTextEdit->clear();
 	dbTextEdit->setText( QString::fromLocal8Bit( n[8].toAscii().constData() ) );
	
	QString textRight;
	textRight += n[2] + "\n";
	textRight += n[3] + "\n";
	textRight += n[4] + "\n";
	textRight += n[5] + "\n";
	textRight += n[6] + "\n";
	textRight += n[7] + "\n";
	textRight += n[9];
	
	charTextLeft->clear();
	charTextLeft->setAlignment( Qt::AlignRight );
	charTextLeft->append( QString::fromLocal8Bit( grenadesTextLeft.toAscii().constData() ));
	
	charTextRight->clear();
	charTextRight->setAlignment( Qt::AlignLeft );
	charTextRight->append( QString::fromLocal8Bit( textRight.toAscii().constData() ));
}

void MainForm::armorsShow()
{
	QStringList t = outfitList[outfitDepartIndex];
	QStringList n = t[outfitIndex].split("\t");
	
	dbArmorLabel->show();
	dbArmorLabel->changePixmap( n[0].trimmed() );
	
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	
	dbHeader->clear();
	dbHeader->append( QString::fromLocal8Bit( n[13].toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[11].toAscii().constData() ) );
	
	QString textRight;
	textRight += n[3] + "\n";
	textRight += n[5] + "\n";
	textRight += n[6] + "\n";
	textRight += n[7] + "\n";
	textRight += n[9] + "\n";
	textRight += n[8] + "\n";
	textRight += n[2] + "\n";
	textRight += n[10] + "\n";
	textRight += n[12];
	
	charTextLeft->clear();
	charTextLeft->setAlignment( Qt::AlignRight );
	charTextLeft->append( QString::fromLocal8Bit( armorsTextLeft.toAscii().constData() ));
	
	charTextRight->clear();
	charTextRight->setAlignment( Qt::AlignLeft );
	charTextRight->append( QString::fromLocal8Bit( textRight.toAscii().constData() ));	
}

void MainForm::loadDbTech()
{
	QFile file(".//data//db//tech.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QString text = file.readAll();
	if( text.isEmpty() )
		return;
	file.close();
	
	file.setFileName(".//data//db//tech_descr.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	techTextLeft = file.readAll();
	if( techTextLeft.isEmpty() )
		return;
	file.close();
	
	
	techList = text.split("\n");
	
	QStringList depart;
	for(int i = 0; i < techList.size(); i++)
	{
		QStringList t = techList[i].split("\t");
  		if( t.size() < 24 )
  			break;
		
		if( depart.size() == 0)
			depart << t[2].trimmed();
		else{
			if( !depart.contains( t[2].trimmed() ) )
				if( !t[2].isEmpty() )
					depart << t[2].trimmed();
		}
	}
	
	for(int i = 0; i < depart.size(); i++)
		tList << "";
	
	for(int i = 0; i < techList.size(); i++)
	{
		for(int j = 0; j < depart.size(); j++)
		{
			if( techList[i].contains( depart[j] ) )
			{
				QString s = tList[j];
				s += techList[i] += "\n";
				tList[j] = s;
			}
		}
	}
	for(int i = 0; i < tList.size(); i++)
	{
		QString s = tList[i].trimmed();
		tList[i] = s;
	}

	techDepartSize = depart.size();
	techDepartIndex = 0;
	techIndex = 0;
}

void MainForm::changeTech()
{
	QPushButton *button = (QPushButton *)sender();
	QStringList t;
	
	if(button->objectName() == "ldtopButton")
	{
		if(techDepartIndex == 0)
			techDepartIndex = techDepartSize - 1;	
		else
			--techDepartIndex;
		techIndex = 0;
	}
	else if(button->objectName() == "rdtopButton")
	{
		if(techDepartIndex == techDepartSize - 1)
			techDepartIndex = 0;
		else
			++techDepartIndex;
		techIndex = 0;
	}
	else if(button->objectName() == "ldButton")
	{
		t = tList[techDepartIndex].split("\n");
		if(techIndex == 0)
			techIndex = t.size() - 1;
		else
			--techIndex;
	}
	else if(button->objectName() == "rdButton")
	{
		t = tList[techDepartIndex].split("\n");
		if(techIndex == t.size() - 1)
			techIndex = 0;
		else
			++techIndex;
	}
	
	t = tList[techDepartIndex].split("\n");
	QStringList n = t[techIndex].split("\t");
	
	dbTechLabel->changePixmap( n[0].trimmed() );
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	
	dbHeader->clear();
	dbHeader->append( QString::fromLocal8Bit( n[2].toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[23].toAscii().constData() ) );
	dbTextEdit->verticalScrollBar()->setValue(dbTextEdit->verticalScrollBar()->minimum());
	
	QString textRight;
	textRight = n[17] + "\n";
	textRight += n[19] + "\n";
	textRight += n[18] + "\n";
	textRight += n[20] + "\n";
	textRight += n[6] + "\n";
	textRight += n[12] + "\n";
	textRight += n[13] + "\n";
	textRight += n[3] + "\n";
	textRight += n[4] + "\n";
	textRight += n[5] + "\n";
	textRight += n[21] + "\n";
	textRight += n[22];
	
	charTextLeft->clear();
	charTextLeft->setAlignment( Qt::AlignRight );
	charTextLeft->append( QString::fromLocal8Bit( techTextLeft.toAscii().constData() ));
	
	charTextRight->clear();
	charTextRight->setAlignment( Qt::AlignLeft );
	charTextRight->append( QString::fromLocal8Bit( textRight.toAscii().constData() ));
}

void MainForm::changePeople()
{
	QPushButton *button = (QPushButton *)sender();
	QStringList t;
	
	if(button->objectName() == "ldtopButton")
	{
		if(peopleDepartIndex == 0)
			peopleDepartIndex = peopleDepartSize - 1;	
		else
			--peopleDepartIndex;
		peopleIndex = 0;
	}
	else if(button->objectName() == "rdtopButton")
	{
		if(peopleDepartIndex == peopleDepartSize - 1)
			peopleDepartIndex = 0;
		else
			++peopleDepartIndex;
		peopleIndex = 0;
	}
	else if(button->objectName() == "ldButton")
	{
		t = pList[peopleDepartIndex].split("\n");
		if(peopleIndex == 0)
			peopleIndex = t.size() - 1;
		else
			--peopleIndex;
	}
	else if(button->objectName() == "rdButton")
	{
		t = pList[peopleDepartIndex].split("\n");
		if(peopleIndex == t.size() - 1)
			peopleIndex = 0;
		else
			++peopleIndex;
	}
	
	t = pList[peopleDepartIndex].split("\n");
	QStringList n = t[peopleIndex].split("\t");
	
	dbPeopleLabel->changePixmap( n[0].trimmed() );
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	
	dbHeader->clear();
	QString a = n[14];
	for(int i = 0; i < peopleTr.size(); i++)
	{
		if( peopleTr[i].contains(a) )
		{
			QStringList aa= peopleTr[i].split("\t");
			a = aa[1];
		}
	}
	dbHeader->append( QString::fromLocal8Bit( a.toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[15].toAscii().constData() ) );
	dbTextEdit->verticalScrollBar()->setValue(dbTextEdit->verticalScrollBar()->minimum());
	
			
	QString textRight;
	textRight = n[9] + "\n";
	textRight += n[3] + "\n";
	textRight += n[7] + "\n";
	textRight += n[5] + "\n";
	textRight += n[4] + "\n";
	textRight += n[13];
	
	charTextLeft->clear();
	charTextLeft->setAlignment( Qt::AlignRight );
	charTextLeft->append( QString::fromLocal8Bit( peopleTextLeft.toAscii().constData() ));
	
	charTextRight->clear();
	charTextRight->setAlignment( Qt::AlignLeft );
	charTextRight->append( QString::fromLocal8Bit( textRight.toAscii().constData() ));
}


void MainForm::loadDbPeople()
{
	QFile file(".//data//db//people.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QString text = file.readAll();
	if( text.isEmpty() )
		return;
	file.close();
	
	
 	file.setFileName(".//data//db//people_descr.txt");
 	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
 		return;
 	peopleTextLeft = file.readAll();
 	if( peopleTextLeft.isEmpty() )
 		return;
 	file.close();
	
	file.setFileName(".//data//db//people_trans.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QString a = file.readAll();
	if(!a.isEmpty())
		peopleTr = a.split("\n");
	
	
	peopleList = text.split("\n");
	
	QStringList depart;
	for(int i = 0; i < peopleList.size(); i++)
	{
		QStringList t = peopleList[i].split("\t");
//  		printf("%s\n", t[14].toAscii().constData());
		if( t.size() < 14 )
			break;
		
		if( depart.size() == 0)
			depart << t[14].trimmed();
		else{
			if( !depart.contains( t[14].trimmed() ) )
				if( !t[14].isEmpty() )
					depart << t[14].trimmed();
		}
	}
	
	for(int i = 0; i < depart.size(); i++)
		pList << "";
	
	for(int i = 0; i < peopleList.size(); i++)
	{
		for(int j = 0; j < depart.size(); j++)
		{
			if( peopleList[i].contains( depart[j] ) )
			{
				QString s = pList[j];
				s += peopleList[i] += "\n";
				pList[j] = s;
			}
		}
	}
	for(int i = 0; i < pList.size(); i++)
	{
		QString s = pList[i].trimmed();
		pList[i] = s;
	}
	
	peopleDepartSize = depart.size();
	peopleDepartIndex = 0;
	peopleIndex = 0;
}

void MainForm::showDataTech()
{
	if(dataPage == "tech")
		return;
	else if(dataPage == "people")
	{
		peopleButton->changePixmap(0);
		peopleButton->incPressIndex();
	}
	else if(dataPage == "forces")
	{
		forcesButton->changePixmap(0);
		forcesButton->incPressIndex();
	}
	else if(dataPage == "outfit")
	{
		outfitButton->changePixmap(0);
		outfitButton->incPressIndex();
	}
	
	dbTechLabel->show();
	dbPeopleLabel->hide();
	dbLabel->hide();
	dbArmorLabel->hide();
	
	
	
	QStringList t = tList[techDepartIndex].split("\n");
	QStringList n = t[techIndex].split("\t");
	
	dbTechLabel->changePixmap( n[0].trimmed() );
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	
	dbHeader->clear();
	dbHeader->append( QString::fromLocal8Bit( n[2].toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[23].toAscii().constData() ) );
	dbTextEdit->verticalScrollBar()->setValue(dbTextEdit->verticalScrollBar()->minimum());
	
	QString textRight;
	textRight = n[17] + "\n";
	textRight += n[19] + "\n";
	textRight += n[18] + "\n";
	textRight += n[20] + "\n";
	textRight += n[6] + "\n";
	textRight += n[12] + "\n";
	textRight += n[13] + "\n";
	textRight += n[3] + "\n";
	textRight += n[4] + "\n";
	textRight += n[5] + "\n";
	textRight += n[21] + "\n";
	textRight += n[22];
	
	charTextLeft->clear();
	charTextLeft->setAlignment( Qt::AlignRight );
	charTextLeft->append( QString::fromLocal8Bit( techTextLeft.toAscii().constData() ));
	
	charTextRight->clear();
	charTextRight->setAlignment( Qt::AlignLeft );
	charTextRight->append( QString::fromLocal8Bit( textRight.toAscii().constData() ));
	
	techButton->changePixmap(1);
	dataPage = "tech";
}

void MainForm::showDataPeople()
{
	if(dataPage == "people")
		return;
	else if(dataPage == "forces")
	{
		forcesButton->changePixmap(0);
		forcesButton->incPressIndex();
	}
	else if(dataPage == "tech")
	{
		techButton->changePixmap(0);
		techButton->incPressIndex();
	}
	else if(dataPage == "outfit")
	{
		outfitButton->changePixmap(0);
		outfitButton->incPressIndex();
	}
	
	dbPeopleLabel->show();
	dbLabel->hide();
	dbTechLabel->hide();
	dbArmorLabel->hide();
	
	QStringList t = pList[peopleDepartIndex].split("\n");
	QStringList n = t[peopleIndex].split("\t");
	
	dbPeopleLabel->changePixmap( n[0].trimmed() );
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	
	dbHeader->clear();
	QString a = n[14];
	for(int i = 0; i < peopleTr.size(); i++)
	{
		if( peopleTr[i].contains(a) )
		{
			QStringList aa= peopleTr[i].split("\t");
			a = aa[1];
		}
	}
	dbHeader->append( QString::fromLocal8Bit( a.toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[15].toAscii().constData() ) );
	dbTextEdit->verticalScrollBar()->setValue(dbTextEdit->verticalScrollBar()->minimum());
	
			
	QString textRight;
	textRight = n[9] + "\n";
	textRight += n[3] + "\n";
	textRight += n[7] + "\n";
	textRight += n[5] + "\n";
	textRight += n[4] + "\n";
	textRight += n[13];
	
	charTextLeft->clear();
	charTextLeft->setAlignment( Qt::AlignRight );
	charTextLeft->append( QString::fromLocal8Bit( peopleTextLeft.toAscii().constData() ));
	
	charTextRight->clear();
	charTextRight->setAlignment( Qt::AlignLeft );
	charTextRight->append( QString::fromLocal8Bit( textRight.toAscii().constData() ));
	
	peopleButton->changePixmap(1);
	dataPage = "people";
}

void MainForm::showDataForces()
{
	if(dataPage == "forces")
		return;
	else if(dataPage == "people")
	{
		peopleButton->changePixmap(0);
		peopleButton->incPressIndex();
	}
	else if(dataPage == "tech")
	{
		techButton->changePixmap(0);
		techButton->incPressIndex();
	}
	else if(dataPage == "outfit")
	{
		outfitButton->changePixmap(0);
		outfitButton->incPressIndex();
	}
	
	dbLabel->show();
	dbPeopleLabel->hide();
	dbTechLabel->hide();
	dbArmorLabel->hide();
	
	charTextRight->clear();
	charTextLeft->clear();
	
	QStringList t = fList[forcesDepartIndex].split("\n");
	QStringList n = t[forcesIndex].split("\t");
	
	
	if( !dbLabel->changePixmap( n[0].trimmed() ) )
		dbLabel->changePixmap(4);
	
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	dbHeader->clear();
	dbHeader->append( QString::fromLocal8Bit( n[2].toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[3].toAscii().constData() ) );
	dbTextEdit->verticalScrollBar()->setValue(dbTextEdit->verticalScrollBar()->minimum());
	
	forcesButton->changePixmap(1);
	dataPage = "forces";
}

void MainForm::loadMainPage()
{
	//Создать главную страницу
	mLabel = new ImageLabel(path+"main//",255,140, this);
	mTextList = new TextEditList( this );
	
	page = "main";
	
	QFile file(".//data//main.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QString text = file.readAll();
	file.close();
	
	if( text.isEmpty() )
		return;
	
	mTextList->append( QString::fromLocal8Bit( text.toAscii().constData() ) );
	
	panelsLabel->hide();
	glassLabel->show();
}

void MainForm::loadNewsPage()
{
	//Создать страницу с новостями
	newsLabel = new ImageLabel(path+"news//", 305,140, this);
	newsHeaderLabel = new ImageLabel(path+"news//header//", 495,50, this);
	newsText = new TextEditList( this );
	newsHeader = new TextEdit(this);
	
	loadNews();
	
	page = "news";
}

void MainForm::loadNavigationPage()
{
	//Создать страницу с картами
 	navLabel = new ImageLabel(path+"navigation//", 128, 2, this);
	pLabel = new ImageLabel(path+"navigation//patch//", 440, 105, this);
	mapLabel = new ImageLabel(path+"navigation//maps//", 130, 118, this);
	
	rnavButton = new ImageButton(QString::fromAscii(":/images/ntopright"),652,87,this);
	rnavButton->setObjectName("rnavButton");
	lnavButton = new ImageButton(QString::fromAscii(":/images/topleft"),433,81,this);
	lnavButton->setObjectName("lnavButton");
	mapHeader = new TextEdit( this );
	mapHeader->setGeometry(450,80,200,22);
	
	mapHeader->append("Map name");
	
	page = "navigation";
	
	loadMaps();
}

//End of Pages slots-----------------------------------

void MainForm::changeForces()
{
	QPushButton *button = (QPushButton *)sender();
	QStringList t;
	
	if(button->objectName() == "ldtopButton")
	{
		if(forcesDepartIndex == 0)
			forcesDepartIndex = forcesDepartSize - 1;	
		else
			--forcesDepartIndex;
		forcesIndex = 0;
	}
	else if(button->objectName() == "rdtopButton")
	{
		if(forcesDepartIndex == forcesDepartSize - 1)
			forcesDepartIndex = 0;
		else
			++forcesDepartIndex;
		forcesIndex = 0;
	}
	else if(button->objectName() == "ldButton")
	{
		t = fList[forcesDepartIndex].split("\n");
		if(forcesIndex == 0)
			forcesIndex = t.size() - 1;
		else
			--forcesIndex;
	}
	else if(button->objectName() == "rdButton")
	{
		t = fList[forcesDepartIndex].split("\n");
		if(forcesIndex == t.size() - 1)
			forcesIndex = 0;
		else
			++forcesIndex;
	}
	
	t = fList[forcesDepartIndex].split("\n");
	QStringList n = t[forcesIndex].split("\t");
	
	if( !dbLabel->changePixmap( n[0].trimmed() ) )
		dbLabel->changePixmap(4);
	
	dbType->clear();
	dbType->append( QString::fromLocal8Bit( n[1].toAscii().constData() ) );
	dbType->setAlignment( Qt::AlignCenter );
	dbHeader->clear();
	dbHeader->append( QString::fromLocal8Bit( n[2].toAscii().constData() ) );
	dbHeader->setAlignment( Qt::AlignCenter );
	dbTextEdit->clear();
	dbTextEdit->setText( QString::fromLocal8Bit( n[3].toAscii().constData() ) );
	dbTextEdit->verticalScrollBar()->setValue(dbTextEdit->verticalScrollBar()->minimum());
}

void MainForm::changeMap()
{
	//Показываем следующю или предыдущую карту, при нажатии стрелки
	
	//Изменяем индекс картинки
	//Индекс картинки берется не из файла со списком карт
	//а из списка файлов-картинок, построенного при загрузки
	//компонента mapLabel
	QPushButton *button = (QPushButton *)sender();
	
	if(button->objectName() == "rnavButton")
	{
		if(mapIndex == mapList.size() - 1)
			mapIndex = 0;
		else
			++mapIndex;
	}
	else if(button->objectName() == "lnavButton")
	{
		if(mapIndex == 0)
			mapIndex = mapList.size() - 1;
		else
			--mapIndex;
	}
	//Ставим картинку с новым индексом
	mapLabel->changePixmap(mapIndex);
	
	//Определяем текст картинки по названию файла
	QStringList t;
	
	for(int i = 0; i < mapList.size(); i++)
	{
		if( mapList[i].contains( mapLabel->pixmap() ) )
		{
			t = mapList[i].split("\t");
			mapHeader->clear();
			mapHeader->append( QString::fromLocal8Bit(t[1].toAscii().constData()) );
			break;
		}
	}
	
	
	//Увеличиваем размер, если текст не влезает
	QString s = QString::fromLocal8Bit( t[1].toAscii().constData() );
	
	if(s.length() > 25)
	{
		mapHeader->setGeometry(406,80,250,22);
		lnavButton->move(392, 83);
		mapHeader->setAlignment( Qt::AlignLeft );
	}
	else
	{
		mapHeader->setGeometry(450,80,200,22);
		lnavButton->move(433, 83);
		mapHeader->setAlignment( Qt::AlignCenter );
	}
}

void MainForm::changeNews()
{
	//Меняем новости при нажатии на стрелки(верхние и нижние)
	
	QPushButton *button = (QPushButton *)sender();
	
	QStringList t;
	
	if(button->objectName() == "topleftButton")
	{
		if(newsDepartIndex == 0)
			newsDepartIndex = newsDepartSize - 1;
		else
			--newsDepartIndex;
		newsSubdepartIndex = 0;
	}
	else if(button->objectName() == "toprightButton")
	{
		if(newsDepartIndex == newsDepartSize - 1)
			newsDepartIndex = 0;
		else
			++newsDepartIndex;
		newsSubdepartIndex = 0;	
	}
	else if(button->objectName() == "leftButton")
	{
		t = nList[newsDepartIndex].split("\n");
		if(newsSubdepartIndex == 0)
			newsSubdepartIndex = t.size() - 1;
		else
			--newsSubdepartIndex;
	}
	else if(button->objectName() == "rightButton")
	{
		t = nList[newsDepartIndex].split("\n");
		if(newsSubdepartIndex == t.size() - 1)
			newsSubdepartIndex = 0;
		else
			++newsSubdepartIndex;
	}
	
	t = nList[newsDepartIndex].split("\n");
	QStringList n = t[newsSubdepartIndex].split("\t");
	
	newsLabel->changePixmap( n[2].trimmed() );
	
	newsText->clear();
// 	newsText->setOwnStyle();
	
	newsText->append( QString::fromLocal8Bit( n[0].toAscii().constData() ) );
	newsText->setAlignment( Qt::AlignCenter );
	newsText->verticalScrollBar()->setValue(newsText->verticalScrollBar()->minimum());
 	
	newsHeader->clear();
	newsHeader->setText( n[1] );
	newsHeader->setAlignment( Qt::AlignCenter );
}

void MainForm::loadDbForces()
{
	QFile file(".//data//db//forces.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QString text = file.readAll();
	if( text.isEmpty() )
		return;
	file.close();
	
	forcesList = text.split("\n");
	
	QStringList depart;
	for(int i = 0; i < forcesList.size(); i++)
	{
		QStringList t = forcesList[i].split("\t");
		if( t.size() < 4 )
			break;
		
		if( depart.size() == 0)
			depart << t[2].trimmed();
		else{
			if( !depart.contains( t[2].trimmed() ) )
				if( !t[2].isEmpty() )
					depart << t[2].trimmed();
		}
	}
	
	
	for(int i = 0; i < depart.size(); i++)
		fList << "";
	
	for(int i = 0; i < forcesList.size(); i++)
	{
		for(int j = 0; j < depart.size(); j++)
		{
			if( forcesList[i].contains( depart[j] ) )
			{
				QString s = fList[j];
				s += forcesList[i] += "\n";
				fList[j] = s;
			}
		}
	}
	
	for(int i = 0; i < fList.size(); i++)
	{
		QString s = fList[i].trimmed();
		fList[i] = s;
	}
	
	forcesDepartSize = depart.size();
	forcesDepartIndex = 0;
	forcesIndex = 0;
	
// 	QStringList a = forcesList[0].split("\t");
// 	dbType->append( QString::fromLocal8Bit( a[1].toAscii().constData() ) );
// 	dbHeader->append( QString::fromLocal8Bit( a[2].toAscii().constData() ) );
//   	dbTextEdit->setText( QString::fromLocal8Bit( a[3].toAscii().constData() ) );
// 	
// 	if( !dbLabel->changePixmap( a[0].trimmed() ) )
// 		dbLabel->changePixmap(4);
}

void MainForm::loadMaps()
{
// 	Грузим список карт из файла
	
	QFile file(".//data//maps.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QString text = file.readAll();
	file.close();
	
	if( text.isEmpty() )
		return;
	
	mapList = text.split("\n");
	mapIndex = 0;
	
	QStringList t = mapList[0].split("\t");
	mapHeader->clear();
	mapHeader->append( QString::fromLocal8Bit(t[1].toAscii().constData()) );
	mapHeader->setAlignment( Qt::AlignCenter );
}

void MainForm::loadNews()
{
// 	Грузим новости из файла. Код очень блядский, я уже и сам плохо понимаю
	
	//Читаем файл
	QFile file(".//data//news.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QString text = file.readAll();
	file.close();
	
	if( text.isEmpty() )
		return;
	
	newsList = text.split("\n");
	
	//грузим 5ю новость
	QStringList news = newsList[4].split("\t");
	newsLabel->changePixmap( news[2].trimmed() );	
	newsHeader->append( news[1] );
	newsText->append( QString::fromLocal8Bit(news[0].toAscii().constData()) );
	
	
	//Определяем что групп новостей - 3, а подгрупп - 7
	//На всякий случай, вдруг файл изменится	
 	QStringList str1; //список групп новостей
 	QStringList str2; //список подгрупп - списка имен файлов для картинок новостей
 	for(int i = 0; i < newsList.size(); i++)
 	{
 		QStringList sm = newsList[i].split("\t");
		if(sm.size() < 3)
			break;
		
 		if(str1.size() == 0)
 			str1 << sm[1].trimmed();
 		else
 		{
			if( !str1.contains(sm[1].trimmed()) )
				if( !sm[1].isEmpty() )
    					str1 << sm[1].trimmed();
 		}
 		
 		if(str2.size() == 0)
 			str2 << sm[2].trimmed();
 		else
 		{
 			if( !str2.contains(sm[2].trimmed()) )
				if( !sm[2].isEmpty() )
 					str2 << sm[2].trimmed();
 		}
 	}
 	newsDepartSize = str1.size();
 	newsSubdepartSize = str2.size();
	
	//Грузим эти долбанные говноновости в другой list
	//из которого потом и будем грузить-менять новости
	for(int i = 0; i < newsDepartSize; i++)
		nList << "";
	
	for(int i = 0; i < newsList.size(); i++)
	{
		for(int j = 0; j < str1.size(); j++)
		{
			if( newsList[i].contains( str1[j] ) )
			{
				QString s = nList[j];
				s += newsList[i] += "\n";
				nList[j] = s;
			}
		}
	}
	
	//Убираем эти гребанные пробелы в конце каждой группы новостей, иначе 
	//новостей будет "показываться" на одну больше с вылетом за границу массива
	
	for(int i = 0; i < nList.size(); i++)
	{
		QString a = nList[i].trimmed();
		nList[i] = a;
	}
	newsDepartIndex = 0;
	newsSubdepartIndex = 4;
}

void MainForm::showStatusText()
{
	if(statusList.size() == 0)
		return;
	
	QPushButton *button = (QPushButton *)sender();
	QString a = button->objectName();
	
	for(int i = 0; i < statusList.size(); i++)
	{
		if( statusList[i].contains(a) )
		{
			QStringList t = statusList[i].split("\t");
			statusTextEdit->clear();
			statusTextEdit->append( QString::fromLocal8Bit( t[1].toAscii().constData() ) );
			statusTextEdit->setAlignment( Qt::AlignCenter );
			break;
		}
	}
}

void MainForm::clearStatusText()
{
	statusTextEdit->clear();
}

void MainForm::playButtonSoundMove()
{
	if(!sound)
		return;
	
	QFile file(".//data//sounds//move.wav");
	if( !file.exists() )
		return;
	
	QSound::play(".//data//sounds//move.wav");
}

void MainForm::playButtonSoundPress()
{
	if(!sound)
		return;
	
	QPushButton *button = (QPushButton *)sender();
	
	if(button->objectName() == "powerButton")
	{
		QFile file(".//data//sounds//press_power.wav");
		if( !file.exists() )
			return;
		
		QSound::play(".//data//sounds//press_power.wav");
	}
	else
	{
		QFile file(".//data//sounds//press_arrow.wav");
		if( !file.exists() )
			return;
		
		QSound::play(".//data//sounds//press_arrow.wav");
	}
}

void MainForm::aboutSlot()
{
	QMessageBox::about(this, tr("About Encyclopedia"),
			   tr("<h3>Power of Law Encyclopedia %1</h3>"
					   "<p>\t..I really don't know, what to say here.."
					   "About some distributions rules?<br>"
					   "Hmm..according to the Qt 4 license rules, this program must be distributed under the GPL, but I really doubt, whether \"Power of Law\" publishers allow me to distribute some parts of their game stuff under the Free license.."
					   "<p>So..let's put here a small copyright, like doing that in any \"Big\" software companies.."
					   "<p>Copyright &copy; 2007; <b>ezheg</b> software; it's all for fun!"
					   "<p>Any questions or wishes about the program: <a href=mailto:popov.petr@gmail.com>popov.petr@gmail.com</a>").arg(version));
}


// Moving form--------------------------------------------
void MainForm::mousePressEvent(QMouseEvent *pe)
{
	if(pe->button() == Qt::LeftButton)
		mLeftPressed = true;
	mPosition = pe->pos();
}

void MainForm::mouseMoveEvent(QMouseEvent *pe)
{
	if( this->cursor().shape() != myCursor.shape() )
		setCursor( myCursor );
	
	if(mLeftPressed)
		move( pe->globalPos() - mPosition );	
}

void MainForm::mouseReleaseEvent(QMouseEvent *pe)
{
	if(pe->button() == Qt::LeftButton)
	{
		mLeftPressed = false;
	}
}
// End of moving form--------------------------------------------
