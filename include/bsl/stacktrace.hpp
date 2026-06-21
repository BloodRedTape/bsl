#pragma once

#include <cstdint>
#include <ostream>
#include <vector>
#include <string>

struct StackFrame {
    void*       Address     = nullptr;
    void*       SymbolAddr  = nullptr;
    std::string Function;
    std::string Module;
    std::size_t Offset      = 0;
};

class Stacktrace{
    static constexpr size_t MaxFramesCount = 256;
private:
    void *m_FramePointers[MaxFramesCount];
    std::size_t m_CapturedFrames = 0;
    std::size_t m_SkipFrames = 0;
public:
    Stacktrace(size_t skip_frames = 0):
        m_SkipFrames(skip_frames)
    {
        Capture(m_FramePointers, m_CapturedFrames);
    }

    std::vector<StackFrame> GetFrames() const;

    friend std::ostream &operator<<(std::ostream &stream, const Stacktrace &trace);
private:

    static void Capture(void *(&frames)[MaxFramesCount], size_t &captured_frames);
};