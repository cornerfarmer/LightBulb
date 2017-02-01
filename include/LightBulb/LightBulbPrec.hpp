
#include <map>
#include <vector>
#include <mutex>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <cmath>

#include <Eigen/Dense>

#include <viennacl/vector.hpp>
#include <viennacl/scalar.hpp>
#include <viennacl/matrix.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/access.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/json.hpp>