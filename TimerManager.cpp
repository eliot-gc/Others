#include "TimerManager.h"
#include <iostream>

TimerManager::TimerManager() :
	  
	  m_timerTotalPauseTime(0)
	, m_timerIsStarted(false)
	, m_timerIsPaused(false)
	, m_timerPointIndicatorIsSet(false)

{}

using namespace std;

/**------- TIMER MANAGMENT -------*/

void TimerManager::StartTimer() {
	if (!m_timerIsStarted) {
		m_timerStartTime = chrono::high_resolution_clock::now();
		m_timerTotalPauseTime = chrono::duration<double>::zero();
		m_timerIsStarted = true;
		m_timerIsPaused = false;
	}
	else {
		cout << "Error->StartTimer(): timer is already started." << endl;
	}
}

void TimerManager::RestartTimer()
{
	m_timerStartTime = chrono::high_resolution_clock::now();
	m_timerTotalPauseTime = chrono::duration<double>::zero();
	m_timerIsStarted = true;
	m_timerIsPaused = false;
}

void TimerManager::StopTimer() {
	if (m_timerIsStarted) {
		m_timerEndTime = chrono::high_resolution_clock::now();
		m_timerIsStarted = false;
		m_timerIsPaused = false;
	}
	else {
		cout << "Error->StopTimer(): timer is not started." << endl;
	}
}

void TimerManager::PauseTimer() {
	if (m_timerIsStarted && !m_timerIsPaused) {
		m_timerIsPaused = true;
		m_timerPauseTime = chrono::high_resolution_clock::now();
	}
	else {
		cout << "Error->PauseTimer(): timer is not started or is already paused." << endl;
	}
}

void TimerManager::ResumeTimer() {
	if (m_timerIsStarted && m_timerIsPaused) {
		m_timerTotalPauseTime += chrono::high_resolution_clock::now() - m_timerPauseTime;
		m_timerIsPaused = false;
	}
	else {
		cout << "Error->ResumeTimer(): timer is not started or is not paused." << endl;
	}
}


void TimerManager::SetTimerPointIndicator() {
	m_timerPointIndicator = chrono::high_resolution_clock::now();
	m_timerPointIndicatorIsSet = true;
}


double TimerManager::GetElapsedTimeBtwLastTimerPointIndicatorInSeconds() const {
	if (m_timerPointIndicatorIsSet) {
		if (!m_timerIsPaused) {
			const auto elapsed = chrono::high_resolution_clock::now() - m_timerPointIndicator;
			return chrono::duration<double>(elapsed).count() - m_timerTotalPauseTime.count();
		}
		else {
			return chrono::duration<double>(m_timerPauseTime - m_timerPointIndicator - m_timerTotalPauseTime).count();
		}
		
	}
	else {
		std::cout << "Error->ResumeTimer(): timerPointIndicator is not set" << endl;
		return -1.f;
	}
}

string TimerManager::TimerPointConvertToDate(chrono::high_resolution_clock::time_point timePoint) {
	// Convert the time_point to system_clock::time_point
	const auto systemTimePoint = chrono::time_point_cast<chrono::system_clock::duration>(
		timePoint - chrono::high_resolution_clock::now() + chrono::system_clock::now()
	);

	// Convert the system_clock::time_point to time_t
	const time_t timeT = chrono::system_clock::to_time_t(systemTimePoint);

	// Convert time_t to struct tm
	tm tm; // Create a tm object
	localtime_s(&tm, &timeT); // Use localtime_s to get the local time  // NOLINT(cert-err33-c)

	// Format the date and time
	ostringstream oss;
	oss << put_time(&tm, "%Y-%m-%d %H:%M:%S"); // Format: "YYYY-MM-DD HH:MM:SS"

	return oss.str();
}

/**-----------------------------*/



/**---------- GETTERS ----------*/

double TimerManager::GetElapsedTimeInSeconds() const {
	if (m_timerIsStarted) {
		if (!m_timerIsPaused) {
			
		const auto elapsed = chrono::high_resolution_clock::now() - m_timerStartTime;
		return (chrono::duration<double>(elapsed).count() - m_timerTotalPauseTime.count()) / CLOCKS_PER_SEC;
		}
		else {
			return chrono::duration<double>(m_timerPauseTime - m_timerStartTime - m_timerTotalPauseTime).count();
		}
	}
	else {
		cout << "Error->GetElapsedTime(): timer is not started." << endl;
		return -1.f;
	}
}

double TimerManager::GetElapsedTimeInSeconds() const {
	if(m_timerIsStarted == false) {
		cout << "Error->GetElapsedTime(): timer is not started." << endl;
		return -1.f;
	}
	
	double elapsed;
	if(m_timerIsPaused) {
		elapsed = chrono::duration<double>(m_timerPauseTime - m_timerStartTime - m_timerTotalPauseTime).count();
	}
	else {
		elapsed = (chrono::high_resolution_clock::now() - m_timerStartTime).count();
	}

	return elapsed / CLOCKS_PER_SEC;
}

chrono::high_resolution_clock::time_point TimerManager::GetStartTime() const {
	return m_timerStartTime;
}

chrono::high_resolution_clock::time_point TimerManager::GetEndTime() const {
	return m_timerEndTime;
}

bool TimerManager::GetTimerIsPaused() const { return m_timerIsPaused; }
bool TimerManager::GetTimerIsStarted() const { return m_timerIsStarted; }

/**--------------------------*/