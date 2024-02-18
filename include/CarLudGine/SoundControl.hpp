
#pragma once

namespace clg_SoundControl
{
	class SoundControl
	{
	public:
		explicit SoundControl(const char* name, unsigned char volume = 50,
			unsigned char number_next_or_back = 5);
		~SoundControl();
		SoundControl( const SoundControl &other )                 = delete;
		SoundControl( SoundControl &&other ) noexcept             = delete;
		SoundControl & operator=( const SoundControl &other )     = delete;
		SoundControl & operator=( SoundControl &&other ) noexcept = delete;

		void run();
		void stop();
		[[noreturn]] void loop();
		void chageVolume(int volume);
		void reset();
		void speed(int number);
		void slowDown(int number);
		void back();
		void next();

		[[nodiscard]] unsigned char getVolume() const;
		[[nodiscard]] unsigned char getNumberNextOrBack() const;
		void setNumberNextOrBack(unsigned char number);

	protected:
		[[nodiscard]] bool getIsRun() const;
		[[nodiscard]] bool getIsStop() const;

	private:
		bool _isRun;
		bool _isStop;
		unsigned char _volume;
		unsigned char _numberNextOrBack;
		const char* _name;
	};

}
