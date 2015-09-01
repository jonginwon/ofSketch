// =============================================================================
//
// Copyright (c) 2013-2015 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "MakeToolchain.h"
#include "Project.h"
#include "ProcessTask.h"


namespace of {
namespace Sketch {


MakeToolchain::MakeToolchain(const std::string& name): BaseToolchain(name)
{
    _targets.reserve(2);
    _targets.push_back("DEBUG");
    _targets.push_back("RELEASE");
}

    
MakeToolchain::~MakeToolchain()
{
}

//#ifdef TARGET_WIN32
//    // Set up toolchain path information for Windows.
//    std::string pathVar = Poco::Environment::get("PATH","");
//
//    std::string pathToolChain0 = ofToDataPath("Toolchains/ofMinGW/MinGW/msys/1.0/bin", true);
//    std::string pathToolChain1 = ofToDataPath("Toolchains/ofMinGW/MinGW/bin", true);
//
//    std::stringstream pathSS;
//    pathSS << pathToolChain0 << ";" << pathToolChain1 << ";" << pathVar;
//    Poco::Environment::set("PATH", pathSS.str());
//#endif


Poco::Task* MakeToolchain::newBuildTask(const Project& project,
                                        const std::string& target) const
{
//    Poco::Path projectPath = _project.getPath();
//    std::string projectPathString = projectPath.toString(Poco::Path::PATH_UNIX);
//
//    Poco::Path ofRootPath = Poco::Path::forDirectory(_settings.ofRoot);
//    std::string ofRootPathString = ofRootPath.toString(Poco::Path::PATH_UNIX);
//
//#if defined(TARGET_WIN32)
//    // Replace colon in device path on windows.
//    ofStringReplace(projectPathString, ":", "");
//    ofStringReplace(ofRootPathString, ":", "");
//#endif
//
//    _args.push_back("--directory=" + projectPathString);
//
//    if (!_settings.ofRoot.empty())
//    {
//        _args.push_back("OF_ROOT=" + ofRootPathString);
//    }
//
//    if (_settings.numProcessors > 1)
//    {
//        _args.push_back("-j" + ofToString(_settings.numProcessors));
//    }
//
//    if (_settings.isSilent)
//    {
//        //_args.push_back("-s");
//    }
//
//    if (!_settings.CC.empty())
//    {
//        _args.push_back("CC=" + _settings.CC);
//    }
//
//    if (!_settings.CXX.empty())
//    {
//        _args.push_back("CXX=" + _settings.CXX);
//    }
//
//    if (!_settings.platformVariant.empty())
//    {
//        _args.push_back("PLATFORM_VARIANT=" + _settings.platformVariant);
//    }
//
//    if (_settings.makefileDebug)
//    {
//        _args.push_back("MAKEFILE_DEBUG=1");
//    }
//
//#if defined(TARGET_WIN32)
//    // uname doesn't return the right host info when the bash environment isn't in an MSYS shell.
//    _args.push_back("HOST_OS=MINGW32_NT-6.2");
//    _args.push_back("PLATFORM_OS=MINGW32_NT-6.2");
//    _args.push_back("PLATFORM_ARCH=i686");
//#endif
//
//    _args.push_back(_target);
//
//    ofLogNotice("MakeTask::MakeTask") << "Configuring Make Task with Args: " << ofToString(_args);

    return 0;
}


Poco::Task* MakeToolchain::newRunTask(const Project& project,
                                      const std::string& target) const
{
    return new ProcessTask(ProcessTaskSettings(project.getName(),
                                               getExecutablePath(project, target).toString()));

}


Poco::Path MakeToolchain::getExecutablePath(const Project& project,
                                            const std::string& target)
{
    std::string suffix = (target == "debug") ? "_debug" : "";

    Poco::Path projectPath = project.getPath();

    std::string exectuableName = project.getName();

    if (target == "debug")
    {
        exectuableName += "_debug";
    }

#if defined(TARGET_OSX)
    Poco::Path executablePath("bin/" + exectuableName + ".app/Contents/MacOS/",
                              exectuableName);
#else
    Poco::Path executablePath("bin/", exectuableName);
    
#endif
    
    return Poco::Path(projectPath, executablePath);
}


} } // namespace of::Sketch