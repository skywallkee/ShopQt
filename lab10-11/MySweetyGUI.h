#pragma once
#include <qwidget.h>
#include "service.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qstring.h>
#include <qerrormessage.h>
#include <qmessagebox.h>
#include <qtablewidget.h>

using std::to_string;
class MySweetyGUI: public QWidget {
public:
	MySweetyGUI(ProdusService& service) :service(service) {
		initGUIComponents();
		initialGUIState(service.getAll());
		connectSignals();
	}
private:
	ProdusService& service;

	QPushButton* btnAdd = new QPushButton("Adauga");
	QPushButton* btnRem = new QPushButton("Sterge");
	QPushButton* btnModif = new QPushButton("Modifica");
	QPushButton* btnUndo = new QPushButton("Undo");
	
	QPushButton* btnSortN = new QPushButton("Sorteaza dupa nume");
	QPushButton* btnSortP = new QPushButton("Sorteaza dupa producator");
	QPushButton* btnSortTP = new QPushButton("Sorteaza dupa tip &pret");
	
	QPushButton* btnFilterT = new QPushButton("Filtrare tip");
	QPushButton* btnFilterPL = new QPushButton("Filtrare pret mai mic");
	QPushButton* btnFilterPG = new QPushButton("Filtrare pret mai mare");
	QPushButton* btnFilterP = new QPushButton("Filtrare pret");

	QLineEdit* lineID = new QLineEdit;
	QLineEdit* lineNume = new QLineEdit;
	QLineEdit* lineTip = new QLineEdit;
	QLineEdit* linePret = new QLineEdit;
	QLineEdit* lineProducator = new QLineEdit;
	QLabel* lblCateNr = new QLabel;
	QLineEdit* filtruT = new QLineEdit;
	QLineEdit* filtruPL = new QLineEdit;
	QLineEdit* filtruPG = new QLineEdit;
	QLineEdit* filtruP1 = new QLineEdit;
	QLineEdit* filtruP2 = new QLineEdit;

	QListWidget* list = new QListWidget;
	QTableWidget* table = new QTableWidget(0,6,this);

