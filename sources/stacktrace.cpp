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

std::vector<StackFrame> Stacktrace::GetFrames() const {
    std::vector<StackFrame> result;

#ifdef _WIN32
    HANDLE process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);

    SYMBOL_INFO* symbol = (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
    if (!symbol) return result;

    symbol->MaxNameLen   = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    for (size_t i = 1 + m_SkipFrames; i < m_CapturedFrames; i++) {
        StackFrame frame;
        frame.Address = m_FramePointers[i];

        if (SymFromAddr(process, (DWORD64)m_FramePointers[i], 0, symbol)) {
            frame.SymbolAddr = (void*)symbol->Address;
            frame.Function   = symbol->Name;
            frame.Offset     = (std::uint8_t*)m_FramePointers[i] - (std::uint8_t*)symbol->Address;

            HMODULE hmod = nullptr;
            if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                  (LPCTSTR)m_FramePointers[i], &hmod)) {
                char mod_path[MAX_PATH] = {0};
                if (GetModuleFileNameA(hmod, mod_path, MAX_PATH))
                    frame.Module = mod_path;
            }
        }

        result.push_back(frame);
    }
    free(symbol);
#elif defined(__unix__)
    char** symbols = backtrace_symbols(m_FramePointers, m_CapturedFrames);

    for (size_t i = 1 + m_SkipFrames; i < m_CapturedFrames; i++) {
        StackFrame frame;
        frame.Address = m_FramePointers[i];

        Dl_info info;
        if (dladdr(m_FramePointers[i], &info) && info.dli_sname) {
            char* demangled = nullptr;
            int status = -1;
            if (info.dli_sname[0] == '_')
                demangled = abi::__cxa_demangle(info.dli_sname, nullptr, 0, &status);

            frame.Function   = (status == 0 && demangled) ? demangled : (info.dli_sname ? info.dli_sname : (symbols ? symbols[i] : ""));
            frame.SymbolAddr = info.dli_saddr;
            frame.Offset     = (std::uint8_t*)m_FramePointers[i] - (std::uint8_t*)info.dli_saddr;
            frame.Module     = info.dli_fname ? info.dli_fname : "";
            free(demangled);
        } else if (symbols) {
            frame.Function = symbols[i];
        }

        result.push_back(frame);
    }
    if (symbols) free(symbols);
#endif

    return result;
}

std::ostream& operator<<(std::ostream& stream, const Stacktrace& trace){
    auto frames = trace.GetFrames();

    if (frames.empty()) {
        stream << "<Stacktrace is not supported>\n";
        return stream;
    }

    char buf[1024];
    for (size_t i = 0; i < frames.size(); i++) {
        const auto& f = frames[i];
        if (!f.Function.empty())
            snprintf(buf, sizeof(buf), "%-3zu 0x%016zx %s :: %s + %zu",
                i, (size_t)f.Address,
                f.Module.empty() ? "?" : f.Module.c_str(),
                f.Function.c_str(), f.Offset);
        else
            snprintf(buf, sizeof(buf), "%-3zu 0x%016zx %s",
                i, (size_t)f.Address,
                f.Module.empty() ? "<unknown>" : f.Module.c_str());
        stream << buf << '\n';
    }

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
