//
// Created by amroy on 6/14/19.
//

#ifndef TEXDIV_TEXDIV_H
#define TEXDIV_TEXDIV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <boost/program_options.hpp>
//
//#define CL_HPP_TARGET_OPENCL_VERSION 120
//#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
////#define __NO_STD_VECTOR
//
//#if defined(__APPLE__) || defined(__MACOSX)
//#include "OpenCL/cl.hpp"
//#else
//#include <CL/cl.hpp>
//#endif

enum DivergenceType { KLD, CSD };

float csd_weibull(const float *models, size_t i, size_t j, size_t M, bool use_mci, size_t N);
float kld_weibull(const float *models, size_t i, size_t j, size_t M, bool use_mci, size_t N);
float* load_models(const std::string &filepath, int &M, int &D);

#endif //TEXDIV_TEXDIV_H