	void initGUIComponents() {
		QWidget* main = new QWidget;

		QHBoxLayout* layout = new QHBoxLayout;
		QVBoxLayout* laySt = new QVBoxLayout;
		QVBoxLayout* layDr = new QVBoxLayout;

		QFormLayout* dreaptaSus = new QFormLayout;
		QHBoxLayout* layBtnSort = new QHBoxLayout;
		QHBoxLayout* layBtn = new QHBoxLayout;
		QHBoxLayout* titlu = new QHBoxLayout;
		QHBoxLayout* titlu2 = new QHBoxLayout;

		QHBoxLayout* layFiltruT = new QHBoxLayout;
		QHBoxLayout* layFiltruPL = new QHBoxLayout;
		QHBoxLayout* layFiltruPG = new QHBoxLayout;
		QHBoxLayout* layFiltruP = new QHBoxLayout;

		//stanga
		QLabel* produse = new QLabel("Lista de Produse");
		titlu->addStretch();
		titlu->addWidget(produse);
		titlu->addStretch();


		laySt->addLayout(titlu);
		//laySt->addWidget(list);
		laySt->addWidget(table);
		table->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
		table->setHorizontalHeaderItem(1, new QTableWidgetItem("Nume"));
		table->setHorizontalHeaderItem(2, new QTableWidgetItem("Tip"));
		table->setHorizontalHeaderItem(3, new QTableWidgetItem("Pret"));
		table->setHorizontalHeaderItem(4, new QTableWidgetItem("Producator"));
		table->setHorizontalHeaderItem(5, new QTableWidgetItem("Nr"));
		table->setSelectionBehavior(QAbstractItemView::SelectRows);
		layBtnSort->addWidget(btnSortN);
		layBtnSort->addWidget(btnSortP);
		layBtnSort->addWidget(btnSortTP);
		laySt->addLayout(layBtnSort);

		/*laySt->addWidget(btnFilterT);
		laySt->addWidget(btnFilterPL);
		laySt->addWidget(btnFilterPG);
		laySt->addWidget(btnFilterP);*/

		QLabel* lblFiltruT = new QLabel("Tip:");
		QLabel* lblFiltruPL = new QLabel("Pret maxim:");
		QLabel* lblFiltruPG = new QLabel("Pret minim:");
		QLabel* lblFiltruP1 = new QLabel("Minim:");
		QLabel* lblFiltruP2 = new QLabel("Maxim:");

		layFiltruT->addWidget(btnFilterT);
		layFiltruT->addWidget(lblFiltruT);
		layFiltruT->addWidget(filtruT);
		
		layFiltruPL->addWidget(btnFilterPL);
		layFiltruPL->addWidget(lblFiltruPL);
		layFiltruPL->addWidget(filtruPL);
		
		layFiltruPG->addWidget(btnFilterPG);
		layFiltruPG->addWidget(lblFiltruPG);
		layFiltruPG->addWidget(filtruPG);
		
		layFiltruP->addWidget(btnFilterP);
		layFiltruP->addWidget(lblFiltruP1);
		layFiltruP->addWidget(filtruP1);
		layFiltruP->addWidget(lblFiltruP2);
		layFiltruP->addWidget(filtruP2);
		
		layDr->addLayout(layFiltruT);
		layDr->addLayout(layFiltruPL);
		layDr->addLayout(layFiltruPG);
		layDr->addLayout(layFiltruP);

		//dreapta
		QLabel* produs_selectat = new QLabel("Detalii Produs Selectat");
		titlu2->addStretch();
		titlu2->addWidget(produs_selectat);
		titlu2->addStretch();


		layDr->addLayout(titlu2);

		QLabel* lblID = new QLabel("ID:");
		QLabel* lblNume = new QLabel("Nume:");
		QLabel* lblTip = new QLabel("Tip:");
		QLabel* lblPret = new QLabel("Pret:");
		QLabel* lblProducator = new QLabel("Producator:");
		QLabel* lblCate = new QLabel("Numar:");
		
		dreaptaSus->addRow(lblID, lineID);
		dreaptaSus->addRow(lblNume, lineNume);
		dreaptaSus->addRow(lblTip, lineTip);
		dreaptaSus->addRow(lblPret, linePret);
		dreaptaSus->addRow(lblProducator, lineProducator);
		dreaptaSus->addRow(lblCate, lblCateNr);

		layDr->addLayout(dreaptaSus);

		layBtn->addWidget(btnAdd);
		layBtn->addWidget(btnRem);
		layBtn->addWidget(btnModif);
		layBtn->addWidget(btnUndo);
		layDr->addLayout(layBtn);
		layDr->addStretch();

		layout->addLayout(laySt);
		layout->addLayout(layDr);
		main->setLayout(layout);
		main->show();
	}

	void initialGUIState(const vector<Produs> v) {
		table->setRowCount(0);
		int counter = 0;
		int size = service.getAll().size();
		list->clear();
		for (auto el : v) {
			table->insertRow(table->rowCount());

			int id = el.getId();
			string nume = el.getNume();
			string tip = el.getTip();
			int pret = el.getPret();
			string producator = el.getProducator();
			int nr = 0;
			for (auto el : service.getAll()) {
				if (el.getTip() == tip) {
					nr++;
				}
			}

			QTableWidgetItem* item1 = new QTableWidgetItem(to_string(id).c_str());
			QTableWidgetItem* item2 = new QTableWidgetItem(nume.c_str());
			QTableWidgetItem* item3 = new QTableWidgetItem(tip.c_str());
			QTableWidgetItem* item4 = new QTableWidgetItem(to_string(pret).c_str());
			QTableWidgetItem* item5 = new QTableWidgetItem(producator.c_str());
			QTableWidgetItem* item6 = new QTableWidgetItem(to_string(nr).c_str());


			if (counter < size / 3) {
				item1->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item2->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item3->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item4->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item5->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item6->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
			}
			else if (counter < 2 * size / 3) {
				item1->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item2->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item3->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item4->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item5->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item6->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
			}
			else {
				item1->setBackground(QBrush{ Qt::green,Qt::SolidPattern });
				item2->setBackground(QBrush{ Qt::green,Qt::SolidPattern });
				item3->setBackground(QBrush{ Qt::green,Qt::SolidPattern });
				item4->setBackground(QBrush{ Qt::green,Qt::SolidPattern });
				item5->setBackground(QBrush{ Qt::green,Qt::SolidPattern });
				item6->setBackground(QBrush{ Qt::green,Qt::SolidPattern });
			}
			counter++;
			table->setItem(table->rowCount() - 1, 0, item1);
			table->setItem(table->rowCount() - 1, 1, item2);
			table->setItem(table->rowCount() - 1, 2, item3);
			table->setItem(table->rowCount() - 1, 3, item4);
			table->setItem(table->rowCount() - 1, 4, item5);
			table->setItem(table->rowCount() - 1, 5, item6);
		}
	}
	

