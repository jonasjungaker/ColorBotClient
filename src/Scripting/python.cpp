#define PY_SSIZE_T_CLEAN
#include <python.h>
#include <iostream>

#include "Scripting/python.hpp"

namespace Client
{

PythonEngine::PythonEngine(wchar_t* programName)
{
    PyStatus status;
    PyConfig config;
    PyConfig_InitPythonConfig(&config);
    config.program_name = programName;
    Py_Initialize();
    std::cout << "[INFO] Initialized Python Engine..." << std::endl;
    std::cout << "Program name: " << Py_GetProgramName() << std::endl;
    std::cout << "Program full path: " << Py_GetProgramFullPath() << std::endl;
}

PythonEngine::~PythonEngine()
{
    Py_FinalizeEx();
}

PythonEngine::ScriptOutput PythonEngine::RunScript(PythonEngine::PythonScript script)
{
    PythonEngine::ScriptOutput out;
    out.data = nullptr;
    out.dataLength = 0;
    out.status = PythonEngine::ScriptOutput::Status::Good;

    FILE* myfile = fopen(script.scriptPath.c_str(), "rb");
    if (myfile == nullptr)
    {
        std::cout << "[ERROR] File " << script.scriptPath << " could not be opened" << std::endl;
        out.status = PythonEngine::ScriptOutput::Status::FileNotFound;
        // Early out since we can't execute the script
        return out;
    }

    PyRun_SimpleFileExFlags(myfile, script.scriptPath.c_str(), 0, NULL);
    fclose(myfile);
    
    if (PyErr_Occurred())
    {
        std::cout << "[ERROR] PythonEngine: Error occurred while executing script " << script.scriptPath << std::endl;
        out.status = PythonEngine::ScriptOutput::Status::ErrorOccured;
    }

    return out;
}

} // namespace Client
