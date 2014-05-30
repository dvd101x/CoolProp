#include <tr1/memory>
#include "SpeedTest.h"
#include "AbstractState.h"
#include "DataStructures.h"

#include <time.h>

namespace CoolProp{

void compare_REFPROP_and_CoolProp(std::string fluid, int inputs, double val1, double val2, std::size_t N, double d1, double d2)
{
    time_t t1,t2;
    double dx = 1/((double)N);

    std::tr1::shared_ptr<AbstractState> State(AbstractState::factory("HEOS", fluid));
    t1 = clock();
    for (std::size_t ii = 0; ii < N; ++ii)
    {
        State->update(inputs, val1 + ii*d1, val2 + ii*d2);
    }
    t2 = clock();

    double elap = ((double)(t2-t1))/CLOCKS_PER_SEC/((double)N)*1e6;
    printf("Elapsed time for CoolProp is %g us/call\n",elap);

    State.reset(AbstractState::factory("REFPROP", fluid));
    t1 = clock();
    for (std::size_t ii = 0; ii < N; ++ii)
    {
        State->update(inputs, val1 + ii*d1, val2 + ii*d2);
    }
    t2 = clock();
    elap = ((double)(t2-t1))/CLOCKS_PER_SEC/((double)N)*1e6;
    printf("Elapsed time for REFPROP is %g us/call\n",elap);
}

} /* namespace CoolProp */
