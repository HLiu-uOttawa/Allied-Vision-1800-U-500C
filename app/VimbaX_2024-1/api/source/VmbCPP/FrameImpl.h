/*=============================================================================
  Copyright (C) 2012 Allied Vision Technologies.  All Rights Reserved.

  Redistribution of this file, in original or modified form, without
  prior written consent of Allied Vision Technologies is prohibited.

-------------------------------------------------------------------------------

  File:        FrameImpl.h

  Description: Definition of pointer to implementation structure used by
               VmbCPP::Frame.
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

#ifndef VMBCPP_FRAMEIMPL_H
#define VMBCPP_FRAMEIMPL_H

/**
* \file        FrameImpl.h
*
* \brief       Definition of pointer to implementation structure used by
*              VmbCPP::Frame.
*              Intended for use in the implementation of VmbCPP.
*/


namespace VmbCPP {

struct Frame::Impl
{
    bool                m_bIsSelfAllocatedBuffer;

    VmbFrame_t          m_frame;

    IFrameObserverPtr   m_pObserver;
    MutexPtr            m_pObserverMutex;

    bool                m_bAlreadyAnnounced;
    bool                m_bAlreadyQueued;
    bool                m_bSynchronousGrab;

    void Init();
};

}

#endif
