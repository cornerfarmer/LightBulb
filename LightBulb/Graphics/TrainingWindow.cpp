// Includes
#include "Graphics/TrainingWindow.hpp"
#include <SFGUI/Box.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/Entry.hpp>
#include <SFGUI/Scale.hpp>
#include "DataTable.hpp"

void TrainingWindow::build()
{
	AbstractWindow::build();

	auto mainColumns = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 1.0f);

	auto nnColumn = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 1.0f);

	nnColumn->Pack(sfg::Label::Create("Neural networks:"), false);

	std::vector<std::vector<std::string>> data(5, std::vector<std::string>(3));
	data[0][0] = "NN#1";
	data[0][1] = "8-3-8";
	data[0][2] = "10.24.1253 21:23";

	data[1][0] = "NN#2";
	data[1][1] = "2-33-8";
	data[1][2] = "10.24.1253 21:23";

	data[2][0] = "NN#3";
	data[2][1] = "5-3-8";
	data[2][2] = "12.24.1253 21:23";

	data[3][0] = "NN#4";
	data[3][1] = "5-3-0";
	data[3][2] = "12.24.1253 13:23";

	data[4][0] = "NN#5";
	data[4][1] = "5-3-1";
	data[4][2] = "12.34.1853 13:53";

	std::vector<std::string> columnNames = {{"Name", "Size", "Date"}};

	auto dataTable = DataTable::Create();
	dataTable->setData(data, columnNames);

	nnColumn->Pack(dataTable);

	mainColumns->Pack(nnColumn);


	auto learningColumn = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 1.0f);

	learningColumn->Pack(sfg::Label::Create("Learning rules:"));

	mainColumns->Pack(learningColumn);


	auto runningLearningColumn = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 1.0f);

	runningLearningColumn->Pack(sfg::Label::Create("Running learning rules:"));

	mainColumns->Pack(runningLearningColumn);

	window->Add(mainColumns);
}
