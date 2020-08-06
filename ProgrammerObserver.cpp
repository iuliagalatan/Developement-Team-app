#include "ProgrammerObserver.h"
#include <QMessageBox>
#include <QModelIndex>


ProgrammerObserver::ProgrammerObserver(IssuesObservable& issuesObs, const QString& name, QSortFilterProxyModel* model, QWidget* parent)
	: QWidget(parent),
	issuesObs{ issuesObs },
	name{ name },
	model{ model }
{
	BuildGui();
	
	ui.tableView->setSortingEnabled(true);
	model->sort(0, Qt::AscendingOrder);
	model->sort(1, Qt::AscendingOrder);
	ui.tableView->setModel(model);

	ui.tableView->setColumnWidth(0, 350);
	ui.tableView->setColumnWidth(1, 100);
	ui.tableView->setColumnWidth(2, 100);
	ui.tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

	connect(ui.btnResolve, &QPushButton::clicked, this, &ProgrammerObserver::OnBtnResolveClicked);
	connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	connect(ui.btnRemove, &QPushButton::clicked, this, &ProgrammerObserver::OnBtnRemoveClicked);
}

ProgrammerObserver::~ProgrammerObserver()
{
}

void ProgrammerObserver::BuildGui()
{
	ui.setupUi(this);
	setWindowTitle(name + ": Programmer");
	setWindowIcon(QIcon("programmer.png"));
	setWindowFlags(Qt::WindowStaysOnTopHint);
	
	resize(700, 400);
	
}

void ProgrammerObserver::OnBtnResolveClicked()
{
	issuesObs.UpdateIssue(to_update);
}

void  ProgrammerObserver::OnBtnRemoveClicked()
{
	if (row_to_delete != -1)
	{
		model->removeRows(row_to_delete, 1);
		issuesObs.RemoveIssue(to_delete);
	}
	else
		QMessageBox::warning(this, "Warning", "Can't remove an open issue");
}

void ProgrammerObserver::onTableClicked(const QModelIndex& index)
{
	int row = index.row();
	
	std::string description = index.sibling(row, 0).data().toString().toStdString();
	std::string status = index.sibling(row, 1).data().toString().toStdString();
	std::string  reporter = index.sibling(row, 2).data().toString().toStdString();
	std::string  solver = index.sibling(row, 3).data().toString().toStdString();

	if (status == "closed")
	{
		to_delete = Issue{ description, Issue::closed, reporter, solver };
		row_to_delete = row;
		to_update = Issue{};
	}
	else
	{
		to_delete = Issue{};  // issue to delete from repository
		row_to_delete = -1;   // row to be deleted from tableView
		to_update = Issue{ description, Issue::closed, reporter, name.toStdString() };
	}
}

void ProgrammerObserver::update()
{
	ui.tableView->viewport()->update();
}

void ProgrammerObserver::show()
{
	QWidget::show();
}