	void connectSignals() {
		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			try {
				int id = lineID->text().toInt();
				string nume = lineNume->text().toStdString();
				string tip = lineTip->text().toStdString();
				int pret = linePret->text().toInt();
				string producator = lineProducator->text().toStdString();
				service.adaugaProdus(id, nume, tip, pret, producator);
				initialGUIState(service.getAll());
			}
			catch (ValidatorException& err) {
				QMessageBox::warning(nullptr, "Eroare", "Ai grija la validare!");
			}
			catch (ProdusRepositoryException& err) {
				QMessageBox::warning(nullptr, "Eroare", "Adaugat deja!");
			}
		});
		QObject::connect(btnRem, &QPushButton::clicked, [&]() {
			try {
				int id = lineID->text().toInt();
				service.stergeProdus(id);
				initialGUIState(service.getAll());
			}
			catch(ProdusRepositoryException& err){
				QMessageBox::warning(nullptr, "Eroare", "Nu este gasit!");
			}
		});
		QObject::connect(btnModif, &QPushButton::clicked, [&]() {
			try
			{
				int id = lineID->text().toInt();
				string numeNou = lineNume->text().toStdString();
				string tipNou = lineTip->text().toStdString();
				int pretNou = linePret->text().toInt();
				string producatorNou = lineProducator->text().toStdString();
				service.modificaProdus(id, numeNou, tipNou, pretNou, producatorNou);
				initialGUIState(service.getAll());
			}
			catch (ProdusRepositoryException& err)
			{
				QMessageBox::warning(nullptr, "Eroare", "Nu este gasit!");
			}
		});
		QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
			try
			{
				service.undo();
				initialGUIState(service.getAll());
			}
			catch (ProdusRepositoryException& err)
			{
				QMessageBox::warning(nullptr, "Eroare", "Nu este gasit!");
			}
		});
		//sort
		QObject::connect(btnSortN, &QPushButton::clicked, [&]() {
			initialGUIState(service.sortareNume());
		});
		QObject::connect(btnSortP, &QPushButton::clicked, [&]() {
			initialGUIState(service.sortareProducator());
		});
		QObject::connect(btnSortTP, &QPushButton::clicked, [&]() {
			initialGUIState(service.sortareTipPret());
		});
		//filtre
		QObject::connect(btnFilterT, &QPushButton::clicked, [&]() {
			string tip = filtruT->text().toStdString();
			initialGUIState(service.filtrareTip(tip));
		});
		QObject::connect(btnFilterPL, &QPushButton::clicked, [&]() {
			int pret = filtruPL->text().toInt();
			initialGUIState(service.filtrarePretMaiMic(pret));
		});
		QObject::connect(btnFilterPG, &QPushButton::clicked, [&]() {
			int pret = filtruPG->text().toInt();
			initialGUIState(service.filtrarePretMaiMare(pret));
		});
		QObject::connect(btnFilterP, &QPushButton::clicked, [&]() {
			int pretMin = filtruP1->text().toInt();
			int pretMax = filtruP2->text().toInt();
			initialGUIState(service.filtrarePret(pretMin,pretMax));
		});

		QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
			if (table->selectedItems().isEmpty()) {
				lineID->setText(QString::fromStdString("1"));
			}
			else {
				QTableWidgetItem* id = table->selectedItems().at(0);
				QTableWidgetItem* nume = table->selectedItems().at(1);
				QTableWidgetItem* tip = table->selectedItems().at(2);
				QTableWidgetItem* pret = table->selectedItems().at(3);
				QTableWidgetItem* producator = table->selectedItems().at(4);
				QTableWidgetItem* nr = table->selectedItems().at(5);
				lineID->setText(id->text());
				lineNume->setText(nume->text());
				lineTip->setText(tip->text());
				linePret->setText(pret->text());
				lineProducator->setText(producator->text());
				lblCateNr->setText(nr->text());
			}
		});
	}
};