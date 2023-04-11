/*BEGIN_LEGAL 
BSD License 

Copyright (c)2022 Intel Corporation. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */
#include <iostream>
#include "pin.H"
#include "NVBitShim.h"
#include "NVBitHandler.H"
#ifdef SDE_INIT
#  include "sde-init.H"
#  include "sde-control.H"
#endif


using namespace std;
NVBIT_HANDLER nvbit_handler;

void CPU_on_gpu_fini()
{
  cerr << "\t->CPU_on_gpu_fini()" << endl;
}

void CPU_on_kernel_run(const char *kname)
{
  cerr << "\t->CPU_on_kernel_run():" << kname << endl;
}

void CPU_on_kernel_complete(const char *kname)
{
  cerr << "\t->CPU_on_kernel_complete():" << kname << endl;
}

INT32 Usage()
{
    cerr << KNOB_BASE::StringKnobSummary() << endl;

    return -1;
}


// argc, argv are the entire command line, including pin -t <toolname> -- ...
int main(int argc, char * argv[])
{
#if defined(SDE_INIT)
    sde_pin_init(argc,argv);
    sde_init();
#else
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
#endif
    PIN_InitSymbols();
    nvbit_handler.Activate(CPU_on_kernel_run,CPU_on_kernel_complete,CPU_on_gpu_fini);

    if(nvbit_handler.KnobProbe)
      PIN_StartProgramProbed();
    else
      PIN_StartProgram();

    return 0;
}
