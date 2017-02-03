#pragma once

#ifndef _FEEDFORWARDNETWORKTOPOLOGYIO_H_
#define _FEEDFORWARDNETWORKTOPOLOGYIO_H_

// Includes
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"

namespace LightBulb
{
	/**
	* \brief Saves FeedForwardNetworkTopologyOptions.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param options The FeedForwardNetworkTopologyOptions to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, FeedForwardNetworkTopologyOptions const & options);
	
	/**
	* \brief Loads FeedForwardNetworkTopologyOptions.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param options The FeedForwardNetworkTopologyOptions to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, FeedForwardNetworkTopologyOptions& options);

	/**
	* \brief Saves a FeedForwardNetworkTopology.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param feedForwardNetworkTopology The FeedForwardNetworkTopologyOptions to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, FeedForwardNetworkTopology const & feedForwardNetworkTopology);

	/**
	* \brief Loads a FeedForwardNetworkTopology.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param feedForwardNetworkTopology The FeedForwardNetworkTopologyOptions to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, FeedForwardNetworkTopology & feedForwardNetworkTopology);

}

#endif
