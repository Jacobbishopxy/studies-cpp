#include <iostream>
#include <string>
#include <string_view>

// Preferred for small use case, but no further information can be stored, such
// as descriptive string.
enum class ArrayExceptionEnum
{
  OutOfRangeError,
  MaxLengthReachedError,
};

// Class's overhead is very high, but on the other hand, it can store extra
// information.
class ArrayException
{
  public:
  enum Type
  {
    OutOfRangeError,
    MaxLengthReachedError,
  };

  // extra info can be stored
  private:
  Type m_error;
  std::string m_info;

  public:
  ArrayException(Type error)
      : m_error{error}
  {
  }
  ArrayException(Type error, std::string_view info)
      : m_error{error}, m_info{info}
  {
  }

  const Type& getError() const { return m_error; }

  const std::string& getInfo() const { return m_info; }

  // other member functions
};

// inherited from std::exception
class ArrayExceptionStdExcp : public std::exception
{
  private:
  std::string m_error{};

  public:
  ArrayExceptionStdExcp(std::string_view error)
      : m_error{error}
  {
  }

  const char* what() const noexcept override { return m_error.c_str(); }
};

// inherited from std::runtime_error
class ArrayExceptionStdRte : public std::runtime_error
{
  public:
  ArrayExceptionStdRte(const std::string& error)
      : std::runtime_error(error.c_str())
  {
  }
};

int main(int argc, char const* argv[])
{
  try
  {
    throw ArrayExceptionEnum::MaxLengthReachedError;
  }
  catch (const ArrayExceptionEnum&)
  {
    std::cout << "hah" << std::endl;
  }

  try
  {
    throw ArrayException{ArrayException::OutOfRangeError, "My bad!"};
  }
  catch (const ArrayException& exception)
  {
    switch (exception.getError())
    {
    case ArrayException::OutOfRangeError:
      std::cout << "oor " << exception.getInfo() << std::endl;
      break;

    case ArrayException::MaxLengthReachedError:
      std::cout << "mlre " << exception.getInfo() << std::endl;
      break;

    default:
      std::cout << "???" << std::endl;
      break;
    }
  }

  return 0;
}
