// #include <iostream>
#include <CL/sycl.hpp>
#define LENGTH 20

class evenNumberGenerator;

int main(int, char **)
{
    cl::sycl::double a[LENGTH] = {0};
    cl::sycl::int k = 2;

    cl::sycl::default_selector device_selector;

    cl::sycl::queue queue(device_selector);
    std::cout << "Running on "
              << queue.get_device().get_info<cl::sycl::info::device::name>()
              << "\n";
    {
        cl::sycl::buffer<cl::sycl::double, 1> a_sycl(&a, cl::sycl::range<1>(1));
        cl::sycl::buffer<cl::sycl::int, 1> k_sycl(&b, cl::sycl::range<1>(1));

        queue.submit([&](cl::sycl::handler &cgh)
                     {
            auto a_acc = a_sycl.get_access<cl::sycl::access::mode::read_write>(cgh);
            auto k_acc = k_sycl.get_access<cl::sycl::access::mode::read>(cgh);

            cgh.parallel_for<class evenNumberGenerator>(cl::sycl::range<1>{LENGTH}[=] (cl::sycl::id<1> id) {
                a_acc[id] = a_acc[id - 1] + k_acc[0];
            }); });
    }

    std::cout << "A array:" << endl;

    for (int i = 0; i < LENGTH; i++)
    {
        std::cout << a[i] << " ,";
    }

    return 0;
}