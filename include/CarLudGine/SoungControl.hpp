
#pragma once

namespace clg_SoungControl
{
	class SoungControl
	{
	public:
		SoungControl(const char* name);
		~SoungControl();

		void run();
		void stop();
		void loop();
		void chageVolume(const int volume);
		void reset();
		void speed(const int number);
		void slowDown(const int number);
		void back();
		void next();

		int  getVolume();
		int  getNumberNextOrBack();
		void setNumberNextOrBack(const int number);

	protected:
		bool getIsRun();
		bool getIsStop();

	private:
		bool _isRun;
		bool _isStop;
		int  _volume;
		int  _numberNextOrBack;
	};

}
