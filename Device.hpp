#ifndef DEVICE_HPP
# define DEVICE_HPP

# include <OpenCL/cl.h>
# include "clUtil.hpp"
# include <iostream>

class Device {
    public:
        Device( cl_platform_id platformId );
        void    displayInfoDevices();
        void    queryInfoDevice(cl_device_info query, int idDevice, std::string paramName);
    private:
        cl_uint         _nbDevices;
        cl_device_id    *_deviceIds;
        cl_platform_id  _platformId;
};

#endif
