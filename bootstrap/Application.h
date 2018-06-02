#pragma once

// forward declared structure for access to GLFW window
struct GLFWwindow;

namespace aie {

// this is the pure-virtual base class that wraps up an application for us.
// we derive our own applications from this class
class Application {
public:

	// STRUCT FOR NOW
	// MAKE IT ITS OWN CLASS THAT CHECK IF GLFW EXISTS
	// BEFORE INITIALISING IN CONSTRUCTOR INSTEAD OF
	// FUNCITON, ADD EXTRA STUFF LIKE RESET, VSYNC AND SUCH
	struct Timer
	{
		float GetCurrentTime() const { return (float)m_CurrentTime; }
		float GetPreviousTime() const { return (float)m_PreviousTime; }

		float GetDeltaTime() const { return (float)m_DeltaTime; }

		float GetStartTime() const { return (float)m_StartTime; }

		float GetTimeNow() const;

	private:

		friend Application;

		void InitTimer()
		{
			m_StartTime = GetTimeNow();
			
			m_CurrentTime = m_StartTime;
			m_PreviousTime = m_StartTime;
		}

		void Tick()
		{
			m_CurrentTime = GetTimeNow();

			m_DeltaTime = m_CurrentTime - m_PreviousTime;

			m_PreviousTime = m_CurrentTime;
		}

		double m_CurrentTime;
		double m_PreviousTime;

		double m_DeltaTime;

		double m_StartTime;
	};

public:

	Application();
	virtual ~Application();

	// creates a window and begins the game loop which calls update() and draw() repeatedly
	// it first calls startup() and if that succeeds it then starts the loop,
	// ending with shutdown() if m_gameOver is true
	void run(const char* title, int width, int height, bool fullscreen);

	// these functions must be implemented by a derived class
	virtual bool startup() = 0;
	virtual void shutdown() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;

	// wipes the screen clear to begin a frame of drawing
	void clearScreen();

	// sets the colour that the sceen is cleared to
	void setBackgroundColour(float r, float g, float b, float a = 1.0f);

	// show or hide the OS cursor
	void setShowCursor(bool visible);

	// enable or disable v-sync
	void setVSync(bool enabled);

	// sets m_gameOver to true which will close the application safely when the frame ends
	void quit() { m_gameOver = true; }

	// access to the GLFW window
	GLFWwindow* getWindowPtr() const { return m_window; }

	// query if the window has been closed somehow
	bool hasWindowClosed();

	// returns the frames-per-second that the loop is running at
	unsigned int getFPS() const { return m_fps; }

	// returns the width / height of the game window
	unsigned int getWindowWidth() const;
	unsigned int getWindowHeight() const;
	
	// returns time since application started
	float getTime() const;

	static Timer* GetTimer()
	{
		// Create the static timer
		static Timer m_Timer;

		// Return the static timer
		return &m_Timer;
	}

protected:

	virtual bool createWindow(const char* title, int width, int height, bool fullscreen);
	virtual void destroyWindow();

	GLFWwindow*		m_window;

	// if set to false, the main game loop will exit
	bool			m_gameOver;
	
	unsigned int	m_fps;
};

} // namespace aie