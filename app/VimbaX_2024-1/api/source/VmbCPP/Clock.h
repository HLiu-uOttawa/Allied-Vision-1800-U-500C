/*=============================================================================
  Copyright (C) 2012 Allied Vision Technologies.  All Rights Reserved.

  Redistribution of this file, in original or modified form, without
  prior written consent of Allied Vision Technologies is prohibited.

-------------------------------------------------------------------------------

  File:        Clock.h

  Description: Definition of a platform independent Sleep.
               Intended for use in the implementation of VmbCPP.

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

#ifndef VMBCPP_CLOCK
#define VMBCPP_CLOCK

/**
* \file      Clock.h
*
* \brief     Definition of a platform independent Sleep.
*            Intended for use in the implementation of VmbCPP.
*/


namespace VmbCPP {

class Clock final
{
  public:
    Clock();
    ~Clock();

    void Reset();
    void SetStartTime();
    void SetStartTime( double dStartTime );
    double GetTime() const;

    static double GetAbsTime();

    static void Sleep( double dTime );
    static void SleepMS( unsigned long nTimeMS );
    static void SleepAbs( double dAbsTime );

  protected:
    double m_dStartTime;
};

}  // namespace VmbCPP

#endif //VMBCPP_CLOCK
