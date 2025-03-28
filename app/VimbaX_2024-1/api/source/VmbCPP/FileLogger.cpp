/*=============================================================================
  Copyright (C) 2012-2022 Allied Vision Technologies.  All Rights Reserved.

  Redistribution of this file, in original or modified form, without
  prior written consent of Allied Vision Technologies is prohibited.

-------------------------------------------------------------------------------

  File:        FileLogger.cpp

  Description: Implementation of class VmbCPP::FileLogger.

-------------------------------------------------------------------------------

  THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF TITLE,
  NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR  PURPOSE ARE
  DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, 
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED  
  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

#include <ctime>
#include <cstdlib>

#include <VmbCPP/FileLogger.h>

#include "MutexGuard.h"

#ifdef _WIN32
#pragma warning(disable: 4996)
#include <Windows.h>
#else //_WIN32
#include <sys/stat.h>
#endif //_WIN32


namespace VmbCPP {

FileLogger::FileLogger( const char *pFileName, bool bAppend )
    :   m_pMutex(new Mutex())
{
    std::string strTempPath = GetTemporaryDirectoryPath();
    std::string strFileName( pFileName );

    if (!strTempPath.empty())
    {
        strFileName = strTempPath.append( strFileName );
        if( true == bAppend )
        {
            m_File.open( strFileName.c_str(), std::fstream::app );
        }
        else
        {
            m_File.open( strFileName.c_str() );
        }
    }
    else
    {
        throw;
    }
}

FileLogger::~FileLogger()
{
    if(m_File.is_open())
    {
        m_File.close();
    }
}

void FileLogger::Log( const std::string &rStrMessage )
{
    MutexGuard guard( m_pMutex );

    if(m_File.is_open())
    {
        #ifdef _WIN32
            time_t nTime = time( &nTime );
            tm timeInfo;
            localtime_s( &timeInfo, &nTime );
            char strTime[100];
            asctime_s( strTime, 100, &timeInfo );
        #else
            time_t nTime = time( nullptr );
            std::string strTime = asctime( localtime( &nTime ) );
        #endif

        m_File << strTime << ": " << rStrMessage << std::endl;
    }
}

std::string FileLogger::GetTemporaryDirectoryPath()
{
#ifndef _WIN32
    std::string tmpDir;
    
    if(tmpDir.size() == 0)
    {
        char *pPath = std::getenv("TMPDIR");
        if(nullptr != pPath)
        {
            struct stat lStats;
            if(stat(pPath, &lStats) == 0)
            {
                tmpDir = pPath;
            }
        }
    }
    if(tmpDir.size() == 0)
    {
        char *pPath = std::getenv("TEMP");
        if(nullptr != pPath)
        {
            struct stat lStats;
            if(stat(pPath, &lStats) == 0)
            {
                tmpDir = pPath;
            }
        }
    }
    if(tmpDir.size() == 0)
    {
        char *pPath = std::getenv("TMP");
        if(nullptr != pPath)
        {
            struct stat lStats;
            if(stat(pPath, &lStats) == 0)
            {
                tmpDir = pPath;
            }
        }
    }
    if(tmpDir.size() == 0)
    {
        std::string path = "/tmp";
        struct stat lStats;
        if(stat(path.c_str(), &lStats) == 0)
        {
            tmpDir = path;
        }
    }
    if(tmpDir.size() == 0)
    {
        std::string path = "/var/tmp";
        struct stat lStats;
        if(stat(path.c_str(), &lStats) == 0)
        {
            tmpDir = path;
        }
    }
    if(tmpDir.size() == 0)
    {
        std::string path = "/usr/tmp";
        struct stat lStats;
        if(stat(path.c_str(), &lStats) == 0)
        {
            tmpDir = path;
        }
    }
    if(tmpDir.size() == 0)
    {
        return "";
    }
    // everyone expects delimiter on the outside
    if( (*tmpDir.rbegin()) != '/' )
    {
        tmpDir +='/';
    }
    return tmpDir;
#else
    DWORD length = ::GetTempPathA( 0, nullptr );
    if( length == 0 )
    {
        return "";
    }
    
    std::vector<TCHAR> tempPath( length );

    length = ::GetTempPathA( static_cast<DWORD>( tempPath.size() ), &tempPath[0] );
    if( length == 0 || length > tempPath.size() )
    {
        return "";
    }

    return std::string( tempPath.begin(), tempPath.begin() + static_cast<std::size_t>(length) );
#endif
}

}  // namespace VmbCPP
