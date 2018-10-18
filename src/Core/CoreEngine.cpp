//
// Created by erick on 9/7/18.
//

#include "CoreEngine.h"
#include "../Common/Time.h"

bool CoreEngine::Init() {
    if(m_window == nullptr
    || m_game == nullptr
    || m_renderingEngine == nullptr
    || m_physicsEngine == nullptr) return false;

    m_window->Initialize();

    m_renderingEngine->setWindow(m_window);
    m_renderingEngine->Initialize();

    m_physicsEngine->Initialize();

    m_game->SetEngine(this);
    m_game->Init();

    return true;
}

void CoreEngine::Start() {
    if(m_isRunning) { //If already running
        return;
    } else {
        m_isRunning = true;
        Run();
    }
}

void CoreEngine::Run() {
    double lastTime = Time::GetTime(); //Current time at the start of the BlastEngine
    double unProcessedTime = 0; //Amount of passed time that the engine hasn't accounted for

    double FPSDisplayTimer = 0;           //Total passed time since last frame counter display
    int FPSFrameCounter = 0;                    //Number of FPSFrameCounter rendered since last

    while(m_isRunning){
        m_shouldRender = false;

        double startTime = Time::GetTime();       //Current time at the start of the frame.
        double passedTime = startTime - lastTime; //Amount of passed time since last frame.
        lastTime = startTime;

        unProcessedTime += passedTime;
        FPSDisplayTimer += passedTime;

        //DO profiling statistics display
        //The engine displays profiling statistics after every second because it needs to display them at some point.
        //The choice of once per second is arbitrary, and can be changed as needed.
        if(FPSDisplayTimer >= 1.0)
        {
            double totalTime = ((1000.0 * FPSDisplayTimer)/((double)FPSFrameCounter));
            double totalMeasuredTime = 0.0;

            totalMeasuredTime += m_inputTimer.DisplayAndReset("Input Time: ", (double)FPSFrameCounter);
            totalMeasuredTime += m_updateTimer.DisplayAndReset("Update Time: ", (double)FPSFrameCounter);
            totalMeasuredTime += m_renderProfileTimer.DisplayAndReset("Render Time: ", (double)FPSFrameCounter);
            totalMeasuredTime += m_sleepTimer.DisplayAndReset("Sleep Time: ", (double)FPSFrameCounter);
            totalMeasuredTime += m_swapBufferTimer.DisplayAndReset("Buffer Swap Time: ", (double)FPSFrameCounter);
//            totalMeasuredTime += m_renderingEngine->DisplayWindowSyncTime((double)FPSFrameCounter);

            printf("Frames (FPS):                           %d ps\n", FPSFrameCounter);
            printf("FrameLimit:                             %lf s\n", m_frameTimeLimit);
            printf("Other Time:                             %f ms\n", (totalTime - totalMeasuredTime));
            printf("Total Time:                             %f ms\n\n", totalTime);
            FPSFrameCounter = 0;
            FPSDisplayTimer = 0;
        }

        //The engine works on a fixed update system, where each update is 1/frameRate seconds of time.
        //Because of this, there can be a situation where there is, for instance, a fixed update of 16ms,
        //but 20ms of actual time has passed. To ensure all time is accounted for, all passed time is
        //stored in unprocessedTime, and then the engine processes as much time as it can. Any
        //unaccounted time can then be processed later, since it will remain stored in unprocessedTime.
        while(unProcessedTime >= m_frameTimeLimit)
        {
            if(m_window->getShouldClose()) Stop();

            //Input must be processed here because the window may have found new
            //input events from the OS when it updated. Since inputs can trigger
            //new game actions, the game also needs to be updated immediately
            //afterwards.
            glfwPollEvents(); //Update input system

            m_inputTimer.StartInvocation();
                m_game->ProcessInput(m_window->getInput(), (float)m_frameTimeLimit);
            m_inputTimer.StopInvocation();

            m_updateTimer.StartInvocation();
                m_game->Update(m_time_since_start, (float)m_frameTimeLimit);
            m_updateTimer.StopInvocation();

            //The scene has been updated therefore rerender the scene.
            m_shouldRender = true;
            unProcessedTime -= m_frameTimeLimit; //Account for un-processed time
            m_time_since_start += m_frameTimeLimit;
        }

        if(m_shouldRender)
        {
            m_window->Clear(0.0f, 0.0f, 0.0f, 0.0f);

            //Render game
            m_renderProfileTimer.StartInvocation();
                m_game->Render();
            m_renderProfileTimer.StopInvocation();


            //The newly rendered image will be in the window's backbuffer,
            //so the buffers must be swapped to display the new image.
            m_swapBufferTimer.StartInvocation();
                m_window->Update();
            m_swapBufferTimer.StopInvocation();
            FPSFrameCounter++;
        } else {
            //If no rendering is needed, sleep for some time so the OS
            //can use the processor for other tasks.
            m_sleepTimer.StartInvocation();
                Util::Sleep(1);
            m_sleepTimer.StopInvocation();
        }

    }
}


void CoreEngine::Stop() {
    if(!m_isRunning) { //IF NOT RUNNING
        return;
    }else{
        m_isRunning = false;
        m_shouldRender = false;
    }
}

