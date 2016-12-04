#ifndef _LEARNINGRESULT_H_
#define _LEARNINGRESULT_H_
#include <vector>
#include <map>
#include "LightBulb/Event/Observable.hpp"

namespace LightBulb
{
	/**
	 * \brief All events LearningState can throw.
	 */
	enum LearningStateEvents
	{
		/**
		 * \brief Is thrown if a dataset has changed.
		 */
		EVT_LS_DS_CHANGED
	};
	/**
	 * \brief Describes a simple dataset.
	 */
	typedef std::vector<double> DataSet;
	/**
	 * \brief Contains all datasets of try mapped with their name.
	 */
	typedef std::map<std::string, DataSet> DataSetsPerTry;
	/**
	 * \brief Contains all datasets.
	 */
	typedef std::vector<DataSetsPerTry> DataSets;
	/**
	 * \brief All information about the current learning process
	 */
	struct LearningState : public Observable<LearningStateEvents, LearningState>
	{
		template <class Archive>
		friend void serialize(Archive& archive, LearningState& learningState);
	private:
		/**
		 * \brief Determines after how many iterations the data sets should be filled.
		 */
		int dataSaveInterval;
	public:
		/**
		 * \brief The current number of completed iterations.
		 */
		int iterations;
		/**
		* \brief The current number of completed tries.
		*/
		int tries;
		/**
		* \brief Contains for every try a map which holds dataset label -> vector of doubles
		*/
		DataSets dataSets;
		/**
		 * \brief Contains all dataset labels which should be completely disabled.
		 */
		std::map<std::string, bool> disabledDatasets;

		/**
		 * \brief Creates a empty learning state.
		 * \param disabledDatasets_ All dataset labels which should be completely disabled.
		 * \param dataSaveInterval_ Determines after how many iterations the data sets should be filled.
		 */
		LearningState(std::map<std::string, bool>& disabledDatasets_, int dataSaveInterval_ = 1)
		{
			disabledDatasets = disabledDatasets_;
			iterations = 0;
			tries = 0;
			dataSaveInterval = dataSaveInterval_;
		}
		/**
		 * \brief Adds data for the determined data set.
		 * \param dataSetLabel The label of the data set.
		 * \param data The new data.
		 * \note Depending on the selected data save interval, this method does not always store the given data.
		 */
		void addData(const std::string& dataSetLabel, double data)
		{
			if ((iterations - 1) % dataSaveInterval == 0)
			{
				dataSets[tries - 1][dataSetLabel].push_back(iterations - 1);
				dataSets[tries - 1][dataSetLabel].push_back(data);
				throwEvent(EVT_LS_DS_CHANGED, *this);
			}
		}
		/**
		 * \brief Advances to the next try.
		 */
		void addTry()
		{
			dataSets.push_back(DataSetsPerTry());
			tries++;
		}
	};
}

#include "LightBulb/IO/LearningStateIO.hpp"

#endif
