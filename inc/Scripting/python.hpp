#pragma once
#include <string>

namespace Client
{

class PythonEngine
{
public:
    struct ScriptOutput
    {
        enum Status
        {
            Good,
            FileNotFound,
            ErrorOccured
        };
        Status status;
        size_t dataLength;
        void* data;
    };

    struct PythonScript
    {
        std::string scriptPath;
        PythonScript(std::string path) : scriptPath(path) {}
    };

public:
    PythonEngine(wchar_t* programName);
    ~PythonEngine();

    ScriptOutput RunScript(PythonScript script);
private:

};

} // namespace Client
