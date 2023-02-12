// #include <iostream>
#include <SYCL/sycl.hpp>
#define LENGTH 20

class evenNumberGenerator;

int main(int, char **)
{
    int a[LENGTH];
    a[0] = 0;
    int k = 2;

    sycl::default_selector device_selector;

    sycl::queue queue(device_selector);

    std::cout << "Running on "
              << queue.get_device().get_info<sycl::info::device::name>()
              << "\n";
    {
        auto a_sycl = sycl::buffer{a, sycl::range{LENGTH}};
        auto k_sycl = sycl::buffer{&k, sycl::range{1}};

        queue.submit([&](sycl::handler &cgh)
                     {
            auto a_acc = a_sycl.get_access<sycl::access::mode::read_write>(cgh);
            auto k_acc = k_sycl.get_access<sycl::access::mode::read>(cgh);

            cgh.parallel_for<class evenNumberGenerator>(sycl::range<1>{LENGTH}, [=](sycl::id<1> id) {
                a_acc[id] = k_acc[0];
            }); });
    }

    std::cout << "A array:" << std::endl;

    for (int i = 0; i < LENGTH; i++)
    {
        std::cout << a[i] << " ,";
    }

    std::cout << std::endl;

    return 0;
}