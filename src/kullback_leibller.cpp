//
// Created by amroy on 7/3/19.
//

#include "kullack_leibller.h"

texdiv::KullbackLeibller::KullbackLeibller(std::string model_name, int nbmodels, int nbfeatures) : nb_features(nbfeatures),
                                                                                                   nb_models(nbmodels), model_name(model_name) {
}

texdiv::KullbackLeibller::~KullbackLeibller() {

}

bool texdiv::KullbackLeibller::
init() {
    // Init OpenCL Program and context
    cl_platform = mf_clh::getPlatform();
    gpu_device = mf_clh::getDevice(cl_platform, 0);
    cl_context = cl::Context({ gpu_device });

    char kernel_filename[256];
    sprintf(kernel_filename, "kernels/%s_kld.cl", model_name.c_str());
    std::string kld_kernel_code(mf_clh::readSource(kernel_filename));
    cl_kernel_sources = cl::Program::Sources();
    cl_kernel_sources.push_back(std::make_pair(kld_kernel_code.c_str(), kld_kernel_code.length() + 1));

    cl_program = cl::Program(cl_context, cl_kernel_sources);
    if (cl_program.build({ gpu_device }) != CL_SUCCESS) {
        std::cout << "Error building: " << cl_program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(gpu_device) << std::endl;
        exit(1);
    }

    models_buffer = cl::Buffer(cl_context, CL_MEM_READ_ONLY, sizeof(float) * nb_models * nb_features);
    divs_buffer   = cl::Buffer(cl_context, CL_MEM_READ_WRITE, sizeof(float) * nb_models * nb_models);

    return true;
}

float* texdiv::KullbackLeibller::
compute(float *models) {
    float *divs = (float *)malloc(sizeof(float) * nb_models * nb_models);
    cl::CommandQueue queue = cl::CommandQueue(cl_context, gpu_device);
    cl::Kernel kernel(cl_program, "weibull_kld");
    cl::Event event;

    queue.enqueueWriteBuffer(models_buffer, CL_FALSE, 0, sizeof(float) * nb_models * nb_features, models);
    queue.enqueueWriteBuffer(divs_buffer, CL_TRUE, 0, sizeof(float) * nb_models * nb_models, divs);

    // Set arguments to kernel
    kernel.setArg(0, models_buffer);
    kernel.setArg(1, divs_buffer);
    kernel.setArg(2, nb_models);
    kernel.setArg(3, nb_features);

    cl_ulong time_start;
    cl_ulong time_end;

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(nb_models * nb_models), cl::NullRange, NULL, &event);
    queue.enqueueReadBuffer(divs_buffer, CL_TRUE, 0, sizeof(float) * nb_models * nb_models, divs);

    event.getProfilingInfo(CL_PROFILING_COMMAND_START, &time_start);
    event.getProfilingInfo(CL_PROFILING_COMMAND_END, &time_end);

    double exec_time = time_end - time_start;
    printf("KLD divergences between %d %s models computed in: %0.3f milliseconds \n", nb_models, model_name.c_str(), exec_time / 1000000.0);

    return divs;
}
