//
// Created by luojiayi on 5/18/17.
//
#include <memory>
#include <iostream>
#include <cassert>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[]){
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    printf("Hardware information: \n");
    printf("  OEM ID: %u\n", sys_info.dwOemId);
    printf("  Number of processors: %u\n",
        sys_info.dwNumberOfProcessors);
    printf("  Page size: %u\n", sys_info.dwPageSize);
    printf("  Processor type: %u\n", sys_info.dwProcessorType);
    printf("  Minimum application address: %lx\n",
        sys_info.lpMinimumApplicationAddress);
    printf("  Maximum application address: %lx\n",
        sys_info.lpMaximumApplicationAddress);
    printf("  Active processor mask: %u\n",
        sys_info.dwActiveProcessorMask);
    printf(" dwAllocationGranularity is %u\n", sys_info.dwAllocationGranularity);

    
    cin.get();
}
