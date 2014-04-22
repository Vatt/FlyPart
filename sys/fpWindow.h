#ifndef _FP_WINDOW_INCLUDE_
#define _FP_WINDOW_INCLUDE_


		class fpWindow
		{
		private:
			static unsigned int _wndCount;

		protected:
			unsigned int _id;
			bool _focus;
			bool _fullscreen;
			bool _deleted;
			int _x, _y;
			int _width, _height;
			const char * _name;
			bool _minimize;
			bool _hidden;


		public:
			fpWindow();
			//fpWindow(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool fullscreen);
			virtual unsigned int getId() const { return _id; }
			virtual ~fpWindow();
			virtual void createWindow(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool fullscreen) = 0;
			virtual bool switchFullscreen(bool flag) = 0;
			virtual void showWindow() = 0;
			virtual void deleteWindow() = 0;
			virtual void minimizeWindow() = 0;
			virtual void hideWindow() = 0;
			virtual void maximizeWindow() = 0;
			virtual void resize(unsigned int width, unsigned int height) = 0;
			virtual bool isFullscreen()const { return _fullscreen; }
			virtual bool isFocused()const{ return _focus; }
			virtual bool isMinimize()const { return _minimize; }
			virtual bool isDeleted()const { return _deleted; }
			virtual const char* getName()const { return _name; }
			//	virtual void* getRenderContext() = 0;
			//	virtual void restoreWindow() = 0;
			virtual void triggerEvent() = 0;
		};


#endif

