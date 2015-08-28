#include "Task.hpp"

cl_kernel       Task::getKernel() {
    return this->_kernel;
}

std::string     *Task::getSrc(std::string filename) const {
    std::ifstream ifs(filename);
    std::string *content;
        
    content = new std::string( (std::istreambuf_iterator<char>(ifs) ),
                            (std::istreambuf_iterator<char>()) );
    return content;
}

void            Task::enqueueKernel(cl_command_queue queue) {
    int     err;

    err = clEnqueueNDRangeKernel(
            queue,
            this->_kernel,
            1,
            NULL,
            &this->_globalWorkSize,
            &this->_localWorkSize,
            0,
            NULL,
            NULL);
    checkCLSuccess(err, "clEnqueueNDRangeKernel");
}

void        Task::_createKernel(std::string filename, std::string kernelName)
{
    std::string     *source;
    const char      *char_source;
    int             err;

    source = this->getSrc(filename);
    char_source = source->c_str();
    this->_program = clCreateProgramWithSource(this->_context, 1, &char_source, NULL, NULL);
    if (this->_program == NULL) {
        std::cerr << "Program creation fail" << std::endl;
        throw new OpenCLException;
    }
    delete source;


    err = clBuildProgram(this->_program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char    buildlog[16384];
        clGetProgramBuildInfo(this->_program, this->_device, CL_PROGRAM_BUILD_LOG, sizeof(buildlog), buildlog, NULL);
        std::cerr << "Error on compilation: " << std::endl;
        std::cerr << buildlog << std::endl;
        throw new OpenCLException();
    }

    this->_kernel = clCreateKernel(this->_program, kernelName.c_str(), &err);
    checkCLSuccess(err, "clCreateKernel");

    err = clGetKernelWorkGroupInfo(
        this->_kernel,
        this->_device,
        CL_KERNEL_WORK_GROUP_SIZE,
        sizeof(this->_localWorkSize),
        &(this->_localWorkSize),
        NULL);
    checkCLSuccess(err, "clGetKernelWorkGroupInfo");

    this->_nbWorkGroup = this->_nbParticle / this->_localWorkSize + 1;
    this->_globalWorkSize = this->_nbWorkGroup * this->_localWorkSize;
    this->_maxGid = this->_nbParticle - 1;
    std::cout << "max gid: " << this->_maxGid << std::endl;

    std::cout << "Local work size: " << this->_localWorkSize << std::endl;
    std::cout << "global work size: " << this->_globalWorkSize << std::endl;
    std::cout << "nb work group: " << this->_nbWorkGroup << std::endl;
}