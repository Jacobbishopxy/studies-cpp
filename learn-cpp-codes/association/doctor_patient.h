
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class Patient;

class Doctor
{
  private:
  std::string m_name{};
  std::vector<std::reference_wrapper<const Patient>> m_patient{};

  public:
  Doctor(const std::string& name)
      : m_name{name}
  {
  }

  void addPatient(Patient& patient);

  friend std::ostream& operator<<(std::ostream& out, const Doctor& doctor);

  const std::string& getName() const { return m_name; }
};

class Patient
{
  private:
  std::string m_name{};
  std::vector<std::reference_wrapper<const Doctor>> m_doctor{};

  void addDoctor(const Doctor& doctor) { m_doctor.push_back(doctor); }

  public:
  Patient(const std::string& name)
      : m_name{name}
  {
  }

  friend std::ostream& operator<<(std::ostream& out, const Patient& patient);

  const std::string& getName() const { return m_name; }

  friend void Doctor::addPatient(Patient& patient);
};

void Doctor::addPatient(Patient& patient)
{
  m_patient.push_back(patient);

  patient.addDoctor(*this);
}

std::ostream& operator<<(std::ostream& out, const Doctor& doctor)
{
  if (doctor.m_patient.empty())
  {
    out << doctor.m_name << " has no patients right now";
    return out;
  }

  out << doctor.m_name << " is seeing patients: ";
  for (const auto& patient : doctor.m_patient)
    out << patient.get().getName() << ' ';

  return out;
}

std::ostream& operator<<(std::ostream& out, const Patient& patient)
{
  if (patient.m_doctor.empty())
  {
    out << patient.getName() << " has no doctors right now";
    return out;
  }

  out << patient.m_name << " is seeing doctors: ";
  for (const auto& doctor : patient.m_doctor)
    out << doctor.get().getName() << ' ';

  return out;
}
