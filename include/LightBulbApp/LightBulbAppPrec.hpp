#include "LightBulb/LightBulbPrec.hpp"




#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"

#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"

#include "LightBulb/Function/ActivationFunction/BinaryFunction.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulb/Function/ActivationFunction/HyperbolicTangentFunction.hpp"
#include "LightBulb/Function/ActivationFunction/IdentityFunction.hpp"
#include "LightBulb/Function/ActivationFunction/RectifierFunction.hpp"

#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"

#include "LightBulb/Function/RandomFunction/EqualRandomFunction.hpp"
#include "LightBulb/Function/RandomFunction/RankBasedRandomFunction.hpp"

#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"

#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

#include "LightBulb/IO/Exporter/SynapticExporter.hpp"
#include "LightBulb/IO/Exporter/BrainJSExporter.hpp"

#include "LightBulb/Learning/Evolution/StochasticUniversalSamplingSelector.hpp"

#include "LightBulb/Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/BestReuseSelector.hpp"



#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/dataview.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/xy/xyplot.h>
#include <wx/xy/xysimpledataset.h>
#include <wx/xy/xylinerenderer.h>
#include <wx/valnum.h>
#include <wx/dcbuffer.h>
#include <wx/splitter.h>
#include <wx/artprov.h>
#include <wx/statline.h>
#include <wx/timer.h>