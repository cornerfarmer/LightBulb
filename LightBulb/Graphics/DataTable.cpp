// Includes
#include "Graphics/DataTable.hpp"
#include <SFGUI/Label.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Entry.hpp>

void DataTable::addCell(std::string content, int x, int y)
{
	auto cell = sfg::Entry::Create(content);
	Attach(cell, sf::Rect<sf::Uint32>(x, y, 1, 1), sfg::Table::EXPAND | sfg::Table::FILL, sfg::Table::FILL);
}

DataTable::DataTable()
{

}

DataTable::Ptr DataTable::Create()
{
	return Ptr(new DataTable());
}

void DataTable::setData(std::vector<std::vector<std::string>> data, std::vector<std::string> columnNames)
{
	for (int i = 0; i < columnNames.size(); i++)
	{
		addCell(columnNames[i], i, 0);
	}

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			addCell(data[i][j], j, i + 1);
		}
	}

	SetRowSpacings(0);
	SetColumnSpacings(0);
}

const std::string& DataTable::GetName() const
{
	static const std::string name("DataTable");
	return name;
}
