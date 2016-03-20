#pragma once

#ifndef _DATATABLE_H_
#define _DATATABLE_H_
#include <SFGUI/Table.hpp>

// Includes

// Forward declarations

class DataTable : public sfg::Table
{
protected:
	void addCell(std::string content, int x, int y);
public:
	typedef std::shared_ptr<DataTable> Ptr; ///< Shared pointer shortcut.
	typedef std::shared_ptr<const DataTable> PtrConst; ///< Shared pointer shortcut.

	DataTable();
	static Ptr Create();
	void setData(std::vector<std::vector<std::string>> data, std::vector<std::string> columnNames);
	const std::string& GetName() const;
};

#endif
