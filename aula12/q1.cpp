#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    map<string, map<string, pair<float, float>>> students;

    for (int i = 0; i < n; i++)
    {
        string student_name;
        int n_courses;
        cin >> student_name >> n_courses;

        for (int j = 0; j < n_courses; j++)
        {
            string course_name;
            float prct_missed, grade;
            cin >> course_name >> prct_missed >> grade;

            students[student_name][course_name] = make_pair(prct_missed, grade);
        }
    }

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string name, course;
        cin >> name >> course;

        // verificar se curso existe
        if (students[name].find(course) == students[name].end())
        {
            cout << "NAO_CURSOU\n";
            continue;
        }

        float prct_missed = students[name][course].first;
        float grade = students[name][course].second;

        if (grade >= 7 && prct_missed <= 0.25)
            cout << "APROVADO\n";
        else
            cout << "REPROVADO\n";
    }

    return 0;
}