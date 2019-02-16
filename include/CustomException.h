#include <string>
#include <limits>


struct InputMismatchException : public std::exception {
	std::string m_data;
	InputMismatchException(const std::string& t_error_signal) 
	: m_data(t_error_signal){}
	const char* what() const throw () {
		return m_data.c_str();
	}
	~InputMismatchException() {}
};

struct FilesNotFound : public std::exception {
	std::string m_data;
	std::string m_filePath;
	FilesNotFound(const std::string& t_error_signal, const std::string& t_filepath_missing)
	: m_data(t_error_signal) , m_filePath(t_filepath_missing) {}
	const char* what() const throw () {
		return m_data.c_str();
	}
};
