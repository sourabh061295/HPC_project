// #include <iostream>
#include <CL/sycl.hpp>
#define LENGTH 20

class evenNumberGenerator;

int main(int, char **)
{
    std::vector a(LENGTH);
    a[0] = 0;
    int k = 2;

    cl::sycl::default_selector device_selector;

    cl::sycl::queue queue(device_selector);
    std::cout << "Running on "
              << queue.get_device().get_info<cl::sycl::info::device::name>()
              << "\n";
    {
        cl::sycl::buffer a_sycl(&a);
        cl::sycl::buffer k_sycl(&k);

        queue.submit([&](cl::sycl::handler &cgh)
                     {
            auto a_acc = a_sycl.get_access<cl::sycl::access::mode::read_write>(cgh);
            auto k_acc = k_sycl.get_access<cl::sycl::access::mode::read>(cgh);

            cgh.parallel_for<class evenNumberGenerator>(cl::sycl::range<1>{LENGTH}, [=](cl::sycl::id<1> id) {
                int i = id.get_global(0);
                a_acc[i] = a_acc[i - 1] + k_acc[0];
            }); });
    }

    std::cout << "A array:" << std::endl;

    for (int i = 0; i < LENGTH; i++)
    {
        std::cout << a[i] << " ,";
    }

    return 0;
}