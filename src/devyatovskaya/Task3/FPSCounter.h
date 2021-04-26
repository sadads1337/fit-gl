#pragma once
#include <chrono>
#include <QObject>

class FPSCounter final : public QObject
{
	
	Q_OBJECT
signals:
	void emit_fps(const QString&);
	
public:
	void calculate_fps();


	[[nodisacrd]] float delta_time() const noexcept;
private:
	
	QString fps_to_str() const;
	
	std::chrono::time_point<std::chrono::system_clock> last_frame_time_;
	int frame_counter_{ 0 };
	float delta_time_{ 0 };
	float average_fps_{ 0 };
	float elapsed_frame_time_{ 0 };
};
