//
// Created by amroy on 7/3/19.
//

#ifndef TEXDIV_KULLACK_LEIBLLER_H
#define TEXDIV_KULLACK_LEIBLLER_H

#include <iostream>
#include <string>
#include "cl_helper.h"

namespace texdiv {
    class KullbackLeibller {
    public:
        KullbackLeibller(std::string model_name, int nbmodels, int nbfeatures);
        ~KullbackLeibller();

        bool init();

        float* compute(float *models);

    private:
        std::string model_name;
        int nb_models;
        int nb_features;

        // OpenCL objects
        cl::Platform			cl_platform;
        cl::Device				gpu_device;
        cl::Context				cl_context;
        cl::Program::Sources	cl_kernel_sources;
        cl::Program				cl_program;

        cl::Buffer models_buffer;
        cl::Buffer divs_buffer;
    };
}

#endif //TEXDIV_KULLACK_LEIBLLER_H
