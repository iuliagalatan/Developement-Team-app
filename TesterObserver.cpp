#include "TesterObserver.h"
#include <QIcon>
#include <QMessageBox>
#include <QModelIndex>
#include <QSortFilterProxyModel>

TesterObserver::TesterObserver(IssuesObservable& issuesObs, const QString& name, QSortFilterProxyModel* model, QWidget* parent)
	: QWidget(parent), 
	issuesObs {issuesObs},
	name {name},
	model{ model }
{
	ui.setupUi(this);
	setWindowTitle(name + ": Tester");
	setWindowIcon(QIcon("tester.jpg"));
	setWindowFlags(Qt::WindowStaysOnTopHint);
	resize(700, 400);

	ui.tableView->setSortingEnabled(true);
	model->sort(0, Qt::AscendingOrder);
	model->sort(1, Qt::AscendingOrder);
	ui.tableView->setModel(model);
	

	ui.tableView->setColumnWidth(0, 350);
	ui.tableView->setColumnWidth(1, 100);
	ui.tableView->setColumnWidth(2, 100);
	ui.tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);	

	connect(ui.btnAdd, &QPushButton::clicked, this, &TesterObserver::OnBtnAddClicked);
	connect(ui.tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	connect(ui.btnRemove, &QPushButton::clicked, this, &TesterObserver::OnBtnRemoveClicked);
}


void TesterObserver::OnBtnAddClicked()
{
	std::string description = ui.leIssue->text().toStdString();
	if (description == "")
	{
		QMessageBox::warning(this, "Error", "The issue is not writen");
		return;
	}

	for (auto issue: issuesObs.GetIssues())
		if (issue.GetDescription() == description)
		{
			QMessageBox::warning(this, "Error", "The issue was already rised");
			return;
		}

	Issue issue { description, Issue::open, name.toStdString(), "nobody" };
	
	issuesObs.AddIssue(issue);

	int rows = issuesObs.GetIssues().size();
	model->insertRows(rows - 1, 1, QModelIndex{});
	model->sort(0, Qt::AscendingOrder);  // sort view in ascending order by Description
	model->sort(1, Qt::AscendingOrder);  // sort view in ascending order by Status
}

TesterObserver::~TesterObserver()
{

}

void TesterObserver::update()
{
	ui.tableView->viewport()->update();
}

void TesterObserver::show()
{
	QWidget::show();
}

void TesterObserver::OnBtnRemoveClicked()
{
	if (row_to_delete != -1)
	{
		model->removeRows(row_to_delete, 1);
		issuesObs.RemoveIssue(to_delete);
	}
	else
		QMessageBox::warning(this, "Warning", "Can't remove an open issue");
}

void TesterObserver::onTableClicked(const QModelIndex& index)
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
	}
	else
	{
		to_delete = Issue{};
		row_to_delete = -1;
	}
}