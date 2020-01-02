#ifndef CL_HELPER_H
#define CL_HELPER_H

#include <iostream>

#if CL_HPP_MINIMUM_OPENCL_VERSION <= 120 && !defined(CL_USE_DEPRECATED_OPENCL_1_2_APIS)
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#endif

#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

namespace mf_clh {
    cl::Platform getPlatform();
    cl::Device getDevice(cl::Platform platform, int i, bool display = true);
    char* readSource(const char *sourceFilename);
}

#endif