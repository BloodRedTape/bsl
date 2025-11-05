#include "bsl/stacktrace.hpp"

#if BSL_WITH_STACKTRACE

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push)
#pragma warning(disable : 4091)
#include <DbgHelp.h>
#pragma warning(pop)
#endif

#ifdef __unix__
#include <execinfo.h>
#include <dlfcn.h>
#include <cxxabi.h>
#endif

void Stacktrace::Capture(void* (&frames)[MaxFramesCount], size_t& captured_frames){
#ifdef _WIN32
	captured_frames = CaptureStackBackTrace(1, MaxFramesCount, frames, nullptr);
#elif defined(__unix__)
    captured_frames = backtrace(frames, MaxFramesCount);
#else
	captured_frames = 0;
#endif
}

std::ostream& operator<<(std::ostream& stream, const Stacktrace& trace){
#ifdef _WIN32
    HANDLE process = GetCurrentProcess();

    SymInitialize(process, NULL, TRUE);

    SYMBOL_INFO *symbol = (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);

    if(!symbol){
        stream << "<Stacktrace memory alloc routine failed>";
        return stream;
    }

    symbol->MaxNameLen = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    for(size_t i = 1 + trace.m_SkipFrames; i < trace.m_CapturedFrames; i++) {
        static_assert(sizeof(trace.m_FramePointers[0]) == sizeof(DWORD64), "Winapi type size mismatch");

        SymFromAddr(process, (DWORD64)(trace.m_FramePointers[i]), 0, symbol);

        char buffer[1024] = {0};
        size_t offset = (std::uint8_t*)trace.m_FramePointers[i] - (std::uint8_t*)symbol->Address;
        snprintf(buffer, sizeof(buffer),"%-3zi [0x%0llX] %s + %zi", i - trace.m_SkipFrames, symbol->Address, symbol->Name, offset);

        stream << buffer << '\n';
    }
    free(symbol);
#elif defined(__unix__)
    char **symbols = backtrace_symbols(value.m_FramePointers, value.m_CapturedFrames);
    if (!symbols) {
        stream << "<Stacktrace symbols routine failed>";
        return stream;
    }
    char buf[2048] = {0};
    for(int i = 1; i < value.m_CapturedFrames; i++) {

        Dl_info info;
        if(dladdr(value.m_FramePointers[i], &info) && info.dli_sname){
            char *demangled = NULL;

            int status = -1;
            if (info.dli_sname[0] == '_')
                demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);

            const char *proc_name = (status == 0 ? demangled : (info.dli_sname == 0 ? symbols[i] : info.dli_sname));
            size_t offset = (u8 *)value.m_FramePointers[i] - (u8 *)info.dli_saddr;
            const char *filename = info.dli_fname;
            void *frame_address = value.m_FramePointers[i];

            snprintf(buf, sizeof(buf), "%-3d 0x%016lx %s :: %s + %zd", i, (size_t)frame_address, filename, proc_name, offset);

            free(demangled);
        }else{
            snprintf(buf, sizeof(buf), "%-3d 0x%016lx %s", i, (size_t)value.m_FramePointers[i], symbols[i]);
        }

        stream << buf << '\n';
    }
    free(symbols);
#else
    stream << "<Stacktrace is not supported>\n";
#endif
	return stream;
}

#else
void Stacktrace::Capture(void* (&frames)[MaxFramesCount], size_t& captured_frames){
	captured_frames = 0;
}
std::ostream& operator<<(std::ostream& stream, const Stacktrace& trace){
    stream << "<bsl stacktrace is disabled>\n";
	return stream;
}

#endif
