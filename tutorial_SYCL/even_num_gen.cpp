// #include <iostream>
#include <CL/sycl.hpp>
#define LENGTH 20

class evenNumberGenerator;

int main(int, char **)
{
    int a[LENGTH] = {0};
    int k = 2;

    cl::sycl::default_selector device_selector;

    cl::sycl::queue queue(device_selector);
    std::cout << "Running on "
              << queue.get_device().get_info<cl::sycl::info::device::name>()
              << "\n";
    {
        auto a_sycl = cl::sycl::buffer<int, 1>(&a, cl::sycl::range<1>{LENGTH});
        auto k_sycl = cl::sycl::buffer<int, 1>(&k, cl::sycl::range<1>(1));

        queue.submit([&](cl::sycl::handler &cgh)
                     {
            auto a_acc = a_sycl.get_access<cl::sycl::access::mode::read_write>(cgh);
            auto k_acc = k_sycl.get_access<cl::sycl::access::mode::read>(cgh);

            cgh.parallel_for<class evenNumberGenerator>(cl::sycl::range<1>{LENGTH}, [=](cl::sycl::id<1> id) {
                a_acc[id] = a_acc[id - 1] + k_acc[0];
            }); });
    }

    std::cout << "A array:" << std::endl;

    for (int i = 0; i < LENGTH; i++)
    {
        std::cout << a[i] << " ,";
    }

    return 0;
}