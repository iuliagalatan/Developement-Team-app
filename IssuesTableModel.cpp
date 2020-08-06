#include "IssuesTableModel.h"
#include "DevelopmentTeam.h"

QVariant IssuesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString("Description");
			case 1:
				return QString("Status");	
			case 2:
				return QString("Reporter");
			case 3:
				return QString("Solver");
				
			}
		}
	}
	return QVariant();
}

QVariant IssuesTableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant{};

	int row = index.row();
	int col = index.column();
	if (row < 0 || col < 0)
		return QVariant{};
	std::vector<Issue> issues = service->GetIssues();
	Issue issue = issues[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (col)
		{
		case 0:
			return QString::fromStdString(issue.GetDescription());
		case 1:
			return QString::fromStdString(issue.GetStatus());
		case 2:
			return QString::fromStdString(issue.GetReporter());
		case 3:
			return QString::fromStdString(issue.GetSolver());
		default:
			break;
		}
		
	}
	return QVariant();
}

int IssuesTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

int IssuesTableModel::rowCount(const QModelIndex& parent) const
{
	return service->GetIssues().size();
}

bool IssuesTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), row, row + count - 1);
	
	endInsertRows();
	return true;
}

// we don't need removeRows 
bool IssuesTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	
	endRemoveRows();
	return true;
}

// we don't need setData; MyList model it's not editable
bool IssuesTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	return false;
}

Qt::ItemFlags IssuesTableModel::flags(const QModelIndex& index) const
{

	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
