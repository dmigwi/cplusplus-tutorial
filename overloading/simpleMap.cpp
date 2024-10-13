#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct StudentGrade
{
    std::string m_name{};
    char m_grade{};

    StudentGrade(std::string name, char grade=' ')
        : m_name {name}, m_grade {grade}
        {}
};

class GradeMap
{
    public:
        char& operator[] (std::string studentName)
        {
            auto isStudent {
                [&](const StudentGrade& grade) { return grade.m_name == studentName; }
            };

            std::vector<StudentGrade>::iterator isFound { 
                std::find_if(m_map.begin(), m_map.end(), isStudent)
            };
            if (isFound != m_map.end())
                return isFound->m_grade;

            StudentGrade newStudentGrade {studentName};
            m_map.push_back(newStudentGrade);
            return m_map.back().m_grade;
        }

    private:
        std::vector<StudentGrade> m_map{};
};

int main()
{
	GradeMap grades{};

	grades["Joe"] = 'A';
	grades["Frank"] = 'B';

    char& gradeJoe{ grades["Joe"] }; // does an emplace_back
    char& gradeFrank{ grades["Frank"] }; // does a emplace_back

    gradeJoe = 'C';
	gradeFrank = 'D';

	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

	std::cout << "Joe has a grade of " << gradeJoe << '\n';
	std::cout << "Frank has a grade of " << gradeFrank << '\n';

	return 0;
}