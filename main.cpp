#include"header.h"


class Handle : public tch::BaseHandle {
private:
	tch::FullTusurCommonConfig _config;
	_parametrs param;

protected:
	virtual void handle_set_bandwidth(float bandwidth) override {
		auto msg = "from c++ handle_set_bandwidt bandwidth: " + std::to_string(bandwidth);
		_config.bandwidth = bandwidth;
		std::cout << msg << std::endl;
		tch::write_common(msg);
	}
	virtual float handle_get_bandwidth() override {
		auto msg = "from c++ handle_get_bandwidt bandwidth: " + std::to_string(_config.bandwidth);
		std::cout << msg << std::endl;
		tch::write_common(msg);
		return _config.bandwidth;
	}

	virtual void handle_set_cp_mode(tch::CpMode mode) override {
		auto msg = "from c++ handle_set_cp_mode cp_mode: " + std::to_string((int)mode);
		_config.cp_mode = mode;
		std::cout << msg << std::endl;
		tch::write_common(msg);
	}
	virtual tch::CpMode handle_get_cp_mode() override {
		auto msg = "from c++ handle_get_cp_mode cp_mode: " + std::to_string((int)_config.cp_mode);
		std::cout << msg << std::endl;
		tch::write_common(msg);
		return _config.cp_mode;
	}

	virtual void handle_set_correlation_kind(tch::CorrelationKind kind) override {
		auto msg = "from c++ handle_set_correlation_kind correlation_kind: " + std::to_string((int)kind);
		_config.correlation_kind = kind;
		std::cout << msg << std::endl;
		tch::write_common(msg);
	}
	virtual tch::CorrelationKind handle_get_correlation_kind() override {
		auto msg = "from c++ handle_get_correlation_kind correlation_kind: " + std::to_string((int)_config.correlation_kind);
		std::cout << msg << std::endl;
		tch::write_common(msg);
		return _config.correlation_kind;
	}
		
	virtual void handle_set_correlation_level(size_t level) override {
		auto msg = "from c++ handle_set_correlation_level correlation_level: " + std::to_string(level);
		_config.correlation_level = level;
		std::cout << msg << std::endl;
		tch::write_common(msg);
	}
	virtual size_t handle_get_correlation_level() override {
		auto msg = "from c++ handle_get_correlation_level correlation_level: " + std::to_string(_config.correlation_level);
		std::cout << msg << std::endl;
		tch::write_common(msg);
		return _config.correlation_level;
	}

	virtual void handle_set_automatic_threshold(bool enable) override {
		auto msg = "from c++ handle_set_automatic_threshold automatic_threshold: " + std::to_string(enable);
		_config.automatic_threshold = enable;
		std::cout << msg << std::endl;
		tch::write_common(msg);
	}
	virtual bool handle_get_automatic_threshold() override {
		auto msg = "from c++ handle_get_automatic_threshold automatic_threshold: " + std::to_string(_config.automatic_threshold);
		std::cout << msg << std::endl;
		tch::write_common(msg);
		return _config.automatic_threshold;
	}

	virtual tch::FullTusurCommonConfig handle_configure() override {
		auto msg = "from c++ handle_configure";
		funk config(_config,&param);
		
		create_mark(param,_config);
		//std::string msg2 = "fftsize = " + std::to_string (param.fftsize) ;
		//std::cout << msg << std::endl;
		//tch::write_common(msg2);
		return _config;
	}
};



int main() {
	tch::init("python3.10", "info");
	

	Handle handle;

	tch::run("/home/debian/work/radius_control_software_tusur", &handle);


	return 0;
}
