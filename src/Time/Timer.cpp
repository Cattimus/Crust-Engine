#include "Timer.hpp"
#include <SDL2/SDL_timer.h>

//Initialize values
void Timer::Init()
{
  startTime = 0;
  endTime = 0;
  enabled = false;
  onElapse = nullptr;
}

bool Timer::Elapsed()
{
  if((SDL_GetTicks() - endTime) < 0)
  {
    return true;
  }

  return false;
}

void Timer::Start(int32_t ms)
{
  startTime = SDL_GetTicks();
  endTime = startTime + ms;
}

void Timer::Reset()
{
  //don't enable the timer if there's no callback set
  if(!onElapse.IsSet())
  {
    return;
  }

  //get the timer duration
  int duration = endTime - startTime;
  
  //reset timer duration
  startTime = endTime;
  endTime += duration;

  enabled = true;
}

void Timer::Stop()
{
  enabled = false;
}

int32_t Timer::TimeSinceStarted()
{
  return SDL_GetTicks() - startTime;
}

int32_t Timer::TimeRemaining()
{
  return endTime - SDL_GetTicks();
}

void Timer::OnElapse(void (*callback)(void* args), void* args)
{
  this->onElapse = Action(callback, args);
}

//This needs to be called from the main loop to check
void Timer::CheckElapse()
{
  //call callback if timer is elapsed
  if(enabled && Elapsed())
  {
    onElapse.ExecuteWithArgs();
  }
}