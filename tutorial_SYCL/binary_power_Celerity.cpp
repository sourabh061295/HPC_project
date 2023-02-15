#include <iostream>
#include <celerity/celerity.h>
#define LENGTH 20

class binaryPower;

int main(int, char **)
{
    int a[LENGTH] = {0};
    int k = 2;

    celerity::distr_queue queue();

    std::cout << "Running on "
              << queue.get_device().get_info<sycl::info::device::name>()
              << "\n";
    {
        auto a_buff = celerity::buffer{a, celerity::range{LENGTH}};
        auto k_buff = celerity::buffer{&k, celerity::range{1}};

        queue.submit([&](celerity::handler &cgh)
                     {
            celerity::accessor a_acc{a_buff, cgh, celerity::access::one_to_one{}, celerity::write_only, celerity::no_init};
            celerity::accessor k_kcc{a_buff, cgh, celerity::access::one_to_one{}, celerity::read_only};

            cgh.parallel_for<class binaryPower>(celerity::range<1>{LENGTH}, [=](celerity::id<1> id) {
                a_acc[id] = (1 << id);
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