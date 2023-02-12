#include <mpi.h>
#include <iostream>
#include <SYCL/sycl.hpp>

#define LENGTH 20

class binaryPower;

void binaryPowerKernel(sycl::queue q, int *off, int *arr, int len)
{
    auto a_sycl = sycl::buffer{&arr[(*off)], sycl::range{len}};

    q.submit([&](sycl::handler &cgh)
             {
        auto a_acc = a_sycl.get_access<sycl::access::mode::read_write>(cgh);

        cgh.parallel_for<class binaryPower>(sycl::range<1>{len}, [=](sycl::id<1> id) {
            a_acc[id] = (1 << (id + (*off)));
        }); });

    *off = (*off) + len;
}

int main()
{
    int size;
    int rank;
    int offset;
    int a[LENGTH] = {0};
    int num_proc = 4;
    int len_per_proc = LENGTH / num_proc;

    sycl::default_selector device_selector;
    sycl::queue queue(device_selector);

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        offset = 0;
    }
    else
    {
        MPI_Recv(&offset, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // binaryPowerKernel(queue, offset, a, len_per_proc);
        std::cout << "Perform the kernel here" << std::endl;
        offset += len_per_proc;
        std::cout << "Process " << rank << " received an offset " << offset << " from process " << size - 1 << std::endl;
        std::cout << "Process " << rank << " updated the offset to " << offset << std::endl;
    }

    MPI_Send(&offset, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        MPI_Recv(&offset, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Process " << rank << " received an offset " << offset << " from process " << size - 1 << std::endl;
    }

    std::cout << "A array:" << std::endl;

    for (int i = 0; i < LENGTH; i++)
    {
        std::cout << a[i] << " ,";
    }

    std::cout << std::endl;

    MPI_Finalize();
    return 0;
}