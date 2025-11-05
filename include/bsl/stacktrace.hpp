#pragma once

#include <cstdint>
#include <ostream>

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

    friend std::ostream &operator<<(std::ostream &stream, const Stacktrace &trace);
private:

    static void Capture(void *(&frames)[MaxFramesCount], size_t &captured_frames);
};