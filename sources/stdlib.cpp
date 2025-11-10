#include "bsl/stdlib.hpp"
#include <signal.h>

static Runtime::FailureHandlerType s_FailureHandler = nullptr;

namespace Runtime{

    static void OnTerminate() {
        if(s_FailureHandler) s_FailureHandler();
        std::abort();
    }

    static void OnSignal(int signum) {
        if(s_FailureHandler) s_FailureHandler();
        std::exit(signum);
    }
}//namespace Runtime::

void Runtime::SetFailureHandler(FailureHandlerType handler) {
    s_FailureHandler = handler;

	std::set_terminate(Runtime::OnTerminate);
    signal(SIGABRT, Runtime::OnSignal);
    signal(SIGSEGV, Runtime::OnSignal);
    signal(SIGILL, Runtime::OnSignal);
    signal(SIGFPE, Runtime::OnSignal);
}
