#pragma once

#ifndef _ABSTRACTNETWORKEXPORTER_H_
#define _ABSTRACTNETWORKEXPORTER_H_

// Library includes
#include <string>

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	/**
	 * \brief Describes an neural network exporter to export networks for other software.
	 */
	class AbstractNetworkExporter
	{
	private:
	public:
		virtual ~AbstractNetworkExporter() {}
		/**
		 * \brief Returns the name of the exporter.
		 * \return The name.
		 */
		virtual std::string getName() const = 0;
		/**
		 * \brief Returns the default file extensions of the export format.
		 * \return The file extensions.
		 */
		virtual std::string getFileExtensions() const = 0;
		/**
		 * \brief Exports the given network to the file with the given path.
		 * \param path Determines where to save the file.
		 * \param neuralNetwork The neural network to export.
		 */
		virtual void exportToFile(std::string path, const AbstractNeuralNetwork& neuralNetwork);
		/**
		 * \brief Exports the network as a string.
		 * \param neuralNetwork The neural network to export.
		 * \return The exported string.
		 */
		virtual std::string exportToString(const AbstractNeuralNetwork& neuralNetwork) = 0;
	};
}

#endif